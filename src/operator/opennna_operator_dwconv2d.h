//
// Created by 董程森 on 2022/7/28.
//

#ifndef CORE_OPENNNA_OPERATOR_DWCONV2D_H
#define CORE_OPENNNA_OPERATOR_DWCONV2D_H

#include "opennna_core.h"



//层参数
struct Layer_Para_DWConv2d{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
    //非对称卷积核在这里做支持
    unsigned int kernel_col;//卷积核col
    unsigned int kernel_row;//卷积核row
    unsigned int kernel_channel;//卷积核channel

    unsigned int filters; //卷积核数量(即卷积输出特征图通道)

    unsigned int strides_col;//步长列
    unsigned int strides_row;//步长行

#if(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
    float Sw;//权重的Scale
    float Sb;//偏置的Scale
    float Si;//输入特征图的Scale
    float So;//输出特征图的Scale
    int Zw;//权重的Zero Point
    int Zb;//偏置的Zero Point
    int Zi;//输入特征图的Zero Point
    int Zo;//输出特征图的Zero Point
#endif
};
typedef struct Layer_Para_DWConv2d Layer_Para_DWConv2d;

//算子
void OpenNNA_Operator_DWConv2d(struct layer *Layers);
#endif //CORE_OPENNNA_OPERATOR_DWCONV2D_H
