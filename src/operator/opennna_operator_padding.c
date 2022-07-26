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
    reg_t Padding_Top = ((Layer_Para_Padding *)Layers->Layer_Para_Extra)->padding_top;//顶部填充行
    reg_t Padding_Bottom = ((Layer_Para_Padding *)Layers->Layer_Para_Extra)->padding_bottom;//底部填充行
    reg_t Padding_Left = ((Layer_Para_Padding *)Layers->Layer_Para_Extra)->padding_left;//左边填充行
    reg_t Padding_Right = ((Layer_Para_Padding *)Layers->Layer_Para_Extra)->padding_right;//右边填充行
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    for (int i = 0; i < Output_Fmap_Channel; i++)//Output_Fmap_Channel
    {
        for (int j = 0; j < Output_Fmap_Row; j++)//Output_Fmap_Row 行
        {
            for (int k = 0; k < Output_Fmap_Col; k++)//Output_Fmap_Col 列
            {
                /*j遍历行,顶部和底部填充*/
                if ( j < Padding_Top)//顶部padding
                {
                    ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i] = 0;
                }
                else if ((j >= (Padding_Top + Input_Fmap_Row))&&(j <= (Padding_Top + Padding_Bottom + Input_Fmap_Row)))//底部padding
                {
                    ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i] = 0;
                }
                /*k遍历列,左边和右边填充*/
                if (k < Padding_Left)//左边padding
                {
                    ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i] = 0;
                }
                else if ((k >= (Padding_Left + Input_Fmap_Col))&&(k <= (Padding_Left + Padding_Right + Input_Fmap_Col)))//右边padding
                {
                    ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i] = 0;
                }
                //输入fmap填充到中间
                if(j >= Padding_Top && j < (Padding_Top + Input_Fmap_Row) && k >= Padding_Left && k < (Padding_Left + Input_Fmap_Col))
                    ((data_t *)Layers->Output_Feature_Map)[(i * Output_Fmap_Row * Output_Fmap_Col) + (j * Output_Fmap_Col) + k] = ((data_t *)Layers->Input_Feature_Map)[(i * Input_Fmap_Row * Input_Fmap_Col) + ((j-Padding_Top) * Input_Fmap_Col) + (k-Padding_Left)];
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}