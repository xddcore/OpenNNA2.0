//
// Created by 董程森 on 2022/7/26.
//
#include "opennna_operator_conv2d.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_Conv2d(struct layer *Layers)
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

#if(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
    float Sw = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Sw;
    float Sb = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Sb;
    float Si = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Si;
    float So = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->So;

    int Zw = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Zw;
    int Zb = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Zb;
    int Zi = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Zi;
    int Zo = ((Layer_Para_Conv2d *)Layers->Layer_Para_Extra)->Zo;

    int Accumulator_INT32=0;
#elif(HARDWARE_ACCELERATION==2)//ARM CMSIS-DSP
    Fmap_t multOutput = 0;  /* Intermediate output */
#endif
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    //以下这个卷积实现思路以输出特征图为导向，当输入特征图为图像数据时，乘加次数最优
    for (int i = 0; i < filters; ++i) {//filters must = Output_Fmap_Channel
        for (int j = 0; j < Output_Fmap_Row; ++j) {
            for (int k = 0; k < Output_Fmap_Col; ++k) {
                //顺道填入偏置
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速,纯c推理(Float32)
                ((Fmap_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i]\
                =\
                ((Bias_t *)Layers->Bias)[i];
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
                Accumulator_INT32 = ((Bias_t *)Layers->Bias)[i];
#endif
                //一个卷积核去卷一下输入特征图
                for (int l = 0; l < kernel_channel; ++l) {
                    for (int m = 0; m < kernel_row; ++m) {
                        for (int n = 0; n < kernel_col; ++n) {
                          //输出特征图=输入特征图*卷积核权重
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速,纯c推理(Float32)
                            ((Fmap_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i]\
                            +=\
                            ((Fmap_t *)Layers->Input_Feature_Map)[(n+k*strides_col)+(m+j*strides_row)*Input_Fmap_Col+l*Input_Fmap_Col*Input_Fmap_Row]\
                            *\
                            ((Weights_t *)Layers->Weights)[n+m*kernel_col+l*kernel_col*kernel_row+i*kernel_col*kernel_row*kernel_channel];
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
                            Accumulator_INT32 += (((short int)((Fmap_t *)Layers->Input_Feature_Map)[(n+k*strides_col)+(m+j*strides_row)*Input_Fmap_Col+l*Input_Fmap_Col*Input_Fmap_Row])-Zi) * ((short int)((Weights_t *)Layers->Weights)[n+m*kernel_col+l*kernel_col*kernel_row+i*kernel_col*kernel_row*kernel_channel]-Zw);
#elif(HARDWARE_ACCELERATION==2)
                            //*
                            arm_mult_f32(&((Fmap_t *)Layers->Input_Feature_Map)[(n+k*strides_col)+(m+j*strides_row)*Input_Fmap_Col+l*Input_Fmap_Col*Input_Fmap_Row], \
                            &((Weights_t *)Layers->Weights)[n+m*kernel_col+l*kernel_col*kernel_row+i*kernel_col*kernel_row*kernel_channel], \
                            &multOutput,\
                            1);
                            //+
                            arm_add_f32(&((Fmap_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i],\
                            &multOutput,\
                            &((Fmap_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i], \
                            1);
                            #endif
                        }
                    }
                }
#if(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
                Accumulator_INT32=(int)((Accumulator_INT32*(Si*Sw/So))+Zo);//得到Qo(输出特征图量化值)
                //while(1);
                //Clip操作，防止溢出
                if(Accumulator_INT32>127)
                    Accumulator_INT32=127;
                else if (Accumulator_INT32<-128)
                    Accumulator_INT32=-128;
                ((Fmap_t *)Layers->Output_Feature_Map)[k+Output_Fmap_Col*j+Output_Fmap_Col*Output_Fmap_Row*i]=Accumulator_INT32;
#endif
            }
        }
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}