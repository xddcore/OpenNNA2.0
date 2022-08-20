//
// Created by 董程森 on 2022/7/13.
//
#include "opennna_operator_dense.h"
#include "stdio.h"
//这里提供一个算子,命名规则:OpenNNA_Operator_算子名
void OpenNNA_Operator_Dense(struct layer *Layers)
{
    //通过Layer对象便可访问当前层的所有计算有关的信息
    reg_t Input_Fmap_Channel = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Channel;
    reg_t Input_Fmap_Row = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Row;
    reg_t Input_Fmap_Col = ((Layer_Para_Base *)Layers->Layer_Para_Base)->Input_Fmap_Col;
    //dense算子独有
    reg_t units = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->units;//神经元数量

#if(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Float32)
    float Sw = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Sw;
    float Sb = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Sb;
    float Si = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Si;
    float So = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->So;

    int Zw = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Zw;
    int Zb = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Zb;
    int Zi = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Zi;
    int Zo = ((Layer_Para_Dense *)Layers->Layer_Para_Extra)->Zo;

    int Accumulator_INT32=0;
#elif(HARDWARE_ACCELERATION==2)//不使用硬件加速,纯c推理(Int8)
    data_t multOutput = 0;  /* Intermediate output */
#endif
#if (CHW==1)
    //在此实现CHW的内存访问逻辑
    for (reg_t i = 0; i < units; ++i)//依次计算每个神经元
    {
        /*bias*/
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速,纯c推理(Float32)
        ((Fmap_t *)Layers->Output_Feature_Map)[i] = ((Bias_t *)Layers->Bias)[i];
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
        Accumulator_INT32 = (((Bias_t *)Layers->Bias)[i]);
#endif
        for (reg_t j= 0; j < (Input_Fmap_Channel*Input_Fmap_Row*Input_Fmap_Col); ++j)
        {
            /*weights*/
#if(HARDWARE_ACCELERATION==0)//不使用硬件加速,纯c推理(Float32)
            ((Fmap_t *)Layers->Output_Feature_Map)[i] += ((Fmap_t *)Layers->Input_Feature_Map)[j] * ((Weights_t *)Layers->Weights)[i*(Input_Fmap_Channel*Input_Fmap_Row*Input_Fmap_Col)+j];
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
            Accumulator_INT32 += (((short int)((Fmap_t *)Layers->Input_Feature_Map)[j])-Zi) * ((short int)((Weights_t *)Layers->Weights)[i*(Input_Fmap_Channel*Input_Fmap_Row*Input_Fmap_Col)+j]);
#elif(HARDWARE_ACCELERATION==2)
            //*
            arm_mult_f32(&((Fmap_t *)Layers->Input_Feature_Map)[j], \
            &((Weights_t *)Layers->Weights)[i*(Input_Fmap_Channel*Input_Fmap_Row*Input_Fmap_Col)+j], \
            &multOutput,\
            1);
            //+
            arm_add_f32(&((Fmap_t *)Layers->Output_Feature_Map)[i],\
            &multOutput,\
            &((Fmap_t *)Layers->Output_Feature_Map)[i], \
            1);
#endif
        }
#if(HARDWARE_ACCELERATION==1)//不使用硬件加速,纯c推理(Int8)
        Accumulator_INT32=(int)((Accumulator_INT32*(Si*Sw/So))+Zo);//得到Qo(输出特征图量化值)
        //Clip操作，防止溢出
        if(Accumulator_INT32>127)
            Accumulator_INT32=127;
        else if (Accumulator_INT32<-128)
            Accumulator_INT32=-128;
        ((Fmap_t *)Layers->Output_Feature_Map)[i]=Accumulator_INT32;
#endif
    }
#elif (CHW==0)//HWC模式
    //在此实现HWC的内存访问逻辑
#endif
}