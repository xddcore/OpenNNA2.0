//
// Created by 董程森 on 2022/6/18.
//

#ifndef CORE_OPENNNA_CORE_H
#define CORE_OPENNNA_CORE_H

#define LIB_NAME "OpenNNA2.0-Tinier, Faster, Easier To Use"
#define Author "xddcore 1034029664@qq.com"

//算子基参数
//opennnacore提供一个算子基本的参数结构体
//不同的算子去包含这个算子基本的参数结构体
//一个算子基本的参数有:
//输入shape
//输出shape

//算子匹配
struct operator{
    char * Operator_Name;//算子名(和layer->Layer_Name进行匹配)
    void (*pfunc_Operation)(struct layer *Layer);//算子函数
};

//神经网络层对象
struct layer{
    struct layer *layer_prev;
    /*****************神经网络相关**********************/
    unsigned int Layer_index;//层序号
    char *Layer_Name; //网络层名
    char *Layer_Name_Alias; //网络层别名
    void *Layer_Para; //层参数地址
    void *Input_Feature_Map; //输入特征图地址
    void *Output_Feature_Map; //输出特征图地址
    void *Weights; //权重地址
    void *Bias; //偏置地址
    //算子/激活函数
    void (*pfunc_Operation)(struct layer *Layer);
    /*****************神经网络相关**********************/
    struct layer *layer_next;
};

typedef struct layer layers;//神经网络层类型

//函数声明
struct layer * OpenNNA_CreateNetwork(void);
int OpenNNA_Add_Layer(struct layer * Network, \
                            char *Layer_Name, \
                            char *Layer_Name_Alias, \
                            const void *Layer_Para, \
                            const void *Weights, \
                            const void *Bias \
                            );
void OpenNNA_Init(struct layer * Network);
void OpenNNA_Print_Network(struct layer * Network);
void OpenNNA_Predict(struct layer * Host_Layer,const void *Network_Input, void *Network_Output);

#endif //CORE_OPENNNA_CORE_H
