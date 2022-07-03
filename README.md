<!--
 * @Author: Chengsen Dong 1034029664@qq.com
 * @Date: 2022-07-01 19:07:43
 * @LastEditors: Chengsen Dong 1034029664@qq.com
 * @LastEditTime: 2022-07-03 10:06:55
 * @FilePath: /OpenNNA2.0/README.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# OpenNNA2.0
OpenNNA2.0-更易用，更通用，更多算子......

### OpenNNA核心特性

1. 适用性，移植性: 相同代码，可用于stm32，fpga，pc平台
2. 对于fpga:多加速器(NNA)调度，负载均衡
3. 提供算子开发框架，可自己开发自己的算子。为了独立性，一个算子一个.c文件
4. 提供demo: 1.手写数字 2.KWS(关键词识别) 3.yolo v1目标检测

### 开发规划

#### 7.4-7月底:
- [ ] 1. OpenNNA框架搭建(C)
- [ ] 2. 算子优化(Conv2D)
- [ ] 3. 算子优化(Depthwise Conv2D)
- [ ] 4. 算子优化(Pool)
- [ ] 5. 算子优化(Dense)
- [ ] 6. 算子优化(Activation)
- [ ] 7. Tensorflow h5 file & tflite 权重偏置读取脚本(Python)
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

用户
>-
应用层「用户态」
>-
网络层（双向循环链表）「用户态」
>-
算子层（对于PC和MCU）

||

NNA调度层（对于FPGA）（模仿Linux对多核CPU的进程调度）1ms为调度最小时间。「部署在用户态」
>-
NNA的Linux驱动(对于FPGA)
>-
硬件(CPU/NNA)

### 框架功能指南
1. opennna_core.c:

- [x] 堆内存管理接口(申请/释放)
- [x] 库信息打印接口
- [x] 网络对象创建
- [x] 网络层添加
- [x] 网络信息打印
- [x] 网络层基参数类型+基参数类型成员类型指定
- [ ] 输入输出特征图地址自动按需分配
- [ ] 权重和偏置的类型(精度)指定
- [ ] 网络释放方式1-释放网络对象的堆内存+输入输出特征图的堆内存
- [ ] 网络释放方式2-仅释放输入输出特征图的堆内存
- [ ] 网络模型直接加载(提取脚本自动生成模型的.c文件(含网络结构+权重)，将.c文件添加至工程中，直接运行加载.c文件中的加载函数)
2. opennna_operator_example.c:
OpenNNA算子开发框架
3. opennna_operator_conv2d.c:
卷积算子
4. opennna_operator_dwconv2d.c:
深度可分离卷积算子
5. opennna_operator_padding.c:
填充算子
6. opennna_operator_maxpool.c:
最大池化算子
7. opennna_operator_avgpool.c:
平均池化算子
8. opennna_operator_dense.c:
全连接算子
9. opennna_operator_relu.c:
relu算子
10. opennna_operator_relu6.c:
relu6算子
11. opennna_operator_leakyrelu.c:
leakyrelu算子
12. opennna_operator_tanh.c:
tanh算子
13. opennna_operator_softmax.c:
softmax算子