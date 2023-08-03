//
// Created by 董程森 on 2022/7/13.
//

#ifndef CORE_OPENNNA_OPERATOR_DENSE_H
#define CORE_OPENNNA_OPERATOR_DENSE_H

#include "opennna_core.h"



//层参数
struct Layer_Para_Dense{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
    unsigned int units;//神经元数量
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
typedef struct Layer_Para_Dense Layer_Para_Dense;

//算子
void OpenNNA_Operator_Dense(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_DENSE_H
