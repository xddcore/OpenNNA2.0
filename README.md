<!--
 * @Author: Chengsen Dong 1034029664@qq.com
 * @Date: 2022-07-01 19:07:43
 * @LastEditors: Chengsen Dong 1034029664@qq.com
 * @LastEditTime: 2022-07-05 13:19:46
 * @FilePath: /OpenNNA2.0/README.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# OpenNNA2.0
OpenNNA2.0-更易用，更通用，更多算子......

### OpenNNA核心特性

1. 适用性，移植性: 相同代码，可用于stm32，fpga，pc等可跑c的平台
2. 对于fpga:多加速器(NNA)调度，负载均衡
3. 提供算子开发框架，可自己开发自己的算子。为了独立性，一个算子一个.c文件
4. 提供demo: 1.手写数字 2.KWS(关键词识别) 3.yolo v1目标检测
5. 算子计算模式:CHW
6. 堆内存管理粒度:1.网络(四舍五入等于静态管理)2.网络层(算子)动态管理
7. 除了避免野指针等引发段错误，其他地方一律不设错误检测，按照demo的方式来调用，理论上不会出错。

### 移植要点
1. 堆内存申请/释放函数
2. printf函数
3. 确保SRAM，Flash能够满足网络结构的要求

### OpenNNA的发展方向

**Xilinx ZYNQ 系列FPGA神经网络加速器**做特别优化(多NNA调度，负载均衡等)

**PC，MCU**等提供纯C算子，不针对某个特定平台做算子优化。

### 开发规划

#### 7.4-7月底:
- [ ] 1. OpenNNA框架搭建(C)
- [ ] 2. 算子移植与优化(Conv2D)
- [ ] 3. 算子移植与优化(Depthwise Conv2D)
- [ ] 4. 算子移植与优化(Pool)
- [ ] 5. 算子移植与优化(Dense)
- [ ] 6. 算子移植与优化(Activation)
- [ ] 7. Tensorflow h5 file & tflite 权重偏置读取脚本(Python)(生成带有网络配置结构配置的.c文件)
- [ ] 8. PC Demo(手写数字｜KWS｜Yolo v1 目标检测)
- [ ] 9. Stm32 Demo(手写数字｜KWS｜Yolo v1 目标检测)

**Extra**

- [ ] 10. 探究更轻量和简单的堆内存管理方式

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
|0|应用层|用户态|NULL|
|1|网络层|用户态|双向循环链表|
|2|算子层(!FPGA)|用户态|纯C算子，若有二次开发需求，套层转换皮可以支持一些厂商级的算子（比如ST的CMSIS-NN等)|
|2|算子层(FPGA)|用户态|多NNA的资源调度|
|3|驱动层(FPGA)|内核态|Linux驱动|
|4|硬件层(CPU/NNA)|硬件|NULL|

### 框架功能指南
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
- [ ] 网络释放方式1-释放网络对象的堆内存+输入输出特征图的堆内存
- [ ] 网络释放方式2-仅释放输入输出特征图的堆内存
- [ ] 以网络层(算子)为粒度的堆内存管理方式
- [ ] 整理代码+宏定义+条件编译等
- [ ] 网络模型直接加载(提取脚本自动生成模型的.c文件(含网络结构+权重)，将.c文件添加至工程中，直接运行加载.c文件中的加载函数)

2. opennna_operator_example.c:
- [x] OpenNNA算子开发框架
3. opennna_operator_conv2d.c:
- [ ] 卷积算子
4. opennna_operator_dwconv2d.c:
- [ ] 深度可分离卷积算子
5. opennna_operator_padding.c:
- [ ] 填充算子
6. opennna_operator_maxpool.c:
- [ ] 最大池化算子
7. opennna_operator_avgpool.c:
- [ ] 平均池化算子
8. opennna_operator_dense.c:
- [ ] 全连接算子
9. opennna_operator_relu.c:
- [ ] relu算子
10. opennna_operator_relu6.c:
- [ ] relu6算子
11. opennna_operator_leakyrelu.c:
- [ ] leakyrelu算子
12. opennna_operator_tanh.c:
- [ ] tanh算子
13. opennna_operator_softmax.c:
- [ ] softmax算子