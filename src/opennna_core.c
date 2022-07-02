#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opennna_core.h"

/************************OpenNNA支持的算子列表****************************/
struct operator operators[]={
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
    return (struct layer *)malloc(size);
}

/* Function: OpenNNA_Free
 * size: 要申请的内存长度
 * return: 内存地址
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
    OpenNNA_Logo();
    return Network;
}
/* Function :OpenNNA_Add_Layer :在网络尾部添加一个网络层
 * struct layer * Network: 网络对象
 * char *Layer_Name: 网络层名(决定算子/激活函数类型)
 * char *Layer_Name_Alias: 网络层别名(用于区分）｜用户自定义
 * void *Layer_Para: 层参数 ｜ 用于控制网络计算行为
 * void *Input_Feature_Map: 输入特征图地址
 * void *Output_Feature_Map: 输出特征图地址
 * void *Weights: 权重地址
 * void *Bias: 偏置地址
 * return 0:成功添加 其他值:见printf打印信息
*/
int OpenNNA_Add_Layer(struct layer * Network, \
                            char *Layer_Name, \
                            char *Layer_Name_Alias, \
                            const void *Layer_Para, \
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
        Network->Layer_Para = Layer_Para;
        Network->pfunc_Operation = NULL;
        //Network->Input_Feature_Map = Input_Feature_Map;
        //Network->Output_Feature_Map = Output_Feature_Map;
        //在算子支持列表中寻找算子
        for (int i = 0; i < sizeof(operators); ++i) {
            if (!strcmp(Layer_Name, operators[i].Operator_Name))//0找到
            {
                Network->pfunc_Operation = operators[i].pfunc_Operation;//算子函数指针填入
                break;
            }
        }
        if(NULL == Network->pfunc_Operation && 0 != Network->Layer_index)//未找到算子报错，index=0时忽略
        {
            char * strings= OpenNNA_Malloc(100);//为这次打印申请一块堆内存
            sprintf(strings,"Operator:%s NOT FOUND IN LIB!!!\n",Layer_Name);
            OpenNNA_Printf(strings);
            OpenNNA_Free(strings);//打印结束，释放这块堆内存
            return -1;
        }
        Network->Weights = Weights;
        Network->Bias =Bias;
    }
    return 0;
}
/* Function :OpenNNA_Init :初始化神经网络
 * struct layer * Network: 网络对象
*/
void OpenNNA_Init(struct layer * Network)
{
    struct layer * Host = Network;
    while(NULL != Network->layer_next)
    {
        //printf("%s|%s-%d\n",Network->Layer_Name,Network->Layer_Name_Alias,Network->Layer_index);
        Network = Network->layer_next;
        //printf("%s|%s-%d\n",Network->Layer_Name,Network->Layer_Name_Alias,Network->Layer_index);
    }
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
        if(0 !=Network->Layer_index)
        printf(
                "----------------------------------------------------------------------\n"
                "%s(%s)         NULL           NULL            NULL      NULL     %d   \n", Network->Layer_Name_Alias, Network->Layer_Name, Network->Layer_index
        );
        if(0 == Network->Layer_index)break;
    }
    printf(
            "======================================================================\n"
            "Total Params:\n"
            "Flash:\n"
            "Heap:\n"
            "\n\n"
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
    /*****************第2步:添加网络层**********************/
    OpenNNA_Add_Layer(Network, "Conv2d", "xdd1", NULL, NULL, NULL);
    OpenNNA_Add_Layer(Network, "ReLU", "xdd2", NULL, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "xdd3", NULL, NULL, NULL);
    OpenNNA_Add_Layer(Network, "ReLU", "xdd4", NULL, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Dense", "xdd5", NULL, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Softmax", "xdd6", NULL, NULL, NULL);
    /*****************第3步:初始化神经网络**********************/
    OpenNNA_Init(Network);
    /*****************第4步:打印神经网络信息**********************/
    OpenNNA_Print_Network(Network);
    /*****************第5步:神经网络推理**********************/
    OpenNNA_Predict(Network, NULL, NULL);
    /*****************第6步:根据推理结果进行动作**********************/

    return 0;
}
