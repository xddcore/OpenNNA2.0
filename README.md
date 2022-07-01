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
- [ ] 1. 探究NNA架构设计
- [ ] 2. PS - PL 通信设计
- [ ] 3. 多NNA调度算法(参考linux进程(=OpenNNA的一个网络)，linux线程(=OpenNNA的一个网络中的一个层/算子))「内核态」
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
NNA调度层（对于FPGA）（模仿Linux对多核CPU的进程调度）1ms为调度最小时间。「内核态」

||

算子层（对于PC和MCU）
>-
硬件(CPU/NNA)