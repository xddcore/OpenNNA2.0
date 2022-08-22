<!--
 * @Author: Chengsen Dong 1034029664@qq.com
 * @Date: 2022-07-01 19:07:43
 * @LastEditors: Chengsen Dong 1034029664@qq.com
 * @LastEditTime: 2022-08-22 14:19:45
 * @FilePath: /OpenNNA2.0/README.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# OpenNNA2.0
>OpenNNA2.0，一个基于C语言(C99)的开源神经网络推理框架

OpenNNA2.0-Tinier, Faster, Easier To Use

### 为什么会有OpenNNA2.0？｜OpenNNA2.0的故事
2022年暑假(6-9月份)，xdd同学刚刚大学毕业(英本大三)。OpenNNA是我的本科毕业设计，当时做得飞快，对于易用性和通用性的考量不是很充分。大三后期充分欣赏了Linux的设计理念，同时接收到了来自英国政府的4000磅科研经费。于是乎，打算多往前走几步，把OpenNNA这个毕设做得完整一些，最终，就形成了大家所看到的OpenNNA2.0。

### 一些感悟和期望
OpenNNA2.0在我心底的定位是一个实践项目，把一些学到的思想和理念进行融合。同时，因为2023年末我将正式成为一只工程师。我也需要这样一个项目来在再次训练工程思维以及熟悉框架的思想。所以，在写OpenNNA2.0的过程中，四舍五入，xdd同学也是摸着石头过河的。希望这个项目可以给大家未来的工作带来一些启发。

### 致谢
对于这一系列的工作，王哥([RoboBachelor](https://github.com/RoboBachelor))与我进行了多次深度的技术交流。本项目的很多灵感和方向来源于技术交流。在此，预祝王哥的paper早日accept，预祝王哥和嫂子的爱情地久天长，预祝董哥和王哥的友谊万古长青，预祝王哥大四GPA90+，硕士一路起飞🛫️！王哥 YYDS！

-xdd 2022.07.28 于Durham, UK

### OpenNNA核心特性

1. 适用性，移植性: 相同代码，可用于stm32，fpga，pc等可跑c的平台
2. 核心代码仅400+行，注释清晰，命名直白，可方便二次开发
3. 推理精度支持:Float32, Int8, 其他精度类型未经测试，用户可自行拓展
4. 对于fpga:多加速器(NNA)调度，负载均衡｜目前计划支持的平台有正点院子ZYNQ-7020;PYNQ-Z2;Xlinx ZCU102
5. 提供算子开发框架，可自己开发自己的算子。为了独立性，一个算子一个.c文件
6. 提供demo: 1.手写数字 2.KWS(关键词识别) 3.yolo v1目标检测
7. 内存排列模式:CHW和HWC（经过试验，得益于优秀的流水线机制，在cortex m核上顺序读取内存空间和以一定规律间隔读取内存空间效率几乎相同)
8. 堆内存管理粒度:1.网络(四舍五入等于静态管理)2.网络层(算子)动态管理
9. 除了避免野指针等引发段错误，其他地方一律不设错误检测，按照demo的方式来调用/直接使用工具将H5/tflite模型文件转为C Model，理论上不会出错。
10. 提供两种网络释放方式:1.仅释放特征图堆内存(在这种释放方式下，重新调用Init函数可以恢复神神经网络计算)。2.释放整个网络的所有有关数据(例如网络结构，特征图堆内存等|网络权重由于是编译器分配的地址，无法通过OpenNNA来free。不过如果想要把这段内存用起来，可以直接对这些变量取址，然后用指针直接往里面去写入其他东西就行)(在这种释放方式下，网络所有信息将会永久从堆内存中被移除。恢复网络计算只能重启)
11. 提供不同硬件平台的算子硬件加速方案，如ARM的CMSIS-DSP/SIMD，FPGA的神经网络加速器等

### 移植要点
1. (**必要**)堆内存申请/释放函数
2. (**可选**)printf函数｜用户通过DEBUG宏进行使能/屏蔽
3. (**必要**)确保SRAM，Flash能够满足网络结构的要求(这一点将会在H5/tflite转C Model工具中被检出)

### OpenNNA的发展方向

**Xilinx ZYNQ 系列FPGA神经网络加速器**做特别优化(多NNA调度，负载均衡等)

**PC，MCU**等提供纯C算子，不针对某个特定平台做算子优化。

### OpenNNA架构

|Index| 层| 空间|注释|
|:----:|:----:|:----:|:----:|
|0|应用层|用户态||
|1|网络层|用户态|双向循环链表|
|2|算子层(!FPGA)|用户态|纯C算子，若有二次开发需求，套层转换皮可以支持一些厂商级的算子（比如ST的CMSIS-NN等)|
|2|算子层(FPGA)|用户态|多NNA的资源调度|
|3|驱动层(FPGA)|内核态|Linux驱动|
|4|硬件层(CPU/NNA)|硬件||

### OpenNNA工作流

|步骤|操作|软件|硬件平台|
|:----:|:----:|:----:|:----:|
|1️⃣|收集数据集，预处理数据集|DataAssitant|PC|
|2️⃣|训练神经网络(自动训练脚本，或将提供云端自动训练服务)|Tensorflow|PC(GPU)|
|3️⃣|Tensorflow Model 转 C Model File(若需量化，也在本步骤进行)|OpenNNA_Model_Converter.py|PC|
|4️⃣|部署到硬件平台运行|OpenNNA框架源码+C Model File|任意具有C编译器支持的硬件平台|
|5️⃣|根据不同的硬件平台，配置OpenNNA启用算子硬件加速，以获得更高的性能|||
|6️⃣|利用神经网络做一些具体应用(目标分类，目标检测，语音关键词识别等)|||

### OpenNNA算子支持
>xdd说:面对浩如烟海的硬件平台,手写算子对于单打独斗的个人爱好者来说是个事业，慢慢来<br>

>为了发挥最大性能，在STM32平台使用SIMD指令(__SMUAD)实现并行加速时:<br>
>请注意保证特征图的宽**2字节对齐**<br>

|算子|FPGA加速|CMSIS-DSP加速(仅fp32)|SIMD加速(仅int8)|HWC/CHW|Convert From Tensorflow|注释|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|Conv2d|✅|✅||✅|✅|面向图像数据/频谱数据分别提供最优实现策略|
|Depthwise Conv2d|✅|||✅|✅||
|Padding|✅|||✅|✅|仅对称填充|
|Max Pool||||✅|✅||
|Avg Pool||||✅|✅||
|Dense|✅|✅|✅|✅|✅||
|ReLU|✅|||✅|✅||
|ReLU6|✅|||✅|✅||
|LeakyReLU|✅|||✅|✅||
|tanh||||✅|✅||
|Softmax||||✅|✅||

### Flash占用
> demo example将所有权重和偏置放在栈中，忽略了权重和偏置对Flash占用的影响。更能体现OpenNNA的Flash实际占用大小。
>DEBUG = 0 时，Flash占用(无代码优化)还能在以下基础上减少4-5KB


|Flash|代码优化等级|环境|注释|
|:----:|:----:|:----:|:----:|
|14.13KB|无优化|STM32CubeIDE(Version: 1.10.1Build: 12716_20220707_0928 (UTC))|在导入OpenNNA2.0 src+demo-example前 Flash占用为42.89KB，导入后Flash占用为57.02KB。故得到OpenNNA Flash占用为14.13KB|
|10.76KB|Optimize for size(-Os)|STM32CubeIDE(Version: 1.10.1Build: 12716_20220707_0928 (UTC))|在导入OpenNNA2.0 src+demo-example前 Flash占用为30.46KB，导入后Flash占用为41.22KB。故得到OpenNNA Flash占用为10.76KB|

### 快速验证
>为了方便大家快速验证框架的功能，我们针对主流平台提供快速验证DEMO。同时也希望大家在使用的过程中，踊跃提出建议与意见。以及欢迎大家进行二次开发。

>同时提供DEMO的jupyter Notebook，可以在网络结构不变的情况下，更换自己的数据集，得到自己的训练权重来替换demo的C Model File中的权重。快速部署自己的任务。

>若自行移植本框架到其他硬件平台，请先尝试运行示例算子推理DEMO。若此DEMO可以正常运行，则证明框架移植成功。

>DEMO位于./platform目录下。<br>
>DEMO的运行需要包含两个必需条件:<br>
>1.src目录下的OpenNNA源码<br>
>2.神经网络模型的C Model File(其实就是利用OpenNNA框架提供的API构造网络结构),C Model File一般以 opennna_demo_xxxxxxx.c命名。


>Heap和Flash统计的单位均为Bytes; <br>
Heap统计为范围值，最小值为动态分配的输出值，最大值为静态分配的最大值，实际推理过程中，Heap占用在Heap范围内浮动。

>✅(xxxx;xxxx)括号内的数字为FPS；<br>
FPS将会测试两个指标:<br>
1.FPS指标为网络一个生命周期(构造，推理，释放)的耗时；<br>
2.FPS指标为网络推理的耗时。<br>
❌代表因为权重精度等问题，导致的Sram/Flash溢出。故不提供Demo。<br>
3.Stm32采用FreeRTOS任务统计API进行运行时间统计，时基为5*(10^-5)s=50us

>PC为Apple M1 Pro(10核CPU+16GPU, 16GB内存, Clion 2022.1.3)<br>
Note:后期可能会测试I9-12900K和I5-9400F<br><br>
STM32H7A3ZIT6Q(280Mhz, Cortex M7, FPU Enable(CMSIS-DSP&arm_cortexM7lfdp_math), 1.4MB SRAM, 2MB Flash, Free RTOS|STM32CubeIDE(-ofast))<br>

>其他性能指标:<br>
1.**以Mnist手写数字识别+OpenNNA-Paper为例**，在采用STM32进行构造OpenNNA Paper中的卷积网络时，构造+释放网络的时间约为0.015873s(63 fps)。

#### Float32|STM32 FPU
|DEMO|网络类型|PC|STM32|STC|FPGA|Heap|Flash(float32)|注释|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|示例算子推理|NULL|✅(333333)|✅(6666)| | |616|160|若此demo可以运行，则证明框架核心功能正常|
|Mnist手写数字识别|全连接神经网络|✅(2398;2755)|✅(136;)| ||4232~6856|407080||
|Mnist手写数字识别|卷积神经网络(LeNet5)|✅(506;544)|✅(14;)| | |8744~39396|246824||
|Mnist手写数字识别|卷积神经网络(OpenNNA-Paper)|✅(219;222)|✅(5.8;6.4)| | |8740~116708|316968|[OpenNNA Paper](https://github.com/xddcore/OpenNNA/blob/main/paper/An%20FPGA%20Resource%20Adaptable%20General%20Neural%20Network%20Accelerator_UKSim2022_08April2022_Fin.pdf)中提到的Network模型，可以对比验证|
|热成像传感器的手势分类|卷积神经网络(LeNet5优化版)| | | | | | |
|目标分类|MobileNet V1(α=0.25)| |❌| | | | |
|目标检测|YOLO V1| |❌| | | | |
|语音关键词分类|卷积神经网络| | | | | | |

#### Float32|STM32 FPU&CMSIS-DSP(❌❌:负优化不做测试)
|DEMO|网络类型|PC|STM32|STC|FPGA|Heap|Flash(float32)|注释|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|示例算子推理|NULL|✅(333333)|❌❌| | |616|160|若此demo可以运行，则证明框架核心功能正常|
|Mnist手写数字识别|全连接神经网络|✅(2398;2755)|❌❌| ||4232~6856|407080||
|Mnist手写数字识别|卷积神经网络(LeNet5)|✅(506;544)|❌❌| | |8744~39396|246824||
|Mnist手写数字识别|卷积神经网络(OpenNNA-Paper)|✅(219;222)|✅(1.07)| | |8740~116708|316968|[OpenNNA Paper](https://github.com/xddcore/OpenNNA/blob/main/paper/An%20FPGA%20Resource%20Adaptable%20General%20Neural%20Network%20Accelerator_UKSim2022_08April2022_Fin.pdf)中提到的Network模型，可以对比验证|
|热成像传感器的手势分类|卷积神经网络(LeNet5优化版)| | | | | | |
|目标分类|MobileNet V1(α=0.25)| |❌| | | | |
|目标检测|YOLO V1| |❌| | | | |
|语音关键词分类|卷积神经网络| | | | | | |

#### Int8
|DEMO|网络类型|PC|STM32|STC|FPGA|Heap|Flash(int8)|注释|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|Mnist手写数字识别|全连接神经网络|✅(4292;4587)|✅(833;)| ||1368~2024|101770||
|Mnist手写数字识别|卷积神经网络(LeNet5)||| | ||||
|Mnist手写数字识别|卷积神经网络(OpenNNA-Paper)||| | |3380-30372|79242|[OpenNNA Paper](https://github.com/xddcore/OpenNNA/blob/main/paper/An%20FPGA%20Resource%20Adaptable%20General%20Neural%20Network%20Accelerator_UKSim2022_08April2022_Fin.pdf)中提到的Network模型，可以对比验证|
|热成像传感器的手势分类|卷积神经网络(LeNet5优化版)| | | | | | |
|目标分类|MobileNet V1(α=0.25)| || | | | |
|目标检测|YOLO V1| || | | | |
|语音关键词分类|卷积神经网络| | | | | | |

#### Int8 |STM32 SIMD
|DEMO|网络类型|PC|STM32|STC|FPGA|Heap|Flash(int8)|注释|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|Mnist手写数字识别|全连接神经网络|✅(4292;4587)|| |||||
|Mnist手写数字识别|卷积神经网络(LeNet5)||| | ||||
|Mnist手写数字识别|卷积神经网络(OpenNNA-Paper)||| | |||[OpenNNA Paper](https://github.com/xddcore/OpenNNA/blob/main/paper/An%20FPGA%20Resource%20Adaptable%20General%20Neural%20Network%20Accelerator_UKSim2022_08April2022_Fin.pdf)中提到的Network模型，可以对比验证|
|热成像传感器的手势分类|卷积神经网络(LeNet5优化版)| | | | | | |
|目标分类|MobileNet V1(α=0.25)| || | | | |
|目标检测|YOLO V1| || | | | |
|语音关键词分类|卷积神经网络| | | | | | |

---
---
---

**以下为开发人员板块，普通用户无需关心**

### 开发规划

#### 7.4-7月底 - ～(事务繁忙，持续维护中):
- [x] 1. OpenNNA框架搭建(C)
- [x] 2. 算子移植与优化(Conv2D)
- [x] 3. 算子移植与优化(Depthwise Conv2D)
- [x] 4. 算子移植与优化(Padding)
- [x] 5. 算子移植与优化(Pool)
- [x] 6. 算子移植与优化(Dense)
- [x] 7. 算子移植与优化(Activation)
- [x] 8. PC & Stm32 的手写数字 Demo(fp32)
- [ ] 9. Int16/Int8量化权重的算子支持(无指令集层加速)
- [ ] 10. Int16/Int8量化权重的算子支持(ARM SIMD加速)
- [ ] 11. PC & Stm32 的手写数字 Demo(int16/int8)
- [ ] 12. Tensorflow h5 file & tflite 权重偏置读取脚本(Python)(生成带有网络配置结构配置的.c文件)
- [ ] 13. PC Demo(KWS｜Yolo v1 目标检测)
- [ ] 14. Stm32 Demo(KWS｜Yolo v1 目标检测)

**Extra**

- [ ] 10. 探究更轻量和简单的堆内存管理方式
- [ ] 11.C语言手写K-means聚类算子，实现无训练自学习分类算法
- [ ] 12.框架堆内存完全计数(10.任务的并行目标)

#### 8.1-8.20:
- [ ] 0. 研究哪些算子值得被FPGA加速(根据上一篇论文的结果，卷积层和全连接层以及简单激活函数的加速收益非常高)
- [ ] 1. 探究NNA架构设计(一个NNA支持卷积/全连接加速，NNA内部缓冲区建立+循环展开)
- [ ] 2. PS - PL 通信设计
- [ ] 3. 多NNA调度算法(参考linux进程(=OpenNNA的一个网络)，linux线程(=OpenNNA的一个网络中的一个层/算子))「部署在用户态」
- [ ] 4. 正点原子ZYNQ-7020 DEMO
- [ ] 5. PYNQ-Z2 DEMO
- [ ] 6. ZCU102 Ultrascale+ MPSOC DEMO

#### 9.1-9.10:
- [ ] 收集实验数据，整理技术文档。准备论文发表

---
### 一些优化思路&发展方向

#### 1.针对于MCU平台使用FreeRTOS(heap_4)的pvPortMalloc&vPortFree
>引用:https://www.freertos.org/a00111.html

如果 RTOS 对象是动态创建的，那么标准 C 库 malloc() 和 free() 函数有时可以用于此目的，但是......

它们并不总是在嵌入式系统上可用，
它们占用了宝贵的代码空间，
它们不是线程安全的，并且
它们不是确定性的（执行函数所花费的时间会因调用而异）
...因此，通常需要替代的内存分配实现。
一个嵌入式/实时系统可能具有与另一个非常不同的 RAM 和时序要求 - 因此单个 RAM 分配算法将只适用于应用程序的子集。

为了解决这个问题，FreeRTOS 将内存分配 API 保留在其可移植层中。可移植层位于实现核心 RTOS 功能的源文件之外，允许提供适用于正在开发的实时系统的特定应用实现。当 RTOS 内核需要 RAM 时，它不会调用 malloc()，而是调用 pvPortMalloc()。当 RAM 被释放时，RTOS 内核不调用 free()，而是调用 vPortFree()。

FreeRTOS 提供了多种复杂性和功能不同的堆管理方案。也可以提供自己的堆实现，甚至同时使用两个堆实现。同时使用两个堆实现允许将任务堆栈和其他 RTOS 对象放置在快速的内部 RAM 中，并将应用程序数据放置在较慢的外部 RAM 中。

#### 2.[定点/Int8/Int16优化]针对于Arm Cortex架构使用SIMD(单指令多数据)
>引用:https://www.keil.com/pack/doc/CMSIS/Core/html/group__intrinsic__SIMD__gr.html
**__SMLAD()** INT点积
---

### 框架功能开发CheckPoint
0. OpenNNA_Converter.py
- [ ] 网络模型直接加载(提取脚本自动生成模型的.c文件(含网络结构+权重)，将.c文件添加至工程中，直接运行加载.c文件中的加载函数)

1. opennna_core.c:

- [x] 堆内存管理接口(申请/释放)
- [x] 库信息打印接口
- [x] 网络对象创建
- [x] 网络层添加
- [x] 网络信息打印
- [x] 网络层基参数类型+基参数类型成员类型指定
- [x] 输入输出特征图地址自动按需分配
- [x] 权重和偏置的类型(精度)指定
- [x] 网络推理实现
- [x] 网络释放方式1-释放网络对象的堆内存+释放输入输出特征图的堆内存(若有)
- [x] 网络释放方式2-释放输入输出特征图的堆内存(仅静态方式申请的特征图堆内存支持这一操作)
- [x] 整理代码+Readme
- [x] 以网络层(算子)为粒度的堆内存管理方式
- [x] CHW / HWC的计算模式转换(算子级实现)
- [x] 整理代码+宏定义+条件编译等

2. opennna_operator_example.c:
- [x] OpenNNA算子开发框架
3. opennna_operator_conv2d.c:
- [x] 卷积算子
- [ ] 探究三种不同卷积实现思路之间的差异(以输入特征图为导向，以卷积核为导向，以输出特征图为导向)
- [ ] 对于stm32使用一种比较优的实现思路，完成汇编卷积的实现
4. opennna_operator_dwconv2d.c:
- [x] 深度可分离卷积算子
5. opennna_operator_padding.c:
- [x] 填充算子
6. opennna_operator_maxpool.c:
- [x] 最大池化算子
7. opennna_operator_avgpool.c:
- [x] 平均池化算子
8. opennna_operator_dense.c:
- [x] 全连接算子
9. opennna_operator_relu.c:
- [x] relu算子
10. opennna_operator_relu6.c:
- [x] relu6算子
11. opennna_operator_leakyrelu.c:
- [x] leakyrelu算子
12. opennna_operator_tanh.c:
- [x] tanh算子
13. opennna_operator_softmax.c:
- [x] softmax算子