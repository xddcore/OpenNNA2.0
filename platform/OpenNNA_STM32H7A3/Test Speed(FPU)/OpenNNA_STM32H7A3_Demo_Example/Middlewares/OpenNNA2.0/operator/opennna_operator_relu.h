//
// Created by 董程森 on 2022/7/13.
//

#ifndef CORE_OPENNNA_OPERATOR_RELU_H
#define CORE_OPENNNA_OPERATOR_RELU_H

#include "opennna_core.h"



//层参数
struct Layer_Para_ReLU{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
};
typedef struct Layer_Para_ReLU Layer_Para_ReLU;

//算子
void OpenNNA_Operator_ReLU(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_RELU_H
