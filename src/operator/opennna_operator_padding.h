//
// Created by 董程森 on 2022/7/26.
//

#ifndef CORE_OPENNNA_OPERATOR_PADDING_H
#define CORE_OPENNNA_OPERATOR_PADDING_H

#include "opennna_core.h"



//层参数
struct Layer_Para_Padding{
    //在这里可以添加其他的层属性(每个算子独有)
    //例如卷积核的大小，stride等
    unsigned int padding_top;//顶部填充几行0
    unsigned int padding_bottom;//底部填充几行0
    unsigned int padding_left;//左边填充几行0
    unsigned int padding_right;//右边填充几行0
};
typedef struct Layer_Para_Padding Layer_Para_Padding;

//算子
void OpenNNA_Operator_Padding(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_PADDING_H
