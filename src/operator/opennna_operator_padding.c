//
// Created by 董程森 on 2022/7/26.
//
#include "opennna_operator_padding.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_Padding(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Input_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Channel;
    reg_t Input_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Row;
    reg_t Input_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Col;
    reg_t Output_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Channel;
    reg_t Output_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Row;
    reg_t Output_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Col;

    //Padding特有参数
    reg_t Padding = ((Layer_Para_Padding *)Layers->Layer_Para_Extra)->padding;//填充几圈0
#if(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
    reg_t Padding_Value = ((Layer_Para_Padding *)Layers->Layer_Para_Extra)->padding_value;//要填充的数
#endif
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    for (int i = 0; i < Output_Fmap_Channel; i++)//Output_Fmap_Channel
    {
        for (int j = 0; j < Output_Fmap_Row; j++)//Output_Fmap_Row 行
        {
            for (int k = 0; k < Output_Fmap_Col; k++)//Output_Fmap_Col 列
            {
                /*j遍历行,顶部和底部填充*/
                if ( j < Padding)//顶部padding
                {
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速，纯c推理(Float32)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = 0;
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = Padding_Value;
#endif
                }
                else if (j >= (Padding + Input_Fmap_Row))//底部padding
                {
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速，纯c推理(Float32)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = 0;
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = Padding_Value;
#endif
                }
                /*k遍历列,左边和右边填充*/
                if (k < Padding)//左边padding
                {
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速，纯c推理(Float32)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = 0;
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = Padding_Value;
#endif
                }
                else if (k >= (Padding + Input_Fmap_Col))//右边padding
                {
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速，纯c推理(Float32)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = 0;
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)] = Padding_Value;
#endif
                }
                //输入fmap填充到中间
                if(j >= Padding && j < (Padding + Input_Fmap_Row) && k >= Padding && k < (Padding + Input_Fmap_Col))
                    ((Fmap_t *)Layers->Output_Feature_Map)[k+(Output_Fmap_Col*j)+(Output_Fmap_Col*Output_Fmap_Row*i)]  = ((Fmap_t *)Layers->Input_Feature_Map)[(i * Input_Fmap_Row * Input_Fmap_Col) + ((j-Padding) * Input_Fmap_Col) + (k-Padding)];
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}