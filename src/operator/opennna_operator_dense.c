//
// Created by 董程森 on 2022/7/13.
//
#include "opennna_operator_dense.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_Dense(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Input_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Channel;
    reg_t Input_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Row;
    reg_t Input_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Col;
    //dense算子独有
    reg_t units = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->units;//神经元数量
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    for (reg_t i = 0; i < units; ++i)//依次计算每个神经元
    {
        /*bias*/
        ((data_t *)Layers->Output_Feature_Map)[i] = ((data_t *)Layers->Bias)[i];
        for (reg_t j= 0; j < (Input_Fmap_Channel*Input_Fmap_Row*Input_Fmap_Col); ++j)
        {
            /*weights*/
            ((data_t *)Layers->Output_Feature_Map)[i] += ((data_t *)Layers->Input_Feature_Map)[i] * ((data_t *)Layers->Weights)[i*(Input_Fmap_Channel*Input_Fmap_Row*Input_Fmap_Col)+j];
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}