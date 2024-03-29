//
// Created by 董程森 on 2022/6/18.
//

#ifndef CORE_OPENNNA_CORE_H
#define CORE_OPENNNA_CORE_H

/************************OpenNNA配置项****************************/
//1. 特征图静态分配 / 特征图动态分配(默认)
// 单位时刻的特征图堆内存占用: 传统的静态堆内存管理方式 > OpenNNA提供的交叉式静态堆内存管理方式 > 动态堆内存管理
/* 静态特征图堆内存的分配策略(Dynamic_Fmap_heap==1):在OpenNNA_Init函数中统计最大的特征图输入堆内存和最大的特征图输出堆内存
 * 然后取其中的最大值为指标创建两块对称的堆内存。将它们依次交叉连接。
 * (网络第二层的输入特征图地址=第一层的输出特征图地址，网络第二层的输出地址=第一层的输入地址(第一层输入地址在第二层计算时已失去存在的意义)
 * 这样的静态堆内存管理方式通常情况下比传统的静态堆内存管理方式(即为每一层单独创建堆内存)将会节省很多的推内存空间。
 */
/* 动态堆内存的分配策略(Dynamic_Fmap_heap==0):在OpenNNA_Init函数中为第一层的输入特征图和输出特征图分配堆内存(为什么需要先分配第一层的堆内存，因为懒得重新写一套free Network逻辑了，
 * 所以默认无论动态还是静态特征图管理，第一层的堆内存都被分配了。
 * 在OpenNNA_Predict推理函数中进行每一层算子的计算时进行动态的堆内存分配
 */
#define Dynamic_Fmap_heap 0

//2.CHW(默认,CHW==1) / HWC模式(CHW == 0)
#define CHW 1

//3.DEBUG模式 (当DEBUG=1时，OpenNNA会打印所有输出信息，方便调试;反之，则不进行输出，同时屏蔽printf相关的所有代码(正式部署为了提高初始化速度，建议将DEBUG设置为0)
//如果不想移植printf函数，则直接DEBUG=0
#define DEBUG 0

//4......

/************************OpenNNA算子引入****************************/
//算子支持CHW/HWC这两种内存操作方式
#include "opennna_operator_example.h"
#include "opennna_operator_dense.h"
#include "opennna_operator_relu.h"
#include "opennna_operator_relu6.h"
#include "opennna_operator_softmax.h"
#include "opennna_operator_conv2d.h"
#include "opennna_operator_dwconv2d.h"
#include "opennna_operator_padding.h"
#include "opennna_operator_maxpool.h"
#include "opennna_operator_avgpool.h"
#include "opennna_operator_leakyrelu.h"
#include "opennna_operator_tanh.h"
/************************OpenNNA库的相关类型&函数声明****************************/
#define LIB_NAME "OpenNNA2.0-Tinier, Faster, Easier To Use"
#define Author "xddcore 1034029664@qq.com"

typedef float data_t;//特征图，权重，偏置等数据的类型

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
void * OpenNNA_Malloc(unsigned long size);
void OpenNNA_Free(void * address);
#if(DEBUG==1)
void OpenNNA_Printf(char * strings);
#endif
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
#if(DEBUG==1)
void OpenNNA_Print_Network(struct layer * Network);
#endif
void OpenNNA_Predict(struct layer * Network, const void *Network_Input, void *Network_Output);
void OpenNNA_Free_Network(struct layer **pNetwork);

#endif //CORE_OPENNNA_CORE_H
