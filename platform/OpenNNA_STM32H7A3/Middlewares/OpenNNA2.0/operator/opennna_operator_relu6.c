//
// Created by 董程森 on 2022/7/26.
//
#include "opennna_operator_relu6.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_ReLU6(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Output_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Channel;
    reg_t Output_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Row;
    reg_t Output_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Col;
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    for (int i = 0; i < Output_Fmap_Channel; i++)
    {
        for (int j = 0; j < Output_Fmap_Row; j++)
        {
            for (int k = 0; k < Output_Fmap_Col; k++)
            {
                ((Fmap_t *)Layers->Output_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] = \
                ((Fmap_t *)Layers->Input_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] > 6 ? \
                ((Fmap_t *)Layers->Input_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] \
                : \
                (Fmap_t)0;
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}