#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opennna_core.h"

/************************OpenNNA堆内存申请总量****************************/
int OpenNNA_Heap_Sum = 0;
/************************OpenNNA输入/输出特征图堆内存****************************/
data_t *Input_Fmap_Heap = NULL;
data_t *Output_Fmap_Heap = NULL;
int Max_Fmap_Heap = 0;//输入/输出堆内存占用，最终占用需要*2。为了实现相邻层之间堆内存翻转，所以以最大的堆内存消耗来申请堆内存。
//这个设计的优点是 逻辑简单
//缺点是对堆内存的管理粒度比较粗，面向网络管理。 没有精确到每一个层的堆内存生命周期。对系统的堆内存占用将会是恒定的。
//对于MCU等SRAM比较紧张的平台来说，堆内存管理粒度需要精确到层算子的计算，这样的生命周期管理是内存友好型的。
//容易发现的是，当堆内存管理粒度越小时，内存占用越小。但代码越复杂。
//OpenNNA会依次探索2种堆内存管理粒度实现之间的区别，比较他们的优缺点。
//堆内存管理粒度由粗到细分别为:网络，网络层(算子)。
//再小的粒度从内存角度是没有意义的，因为神经网络计算是个串行的计算流程，粒度即便比网络层更小，也要等整个网络层计算完成，才能进行下一步。
//所以更小的粒度内存在宏观上的占用和 以网络层(算子)为粒度的占用是相同的。
/************************OpenNNA支持的算子列表****************************/
struct operator operators[]={
        //示例算子框架
        {"Example",OpenNNA_Operator_Example},
        //卷积类
        {"Conv2d",NULL},
        {"Depthwise Conv2d",NULL},
        //Padding类
        {"Padding",NULL},
        //Pool类
        {"Maxpool",NULL},
        {"Avgpool",NULL},
        //全连接类
        {"Dense",NULL},
        //激活函数类
        {"ReLU",NULL},
        {"ReLU6",NULL},
        {"LeakyRelu",NULL},
        {"tanh",NULL},
        {"Softmax",NULL},
};

/* Function: OpenNNA_Printf OpenNNA打印信息
 * strings: OpenNNA输出的信息
 */
static void OpenNNA_Logo(void)
{
    printf(
            " #######  ########  ######## ##    ## ##    ## ##    ##    ###\n"
            "##     ## ##     ## ##       ###   ## ###   ## ###   ##   ## ##\n"
            "##     ## ##     ## ##       ####  ## ####  ## ####  ##  ##   ##\n"
            "##     ## ########  ######   ## ## ## ## ## ## ## ## ## ##     ##\n"
            "##     ## ##        ##       ##  #### ##  #### ##  #### #########\n"
            "##     ## ##        ##       ##   ### ##   ### ##   ### ##     ##\n"
            "#######   ##        ######## ##    ## ##    ## ##    ## ##     ##\n");
}
/* Function: OpenNNA_Printf OpenNNA打印信息
 * strings: OpenNNA输出的信息
 * PS：影响库运行的关键信息会通过这个函数往外打印，其他不重要的信息直接采用printf打印
 */
static void OpenNNA_Printf(char * strings)
{
    char mesg[100] = {"OpenNNA: "};
    strcat(mesg, strings);
    printf("%s", mesg);
}
/* Function: OpenNNA_Malloc
 * size: 要申请的内存长度
 * return: 内存地址
 */
static struct layer * OpenNNA_Malloc(unsigned long size)
{
    OpenNNA_Heap_Sum +=size;
    return (struct layer *)malloc(size);
}

/* Function: OpenNNA_Free
 * size: 要释放的内存首地址address
 */
void OpenNNA_Free(void * address)
{
    free(address);
}

/* Function :OpenNNA_CreateNetwork :创建一个神经网络对象
 * return: 神经网络对象
*/
struct layer * OpenNNA_CreateNetwork(void)
{
    struct layer * Network = NULL;
    Network = OpenNNA_Malloc(sizeof(layers));//为神经网络对象申请堆内存
    Network->layer_next = NULL;
    Network->layer_prev = NULL;
    Network->Layer_index = 0;
    Network->Layer_Name = LIB_NAME;
    Network->Layer_Name_Alias = Author;
    Network->Layer_Para_Base = NULL;
    Network->Layer_Para_Extra = NULL;
    Network->Input_Feature_Map=NULL;
    Network->Output_Feature_Map=NULL;
    OpenNNA_Logo();
    return Network;
}
/* Function :OpenNNA_Add_Layer :在网络尾部添加一个网络层
 * struct layer * Network: 网络对象
 * char *Layer_Name: 网络层名(决定算子/激活函数类型)
 * char *Layer_Name_Alias: 网络层别名(用于区分）｜用户自定义
 * const void *Layer_Para_Base: 基本层参数 ｜ 用于控制网络计算行为
 * const void *Layer_Para_Extra: 额外层参数 ｜ 用于控制网络计算行为，例如卷积算子，这里面就可以装卷积核相关参数
 * const void *Weights: 权重地址
 * const void *Bias: 偏置地址
 * return 0:成功添加 其他值:见printf打印信息
*/
int OpenNNA_Add_Layer(struct layer * Network, \
                            char *Layer_Name, \
                            char *Layer_Name_Alias, \
                            const void *Layer_Para_Base, \
                            const void *Layer_Para_Extra, \
                            const void *Weights, \
                            const void *Bias \
                            )
{
    unsigned int layer_index = 0;
    struct layer * layer_prev = NULL;
    if(NULL != Network) {
        while(NULL != Network->layer_next)
        {
            Network = Network->layer_next;
            layer_index = Network->Layer_index;
        }
        Network->layer_next = OpenNNA_Malloc(sizeof(layers));//新建一个Layer
        layer_prev = Network;
        Network = Network->layer_next;
        Network->layer_next = NULL;
        Network->layer_prev = layer_prev;
        Network->Layer_index = layer_index + 1;
        Network->Layer_Name = Layer_Name;
        Network->Layer_Name_Alias = Layer_Name_Alias;
        Network->Layer_Para_Base = Layer_Para_Base;
        Network->Layer_Para_Extra = Layer_Para_Extra;
        Network->pfunc_Operator = NULL;
        Network->Input_Feature_Map = NULL;
        Network->Output_Feature_Map = NULL;
        //在算子支持列表中寻找算子
        for (int i = 0; i < sizeof(operators); ++i) {
            if (!strcmp(Layer_Name, operators[i].Operator_Name))//0找到
            {
                Network->pfunc_Operator = operators[i].pfunc_Operator;//算子函数指针填入
                break;
            }
        }
        if(NULL == Network->pfunc_Operator && 0 != Network->Layer_index)//未找到算子报错，index=0时忽略
        {
            char mesg[100] = {0};
            sprintf(mesg,"Layer %d Operator:%s NOT FOUND IN LIB!!!\n",Network->Layer_index,Layer_Name);
            OpenNNA_Printf(mesg);
            return -1;
        }
        Network->Weights = Weights;
        Network->Bias =Bias;
    }
    return 0;
}
/* Function :OpenNNA_GetFmapHeap :获取网络的特征图堆内存大小
 * struct layer * Network: 网络对象
 * int *Input_Fmap_HeapSize: 输入特征图堆内存大小
 * int *Output_Fmap_HeapSize: 输出特征图堆内存大小
*/
void OpenNNA_GetFmapHeap(struct layer * Network,int *Input_Fmap_HeapSize,int *Output_Fmap_HeapSize)
{
    while(NULL != Network->layer_next)
    {
        if(Network->Layer_index!=0)
        {
            //计算输入特征图的最大堆内存
            *Input_Fmap_HeapSize = *Input_Fmap_HeapSize<\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
            ?\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
            :\
            *Input_Fmap_HeapSize;
            //计算输出特征图的最大堆内存
            *Output_Fmap_HeapSize = *Output_Fmap_HeapSize<\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
            ?\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
            :\
            *Output_Fmap_HeapSize;
        }
        Network = Network->layer_next;
    }
    //计算输入特征图的最大堆内存
    *Input_Fmap_HeapSize = *Input_Fmap_HeapSize<\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
            ?\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
            :\
            *Input_Fmap_HeapSize;
    //计算输出特征图的最大堆内存
    *Output_Fmap_HeapSize = *Output_Fmap_HeapSize<\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
            ?\
            sizeof(data_t)*((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel\
            *\
            ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
            :\
            *Output_Fmap_HeapSize;
}
/* Function :OpenNNA_Init :初始化神经网络
 * struct layer * Network: 网络对象
 * 这个函数主要做以下几件事情:
 * 1.以网络为粒度，为每一层分配输入/输出堆内存
 * 2.将最后一层和第0层(Host节点)连接，构成循环链表。方便推理函数遍历干活
*/
void OpenNNA_Init(struct layer * Network)
{
    struct layer * Host = Network;
    int Input_Fmap_HeapSize = 0;//获取最大的输入特征图堆内存
    int Output_Fmap_HeapSize = 0;//获取最大的输出特征图堆内存
    unsigned int fmap_heap_flip = 1;//翻转堆内存(第一层的输出地址是第二层的输入地址，第二层的输出地址，是第一层的输入地址。
    char mesg[100] = {0};
    //获取输入/输出特征图堆内存
    OpenNNA_GetFmapHeap(Network,&Input_Fmap_HeapSize,&Output_Fmap_HeapSize);
    sprintf(mesg,"Max Input Fmap Heap = %d bytes, Max Output Fmap Heap = %d bytes\n",Input_Fmap_HeapSize,Output_Fmap_HeapSize);
    OpenNNA_Printf(mesg);
    //最大堆内存，由于堆内存翻转设计，也就是OpenNNA将会以最大特征图占用为标准，申请两块对称的堆内存空间
    Max_Fmap_Heap=(Input_Fmap_HeapSize > Output_Fmap_HeapSize ? Input_Fmap_HeapSize : Output_Fmap_HeapSize);
    Input_Fmap_Heap = OpenNNA_Malloc(Max_Fmap_Heap);//为输入特征图申请堆内存空间
    Output_Fmap_Heap = OpenNNA_Malloc(Max_Fmap_Heap);//为输出特征图申请堆内存空间
    //对称堆内存分配到每一个层
    while(NULL != Network->layer_next)
    {
        if((fmap_heap_flip==1)&&(0!=Network->Layer_index)) {
            Network->Input_Feature_Map = Input_Fmap_Heap;
            Network->Output_Feature_Map = Output_Fmap_Heap;
            fmap_heap_flip=0;
        }
        else if((fmap_heap_flip==0)&&(0!=Network->Layer_index)){
            Network->Input_Feature_Map = Output_Fmap_Heap;
            Network->Output_Feature_Map = Input_Fmap_Heap;
            fmap_heap_flip=1;
        }
        Network = Network->layer_next;
    }
    if((fmap_heap_flip==1)&&(0!=Network->Layer_index)) {
        Network->Input_Feature_Map = Input_Fmap_Heap;
        Network->Output_Feature_Map = Output_Fmap_Heap;
        fmap_heap_flip=0;
    }
    else if((fmap_heap_flip==0)&&(0!=Network->Layer_index)){
        Network->Input_Feature_Map = Output_Fmap_Heap;
        Network->Output_Feature_Map = Input_Fmap_Heap;
        fmap_heap_flip=1;
    }
    //将最后一层和第0层(Host节点)连接，构成循环链表。方便推理函数遍历干活
    Network->layer_next = Host;
    OpenNNA_Printf("Init OK!\n");
}

/* Function :OpenNNA_Print_Network :打印网络信息
 * struct layer * Network: 网络对象
*/
void OpenNNA_Print_Network(struct layer * Network)
{
    printf(
            "\n\n"
            "----------------------------------------------------------------------\n"
            "%s(%s)                                                                \n", Network->Layer_Name, Network->Layer_Name_Alias, Network->Layer_index
    );
    printf(
            "----------------------------------------------------------------------\n"
            "Layer(type)    Input Shape    Output Shape    Kernel    Param    Index\n"
            "======================================================================\n"
    );
    while(NULL != Network->layer_next)
    {
        Network = Network->layer_next;
        if(0 !=Network->Layer_index && NULL != Network->Layer_Para_Base)
        printf(
                "----------------------------------------------------------------------\n"
                "%s(%s)    (%d,%d,%d)    (%d,%d,%d)            NULL      NULL     %d   \n",
                Network->Layer_Name_Alias, Network->Layer_Name,\
                ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel,\
                ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row,\
                ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col,\
                ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel,\
                ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row,\
                ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col,\
                Network->Layer_index
        );
        if(0 == Network->Layer_index)break;
    }
    printf(
            "======================================================================\n"
            "Total Params:\n"
            "Flash:\n"
            "Heap:%d bytes\n"
            "\n\n",OpenNNA_Heap_Sum
    );
}

/* Function :OpenNNA_Init :神经网络推理
 * struct layer * Network: 网络对象
*/
void OpenNNA_Predict(struct layer * Host_Layer,const void *Network_Input, void *Network_Output)
{

}

int main() {
    /*****************第1步:创建神经网络对象**********************/
    struct layer * Network = OpenNNA_CreateNetwork();
    /*****************第2步:配置网络层参数**********************/
    Layer_Para_Base *Layer_Para_Base1 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Example *Layer_Para_Example1 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base1->Input_Fmap_Channel=3;
    Layer_Para_Base1->Input_Fmap_Row=320;
    Layer_Para_Base1->Input_Fmap_Col=320;
    Layer_Para_Base1->Output_Fmap_Channel=32;
    Layer_Para_Base1->Output_Fmap_Row=250;
    Layer_Para_Base1->Output_Fmap_Col=250;

    Layer_Para_Base *Layer_Para_Base2 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Example *Layer_Para_Example2 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base2->Input_Fmap_Channel=64;
    Layer_Para_Base2->Input_Fmap_Row=100;
    Layer_Para_Base2->Input_Fmap_Col=100;
    Layer_Para_Base2->Output_Fmap_Channel=128;
    Layer_Para_Base2->Output_Fmap_Row=30;
    Layer_Para_Base2->Output_Fmap_Col=30;

    Layer_Para_Base *Layer_Para_Base3 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Example *Layer_Para_Example3 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base3->Input_Fmap_Channel=1;
    Layer_Para_Base3->Input_Fmap_Row=32;
    Layer_Para_Base3->Input_Fmap_Col=32;
    Layer_Para_Base3->Output_Fmap_Channel=6;
    Layer_Para_Base3->Output_Fmap_Row=6;
    Layer_Para_Base3->Output_Fmap_Col=6;
    /*****************第3步:添加网络层**********************/
    OpenNNA_Add_Layer(Network, "Example", "xdd1", Layer_Para_Base1,Layer_Para_Example1, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Example", "xdd2", Layer_Para_Base2, Layer_Para_Example2,NULL, NULL);
    OpenNNA_Add_Layer(Network, "Example", "xdd3", Layer_Para_Base3, Layer_Para_Example3,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "ReLU", "xdd4", NULL, NULL,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "Dense", "xdd5", NULL, NULL,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "Softmax", "xdd6", NULL, NULL,NULL, NULL);
    /*****************第4步:初始化神经网络**********************/
    OpenNNA_Init(Network);
    /*****************第5步:打印神经网络信息**********************/
    OpenNNA_Print_Network(Network);
    /*****************第6步:神经网络推理**********************/
    OpenNNA_Predict(Network, NULL, NULL);
    /*****************第7步:根据推理结果进行动作**********************/

    return 0;
}
