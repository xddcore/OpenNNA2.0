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
void OpenNNA_Printf(char * strings)
{
    char mesg[100] = {"OpenNNA: "};
    strcat(mesg, strings);
    printf("%s", mesg);
}
/* Function: OpenNNA_Malloc
 * size: 要申请的内存长度
 * return: 内存地址
 */
void * OpenNNA_Malloc(unsigned long size)
{
    OpenNNA_Heap_Sum +=size;
    return (void *)malloc(size);
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
    Network->Layer_Index = 0;
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
            layer_index = Network->Layer_Index;
        }
        Network->layer_next = OpenNNA_Malloc(sizeof(layers));//新建一个Layer
        layer_prev = Network;
        Network = Network->layer_next;
        Network->layer_next = NULL;
        Network->layer_prev = layer_prev;
        Network->Layer_Index = layer_index + 1;
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
        if(NULL == Network->pfunc_Operator && 0 != Network->Layer_Index)//未找到算子报错，index=0时忽略
        {
            char mesg[100] = {0};
            sprintf(mesg, "Layer %d Operator:%s NOT FOUND IN LIB!!!\n", Network->Layer_Index, Layer_Name);
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
        if(Network->Layer_Index != 0)
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
#if(Dynamic_Fmap_heap == 1)//动态特征图堆内存(管理粒度:层)
    struct layer * Host = Network;//第0层
    struct layer * Last_Layer = NULL;//最后一层
    Network = Network->layer_next;//跳转到第一层
    //提示动态堆内存分配已开启
    OpenNNA_Printf("Dynamic Fmap Heap Enable!\n");
    Network->Input_Feature_Map= OpenNNA_Malloc(sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
    );
    //分配输出特征图的堆内存
    Network->Output_Feature_Map= OpenNNA_Malloc(sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
    );
    while(NULL != Network->layer_next)//遍历到最后一层
    {
        Network = Network->layer_next;
    }
    //将最后一层和第0层(Host节点)连接，构成循环链表。方便推理函数遍历干活
    Network->layer_next = Host;
    //将第0层的prev和最后一层连接，构成双向循环链表
    Last_Layer = Network;
    Network = Network->layer_next;//跳转到第0层
    Network->layer_prev= Last_Layer;//第0层prev连接最后一层
    OpenNNA_Printf("Init OK!\n");
#elif(Dynamic_Fmap_heap == 0)//静态特征图堆内存(管理粒度:网络)
    struct layer * Host = Network;//第0层
    struct layer * Last_Layer = NULL;//最后一层
    int Input_Fmap_HeapSize = 0;//获取最大的输入特征图堆内存
    int Output_Fmap_HeapSize = 0;//获取最大的输出特征图堆内存
    unsigned int fmap_heap_flip = 1;//翻转堆内存(第一层的输出地址是第二层的输入地址，第二层的输出地址，是第一层的输入地址。
    char mesg[100] = {0};
    //获取输入/输出特征图堆内存
    OpenNNA_GetFmapHeap(Network,&Input_Fmap_HeapSize,&Output_Fmap_HeapSize);
    sprintf(mesg,"Static Fmap Heap Enable!\nMax Input Fmap Heap = %d bytes, Max Output Fmap Heap = %d bytes\n",Input_Fmap_HeapSize,Output_Fmap_HeapSize);
    OpenNNA_Printf(mesg);
    //最大堆内存，由于堆内存翻转设计，也就是OpenNNA将会以最大特征图占用为标准，申请两块对称的堆内存空间
    Max_Fmap_Heap=(Input_Fmap_HeapSize > Output_Fmap_HeapSize ? Input_Fmap_HeapSize : Output_Fmap_HeapSize);
    Input_Fmap_Heap = OpenNNA_Malloc(Max_Fmap_Heap);//为输入特征图申请堆内存空间
    Output_Fmap_Heap = OpenNNA_Malloc(Max_Fmap_Heap);//为输出特征图申请堆内存空间
    //对称堆内存分配到每一个层
    while(NULL != Network->layer_next)
    {
        if((fmap_heap_flip==1)&&(0!=Network->Layer_Index)) {
            Network->Input_Feature_Map = Input_Fmap_Heap;
            Network->Output_Feature_Map = Output_Fmap_Heap;
            fmap_heap_flip=0;
        }
        else if((fmap_heap_flip==0)&&(0!=Network->Layer_Index)){
            Network->Input_Feature_Map = Output_Fmap_Heap;
            Network->Output_Feature_Map = Input_Fmap_Heap;
            fmap_heap_flip=1;
        }
        Network = Network->layer_next;
    }
    if((fmap_heap_flip==1)&&(0!=Network->Layer_Index)) {
        Network->Input_Feature_Map = Input_Fmap_Heap;
        Network->Output_Feature_Map = Output_Fmap_Heap;
        fmap_heap_flip=0;
    }
    else if((fmap_heap_flip==0)&&(0!=Network->Layer_Index)){
        Network->Input_Feature_Map = Output_Fmap_Heap;
        Network->Output_Feature_Map = Input_Fmap_Heap;
        fmap_heap_flip=1;
    }
    //将最后一层和第0层(Host节点)连接，构成循环链表。方便推理函数遍历干活
    Network->layer_next = Host;
    //将第0层的prev和最后一层连接，构成双向循环链表
    Last_Layer = Network;
    Network = Network->layer_next;//跳转到第0层
    Network->layer_prev= Last_Layer;//第0层prev连接最后一层
    OpenNNA_Printf("Init OK!\n");
#endif
}

/* Function :OpenNNA_Print_Network :打印网络信息
 * struct layer * Network: 网络对象
*/
void OpenNNA_Print_Network(struct layer * Network)
{
    printf(
            "\n\n"
            "----------------------------------------------------------------------\n"
            "%s(%s)                                                                \n", Network->Layer_Name, Network->Layer_Name_Alias, Network->Layer_Index
    );
    printf(
            "----------------------------------------------------------------------\n"
            "Layer(type)    Input Shape    Output Shape    Kernel    Param    Index\n"
            "======================================================================\n"
    );
    while(NULL != Network->layer_next)
    {
        Network = Network->layer_next;
        if(0 !=Network->Layer_Index && NULL != Network->Layer_Para_Base)
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
                Network->Layer_Index
        );
        if(0 == Network->Layer_Index)break;
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
void OpenNNA_Predict(struct layer * Network, const void *Network_Input, void *Network_Output)
{
#if (Dynamic_Fmap_heap==1)
    //跳转到第一层
    Network = Network->layer_next;
    //将用户传入的神经网络输入copy到第一层的堆内存上
    memcpy(Network->Input_Feature_Map,Network_Input,\
    sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel\
    );
    //手动计算第一层结果
    Network->pfunc_Operator(Network);//将本层参数传入算子进行计算
    //第一层计算完成，跳转到第二层
    Network = Network->layer_next;
    //遍历每一层计算一次(从第二层开始)
    while(0!=Network->Layer_Index)
    {
        //Free上一层的输入
        OpenNNA_Free(Network->layer_prev->Input_Feature_Map);
        //将上一层的输出绑定到本层的输入
        Network->Input_Feature_Map=Network->layer_prev->Output_Feature_Map;
        //为本层输出特征图Malloc堆内存
        Network->Output_Feature_Map= OpenNNA_Malloc(sizeof(data_t)*\
        ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel*\
        ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row*\
        ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
        );
        Network->pfunc_Operator(Network);//将本层参数传入算子进行计算
        Network = Network->layer_next;//计算完成跳转到下一层
    }
    //跳回最后一层取结果
    Network = Network->layer_prev;
    //把最后一层的结果取出
    memcpy(Network_Output,Network->Output_Feature_Map,\
    sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel\
    );
    //把最后一层的输输出free
    OpenNNA_Free(Network->Output_Feature_Map);
    //跳转到第一层
    Network = Network->layer_next;
    Network = Network->layer_next;
    //为第一层输入输出特征图申请堆内存
    //分配输入特征图的堆内存
    Network->Input_Feature_Map= OpenNNA_Malloc(sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
    );
    //分配输出特征图的堆内存
    Network->Output_Feature_Map= OpenNNA_Malloc(sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
    );
#elif(Dynamic_Fmap_heap==0)
    //跳转到第一层
    Network = Network->layer_next;
    //将用户传入的神经网络输入copy到第一层的堆内存上
    memcpy(Network->Input_Feature_Map,Network_Input,\
    sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Col\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Row\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Input_Fmap_Channel\
    );
    //遍历每一层计算一次
    while(0!=Network->Layer_Index)
    {
        Network->pfunc_Operator(Network);//将本层参数传入算子进行计算
        Network = Network->layer_next;//计算完成跳转到下一层
    }
    //跳回最后一层取结果
    Network = Network->layer_prev;
    //把最后一层的结果取出
    memcpy(Network_Output,Network->Output_Feature_Map,\
    sizeof(data_t)*\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Col\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Row\
    *\
    ((Layer_Para_Base *)Network->Layer_Para_Base)->Output_Fmap_Channel\
    );
#endif
}
/* Function :OpenNNA_Free_Static_FmapHeap :释放输入输出特征图的堆内存
 * struct layer * Network: 网络对象
 * (无论是静态申请堆内存还是动态申请堆内存，
 * 第一层网络对象的属性里的Input_Feature_Map&Output_Feature_Map一定会被分配值)
*/
void OpenNNA_Free_FmapHeap(struct layer *Network)
{
    Network= Network->layer_next;
    if(0!=Network->Layer_Index) {
        OpenNNA_Free(Network->Input_Feature_Map);
        OpenNNA_Free(Network->Output_Feature_Map);
    }
    OpenNNA_Printf("Fmap Heap Free Success!\n");
}
/* Function :OpenNNA_Free_Network :释放网络对象的堆内存+释放输入输出特征图的堆内存(若有)
 * struct layer * Network: 网络对象
*/
void OpenNNA_Free_Network(struct layer *Network)
{
    //先释放静态申请的堆内存
    //(无论是静态申请堆内存还是动态申请堆内存，
    //第一层网络对象的属性里的Input_Feature_Map&Output_Feature_Map一定会被分配值)
    OpenNNA_Free_FmapHeap(Network);
    //跳转到第一层
    Network= Network->layer_next;
    while (0!=Network->Layer_Index) {
        if(1!=Network->Layer_Index)OpenNNA_Free(Network->layer_prev);//释放上一层，从1开始，0先留着(0作为遍历终止条件比较方便)
        Network->layer_prev=NULL;//为了保险把访问上一层对象的指针置NULL
        Network = Network->layer_next;//跳转到下一层
    }
    //最后释放第0层
    OpenNNA_Free(Network);
    OpenNNA_Printf("Network Free Success!\n");
}
