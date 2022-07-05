//
// Created by 董程森 on 2022/7/4.
//

#ifndef CORE_OPENNNA_OPERATOR_EXAMPLE_H
#define CORE_OPENNNA_OPERATOR_EXAMPLE_H

#include "opennna_core.h"



//层参数
struct Layer_Para_Example{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
};
typedef struct Layer_Para_Example Layer_Para_Example;

//算子
void OpenNNA_Operator_Example(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_EXAMPLE_H
