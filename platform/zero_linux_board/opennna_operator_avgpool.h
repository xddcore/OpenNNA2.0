//
// Created by 董程森 on 2022/7/26.
//

#ifndef CORE_OPENNNA_OPERATOR_AVGPOOL_H
#define CORE_OPENNNA_OPERATOR_AVGPOOL_H

#include "opennna_core.h"



//层参数
struct Layer_Para_AvgPool{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
    unsigned int kernel_col;//池化核col
    unsigned int kernel_row;//池化核row

    unsigned int strides_col;//步长列
    unsigned int strides_row;//步长行
};
typedef struct Layer_Para_AvgPool Layer_Para_AvgPool;

//算子
void OpenNNA_Operator_AvgPool(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_AVGPOOL_H
