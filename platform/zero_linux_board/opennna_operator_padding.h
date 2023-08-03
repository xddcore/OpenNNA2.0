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
    unsigned int padding;//填充几圈0
#if(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
    int padding_value;//要填充的数
#endif
};
typedef struct Layer_Para_Padding Layer_Para_Padding;

//算子
void OpenNNA_Operator_Padding(struct layer *Layers);

#endif //CORE_OPENNNA_OPERATOR_PADDING_H
