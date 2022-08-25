//
// Created by 董程森 on 2022/6/18.
//

#ifndef CORE_OPENNNA_CORE_H
#define CORE_OPENNNA_CORE_H

/************************OpenNNA配置项****************************/
//1. 特征图静态分配 / 特征图动态分配(默认)
/* 单位时刻的特征图堆内存占用: 传统的静态堆内存管理方式 > OpenNNA提供的交叉式静态堆内存管理方式 > 动态堆内存管理 */
/* 静态特征图堆内存的分配策略(DYNAMIC_FMAP_HEAP=1):在OpenNNA_Init函数中统计最大的特征图输入堆内存和最大的特征图输出堆内存
 * 然后取其中的最大值为指标创建两块对称的堆内存。将它们依次交叉连接。
 * (网络第二层的输入特征图地址=第一层的输出特征图地址，网络第二层的输出地址=第一层的输入地址(第一层输入地址在第二层计算时已失去存在的意义)
 * 这样的静态堆内存管理方式通常情况下比传统的静态堆内存管理方式(即为每一层单独创建堆内存)将会节省很多的推内存空间。
 */
/* 动态堆内存的分配策略(DYNAMIC_FMAP_HEAP=0):在OpenNNA_Init函数中为第一层的输入特征图和输出特征图分配堆内存(为什么需要先分配第一层的堆内存，因为懒得重新写一套free Network逻辑了，
 * 所以默认无论动态还是静态特征图管理，第一层的堆内存都被分配了。
 * 在OpenNNA_Predict推理函数中进行每一层算子的计算时进行动态的堆内存分配
 */
#define DYNAMIC_FMAP_HEAP 1

//2.权重排布方式
/*CHW(默认,CHW=1)
 * 通道，行，列
 */
/*HWC模式(CHW=0)
 * 行，列，通道
 */
#define CHW 1

//3.DEBUG模式
/*当DEBUG=1时，OpenNNA会打印所有输出信息，方便调试;
 * 反之，则不进行输出，同时屏蔽printf相关的所有代码(正式部署为了提高初始化速度，建议将DEBUG设置为0)
 * 如果不想移植printf函数，则直接DEBUG=0
 */
#define DEBUG 0

//4.堆内存管理方式
/* HEAP_MANAGER=0:使用C语言STDLIB中自带的Malloc()和Free()进行动态堆内存管理
 * HEAP_MANAGER=1:使用FreeRTOS的pvPortMalloc()和vPortFree()进行动态堆内存管理
 */
#define HEAP_MANAGER 1

//5.算子硬件加速
/* HARDWARE_ACCELERATION=0:不使用任何硬件加速手段，纯C推理，几乎可以运行在任何平台上(Float32推理)
 * HARDWARE_ACCELERATION=1:不使用任何硬件加速手段，纯C推理，几乎可以运行在任何平台上(Int8推理)
 * HARDWARE_ACCELERATION=2:ARM_CMSIS_DSP_FP32｜使用ARM的CMSIS-DSP库，并实现fp32精度权重的加速
 * HARDWARE_ACCELERATION=3:ARM_SIMD_INT8｜使用ARM的SIMD指令，并实现int8精度权重的加速(2路并行)
 */
#define HARDWARE_ACCELERATION 1

//6......

/************************OpenNNA算子引入****************************/
//算子支持CHW/HWC这两种内存操作方式
#include "opennna_operator_example.h"
#include "opennna_operator_dense.h"
#include "opennna_operator_relu.h"
#include "opennna_operator_relu6.h"
#include "opennna_operator_softmax.h"
#include "opennna_operator_conv2d.h"
#include "opennna_operator_dwconv2d.h"
#include "opennna_operator_padding.h"
#include "opennna_operator_maxpool.h"
#include "opennna_operator_avgpool.h"
#include "opennna_operator_leakyrelu.h"
#include "opennna_operator_tanh.h"
/************************OpenNNA库的相关类型&函数声明****************************/
#define LIB_NAME "OpenNNA2.0-Tinier, Faster, Easier To Use"
#define Author "xddcore 1034029664@qq.com"

#if(HARDWARE_ACCELERATION==0)//不使用硬件加速，纯c推理(Float32)
    typedef float Fmap_t;//特征图数据的类型
    typedef float Weights_t;//权重数据的类型
    typedef float Bias_t;//偏置数据的类型
    typedef unsigned int reg_t;//对每一个层的控制可以理解为对算子寄存器(参数)的控制
#elif(HARDWARE_ACCELERATION==1)//不使用硬件加速，纯c推理(Int8)
#define CLIP_MAX 255
#define CLIP_MIN 0
    /*
    typedef unsigned char Fmap_t;//特征图数据的类型
    typedef unsigned char Weights_t;//权重数据的类型
    typedef int Bias_t;//偏置数据的类型
    typedef int reg_t;//对每一个层的控制可以理解为对算子寄存器(参数)的控制
    */
    /*
     * 如果你使用Stm32进行Int8推理，请将以上类型定义换为以下类型定义
     * 原因:在STM32CUBEIDE+GCC下，char并不能表示负数，将会溢出为负数的补码。需要用int8_t,int32_t来表示负数
     */
	#include "stm32h7xx_hal.h"
    typedef uint8_t Fmap_t;//特征图数据的类型
    typedef uint8_t Weights_t;//权重数据的类型
    typedef int32_t Bias_t;//偏置数据的类型
    typedef int32_t reg_t;//对每一个层的控制可以理解为对算子寄存器(参数)的控制

#elif(HARDWARE_ACCELERATION==2)//ARM CMSIS-DSP加速
    //添加CMSIS-DSP支持(可以引入静态库 或者从CMSIS-DSP源码编译)
    //Note: 为了避免#error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
    //请在预编译命令中将"__FPU_PRESENT" = 1
    #include "arm_math.h"
    typedef float32_t Fmap_t;//特征图数据的类型
    typedef float32_t Weights_t;//权重数据的类型
    typedef float32_t Bias_t;//偏置数据的类型
    typedef uint32_t reg_t;//对每一个层的控制可以理解为对算子寄存器(参数)的控制

#elif(HARDWARE_ACCELERATION==3)//ARM SIMD_INT8加速

#endif

//网络层算子基本参数
struct Layer_Para_base{
    reg_t Input_Fmap_Channel; //输入特征图通道，也就是c
    reg_t Input_Fmap_Row; //输入特征图行，也就是h
    reg_t Input_Fmap_Col; //输入特征图列，也就是w
    reg_t Output_Fmap_Channel; //输出特征图通道，也就是c
    reg_t Output_Fmap_Row; //输出特征图行，也就是h
    reg_t Output_Fmap_Col; //输出特征图列，也就是w
};
typedef struct Layer_Para_base Layer_Para_Base;
//算子匹配
struct operator{
    char * Operator_Name;//算子名(和layer->Layer_Name进行匹配)
    void (*pfunc_Operator)(struct layer *Layer);//算子函数
};

//神经网络层对象
struct layer{
    struct layer *layer_prev;
    /*****************神经网络相关**********************/
    unsigned int Layer_Index;//层序号
    char *Layer_Name; //网络层名
    char *Layer_Name_Alias; //网络层别名
    void *Layer_Para_Base; //基本层参数地址
    void *Layer_Para_Extra; //额外层参数地址
    void *Input_Feature_Map; //输入特征图地址
    void *Output_Feature_Map; //输出特征图地址
    void *Weights; //权重地址
    void *Bias; //偏置地址
    //算子/激活函数
    void (*pfunc_Operator)(struct layer *Layer);
    /*****************神经网络相关**********************/
    struct layer *layer_next;
};

typedef struct layer layers;//神经网络层类型

//函数声明
void * OpenNNA_Malloc(unsigned long size);
void OpenNNA_Free(void * address);
#if(DEBUG==1)
void OpenNNA_Printf(char * strings);
#endif
struct layer * OpenNNA_CreateNetwork(void);
int OpenNNA_Add_Layer(struct layer * Network, \
                            char *Layer_Name, \
                            char *Layer_Name_Alias, \
                            const void *Layer_Para_Base, \
                            const void *Layer_Para_Extra, \
                            const void *Weights, \
                            const void *Bias \
                            );
void OpenNNA_Init(struct layer * Network);
#if(DEBUG==1)
void OpenNNA_Print_Network(struct layer * Network);
#endif
void OpenNNA_Predict(struct layer * Network, const void *Network_Input, void *Network_Output);
void OpenNNA_Free_Network(struct layer **pNetwork);

#endif //CORE_OPENNNA_CORE_H
