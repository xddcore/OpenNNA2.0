//
// Created by 董程森 on 2022/7/26.
//
//
// Created by 董程森 on 2022/7/26.
//
#include "opennna_operator_avgpool.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_AvgPool(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Input_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Channel;
    reg_t Input_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Row;
    reg_t Input_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Col;
    reg_t Output_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Channel;
    reg_t Output_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Row;
    reg_t Output_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Col;

    //池化算子特有参数
    reg_t kernel_col = ((Layer_Para_MaxPool *)Layers->Layer_Para_Extra)->kernel_col;
    reg_t kernel_row = ((Layer_Para_MaxPool *)Layers->Layer_Para_Extra)->kernel_row;

    reg_t strides_col = ((Layer_Para_MaxPool *)Layers->Layer_Para_Extra)->strides_col;
    reg_t strides_row = ((Layer_Para_MaxPool *)Layers->Layer_Para_Extra)->strides_row;
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    register reg_t max_value=0;//在MaxPool时存储最大值,在AveragePool存储均值
    for (int i = 0; i < Output_Fmap_Channel; ++i)//output_fmap_channel
    {
        for (int j = 0; j < Output_Fmap_Row; ++j)//Output_Fmap_Row = (((input_fmap_size - pool_Kernel_size) / pool_Kernel_stride) + 1)
        {
            for (int k = 0; k < Output_Fmap_Col; ++k)//(((input_fmap_size - pool_Kernel_size) / pool_Kernel_stride) + 1)
            {
                max_value = ((Fmap_t *)Layers->Input_Feature_Map)[(i * Input_Fmap_Col * Input_Fmap_Row) + ((j * strides_row) * Input_Fmap_Col) + (k * strides_col)];
                for (int l = 0; l < kernel_row; ++l)//pool_Kernel_size_row
                {
                    for (int m = 1; m < kernel_col; ++m)//pool_Kernel_size_col
                    {
                        max_value += ((Fmap_t *)Layers->Input_Feature_Map)[(i * Input_Fmap_Col * Input_Fmap_Row) + ((l + j * strides_row) * Input_Fmap_Col) + (m + k * strides_col)];
                    }
                }
                ((Fmap_t *)Layers->Output_Feature_Map)[(i*Output_Fmap_Col*Output_Fmap_Row) + (j*Output_Fmap_Col) + k] = (max_value/(kernel_col*kernel_row));//取平均
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}