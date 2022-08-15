//
// Created by 董程森 on 2022/7/26.
//

#ifndef CORE_OPENNNA_OPERATOR_CONV2D_H
#define CORE_OPENNNA_OPERATOR_CONV2D_H

#include "opennna_core.h"



//层参数
struct Layer_Para_Conv2d{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
    //非对称卷积核在这里做支持
    unsigned int kernel_col;//卷积核col
    unsigned int kernel_row;//卷积核row
    unsigned int kernel_channel;//卷积核channel

    unsigned int filters; //卷积核数量(即卷积输出特征图通道)

    unsigned int strides_col;//步长列
    unsigned int strides_row;//步长行
};
typedef struct Layer_Para_Conv2d Layer_Para_Conv2d;

//算子
void OpenNNA_Operator_Conv2d(struct layer *Layers);
#endif //CORE_OPENNNA_OPERATOR_CONV2D_H
