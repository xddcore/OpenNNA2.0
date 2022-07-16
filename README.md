<!--
 * @Author: Chengsen Dong 1034029664@qq.com
 * @Date: 2022-07-01 19:07:43
 * @LastEditors: Chengsen Dong 1034029664@qq.com
 * @LastEditTime: 2022-07-16 15:10:14
 * @FilePath: /OpenNNA2.0/README.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# OpenNNA2.0
OpenNNA2.0-Tinier, Faster, Easier To Use

### OpenNNA核心特性

1. 适用性，移植性: 相同代码，可用于stm32，fpga，pc等可跑c的平台
2. 对于fpga:多加速器(NNA)调度，负载均衡
3. 提供算子开发框架，可自己开发自己的算子。为了独立性，一个算子一个.c文件
4. 提供demo: 1.手写数字 2.KWS(关键词识别) 3.yolo v1目标检测
5. 内存排列模式:CHW和HWC（经过试验，得益于优秀的流水线机制，在cortex m核上顺序读取内存空间和以一定规律间隔读取内存空间效率几乎相同)
6. 堆内存管理粒度:1.网络(四舍五入等于静态管理)2.网络层(算子)动态管理
7. 除了避免野指针等引发段错误，其他地方一律不设错误检测，按照demo的方式来调用/直接使用工具将H5/tflite模型文件转为C Model，理论上不会出错。
8. 提供两种网络释放方式:1.仅释放特征图堆内存(在这种释放方式下，重新调用Init函数可以恢复神神经网络计算)。2.释放整个网络的所有有关数据(例如网络结构，特征图堆内存等|网络权重由于是编译器分配的地址，无法通过OpenNNA来free。不过如果想要把这段内存用起来，可以直接对这些变量取址，然后用指针直接往里面去写入其他东西就行)(在这种释放方式下，网络所有信息将会永久从堆内存中被移除。恢复网络计算只能重启)

### 移植要点
1. (**必要**)堆内存申请/释放函数
2. (**可选**)printf函数
3. (**必要**)确保SRAM，Flash能够满足网络结构的要求(这一点将会在H5/tflite转C Model工具中被检出)

### OpenNNA的发展方向

**Xilinx ZYNQ 系列FPGA神经网络加速器**做特别优化(多NNA调度，负载均衡等)

**PC，MCU**等提供纯C算子，不针对某个特定平台做算子优化。

### 快速验证
>为了方便大家快速验证框架的功能，我们针对主流平台提供快速验证DEMO。同时也希望大家在使用的过程中，踊跃提出建议与意见。以及欢迎大家进行二次开发。

>若自行移植本框架到其他硬件平台，请先尝试运行示例算子推理DEMO。若此DEMO可以正常运行，则证明框架移植成功。

|DEMO|网络类型|PC|STM32|STC8051|FPGA|Heap|Flash|注释|
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|示例算子推理|NULL| | | | | | |若此demo可以运行，则证明框架核心功能正常|
|Mnist手写数字识别|全连接神经网络| | | | | | |
|Mnist手写数字识别|卷积神经网络| | | | | | |
|热成像传感器的手势识别|全连接神经网络| | | | | | |
|热成像传感器的手势识别|卷积神经网络| | | | | | |
|语音关键词识别|卷积神经网络| | | | | | |
|目标分类|MobileNet V1(α=0.25)| | | | | | |
|目标检测|YOLO V1| | | | | | |

### OpenNNA算子支持
>xdd说:面对浩如烟海的硬件平台,手写算子对于单打独斗的个人爱好者来说是个事业，慢慢来

|算子|可被FPGA加速|HWC/CHW|Convert From Tensorflow|注释|
|:----:|:----:|:----:|:----:|:----:|
|Conv2d|Y|Y|Y|面向图像数据/频谱数据分别提供最优实现策略|
|Depthwise Conv2d|Y|Y|Y||
|Padding|Y|Y|Y|对称/非对称填充|
|Max Pool||Y|Y||
|Avg Pool||Y|Y||
|Dense|Y|Y|Y||
|ReLU|Y|Y|Y||
|ReLU6|Y|Y|Y||
|LeakyReLU|Y|Y|Y||
|tanh||Y|Y||
|Softmax||Y|Y||

### 开发规划

#### 7.4-7月底:
- [x] 1. OpenNNA框架搭建(C)
- [ ] 2. 算子移植与优化(Conv2D)
- [ ] 3. 算子移植与优化(Depthwise Conv2D)
- [ ] 4. 算子移植与优化(Padding)
- [ ] 5. 算子移植与优化(Pool)
- [ ] 6. 算子移植与优化(Dense)
- [ ] 7. 算子移植与优化(Activation)
- [ ] 8. Tensorflow h5 file & tflite 权重偏置读取脚本(Python)(生成带有网络配置结构配置的.c文件)
- [ ] 9. PC Demo(手写数字｜KWS｜Yolo v1 目标检测)
- [ ] 10. Stm32 Demo(手写数字｜KWS｜Yolo v1 目标检测)

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

### OpenNNA架构

|Index| 层| 空间|注释|
|:----:|:----:|:----:|:----:|
|0|应用层|用户态||
|1|网络层|用户态|双向循环链表|
|2|算子层(!FPGA)|用户态|纯C算子，若有二次开发需求，套层转换皮可以支持一些厂商级的算子（比如ST的CMSIS-NN等)|
|2|算子层(FPGA)|用户态|多NNA的资源调度|
|3|驱动层(FPGA)|内核态|Linux驱动|
|4|硬件层(CPU/NNA)|硬件||

### 框架功能指南
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
- [ ] 卷积算子
- [ ] 探究三种不同卷积实现思路之间的差异(以输入特征图为导向，以卷积核为导向，以输出特征图为导向)
- [ ] 对于stm32使用一种比较优的实现思路，完成汇编卷积的实现
4. opennna_operator_dwconv2d.c:
- [ ] 深度可分离卷积算子
5. opennna_operator_padding.c:
- [ ] 填充算子
6. opennna_operator_maxpool.c:
- [ ] 最大池化算子
7. opennna_operator_avgpool.c:
- [ ] 平均池化算子
8. opennna_operator_dense.c:
- [x] 全连接算子
9. opennna_operator_relu.c:
- [x] relu算子
10. opennna_operator_relu6.c:
- [ ] relu6算子
11. opennna_operator_leakyrelu.c:
- [ ] leakyrelu算子
12. opennna_operator_tanh.c:
- [ ] tanh算子
13. opennna_operator_softmax.c:
- [x] softmax算子