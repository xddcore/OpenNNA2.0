//
// Created by 董程森 on 2022/7/13.
//
#include "opennna_operator_softmax.h"
#include "math.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_Softmax(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Output_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Channel;
    reg_t Output_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Row;
    reg_t Output_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Col;
    //Softmax独有
    data_t exp_sum = 0;//exp求sum
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    //得到exp 和exp sum
    for (int i = 0; i < Output_Fmap_Channel; i++)
    {
        for (int j = 0; j < Output_Fmap_Row; j++)
        {
            for (int k = 0; k < Output_Fmap_Col; k++)
            {
                ((data_t *)Layers->Output_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] = \
                exp(((data_t *)Layers->Input_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k]);
                exp_sum += exp(((data_t *)Layers->Input_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k]);
            }
        }
    }
    //得到softmax的概率 = 每个exp /sum
    for (int i = 0; i < Output_Fmap_Channel; i++)
    {
        for (int j = 0; j < Output_Fmap_Row; j++)
        {
            for (int k = 0; k < Output_Fmap_Col; k++)
            {
                ((data_t *)Layers->Output_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] = \
                ((data_t *)Layers->Output_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] / exp_sum;
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}