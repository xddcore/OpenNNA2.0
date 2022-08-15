//
// Created by 董程森 on 2022/7/28.
//

#ifndef CORE_OPENNNA_OPERATOR_LEAKYRELU_H
#define CORE_OPENNNA_OPERATOR_LEAKYRELU_H

#include "opennna_core.h"



//层参数
struct Layer_Para_LeakyReLU{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
};
typedef struct Layer_Para_LeakyReLU Layer_Para_LeakyReLU;

//算子
void OpenNNA_Operator_LeakyReLU(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_LEAKYRELU_H
