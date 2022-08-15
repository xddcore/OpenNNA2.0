//
// Created by 董程森 on 2022/7/13.
//

#ifndef CORE_OPENNNA_OPERATOR_SOFTMAX_H
#define CORE_OPENNNA_OPERATOR_SOFTMAX_H

#include "opennna_core.h"



//层参数
struct Layer_Para_Softmax{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
};
typedef struct Layer_Para_Softmax Layer_Para_Softmax;

//算子
void OpenNNA_Operator_Softmax(struct layer *Layers);


#endif //CORE_OPENNNA_OPERATOR_SOFTMAX_H
