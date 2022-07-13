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
    int units;//神经元数量
};
typedef struct Layer_Para_Dense Layer_Para_Dense;

//算子
void OpenNNA_Operator_Dense(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_DENSE_H
