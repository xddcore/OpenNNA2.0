//
// Created by 董程森 on 2022/6/18.
//

#ifndef CORE_OPENNNA_CORE_H
#define CORE_OPENNNA_CORE_H

/************************OpenNNA算子引入****************************/
//CHW
#include "opennna_operator_example.h"

#define LIB_NAME "OpenNNA2.0-Tinier, Faster, Easier To Use"
#define Author "xddcore 1034029664@qq.com"

typedef int data_t;//特征图，权重，偏置等数据的类型

typedef int reg_t;//对每一个层的控制可以理解为对算子寄存器(参数)的控制

//网络层算子基本参数
struct Layer_Para_base{
    reg_t Input_Fmap_Channel; //输入特征图通道，也就是c
    reg_t Input_Fmap_Row; //输入特征图行，也就是h
    reg_t Input_Fmap_Col; //输入特征图列，也就是w
    reg_t Output_Fmap_Channel; //输出特征图通道，也就是c
    reg_t Output_Fmap_Row; //输出特征图行，也就是h
    reg_t Output_Fmap_Col; //输出特征图列，也就是w
};
typedef struct Layer_Para_base Layer_Para_Base;
//算子匹配
struct operator{
    char * Operator_Name;//算子名(和layer->Layer_Name进行匹配)
    void (*pfunc_Operator)(struct layer *Layer);//算子函数
};

//神经网络层对象
struct layer{
    struct layer *layer_prev;
    /*****************神经网络相关**********************/
    unsigned int Layer_Index;//层序号
    char *Layer_Name; //网络层名
    char *Layer_Name_Alias; //网络层别名
    void *Layer_Para_Base; //基本层参数地址
    void *Layer_Para_Extra; //额外层参数地址
    void *Input_Feature_Map; //输入特征图地址
    void *Output_Feature_Map; //输出特征图地址
    void *Weights; //权重地址
    void *Bias; //偏置地址
    //算子/激活函数
    void (*pfunc_Operator)(struct layer *Layer);
    /*****************神经网络相关**********************/
    struct layer *layer_next;
};

typedef struct layer layers;//神经网络层类型

//函数声明
struct layer * OpenNNA_CreateNetwork(void);
int OpenNNA_Add_Layer(struct layer * Network, \
                            char *Layer_Name, \
                            char *Layer_Name_Alias, \
                            const void *Layer_Para_Base, \
                            const void *Layer_Para_Extra, \
                            const void *Weights, \
                            const void *Bias \
                            );
void OpenNNA_Init(struct layer * Network);
void OpenNNA_Print_Network(struct layer * Network);
void OpenNNA_Predict(struct layer * Network, const void *Network_Input, void *Network_Output);

#endif //CORE_OPENNNA_CORE_H
