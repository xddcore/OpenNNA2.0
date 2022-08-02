//
// Created by 董程森 on 2022/7/28.
//
#include "opennna_operator_dwconv2d.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
// Note: 深度可分离卷积= 一个逐通道卷积(提取特征)+一个逐点卷积(融合，四舍五入就是普通卷积)构成，
// 本算子实现逐通道卷积，后面再接一层普通的conv2d卷积层就可以实现dwconv2d
void OpenNNA_Operator_DWConv2d(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Input_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Channel;
    reg_t Input_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Row;
    reg_t Input_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Col;
    reg_t Output_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Channel;
    reg_t Output_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Row;
    reg_t Output_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Output_Fmap_Col;
    //卷积运算相关的参数
    reg_t kernel_col = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->kernel_col;
    reg_t kernel_row = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->kernel_row;
    reg_t kernel_channel = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->kernel_channel;

    reg_t filters = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->filters;

    reg_t strides_col = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->strides_col;
    reg_t strides_row = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->strides_row;
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    //以下这个卷积实现思路以输出特征图为导向，当输入特征图为图像数据时，乘加次数最优
    for (int i = 0; i < filters; ++i) {//filters must = Output_Fmap_Channel
        for (int j = 0; j < Output_Fmap_Row; ++j) {
            for (int k = 0; k < Output_Fmap_Col; ++k) {
                //顺道填入偏置
                ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i]\
                =\
                ((data_t *)Layers->Bias)[i];
                //一个卷积核去卷一下输入特征图
                for (int l = 0; l < kernel_channel; ++l) {
                    for (int m = 0; m < kernel_row; ++m) {
                        for (int n = 0; n < kernel_col; ++n) {
                            //输出特征图=输入特征图*卷积核权重
                            ((data_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i]\
                            +=\
                            //dw的实现主要修改下面这一行代码中输入特征图的load逻辑(以kernel channel参数进行内存偏移访问 改为 以filter参数进行内存偏移访问)
                            // (l*Input_Fmap_Col*Input_Fmap_Row->i*Input_Fmap_Col*Input_Fmap_Row)
                            ((data_t *)Layers->Input_Feature_Map)[(n+k*strides_col)+(m+j*strides_row)*Input_Fmap_Col+i*Input_Fmap_Col*Input_Fmap_Row]\
                            *\
                            ((data_t *)Layers->Weights)[n+m*kernel_col+l*kernel_col*kernel_row+i*kernel_col*kernel_row*kernel_channel];
                        }
                    }
                }
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}