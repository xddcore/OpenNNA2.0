//
// Created by 董程森 on 2022/7/4.
//
#include "opennna_operator_example.h"
#include "stdio.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_Example(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Input_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Channel;
    reg_t Input_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Row;
    reg_t Input_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Col;
    reg_t Output_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Channel;
    reg_t Output_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Row;
    reg_t Output_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Col;
    //printf("Example算子已被调用\n");
    //下方示例会实现 输出特征图 = 输入特征图 * Weights + Bias
    for (int i = 0; i < Output_Fmap_Channel; ++i) {
        for (int j = 0; j < Output_Fmap_Row; ++j) {
            for (int k = 0; k < Output_Fmap_Col; ++k) {
                ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i]\
                =\
                ((data_t *)Layers->Input_Feature_Map)[k+Input_Fmap_Col*j+Input_Fmap_Col*Input_Fmap_Row*i]\
                *((data_t *)Layers->Weights)[k+Input_Fmap_Col*j+Input_Fmap_Col*Input_Fmap_Row*i]\
                +((data_t *)Layers->Bias)[k+Input_Fmap_Col*j+Input_Fmap_Col*Input_Fmap_Row*i];
            }
        }

    }
}