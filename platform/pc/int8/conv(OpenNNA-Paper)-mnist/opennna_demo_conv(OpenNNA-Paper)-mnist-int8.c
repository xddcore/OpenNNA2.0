//
// Created by 董程森 on 2022/7/13.
//
//
// Created by 董程森 on 2022/7/7.
//
#include "opennna_core.h"
#include "stdio.h"
/*****************OpenNNA 卷积神经网络(OpenNNA-Paper)实现Mnist手写数字分类示例**********************/
int main() {
    /*****************第1步:创建神经网络对象**********************/
    struct layer * Network = OpenNNA_CreateNetwork();
    /*****************第2步:配置网络层参数**********************/
    //第一层Padding(对称填充=4，Mnist 1,28,28 填充至 1,32,32
    struct Layer_Para_base *Layer_Para_Base1 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Padding *Layer_Para_Padding1 = OpenNNA_Malloc(sizeof(Layer_Para_Padding));
    Layer_Para_Base1->Input_Fmap_Channel=1;
    Layer_Para_Base1->Input_Fmap_Row=28;
    Layer_Para_Base1->Input_Fmap_Col=28;
    Layer_Para_Base1->Output_Fmap_Channel=1;
    Layer_Para_Base1->Output_Fmap_Row=32;
    Layer_Para_Base1->Output_Fmap_Col=32;

    //填充两圈
    Layer_Para_Padding1->padding = 2;

    //第二层Conv2d
    struct Layer_Para_base *Layer_Para_Base2 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d2 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base2->Input_Fmap_Channel=1;
    Layer_Para_Base2->Input_Fmap_Row=32;
    Layer_Para_Base2->Input_Fmap_Col=32;
    Layer_Para_Base2->Output_Fmap_Channel=16;
    Layer_Para_Base2->Output_Fmap_Row=30;
    Layer_Para_Base2->Output_Fmap_Col=30;

    Layer_Para_Conv2d2->kernel_row=3;
    Layer_Para_Conv2d2->kernel_col=3;
    Layer_Para_Conv2d2->kernel_channel=1;
    Layer_Para_Conv2d2->filters=16;
    Layer_Para_Conv2d2->strides_row=1;
    Layer_Para_Conv2d2->strides_col=1;

    //第三层ReLu激活函数
    struct Layer_Para_base *Layer_Para_Base3 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_ReLU *Layer_Para_ReLU3 = OpenNNA_Malloc(sizeof(Layer_Para_ReLU));
    Layer_Para_Base3->Input_Fmap_Channel=16;
    Layer_Para_Base3->Input_Fmap_Row=30;
    Layer_Para_Base3->Input_Fmap_Col=30;
    Layer_Para_Base3->Output_Fmap_Channel=16;
    Layer_Para_Base3->Output_Fmap_Row=30;
    Layer_Para_Base3->Output_Fmap_Col=30;

    //第四层maxpool
    struct Layer_Para_base *Layer_Para_Base4 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_MaxPool *Layer_Para_MaxPool4 = OpenNNA_Malloc(sizeof(Layer_Para_MaxPool));
    Layer_Para_Base4->Input_Fmap_Channel=16;
    Layer_Para_Base4->Input_Fmap_Row=30;
    Layer_Para_Base4->Input_Fmap_Col=30;
    Layer_Para_Base4->Output_Fmap_Channel=16;
    Layer_Para_Base4->Output_Fmap_Row=15;
    Layer_Para_Base4->Output_Fmap_Col=15;

    Layer_Para_MaxPool4->strides_col=2;
    Layer_Para_MaxPool4->strides_row=2;
    Layer_Para_MaxPool4->kernel_row=2;
    Layer_Para_MaxPool4->kernel_col=2;

    //第五层Conv2d
    struct Layer_Para_base *Layer_Para_Base5 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d5 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base5->Input_Fmap_Channel=16;
    Layer_Para_Base5->Input_Fmap_Row=15;
    Layer_Para_Base5->Input_Fmap_Col=15;
    Layer_Para_Base5->Output_Fmap_Channel=32;
    Layer_Para_Base5->Output_Fmap_Row=13;
    Layer_Para_Base5->Output_Fmap_Col=13;

    Layer_Para_Conv2d5->kernel_row=3;
    Layer_Para_Conv2d5->kernel_col=3;
    Layer_Para_Conv2d5->kernel_channel=16;
    Layer_Para_Conv2d5->filters=32;
    Layer_Para_Conv2d5->strides_row=1;
    Layer_Para_Conv2d5->strides_col=1;

    //第六层ReLU激活函数
    struct Layer_Para_base *Layer_Para_Base6 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_ReLU *Layer_Para_ReLU6 = OpenNNA_Malloc(sizeof(Layer_Para_ReLU));
    Layer_Para_Base6->Input_Fmap_Channel=32;
    Layer_Para_Base6->Input_Fmap_Row=13;
    Layer_Para_Base6->Input_Fmap_Col=13;
    Layer_Para_Base6->Output_Fmap_Channel=32;
    Layer_Para_Base6->Output_Fmap_Row=13;
    Layer_Para_Base6->Output_Fmap_Col=13;

    //第七层maxpool
    struct Layer_Para_base *Layer_Para_Base7 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_MaxPool *Layer_Para_MaxPool7 = OpenNNA_Malloc(sizeof(Layer_Para_MaxPool));
    Layer_Para_Base7->Input_Fmap_Channel=32;
    Layer_Para_Base7->Input_Fmap_Row=13;
    Layer_Para_Base7->Input_Fmap_Col=13;
    Layer_Para_Base7->Output_Fmap_Channel=32;
    Layer_Para_Base7->Output_Fmap_Row=6;
    Layer_Para_Base7->Output_Fmap_Col=6;

    Layer_Para_MaxPool7->strides_col=2;
    Layer_Para_MaxPool7->strides_row=2;
    Layer_Para_MaxPool7->kernel_row=2;
    Layer_Para_MaxPool7->kernel_col=2;

    //第八层Dense 64
    struct Layer_Para_base *Layer_Para_Base8 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Dense *Layer_Para_Dense8 = OpenNNA_Malloc(sizeof(Layer_Para_Dense));
    Layer_Para_Base8->Input_Fmap_Channel=32;
    Layer_Para_Base8->Input_Fmap_Row=6;
    Layer_Para_Base8->Input_Fmap_Col=6;
    Layer_Para_Base8->Output_Fmap_Channel=1;
    Layer_Para_Base8->Output_Fmap_Row=1;
    Layer_Para_Base8->Output_Fmap_Col=64;

    Layer_Para_Dense8->units = 64;

    Layer_Para_Dense8->Si = 0.018646985292434692;
    Layer_Para_Dense8->Sw = 0.005728338845074177;
    Layer_Para_Dense8->Sb = 0.00010681625280994922;
    Layer_Para_Dense8->So = 0.0777057483792305;

    Layer_Para_Dense8->Zi = -128;
    Layer_Para_Dense8->Zw = 0;
    Layer_Para_Dense8->Zb = 0;
    Layer_Para_Dense8->Zo = -128;

    //第九层ReLU激活函数
    struct Layer_Para_base *Layer_Para_Base9 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_ReLU *Layer_Para_ReLU9 = OpenNNA_Malloc(sizeof(Layer_Para_ReLU));
    Layer_Para_Base9->Input_Fmap_Channel=1;
    Layer_Para_Base9->Input_Fmap_Row=1;
    Layer_Para_Base9->Input_Fmap_Col=64;
    Layer_Para_Base9->Output_Fmap_Channel=1;
    Layer_Para_Base9->Output_Fmap_Row=1;
    Layer_Para_Base9->Output_Fmap_Col=64;

    //第10层Dense 10
    struct Layer_Para_base *Layer_Para_Base10 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Dense *Layer_Para_Dense10 = OpenNNA_Malloc(sizeof(Layer_Para_Dense));
    Layer_Para_Base10->Input_Fmap_Channel=1;
    Layer_Para_Base10->Input_Fmap_Row=1;
    Layer_Para_Base10->Input_Fmap_Col=64;
    Layer_Para_Base10->Output_Fmap_Channel=1;
    Layer_Para_Base10->Output_Fmap_Row=1;
    Layer_Para_Base10->Output_Fmap_Col=10;

    Layer_Para_Dense10->units = 10;

    Layer_Para_Dense10->Si = 0.0777057483792305;
    Layer_Para_Dense10->Sw = 0.006086254492402077;
    Layer_Para_Dense10->Sb = 0.0004729369538836181;
    Layer_Para_Dense10->So = 0.309154212474823;

    Layer_Para_Dense10->Zi = -128;
    Layer_Para_Dense10->Zw = 0;
    Layer_Para_Dense10->Zb = 0;
    Layer_Para_Dense10->Zo = 6;

    //第11层Softmax激活函数
    struct Layer_Para_base *Layer_Para_Base11 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Softmax *Layer_Para_Softmax11 = OpenNNA_Malloc(sizeof(Layer_Para_Softmax));
    Layer_Para_Base11->Input_Fmap_Channel=1;
    Layer_Para_Base11->Input_Fmap_Row=1;
    Layer_Para_Base11->Input_Fmap_Col=10;
    Layer_Para_Base11->Output_Fmap_Channel=1;
    Layer_Para_Base11->Output_Fmap_Row=1;
    Layer_Para_Base11->Output_Fmap_Col=10;
    /*****************第3步:设置神经网络输入数据和输出数据**********************/
    Weights_t Conv2d_2_Weights[16][1][3][3]={
            {
                    {
                            {101, 16, -32, },
                            {-77, -127, -56, },
                            {9, 52, 101, },
                    },
            },

            {
                    {
                            {20, 97, 34, },
                            {-52, 29, 91, },
                            {-127, -77, 34, },
                    },
            },

            {
                    {
                            {43, 119, 100, },
                            {-96, -19, 7, },
                            {-127, -120, -89, },
                    },
            },

            {
                    {
                            {36, -127, -89, },
                            {74, -14, 50, },
                            {89, 124, 17, },
                    },
            },

            {
                    {
                            {-49, -110, -127, },
                            {12, 13, 18, },
                            {101, 60, 102, },
                    },
            },

            {
                    {
                            {-33, -19, 68, },
                            {-64, -78, 60, },
                            {-51, -127, 103, },
                    },
            },

            {
                    {
                            {-18, 17, 56, },
                            {118, 82, 127, },
                            {-62, -122, -103, },
                    },
            },

            {
                    {
                            {83, 127, -7, },
                            {66, 16, -105, },
                            {34, -113, -105, },
                    },
            },

            {
                    {
                            {118, 38, -78, },
                            {6, 108, 84, },
                            {-127, 22, 28, },
                    },
            },

            {
                    {
                            {25, -40, 50, },
                            {44, 127, 114, },
                            {-15, 50, 87, },
                    },
            },

            {
                    {
                            {41, 27, -127, },
                            {62, 22, -96, },
                            {53, 56, -40, },
                    },
            },

            {
                    {
                            {22, -127, 77, },
                            {-71, -76, 116, },
                            {57, 85, 59, },
                    },
            },

            {
                    {
                            {64, 23, 100, },
                            {14, 66, 9, },
                            {-118, -127, -118, },
                    },
            },

            {
                    {
                            {-127, -33, 36, },
                            {-4, 103, 46, },
                            {55, 40, -101, },
                    },
            },

            {
                    {
                            {-127, 14, 3, },
                            {-120, 35, 38, },
                            {-83, 13, 64, },
                    },
            },

            {
                    {
                            {-116, 23, 41, },
                            {1, 127, -6, },
                            {39, 6, -72, },
                    },
            },
    };
    Bias_t Conv2d_2_Bias[16]={
            -1515, -3154, 3679, -10106, 337, -1995, -6509, -1289, -40061, -24580, -1159, -16877, 2063, -8186, 1877, -10157,
            };

    Weights_t Conv2d_5_Weights[32][16][3][3]={
            {
                    {
                            {-11, 25, 54, },
                            {49, 81, -2, },
                            {16, 90, 127, },
                    },
                    {
                            {-83, 20, 24, },
                            {34, -97, -62, },
                            {17, -24, -42, },
                    },
                    {
                            {-67, 5, -45, },
                            {4, -59, 0, },
                            {55, 15, -12, },
                    },
                    {
                            {-12, -101, -53, },
                            {12, 8, 16, },
                            {-4, -22, 3, },
                    },
                    {
                            {-80, -46, 1, },
                            {35, 34, 21, },
                            {12, -43, -21, },
                    },
                    {
                            {-76, 6, 18, },
                            {-31, 11, -47, },
                            {5, -34, 40, },
                    },
                    {
                            {-12, -34, -63, },
                            {45, -11, 9, },
                            {-4, 26, -12, },
                    },
                    {
                            {45, 5, -53, },
                            {-34, -87, 57, },
                            {18, 39, 24, },
                    },
                    {
                            {2, -47, 30, },
                            {50, -30, -47, },
                            {17, -38, -55, },
                    },
                    {
                            {-12, -62, -20, },
                            {6, 34, 8, },
                            {-18, 3, -33, },
                    },
                    {
                            {16, -48, -68, },
                            {7, -28, 11, },
                            {10, -9, 19, },
                    },
                    {
                            {-46, -74, -10, },
                            {13, 31, 35, },
                            {-16, -20, -4, },
                    },
                    {
                            {-19, 52, -56, },
                            {25, -40, 50, },
                            {13, 8, -22, },
                    },
                    {
                            {-3, -53, -5, },
                            {-13, 42, 45, },
                            {-13, 1, -66, },
                    },
                    {
                            {-70, -10, 20, },
                            {-14, 6, 33, },
                            {-45, 2, -21, },
                    },
                    {
                            {30, -61, -9, },
                            {4, 43, 22, },
                            {4, 15, -64, },
                    },
            },

            {
                    {
                            {39, -69, -116, },
                            {44, -50, -25, },
                            {-26, 95, 41, },
                    },
                    {
                            {105, 82, -62, },
                            {20, 3, -80, },
                            {-60, -37, -96, },
                    },
                    {
                            {58, -66, -41, },
                            {-37, -46, -58, },
                            {-67, -15, -28, },
                    },
                    {
                            {-2, 49, 10, },
                            {3, -45, -55, },
                            {-17, -29, -41, },
                    },
                    {
                            {26, 11, -58, },
                            {12, -34, -127, },
                            {-33, -53, -18, },
                    },
                    {
                            {114, 67, -104, },
                            {20, 61, -50, },
                            {-51, -1, -10, },
                    },
                    {
                            {-40, 2, 25, },
                            {-16, 9, -17, },
                            {31, 7, -31, },
                    },
                    {
                            {-65, 33, -9, },
                            {-13, 36, 9, },
                            {88, 39, 31, },
                    },
                    {
                            {32, 51, 21, },
                            {-3, -28, -42, },
                            {-64, -34, -54, },
                    },
                    {
                            {-12, 13, -21, },
                            {21, 18, -54, },
                            {-11, -35, -62, },
                    },
                    {
                            {-73, 87, 9, },
                            {-65, 49, -7, },
                            {-18, -25, 20, },
                    },
                    {
                            {18, 31, -5, },
                            {60, -21, -45, },
                            {6, -56, -33, },
                    },
                    {
                            {-26, -106, -26, },
                            {-37, -44, -24, },
                            {-34, -15, -5, },
                    },
                    {
                            {-1, 48, -35, },
                            {26, 57, -39, },
                            {47, -20, -43, },
                    },
                    {
                            {54, 66, -37, },
                            {61, 75, -10, },
                            {32, 11, 18, },
                    },
                    {
                            {-30, 27, -53, },
                            {49, 72, -40, },
                            {52, 17, -74, },
                    },
            },

            {
                    {
                            {-57, -71, 74, },
                            {-15, 92, 22, },
                            {17, 16, 127, },
                    },
                    {
                            {28, 54, 58, },
                            {44, 26, -16, },
                            {-13, -85, -59, },
                    },
                    {
                            {10, 54, 43, },
                            {20, 15, -100, },
                            {-25, -14, -6, },
                    },
                    {
                            {13, 2, 18, },
                            {-28, 41, 35, },
                            {40, 16, -67, },
                    },
                    {
                            {47, -65, 56, },
                            {-29, 49, 55, },
                            {34, 28, -84, },
                    },
                    {
                            {46, 26, 35, },
                            {42, 37, -29, },
                            {-15, -63, -91, },
                    },
                    {
                            {-25, 36, -15, },
                            {9, -9, 20, },
                            {-45, 11, 20, },
                    },
                    {
                            {-53, -34, -34, },
                            {-43, -49, -6, },
                            {-36, 62, 73, },
                    },
                    {
                            {10, 14, 22, },
                            {-4, 2, -9, },
                            {-19, -37, -9, },
                    },
                    {
                            {12, -11, -23, },
                            {-17, -1, 40, },
                            {-6, -8, -39, },
                    },
                    {
                            {17, 21, 19, },
                            {39, -40, -49, },
                            {-38, -55, -19, },
                    },
                    {
                            {-33, -63, 5, },
                            {-51, 51, 71, },
                            {-5, 6, -46, },
                    },
                    {
                            {-2, 15, -15, },
                            {-3, -18, -36, },
                            {-1, 9, -9, },
                    },
                    {
                            {-36, -4, -57, },
                            {-76, 11, 39, },
                            {8, 62, 26, },
                    },
                    {
                            {51, -48, -25, },
                            {6, -21, -11, },
                            {-5, -34, -99, },
                    },
                    {
                            {-10, -4, -52, },
                            {-77, -47, 59, },
                            {4, 27, 61, },
                    },
            },

            {
                    {
                            {-14, 37, 47, },
                            {27, -3, 9, },
                            {-29, 10, -63, },
                    },
                    {
                            {-4, -4, -49, },
                            {2, 3, -7, },
                            {11, -4, 62, },
                    },
                    {
                            {-54, -76, -24, },
                            {-8, -7, -25, },
                            {46, 60, 10, },
                    },
                    {
                            {-11, 3, 35, },
                            {-17, -7, 66, },
                            {-49, -32, 44, },
                    },
                    {
                            {-35, -30, 32, },
                            {-21, 16, 21, },
                            {-21, -13, 3, },
                    },
                    {
                            {-11, 28, -10, },
                            {-23, 16, -38, },
                            {-49, 45, 22, },
                    },
                    {
                            {33, -7, 11, },
                            {17, 5, -27, },
                            {8, 14, -8, },
                    },
                    {
                            {10, 17, 81, },
                            {-62, -98, -8, },
                            {-41, -30, -127, },
                    },
                    {
                            {-3, -14, -35, },
                            {10, -17, -4, },
                            {-4, -21, 40, },
                    },
                    {
                            {32, -11, -12, },
                            {25, -3, -8, },
                            {-21, -33, 39, },
                    },
                    {
                            {-51, 25, 11, },
                            {-13, -27, 55, },
                            {-109, -40, 2, },
                    },
                    {
                            {1, -2, 20, },
                            {3, 11, -1, },
                            {-38, -7, 49, },
                    },
                    {
                            {-21, -40, 3, },
                            {-33, -35, -11, },
                            {0, 29, -66, },
                    },
                    {
                            {52, 22, 49, },
                            {-52, -28, 1, },
                            {-52, -22, -22, },
                    },
                    {
                            {13, -32, -9, },
                            {-12, -36, -60, },
                            {-29, -8, -29, },
                    },
                    {
                            {80, 29, 51, },
                            {10, -22, -7, },
                            {-22, -58, -27, },
                    },
            },

            {
                    {
                            {-32, -65, 42, },
                            {-127, -7, -12, },
                            {-28, 80, 26, },
                    },
                    {
                            {42, -50, 11, },
                            {-18, -124, -27, },
                            {-34, -25, -41, },
                    },
                    {
                            {-35, -37, 49, },
                            {-103, -102, 3, },
                            {-51, -62, 25, },
                    },
                    {
                            {31, 2, -19, },
                            {3, 27, -54, },
                            {-29, 16, 8, },
                    },
                    {
                            {17, 28, -66, },
                            {-35, -46, -76, },
                            {-70, -28, 10, },
                    },
                    {
                            {29, -121, -19, },
                            {8, -55, -59, },
                            {-24, 7, -29, },
                    },
                    {
                            {19, 25, -18, },
                            {16, 10, -31, },
                            {43, -33, -56, },
                    },
                    {
                            {-48, 19, 30, },
                            {1, 46, 9, },
                            {4, 45, 1, },
                    },
                    {
                            {34, 47, 20, },
                            {-10, 33, -4, },
                            {-6, -31, -36, },
                    },
                    {
                            {47, 1, -3, },
                            {19, -25, -59, },
                            {24, -38, -40, },
                    },
                    {
                            {-4, 3, 24, },
                            {26, 16, -34, },
                            {51, 13, 12, },
                    },
                    {
                            {7, -14, -70, },
                            {45, -9, -37, },
                            {-14, 37, -10, },
                    },
                    {
                            {-44, 26, -4, },
                            {-86, -36, 2, },
                            {-46, -9, -2, },
                    },
                    {
                            {75, 5, -73, },
                            {1, 3, -101, },
                            {39, -67, -14, },
                    },
                    {
                            {81, 2, -45, },
                            {65, -102, -53, },
                            {21, 10, -17, },
                    },
                    {
                            {80, -3, -56, },
                            {30, -22, -113, },
                            {43, -66, -66, },
                    },
            },

            {
                    {
                            {25, 74, 4, },
                            {-2, 5, 84, },
                            {-45, 14, 30, },
                    },
                    {
                            {-30, -13, -22, },
                            {35, 11, 1, },
                            {1, -46, -14, },
                    },
                    {
                            {-27, 0, -23, },
                            {70, 56, 11, },
                            {44, 17, -105, },
                    },
                    {
                            {-11, 28, -14, },
                            {16, 5, -16, },
                            {-119, -87, -11, },
                    },
                    {
                            {21, 17, 25, },
                            {9, 14, -29, },
                            {-61, -25, 29, },
                    },
                    {
                            {29, -6, -9, },
                            {1, 37, -6, },
                            {-49, -38, -9, },
                    },
                    {
                            {-36, -15, 21, },
                            {-7, -9, 19, },
                            {-57, -55, -78, },
                    },
                    {
                            {-17, 6, 27, },
                            {26, 10, 53, },
                            {-22, 37, -51, },
                    },
                    {
                            {-44, -31, -30, },
                            {30, -5, -36, },
                            {-73, -43, -4, },
                    },
                    {
                            {-7, 15, 24, },
                            {21, -23, -21, },
                            {-119, -61, -5, },
                    },
                    {
                            {42, -2, -52, },
                            {-17, 8, -15, },
                            {-108, -95, -39, },
                    },
                    {
                            {26, 11, 57, },
                            {-30, -6, -20, },
                            {-127, -29, 18, },
                    },
                    {
                            {-26, -4, 8, },
                            {43, 50, 49, },
                            {0, 6, -120, },
                    },
                    {
                            {19, 3, 53, },
                            {-3, 38, 47, },
                            {-103, -75, 32, },
                    },
                    {
                            {-22, 37, 25, },
                            {-34, -21, -50, },
                            {-31, -38, 46, },
                    },
                    {
                            {-7, -2, 36, },
                            {-56, 26, 32, },
                            {-68, -39, 37, },
                    },
            },

            {
                    {
                            {-66, -53, 26, },
                            {-52, 1, -6, },
                            {-24, -42, -1, },
                    },
                    {
                            {-1, -17, -9, },
                            {37, 3, -41, },
                            {38, 71, -26, },
                    },
                    {
                            {-20, -60, 5, },
                            {-40, -63, 40, },
                            {17, -15, -74, },
                    },
                    {
                            {31, 20, 26, },
                            {-78, -16, -8, },
                            {-90, -19, 30, },
                    },
                    {
                            {-24, 8, 9, },
                            {-95, -36, -35, },
                            {-63, -9, -2, },
                    },
                    {
                            {-28, -38, -71, },
                            {-20, 74, -31, },
                            {80, 127, 9, },
                    },
                    {
                            {-1, 46, 17, },
                            {-12, 2, 9, },
                            {-8, -11, -75, },
                    },
                    {
                            {-104, 29, 25, },
                            {-74, 2, 60, },
                            {-9, 22, 20, },
                    },
                    {
                            {-15, -23, 4, },
                            {13, -10, -46, },
                            {-35, -6, -36, },
                    },
                    {
                            {27, 26, -28, },
                            {-34, 12, -90, },
                            {7, 22, -60, },
                    },
                    {
                            {-86, 21, -50, },
                            {-119, 49, 45, },
                            {-25, 60, 76, },
                    },
                    {
                            {36, -8, -14, },
                            {-34, -40, -59, },
                            {-15, 23, -77, },
                    },
                    {
                            {-44, -65, 35, },
                            {-65, -30, 47, },
                            {-2, -52, -103, },
                    },
                    {
                            {20, 0, -17, },
                            {-52, 23, -16, },
                            {-70, 47, -22, },
                    },
                    {
                            {-26, 15, -8, },
                            {14, 4, -41, },
                            {35, 88, 17, },
                    },
                    {
                            {-31, 30, -23, },
                            {-57, -7, -32, },
                            {-38, 51, -10, },
                    },
            },

            {
                    {
                            {-5, -66, -2, },
                            {-104, -38, -15, },
                            {17, -24, -65, },
                    },
                    {
                            {48, 5, -32, },
                            {48, 41, -15, },
                            {-29, 26, 48, },
                    },
                    {
                            {35, -56, -25, },
                            {27, 29, -63, },
                            {18, 36, -14, },
                    },
                    {
                            {-19, -11, 29, },
                            {1, 5, 41, },
                            {4, -22, 35, },
                    },
                    {
                            {-31, -59, -24, },
                            {-38, -20, 7, },
                            {28, -32, 0, },
                    },
                    {
                            {21, -14, -48, },
                            {46, 14, -5, },
                            {-32, 37, 21, },
                    },
                    {
                            {-16, 33, 18, },
                            {16, 25, -20, },
                            {-29, 16, 3, },
                    },
                    {
                            {-102, -28, 29, },
                            {-66, -86, -38, },
                            {-64, -127, -68, },
                    },
                    {
                            {1, 1, 18, },
                            {7, 17, -4, },
                            {-25, 4, 54, },
                    },
                    {
                            {22, 7, -18, },
                            {6, 19, 21, },
                            {-22, 17, 26, },
                    },
                    {
                            {-47, 6, 31, },
                            {-42, -32, 45, },
                            {-57, -80, 35, },
                    },
                    {
                            {35, 28, -22, },
                            {14, 11, -1, },
                            {-20, -8, 22, },
                    },
                    {
                            {2, -37, -20, },
                            {20, -9, -77, },
                            {-4, 10, -52, },
                    },
                    {
                            {1, 7, 18, },
                            {-29, -45, 14, },
                            {-6, -41, -40, },
                    },
                    {
                            {51, -13, -39, },
                            {18, -4, -16, },
                            {-52, -21, -21, },
                    },
                    {
                            {32, 10, -16, },
                            {-12, -15, -3, },
                            {-18, -23, -20, },
                    },
            },

            {
                    {
                            {9, -11, 24, },
                            {-80, -38, 38, },
                            {-1, 11, 32, },
                    },
                    {
                            {-80, -77, -79, },
                            {-26, -17, 13, },
                            {-43, -18, 50, },
                    },
                    {
                            {-115, -56, -8, },
                            {-35, -46, -70, },
                            {-9, -6, 68, },
                    },
                    {
                            {19, 32, -11, },
                            {45, 28, 68, },
                            {-6, 0, -21, },
                    },
                    {
                            {44, 21, -6, },
                            {-2, 46, 27, },
                            {-93, -41, -57, },
                    },
                    {
                            {6, -97, -98, },
                            {-26, -33, -25, },
                            {-17, 1, -18, },
                    },
                    {
                            {-40, -14, -41, },
                            {42, 43, 32, },
                            {5, -9, 28, },
                    },
                    {
                            {-120, -37, -35, },
                            {10, -56, -59, },
                            {5, 11, 55, },
                    },
                    {
                            {-43, -12, -26, },
                            {-5, 41, 22, },
                            {-20, 21, 23, },
                    },
                    {
                            {-12, 5, -45, },
                            {35, 44, 43, },
                            {-6, -18, -5, },
                    },
                    {
                            {-46, -9, 18, },
                            {-18, -4, 43, },
                            {7, 14, -15, },
                    },
                    {
                            {13, 26, -20, },
                            {33, -22, 9, },
                            {-7, 3, -6, },
                    },
                    {
                            {-127, -30, -89, },
                            {-4, -25, -40, },
                            {-22, 10, 66, },
                    },
                    {
                            {47, -22, -28, },
                            {36, 10, -19, },
                            {-40, -21, 7, },
                    },
                    {
                            {-11, -63, -46, },
                            {-23, -56, -33, },
                            {-37, -58, -12, },
                    },
                    {
                            {30, -31, -32, },
                            {10, -3, 9, },
                            {-17, 4, -1, },
                    },
            },

            {
                    {
                            {-23, 54, 101, },
                            {34, 52, 48, },
                            {31, 86, 91, },
                    },
                    {
                            {-14, 1, -10, },
                            {-69, 22, 35, },
                            {-32, -46, -6, },
                    },
                    {
                            {-18, -8, -16, },
                            {-38, 52, 24, },
                            {-41, 54, 29, },
                    },
                    {
                            {-79, -27, 20, },
                            {-64, -14, 28, },
                            {-36, -43, -127, },
                    },
                    {
                            {-125, 9, 20, },
                            {-29, 9, 11, },
                            {2, -36, -50, },
                    },
                    {
                            {12, 53, -3, },
                            {10, 59, 23, },
                            {2, -18, -9, },
                    },
                    {
                            {19, -41, -46, },
                            {-61, -8, 39, },
                            {-11, -29, -33, },
                    },
                    {
                            {38, 1, 32, },
                            {-25, 30, 30, },
                            {-1, -11, -19, },
                    },
                    {
                            {-27, -9, -37, },
                            {-22, -30, 28, },
                            {-3, -80, -11, },
                    },
                    {
                            {-72, -45, -41, },
                            {-32, 21, -27, },
                            {-2, -80, -94, },
                    },
                    {
                            {25, -3, -6, },
                            {-18, 2, 33, },
                            {5, 47, -89, },
                    },
                    {
                            {-29, -35, 15, },
                            {-19, -32, -34, },
                            {-27, -48, -74, },
                    },
                    {
                            {5, -38, -29, },
                            {-60, 9, 22, },
                            {18, 33, 25, },
                    },
                    {
                            {-49, -9, 76, },
                            {-11, -2, 27, },
                            {-14, 5, -67, },
                    },
                    {
                            {-39, 50, 61, },
                            {-5, 31, 28, },
                            {34, -66, -42, },
                    },
                    {
                            {-6, -26, 48, },
                            {-38, 22, 6, },
                            {-4, -17, -33, },
                    },
            },

            {
                    {
                            {44, 68, 7, },
                            {-3, 24, 11, },
                            {13, -12, 19, },
                    },
                    {
                            {-50, -38, -49, },
                            {-18, -39, 0, },
                            {-6, -44, -22, },
                    },
                    {
                            {2, -51, -10, },
                            {-79, -19, 25, },
                            {-90, -68, 4, },
                    },
                    {
                            {-116, 2, -30, },
                            {-21, 0, -18, },
                            {12, -32, -19, },
                    },
                    {
                            {-54, 35, -11, },
                            {-25, 15, -21, },
                            {-5, -11, -49, },
                    },
                    {
                            {-60, 31, -25, },
                            {42, 27, -49, },
                            {39, -33, -13, },
                    },
                    {
                            {-33, -69, 13, },
                            {-127, 20, 10, },
                            {-41, 11, -26, },
                    },
                    {
                            {22, -37, 41, },
                            {-23, 51, 64, },
                            {-1, 62, 41, },
                    },
                    {
                            {-60, -23, -37, },
                            {-54, -30, 3, },
                            {-20, -18, -20, },
                    },
                    {
                            {-100, -23, 21, },
                            {-28, -26, -54, },
                            {-10, -17, -87, },
                    },
                    {
                            {-38, -111, -22, },
                            {-119, 29, 19, },
                            {-28, 28, -27, },
                    },
                    {
                            {-107, 12, 17, },
                            {8, 12, -67, },
                            {-3, -1, -47, },
                    },
                    {
                            {13, -28, 2, },
                            {-52, -17, 30, },
                            {-85, -27, -20, },
                    },
                    {
                            {-97, -32, 72, },
                            {-57, 75, -23, },
                            {16, 37, -18, },
                    },
                    {
                            {-36, 29, 34, },
                            {46, 20, -49, },
                            {88, -11, -51, },
                    },
                    {
                            {-120, -39, 56, },
                            {-65, 52, 3, },
                            {27, 1, -43, },
                    },
            },

            {
                    {
                            {39, 43, -36, },
                            {-28, -19, -36, },
                            {42, -12, -60, },
                    },
                    {
                            {-69, -44, 10, },
                            {86, 25, -34, },
                            {23, 42, 56, },
                    },
                    {
                            {-76, 4, 44, },
                            {79, -47, -36, },
                            {9, 15, -17, },
                    },
                    {
                            {46, 4, -47, },
                            {4, 51, 22, },
                            {-13, -33, 36, },
                    },
                    {
                            {61, 51, -16, },
                            {31, 51, 31, },
                            {-10, -25, 22, },
                    },
                    {
                            {-127, -20, -40, },
                            {-17, -36, -44, },
                            {3, 48, 9, },
                    },
                    {
                            {-17, 1, -55, },
                            {51, -8, -54, },
                            {-20, 28, -9, },
                    },
                    {
                            {-49, -24, -44, },
                            {-29, -53, -57, },
                            {10, -23, -46, },
                    },
                    {
                            {-21, -68, -44, },
                            {54, 33, -47, },
                            {-27, -10, 45, },
                    },
                    {
                            {-6, -43, -62, },
                            {16, -3, -22, },
                            {7, -3, 27, },
                    },
                    {
                            {11, -2, -52, },
                            {16, 28, 59, },
                            {-29, 14, 28, },
                    },
                    {
                            {23, -13, -42, },
                            {9, 16, -8, },
                            {12, -21, -30, },
                    },
                    {
                            {-23, 36, 18, },
                            {57, -42, -67, },
                            {-2, 28, -45, },
                    },
                    {
                            {18, -9, -46, },
                            {-15, -17, 11, },
                            {40, 12, -12, },
                    },
                    {
                            {-118, -55, -8, },
                            {-59, -2, -50, },
                            {6, 25, -23, },
                    },
                    {
                            {-11, -55, -44, },
                            {-33, -49, -36, },
                            {51, 8, -31, },
                    },
            },

            {
                    {
                            {66, 87, 15, },
                            {122, 36, 70, },
                            {86, 127, -11, },
                    },
                    {
                            {-41, 50, -2, },
                            {-37, -25, 24, },
                            {11, -3, 38, },
                    },
                    {
                            {-21, 7, -62, },
                            {-9, 57, -31, },
                            {50, 5, -24, },
                    },
                    {
                            {-56, 6, 13, },
                            {63, -2, -26, },
                            {-66, -41, -31, },
                    },
                    {
                            {-25, 30, 0, },
                            {56, 33, -18, },
                            {-14, -2, -42, },
                    },
                    {
                            {-28, 22, -42, },
                            {-40, -60, -31, },
                            {-75, -7, 26, },
                    },
                    {
                            {-38, -69, -21, },
                            {-5, 8, -15, },
                            {39, -15, 7, },
                    },
                    {
                            {56, -37, -24, },
                            {-47, 32, -10, },
                            {36, 37, -41, },
                    },
                    {
                            {-50, 30, -29, },
                            {-4, -18, 6, },
                            {-40, -63, 36, },
                    },
                    {
                            {-73, -13, -22, },
                            {4, 6, 19, },
                            {-43, -34, 19, },
                    },
                    {
                            {-47, -44, -22, },
                            {-30, -4, 27, },
                            {8, -52, -44, },
                    },
                    {
                            {-44, -6, 9, },
                            {30, 6, 4, },
                            {-34, -21, -42, },
                    },
                    {
                            {-42, -6, -77, },
                            {20, 52, 1, },
                            {17, 38, -16, },
                    },
                    {
                            {-2, -14, 31, },
                            {15, 78, -10, },
                            {9, -20, -16, },
                    },
                    {
                            {-32, -7, -4, },
                            {-53, -25, -17, },
                            {-37, -60, 9, },
                    },
                    {
                            {26, -11, -14, },
                            {38, 67, 0, },
                            {17, -23, 34, },
                    },
            },

            {
                    {
                            {-49, -23, 66, },
                            {-2, -44, -22, },
                            {-48, -63, -21, },
                    },
                    {
                            {21, 0, -76, },
                            {12, -11, -127, },
                            {5, -61, -49, },
                    },
                    {
                            {-50, -95, -49, },
                            {-53, -113, -25, },
                            {-116, -86, -46, },
                    },
                    {
                            {-17, -18, 1, },
                            {-55, 5, 9, },
                            {-18, 21, 10, },
                    },
                    {
                            {-21, -62, 5, },
                            {-24, -49, 19, },
                            {19, -42, 1, },
                    },
                    {
                            {-31, -26, -26, },
                            {36, -13, -61, },
                            {29, 12, -79, },
                    },
                    {
                            {-13, 34, 58, },
                            {-95, -19, 39, },
                            {-55, -7, 25, },
                    },
                    {
                            {-9, -63, 62, },
                            {-45, -10, 64, },
                            {-127, -81, -11, },
                    },
                    {
                            {-14, 6, -1, },
                            {-12, 16, -8, },
                            {-9, -4, -2, },
                    },
                    {
                            {29, 38, 55, },
                            {6, 19, 27, },
                            {33, 12, 0, },
                    },
                    {
                            {-16, -29, 11, },
                            {-54, -42, 14, },
                            {-89, 12, 22, },
                    },
                    {
                            {-18, -12, 52, },
                            {-2, 33, 34, },
                            {25, 3, 30, },
                    },
                    {
                            {-30, -30, -9, },
                            {-81, -104, 9, },
                            {-121, -120, -47, },
                    },
                    {
                            {6, 36, 77, },
                            {-62, -20, 12, },
                            {-24, 19, -28, },
                    },
                    {
                            {-2, 9, 9, },
                            {35, -3, -3, },
                            {44, 18, -14, },
                    },
                    {
                            {8, -3, 5, },
                            {-35, 22, 33, },
                            {6, 32, 13, },
                    },
            },

            {
                    {
                            {-47, -25, 40, },
                            {-50, 34, 31, },
                            {-5, 43, 46, },
                    },
                    {
                            {15, -33, -62, },
                            {-26, -27, 13, },
                            {-67, 26, 24, },
                    },
                    {
                            {-105, -87, -91, },
                            {-127, -71, -71, },
                            {-99, -17, -17, },
                    },
                    {
                            {8, -10, -48, },
                            {-15, 15, 23, },
                            {34, 54, 11, },
                    },
                    {
                            {2, -15, -3, },
                            {-21, -22, -6, },
                            {8, 45, 40, },
                    },
                    {
                            {11, 18, 36, },
                            {23, -41, 19, },
                            {-37, -43, 11, },
                    },
                    {
                            {-5, 37, -13, },
                            {-3, -6, -3, },
                            {14, 5, -5, },
                    },
                    {
                            {-35, 30, 38, },
                            {-1, 32, 2, },
                            {4, -26, -12, },
                    },
                    {
                            {21, 11, -23, },
                            {-2, -1, -9, },
                            {-33, 15, 23, },
                    },
                    {
                            {20, -14, -38, },
                            {6, -48, 4, },
                            {10, -21, 30, },
                    },
                    {
                            {-9, 35, 13, },
                            {1, 13, -38, },
                            {30, 22, -28, },
                    },
                    {
                            {42, -5, -55, },
                            {28, 19, 35, },
                            {17, 31, 17, },
                    },
                    {
                            {-90, -34, -10, },
                            {-68, -54, -71, },
                            {-63, -17, -2, },
                    },
                    {
                            {44, 22, -40, },
                            {28, -43, 7, },
                            {-9, -25, 12, },
                    },
                    {
                            {42, 40, 44, },
                            {15, -51, 17, },
                            {5, -2, -34, },
                    },
                    {
                            {37, 44, -16, },
                            {35, -2, 7, },
                            {-9, -21, 7, },
                    },
            },

            {
                    {
                            {93, -3, -24, },
                            {27, -23, -29, },
                            {-61, 22, -68, },
                    },
                    {
                            {-13, -33, -76, },
                            {-6, 8, 69, },
                            {-81, 9, 60, },
                    },
                    {
                            {-76, -66, -73, },
                            {38, 28, -6, },
                            {-32, 19, 69, },
                    },
                    {
                            {31, 34, 8, },
                            {-17, -84, 4, },
                            {-16, -83, -71, },
                    },
                    {
                            {45, 35, -35, },
                            {13, -47, -4, },
                            {-20, -46, -127, },
                    },
                    {
                            {43, -13, -35, },
                            {-7, 11, 47, },
                            {-58, 25, 46, },
                    },
                    {
                            {-46, -7, -29, },
                            {31, 1, -53, },
                            {-14, -29, 48, },
                    },
                    {
                            {-37, -50, -61, },
                            {67, 14, -97, },
                            {-5, -44, -4, },
                    },
                    {
                            {-60, -23, 19, },
                            {-32, 18, 30, },
                            {-22, -61, 28, },
                    },
                    {
                            {37, 0, -22, },
                            {-2, -20, 37, },
                            {-69, -57, 15, },
                    },
                    {
                            {12, -15, -3, },
                            {-23, 14, -9, },
                            {33, 36, 30, },
                    },
                    {
                            {53, -11, -15, },
                            {-6, -38, -17, },
                            {-37, -15, -34, },
                    },
                    {
                            {-12, -39, -46, },
                            {48, 34, -49, },
                            {-16, -22, 49, },
                    },
                    {
                            {47, 56, 19, },
                            {21, 7, -18, },
                            {-16, -75, -7, },
                    },
                    {
                            {29, -5, -45, },
                            {-23, 5, -39, },
                            {-82, -28, 19, },
                    },
                    {
                            {-13, 39, 7, },
                            {33, -13, -16, },
                            {-59, -63, 55, },
                    },
            },

            {
                    {
                            {19, 68, 127, },
                            {-52, -19, -78, },
                            {-30, 44, 43, },
                    },
                    {
                            {5, 11, -37, },
                            {43, 26, 59, },
                            {-65, 4, 29, },
                    },
                    {
                            {37, 14, 27, },
                            {75, 22, 51, },
                            {-11, 14, 20, },
                    },
                    {
                            {13, -12, 27, },
                            {-12, 13, 40, },
                            {-30, -52, -59, },
                    },
                    {
                            {14, 23, 18, },
                            {-40, 7, 71, },
                            {-5, 0, -53, },
                    },
                    {
                            {14, -58, -45, },
                            {3, -10, 3, },
                            {-5, 32, 0, },
                    },
                    {
                            {25, 20, -19, },
                            {12, 18, 31, },
                            {-15, -46, 7, },
                    },
                    {
                            {-29, -77, -73, },
                            {4, -52, -76, },
                            {-20, 34, 29, },
                    },
                    {
                            {12, 1, -17, },
                            {14, 14, -6, },
                            {-70, -32, -18, },
                    },
                    {
                            {-7, 19, -16, },
                            {-37, -1, 23, },
                            {-58, -57, -6, },
                    },
                    {
                            {-23, 25, -8, },
                            {-64, -29, -50, },
                            {-36, -24, -49, },
                    },
                    {
                            {0, 7, 33, },
                            {-20, -30, 27, },
                            {-2, 3, 19, },
                    },
                    {
                            {32, -47, 2, },
                            {15, 46, 36, },
                            {-24, 12, 85, },
                    },
                    {
                            {-10, 5, 9, },
                            {-46, -21, 16, },
                            {-23, -46, -21, },
                    },
                    {
                            {-26, -40, -93, },
                            {-33, -79, -83, },
                            {-27, -17, 37, },
                    },
                    {
                            {2, -10, 10, },
                            {3, 14, -49, },
                            {24, -27, 12, },
                    },
            },

            {
                    {
                            {-35, -40, 12, },
                            {6, 61, 43, },
                            {49, 11, -5, },
                    },
                    {
                            {49, 64, 30, },
                            {-86, -79, -54, },
                            {-41, 0, 63, },
                    },
                    {
                            {37, 55, 90, },
                            {25, 79, 35, },
                            {-121, -46, 39, },
                    },
                    {
                            {-93, -65, -61, },
                            {0, 57, -40, },
                            {19, 15, 30, },
                    },
                    {
                            {-127, -118, -97, },
                            {51, 49, 18, },
                            {-6, 47, 94, },
                    },
                    {
                            {28, 4, -24, },
                            {-41, -85, -75, },
                            {-6, -9, -42, },
                    },
                    {
                            {-32, 27, 59, },
                            {-118, -82, -89, },
                            {41, 13, -8, },
                    },
                    {
                            {-32, 28, 119, },
                            {-75, -66, -56, },
                            {-7, -62, -65, },
                    },
                    {
                            {14, 0, 0, },
                            {-111, -111, -77, },
                            {-30, 12, 49, },
                    },
                    {
                            {-54, 13, 12, },
                            {-43, -66, -47, },
                            {4, 47, 20, },
                    },
                    {
                            {-105, -60, -37, },
                            {-126, -110, -64, },
                            {-67, -6, 69, },
                    },
                    {
                            {-60, 12, -11, },
                            {-24, -57, -50, },
                            {14, 24, 30, },
                    },
                    {
                            {57, 85, 117, },
                            {10, 15, -28, },
                            {-81, -16, 22, },
                    },
                    {
                            {-97, -48, 44, },
                            {-30, 2, 0, },
                            {83, -5, 4, },
                    },
                    {
                            {-55, -20, -46, },
                            {13, -63, -21, },
                            {59, 13, -17, },
                    },
                    {
                            {-73, 30, 52, },
                            {-47, -50, -79, },
                            {58, -22, -5, },
                    },
            },

            {
                    {
                            {-41, 13, -5, },
                            {-14, 11, -40, },
                            {8, 17, -61, },
                    },
                    {
                            {-13, 9, 38, },
                            {-67, -21, 55, },
                            {-60, 11, 32, },
                    },
                    {
                            {-22, -1, -50, },
                            {-13, -59, -127, },
                            {-4, -30, -84, },
                    },
                    {
                            {32, -46, -12, },
                            {6, -50, -26, },
                            {-32, -12, -10, },
                    },
                    {
                            {1, -53, -32, },
                            {14, -24, -14, },
                            {-63, -3, -26, },
                    },
                    {
                            {-35, 107, 74, },
                            {-19, 7, 54, },
                            {-74, 34, 38, },
                    },
                    {
                            {-19, -15, -21, },
                            {-1, -66, 6, },
                            {51, -13, 4, },
                    },
                    {
                            {15, 32, -25, },
                            {26, -21, -48, },
                            {105, 12, -54, },
                    },
                    {
                            {19, -9, 47, },
                            {42, -33, 15, },
                            {-42, -19, 6, },
                    },
                    {
                            {-17, -5, 29, },
                            {13, -16, 32, },
                            {-43, -28, 33, },
                    },
                    {
                            {70, 19, -45, },
                            {43, 7, -13, },
                            {41, -33, 7, },
                    },
                    {
                            {-8, 9, 68, },
                            {-50, -49, 35, },
                            {-49, -16, 27, },
                    },
                    {
                            {-30, -8, -77, },
                            {-42, -31, -120, },
                            {40, -20, -64, },
                    },
                    {
                            {20, -39, 8, },
                            {1, -44, 18, },
                            {-26, -58, -15, },
                    },
                    {
                            {-55, 98, 90, },
                            {-63, 34, 14, },
                            {-58, 6, 21, },
                    },
                    {
                            {-18, -25, 33, },
                            {14, -46, 20, },
                            {-34, -62, 2, },
                    },
            },

            {
                    {
                            {1, 10, -18, },
                            {-57, -73, -41, },
                            {-9, -56, -52, },
                    },
                    {
                            {46, 76, -6, },
                            {-39, 29, 8, },
                            {-76, 32, 63, },
                    },
                    {
                            {21, 24, -82, },
                            {-55, -33, -41, },
                            {-8, 11, -40, },
                    },
                    {
                            {-61, -45, 19, },
                            {26, -64, 9, },
                            {-23, -31, -5, },
                    },
                    {
                            {-93, -103, -51, },
                            {5, -101, -7, },
                            {-12, -60, -49, },
                    },
                    {
                            {58, 62, 31, },
                            {-10, 63, 32, },
                            {-27, 43, 53, },
                    },
                    {
                            {34, 9, -19, },
                            {-3, 24, -14, },
                            {30, -1, -21, },
                    },
                    {
                            {11, -23, -7, },
                            {-9, -127, -25, },
                            {56, -41, -78, },
                    },
                    {
                            {-4, 25, 9, },
                            {-70, 46, -2, },
                            {-26, -10, 11, },
                    },
                    {
                            {-14, 6, 32, },
                            {-56, 29, 18, },
                            {-65, -20, 20, },
                    },
                    {
                            {-3, 46, 54, },
                            {31, -62, 64, },
                            {21, -68, 22, },
                    },
                    {
                            {-19, -18, -19, },
                            {-16, 7, 12, },
                            {-52, 3, 1, },
                    },
                    {
                            {34, -26, -120, },
                            {-16, 5, -43, },
                            {10, -44, -63, },
                    },
                    {
                            {6, -31, -15, },
                            {4, -10, -50, },
                            {10, -37, -53, },
                    },
                    {
                            {-17, 19, -19, },
                            {-41, 16, -1, },
                            {-65, 25, 36, },
                    },
                    {
                            {-14, 29, -8, },
                            {14, 25, -38, },
                            {-5, -11, -14, },
                    },
            },

            {
                    {
                            {-58, -3, 39, },
                            {-43, -37, 18, },
                            {-12, -121, -76, },
                    },
                    {
                            {54, 18, 0, },
                            {49, 63, 17, },
                            {-21, -12, -35, },
                    },
                    {
                            {52, 28, 20, },
                            {18, 19, 26, },
                            {-89, -11, 87, },
                    },
                    {
                            {21, 29, 25, },
                            {-30, -37, 11, },
                            {49, -4, -81, },
                    },
                    {
                            {-24, -14, 19, },
                            {-87, -106, 20, },
                            {12, 1, -110, },
                    },
                    {
                            {14, 24, -60, },
                            {-6, 31, -73, },
                            {-52, -14, -61, },
                    },
                    {
                            {58, 27, -3, },
                            {-31, 20, 9, },
                            {-63, -43, 12, },
                    },
                    {
                            {0, -39, 23, },
                            {-1, -27, 30, },
                            {2, -31, 36, },
                    },
                    {
                            {28, 1, -9, },
                            {-29, 46, 28, },
                            {-56, -49, -78, },
                    },
                    {
                            {25, 33, 22, },
                            {-33, 11, 0, },
                            {21, -89, -113, },
                    },
                    {
                            {38, 41, -7, },
                            {18, -15, -33, },
                            {23, 43, -50, },
                    },
                    {
                            {-28, 23, 7, },
                            {-57, -4, -52, },
                            {14, -53, -111, },
                    },
                    {
                            {36, -13, 21, },
                            {11, 29, 25, },
                            {-115, -34, 65, },
                    },
                    {
                            {17, -31, 28, },
                            {-26, -78, -40, },
                            {-11, -43, -127, },
                    },
                    {
                            {1, -41, -21, },
                            {-10, -23, -9, },
                            {13, -61, -111, },
                    },
                    {
                            {21, -36, -7, },
                            {-3, -23, -30, },
                            {-16, -70, -86, },
                    },
            },

            {
                    {
                            {99, -24, -104, },
                            {-2, 23, 2, },
                            {62, 71, 39, },
                    },
                    {
                            {1, -44, -36, },
                            {-50, -59, 32, },
                            {27, 5, -15, },
                    },
                    {
                            {36, -89, -51, },
                            {44, -29, 31, },
                            {75, 59, -43, },
                    },
                    {
                            {20, -1, -10, },
                            {35, -13, -80, },
                            {-103, 30, -64, },
                    },
                    {
                            {42, -44, -61, },
                            {8, -52, -111, },
                            {-88, 39, -46, },
                    },
                    {
                            {13, -37, -75, },
                            {-26, -60, 33, },
                            {-5, -29, 18, },
                    },
                    {
                            {-114, -6, 54, },
                            {71, 42, 31, },
                            {25, -73, -67, },
                    },
                    {
                            {-44, -99, 40, },
                            {-24, -5, 60, },
                            {9, 51, -24, },
                    },
                    {
                            {-7, 6, 55, },
                            {0, -22, -14, },
                            {-13, -51, -41, },
                    },
                    {
                            {-24, 40, 71, },
                            {36, 27, -15, },
                            {-42, -52, -11, },
                    },
                    {
                            {-8, -108, -7, },
                            {-2, -50, 39, },
                            {-32, -8, -14, },
                    },
                    {
                            {57, 43, 2, },
                            {4, 33, -58, },
                            {-71, 29, -20, },
                    },
                    {
                            {-13, -127, -13, },
                            {47, 39, 37, },
                            {45, -18, -45, },
                    },
                    {
                            {-6, 9, 5, },
                            {-13, 66, 24, },
                            {-116, -66, -57, },
                    },
                    {
                            {-16, -46, 9, },
                            {-11, -86, -57, },
                            {-88, -26, 42, },
                    },
                    {
                            {-22, 32, 2, },
                            {16, 52, -2, },
                            {-50, -73, -26, },
                    },
            },

            {
                    {
                            {-7, -15, -47, },
                            {-25, -52, 12, },
                            {-127, -44, -3, },
                    },
                    {
                            {13, -13, -54, },
                            {-31, -44, -41, },
                            {-24, -36, -1, },
                    },
                    {
                            {-49, -66, -43, },
                            {-92, -116, -28, },
                            {-44, -50, 15, },
                    },
                    {
                            {-15, 18, 19, },
                            {8, 30, 1, },
                            {1, 35, -10, },
                    },
                    {
                            {-22, 22, 0, },
                            {-17, 24, -11, },
                            {-28, -23, -1, },
                    },
                    {
                            {-15, -31, -13, },
                            {-31, -46, -17, },
                            {-19, -32, 23, },
                    },
                    {
                            {-20, 3, 12, },
                            {-26, 8, 15, },
                            {15, 22, 17, },
                    },
                    {
                            {-72, -6, 22, },
                            {-110, -7, 41, },
                            {-53, 16, 22, },
                    },
                    {
                            {12, 15, 19, },
                            {12, 9, -20, },
                            {16, 0, 8, },
                    },
                    {
                            {16, 16, 3, },
                            {16, 26, -6, },
                            {11, 36, 16, },
                    },
                    {
                            {-39, 1, 42, },
                            {-80, 21, 15, },
                            {-56, 22, 8, },
                    },
                    {
                            {11, 4, -8, },
                            {9, 9, -8, },
                            {4, 19, -3, },
                    },
                    {
                            {-96, -19, -19, },
                            {-91, -57, -48, },
                            {-41, -32, 21, },
                    },
                    {
                            {21, 22, 17, },
                            {26, -14, -23, },
                            {-4, 4, -24, },
                    },
                    {
                            {7, -16, 0, },
                            {5, -31, -34, },
                            {-22, -12, -48, },
                    },
                    {
                            {12, 8, 9, },
                            {-1, 9, 1, },
                            {-32, 7, -37, },
                    },
            },

            {
                    {
                            {-90, 28, 41, },
                            {-11, 17, -13, },
                            {25, -21, 0, },
                    },
                    {
                            {-62, -34, -2, },
                            {-6, 9, -52, },
                            {-2, -2, -28, },
                    },
                    {
                            {-11, -39, -82, },
                            {-6, -127, -69, },
                            {-29, -90, -53, },
                    },
                    {
                            {-31, -47, -12, },
                            {-38, 15, -1, },
                            {-5, -24, -5, },
                    },
                    {
                            {-60, 16, 13, },
                            {-21, 1, -2, },
                            {4, -7, -34, },
                    },
                    {
                            {-81, 22, 30, },
                            {-8, 26, -12, },
                            {18, 30, -10, },
                    },
                    {
                            {-25, -72, 0, },
                            {-58, -30, 16, },
                            {-14, -18, 12, },
                    },
                    {
                            {-73, -30, 3, },
                            {-52, -26, 19, },
                            {-25, -23, 31, },
                    },
                    {
                            {-25, -36, 6, },
                            {-35, 6, -42, },
                            {-14, 11, -11, },
                    },
                    {
                            {-39, -48, 1, },
                            {-58, 29, 25, },
                            {12, 20, -2, },
                    },
                    {
                            {-48, -70, -25, },
                            {-34, -37, -8, },
                            {-2, -16, 27, },
                    },
                    {
                            {-47, -17, 35, },
                            {-40, 30, 11, },
                            {8, 14, 0, },
                    },
                    {
                            {-22, -21, -64, },
                            {-9, -110, -8, },
                            {-2, -85, -46, },
                    },
                    {
                            {-29, -50, 54, },
                            {-40, 4, 54, },
                            {19, 33, 6, },
                    },
                    {
                            {-37, 5, 34, },
                            {-27, 23, 29, },
                            {18, 19, 12, },
                    },
                    {
                            {-23, -73, 21, },
                            {-44, -11, 39, },
                            {-1, 29, -12, },
                    },
            },

            {
                    {
                            {6, 32, -51, },
                            {-19, 53, 26, },
                            {-33, 42, 33, },
                    },
                    {
                            {46, -25, 24, },
                            {84, 20, 22, },
                            {-93, -58, -66, },
                    },
                    {
                            {-10, 28, 61, },
                            {59, 65, -27, },
                            {-71, -21, -127, },
                    },
                    {
                            {49, 39, 25, },
                            {-85, -63, -32, },
                            {-15, -32, 24, },
                    },
                    {
                            {-7, 0, -2, },
                            {-92, -70, -72, },
                            {50, 56, -2, },
                    },
                    {
                            {68, -54, 4, },
                            {48, 56, -11, },
                            {-10, 55, 44, },
                    },
                    {
                            {26, -24, 16, },
                            {39, 50, 32, },
                            {-57, -44, -4, },
                    },
                    {
                            {-18, -45, -6, },
                            {-32, 42, 66, },
                            {-21, 47, 55, },
                    },
                    {
                            {9, 15, -8, },
                            {14, 31, -14, },
                            {-34, -54, 23, },
                    },
                    {
                            {50, 32, 60, },
                            {-42, -32, -47, },
                            {-42, -15, 12, },
                    },
                    {
                            {99, 34, -27, },
                            {-21, -58, -95, },
                            {22, -33, -51, },
                    },
                    {
                            {17, -7, 54, },
                            {-26, -16, -3, },
                            {1, 9, 31, },
                    },
                    {
                            {-39, -52, 49, },
                            {52, 77, 63, },
                            {-60, -18, -69, },
                    },
                    {
                            {-24, 31, 37, },
                            {-53, -33, -30, },
                            {1, 0, 43, },
                    },
                    {
                            {3, 3, -114, },
                            {9, -88, -43, },
                            {-13, 2, 75, },
                    },
                    {
                            {9, -10, 3, },
                            {-26, -30, -62, },
                            {-20, -7, 42, },
                    },
            },

            {
                    {
                            {-26, 34, 43, },
                            {71, 65, -85, },
                            {-29, 68, 59, },
                    },
                    {
                            {31, 65, 51, },
                            {15, -73, -57, },
                            {-42, -57, 46, },
                    },
                    {
                            {50, 43, -84, },
                            {1, -101, -45, },
                            {-96, -4, -7, },
                    },
                    {
                            {57, 6, 39, },
                            {33, 12, 13, },
                            {-19, 5, 6, },
                    },
                    {
                            {75, 11, 51, },
                            {19, 35, -44, },
                            {-21, -76, -40, },
                    },
                    {
                            {32, 28, 43, },
                            {18, -7, -113, },
                            {-30, -31, -50, },
                    },
                    {
                            {-10, 48, -22, },
                            {-12, -5, 63, },
                            {4, 13, -6, },
                    },
                    {
                            {-33, -35, -82, },
                            {-59, -50, -14, },
                            {-99, 14, 26, },
                    },
                    {
                            {51, 7, 80, },
                            {6, -35, 21, },
                            {-14, -9, -5, },
                    },
                    {
                            {-29, -6, 28, },
                            {-2, 43, 55, },
                            {39, -15, 39, },
                    },
                    {
                            {-77, -8, 9, },
                            {-82, -127, -16, },
                            {7, -23, 7, },
                    },
                    {
                            {-9, 22, 12, },
                            {2, 66, 25, },
                            {36, 38, 12, },
                    },
                    {
                            {51, 36, -102, },
                            {-27, -63, 1, },
                            {-103, 26, -17, },
                    },
                    {
                            {-43, -37, -11, },
                            {44, 102, 71, },
                            {42, 28, 27, },
                    },
                    {
                            {-69, -62, -20, },
                            {23, 28, -42, },
                            {-17, -46, -99, },
                    },
                    {
                            {-45, -48, 17, },
                            {-24, 82, 68, },
                            {56, 56, 11, },
                    },
            },

            {
                    {
                            {-20, 25, 12, },
                            {16, -14, -31, },
                            {27, 52, -23, },
                    },
                    {
                            {7, 30, 7, },
                            {-54, -12, 38, },
                            {-33, -83, -125, },
                    },
                    {
                            {-71, 12, 27, },
                            {-63, 13, 11, },
                            {-71, -60, -57, },
                    },
                    {
                            {9, -16, 10, },
                            {24, -33, -102, },
                            {50, 10, 58, },
                    },
                    {
                            {23, 6, -13, },
                            {-65, -62, -103, },
                            {-4, 34, 52, },
                    },
                    {
                            {-108, -10, 11, },
                            {-55, -56, -23, },
                            {26, -12, -127, },
                    },
                    {
                            {34, 8, 0, },
                            {10, -3, -21, },
                            {-13, -33, -61, },
                    },
                    {
                            {1, 25, 23, },
                            {44, 22, -23, },
                            {-21, -10, -97, },
                    },
                    {
                            {3, 10, 52, },
                            {-64, -4, -29, },
                            {64, -40, -57, },
                    },
                    {
                            {7, -17, 18, },
                            {-4, -57, -72, },
                            {8, -10, -37, },
                    },
                    {
                            {10, 25, 10, },
                            {65, -19, -38, },
                            {28, -10, 26, },
                    },
                    {
                            {1, 5, -16, },
                            {-18, -50, -59, },
                            {11, 16, -11, },
                    },
                    {
                            {-26, 33, -6, },
                            {-56, -15, 4, },
                            {-56, -29, -59, },
                    },
                    {
                            {56, -6, -6, },
                            {56, -60, -89, },
                            {2, -25, -11, },
                    },
                    {
                            {2, -96, -15, },
                            {-16, -93, -86, },
                            {-57, -65, -112, },
                    },
                    {
                            {83, -33, 16, },
                            {21, -55, -50, },
                            {-23, -49, -55, },
                    },
            },

            {
                    {
                            {-28, -19, 6, },
                            {22, 33, 7, },
                            {-7, 24, 2, },
                    },
                    {
                            {-12, 16, 20, },
                            {-6, -83, -32, },
                            {-28, -1, 13, },
                    },
                    {
                            {-11, 55, 39, },
                            {-41, -50, -33, },
                            {-20, -7, 39, },
                    },
                    {
                            {3, 10, -14, },
                            {4, 29, 23, },
                            {26, 16, -7, },
                    },
                    {
                            {3, -13, 1, },
                            {32, 24, 27, },
                            {33, 14, -14, },
                    },
                    {
                            {-26, -5, -13, },
                            {-26, -11, 16, },
                            {-43, -39, -32, },
                    },
                    {
                            {-62, 6, 24, },
                            {-17, 27, -5, },
                            {20, 39, 56, },
                    },
                    {
                            {-72, -73, -19, },
                            {-67, -127, -79, },
                            {10, 11, -10, },
                    },
                    {
                            {-36, -32, 8, },
                            {-19, 4, 18, },
                            {-17, -10, 28, },
                    },
                    {
                            {-33, -3, 12, },
                            {5, -8, 40, },
                            {-9, 15, 29, },
                    },
                    {
                            {-12, -15, 16, },
                            {-42, -55, -21, },
                            {-55, -51, -47, },
                    },
                    {
                            {-17, 9, -32, },
                            {28, 2, 23, },
                            {32, 1, 21, },
                    },
                    {
                            {-33, 29, 10, },
                            {-25, -72, -40, },
                            {27, 15, 17, },
                    },
                    {
                            {4, -33, -35, },
                            {-40, -2, 7, },
                            {35, 36, 29, },
                    },
                    {
                            {-24, -4, 9, },
                            {10, -7, 7, },
                            {-14, -24, -48, },
                    },
                    {
                            {-14, -40, -22, },
                            {-15, -23, 1, },
                            {9, 26, 43, },
                    },
            },

            {
                    {
                            {7, 57, 36, },
                            {-25, -17, 6, },
                            {-116, -77, 32, },
                    },
                    {
                            {8, -77, 55, },
                            {52, -19, -28, },
                            {69, 50, -77, },
                    },
                    {
                            {-36, 15, 27, },
                            {-7, -109, -23, },
                            {-12, -33, 27, },
                    },
                    {
                            {23, -18, -73, },
                            {4, 34, -9, },
                            {-55, 23, 39, },
                    },
                    {
                            {17, -15, -11, },
                            {13, 49, 23, },
                            {-81, -3, 33, },
                    },
                    {
                            {10, 15, 40, },
                            {75, -24, 15, },
                            {49, -28, -48, },
                    },
                    {
                            {-27, -24, -42, },
                            {3, -38, -76, },
                            {1, 13, -2, },
                    },
                    {
                            {-34, 14, -19, },
                            {-50, 10, -7, },
                            {-107, -89, -7, },
                    },
                    {
                            {-6, -52, 10, },
                            {46, -10, -42, },
                            {-14, 10, -64, },
                    },
                    {
                            {-9, -42, -51, },
                            {27, -12, -67, },
                            {0, 32, 3, },
                    },
                    {
                            {21, 26, -50, },
                            {44, 51, 27, },
                            {-15, 50, 31, },
                    },
                    {
                            {-12, -62, -36, },
                            {-1, 10, 18, },
                            {-6, 5, 23, },
                    },
                    {
                            {-69, -9, 12, },
                            {-15, -127, -78, },
                            {-66, -72, -32, },
                    },
                    {
                            {-35, 3, 13, },
                            {-15, 12, 28, },
                            {-49, -13, 44, },
                    },
                    {
                            {-22, -3, 13, },
                            {51, 12, 9, },
                            {63, 16, -60, },
                    },
                    {
                            {-50, 15, 7, },
                            {-21, 37, 40, },
                            {-42, -42, 46, },
                    },
            },

            {
                    {
                            {15, 48, 34, },
                            {-17, 12, 122, },
                            {-127, -116, -36, },
                    },
                    {
                            {-15, -36, 21, },
                            {19, -8, -30, },
                            {-23, 63, 70, },
                    },
                    {
                            {-68, -63, -20, },
                            {-78, -80, -45, },
                            {-44, 48, 58, },
                    },
                    {
                            {10, -19, -41, },
                            {29, 13, 48, },
                            {4, 8, 68, },
                    },
                    {
                            {-13, -3, -12, },
                            {7, 7, 55, },
                            {-57, -4, 50, },
                    },
                    {
                            {2, 4, 2, },
                            {23, 13, -26, },
                            {-25, 39, -50, },
                    },
                    {
                            {-17, 9, 64, },
                            {5, 6, -25, },
                            {-2, 5, -15, },
                    },
                    {
                            {54, 47, 92, },
                            {4, -5, -1, },
                            {-63, -66, -65, },
                    },
                    {
                            {-11, -29, -5, },
                            {8, -16, 5, },
                            {1, 14, 48, },
                    },
                    {
                            {-27, 20, 8, },
                            {20, -16, -15, },
                            {7, 18, 31, },
                    },
                    {
                            {-24, -19, -20, },
                            {27, 32, -2, },
                            {42, 8, -16, },
                    },
                    {
                            {12, 41, 11, },
                            {28, 9, 17, },
                            {-20, -33, 49, },
                    },
                    {
                            {-40, -31, 51, },
                            {-73, -94, -29, },
                            {-43, 15, 19, },
                    },
                    {
                            {11, 76, 48, },
                            {17, 14, 16, },
                            {-62, -42, 49, },
                    },
                    {
                            {-12, 4, -55, },
                            {-14, -25, -95, },
                            {-12, -24, -79, },
                    },
                    {
                            {-17, 35, 27, },
                            {10, 49, -23, },
                            {-21, -46, -12, },
                    },
            },

            {
                    {
                            {-51, -44, -56, },
                            {2, 47, 46, },
                            {53, 94, 31, },
                    },
                    {
                            {15, 37, -33, },
                            {19, -50, -55, },
                            {-24, -78, 1, },
                    },
                    {
                            {-38, -14, -25, },
                            {32, 15, -35, },
                            {95, 0, -59, },
                    },
                    {
                            {9, -5, -20, },
                            {3, -12, -96, },
                            {-112, -127, 23, },
                    },
                    {
                            {-10, -59, -78, },
                            {2, -67, -60, },
                            {-82, -23, 28, },
                    },
                    {
                            {67, 109, -5, },
                            {46, 17, -39, },
                            {-88, -26, 0, },
                    },
                    {
                            {-20, -5, 2, },
                            {39, 28, -41, },
                            {4, -30, -38, },
                    },
                    {
                            {-20, 20, 57, },
                            {24, 39, 25, },
                            {36, 25, -80, },
                    },
                    {
                            {-3, 27, -19, },
                            {36, -24, -55, },
                            {3, -68, -33, },
                    },
                    {
                            {0, 18, -5, },
                            {-4, -17, -79, },
                            {-76, -110, -6, },
                    },
                    {
                            {13, 47, 22, },
                            {17, 35, -5, },
                            {-49, -46, -93, },
                    },
                    {
                            {16, -11, -41, },
                            {4, -37, -27, },
                            {-91, -56, 1, },
                    },
                    {
                            {-23, -26, 9, },
                            {49, 15, -45, },
                            {75, 6, -42, },
                    },
                    {
                            {1, 14, -38, },
                            {34, 20, -103, },
                            {-65, -81, 39, },
                    },
                    {
                            {10, 46, 21, },
                            {-21, 13, 19, },
                            {-90, -6, 58, },
                    },
                    {
                            {31, -14, -14, },
                            {12, 31, -77, },
                            {-49, -96, -5, },
                    },
            },

            {
                    {
                            {-19, 40, 20, },
                            {-16, -36, 16, },
                            {2, -17, -13, },
                    },
                    {
                            {-19, 2, -11, },
                            {-46, 15, -8, },
                            {-86, 0, 13, },
                    },
                    {
                            {2, -2, -45, },
                            {-9, 0, -68, },
                            {-17, -18, -3, },
                    },
                    {
                            {10, -10, -12, },
                            {-44, -51, 20, },
                            {35, -20, 28, },
                    },
                    {
                            {-17, -45, -33, },
                            {-66, -25, -26, },
                            {41, 5, -3, },
                    },
                    {
                            {-8, 58, 35, },
                            {-32, 69, -25, },
                            {-86, 36, 19, },
                    },
                    {
                            {29, -13, 52, },
                            {-4, 3, -18, },
                            {-23, -53, 6, },
                    },
                    {
                            {29, -10, 41, },
                            {-23, 1, 52, },
                            {-36, -43, -8, },
                    },
                    {
                            {-10, 6, -7, },
                            {-58, -10, -6, },
                            {17, 22, 14, },
                    },
                    {
                            {-15, 20, 6, },
                            {-58, 21, 11, },
                            {-52, 4, -6, },
                    },
                    {
                            {0, -18, -1, },
                            {-6, -11, 98, },
                            {56, -46, 51, },
                    },
                    {
                            {-31, 25, -6, },
                            {-49, 5, 13, },
                            {-35, -16, 7, },
                    },
                    {
                            {19, -51, -16, },
                            {-6, 1, -50, },
                            {22, -19, -43, },
                    },
                    {
                            {-1, -13, 49, },
                            {-30, -17, -25, },
                            {22, -7, -19, },
                    },
                    {
                            {-8, 37, 5, },
                            {-62, 19, -19, },
                            {-127, 23, -44, },
                    },
                    {
                            {26, 4, 45, },
                            {-13, -14, 8, },
                            {-45, -57, -24, },
                    },
            },
    };
    Bias_t Conv2d_5_Bias[32]=	{
            -7438, 602, -9963, -8759, 356, -4141, -510, -629, 1603, -6494, -308, 677, -4618, -2116, -7499, -5123, -4343, -4598, -815, -3763, -1601, -3693, -886, -747, -8058, -9947, -7658, -1476, -5050, -8664, -2262, -7737,
            };

    Weights_t Dense_8_Weights[1][64][1152]={

            {
                    {-4,-4,1,-3,-19,-18,-12,-1,24,-13,38,-9,45,0,-33,19,13,-30,-9,9,-15,6,4,-39,-49,36,0,-12,8,9,30,3,-6,1,-42,-35,7,-27,-40,33,-23,-7,-5,-26,-41,-8,21,-5,-57,5,-14,9,31,40,22,35,21,-6,12,9,31,18,-5,8,16,20,-49,-8,22,22,-26,-3,-7,-10,28,-21,-14,-53,43,14,28,-4,9,3,-19,22,-16,42,36,-13,0,-24,12,32,54,-32,-45,-7,-4,10,-14,-34,44,7,-26,-3,-40,-14,-22,-21,-18,18,13,28,-5,0,18,28,14,14,31,33,46,9,-9,9,-5,7,31,-10,-11,17,22,-15,-18,-28,-12,-18,-9,-28,-22,16,-6,-20,-19,12,-48,18,38,18,21,-34,-35,-1,41,4,-9,16,32,1,31,34,29,62,60,-25,-7,-4,-9,4,1,-4,9,-1,-13,14,-5,18,-11,5,-1,6,16,-30,-16,16,-14,22,46,10,-17,-46,-14,20,-6,-5,-41,-27,-11,-25,-5,-35,6,-7,-1,-11,5,-4,4,6,-38,-10,-20,22,-2,13,-36,-58,-54,-19,-37,-1,-22,-13,-33,-26,-4,-8,-9,26,38,33,-20,7,48,22,8,8,2,20,25,-1,2,9,3,-18,-22,-7,5,-5,-8,1,-15,-57,-36,10,7,3,-13,-4,-4,10,32,64,12,28,27,25,-4,56,-6,13,40,6,-13,14,26,-31,-5,-12,4,-32,8,2,-15,36,-16,-30,-4,-20,21,13,12,-12,20,11,-4,25,-14,2,13,32,22,14,-12,21,-8,-12,-16,-45,13,-10,-20,-8,-15,-16,0,-41,2,17,-21,-15,-31,-32,5,-20,9,-31,-26,6,-22,53,25,-28,-8,-46,-20,10,-2,2,8,-19,-4,0,6,2,-28,-53,-8,15,11,25,14,4,31,8,41,-7,5,-7,-13,-43,28,0,-17,-34,-71,19,20,-12,12,-36,0,15,34,-2,32,3,18,-1,-16,-20,-35,1,11,23,19,-2,-15,9,5,-19,19,-41,-36,27,-38,7,17,46,-22,-18,-14,-26,-6,25,45,16,43,19,29,22,-4,3,1,-15,33,-94,-13,-24,-10,26,-8,-11,-11,-27,-12,2,12,-4,-27,-40,-13,-29,-9,43,-17,-44,12,29,32,10,-16,-18,39,3,-11,-21,33,-29,-19,7,-44,-8,52,-25,-1,-3,20,4,-14,-35,8,0,25,-13,20,-8,2,-2,25,17,-28,7,-20,-4,25,-6,-55,-26,-8,21,-16,-1,-5,-8,15,25,-12,6,7,6,-24,-5,14,11,-6,10,2,21,4,8,-45,-27,-2,-11,2,13,-11,-10,8,19,-11,-8,57,12,21,32,5,19,42,15,-60,22,27,8,-15,-7,-12,-8,-9,-9,10,-24,-6,21,-7,19,-9,1,-13,-16,40,-3,20,-28,-15,-14,17,13,9,-28,-1,28,26,-3,-9,-33,2,28,-10,-59,21,6,-35,-3,34,-11,17,-17,18,6,3,19,-28,-16,-16,-41,17,14,-16,-5,-5,-13,3,25,1,12,38,5,26,38,-16,-54,-4,16,4,-19,-14,-19,-10,8,13,-15,14,-10,7,-22,-7,12,-8,-15,-17,8,21,13,-1,0,18,1,-2,20,4,-30,-9,-4,2,-37,-19,-26,2,-10,-4,-8,-21,-45,4,-1,-15,10,-39,-54,-17,-1,-32,-25,-60,-18,-23,-3,-1,-26,-15,-30,-11,-7,-44,-85,11,-3,-2,-12,-6,-44,37,12,-6,-16,11,4,7,31,3,-3,1,31,-1,8,22,-1,57,31,-6,2,-3,-74,-34,3,31,18,-23,1,-59,-33,47,-38,28,13,23,1,9,34,29,-2,6,10,-17,14,-6,-24,21,4,4,-29,25,-34,30,11,-19,-43,5,-1,-48,22,54,17,14,40,15,-38,-44,-11,3,6,28,-62,-15,-37,-15,6,25,13,12,-27,1,-17,-5,16,16,-41,10,-10,25,9,-2,-13,11,-14,10,9,-24,-59,10,27,41,-14,-11,-23,29,5,4,2,21,7,-1,-16,-22,3,60,2,-18,-33,-10,-16,33,5,-29,-3,-9,10,4,-26,-7,-21,-10,27,-15,-13,-8,11,-17,23,-28,-20,-12,41,-23,-19,19,28,23,10,-18,-15,45,0,18,-20,-15,-15,-20,-43,6,14,20,8,-11,-22,-15,5,17,-2,-21,-10,35,28,7,-41,-46,-28,28,31,7,-13,-31,-46,8,-30,-21,-2,-5,10,-17,-9,-3,-24,-1,9,33,10,43,-51,-24,-7,-28,26,-13,-13,13,0,6,15,18,14,4,6,-2,-4,12,7,-21,-22,-25,6,-2,8,-13,-22,-12,-17,16,7,22,-3,-35,10,-8,4,-6,-6,10,27,38,-4,-46,-27,-1,11,-2,-15,-32,-21,31,-6,-4,63,66,20,-6,-20,-12,14,14,-41,-49,37,-14,-21,2,20,34,-7,17,-33,-44,-16,3,-1,11,11,20,0,2,-16,-42,-50,52,4,2,-14,-7,-53,17,-3,16,39,59,-36,17,1,-25,25,-7,-4,18,0,-10,-32,0,-15,14,-13,-3,12,45,-1,-14,-17,27,24,20,2,3,-34,-20,-5,2,-3,30,-30,-39,-44,-1,-4,5,-29,-11,-23,4,-19,-3,-14,-20,-29,-36,-17,-14,-51,8,-51,-25,16,-24,37,-6,-11,-26,29,24,17,21,40,19,41,36,6,-15,41,48,-34,-23,-32,-14,3,-6,0,2,0,16,-29,13,0,12,1,-12,8,-28,17,0,33,-21,-7,0,33,1,7,4,20,7,11,-7,6,-4,-1,27,-3,-37,-23,27,14,-19,-33,5,-54,-22,-49,2,32,31,-7,-4,31,11,-54,-11,-47,-3,22,-23,-30,-80,-52,-22,-51,-33,-51,35,14,-29,13,8,-14,28,38,-15,-29,-43,-8,39,11,3,9,-18,10,9,-14,-8,-30,8,11,21,18,-31,10,-54,-27,5,16,29,20,24,-17,-38,21,38,10,23,-23,22,46,14,-31,10,8,26,-5,22,-32,28,23,22,-22,},

                    {7,9,-10,-3,-1,5,7,-12,-10,10,-14,-14,-7,6,5,-6,9,-4,-10,7,2,3,-1,9,-3,-10,-3,-3,9,-3,4,-3,1,8,-13,-5,8,-7,1,-6,3,-12,-1,-5,4,0,-3,4,-3,-9,-15,-11,-10,-4,9,4,-5,-3,-10,-9,5,6,-6,2,-2,-2,5,2,7,-10,-8,-13,-8,-4,6,-4,2,-2,-2,-1,-8,-6,6,-3,6,-11,-9,-6,10,-3,-3,-4,-4,-1,-12,-9,-8,-10,-1,7,-11,4,2,-8,6,10,-7,-2,6,9,6,-5,-4,-1,-7,-2,-11,-4,6,8,0,7,0,-13,5,-10,1,-3,-12,-3,3,2,-2,1,-6,2,-12,-10,-9,7,4,-11,9,-10,-8,-2,2,-1,4,-5,10,-1,11,5,4,-4,6,-11,-8,-1,-10,-13,-1,-4,-4,-13,5,-1,-7,-13,-1,2,-3,-14,0,11,0,-7,6,1,-8,8,-1,4,-11,-6,-2,10,5,-7,-9,-2,-16,-9,-13,1,-8,8,-7,-6,10,6,-6,4,3,3,-8,-8,-8,-13,9,-8,-8,-5,2,-3,-5,6,-6,-4,2,-4,5,7,-14,-4,7,7,-5,4,3,11,1,4,6,-11,-7,-6,-8,-6,-7,-3,-5,12,-11,4,8,-4,10,-2,-7,2,6,-2,4,8,-3,-13,4,1,10,-7,3,-13,9,-4,-1,-4,-2,4,-3,-4,5,0,-8,3,-2,2,-13,10,8,-4,10,8,8,7,-18,-8,-9,-9,10,6,3,10,11,-4,-3,4,9,-4,3,6,-4,-15,5,-4,5,-4,-10,-4,-3,-8,-4,-3,-5,6,4,6,9,8,5,-9,-4,10,9,11,4,-8,4,0,7,2,6,-14,-9,-6,0,-7,-9,5,7,-6,7,-9,8,1,-5,3,-7,-4,-5,-10,-1,1,-10,5,-11,13,-11,7,-2,-7,-13,-6,7,1,-4,5,7,-1,-3,-11,-15,-5,-8,-3,-4,-2,-12,-11,-12,-7,-5,-9,-2,0,-1,-7,4,-12,-6,3,3,-6,7,6,10,-5,4,4,6,-10,-14,-6,-4,-16,-18,-9,11,6,-3,-4,-15,-10,-12,-6,-8,-16,-1,3,4,1,-7,5,8,-9,7,9,-2,-11,-7,0,-4,-8,7,-6,7,8,3,-9,1,-7,-6,-10,0,0,6,7,-7,-14,9,11,10,-8,-1,-12,-3,-13,1,-7,6,2,6,0,-1,3,-2,-2,-7,-13,0,-12,-8,-11,-1,-6,-10,9,7,-10,-12,-3,3,3,6,-2,5,4,-10,-7,-1,9,4,4,-13,2,-13,8,-12,-5,0,-2,-8,1,-7,10,11,3,6,-8,10,-12,2,-5,-8,5,-1,10,-2,-3,7,-15,4,-8,-9,-18,-3,-8,9,-1,8,6,-3,-11,-11,3,-4,4,5,-12,-8,-7,-14,-8,3,-5,-2,7,-1,7,-13,-13,-6,6,-8,-7,-12,0,4,10,-6,-9,10,9,-9,0,-3,-8,-12,-2,-4,-5,4,-9,-12,-4,-12,-9,0,-12,-6,7,-8,-3,-11,-14,-6,-3,-8,-3,-13,6,-15,4,-9,9,7,2,-7,-4,-5,-5,8,-8,-17,7,-9,8,-12,-12,-4,-1,5,-3,5,1,14,-13,-3,-7,7,4,-13,-13,-5,-13,-1,-6,10,2,5,6,-5,0,-9,-8,-7,0,-6,-11,7,-11,7,-12,1,-4,-4,2,-6,1,-8,3,-5,7,-8,8,-10,-5,6,3,-4,-2,-17,-3,-8,-16,5,-15,-5,9,4,-6,9,0,-13,4,-12,3,-9,-8,-5,-3,-11,5,-10,-1,10,4,-6,10,-6,2,-13,-6,3,2,-5,10,6,-9,-12,1,-5,-10,-8,9,-4,4,2,-13,-10,-11,-12,-1,8,1,0,4,-3,-7,1,-2,-9,-8,0,-5,0,0,5,-4,1,-5,-10,-19,1,3,-8,-2,-9,-10,-10,-18,6,8,0,-2,11,-9,4,1,-7,-9,-13,-14,-2,8,9,9,9,9,-12,1,6,-13,4,3,-2,0,-13,0,-14,10,1,1,1,-2,-8,-2,-1,8,-3,2,-2,-12,-7,9,0,7,-2,-11,9,-9,-4,3,-10,5,10,5,8,-2,-8,-2,-13,5,0,-2,10,7,8,-9,-2,-10,0,-1,4,-2,-10,-12,-4,-7,-4,0,-10,-3,0,2,-1,-1,-11,1,-7,6,6,7,7,6,-2,-3,-14,-3,-6,-11,-5,-2,7,-2,2,-12,1,-7,10,-4,-7,5,-2,-10,-3,3,7,-5,1,5,3,-7,4,-14,0,-4,6,-5,0,-14,-2,-6,-10,-3,5,-19,0,6,-17,-2,-18,9,-6,7,-10,-5,-2,-8,4,-11,4,11,0,-3,5,-6,-15,5,-13,-11,7,-3,4,5,-12,6,-8,-4,-7,8,4,-1,6,-9,-3,4,-10,-13,-7,-6,-12,9,3,-14,-8,5,5,7,-3,-13,-4,-12,-12,-2,-3,-8,-11,4,-12,-10,1,-12,0,-13,2,-7,9,-8,11,-8,-5,-7,7,-18,-6,-5,6,1,-13,12,6,-10,-5,4,6,6,-12,-2,3,-7,3,0,7,4,-10,9,-13,2,7,-1,-9,-13,-14,3,-16,-3,4,-9,-6,-4,-11,9,-5,4,8,-3,-14,-10,5,-1,-13,8,-6,6,-11,-2,-5,-6,-4,-3,-11,-2,4,-8,8,-2,4,-8,-10,7,-12,-8,-2,-5,-4,3,8,1,4,6,7,-3,7,-9,7,1,-12,-2,0,-11,-4,-4,-3,-1,-3,6,-2,5,-3,-3,-16,-9,-11,-2,-4,-5,5,6,-8,4,6,9,-16,-2,-6,4,-1,10,3,3,-3,5,4,-3,-6,-8,-7,10,-5,-8,8,3,-2,0,3,5,5,-5,-19,-7,1,-1,-1,2,-7,4,-12,-7,-4,-7,-8,0,8,5,0,-13,-11,-19,-5,8,-11,0,10,2,-10,-12,7,-6,4,-7,-8,-9,9,-5,1,5,-3,-9,-8,-11,-2,-11,-3,-12,5,4,-13,0,7,3,-11,-13,6,-10,-14,4,-11,10,-16,-1,},

                    {-23,-49,-10,12,21,12,-6,22,7,9,16,9,30,28,41,-30,2,26,-4,59,10,22,6,-27,4,20,-24,-16,-19,-21,5,1,-17,4,-16,14,-28,-38,4,9,5,5,-26,-24,7,-9,3,-20,15,-32,-1,-40,36,5,-42,-50,6,-1,2,-14,31,2,0,9,17,8,5,-37,-11,4,26,-7,-14,-14,-10,34,1,-3,-5,15,15,-12,20,-5,34,-12,24,-52,-1,31,28,38,12,38,-7,3,40,37,-17,-24,-4,-26,-40,-24,-22,33,24,8,-34,21,2,-8,-10,10,-11,-7,25,-38,-33,18,17,25,48,-13,-1,19,4,26,27,-19,-1,9,13,-18,-31,20,-32,-7,-4,20,-9,4,-13,1,-3,-3,-25,-18,-12,1,-5,-14,29,-29,-8,-6,18,-21,-9,-30,19,-25,-26,-49,13,-24,18,-18,27,19,-15,0,16,16,13,-23,-24,5,12,-18,21,43,-11,15,10,-28,-52,-17,-29,-11,27,33,-33,-69,-69,-3,10,31,9,4,12,-8,14,22,8,-21,-4,4,-22,-3,14,24,7,-1,6,10,-26,-17,8,37,41,35,-11,-11,29,33,-1,3,-1,19,42,-19,3,-11,-65,-12,18,4,-24,2,0,20,-14,-2,-13,43,-26,32,-3,-12,5,4,-30,-2,1,2,-6,5,-2,25,47,-21,1,53,23,8,50,16,-4,9,22,6,28,-25,-6,1,26,-30,-28,-5,-32,27,6,8,-36,6,1,6,-28,-15,-24,-10,3,13,-1,-10,-13,-8,-12,-24,6,-41,-16,-25,-7,-4,-11,-7,0,5,-12,-16,0,-1,17,4,21,40,-14,-9,-7,9,24,40,-62,-25,-46,29,9,35,-22,14,17,24,-12,63,27,2,-18,0,26,21,-1,27,5,11,50,-13,10,-2,-21,-19,7,-8,22,27,24,22,17,41,-28,-11,-16,46,53,26,-38,11,30,11,16,46,-9,-4,20,-21,25,19,-35,30,24,1,25,-34,-18,68,18,-19,-47,-24,18,10,-37,-42,25,44,-23,-6,-30,-30,1,3,17,-6,8,-31,0,5,-17,-5,15,-34,-26,21,10,8,37,36,-4,7,-12,-10,13,18,29,26,8,-20,10,12,-4,-7,-10,-26,-29,25,13,33,1,0,8,4,16,22,-13,23,18,4,11,44,7,28,37,-12,34,-24,31,7,1,-10,-39,-15,19,11,19,22,30,-2,-13,-31,0,-1,6,-8,-15,-28,-2,-7,-4,33,19,6,11,-9,24,23,-39,6,-5,24,-4,-13,31,7,-8,-22,-13,19,-4,-3,-11,-10,27,10,11,2,-6,8,6,26,-30,-33,2,17,8,-4,-25,13,26,-23,9,-13,28,-22,-4,16,53,-28,4,9,-13,-1,17,-13,-31,-6,18,-21,-2,5,-32,-28,-40,-5,-8,-10,-25,4,-18,-9,-11,6,4,14,11,-5,19,48,24,-3,29,4,30,29,37,-38,9,-12,-46,-29,16,-30,-9,10,17,47,-29,-41,-30,-12,0,11,-29,5,-28,-13,-10,22,5,12,-11,-33,11,65,25,44,31,3,11,45,14,4,10,-4,-11,-16,-1,1,1,3,-1,4,13,6,3,4,-4,16,20,-36,-15,-9,9,45,-18,-43,-45,-22,15,-2,32,23,-21,-19,-57,13,11,15,-23,-14,-7,5,19,-11,2,-15,-20,5,-22,-28,16,18,41,1,-24,3,39,51,13,0,-25,24,8,9,-3,4,-2,-19,0,-44,0,-58,10,-25,26,-17,12,-5,-10,-18,6,20,24,19,-30,-5,30,1,21,-10,-22,7,12,36,18,3,-20,11,40,13,-18,-35,-22,-7,13,-20,-10,12,-16,-47,0,-3,22,48,-7,-19,-25,36,-20,17,11,-11,-17,-19,-9,-23,-38,-41,-26,-29,14,7,13,6,-25,68,-3,21,47,37,8,16,23,12,12,8,12,-26,-5,-20,23,16,-6,-12,14,10,-2,-16,-40,-16,6,29,-38,-25,-19,7,18,27,-17,19,-27,-3,4,11,-14,7,41,-14,-2,6,37,34,23,-7,-46,2,24,-10,-20,-6,13,-9,-11,6,-11,-5,23,-31,-18,-1,-7,-7,-25,-11,-17,-7,-3,-19,-38,-34,-15,-22,-13,-11,-34,-27,-29,-1,-11,-2,-7,10,1,-11,-9,11,20,18,-24,-10,25,8,-6,-4,1,-17,-21,26,41,51,19,15,8,-56,6,47,-28,27,3,-15,53,-18,50,31,35,-10,-17,-12,2,-45,-29,6,-13,3,27,-19,4,23,-28,32,-32,-9,-21,-20,-6,5,-19,-21,-62,19,45,48,25,29,12,-12,21,39,11,22,-6,32,9,17,20,21,1,-13,29,9,-8,-13,-19,-3,-12,28,15,-6,-10,4,-2,-34,-15,-15,-14,-30,15,41,-2,70,25,-6,-46,-6,16,47,26,-16,-13,3,-14,-19,-30,2,-35,19,9,19,-42,15,8,-54,-3,-16,-5,-25,-21,12,-13,14,13,-23,-10,14,-11,-14,24,-7,58,-8,19,50,27,-41,-25,-5,-2,0,-10,-8,7,0,-41,-29,3,-6,5,9,-5,-8,-3,-14,15,13,-7,20,-37,-36,-12,-16,48,36,19,4,12,-5,32,-5,10,-20,-18,-45,4,-4,-16,-1,-37,-3,-8,-5,17,-7,4,-36,-2,4,7,12,7,8,-11,-17,20,61,1,-23,14,9,10,31,8,25,6,-9,-14,13,16,-7,-32,4,42,-11,16,24,-21,21,-22,-23,-19,-26,8,-21,-1,-16,10,31,29,34,25,-2,13,-6,2,6,10,-14,32,26,-22,8,-8,12,2,-12,4,29,16,13,-25,13,-28,19,7,16,20,4,2,6,3,-14,11,22,2,-52,-87,8,-12,12,17,-42,-45,-32,-2,-1,-4,3,-52,-19,-24,-8,-21,-1,17,13,27,13,-8,0,-17,-24,6,0,-25,6,7,1,12,27,26,-13,27,21,14,26,-17,10,-21,-5,-14,19,2,-11,12,-24,23,17,0,31,2,18,-21,14,},

                    {-7,-6,-5,-3,24,10,16,10,3,-6,0,-26,-31,-8,-17,-27,22,39,-7,-24,26,-20,14,10,15,-19,15,13,32,13,-5,24,-7,14,12,47,15,1,-13,-56,21,-12,15,9,23,14,23,16,39,-24,6,-14,10,6,-25,-9,-40,-16,2,5,-37,-8,-45,15,-3,7,49,72,7,34,11,24,12,24,-3,-16,10,-23,-1,8,6,10,-15,-14,8,-15,-18,-7,40,-11,-32,-14,-12,11,-14,-18,-4,37,41,43,-14,4,17,35,18,-2,-41,81,-15,-34,17,-13,17,0,19,14,20,8,9,-17,-3,13,17,21,10,-35,33,-13,24,30,1,1,-2,18,3,-8,17,41,-9,-7,-19,-22,-11,-1,2,-33,-35,-63,-3,-12,16,32,4,9,36,8,28,-20,22,-21,19,2,-9,-4,-26,-15,23,23,-28,23,-46,23,13,34,4,33,5,35,21,-14,-9,-16,-35,-34,-41,-29,37,57,28,35,18,-8,-11,6,32,15,28,-2,16,31,30,41,11,-1,19,10,50,1,-34,-22,-8,2,-6,-24,-21,-5,-10,-9,-44,-19,-45,-1,-28,30,-8,41,27,-4,2,0,-31,3,19,-4,13,-15,-21,10,9,-10,-5,11,-29,9,8,48,-3,-15,-43,26,59,80,-25,-7,4,18,-16,-15,21,2,10,42,12,-36,5,12,20,35,28,-60,30,-5,-14,58,10,-28,17,12,-38,-8,6,25,-8,-5,-38,-12,59,84,0,23,-8,22,-2,-8,-1,5,26,-1,-8,-28,-3,23,-10,-36,-21,-1,10,29,13,32,11,26,8,0,-29,-23,5,33,32,7,15,-26,8,0,-6,-6,-16,27,-25,-20,0,-15,28,26,-17,-20,27,-1,48,-22,-34,3,-4,-22,50,-7,-52,8,4,6,9,-19,2,8,-23,4,-9,42,27,41,6,-18,-15,-23,2,-63,58,18,16,12,-43,-4,-1,-1,-10,-46,3,10,25,-10,-24,-25,-9,4,0,-25,3,6,28,30,-16,22,41,52,21,11,5,-22,12,-8,13,-25,32,-13,6,9,-7,-27,1,17,-17,-17,-3,-41,50,31,-18,9,-21,4,17,28,2,-6,-47,16,21,-13,-9,3,39,84,13,23,20,25,18,-11,-46,4,5,17,11,16,-28,10,-13,11,-13,26,36,-18,10,41,2,8,-15,-32,3,7,-29,-16,-5,18,1,6,-11,-20,-14,-38,-31,-4,7,-15,9,30,0,21,32,-28,14,-5,9,12,1,-4,-1,-5,-20,14,14,19,-32,35,-26,-3,24,-18,7,9,-5,8,18,16,23,34,-27,-6,3,10,0,28,-13,-10,34,27,-10,-12,14,-5,21,21,32,-19,-4,-55,8,23,3,15,-19,-4,15,40,25,-17,-14,11,-7,27,-13,19,-19,31,-6,-38,-17,44,-1,-11,-13,-28,18,49,-14,-26,10,-35,-12,25,32,38,-13,-7,9,-3,-4,24,32,25,3,11,-10,14,20,-43,4,24,-16,17,-14,-56,-18,-9,-20,-3,-20,-26,-8,7,25,10,-29,-63,14,19,57,56,-11,-5,15,-11,9,-3,-11,16,-12,6,-7,-40,-12,13,10,6,15,20,10,-42,2,-9,14,10,-40,-32,23,4,10,35,3,-33,30,33,88,50,-38,19,-14,45,70,24,-25,36,32,43,40,-22,-7,16,0,-32,-10,-1,1,20,-7,9,4,11,6,17,-24,12,-4,14,20,7,-18,-13,-16,-31,17,5,-8,-17,-15,-5,12,13,31,24,-17,35,41,15,-24,12,-4,7,-17,28,7,12,11,34,-27,14,-6,18,23,11,21,-6,-9,-24,-44,36,19,-15,4,-21,-61,26,19,63,14,-5,-8,27,51,24,-5,-9,11,-16,-38,-37,-9,6,-18,8,8,-24,45,39,12,-24,-54,-35,38,39,60,15,-11,26,24,12,13,-31,10,15,-1,5,-15,-28,5,29,2,-23,-35,-63,5,-36,6,36,0,-10,-9,-12,5,2,22,22,8,-17,29,29,-4,46,11,10,27,13,26,21,-5,-29,21,14,-4,-27,3,0,18,23,-45,-10,1,-9,-5,18,13,30,39,7,-4,-11,4,31,29,22,13,-7,-19,-6,19,34,3,16,-2,-13,31,38,14,11,35,5,-3,21,-13,-23,-44,5,15,-7,27,15,13,-12,-40,-25,2,2,-26,1,22,62,-13,-13,-37,5,48,32,-1,25,9,27,14,31,-8,2,19,26,30,13,25,4,0,-30,-56,-32,9,20,10,-2,12,-1,-9,-21,24,4,-36,-28,17,45,63,51,-19,-3,25,15,55,13,-11,-18,7,12,-9,-26,-10,3,5,-10,-38,-5,-43,-33,20,2,33,-17,-35,2,20,0,16,-8,-2,3,12,-41,-5,0,-2,12,21,-18,-5,27,2,-3,26,9,9,25,16,-19,-6,11,-41,-36,0,-37,7,-17,6,-10,25,24,-5,-5,8,29,28,3,15,15,-17,-22,-3,36,20,-20,-5,27,13,29,12,25,31,34,22,20,14,14,13,-2,30,14,-6,23,-2,-2,-32,-9,20,-10,-26,3,3,6,4,-13,17,17,6,10,1,13,-21,25,-32,-10,31,46,17,-19,-2,53,3,2,4,-4,-21,-25,5,-3,20,34,-6,-13,-3,5,6,3,29,21,27,-2,-8,-50,10,-1,26,8,-6,-34,34,36,48,16,-53,6,20,56,-16,-42,5,-18,1,-5,15,17,8,-15,-23,-25,4,-3,25,32,5,-6,48,-7,-4,-2,9,37,-4,15,8,-30,-18,57,59,-23,-26,14,54,36,15,3,8,-28,-5,-58,-9,10,-29,27,3,-26,26,37,10,2,-23,-6,22,4,-12,-4,19,6,26,97,54,4,-42,3,66,59,-5,-4,18,21,-1,-7,-26,0,-14,-32,7,35,34,46,-29,2,12,17,23,-33,46,-23,-2,0,-49,11,6,-43,-15,25,-15,-21,-9,1,-10,-20,-1,30,57,29,},

                    {11,35,-34,14,-1,12,-24,-13,-29,-3,20,14,-20,-1,10,29,-47,-41,14,-17,16,-18,4,-22,-1,22,42,13,-63,-47,42,-15,10,-12,5,-28,-17,-20,11,33,23,14,-28,-4,-29,16,-10,33,12,-20,-4,55,-22,23,30,43,59,35,23,33,30,16,16,17,-23,-14,22,28,7,-37,-59,-32,20,1,-56,5,34,31,-12,-21,-7,21,2,-30,-7,20,9,41,-32,4,25,-20,-28,-14,0,-67,-35,-33,1,4,-3,-27,43,12,-21,-56,-43,-57,48,65,-22,-24,-22,1,23,0,-51,16,17,22,3,4,-62,-33,31,0,-15,16,-59,-24,-20,-1,32,-6,12,-12,-4,5,6,-3,-31,-26,-20,-17,-11,15,-7,21,12,34,-15,3,-41,14,-3,0,-21,3,-17,51,-9,22,-1,21,0,55,11,35,-3,-7,54,24,-5,-31,-7,23,48,-32,-47,-25,2,-24,-3,2,22,39,41,24,-27,-4,5,32,-17,-30,8,-5,6,-35,3,-2,32,-20,-32,-43,0,0,16,32,-4,-36,-8,16,1,12,2,-29,48,-8,10,19,-2,6,10,-18,-33,-33,-8,-13,-16,-48,-31,13,2,-5,26,-12,-15,-14,-13,54,50,15,26,23,-43,-16,14,7,41,17,-10,-36,26,1,-13,13,31,29,30,-18,-32,-21,17,15,-6,5,-77,-53,18,20,-15,-8,-90,-37,-18,19,2,16,4,-27,-27,5,11,30,29,-23,-51,-17,28,-25,-57,-77,-9,14,3,12,-15,-2,28,2,20,19,-3,65,39,-1,24,-5,18,25,-9,15,-31,-12,-17,5,-32,-65,7,21,-5,4,-56,-24,-3,-6,-70,-6,43,1,36,-27,-14,-7,27,-28,-44,-19,-36,-4,-24,-15,-13,-5,-27,-1,10,-34,20,-4,38,43,-13,-2,45,13,13,-11,7,-12,-7,13,-77,24,31,25,16,-37,-39,19,45,-12,-12,-3,18,36,-15,-1,9,34,48,26,-14,-27,39,5,34,21,9,-6,10,-2,27,-24,-37,-27,41,43,-9,0,-17,30,-16,4,0,2,7,3,-21,8,-8,-31,41,1,-41,19,-55,39,-13,-23,13,-23,-29,-54,-17,-43,-9,24,4,-13,-19,-9,-9,-5,-44,-59,5,13,26,-6,-27,-1,1,1,-31,-36,-11,20,-19,-76,-16,13,-33,-55,-3,-51,-13,4,6,16,1,-46,-1,-30,24,6,22,-42,7,-36,-39,3,21,24,11,13,19,12,-13,-18,18,2,22,19,-1,-3,1,20,41,5,-6,46,7,16,44,38,-20,11,26,-13,48,-21,-11,-3,9,-30,-12,-20,0,-1,-1,-12,-19,25,-3,-19,2,11,-20,15,-16,31,-27,-6,1,32,-10,13,-3,19,36,21,-11,-49,14,4,8,-13,-69,-22,8,-76,-43,-34,23,57,17,-40,-16,30,-6,36,-25,-15,-50,37,-52,-63,-13,-1,-43,-30,-9,-40,-11,-3,-30,-54,-63,-69,14,21,5,-28,-3,10,1,-29,-47,-27,1,35,16,0,16,15,7,27,-11,-5,-54,-9,4,-35,28,13,-13,-25,-11,-48,15,-18,-55,-31,-29,-38,16,23,12,9,-27,-52,31,11,-36,-1,46,22,-35,7,-17,3,9,-41,16,8,20,30,-26,-3,-45,-22,-60,-97,32,-61,1,-38,0,15,-2,-33,-7,-26,-31,12,-60,-33,-1,-33,-22,42,-10,23,7,-28,-10,-19,-14,3,13,-21,11,4,8,5,18,36,37,34,8,71,5,41,24,-29,11,30,23,21,31,2,-28,-36,-1,-28,-42,-6,7,32,9,-40,-35,-64,19,-21,-4,-38,-34,-7,40,20,-3,-11,-21,17,20,-10,17,29,22,-15,-39,-30,32,39,40,-25,-29,-41,-3,31,2,23,17,55,41,19,39,20,-4,56,-7,22,-17,7,34,10,-36,1,-29,-38,-50,-28,7,-25,-13,-13,5,-23,5,-3,5,-12,-49,-57,-11,-14,18,12,6,2,7,-14,-15,6,31,15,-5,-12,20,32,-9,-23,-30,-8,-12,-1,-3,-28,-17,-2,4,29,13,-42,-28,15,5,10,-12,3,-2,-6,-53,-35,4,36,-1,-9,-17,18,39,-22,18,-17,18,29,38,-1,-23,40,45,45,53,39,33,19,19,16,-25,3,6,24,3,-1,-29,-13,-5,-32,-15,27,11,4,-11,14,34,35,-21,-32,-30,10,12,67,-16,-54,27,20,32,15,25,0,-28,-11,33,21,2,-10,16,43,44,-47,-25,-10,32,-25,-19,5,73,-3,11,45,16,4,9,14,-6,-19,-18,-10,-18,-49,-2,16,22,-68,-26,-69,17,-5,-27,-21,-31,-49,-5,10,-2,9,-36,-49,-10,-14,-84,2,38,23,-9,17,-7,15,31,0,-4,43,21,33,2,-39,-1,-3,20,6,28,-21,-31,6,4,11,14,-41,35,10,44,-56,-23,-34,21,37,49,-60,10,61,11,35,-26,25,21,6,-3,8,-29,19,-11,-12,0,-7,1,12,-23,3,-12,22,52,6,20,4,-27,0,34,-18,-40,-14,33,22,-60,-33,-4,33,17,-28,-16,17,33,-6,33,5,14,28,46,27,10,-4,0,15,14,-17,-12,-33,2,-11,4,-54,-7,6,5,-3,-86,-63,11,-6,3,-15,26,46,8,22,-26,12,0,21,-70,11,-37,-77,-8,27,-30,-27,-66,-28,-44,-10,-9,-1,-18,-5,-33,-6,0,-40,-31,19,-32,-4,47,57,-5,-16,-3,22,-4,6,-46,23,35,-21,-10,14,-17,-22,-60,-18,-31,38,-20,5,-40,-16,28,16,-7,-28,8,-16,-36,-26,-9,31,-31,-25,11,-20,-21,35,11,28,-17,-7,13,39,19,1,-10,-10,34,7,27,-13,-24,-2,48,32,23,30,14,-23,67,55,26,-19,-28,24,10,14,-19,-30,0,-16,-18,26,39,60,46,-30,-28,-17,6,-16,-7,-2,-45,-25,19,-16,10,-14,-2,-14,38,16,30,26,-19,29,-6,14,16,16,32,-22,-32,13,},

                    {-25,18,6,-8,5,-6,-2,6,17,6,-39,-22,34,0,-11,18,4,-12,10,38,26,58,-8,0,19,2,30,17,-22,7,-22,-9,25,3,12,41,-21,-5,2,-15,-24,0,10,21,-8,13,-19,-46,7,32,-44,-2,18,39,-9,6,13,12,-10,12,26,5,0,3,-5,-4,22,-92,-50,-18,7,16,10,15,9,22,8,-21,-33,2,18,-2,-22,17,27,38,13,23,7,59,21,28,38,41,16,10,-1,14,-9,14,-20,5,-40,-79,-10,27,4,-18,-38,21,-15,15,6,19,-2,-23,10,20,17,5,25,7,8,-5,-2,0,-5,5,-3,-12,-9,1,17,-20,18,22,-8,-14,-30,33,31,33,-8,-2,13,23,-16,-10,4,-28,10,-27,-7,0,-21,-18,3,33,-18,5,-9,12,-24,4,37,2,-9,-7,7,1,-9,-19,-16,-9,5,-35,-62,-11,-31,8,34,13,69,23,4,30,-17,-4,-4,-38,-13,-10,30,-5,-26,-41,-31,-13,-52,-75,-26,-21,-24,36,-20,-62,-44,-6,28,39,22,-29,22,1,27,29,13,27,-44,-27,5,-4,9,-25,9,-8,-14,14,-8,12,-2,-7,-1,25,-12,46,38,-21,-13,12,-20,45,66,-35,-24,-5,10,13,15,-53,-53,-31,-5,23,-28,5,-20,7,-17,1,-9,-5,42,70,36,11,0,-6,13,56,5,7,-17,-68,14,27,15,4,33,-21,0,30,-6,23,29,59,-23,-15,12,34,-12,-1,14,-15,-5,-12,-4,-12,-11,-8,20,-2,26,-4,-16,-12,-14,1,14,-18,-2,-20,21,-30,20,23,40,31,-21,-9,-25,24,57,45,-36,78,36,-5,13,-3,1,27,-6,18,23,10,14,-29,-26,53,35,29,2,-61,-28,0,19,39,-37,-14,0,45,10,10,-4,0,24,5,-9,-9,-11,8,-14,-7,-5,-11,31,35,40,26,-16,-53,6,20,18,-9,19,34,-18,7,34,9,67,38,1,18,35,22,-14,-21,-4,-19,-89,-74,-13,-7,-33,27,-11,0,-7,9,29,1,11,6,34,40,4,37,16,41,2,14,-29,-48,20,8,20,-11,-37,-44,-20,13,16,12,-42,2,4,7,14,6,-24,32,28,-14,-9,5,-6,20,-4,-17,11,-26,6,-7,-41,-22,29,-2,-17,34,-4,4,22,17,32,-7,39,22,12,12,5,-21,-4,17,8,37,22,39,6,-14,-8,23,9,5,17,-28,-38,-16,14,4,4,-45,-23,32,0,54,17,-20,-22,-33,33,44,29,-52,2,6,-8,25,-26,-22,-39,-23,-5,-9,-13,-8,-14,-16,15,-19,-3,-26,-17,-42,13,6,1,16,-20,13,-20,-2,13,30,3,-17,-3,6,18,23,-17,-13,3,15,36,10,14,-16,18,3,-4,-18,-2,14,7,-22,12,13,29,-23,2,-10,5,-20,-28,-16,25,-29,-25,-2,-2,-1,8,7,36,0,-1,3,24,-10,-6,6,-4,14,17,53,25,-1,-9,17,-10,4,2,3,20,31,5,-6,-20,-18,-7,5,12,-6,-21,-16,2,33,0,-9,-21,-1,-1,26,-13,1,18,19,19,32,8,16,9,2,-17,22,19,10,-4,-31,-15,-30,11,3,9,-39,-26,0,-8,-65,-61,-47,-36,-45,-25,-104,-78,-18,-5,3,-17,-36,-23,9,57,50,-2,3,-6,-11,-54,-22,25,1,-23,-16,-17,-35,17,5,-20,0,42,2,35,41,-27,-23,-14,-22,29,64,-19,-10,-6,-19,29,36,8,-59,-33,11,0,-27,-25,-2,9,7,-16,13,-30,-6,14,-6,18,10,-12,-17,12,14,46,20,-7,-5,-4,-7,18,27,40,32,20,-20,23,0,33,5,-13,-2,9,-16,-37,23,54,-18,-9,-9,-11,-30,-29,-4,0,-9,-5,-28,-19,-31,-5,-8,-40,-15,25,16,2,-16,29,1,8,28,3,21,29,10,39,9,-17,-9,34,20,-17,6,-4,-16,-1,-2,0,-24,0,-3,-2,-4,-6,-10,-11,-12,-12,-15,20,61,11,8,31,-2,4,30,23,-26,-4,24,17,21,-3,-13,28,4,-30,20,4,1,33,2,-69,-30,1,-1,18,-15,-41,1,-24,36,21,-33,-41,-17,-35,12,17,-5,-41,-19,9,-15,-26,-8,11,-5,42,35,10,-23,-14,-3,-5,-7,21,13,1,2,28,22,13,-28,17,12,41,64,44,-6,-11,32,45,41,48,-35,-35,-23,-36,3,-62,-53,-32,-16,-14,23,18,36,20,-24,4,-27,-24,-7,-4,13,22,-7,-21,-19,-11,18,-9,-27,-10,-2,14,21,16,-12,-62,0,-6,57,10,-19,0,22,33,50,11,25,-6,13,9,-1,1,11,12,9,-6,-47,-17,-3,6,-10,6,59,-20,78,30,28,-2,8,10,4,22,-14,19,-3,-8,-25,-55,-22,-51,25,-12,3,25,38,-27,-22,-6,1,-9,-31,17,-11,-1,19,-23,-13,0,-30,-2,-5,30,26,31,21,-20,23,27,-39,-13,-7,-1,-11,-54,2,6,-31,-1,4,7,11,2,-3,8,11,9,14,-23,-27,-6,16,4,-31,-2,9,28,48,26,25,22,-5,-12,-29,-33,-30,11,-6,0,-83,-33,6,30,53,-11,21,-16,-4,-12,35,-6,-15,-43,19,40,38,28,1,0,22,24,18,10,-22,1,-3,-17,16,-43,1,6,44,-7,24,-59,27,84,15,-13,-14,-48,-2,-6,15,0,30,7,-19,-18,5,-10,-9,9,11,14,6,-27,8,-15,-7,6,0,19,1,-13,16,15,15,-1,0,-57,73,48,13,-30,-6,17,20,7,3,-34,21,11,27,6,6,-65,-53,25,13,-34,-10,3,17,-38,-28,-28,-16,6,18,-32,-99,-58,33,0,15,-15,-36,1,-2,-20,14,-24,14,12,4,-26,8,-30,5,-33,-35,8,-6,34,-1,-10,-8,6,25,6,30,17,-7,3,12,5,19,25,-2,3,7,-12,28,22,-7,-38,2,},

                    {-10,-4,28,5,0,22,3,6,-7,-8,3,-14,23,9,29,-3,3,-16,14,57,-40,22,-15,12,11,26,3,6,-16,-39,-7,-26,20,5,12,-24,30,-24,-28,0,-14,-44,1,4,-18,-2,-19,-32,48,-18,-2,-33,57,8,-45,-10,4,-8,4,10,1,29,-1,-3,10,12,-38,-44,-37,-15,19,7,8,6,1,6,-7,-7,-17,-3,6,0,-14,-4,18,38,47,-21,23,41,24,16,-1,10,14,12,32,-1,-16,12,-2,-12,-10,-35,-24,30,54,9,-24,-1,6,12,-23,24,6,14,29,6,24,26,-5,-8,42,1,8,-5,4,3,14,10,46,16,7,7,14,-4,-2,-15,-16,24,25,39,4,-1,1,-27,-32,-13,-7,-33,-1,3,-21,-7,18,-8,14,-18,-27,-49,62,3,-31,-15,19,-30,24,1,1,19,-6,-29,5,31,-4,-25,-79,-19,-14,-4,42,17,20,21,-14,-43,46,-1,-3,-46,4,-9,3,-8,-43,-24,-15,27,1,6,11,-27,-6,-6,30,-22,-30,0,26,19,45,3,17,17,1,-4,-11,-10,-21,24,-20,22,-4,-37,16,-3,24,15,-11,-16,15,-33,62,35,-29,2,44,5,-5,11,24,11,27,-32,-6,11,4,20,13,-40,-6,3,4,13,32,37,-12,-26,4,29,51,34,51,46,-10,-16,24,33,32,14,0,4,29,-19,17,15,10,1,-2,14,-37,24,-4,7,29,11,-8,-22,13,-6,13,21,6,10,16,-14,-15,-1,7,-1,17,-46,-12,-5,-47,-44,-40,11,-18,-26,-40,-14,54,-29,0,19,8,-15,-24,14,-13,27,34,52,9,3,29,6,-24,-3,21,-2,8,17,-2,36,18,-4,6,-15,-1,51,13,31,27,21,53,21,-6,-18,-31,-40,19,-26,18,-2,5,11,5,33,-15,10,-13,30,12,-5,25,-29,15,-2,-10,-6,-26,-2,20,-27,12,74,-7,12,20,26,48,1,2,48,24,-22,-13,-11,37,-36,-46,-20,40,43,-18,-26,8,3,0,13,19,10,3,-12,14,13,-7,-7,13,-12,-30,-9,3,-8,23,-7,-7,11,-14,-10,-14,35,31,5,-35,9,-19,30,20,-23,24,53,20,29,-1,19,8,6,-20,-29,-27,9,-31,7,32,-32,-3,32,-15,15,8,-36,6,0,35,-12,-11,-22,20,-36,14,18,-7,11,6,44,-21,-11,-22,6,-5,-17,-4,-25,-17,6,-9,13,-2,-20,-14,-42,29,43,-25,19,-12,17,32,-4,9,7,9,-55,3,36,-9,-10,-27,6,-10,-5,47,-8,-13,-21,7,4,3,-17,3,-12,18,-13,6,13,-23,-45,41,-28,32,-43,-28,1,56,-20,44,-6,-10,-6,1,15,-22,31,8,-28,16,21,-12,33,57,4,-4,-33,20,33,20,-20,-48,-7,-13,18,21,-19,-13,8,17,-12,51,11,12,-9,9,-3,0,-44,-22,-41,-11,-2,2,-17,1,-3,31,14,52,49,-14,-11,19,-8,-9,-31,-22,-29,-9,6,-12,-32,-21,14,22,5,41,29,12,1,9,-8,-12,-11,-12,-6,4,4,3,8,18,-4,32,12,16,18,1,17,13,-3,-13,-33,-26,1,15,-19,-21,-44,-55,-48,20,4,-26,-37,-75,-4,-9,6,-16,-2,-7,-23,-5,-42,7,9,8,5,17,-19,7,-7,-11,-46,-11,-25,3,61,1,-26,-12,-16,8,8,37,-5,2,4,16,-14,31,-30,17,1,18,-3,-8,2,11,25,-19,-22,-13,29,6,6,8,15,3,-6,13,-1,19,58,23,20,-11,-22,18,14,22,28,-4,-7,-8,11,-8,19,-8,14,11,-36,13,-19,-17,5,8,20,-1,19,21,5,4,12,9,-12,-8,-21,-36,-74,-58,-27,11,-1,-34,9,-36,-17,24,24,3,10,46,37,23,-24,-12,-9,-3,-1,4,3,24,5,25,1,16,2,2,2,-25,-2,8,9,-21,-18,-5,-12,20,17,-20,-10,19,25,-26,-13,15,-35,0,23,17,15,17,-3,8,-16,28,-11,-16,16,9,18,7,-1,-11,-16,16,-3,0,-10,10,18,2,25,-1,-16,-2,11,-18,-21,-14,-9,-4,-8,-41,-5,20,-13,-17,-9,-8,8,12,-18,-20,-17,16,11,-28,23,-12,-12,-13,19,-11,4,-16,6,12,44,12,18,-33,-56,7,39,-29,9,13,5,33,-12,13,46,14,2,-5,-1,13,-40,-53,-10,14,-13,21,-35,29,50,-51,15,4,5,-31,-36,-21,-32,6,22,-17,-6,-5,3,25,24,16,-4,-1,-2,8,-20,-19,12,7,45,20,7,6,-6,24,-6,-10,6,-9,-9,-21,4,-1,-25,0,35,-17,-6,-6,4,35,-1,-14,63,-12,30,19,-5,-24,10,5,24,26,18,19,5,-10,-12,-49,-21,9,5,-1,-8,-51,25,-5,-54,-1,-14,-21,-47,-9,23,12,16,-26,-41,11,2,-12,-9,28,6,64,36,19,11,-14,-51,-41,-5,4,-7,-23,-9,-15,-5,12,18,-1,1,-6,-5,-5,8,27,-7,-23,-24,-1,37,-6,-62,-40,-39,10,9,-2,-43,-34,1,51,21,1,-13,-17,-67,-20,-24,-24,9,33,22,8,6,-4,10,19,-19,-24,10,-4,55,31,-2,5,5,-22,69,21,-10,38,-4,-8,28,14,33,6,-6,21,13,25,-13,-18,51,50,-6,15,10,-18,-18,6,-18,8,1,-19,13,22,16,33,38,11,17,4,-8,0,-7,4,5,13,-17,74,18,17,18,17,17,-18,-31,-29,59,6,-13,-39,8,3,19,8,-6,-7,-35,8,2,-46,-25,-47,-32,21,5,-28,12,-10,20,-5,14,-12,5,1,-14,4,-17,-36,-24,-18,5,-17,-20,10,6,25,36,-9,-2,-8,-17,-27,15,1,10,-23,4,-13,8,1,-9,-11,17,-5,23,-14,13,-20,-34,4,29,13,11,33,-47,-12,12,-1,45,29,-3,-18,-8,},

                    {-13,-6,5,-9,-11,2,9,3,-7,-1,-9,1,-9,-11,-4,3,-11,1,11,-10,-2,5,-6,-10,-1,-11,-6,-11,3,-4,0,6,-13,-9,-9,-15,-11,7,-9,-8,-8,0,2,5,-4,5,7,10,5,4,-1,4,-16,-10,5,-10,-1,1,-10,-9,-11,-6,-2,1,-4,-9,10,2,-7,0,3,-4,9,7,-9,-1,-5,8,-7,7,1,4,-3,8,0,-4,-2,-8,7,-2,-9,5,-3,-4,1,-4,8,7,-8,-9,-4,-11,-6,-3,-10,6,-4,-1,-6,-8,2,3,1,-3,-2,-9,6,2,-11,-12,2,-11,3,-11,0,-13,7,-13,-11,7,5,2,9,7,6,-2,-10,6,-9,-12,-14,5,0,7,3,-10,-9,-12,-7,9,-1,-15,-10,-6,3,0,-12,-14,-1,4,3,1,4,-2,-12,5,-10,-13,-6,-12,-7,-4,-12,2,-3,2,-1,9,-4,-16,-7,-7,-1,4,-4,-4,-5,-13,5,-13,9,-10,8,-12,5,1,-1,-13,2,1,-9,-3,-11,-8,5,8,-13,5,-4,-10,-7,9,-2,-10,3,-11,8,-3,3,3,1,-5,4,-12,-3,4,-1,4,-13,-2,-13,-4,-6,6,4,-16,-1,7,5,-1,-6,1,0,-6,6,2,-12,1,10,-9,-12,-10,-9,10,4,6,-7,0,3,9,-8,5,4,8,4,4,-1,-9,-12,-1,-1,-11,-10,-4,-1,-7,-2,-11,3,-9,8,11,6,5,-9,0,4,-13,8,9,7,-1,-4,-5,7,-13,-9,-6,-6,-4,-3,6,-5,1,0,-7,0,-7,-3,-2,2,6,-9,4,-13,-11,0,-12,-3,-8,-1,0,-13,-5,-3,-8,-2,10,-9,-10,7,-12,-3,-4,10,11,9,6,4,-5,3,-5,-11,5,-13,-4,6,-11,8,5,-10,-3,-6,-6,1,10,8,6,-1,-9,5,-10,0,-11,-7,9,-8,6,-9,2,11,1,10,-5,6,-7,7,-11,-1,7,-3,3,-7,-1,-6,5,-1,8,5,-10,5,10,-5,3,-9,-11,-1,4,4,-9,-2,-2,-13,5,2,2,4,3,-4,-2,-1,-14,-6,6,-3,1,-5,-10,8,-10,-10,0,-3,1,-7,-3,-12,-2,-1,-9,-16,1,-3,7,0,8,-3,-7,2,10,7,7,-10,-5,-2,-4,-8,-3,-1,6,-1,9,0,-10,3,-4,7,7,-6,-2,-13,-12,1,-12,-14,-4,-16,-4,-8,6,-3,-10,7,-5,-12,6,-9,4,-4,-1,3,2,1,4,-2,2,5,-2,-4,8,-12,6,6,-13,-8,-6,2,4,-4,5,-4,-12,9,-1,-8,-4,1,9,-13,-6,0,-1,-9,1,-12,-11,-3,5,0,1,9,8,-5,-13,-11,2,-9,3,2,1,4,2,0,-13,-5,-8,-2,1,-6,-13,-11,-6,1,10,1,0,7,7,4,-5,9,5,-9,-13,2,2,6,9,9,5,-2,-2,-5,9,8,-10,2,-9,-10,-5,1,-5,-7,-6,4,-6,-6,6,3,-7,-8,-5,0,-10,-7,-1,6,-8,1,4,-13,-12,-5,-10,-9,-7,-10,1,-13,-13,8,0,2,-15,-8,-12,10,-6,-13,0,5,6,-14,-15,-11,-5,1,-5,-2,5,-8,-12,-1,9,-3,7,2,-5,-1,-3,0,-1,-2,6,-3,-3,0,7,5,8,4,-2,4,-2,0,-3,2,-4,6,-8,-12,-3,-2,0,2,6,-12,-13,-10,-5,-15,-6,-17,10,-12,-9,6,-2,6,-3,-6,-14,5,7,-13,-2,-5,-3,-4,0,11,2,-3,-7,-13,0,11,9,-10,-10,-13,-6,-8,-8,-12,5,-2,-13,10,-8,8,-3,-10,-5,4,-10,3,-2,8,-16,6,2,-13,-1,-4,6,-5,-8,0,6,-2,-12,2,7,3,-9,-6,5,5,-5,-3,7,11,6,1,2,-3,-5,9,5,-10,2,-9,-3,7,9,-3,9,-11,2,-3,4,7,1,-13,-2,-6,-8,-4,7,5,-11,7,5,-9,-4,-12,-10,-4,-12,9,1,-1,-4,3,-6,-14,-3,-10,-2,-10,-11,-12,-11,-1,-3,6,-13,-8,-11,-8,-13,-2,1,-10,-1,9,6,11,7,1,10,0,-2,-9,0,-3,-1,8,-13,2,-1,7,8,-11,-1,0,-7,-2,-9,11,5,10,-12,5,-2,1,-3,-10,0,-9,-12,9,3,4,0,5,2,-5,-13,7,-8,-8,-7,-3,8,-5,9,4,-5,-10,1,11,-4,10,-11,2,-10,-2,7,-6,1,-12,-3,-10,-13,-13,-2,7,-7,-3,-12,-10,-1,10,-2,9,-7,-11,-7,-4,-8,2,-4,-10,-10,-3,3,-12,-5,-7,-2,4,-4,4,-13,-4,-10,-5,11,-8,4,10,4,-1,-6,6,6,8,4,-6,0,-6,-1,-12,-7,-11,-7,-2,8,9,2,10,10,-5,5,-5,-7,-3,-6,-11,-10,-5,-11,6,-10,-11,9,-5,11,2,9,-9,4,0,11,8,-1,-1,8,-8,-9,-7,-10,1,-12,2,-2,0,3,9,9,-8,-11,11,-9,7,10,-4,-4,9,-15,9,5,3,-8,5,8,-8,8,-1,-10,0,-13,11,-5,-13,-7,2,1,4,-1,-1,-9,10,4,-1,7,-11,-1,5,10,-10,4,6,6,5,-11,7,8,-4,5,-7,-11,0,-12,-12,4,-15,7,-7,-1,5,-9,-5,-4,6,-10,2,6,3,1,3,-7,-14,-2,-8,8,9,1,-7,3,4,-7,-9,2,10,-8,-5,-2,0,0,-4,-1,6,-7,-5,8,-6,-12,4,-9,-13,-1,1,-7,-11,3,6,-2,-10,-2,8,-6,4,-3,-2,-5,-7,2,-13,-8,5,11,-10,-9,1,-16,-18,3,-5,4,6,2,8,-2,-9,0,9,10,2,1,-4,5,-6,0,-8,-4,1,-2,-7,-13,-2,5,-9,2,-13,-10,-10,11,-11,9,6,10,1,-12,10,-7,-8,4,-5,-11,-12,0,4,8,-5,-9,-11,1,-5,-3,-8,-14,2,-3,9,3,-3,4,-4,-12,},

                    {-7,6,0,-1,-21,9,-9,-5,-13,6,3,-7,0,7,1,-11,-11,-7,4,0,10,-23,-2,-2,-3,10,20,-24,-3,-3,-4,10,-15,-15,-31,-8,-13,0,-5,18,3,8,7,-9,11,28,-10,-12,0,-14,-13,1,-46,-14,14,-14,-15,12,-37,4,-3,-4,-4,-3,-18,-10,-12,0,-16,-4,-11,-2,9,-14,-31,1,13,-1,16,-1,-10,-6,-20,-4,-8,-4,-9,-16,-20,21,-9,14,24,-4,0,3,-20,-7,-7,-27,-6,-20,7,-11,-27,-14,-7,-15,-7,-25,13,-2,9,-6,-5,1,34,-8,-5,4,7,-12,-3,7,-4,-6,-3,-7,-4,26,-1,4,-15,1,7,15,19,-16,-11,16,2,-14,17,6,-2,3,4,30,24,5,10,-19,-19,20,15,3,4,2,-19,1,-30,-6,-10,7,-24,20,-39,-9,6,13,8,23,-18,10,5,3,-1,-11,1,-8,-20,-14,4,19,0,10,-15,-22,-11,-1,-27,-29,10,21,-16,1,-7,-6,-6,-17,3,-12,-25,-30,-14,-3,-26,8,-2,-4,-4,9,-16,-7,7,-15,13,-25,45,14,16,1,-1,-16,-13,8,-15,8,-10,-26,-7,3,-18,-4,-9,-13,-18,12,-13,3,-6,-6,-3,-8,-9,1,-1,-5,-8,1,-20,8,1,-15,13,10,8,-8,11,-14,24,4,-15,5,10,-5,7,12,-14,-8,-3,-10,-2,11,5,6,-19,11,-3,-5,14,25,-8,-11,-5,2,4,11,4,-32,7,-11,3,18,10,-13,-10,-9,-6,-15,23,17,18,-6,-12,-19,-23,-5,-9,19,-1,3,-13,10,32,-11,-8,-7,15,-25,-22,0,0,-18,3,-21,11,-13,28,6,-11,-26,-16,-26,-12,-5,7,7,14,-2,-24,-3,-24,-30,0,-28,2,-5,-11,-8,-14,-15,-4,-7,9,-6,4,-5,-18,13,3,9,13,17,9,10,-17,-21,-29,2,-18,-5,-1,20,-24,19,-23,-3,9,-28,-15,-13,-20,-23,-16,6,-7,-11,-18,-2,3,6,-42,18,-15,-9,4,-19,-4,-19,-22,-1,-11,-9,1,-11,-20,-22,14,-23,-9,-10,-27,-41,7,-11,6,5,-9,-1,-10,7,-6,5,-20,1,-9,-9,-39,-1,11,-28,7,-18,6,-17,-11,-8,1,3,5,-39,-2,-33,2,27,14,-19,-17,-25,-3,-14,18,-10,-17,-20,-11,0,7,-6,-26,-16,-5,-7,-11,-15,-8,-3,10,-11,5,13,19,7,3,-5,-18,0,-15,-11,6,-9,-19,21,-18,14,-8,-1,-13,-6,-14,7,-14,-5,-11,-3,-13,21,2,-5,-5,31,-4,-4,5,11,-1,-12,-9,2,-9,5,-8,12,12,3,-7,1,3,20,-31,-18,-18,2,-27,-1,-22,-8,5,-1,6,1,-28,-6,2,-1,4,-13,-7,0,-3,-11,24,-2,8,7,-4,-31,28,-24,4,-10,10,-6,23,3,-29,-44,-15,-20,-19,-8,-28,-19,5,21,-22,-15,-4,-3,-3,-18,8,4,-11,-10,-3,-2,0,-5,3,-8,-6,-24,9,-11,-15,-15,2,4,-5,-24,-12,-11,-8,8,-3,0,-9,-8,-8,5,-20,-13,-6,-14,-13,7,-13,-5,-12,-13,5,-34,-16,-11,-16,-18,9,-7,9,-22,-30,-14,-20,-16,-17,-9,-7,-4,-13,30,13,-11,7,-8,-33,-32,-23,-1,-5,6,-25,-7,8,-3,20,-14,9,-7,14,15,7,-15,-6,-25,18,-10,15,-37,4,-51,-5,-24,-3,-34,-17,-46,13,-10,3,0,-12,-7,-4,-24,-3,5,13,-9,17,-12,-9,-16,-15,-3,-11,6,-6,2,8,-17,14,-11,-14,-23,-5,-20,20,-14,-4,-33,-5,-16,16,3,7,-9,-10,-24,-5,-3,-13,1,8,-19,4,-7,11,-18,-8,-3,9,42,12,-26,-16,-25,-31,-24,-20,-14,20,3,12,4,-1,-7,-4,-18,-20,0,-42,-4,-17,-5,-23,-3,-10,-7,-18,-7,-9,-7,-12,-19,0,-15,2,3,-7,-6,-9,-22,-16,-6,4,-2,-1,23,38,-2,-16,-18,-3,-17,-1,-10,-9,-1,9,-15,15,-2,-6,-7,-12,8,-3,-10,-6,-7,11,-12,-11,25,11,2,1,-17,-1,21,13,-11,7,-1,-25,14,-29,-2,-9,-14,-10,13,-16,15,13,8,1,-9,-16,4,13,-8,-3,22,10,7,-2,-24,-16,2,10,16,6,1,-10,8,1,2,6,-26,-5,-9,-16,6,-5,-11,-9,-18,-6,-16,-15,11,12,2,-20,7,-2,-16,-2,10,10,-3,-11,-23,-2,20,16,18,-9,4,-28,-12,-14,-25,6,10,14,-8,-14,-2,15,-3,-24,1,-17,1,-13,0,-28,-16,2,6,4,-4,0,-9,-4,-6,6,-11,20,-10,20,-2,-4,1,-22,0,-19,0,6,1,-16,-5,-18,-20,1,1,13,-1,-3,-7,-5,9,-2,-15,-10,-5,-8,-5,-25,0,14,-27,11,-10,19,1,4,-18,8,9,-11,-8,14,-6,14,5,15,14,-4,-10,-6,-7,-7,7,-24,-17,-9,-17,6,16,-10,-10,-10,-16,3,-15,-25,2,6,-13,-38,-24,-4,6,16,0,3,1,-27,-1,0,-6,3,8,-14,0,-8,-10,12,13,22,-13,-13,9,25,-13,18,-31,8,-24,-3,-24,4,5,-2,5,0,10,6,-3,-2,-14,-2,32,-9,-1,6,-17,-10,21,-16,7,16,-21,-32,1,-13,-2,-2,-7,-5,29,-12,18,-9,6,3,24,-16,1,5,-11,-3,-9,-22,3,1,-2,-3,-18,-9,-3,7,-12,-10,-7,9,-8,4,7,-13,-9,-10,7,-14,4,0,1,-9,-3,-13,4,-2,-19,2,-4,-14,-22,10,11,13,11,10,-23,-28,-23,12,-23,-13,-30,11,7,-35,-31,-21,17,-21,12,-38,-13,-3,-15,-17,-20,-15,-1,-14,-2,10,-8,-2,-15,-5,12,25,34,17,7,-1,-26,-10,0,-12,1,2,-19,2,-21,12,4,-13,-25,17,-29,13,21,-12,2,-3,-6,34,2,-6,-4,10,-17,7,10,},

                    {-7,-16,6,10,-19,-4,9,23,-21,-17,20,43,7,4,12,8,5,-6,4,-12,-14,-8,6,36,-39,-6,-28,10,26,-10,-5,31,19,5,28,-38,-33,38,25,4,17,23,-7,9,25,25,31,30,-1,2,80,-22,-24,-62,-38,3,0,-62,9,-22,-29,13,-29,-4,19,18,-25,41,17,42,32,1,3,11,-5,-9,-5,22,40,21,-24,-25,35,9,-21,-10,-15,-16,-20,-67,-12,-18,-20,4,-3,44,-21,-39,39,-12,16,20,-6,36,17,-6,46,24,-5,-18,42,5,7,7,39,22,-58,-28,-35,5,16,-20,-11,29,1,-4,-27,13,-7,1,-7,-2,6,13,14,-1,-16,6,-25,-25,24,12,24,0,4,36,32,3,-18,36,7,18,28,27,45,9,21,-14,46,5,-6,-35,8,12,-22,-45,2,-6,9,-31,-33,-23,8,-1,-12,13,-1,44,48,21,-24,-8,-51,-11,20,7,4,23,-8,5,13,19,11,27,15,37,25,3,49,38,-3,13,22,-46,2,25,-10,7,12,0,-16,30,-1,-12,-1,-29,-11,40,26,15,19,5,13,17,18,24,31,-9,16,24,16,-2,13,-32,11,-5,-15,-48,2,27,-3,-19,-31,-2,29,15,8,14,-13,3,0,-12,-4,-24,26,-9,14,20,31,4,-12,3,-28,-46,11,1,-26,34,0,-26,-4,22,-1,14,4,2,0,3,-4,-16,-9,-10,-30,0,21,-41,-15,-26,-2,19,40,6,8,31,27,10,-3,-28,-3,23,5,34,-5,-1,33,7,32,-31,-19,-7,39,39,-18,-6,7,13,19,-1,42,-31,29,7,-44,-45,1,-32,6,-10,11,48,5,-14,-14,-17,-14,48,-17,15,33,25,-17,-33,-8,28,26,26,-34,-6,25,36,22,3,13,-8,-28,-15,-10,29,-2,-16,-11,-12,6,-23,19,19,-28,14,-33,-4,49,26,10,1,20,20,-53,-12,5,12,-3,-10,-25,-30,-28,-17,1,11,18,21,-31,5,55,55,38,33,-11,8,1,3,7,14,32,40,-3,-26,-19,-17,18,25,-15,-31,26,-29,30,22,-14,24,48,38,15,1,29,19,7,5,43,-29,23,1,-35,-39,-14,-1,13,7,-5,1,-11,6,-8,-6,-4,39,-7,19,9,24,-12,-8,9,5,-31,4,-11,4,-29,0,-19,-3,15,30,-21,32,5,-2,-2,3,-1,-2,-37,15,32,8,12,16,-31,24,21,27,-16,19,38,8,-1,-11,-8,-20,-6,-27,33,61,-31,-26,-28,3,34,6,21,8,-15,-29,28,14,11,23,19,-17,-20,26,-11,20,-16,27,32,10,0,1,5,28,25,-31,-7,16,37,-28,-17,-15,10,-32,-19,-39,-12,15,-1,-33,-61,19,19,33,-4,22,18,10,-13,22,-7,-20,-22,5,-11,-5,-8,-11,-15,51,5,7,-22,37,-11,6,26,9,19,12,-9,9,20,34,-52,27,-12,-13,2,-35,10,-21,-40,-19,12,1,6,-7,-29,-28,-17,11,10,1,-26,25,20,-4,-2,-20,-14,18,35,-33,24,22,28,10,-2,-5,-22,8,8,-9,5,-36,-7,-2,-11,-7,7,15,-2,31,5,21,3,-25,6,14,-19,16,8,46,-9,16,50,44,33,17,-23,33,12,0,24,-7,20,32,5,-23,-23,-23,-3,-25,27,2,24,22,0,-33,27,47,48,30,-3,-4,16,19,-56,-24,-16,2,5,2,-26,4,-13,-13,-42,45,33,12,-23,17,-51,1,-1,-3,-4,28,29,-14,9,14,19,-5,9,15,13,24,20,5,-14,-11,-9,-36,-24,15,12,38,40,21,-3,-5,-24,-16,-13,13,-36,-5,-17,-11,-3,17,13,4,1,4,-31,12,-17,-27,-54,22,32,18,14,-17,-11,41,34,24,1,-47,7,28,-13,-19,30,5,-27,-10,19,8,-3,-12,9,-10,-28,-37,-8,-18,-17,-16,-2,21,21,21,-9,-18,-11,37,0,-18,-18,13,-20,40,3,6,-8,-18,-53,-48,3,-7,-30,-2,20,33,-18,-11,-6,-5,8,11,16,-11,-14,-8,22,8,-3,0,4,11,52,40,-7,20,10,19,-26,-9,-12,-2,-6,-34,-12,55,7,-5,-1,26,19,27,-12,-4,17,-23,6,-4,-12,-7,-27,18,9,13,4,1,-23,5,33,27,-12,-8,27,-13,-51,-21,-11,-10,-53,-7,-22,-27,-31,4,-63,-2,72,-20,-11,-23,14,20,35,-18,6,13,-34,-39,35,49,-19,-1,-4,-2,20,14,-15,17,-17,13,19,1,-10,3,-25,37,31,-10,-25,16,36,26,23,-8,-17,5,1,-15,-6,-63,7,-15,2,-35,20,53,-12,29,-32,0,4,55,-4,18,12,6,-53,-50,4,-26,-47,1,-10,31,6,20,-4,12,0,14,0,-1,40,25,69,19,-3,-10,14,-20,-35,46,-13,-20,7,21,-13,2,5,-10,54,37,-13,20,9,-1,-31,-9,-42,-27,18,-39,-51,15,30,2,3,17,17,28,15,58,-17,14,-5,-18,16,41,0,-1,-16,-5,27,40,3,8,-15,50,4,8,-11,-14,-32,-18,-3,3,11,18,-18,5,33,18,6,53,-19,26,15,30,-10,3,-11,-4,-6,-11,5,29,36,-28,-53,-43,9,-10,1,-21,-17,-3,1,13,61,8,28,9,-21,-26,-11,-39,4,-23,31,13,-13,-26,34,0,-2,-15,10,6,15,28,48,41,-16,0,-4,13,33,-13,-19,24,33,21,-43,-2,5,1,8,-15,11,-10,12,9,33,9,12,-34,6,1,5,-16,-19,-22,-23,-11,6,9,-5,-29,20,13,81,27,-40,46,-2,-11,-14,-8,45,24,-2,7,-32,-31,3,79,14,-14,28,37,-10,1,9,18,30,18,22,8,-15,-13,-2,-4,17,4,26,7,-29,-13,-15,33,-10,-18,5,-17,-8,4,3,27,31,-5,-20,0,-29,-11,6,-11,-23,0,25,-16,-12,7,},

                    {11,16,8,-11,9,-11,-13,33,7,11,34,23,-5,-10,-10,43,17,20,-20,11,-14,-22,5,6,-67,10,-28,5,-23,-14,27,34,-24,20,-26,-56,-5,-18,-12,-12,-37,-13,16,-61,-72,-21,53,7,-42,-66,1,-26,55,16,6,1,36,-4,7,-12,0,22,4,-15,38,15,-50,4,24,29,30,4,-9,-2,12,1,3,-50,44,0,-7,0,28,26,-35,0,-15,37,67,-18,-27,-8,21,21,6,-25,-70,13,3,-6,20,-32,27,25,-7,22,-19,-14,-22,-26,-5,18,4,32,11,32,20,-5,-27,-2,-7,22,45,-1,23,7,-31,-29,20,-1,21,1,-18,0,10,-23,-13,2,22,-18,2,14,17,-3,-14,4,-25,-46,-18,-2,14,-27,-89,1,25,20,-9,-84,1,-22,38,1,23,-26,49,-27,-13,-9,-14,28,12,-11,5,23,-7,15,-21,17,12,10,-21,-17,-41,-45,-22,-36,3,33,35,35,-6,-37,7,53,-13,15,12,50,43,1,-4,-4,22,13,-17,15,-2,-38,6,9,-55,-9,-8,16,-1,-2,-29,-1,-40,-41,-29,-12,-24,-21,-8,-8,-2,0,-37,-1,38,34,-18,-21,-5,2,26,3,-13,-10,-9,6,7,20,11,7,-30,-6,-2,6,19,4,-18,-35,4,1,25,-8,8,19,22,-14,1,21,-15,21,45,9,-35,0,-34,-7,14,7,-18,-3,-6,-32,-5,22,-16,-49,1,-7,-14,14,3,-45,-12,-16,23,25,9,17,33,-4,15,46,4,6,22,78,24,29,12,27,25,-37,-20,-3,19,6,-28,-44,-20,-41,-13,-17,29,1,8,-25,-42,-29,-3,-15,35,-7,15,-23,-12,64,15,-12,-31,-34,6,7,-10,8,-23,-10,-19,27,63,-7,-14,-58,-31,27,-8,-11,7,15,14,-3,33,30,-6,-11,24,-9,-7,-42,6,-12,-60,9,25,-26,-5,-10,-9,-7,-7,1,24,5,10,-12,10,-19,-35,-51,-11,35,14,-44,-20,26,-3,-1,25,-5,-5,16,-9,-6,26,26,1,0,9,5,5,9,13,-6,37,-2,43,7,-3,-15,18,-25,37,-21,38,40,-16,-23,-18,19,28,19,3,-16,-22,3,-46,-29,24,-10,37,31,21,4,16,22,25,22,34,17,57,19,-4,1,67,27,-22,-35,-8,-5,42,-4,-53,-72,-20,-8,-27,-32,7,7,12,0,17,-57,6,14,-21,-11,-35,-19,-27,-4,10,9,-32,-19,-34,7,-5,40,0,-10,-40,0,-20,-6,-7,3,-25,11,-12,-8,14,-1,1,9,-6,-9,-24,-12,34,2,36,29,35,-3,21,30,0,10,23,22,12,-28,-3,-1,37,-9,4,-41,-6,-26,2,-13,12,5,-23,-11,-5,-6,16,8,-43,18,3,23,2,9,52,38,13,10,27,2,7,0,-26,-4,7,57,8,17,5,43,-21,4,22,-32,35,-4,-7,-15,8,-24,22,-24,9,2,-1,20,-32,-41,-19,-34,32,25,2,16,9,13,24,16,-2,-33,40,34,20,28,-4,1,-10,16,30,-6,34,-1,-49,-24,-11,-17,17,-21,19,-10,-6,-7,-25,-25,-7,10,37,6,-7,-6,8,-7,13,31,38,33,-10,33,11,-4,-12,-54,40,58,-1,-5,-53,24,7,28,10,-12,-2,-34,-23,0,-1,-46,-40,-39,-7,-17,-11,-61,-16,16,-18,4,-14,-55,18,27,-27,-6,17,-36,-8,9,-38,-3,-5,-32,-46,-4,-12,-5,5,11,2,21,21,-5,25,59,8,0,1,-19,11,7,-10,8,-8,6,-13,-23,2,17,-20,22,36,9,-56,12,-40,-19,-12,-24,-9,38,-24,-4,-5,-2,4,-16,-10,-3,12,22,21,-37,9,-7,20,-17,-28,15,28,48,5,-44,-43,11,24,15,8,-51,-28,-18,9,-7,4,6,27,17,-15,-27,-37,8,16,-19,-11,-5,3,-17,-13,-8,8,-7,2,-45,-36,25,10,48,31,2,1,-35,11,-1,1,14,66,18,3,-15,-14,35,44,-24,-35,-39,-17,-44,-13,-4,-48,-3,-23,-7,-1,-19,-3,22,5,-6,6,-31,7,7,-1,3,17,9,-33,5,-6,-10,7,31,20,-27,-13,6,18,-10,26,8,-28,-15,-1,0,12,26,6,-7,-7,42,-25,21,-29,-21,-8,-32,20,33,-15,-26,-48,-5,-12,7,-32,-45,-6,-33,-38,-14,-26,4,14,37,-27,2,-29,-11,-3,-3,54,-8,38,-22,-16,-16,-12,-28,-7,-14,-67,-21,-9,25,19,29,24,-15,7,42,30,29,-21,-10,8,20,4,13,33,-15,-40,-19,16,17,10,-20,-42,-7,-7,0,-11,-48,11,35,-21,-18,-23,-32,2,7,-8,9,-20,-9,54,-19,4,38,64,38,-17,-20,24,-5,-20,-41,-41,26,10,-11,30,38,24,-7,29,15,17,-5,-4,-4,-7,-1,-9,-40,7,-16,-16,-85,17,25,10,-34,-15,1,45,26,12,-33,23,-32,11,-17,-2,-6,6,0,0,0,-8,-32,-24,7,-7,20,25,24,57,33,20,-13,30,13,26,12,22,-6,19,-3,10,9,57,8,-27,-22,33,-19,-43,-33,-14,-8,-13,-21,-11,-16,24,13,-29,-28,-22,-49,2,-31,-29,-13,-36,-9,15,21,41,-16,0,-13,32,-10,-3,45,-7,-15,2,6,25,10,2,-4,6,-12,-5,-24,33,-9,30,15,9,15,55,-9,10,6,-23,-20,-4,9,19,37,44,15,16,26,5,-13,-2,22,46,-9,-38,-29,17,47,44,4,5,-1,22,-25,14,-24,21,-26,18,-17,38,23,7,21,-13,-42,-20,-33,-7,-4,-53,-32,7,4,-22,5,-7,-17,56,55,32,57,55,-26,-18,13,12,11,-4,-46,-8,24,-13,2,-22,19,15,8,-4,17,-9,3,28,-14,2,47,-7,2,-5,-11,-22,-3,47,15,-39,27,-31,14,-3,-29,-9,37,-17,-7,2,8,0,-18,2,-38,19,27,20,-30,},

                    {5,0,18,-38,-12,11,9,13,18,-9,2,-21,-15,7,-49,3,19,11,-35,35,26,25,9,-14,-1,32,10,5,14,19,-7,27,-16,-8,14,32,10,-8,-19,-52,-54,7,14,39,-37,4,30,-5,44,16,-46,15,48,35,-7,-13,-58,29,3,-3,-5,-18,-9,-2,6,-6,31,-36,-7,7,14,11,13,7,7,-24,-23,-22,-11,11,18,15,-22,6,33,13,4,49,62,30,-25,9,40,59,11,5,-9,48,9,27,-8,-5,15,-43,-22,-1,-12,-8,-62,-22,9,24,42,23,-31,-5,23,7,24,0,-22,23,31,-9,-11,-11,16,-3,40,30,15,8,20,-1,-14,21,12,38,-8,25,1,15,5,13,-2,-9,-13,-64,-17,-29,7,11,-42,5,11,12,13,-2,1,-11,25,14,-10,-5,0,-4,-7,-19,-13,1,-15,-1,-25,9,7,-35,-30,14,-26,-8,13,-4,38,-9,-74,-5,52,45,50,-30,-19,-29,17,1,-24,-6,12,32,-3,-23,12,-2,15,12,-20,-75,-22,-4,10,19,15,-2,27,-6,-3,13,-16,-4,-49,-56,-32,-46,-25,-17,-31,5,3,2,-10,-13,-31,7,3,-8,14,0,24,22,12,-29,-22,38,17,17,17,15,15,12,-3,2,-1,25,-9,-26,-7,30,24,-20,-34,-2,23,47,45,-8,2,-3,41,14,-11,-41,50,-7,29,-1,-28,-32,25,0,-5,1,10,-18,6,0,-35,34,38,33,20,54,16,35,-5,1,-7,-27,-13,22,-2,2,27,-27,-8,-46,-45,16,-21,28,11,3,20,13,23,-13,-3,-11,-6,8,25,23,-7,3,29,16,-5,65,58,8,6,-17,19,31,50,22,5,-28,15,0,30,0,9,7,2,-55,0,-2,-27,11,-17,-18,-29,-17,4,31,-3,8,-11,4,24,5,-1,24,-21,-55,-32,-18,63,23,37,2,-29,-44,-29,30,9,-22,56,0,-12,0,28,21,20,-1,-11,9,27,-36,-14,3,-7,-7,-13,-10,-10,-25,-52,-22,13,24,6,13,-20,-36,-6,25,24,20,15,-5,11,18,-24,2,30,-2,14,-15,6,-11,-6,-3,-28,-9,2,8,-5,0,2,-5,31,70,-5,62,29,9,-16,-26,-15,27,14,-10,8,-25,-14,-3,-28,-4,52,25,-1,0,2,39,39,2,5,-27,22,23,-4,11,-9,0,9,4,11,19,13,2,-11,-39,-39,4,-11,-6,-15,-35,-3,-25,19,-5,-25,-17,16,-33,-2,21,14,16,-26,-26,-8,36,14,-22,-35,-13,-16,37,-3,38,-50,-29,11,18,-50,-14,-7,-14,-9,-30,-24,-52,6,11,12,3,0,-25,34,-3,7,13,11,-3,6,-25,2,-11,-13,-2,-6,-8,9,29,29,15,-8,-3,29,47,42,55,-23,-9,9,13,44,-11,-19,-23,-4,-1,4,-50,3,-23,21,6,24,17,-6,-19,8,2,17,14,35,13,26,-6,-16,13,-20,7,24,51,41,69,4,-13,18,-4,-2,17,-6,-15,-9,-22,18,-8,-37,-9,21,20,42,24,-11,-1,-5,-26,-9,5,0,11,16,8,-11,5,16,10,27,-4,15,43,10,-21,3,-22,17,10,-22,-23,31,19,-11,-17,-16,-26,10,-12,-11,-20,-69,-1,-11,-6,0,19,-10,-10,30,9,37,16,39,32,26,0,15,-2,-25,-25,-4,-5,-35,11,15,1,-27,-8,-26,-27,20,31,-8,-1,-18,-48,-14,-12,21,27,-24,11,-1,1,40,32,18,35,8,21,8,-44,-22,37,2,-7,-26,1,-2,8,-5,9,-31,11,3,-27,-7,2,41,11,1,1,-11,-23,8,19,9,-6,22,-10,-5,-1,8,16,53,4,-3,-10,34,-8,27,-22,19,17,-19,-63,-60,-26,-1,20,12,-60,-55,-21,10,17,-7,3,9,27,21,-11,18,-3,-4,2,16,32,8,-3,35,37,3,-9,7,-57,-48,-19,15,46,20,1,-3,-23,11,-13,-18,14,62,10,-1,-5,-7,45,48,18,-9,19,13,14,-3,10,18,10,20,-4,-4,-20,-4,28,11,11,-9,15,12,13,-7,-7,-37,3,-17,-6,-36,-3,14,27,8,10,9,15,-7,-23,-6,3,15,16,-20,-34,1,0,20,-5,-10,24,13,10,-10,-71,9,20,27,0,-11,-37,-43,-47,23,6,-25,-43,42,52,-3,7,4,17,18,16,7,29,39,17,-27,-22,-12,-4,-11,-7,-10,9,27,19,30,7,-37,-2,13,13,-1,18,-5,-17,5,-5,29,-18,-5,13,5,3,23,22,-22,-15,16,-18,-12,5,-17,54,24,2,9,-4,30,18,6,21,-28,-9,-44,13,1,-24,35,5,3,-29,3,-12,10,19,74,41,-10,13,51,42,7,11,-1,24,29,-7,5,22,4,18,-43,-36,-26,-25,-5,12,-14,40,-20,-52,10,-31,-4,-45,30,16,1,8,-30,-22,56,-11,4,-26,-1,-14,36,21,-12,-10,46,3,-23,2,9,-11,-1,3,6,-12,8,17,15,18,-7,3,-27,18,3,5,-25,-61,17,7,-4,-12,7,12,-5,9,36,29,8,6,21,0,9,-31,-18,-26,23,1,-10,-17,16,8,-16,14,-27,6,2,23,2,-48,-31,22,26,4,45,4,7,41,12,2,57,7,-7,-14,-6,-7,20,26,-5,2,21,14,50,2,-10,24,32,26,-53,-48,-5,15,-9,12,-34,-18,-17,-28,-5,0,13,-3,14,41,-13,-14,38,-14,49,37,53,42,-5,14,17,10,-23,36,1,30,-11,29,13,34,28,15,19,-30,-56,-30,8,53,19,13,-38,6,40,11,-19,1,42,60,-11,-24,-66,-36,20,3,24,-40,-50,-30,-28,-18,46,-20,-4,-34,7,29,-26,6,3,17,8,-12,-23,14,-20,0,7,-7,-6,3,12,-11,-1,5,6,11,-16,-23,-4,-4,7,3,12,-43,9,-1,-20,-5,10,40,39,12,},

                    {-23,1,-2,-2,-3,-2,-14,-19,-10,7,-1,50,11,-2,-13,36,-53,-38,16,-21,-18,-12,-12,32,29,23,16,0,34,7,19,-21,25,7,28,5,-4,-29,-26,-20,-26,0,19,-21,4,-35,-50,-15,-41,-3,30,-5,-24,5,8,-10,15,-5,12,9,35,32,-2,19,11,31,25,79,23,-27,-36,-2,11,17,24,4,-10,14,-14,16,-28,-16,-16,2,7,12,-48,-60,-87,-44,0,21,-17,-28,-33,35,31,-8,-10,16,-7,18,5,25,5,-10,31,4,-4,4,-39,-11,-31,-17,-4,4,-13,31,10,18,38,-7,-14,-3,-3,-14,-7,6,-50,3,15,-5,-6,19,14,33,-6,-10,9,25,-25,25,5,-3,6,-54,-11,-13,-45,1,20,-20,20,7,-50,-47,36,8,12,12,-1,-2,3,8,-16,20,40,28,19,21,-25,11,21,9,22,37,26,-9,-18,10,3,-1,-18,17,52,15,17,-39,-23,36,4,22,40,-9,36,-4,3,6,15,2,-4,-5,-36,-38,8,37,-38,-7,4,19,16,9,10,3,-6,-10,-11,-28,30,7,13,49,-34,-20,56,4,23,39,-1,15,52,24,19,45,2,17,-1,-18,3,39,3,28,-5,-18,-23,-20,0,42,23,-29,-28,-40,-16,-3,4,-22,6,1,-21,-7,1,-7,25,15,26,2,-32,14,30,44,3,11,-14,-6,28,12,10,14,-8,-48,2,36,-4,21,6,-14,-9,14,1,0,-2,4,9,17,-34,-10,5,2,-18,6,5,23,9,4,-3,1,-2,-18,25,-30,-40,-42,9,4,0,17,25,2,-6,-26,36,8,-13,-5,-15,24,0,14,0,47,-10,-47,-27,-1,27,47,-9,-25,-29,43,9,18,6,24,1,11,1,25,41,0,-11,3,16,14,31,0,-31,3,-40,-6,20,-11,4,4,-33,16,-6,-8,-2,21,-14,48,2,-16,6,20,-66,-15,-14,19,-14,17,38,39,27,4,7,55,30,0,22,50,4,-24,-30,-11,-3,-17,-24,10,0,-17,3,12,-4,12,15,4,24,11,-24,19,-2,7,1,39,-14,49,-7,-29,21,24,5,4,32,23,-4,10,11,0,26,-41,-16,31,10,35,-16,14,14,-19,-12,0,-6,22,29,25,-21,-37,-19,-28,1,-20,6,-26,-78,-19,51,41,-21,-36,20,12,46,1,-2,16,8,38,-28,-12,10,27,26,16,-27,26,32,5,-19,30,16,14,16,-1,-4,48,-9,2,-6,12,37,1,10,-13,12,18,26,28,23,53,-7,-30,-9,-8,-21,4,-7,-13,-4,21,-1,17,10,34,-32,-17,6,21,-3,5,-38,-3,38,-17,-4,32,38,45,-6,11,9,18,14,12,35,-13,41,0,17,-1,-36,-13,-53,-15,22,16,-26,-10,-32,51,11,-4,14,-5,42,9,-17,2,29,-10,-54,-40,-4,-35,2,5,-13,-13,15,15,11,17,-15,-6,-2,-30,-7,5,-35,7,5,10,-2,-5,-19,4,23,18,23,-35,-13,5,36,35,4,-13,-44,-31,-5,-14,23,2,-17,10,37,26,4,8,5,4,7,5,-16,15,-5,-6,-4,23,8,0,-15,8,29,10,-27,-45,-1,7,17,46,2,23,35,7,57,26,9,-12,-13,-4,-6,16,22,-24,-43,20,10,16,-13,2,0,10,-45,4,-4,27,47,15,-44,-41,18,9,11,63,17,3,25,-22,17,42,53,20,23,-2,26,-1,24,-9,-9,-2,-29,-29,-47,-19,-18,44,27,9,-10,25,-4,2,14,35,54,2,36,-23,-6,69,43,-27,29,-17,-15,-5,-10,10,5,-3,-7,0,-29,-30,7,21,-18,-18,-43,-15,7,-38,-31,24,-19,11,-1,-2,31,49,33,15,-31,-34,18,52,58,11,-5,-10,7,-31,-19,-10,9,-10,-22,-22,15,-6,1,-12,-1,4,14,5,3,6,-5,22,36,18,-9,-27,3,4,-9,13,1,20,32,-9,-58,22,-23,13,3,-81,-94,-32,16,57,-20,-13,13,-10,35,3,7,13,9,15,4,-1,-30,0,-22,-7,-4,-1,27,-6,-19,5,3,23,16,-4,-20,-2,-25,-10,-2,8,-7,10,-22,2,-8,9,15,27,7,11,21,-18,32,-41,-19,12,9,10,-31,-8,-37,1,26,6,21,28,15,-12,38,14,-27,4,11,7,-35,17,13,13,27,-18,9,20,20,6,18,60,-5,2,-24,-6,-25,3,5,1,15,51,40,-34,-33,-6,-9,22,31,0,-6,2,38,41,31,11,-12,-19,-11,-7,0,10,-40,-15,30,22,26,-6,10,18,-10,-11,-10,15,32,19,-5,21,-11,30,-6,-6,-15,46,18,34,-27,-29,-93,-42,4,38,-19,-35,-12,37,50,10,12,33,-7,-4,12,32,0,-8,15,11,5,21,60,16,-26,34,6,-24,29,36,-45,4,4,11,17,12,-41,4,-8,3,0,6,3,15,11,27,-12,-27,13,12,27,26,-7,28,-1,7,-1,-11,-14,-10,-18,21,26,5,-25,8,13,52,33,30,13,-41,-73,-32,7,8,-26,-46,-18,11,22,-1,-2,-3,38,17,-12,-16,-2,23,15,65,-11,0,-4,24,20,-9,28,1,25,35,31,40,-1,24,-32,0,-4,26,-5,19,-21,8,-6,7,-12,8,4,-1,-46,-2,-17,30,5,0,-29,-47,-10,0,-20,4,15,-1,19,22,27,30,13,-2,41,8,-10,-36,-30,8,-2,-3,-18,-15,-12,-36,-14,14,4,23,26,15,-21,-11,-19,9,21,-12,-13,-1,-26,-28,30,23,-8,-41,-26,2,-23,-21,4,-13,28,4,-70,-42,35,42,60,23,-35,-26,-7,30,31,1,29,26,29,38,31,13,-16,-13,3,-6,-7,-12,16,4,-12,16,64,10,21,27,30,-4,12,11,27,12,20,-7,7,20,19,16,15,2,-26,9,-5,17,14,23,-18,-31,-38,-16,},

                    {-1,-15,-21,30,28,4,11,-17,-4,-12,-13,12,-12,-36,-3,0,17,10,42,-25,-9,-20,3,63,44,-31,-19,-17,37,57,7,-5,-19,-25,-5,46,14,-35,13,7,51,10,-10,-44,11,15,26,15,21,-68,28,14,8,-21,54,10,35,-2,-6,-38,31,-25,55,9,-47,-71,50,48,37,-9,-21,-41,-15,-32,-13,6,29,28,-21,-39,-20,-1,9,19,-9,-41,18,-32,4,-5,52,34,7,-46,-22,27,59,14,-6,-24,-21,27,-12,27,-34,-79,0,4,24,23,-13,-22,-23,-21,48,-11,7,-1,-23,-47,24,9,-4,4,-24,20,-22,-15,2,4,-26,7,-8,-15,-13,-7,24,4,-4,-9,-3,-32,11,-6,12,-27,21,-1,17,13,-23,18,31,23,29,-6,-6,-69,-23,-2,12,-17,15,-29,31,13,17,-59,45,11,73,15,-1,-78,30,34,58,1,-35,-46,10,24,17,18,-13,-44,-18,-31,12,6,-6,-13,-28,0,53,19,-40,13,-7,40,14,21,6,36,23,32,-3,7,4,49,31,14,-15,-18,5,5,5,-25,47,45,24,38,24,-3,25,42,-22,45,11,-21,-6,11,-3,1,-30,-8,-14,35,-15,-27,-16,-69,-6,33,4,-41,0,-12,9,52,2,-9,-5,6,-22,1,-15,-1,36,20,20,8,-51,-42,7,15,6,10,-25,-58,-23,-9,2,7,2,-25,-1,-23,22,13,-3,-13,13,-20,7,16,51,0,-19,16,-12,-51,-47,-49,-37,11,20,-19,11,-11,-13,41,-27,1,7,4,4,22,-14,9,-13,-8,42,34,26,21,20,30,-14,3,27,14,18,4,0,2,-35,9,-49,-17,-30,-24,19,6,-16,16,-40,30,-2,16,16,34,-3,19,-3,2,-1,42,6,4,-3,10,11,30,-13,10,9,26,9,0,21,-3,-12,40,24,3,-19,-58,-18,25,33,57,-47,-49,-26,-13,28,22,0,18,26,13,8,44,15,1,14,-7,-3,25,16,38,29,10,-61,-25,37,5,-2,-2,11,-19,9,38,-11,-45,-18,-14,41,68,4,-30,-36,-39,12,-7,2,-26,-66,26,-8,12,38,-49,2,40,-19,14,1,30,76,58,33,6,-7,-23,13,2,49,-26,-13,5,5,3,7,-7,39,-8,-28,40,41,-3,7,-35,16,89,27,32,5,24,47,79,-1,4,-39,-18,-16,31,-25,-44,-1,7,32,-9,21,-28,4,18,34,30,-11,-22,-14,-4,25,18,8,-35,-22,-2,-21,-3,12,-21,21,31,-53,-24,39,-14,2,24,0,0,-30,-20,-25,-16,16,23,-23,-5,26,56,29,8,-10,-52,-1,6,32,-12,21,-35,-29,9,11,-2,-19,23,33,22,3,-8,-7,-20,16,8,-27,-29,-21,-12,-30,-36,22,-24,-15,17,-16,-16,-7,14,5,-9,8,3,-22,9,-9,-14,-15,34,-11,78,2,-15,-3,-1,-13,90,-5,-4,43,13,37,31,0,15,-15,-29,2,-32,-2,-3,-6,-44,-53,-63,-1,7,-14,-18,-25,-15,14,2,-23,8,-15,37,14,4,12,13,2,65,-4,-12,8,-2,36,56,29,-10,-17,-26,-2,16,-18,23,4,-11,1,-6,-13,29,27,19,-83,35,-8,38,40,3,-60,44,7,13,2,-18,24,65,33,6,-26,-22,21,33,-25,-33,-12,13,26,-5,-47,-16,12,50,21,27,-42,-4,4,63,29,9,-8,-19,28,41,9,-30,-27,12,33,-9,-55,-48,-23,-1,18,19,-11,-44,9,24,-10,3,-12,0,21,30,19,39,-36,-1,-19,2,-12,29,-30,-27,-51,-16,3,10,7,-3,-12,-6,17,7,-21,23,-14,-14,7,33,47,18,-12,2,-6,-7,-40,0,-11,3,7,34,34,-28,-1,20,10,-2,11,24,25,7,11,6,-13,18,7,0,-8,10,39,61,4,5,-16,5,29,38,14,24,-16,17,-1,-35,-5,-16,-32,-24,2,-5,14,-7,49,-9,-22,6,15,20,2,-24,21,11,24,20,1,10,14,50,6,23,-12,-32,-12,49,0,-11,-41,-22,-8,22,12,3,21,-4,17,20,14,-35,1,29,-5,-31,12,-11,0,20,3,-8,6,10,31,15,-30,4,1,0,5,11,-9,-22,-34,-51,-17,8,15,21,5,-22,0,31,21,26,-46,-38,-2,6,-2,59,-16,11,11,-5,11,13,3,-17,13,23,4,17,-10,43,20,1,10,-12,1,19,12,13,-16,-28,-14,-18,2,-24,-11,-48,16,8,5,-4,-39,-24,20,4,12,-23,15,34,7,21,7,2,20,32,24,7,-18,-13,46,48,-9,-46,10,18,27,-30,16,-25,-8,3,8,26,-7,-8,2,-13,-7,-27,45,12,30,-9,-20,-3,34,-15,12,-26,-44,4,-10,31,16,-40,-13,-26,11,0,-14,-22,26,17,-8,19,1,59,8,19,12,-32,10,-6,26,17,6,-25,11,4,7,-12,8,28,24,38,-7,-22,16,21,36,-13,0,-47,-29,-25,-26,-9,18,-9,-26,-23,-18,-18,7,10,-4,8,27,34,11,35,16,51,-24,17,-33,59,-8,21,40,17,9,91,-20,-11,10,-13,-46,18,5,-35,2,7,26,-16,46,29,72,40,-7,-31,6,-14,25,19,-4,-19,-3,-45,-18,-22,-23,-61,7,-26,-12,4,0,-22,21,-73,-21,39,0,-25,19,23,18,-3,9,-51,56,-3,6,9,-10,-58,6,1,-32,-11,-3,22,-8,-43,-26,-16,-1,38,6,-12,-10,29,18,23,-7,-35,56,4,-19,-2,-4,-17,-15,33,-3,-36,-36,-11,-17,0,30,55,-22,31,46,10,-20,-3,-10,19,20,13,18,-26,23,37,39,-11,-14,-4,-2,17,14,-12,8,-6,6,-18,10,9,-25,26,11,-17,25,33,-29,-9,-23,-19,-5,62,-6,-46,-32,-38,-11,58,-19,-55,-25,-8,-11,14,-1,-27,16,-15,15,18,11,-13,},

                    {-6,1,12,16,1,13,7,5,-5,5,-6,-1,0,48,16,-24,-3,-5,23,44,10,35,6,-12,16,24,23,-15,-26,-24,15,-16,24,16,-13,5,21,-30,-10,20,-25,-32,-18,17,26,-10,-16,-18,53,39,16,-3,17,19,3,5,27,-10,4,26,-12,-7,22,26,-2,25,-14,-46,22,7,-1,-2,0,-13,-19,-5,5,-16,-26,5,13,-14,15,-6,23,15,41,-24,2,54,18,-5,4,11,2,11,42,-29,0,9,-1,-18,-31,-22,8,26,17,-4,11,9,10,7,1,7,17,-29,32,4,4,14,6,-1,36,3,5,-13,-4,33,47,-39,-21,-15,26,5,-34,-34,4,-6,1,24,-22,6,13,3,9,-25,-20,-12,-19,-10,-4,23,30,-20,-3,-4,33,35,3,-13,32,23,-20,-4,34,18,24,3,18,-27,14,-5,-3,11,0,-21,50,-9,3,6,48,50,38,41,53,4,42,-68,-59,-67,3,6,10,-72,-56,-68,-74,7,-6,-9,13,1,15,11,13,7,33,60,-30,-7,22,25,26,22,32,10,1,10,26,9,31,10,30,15,-7,-12,18,-10,18,-6,8,-6,37,3,-10,-11,-15,-12,24,34,36,-18,0,5,3,25,-25,14,17,1,-8,6,21,21,7,9,-17,4,20,1,31,39,28,54,36,13,57,37,21,12,1,15,54,8,56,14,10,-27,-14,-3,-7,9,8,33,24,9,-7,8,2,-50,-24,-15,1,-28,22,12,-23,-35,18,-4,-21,-68,-31,-26,-42,-13,-19,-12,-3,-36,-22,-5,23,9,-13,-25,-27,17,-79,21,1,33,22,18,-18,-82,-58,-50,-9,36,16,-35,-20,8,7,39,3,-4,9,-6,42,4,10,-4,6,25,5,14,7,-2,21,-3,-14,-7,11,0,24,14,19,36,-7,14,21,33,23,2,47,0,-8,7,54,17,-2,21,28,0,12,15,4,39,11,-24,-10,-3,9,49,1,-25,-25,-31,19,1,18,-39,-4,-10,33,11,-5,-9,6,1,70,10,7,-12,15,23,-13,-31,-16,-14,-11,2,-1,-56,-63,-67,-71,-16,-16,-3,-12,-13,-80,-57,0,74,31,21,-32,-20,12,-35,-73,-29,-25,7,26,6,-30,-34,-40,3,-11,-11,6,-11,-28,-18,11,7,23,14,18,-12,1,28,7,7,-2,-49,15,-2,18,7,31,25,-27,-7,2,-1,-3,28,-8,-12,-3,3,35,13,41,30,26,-1,42,21,-10,29,13,-19,14,9,19,7,-25,-20,-9,24,-12,-15,17,-18,-9,-16,19,-8,-39,-47,-58,10,7,-35,-9,-9,14,-13,-36,12,33,-1,10,9,-3,21,62,8,19,4,11,29,6,-2,5,-15,-50,25,46,-13,-6,-1,-5,-65,0,-48,-37,-26,41,-2,9,-31,0,33,-7,-43,-7,-21,-33,-22,6,26,34,23,12,27,17,-9,-11,6,-2,-28,-14,11,-9,16,11,-16,12,-78,-28,-50,-18,1,48,-33,-46,-61,-17,18,-8,-45,-32,-55,-28,-19,8,5,31,20,-29,11,17,10,23,-3,-43,-11,1,10,3,6,4,5,68,8,6,23,27,14,44,-35,-14,-28,-36,-20,-5,-55,-77,-69,-67,-8,-5,-59,-82,-58,-71,5,2,-4,-9,17,-17,-17,-1,-20,-20,-39,-52,17,21,-17,-4,5,-53,-22,16,16,27,62,10,-24,4,-11,27,27,55,13,12,11,24,9,42,-1,0,-17,23,20,11,9,-19,2,-1,1,10,2,0,-14,-21,-13,39,-1,17,22,4,14,32,-5,5,-5,37,21,27,5,5,-1,2,11,33,-11,-4,-5,17,12,18,0,20,29,9,6,-8,8,23,12,-2,33,8,8,22,-61,-69,-43,-25,5,-7,-18,-27,5,-48,-9,13,15,53,51,16,8,1,-2,10,-11,-5,6,29,12,5,-7,3,-3,17,24,-16,-17,-18,2,8,-50,-45,-36,-14,24,6,26,-42,-66,-20,15,-17,10,30,22,29,16,17,26,31,-3,17,-26,-16,-13,-7,-7,28,35,8,11,-44,-4,-48,3,-13,6,23,-4,-2,-13,3,24,5,37,41,8,-8,13,7,-22,30,8,18,-4,-4,-23,-10,19,3,-29,10,20,-21,0,-37,-9,15,-16,12,44,1,-12,-13,22,58,1,40,30,11,-7,21,33,-24,49,42,-16,45,-30,16,26,19,-29,8,20,-13,11,-14,-19,30,5,46,3,25,19,15,16,25,-26,-38,-63,-47,14,-4,-28,-75,-89,-42,1,-5,-11,-8,32,-32,-2,21,19,8,6,1,12,35,26,0,8,18,-1,-11,-40,-17,-11,-16,25,46,-23,-3,25,10,14,-9,13,11,18,18,27,-12,25,1,-29,-3,-29,1,11,-26,-24,16,23,1,-7,-35,1,14,-14,3,-6,-50,16,-13,2,-1,19,-22,-9,-28,-13,-20,46,-33,-45,5,25,-30,32,33,-33,17,3,9,22,25,-19,-10,19,4,-7,38,7,-1,1,13,-24,-19,-9,-4,-19,12,1,-13,-23,-38,3,-18,-4,-33,-4,-4,-1,12,-17,-7,8,-9,7,23,-22,-12,13,0,-29,-44,-22,1,48,32,3,17,16,21,14,7,-2,6,20,-5,37,26,4,-41,-21,10,60,11,7,-29,-22,-3,-14,-8,31,-1,-3,-4,1,6,4,-35,12,47,22,8,15,21,13,-2,34,26,20,-2,-19,-20,-2,21,15,4,46,29,-1,10,-16,18,12,25,-58,-1,14,18,24,-25,-36,3,-9,-38,38,7,6,-18,-22,47,-3,16,45,13,-7,8,11,-17,5,-46,-11,-5,-5,-36,-11,-19,10,-6,-38,-45,39,29,3,-13,-16,-31,25,-20,-6,-22,-11,20,16,11,29,-8,-14,-29,-8,9,17,4,14,7,-9,14,35,50,17,17,13,24,-4,12,-2,-17,1,35,5,16,1,36,10,21,4,36,44,11,18,12,-19,},

                    {14,26,0,-6,-21,-1,31,-5,-2,5,-26,-15,21,-8,-10,22,39,7,4,1,-33,-8,15,10,-4,45,5,23,-31,-40,-15,0,32,15,18,-42,-15,41,53,40,21,20,-3,7,3,59,-26,-26,47,48,-16,-5,-42,42,11,18,23,-8,-9,24,9,0,-20,-22,1,-2,-44,-37,-22,-27,-47,-1,15,-4,-16,13,-8,-7,8,17,10,18,-41,-7,23,13,17,40,8,62,19,-24,3,2,28,32,-20,-30,-39,-8,20,39,-17,-9,9,26,21,-69,5,2,52,38,9,31,4,13,-31,-6,25,-4,-30,-20,-16,30,8,25,-15,5,-28,3,33,12,10,9,6,33,-2,-30,-5,3,5,25,10,-22,-4,73,37,42,37,12,-16,-13,-4,37,-5,-13,-8,12,-8,7,-16,1,32,3,2,38,-18,3,-2,-34,29,-10,-10,-16,-18,-10,-23,-4,-26,18,18,2,6,6,1,31,30,12,-16,-40,-14,-3,66,58,-11,-14,12,25,19,-54,-5,16,17,9,-17,-48,-29,20,74,42,13,13,20,14,28,-2,31,62,9,17,-11,-28,2,-14,-43,-9,-17,0,3,8,-24,-19,-28,-3,-9,15,31,-20,9,-2,0,47,30,-4,-14,-34,37,24,-28,-54,-90,-29,20,9,10,23,8,29,-11,-3,-57,0,-33,35,-33,-6,-30,-2,-30,33,-28,16,1,8,15,33,9,32,29,-31,-11,-38,31,27,44,-8,-74,-57,43,26,6,-7,14,-7,-8,-25,-7,-5,6,27,39,-32,8,24,26,24,-34,-45,-4,17,26,44,35,5,30,62,7,-12,13,4,1,35,0,-2,23,33,39,-12,15,-4,30,14,-16,-16,27,-18,61,9,-2,3,28,19,13,-34,-1,27,26,52,0,-10,6,-6,3,5,-3,18,-50,-78,-38,-36,8,26,18,33,-4,-33,62,-2,-20,5,-1,-24,41,10,2,15,4,-7,-3,-15,16,29,22,-13,21,14,-32,4,18,18,11,-9,-58,-51,-8,26,-3,25,4,-19,-22,38,30,-3,-1,5,-23,36,-8,-36,-47,30,34,53,27,-17,-48,14,63,50,-20,12,-2,-5,-25,-27,32,20,26,17,-47,-96,-13,-3,11,-23,-2,11,-16,25,5,-21,-7,-41,-13,29,-29,10,43,4,-8,0,-41,4,0,34,9,20,2,-3,35,29,-26,29,19,-3,-11,13,29,38,8,4,2,13,16,-7,-3,18,-26,-9,-27,-4,16,-1,-28,-31,-13,15,12,-4,-4,-6,-7,-8,17,-2,1,20,-27,-17,33,16,-8,21,31,64,33,17,-3,-16,4,-23,20,42,-17,-21,22,-3,1,8,-33,-2,-21,15,2,-17,-47,-22,63,-46,-30,14,-20,-1,-18,65,-10,-12,51,11,50,32,69,1,-7,38,72,-36,7,-38,31,-15,-1,-51,-10,33,24,-10,-20,-3,-17,14,22,7,21,30,-4,5,0,-38,3,30,5,-3,-11,-3,31,36,46,-9,-7,32,21,-19,-2,-49,-19,24,9,-23,-26,-26,8,19,-29,-46,-34,11,48,71,-1,-11,-28,16,28,-9,-10,28,37,41,16,-21,19,18,-12,5,-18,-1,44,27,12,18,47,4,39,6,-27,-5,6,32,31,-28,-66,-9,26,-19,-41,-55,-35,29,42,-32,2,-16,1,56,32,-1,28,31,23,-9,13,14,31,-28,9,19,27,-1,16,-21,13,-46,-26,-9,3,35,2,-8,-25,-6,28,40,-1,8,0,-5,25,-5,-44,-44,-53,21,50,-1,8,-2,50,15,25,-30,-7,-57,19,9,-4,8,-37,-53,-63,53,12,27,32,-8,2,14,-1,32,20,-20,1,-32,-1,38,14,-49,-50,-25,9,30,25,17,4,30,-15,-27,-25,-43,18,16,34,-25,-33,-27,0,-24,-31,-57,-41,11,25,45,-4,-17,13,59,14,17,1,38,41,12,5,-31,-14,-17,22,9,-32,3,29,-28,-6,1,-13,-26,9,24,-13,9,12,-4,-15,-28,0,21,21,44,-9,7,-15,32,27,43,-27,-7,11,20,-8,18,3,-18,46,0,2,27,15,-9,24,18,-30,-5,-16,19,13,27,-22,-26,-13,7,9,-27,-19,-12,31,-24,7,30,3,-13,14,-4,12,28,30,14,52,32,8,18,-1,-7,-12,9,-3,0,-14,-14,1,20,-6,-14,-18,-5,14,-4,42,7,-50,-1,-29,28,2,6,22,15,-11,-47,-15,-22,8,6,2,47,18,19,32,-9,16,-21,-20,-15,-24,-4,14,13,6,-14,17,21,-35,-51,-29,2,27,17,-25,-33,-36,16,31,28,16,14,34,27,17,14,2,28,30,17,7,18,17,-7,8,-1,-7,-15,4,-4,-1,12,20,45,-49,12,-16,13,31,35,13,14,19,17,17,60,-55,1,-20,-46,18,18,-4,18,70,30,17,40,7,25,-22,-8,38,-25,-7,16,-31,-2,-21,2,1,-24,1,19,-8,-15,-15,-16,6,0,9,-5,-15,-10,-24,-2,-30,-21,9,17,5,-1,1,3,8,1,14,0,-3,-20,0,9,-16,-2,23,32,-38,-27,11,10,22,22,19,17,26,11,24,-36,0,22,17,32,35,-31,-1,35,-4,15,22,64,1,11,-43,-24,-28,14,19,-30,-29,7,-7,6,18,-6,-2,13,8,7,-3,42,30,36,-24,-51,-12,56,22,-1,-32,-37,-20,23,9,26,22,48,-9,-22,-14,3,26,-17,-11,-10,-15,28,15,37,-25,-10,-9,23,-6,2,26,11,-7,31,9,-44,-12,66,-27,-17,-46,-8,9,3,30,6,-27,35,46,-3,37,10,3,-25,15,42,1,16,4,37,21,-10,8,23,11,37,-21,-53,-28,37,35,25,7,-56,-18,-24,-19,4,6,26,16,-6,6,28,-10,-17,-40,-50,-8,5,-4,-10,-40,-39,-54,26,1,9,38,-30,6,55,7,6,22,-8,20,-5,-7,37,-26,-85,-47,-22,},

                    {-4,6,17,13,-18,-13,7,2,-18,-2,-31,-3,-7,-3,-8,-16,-9,6,-1,-16,-4,22,-9,-24,-9,-10,-10,-10,-3,14,11,-16,10,-1,5,24,-13,-8,12,29,5,-15,-15,-12,14,17,-31,-8,-2,-16,-6,3,-13,-10,12,-10,-7,11,-9,13,-6,-7,-12,-7,0,9,-12,-4,-14,-2,-19,2,-4,-8,-9,-16,-9,-10,-5,1,-18,2,-2,-15,11,-13,-19,-5,-2,-5,3,-8,14,10,3,6,-2,8,-9,-2,-4,10,-3,-11,17,-6,-16,-16,-10,-3,5,-6,-13,-8,-12,-12,9,-30,3,11,6,6,-12,3,-13,2,4,7,-4,31,-16,-14,1,-28,-11,-1,-1,8,-4,-12,-10,-1,1,-2,12,1,8,36,6,-10,-9,-9,-11,7,0,-31,7,-11,-23,14,-23,-11,0,0,-3,1,-24,-19,5,5,3,7,-4,-3,9,-34,17,-12,-15,-10,-6,-14,10,-5,21,5,-1,-34,-29,-10,-10,-17,2,-6,1,-8,-2,-21,9,5,-16,-23,-11,1,-14,17,13,-16,-1,6,-32,-10,-13,6,-6,-15,-1,-20,7,17,-37,-7,-2,-20,0,-2,-12,-11,-12,-14,5,8,-28,-1,0,-23,2,-4,4,7,-18,-26,1,5,-28,10,10,-18,0,27,-28,-4,6,-8,28,9,-1,-2,2,-17,3,-5,-12,-8,-6,-6,-14,-1,-31,-13,-15,-26,-7,3,5,13,11,-28,10,-4,-16,4,3,-14,2,16,-9,-11,11,-12,-25,-11,-2,-18,0,-7,-17,-3,-26,0,11,6,10,-21,17,2,-7,-1,-2,22,17,-1,-16,14,0,39,11,-12,-9,-10,-13,1,-8,3,-12,-15,-15,1,-6,-3,0,-33,-20,0,-16,0,2,0,3,-34,-13,-15,-3,-1,-10,-10,1,-12,-10,-3,5,-5,-5,0,-13,-9,-18,-20,-25,-17,1,-5,20,2,-9,-1,-2,-6,-14,4,-28,-5,6,4,-5,-3,-16,-13,-5,-35,-20,-18,-2,-2,-9,0,-17,2,-1,4,-20,-7,-14,-7,-5,23,-14,-27,-17,-18,-17,-2,0,2,-25,-21,-31,-11,9,-1,-6,1,2,-19,5,2,-10,18,16,9,-9,-11,-15,-9,-5,-3,-6,-8,1,-8,19,-14,7,-7,-12,-9,-3,0,-13,-2,-14,-30,-30,-23,-10,-9,-8,-20,-28,-20,-8,0,5,7,-15,5,-8,7,10,-11,1,2,-12,-15,-15,-16,-14,-3,-10,0,2,38,-13,-1,-2,-10,2,15,-14,4,-10,-18,-9,-2,-10,1,-12,-23,17,17,-20,-5,0,-5,-6,5,-22,-1,2,-2,-9,2,11,-7,7,2,-12,5,17,-5,-12,-25,7,-3,-17,-18,0,13,-4,0,-4,-19,-11,3,-15,-7,-2,-28,-13,-16,-15,2,-21,-23,-3,-3,11,-11,22,-4,0,-21,-2,14,2,0,-16,5,4,-15,-18,-20,1,-12,-5,-1,-20,-25,-4,-8,4,-7,18,-3,-21,0,20,7,-27,-2,-13,-19,-5,0,-24,6,3,-25,-17,-20,5,1,-6,-26,-18,-13,-33,-13,-16,-11,-19,-8,-17,-8,2,10,2,8,-1,-20,-4,-20,8,15,-6,-4,-27,-15,2,-7,-10,-1,-2,-35,-21,-28,-12,-26,-7,-14,-22,-11,-27,-9,-29,-10,-8,-7,-15,-10,-6,0,-6,-3,10,-8,-34,-16,-17,-21,3,-16,-19,11,6,-3,11,-12,9,-2,30,1,13,-5,-13,-10,9,-2,0,-10,-3,-9,23,-8,-7,-20,-29,-4,11,-3,-9,8,-31,13,0,-29,8,10,-20,-12,22,-15,-17,-13,-8,4,13,-8,-7,12,4,-1,28,-6,-3,4,-5,6,-8,-20,-14,9,-28,-17,17,-10,-12,-10,-9,-27,-1,6,-27,16,3,-7,5,8,-5,-23,-7,-4,-5,21,1,-11,2,-13,-17,-8,-17,-7,-16,7,-21,-20,12,-10,-5,-12,6,10,-3,-11,-1,6,-4,-1,-13,-24,-13,-14,11,16,-9,-24,-6,-7,-3,6,10,-21,-12,3,-2,-13,-22,-2,9,-4,-6,-3,-4,-14,-12,-21,4,23,-6,-23,-8,-3,11,9,8,-3,-11,-23,1,-15,1,-22,-7,1,-1,12,6,-3,1,-1,-14,29,19,-13,8,-18,-10,-4,16,0,6,-7,-4,13,6,2,-12,4,-18,19,-10,-11,-4,-7,-9,13,-4,-9,-12,6,23,23,-23,-9,-2,-21,-4,2,-7,1,9,-29,-1,-4,-18,-10,3,-30,17,-29,-9,-10,-9,-4,-17,-23,-12,1,-18,11,-15,2,7,8,4,-9,-9,-22,-6,11,-13,-11,-32,-23,-35,-11,-11,-11,-15,-16,-21,-14,-9,7,-7,15,12,5,-25,11,-7,-11,-4,-28,2,-22,9,-2,11,6,-7,3,7,6,-19,-7,9,-16,-21,13,-7,3,-14,1,2,18,-26,2,8,-19,2,-6,-14,-10,4,15,6,20,23,-12,-8,-19,-1,2,13,3,11,0,5,5,31,-16,5,3,6,-14,2,-6,-9,-1,-22,10,7,-23,1,2,0,16,-16,0,-7,-11,-4,-25,7,-14,-5,-5,0,-23,-1,-19,9,-3,-15,-19,-10,-21,-4,-8,-9,1,-11,-25,-12,-16,-9,-6,0,-2,-19,-4,15,-12,37,4,-33,16,-1,-1,22,-5,-13,-11,17,-1,-4,3,6,-12,-21,15,6,-6,1,-4,-4,-16,-39,0,-7,4,-3,16,-17,0,1,-22,7,12,6,1,-9,-13,-1,5,-29,-3,-3,-12,-11,7,-20,4,-6,-6,4,-8,-22,-2,-11,-18,-28,-6,1,-1,14,-15,-9,-4,-7,-8,2,-2,-8,15,1,-13,-15,-11,16,22,-10,-6,-20,-4,-31,9,-1,10,-16,-28,-27,-8,11,-1,-12,-27,-7,14,-16,-7,-5,-1,11,-2,-33,-21,-7,5,-27,-28,-16,3,-28,-6,-9,7,11,7,-11,-3,8,-31,-21,-12,3,-9,8,4,-1,-18,-5,-27,12,-14,3,-9,-17,-35,3,-3,-26,12,9,-12,19,-16,-13,6,-8,-19,3,0,-5,9,0,-12,-19,24,1,-2,},

                    {11,35,10,-4,5,-30,9,8,1,18,43,24,4,0,-5,31,4,10,-4,-19,8,-23,30,35,-7,-26,34,-12,17,7,20,-7,-49,-15,-11,-3,-14,3,33,10,44,-16,22,9,27,20,16,11,-19,21,2,19,-39,-42,39,45,38,-2,-19,16,20,33,-8,25,-3,7,-31,52,68,47,0,12,0,-2,-2,-9,-26,11,-3,19,17,10,38,5,-2,-6,4,6,-12,-30,-8,2,6,-17,4,-27,-7,24,42,-20,23,2,-1,-7,-55,-28,-20,17,25,35,11,-23,-2,-8,5,16,9,8,-27,15,25,0,-13,-1,-20,13,10,-16,5,6,-26,14,-1,8,14,-45,30,35,11,-41,4,-6,21,0,8,23,20,28,14,9,11,42,51,-3,-2,-19,2,1,14,23,-19,-12,40,33,39,-2,-3,31,-11,38,10,44,-6,3,-13,34,67,47,25,13,-3,-3,-20,-8,8,35,-36,1,0,46,14,24,-8,4,-6,26,11,32,-6,-7,23,16,-1,-20,19,49,9,-22,-11,-13,-18,21,-16,-29,-32,3,7,53,39,48,-15,-9,12,49,-24,-15,-45,-36,4,13,3,28,10,21,13,21,4,-21,28,12,21,1,-8,12,34,19,-51,16,37,54,44,38,40,13,-25,-19,-41,1,23,-4,-18,-12,-40,-33,0,24,-27,-9,0,-37,27,5,-19,-10,10,-23,-11,-3,-13,-29,29,-12,-21,-12,-28,12,38,37,-6,35,15,-2,-41,-21,12,29,12,2,-7,-8,-10,35,10,10,6,10,31,3,19,6,65,25,-1,42,16,2,0,-20,-35,-39,-58,-66,-35,-30,5,15,-7,-18,39,23,-2,3,-4,-11,-19,17,-1,18,-21,-3,11,-22,0,18,24,7,-29,6,29,38,58,27,4,20,-28,-17,45,21,28,-30,13,30,52,-6,30,29,-35,19,-4,11,49,58,-10,7,2,14,21,-13,14,22,-10,-5,-19,19,3,-10,-6,10,-12,3,14,45,58,3,4,-12,7,46,7,-13,-27,-65,14,21,28,-2,9,-46,24,7,-12,-31,-8,9,-36,-41,-12,-17,-9,25,12,6,21,-42,-49,36,-27,-48,-46,2,-22,35,4,-5,39,-22,20,-24,16,1,15,13,33,42,26,13,0,18,17,25,-3,23,19,0,0,31,-43,5,17,22,1,26,-17,-39,-26,-50,-41,-25,25,1,16,28,24,20,-9,3,10,14,-22,12,6,42,13,0,-6,-43,32,35,30,7,25,33,-20,-3,2,32,5,-28,4,26,-3,3,-1,29,6,2,31,52,19,-3,-2,14,20,26,48,16,10,42,-2,32,-39,-28,-7,43,49,25,-7,45,-17,8,8,-2,5,23,-19,-67,6,20,-3,-5,4,1,-18,4,4,62,15,2,19,13,18,16,17,10,-45,-9,14,41,17,-1,-25,-15,-18,18,8,-1,21,13,31,46,-38,-41,19,26,32,-8,-27,5,-26,-57,-18,31,18,10,14,7,-8,-8,12,10,10,9,-5,9,2,-4,-13,-19,-23,-39,4,15,25,-15,-5,16,-8,0,6,-46,-17,-3,-15,6,6,-11,-2,-11,19,19,-1,17,34,38,-28,-12,-6,23,21,55,-4,15,15,1,4,14,11,18,-3,-7,1,7,22,25,4,-25,-7,-32,30,40,-1,38,58,25,16,21,6,-22,12,-6,5,13,17,-7,-16,5,18,20,-9,39,-11,10,9,-32,-12,28,-21,17,-38,-38,48,70,37,-25,36,39,11,31,-31,15,2,-4,-15,-9,-51,26,6,-4,-3,9,11,-1,8,14,-37,0,17,-4,12,0,-42,-8,-15,38,23,-24,12,9,67,10,-5,4,-21,-9,33,67,-5,5,18,16,48,21,7,13,11,11,32,37,12,9,33,15,-44,-30,19,10,-31,-12,23,17,-8,-13,-37,-17,-24,-4,6,20,28,28,35,18,-4,-21,8,40,10,34,11,5,7,25,6,27,5,23,36,-27,-5,-34,-2,12,-21,-29,-4,13,-33,-7,-19,-27,-50,-29,-8,-2,5,20,27,12,2,2,-9,5,-20,-2,11,1,6,-23,16,-1,2,16,-2,-3,64,22,-4,-5,-15,6,38,10,-10,14,17,32,18,16,15,9,-12,44,8,0,5,11,2,16,1,21,-7,17,7,40,-10,-10,5,18,-13,-3,15,-19,1,-27,-27,-4,-16,-17,0,36,-1,20,0,0,-18,-7,-25,-26,19,40,-28,-3,-2,-3,-19,13,29,41,-4,11,1,7,-6,-18,-4,-16,5,17,-14,5,13,-5,21,-8,12,2,-35,-29,-14,8,-7,13,-1,-12,13,12,14,22,-21,-11,-16,25,-18,16,-2,10,8,-32,41,-15,-27,-18,19,-20,-12,-10,-13,12,-11,1,9,1,9,-10,19,-12,7,13,28,26,19,-27,6,13,32,-10,3,-17,-4,-26,62,5,-18,-4,-10,25,6,1,-8,9,14,-2,5,45,3,10,-19,-24,29,12,-2,-14,-7,18,5,-22,-26,-27,12,-1,16,15,34,58,9,-29,-7,33,48,48,5,-7,-6,1,-10,0,-6,-3,18,7,-34,-18,-33,-16,-42,-3,-15,-40,25,40,19,-21,-62,-56,-12,27,12,-32,-38,-43,-10,27,-9,-52,-17,-8,-22,-17,24,-45,-5,-26,11,27,-30,-32,-14,27,17,-65,-3,26,29,30,28,47,-8,-6,-38,-24,3,34,12,8,-23,-12,-20,-5,2,2,-3,-27,5,-18,14,18,9,48,0,-14,1,-31,22,27,-21,-63,30,7,55,16,16,10,-20,20,63,24,21,-16,15,55,110,42,-46,-11,-8,6,17,-34,1,-10,21,11,-27,8,9,49,-37,-33,0,5,-32,28,4,12,-10,-22,27,-11,24,18,-10,1,1,18,-2,-8,-44,7,-12,35,2,-2,-1,10,18,3,-3,4,14,-20,-18,3,3,9,-8,20,-13,-15,54,53,40,18,},

                    {-5,-10,19,31,16,4,5,4,-8,-14,-27,15,-31,7,-18,-3,28,13,13,-34,23,-12,-15,35,13,0,-23,24,26,31,1,-2,34,21,11,0,19,14,3,6,34,-17,3,9,-29,5,26,23,26,-20,18,19,11,-6,3,-42,-23,25,-8,-26,-33,-24,-13,-12,-18,-5,33,-13,-2,-10,16,22,8,-17,10,-7,6,-27,8,1,0,25,-1,15,-6,-15,14,30,35,-22,-12,-3,-13,5,-7,22,-20,18,-6,35,15,26,12,20,29,24,15,43,27,-2,8,29,22,10,-4,-11,8,12,9,10,-41,-41,3,21,-1,-6,11,-22,22,26,14,-21,-7,-5,5,11,23,46,10,-12,2,-25,-5,8,0,-19,21,8,-1,-19,6,1,-10,14,34,16,-34,-32,-27,9,9,20,4,-33,-37,23,-7,-7,-15,-11,1,-7,-37,5,12,0,1,-37,-1,-10,23,-27,-1,9,-19,-37,75,34,24,-4,11,-40,1,36,19,35,51,41,34,38,45,24,2,-13,6,19,56,23,7,35,26,-6,10,7,3,6,5,17,32,0,-12,-27,-13,-35,-6,23,15,27,-6,-34,-16,6,41,-32,3,-24,6,42,-3,-6,-18,0,-1,23,1,20,38,-2,-9,-9,23,47,12,27,14,29,-23,-10,-3,-30,30,37,4,-32,-22,-29,16,44,-9,-53,20,-43,-13,66,-23,-27,8,0,-2,60,11,21,12,9,-19,-27,42,34,15,41,10,41,1,-31,3,-6,13,6,9,12,18,21,-18,12,-3,-23,33,25,-42,3,-20,27,35,5,4,-33,-18,3,24,13,15,18,20,19,44,-6,47,5,-22,-36,19,-22,24,2,1,4,15,3,60,-8,19,26,3,30,61,39,2,31,6,3,12,-9,13,17,8,5,-12,23,29,22,30,-5,5,25,-7,-48,57,-21,-2,-13,-27,-16,8,-35,-33,-14,36,31,36,-18,15,50,-1,-2,7,-13,-2,-26,34,24,6,-8,43,55,21,0,35,-18,18,-8,25,7,-2,8,-1,-8,-19,1,-3,-21,-33,2,12,-38,44,25,-31,-4,-24,6,0,22,0,1,9,35,3,9,9,33,69,74,20,49,32,21,8,-8,-24,12,-18,-6,-16,-5,-38,-7,24,9,21,46,20,-16,19,-11,-19,22,-26,-5,-6,-1,7,24,-8,10,-2,20,10,14,-21,5,-16,-3,-1,-28,15,-17,-7,23,35,-16,-16,-41,-41,15,14,7,3,-29,-18,19,-7,-8,-17,-6,-34,2,-2,-7,-21,-9,9,17,-14,0,19,22,-2,4,0,-6,16,32,21,-1,10,26,-13,-42,-27,-22,25,22,37,-40,-25,-43,15,0,13,-24,-34,8,-4,40,34,3,7,-16,8,45,21,71,25,34,23,-54,19,40,30,-18,-29,-10,-4,5,17,2,22,0,-13,-13,42,11,3,-34,6,15,-9,13,44,47,-5,25,13,-30,31,1,28,51,38,53,6,-49,9,14,24,-16,-22,-39,-6,-4,8,-4,-13,-20,-25,-3,12,18,-18,6,1,-6,-2,-6,14,42,-5,6,-5,-6,3,31,27,-10,-5,10,5,-36,-4,-2,21,23,-11,-24,18,33,38,19,-8,-58,35,59,64,42,15,47,4,48,65,15,23,61,9,45,46,14,32,27,12,19,-20,17,-1,-5,-6,-15,-2,55,10,7,-35,-41,14,0,0,12,-42,-18,33,-7,15,-15,7,3,15,-14,-5,1,8,25,-32,-11,-8,13,2,19,-16,46,-21,-7,1,-22,33,56,-25,29,-20,-32,3,-4,-4,19,-16,-29,-4,33,1,-18,-11,-11,-2,-9,31,-3,-38,14,-35,-14,52,19,-9,34,67,29,-27,-17,17,15,-4,8,-9,-29,41,4,-3,-24,-42,-9,-5,11,-7,8,8,31,25,-6,-18,25,33,18,-14,-3,-18,-1,12,53,10,17,-39,-37,2,-37,24,27,-13,-2,-13,-39,11,-1,28,19,21,35,52,7,1,25,-13,5,-14,-2,34,27,-16,11,-10,9,-7,-8,17,14,12,17,-20,-9,-1,30,-12,-6,-6,24,32,28,-14,-45,-46,13,24,16,25,-35,-38,20,-18,9,22,-28,11,-9,3,11,2,2,6,-12,-20,21,-32,-12,-7,-9,0,-30,44,-4,-7,-16,-30,-6,-10,-26,-37,15,29,42,-21,-47,-14,-11,8,24,-27,-6,-36,-13,29,45,-15,-8,14,-17,28,17,24,2,41,22,-63,-37,26,37,22,11,17,-44,9,15,34,0,-24,-25,-7,24,16,-1,-24,-21,-18,6,31,3,-6,29,10,4,9,0,-10,33,7,-4,-27,18,-9,-59,14,-7,21,1,-15,38,10,-9,-2,13,25,24,1,-62,-9,13,-26,16,-9,-25,-4,4,3,10,-21,8,36,24,31,7,-12,-3,-4,24,26,-14,6,10,9,31,16,-8,1,-4,-43,4,31,4,23,1,-50,-5,9,-8,10,-40,3,22,-21,-8,1,21,51,9,-20,31,37,24,12,4,6,6,-11,2,-20,-13,-17,-15,1,-32,39,11,5,-10,-22,-6,20,7,7,40,12,23,23,27,-14,6,-13,27,34,4,4,59,6,12,9,9,7,18,17,37,12,30,-34,-9,41,-39,-30,29,3,-2,29,21,-9,49,-3,19,27,8,4,6,15,1,47,15,-52,-1,5,29,36,-14,44,-15,6,29,-5,-22,37,8,6,-1,-27,-49,-54,18,11,3,17,12,-1,-5,42,22,16,-10,10,1,-31,40,-1,6,-6,-15,11,33,38,8,21,-2,-24,-45,2,10,13,1,14,-23,21,57,61,37,27,33,58,65,36,14,3,-19,47,55,80,-14,-42,-4,33,22,1,-14,13,22,-19,12,12,38,-9,14,24,1,4,70,2,-6,-4,-25,11,21,-11,-33,2,-11,-14,15,-19,3,-11,19,5,-31,-4,-7,4,-3,-26,-17,73,9,},

                    {0,-4,10,-4,-12,13,8,-14,9,10,10,-27,-5,9,-23,24,16,-3,4,-2,5,-4,-14,11,-2,17,32,27,17,-9,-14,15,15,27,23,-3,25,38,-49,-59,-51,-10,25,-4,-53,-22,-4,13,-20,3,-17,5,12,17,-18,28,-21,12,19,34,-4,-11,-64,12,9,1,66,26,12,3,-17,-13,16,25,-2,5,20,-27,0,15,5,12,6,-38,-24,13,-25,-5,-2,-13,-2,-13,-20,10,11,7,-52,-15,36,48,9,-1,-1,29,32,9,-14,35,-7,-16,-18,-18,-3,7,13,-7,12,15,11,20,-36,-17,-10,16,15,-35,12,-7,-8,18,-32,-16,19,-13,11,14,-6,14,-11,9,15,19,-10,2,6,-34,-57,-40,-40,14,21,-45,-53,7,8,3,-8,24,-13,9,12,5,0,27,-25,3,2,1,-33,12,-49,-19,-9,21,19,12,-14,11,13,-12,6,-47,-27,8,-25,-18,49,85,44,40,26,-9,18,36,31,22,20,-14,16,2,9,6,-38,3,2,-5,49,32,7,10,-16,1,-9,-5,-28,-24,-23,-25,-72,-83,-104,-16,-41,9,-20,-24,3,23,-1,-4,-6,15,-1,9,55,-24,-3,-2,-24,33,48,1,-19,1,-27,-15,12,15,-19,-7,8,-10,-5,-19,-37,-21,-21,-10,2,-12,-47,-13,15,18,5,4,-30,31,11,14,-5,-12,-16,38,-19,22,20,1,-16,-4,-1,7,17,6,-2,13,7,-1,24,27,-11,5,42,28,2,16,25,21,6,4,9,10,16,-5,-33,13,8,8,-39,-49,-15,-4,8,4,-10,-8,22,-21,9,29,15,6,19,18,42,-19,-1,-24,3,-7,-14,21,19,2,39,-55,28,-1,48,29,-13,0,-3,-1,51,5,-18,11,8,-32,49,-21,0,3,-1,-15,-15,3,-36,-15,11,-15,-12,-53,-64,-40,44,4,9,-6,-20,-84,11,1,8,35,-23,2,34,-8,-39,5,1,36,35,-57,19,36,33,36,-36,-17,25,16,-16,-25,-7,-1,2,-17,-3,30,-5,-6,12,23,25,18,18,-13,-36,6,3,-14,41,22,-43,-43,-19,-20,11,26,5,18,-44,-30,-5,15,4,39,28,-17,4,40,4,21,-12,1,-33,-2,17,12,10,-32,-14,15,-28,23,17,-29,-6,-1,-27,0,-2,1,8,-37,2,4,1,-22,-19,-6,5,19,28,-15,-19,-1,-28,1,-3,7,9,29,13,26,1,-36,-26,-3,11,17,-27,10,19,-26,-24,-14,30,10,8,-8,-5,4,6,15,0,46,15,-6,-22,2,19,51,14,14,-3,9,24,23,-22,-14,17,20,-7,4,-27,20,15,50,6,0,-12,4,-9,12,27,16,17,-7,-16,4,33,20,2,15,-9,32,3,28,-36,3,-9,-22,-17,6,19,-3,-12,-24,4,-3,9,-16,0,-24,-15,21,-1,-24,-2,-22,16,17,-3,-1,22,20,7,43,-1,-6,-7,-45,50,18,-2,10,23,-18,3,-8,-3,22,19,38,10,-24,10,5,4,-46,-11,-15,12,9,-30,-20,15,-9,16,3,-15,4,-20,-12,-18,-9,-16,-14,-1,6,-2,14,3,-35,-18,8,0,27,-15,-50,15,8,6,-20,-7,-24,28,-10,50,36,46,-16,-20,4,40,27,-4,19,13,2,12,0,23,9,-1,-11,-26,-49,-113,14,7,0,-31,-57,-36,-20,12,-9,3,-17,19,4,7,-19,-9,-2,29,27,15,-21,-43,1,12,16,64,36,5,-30,-19,-18,-17,-17,-34,-29,-51,-9,-4,-11,-41,-39,-2,-6,23,0,-11,-49,24,7,0,0,-31,25,-35,-5,31,-4,14,14,-4,-16,51,7,14,7,-15,-5,14,-12,-3,15,-14,-34,4,25,20,-7,-29,-24,40,0,32,-53,-5,-4,-14,-3,11,19,21,30,7,1,12,0,4,27,-1,2,-10,6,-1,15,2,-11,-29,-48,-39,-14,13,38,36,-3,10,-11,7,-11,-4,25,8,-24,6,-2,-9,23,-13,40,-2,-10,1,29,15,-11,7,5,11,6,17,4,1,20,-10,-28,10,24,-12,2,0,57,17,-2,-6,-18,-15,42,7,8,36,-8,-42,-23,-4,36,40,4,-3,-21,19,28,-5,0,23,-23,-8,19,-29,9,-47,-14,-18,21,15,19,17,-16,-64,-53,-8,-6,10,31,-27,20,28,-22,-31,-6,-18,-2,-1,8,-9,8,59,27,-11,3,11,6,19,4,10,-1,-14,11,-23,-36,28,6,8,25,13,11,11,-17,58,34,-21,-6,-19,-18,30,18,-55,-11,8,-12,12,-8,0,4,-9,-1,-17,3,-15,-16,-5,4,-4,-18,-9,-14,9,15,31,14,-8,-24,23,4,6,43,-6,26,-10,-40,-46,4,19,27,24,-30,-12,19,7,10,14,22,7,16,7,-28,4,-22,11,15,-14,27,12,-42,-60,-61,7,10,-9,-16,-31,22,22,3,18,40,-32,-4,-18,19,-22,-13,-36,23,13,-2,11,33,9,33,11,21,47,31,6,15,30,22,5,8,19,25,-15,-14,-11,-12,5,-12,-37,-20,-13,-24,-20,-23,-10,2,15,-9,-16,13,12,10,-5,27,25,20,34,47,-13,5,-13,-26,-41,13,-8,26,-5,47,16,26,27,-18,-39,-16,23,24,27,36,-6,-45,-31,3,2,28,31,8,15,-18,38,35,-20,12,9,-17,-16,-13,-21,2,14,16,3,10,-2,-4,28,-4,-31,-45,-12,8,-15,8,49,5,9,7,-39,-50,27,-5,14,-14,-28,7,11,-4,-11,23,2,14,22,-3,-2,-55,-71,-29,-7,7,-24,-5,-63,-34,20,50,44,-9,28,-12,11,55,34,53,29,16,3,5,3,47,9,21,72,29,3,-31,-18,-25,-22,23,-23,9,-31,-11,-14,26,3,24,-21,29,5,15,40,-46,4,-6,35,8,-7,-10,-16,30,9,-12,-4,-10,-32,-7,23,-15,0,0,14,-16,},

                    {-4,-24,21,13,0,-12,3,-3,-9,-32,-11,-22,18,-7,-11,-16,-17,-4,3,-9,31,19,1,6,-8,7,-21,24,35,-13,-26,9,18,12,1,8,11,20,-28,-37,-21,-2,19,6,-6,-3,0,-25,53,20,20,12,-7,-20,-9,-22,-33,7,16,20,-41,-26,-94,11,12,12,61,7,-49,20,-6,0,-7,57,1,-7,-15,-17,3,23,-3,-22,-24,1,-15,-5,-25,-2,-29,-1,2,-18,12,20,1,3,-10,-9,3,43,13,-1,-13,-14,45,-4,18,47,1,-13,12,10,2,-5,17,-16,11,15,10,14,-38,15,-26,5,10,-14,28,27,9,15,-15,-13,16,1,13,17,12,9,-16,-8,3,-1,8,13,0,-25,-53,-50,-19,11,28,-23,-15,-9,6,5,46,21,10,7,1,17,-28,9,-59,2,10,29,-31,-7,-83,-7,21,17,27,-2,-46,19,21,-1,22,-9,8,0,2,-36,33,45,-6,25,-1,-28,-14,-11,9,1,-13,-33,-2,-51,-21,8,11,9,5,-29,24,21,8,6,0,-17,-18,-5,3,-8,-4,-33,-36,-23,-27,-4,27,29,24,13,21,9,23,9,13,-17,-10,-6,51,-22,22,-33,14,10,10,-21,-8,-29,1,-23,-3,-5,-33,-23,1,4,-5,9,13,7,-45,7,18,-24,-11,17,10,0,18,1,-33,46,5,3,18,4,5,-1,-6,11,-2,-6,-2,-14,-18,20,5,1,-2,-36,-8,21,11,35,11,34,47,15,2,35,23,2,-15,8,-2,-5,0,-24,-12,4,-3,22,2,8,-21,8,26,-6,2,-6,18,-1,-12,12,3,9,34,29,10,53,46,25,-1,-19,9,-25,25,0,-2,-6,14,-22,24,43,-14,-6,-23,-5,24,29,-28,45,16,-13,24,-54,14,-17,-13,3,-15,-4,-9,26,-5,-20,6,-19,-29,-28,57,19,-4,13,-46,-40,15,-7,12,12,-37,-32,17,-20,7,0,-13,37,6,-28,-10,17,20,23,-22,-18,-21,19,-14,-12,18,-19,-3,-2,-6,-7,-4,-1,11,16,0,-21,-18,-8,-6,25,-10,-26,29,47,1,45,20,-18,-11,-10,-8,34,3,8,0,-20,-9,-13,-32,18,-31,56,24,29,-7,-2,-21,4,32,-10,-41,-33,-16,-10,-16,3,-20,-7,-21,-6,-21,32,1,-5,30,-7,-16,-14,19,3,0,11,-11,0,10,8,-4,7,-22,-13,8,-2,26,12,-16,-3,14,0,-2,-12,2,1,-18,3,16,-17,15,-10,32,1,-6,-12,-16,-28,14,9,-9,12,-17,-12,-20,-7,7,39,7,-45,-55,20,-4,1,-8,-13,23,34,-36,-15,-12,-2,7,20,-2,3,8,15,14,16,5,-1,7,-7,0,4,-22,3,-17,-5,21,27,-12,53,-5,32,-9,-2,5,-17,18,6,-17,-56,-18,5,3,-5,-23,-21,-14,17,-6,35,11,-10,38,22,20,24,-9,-25,-1,25,-31,-42,3,-14,15,42,32,47,12,-36,13,-17,5,5,-12,0,-27,-22,-16,16,1,-22,-11,-14,11,27,5,-8,33,18,23,21,8,3,0,-12,8,11,-4,8,4,-5,-4,-2,-23,-29,-26,15,3,-5,-29,-48,27,-6,1,-17,-12,1,-8,-34,9,5,33,-3,-30,-31,39,31,9,31,29,16,25,5,4,-6,25,-25,-9,9,-30,0,28,-18,-13,11,-23,-46,1,-9,6,2,-13,-2,23,3,-26,6,4,-9,5,-9,-50,17,1,18,23,12,-58,-75,-12,10,-15,26,2,20,-23,-22,22,-17,23,20,21,-21,25,3,-17,-8,29,-6,14,16,-25,9,-29,-16,7,-18,12,8,26,19,19,-19,-3,-34,10,-2,-8,-13,-7,61,-18,-35,12,-12,5,22,-12,-23,9,-7,-10,24,-1,-27,-10,8,23,6,24,43,10,16,37,12,15,21,-1,-9,11,-7,1,4,-20,-12,-22,-47,-26,-25,20,14,-12,-16,-27,-26,-9,-21,-13,-15,-21,-8,-4,-30,-35,-13,-25,22,12,11,-11,28,7,-7,37,11,4,24,26,6,-9,22,-17,-36,31,17,-16,-5,0,27,11,4,10,4,-15,-10,-11,3,12,-8,-17,-11,-14,14,14,4,-5,11,23,27,-5,-8,-36,17,14,-10,8,24,-38,-5,-7,7,-8,10,-24,-23,-26,-58,-11,-25,-17,5,-1,9,18,-12,6,-4,-32,16,-13,19,-18,-1,28,12,0,-31,-14,12,34,-1,32,-12,-2,20,-24,-5,14,3,-9,-6,-7,-20,3,-13,5,22,-14,7,4,-44,-7,28,-27,16,24,18,34,3,-2,0,-6,-15,1,-12,-10,-8,-8,20,5,0,8,10,-15,3,-20,-9,-24,-4,-5,-14,-9,-3,-55,-24,-17,-26,-28,-8,2,48,47,-17,-29,10,7,-4,-26,12,19,12,12,-21,-13,-13,-1,42,-45,-4,-3,-2,6,-22,-4,13,1,21,-14,23,-17,0,13,23,-47,15,2,36,-7,-14,-43,-24,15,1,11,29,-6,-3,26,28,12,9,3,-22,-13,15,-12,1,8,-13,-17,0,-17,-23,0,-61,-55,-11,8,5,12,-16,-8,-7,4,-30,-32,1,11,0,-8,27,30,21,0,81,-1,0,7,7,-19,7,-15,5,-24,50,7,-8,29,-15,0,-5,28,6,6,50,28,-11,-7,7,19,-17,40,-15,32,-13,7,21,-11,-49,12,-5,-16,-1,12,-6,1,29,9,-14,-8,0,-15,-17,-19,5,-15,-26,12,-5,47,17,31,-9,-5,-39,2,-3,4,7,-29,-1,3,-15,-6,4,6,2,25,-5,-15,-44,-37,-19,-5,13,1,17,-41,-46,-6,22,-14,-18,-13,-61,-5,-41,-75,14,-1,-1,-24,-40,-1,28,7,20,65,-9,15,1,18,1,7,-3,-16,-21,-50,-8,-9,43,22,33,6,37,-2,44,3,-9,15,-31,20,20,0,-31,-12,20,6,-13,8,-26,9,-3,2,13,5,-46,24,-10,},

                    {-11,-13,-48,-35,-37,-48,-4,-13,-9,-18,-4,6,-13,-16,37,-10,-1,4,-12,0,-51,5,4,-2,-16,-48,-27,-8,-7,-19,-1,-37,-7,-49,-15,-15,23,51,4,5,0,-33,26,9,-11,-10,-12,-36,-18,6,-8,-6,2,-11,10,-8,17,30,-9,9,18,-19,-21,-14,-32,-39,44,-27,-39,-111,-71,-35,-12,-23,-48,-64,-44,-21,-24,-16,-3,-29,-16,10,-14,14,7,-19,-10,10,-23,-8,0,12,20,37,-30,-70,-23,-37,-31,-17,-12,-20,21,-1,-22,-5,-6,39,-6,25,-31,-10,3,22,-15,20,5,-8,4,-12,20,10,10,24,-23,6,-13,8,1,1,-12,32,10,24,-8,-35,-19,5,-28,-24,-31,-25,-16,56,-20,9,10,-12,-8,7,-23,-1,-12,-46,-13,-2,-20,-3,4,-11,12,23,5,-9,6,-6,-4,7,-33,-15,-42,-27,14,1,-57,-47,-52,-18,2,10,-6,16,0,-23,6,-8,-20,-10,-5,17,-25,9,-12,-32,4,33,23,5,11,29,34,19,-3,-29,21,32,46,43,-48,-24,-12,-30,-29,-24,8,11,-8,-1,-25,6,-36,-5,-19,12,1,-44,-5,-7,-11,-20,-2,16,18,21,17,11,-24,-23,-6,-6,1,-90,-72,-54,8,-25,-54,-94,-30,-39,8,31,25,60,-32,-15,-4,20,30,18,-22,-13,6,-18,8,45,5,26,-6,0,3,16,-21,10,-11,24,22,-3,-27,-13,-14,-40,5,-92,-40,-30,0,-10,-12,-7,-26,-46,-12,-25,-13,-12,-4,-12,1,45,15,46,55,24,-20,-5,-16,-4,-2,-6,-16,44,42,15,27,54,-21,-5,-3,-24,2,-6,17,25,3,19,-50,-28,-9,-2,-39,-47,-6,42,10,-10,-18,7,-9,28,4,5,-23,-15,16,51,-18,15,19,-7,-26,-22,-44,-43,-99,-74,-39,-25,9,1,-33,-13,-37,-32,14,13,-24,-34,-23,12,10,-19,4,10,-7,47,9,19,24,-7,2,58,-15,-21,-27,-10,-50,-27,-48,-18,-92,-78,-5,-8,10,2,-15,-23,-50,-65,-26,5,9,6,14,-28,-47,32,20,24,21,31,0,31,-2,22,30,-9,5,29,13,-12,-15,10,-13,25,-16,-27,-57,-58,10,28,-6,-23,-38,-33,7,-13,-8,-9,-20,-8,4,-9,22,20,5,14,-13,-7,-15,2,10,27,9,-16,-7,27,-7,-7,-22,-28,-29,-47,-46,-42,12,0,2,-21,2,11,6,3,-48,-9,-7,25,6,-32,-7,-1,-5,3,-14,4,31,13,2,29,7,4,26,-33,-35,7,1,-28,-37,-43,-22,-12,8,17,-36,5,1,-4,3,21,-18,-25,11,-7,13,9,-18,-10,-6,-23,12,-6,2,4,3,-26,-20,11,13,23,1,-27,-5,-8,-55,-39,-1,-20,15,44,24,35,-17,-29,1,24,-25,-2,-22,-20,-7,-2,-22,20,52,30,-2,34,10,28,17,33,26,66,10,3,0,0,2,-14,-17,-53,-56,-27,13,45,37,50,-11,-18,2,17,7,-26,-61,-16,4,-2,9,-12,16,46,-27,2,-14,3,24,34,-2,12,20,29,53,34,-32,-13,-2,-28,-24,8,-5,20,-12,-27,-26,-19,-9,21,3,2,24,49,-28,4,20,-17,29,33,19,30,2,-9,35,13,-23,-13,26,16,5,10,-27,15,42,22,35,29,0,-4,-19,-9,6,-6,11,4,3,-4,-27,-33,18,5,0,8,-23,-27,-1,27,17,-23,-11,0,-2,48,-13,-38,-10,-51,3,-17,-117,-72,-60,-53,9,26,18,47,-24,18,13,0,27,17,-35,-9,-12,-19,16,13,-33,2,-7,9,6,-15,-19,-15,-25,30,-24,-22,-38,-11,-1,14,-43,-15,-32,5,10,12,29,23,37,-36,12,-3,-17,-37,-28,-19,14,13,-17,8,56,18,1,69,4,24,11,37,-13,52,57,67,31,27,-31,-4,26,2,-18,2,-7,-11,14,-7,12,-28,-27,-24,-4,-37,-21,-14,-27,12,-7,-28,2,18,13,-5,21,5,1,26,0,-19,20,44,32,26,8,-33,-21,-46,-29,-22,-1,-21,-26,9,20,-2,13,18,6,4,15,-23,7,5,-32,2,5,-26,6,25,12,25,-8,5,17,-15,12,26,-41,11,7,-7,-15,-26,-14,3,-6,-6,-21,-36,-28,-8,-4,3,-30,15,-12,35,1,-14,-17,46,9,28,6,40,62,17,-33,15,12,3,44,-4,-19,8,2,-69,-54,-29,-18,-13,-16,10,12,1,-7,-31,2,-17,-10,-18,-35,-28,-10,14,0,-26,-3,36,25,29,2,-9,1,-1,-15,15,22,37,39,39,-19,-10,-1,-20,-11,13,5,-1,-10,-24,-28,-26,-34,21,-47,-24,-17,-7,19,6,11,11,3,14,-27,2,13,16,6,64,-6,-23,-22,-8,-34,-26,-36,-25,-61,-33,-16,0,9,17,23,22,10,-22,6,5,-27,32,24,1,-4,-16,-27,12,2,-12,-13,19,8,-6,19,-12,-11,41,-35,-21,7,-16,2,10,-40,-20,-45,-42,-1,-20,-34,-22,-62,-35,-5,-11,-1,-11,-3,38,7,12,11,32,16,-3,5,4,-4,25,9,-4,-29,-23,3,-5,31,53,-34,-38,-28,-13,-29,28,7,-20,3,-16,-5,-36,-36,15,40,30,-1,-5,-7,9,4,11,18,-4,13,13,21,25,25,-20,26,-6,44,-54,-42,-39,0,45,-2,-36,-30,-25,-4,36,-5,-13,-37,-33,-1,2,15,-4,-5,-6,15,14,-37,-12,7,45,7,8,12,-19,-22,-45,-23,25,2,-4,-31,-6,0,-5,-36,-56,-6,0,-9,2,-35,-22,-20,-14,2,-26,-20,-14,-42,-17,-13,26,17,-12,-52,-12,-9,15,46,3,30,15,-53,-32,3,48,12,-3,-21,-52,-9,-43,-69,-48,16,15,18,44,-37,16,-1,-27,-13,29,-19,-17,10,-22,-22,-12,-8,14,-17,21,16,-14,-43,36,-10,15,-38,-29,-31,-12,-16,-15,-57,-38,-11,-8,},

                    {16,0,26,10,-8,-9,1,0,7,-6,0,11,-8,21,-5,36,34,20,-6,-6,2,-31,-5,-24,-42,19,-22,20,-52,-34,24,10,68,-1,-25,-39,19,24,2,48,32,-5,35,-34,-49,-10,-25,11,18,-5,-38,-11,-13,-2,27,0,-4,17,-7,-24,-28,-5,-5,-8,56,5,-33,-70,-6,2,28,29,1,-23,8,-6,-5,-29,37,18,15,3,0,13,-17,-28,1,66,21,-14,9,-40,0,-10,-6,-33,-41,-19,-5,10,18,-14,19,6,33,55,30,-9,34,-1,1,16,16,19,-24,15,-27,-5,-27,17,-10,-26,15,39,28,-20,4,1,1,20,54,-3,-4,-14,-1,-13,23,3,-16,-9,-18,-15,19,10,22,7,14,31,25,11,-3,2,-56,-23,-19,7,-23,-23,-46,16,-1,2,11,3,-32,39,-20,-13,-6,-25,3,-21,16,25,-19,-19,-2,-10,44,30,18,3,15,-14,-2,8,30,-15,-24,-35,15,-19,-2,25,-19,3,36,45,12,-19,9,-15,-22,-38,25,13,21,-16,-58,-52,10,-2,14,23,-8,33,23,-8,18,-36,-2,-21,18,-98,-71,-15,-16,-22,-4,2,-8,28,-23,-49,18,-26,6,39,25,-18,3,-3,-32,7,19,17,42,17,12,-13,6,-11,53,-6,12,24,37,-9,-1,-22,-8,-17,-12,28,-16,-43,7,-2,-44,-16,-1,-7,36,29,-22,25,-13,-17,17,17,32,13,1,15,-13,-3,-28,-1,8,-21,8,6,14,-12,23,-12,2,16,20,-3,27,10,9,47,18,9,48,-33,-54,-4,-1,-3,-10,-12,-11,-35,-23,-30,25,32,10,8,-5,-22,45,-58,1,-17,11,-8,15,-16,4,-48,16,-24,36,1,23,-12,16,10,11,2,58,14,17,-17,13,14,-5,-12,1,-24,22,9,-9,-10,-2,-3,41,20,17,-11,-17,1,-9,-38,-19,-55,0,-4,33,23,-23,41,-3,-2,25,-6,12,20,-64,-108,23,18,-29,-32,23,6,12,-21,4,25,38,7,21,-18,-7,-12,-11,17,-21,-16,-12,-4,-13,19,-19,-50,1,16,40,5,21,19,-15,-6,58,4,-15,42,3,9,38,10,2,42,-8,-28,-48,-40,33,-6,-26,-6,2,18,-17,22,9,-4,-1,-1,0,7,27,25,69,9,15,-9,-10,-18,-30,-76,-28,1,-9,4,-51,-36,-36,4,39,12,-10,1,16,15,18,2,-18,-19,22,-10,-9,9,0,21,-5,-13,-39,33,-16,-40,-22,-3,-15,1,9,-4,-33,-17,-24,19,25,4,-17,-17,27,24,11,6,46,17,36,22,10,4,20,39,0,-12,-3,-5,-5,-16,-29,-21,-11,20,-6,-10,-41,-24,9,3,9,-37,-64,7,18,-4,2,40,-22,-8,48,48,36,17,38,1,2,-7,62,13,13,-40,-9,18,1,9,3,3,9,33,-7,-30,26,-13,17,-54,10,22,-15,10,-5,-47,-12,21,3,0,-32,-14,11,-46,2,27,5,39,13,-4,-9,-12,7,-13,-2,4,22,13,8,24,3,-4,-1,3,6,-20,-5,-11,-23,2,3,-41,-1,6,8,-12,-18,-5,-1,-14,-16,-4,-14,-23,-7,-5,29,51,63,1,29,15,11,9,8,-55,22,30,-17,-16,30,-19,7,20,27,-2,-5,-68,8,20,36,30,-18,-41,7,12,-17,20,6,22,27,-25,-31,-10,-6,9,0,-34,12,-51,-5,-7,-31,-7,36,-6,-17,-19,-37,-8,20,31,17,45,9,18,10,1,-3,33,34,7,-8,38,16,-33,1,-24,16,-3,-10,-5,-9,-23,23,-31,-48,12,-7,-28,31,29,5,27,-12,-19,16,-9,11,-12,-31,-6,-40,-12,-8,-37,8,20,31,33,4,52,25,-30,-32,-34,28,29,4,-3,-12,-26,-31,2,6,-27,-35,3,29,44,25,-15,-6,3,-48,-55,7,15,26,0,0,6,4,9,12,31,4,19,14,19,5,6,17,-5,10,19,6,6,23,44,12,-24,21,44,-13,-46,-7,5,-8,-20,-50,-44,-39,-5,38,16,16,14,13,7,-24,17,20,-11,23,-21,-22,15,23,-17,9,-15,-11,-4,11,10,-1,-26,-39,47,11,-46,24,-30,-21,-4,56,-14,-5,6,3,8,27,28,19,-7,9,3,6,8,19,-12,-8,9,-29,10,13,6,-12,22,5,-29,-9,-53,4,-20,-32,-23,-30,-11,-7,-16,20,-7,13,1,-8,-22,-2,1,6,-9,0,-18,-24,0,35,1,-6,1,38,-20,-15,22,33,-23,-14,-4,-2,-31,-21,-12,11,-20,-3,12,16,-16,-34,-32,-6,6,29,17,-29,28,5,16,3,25,2,-33,-13,20,20,8,5,-32,32,15,9,26,38,40,-45,-53,4,11,-30,-65,-30,-9,-8,2,29,37,-18,-32,28,16,44,14,9,-15,-6,9,37,13,-8,50,-40,-6,8,-33,9,9,-53,13,26,-2,9,-5,1,17,8,6,-16,-11,14,-26,1,10,10,-5,26,15,13,22,52,-5,4,8,-14,-24,4,17,13,25,11,-5,1,-57,17,14,18,4,-32,-49,26,-39,-67,-38,1,-1,27,9,-39,-47,-6,36,49,18,25,-45,-16,16,-8,-2,42,33,-9,32,-10,-26,-34,-8,45,-32,-26,37,-16,-28,16,28,10,65,17,21,4,30,4,20,0,5,16,44,-21,-1,-12,-17,31,-20,16,-4,26,21,-45,-2,11,-13,9,20,-11,-33,-25,28,22,-1,17,20,-30,38,46,2,36,-24,-3,-7,14,-31,-11,17,-35,-28,-6,10,6,4,16,9,-14,2,39,-2,-17,-21,8,14,-1,12,5,-14,45,36,54,29,32,37,-51,-48,2,-19,41,10,-1,-17,-28,-46,-19,-2,-2,33,1,11,13,22,24,13,29,-37,-27,-1,-25,10,5,-29,8,6,-61,11,9,12,17,-2,9,45,6,-20,15,-1,5,-5,-6,39,-19,-12,-15,0,},

                    {-13,27,-21,-6,-19,2,-50,22,18,30,-5,3,-5,-28,-17,25,-19,-16,-7,-3,0,27,13,-23,19,-2,29,10,23,55,-1,0,-62,27,-15,-2,-6,-20,0,-48,-24,-32,23,-22,-30,-3,-23,-5,1,-23,14,-3,17,5,-10,19,36,-6,15,-18,-8,-15,-7,7,-22,-13,33,34,13,-5,-52,-41,-1,6,6,10,-8,11,25,-2,31,-19,16,51,-8,0,10,-3,17,-25,34,45,25,13,12,-38,12,22,2,20,11,-34,4,-13,-33,-17,-28,-14,4,43,-9,-5,22,3,28,-16,-5,33,20,36,25,-5,36,-45,-9,10,-51,-31,-62,-52,-40,-26,-19,13,27,-15,8,-21,31,-32,-12,-31,-33,-2,3,-1,-5,-48,-20,2,26,20,-1,-50,-17,-16,36,-49,21,1,-3,2,11,-35,35,-4,3,-26,17,-21,23,-13,-12,-46,24,-10,12,22,-51,-45,17,5,-15,1,12,-1,-2,15,-1,32,-7,-30,52,20,7,-5,-16,-22,-47,-26,-19,-41,-47,-3,-17,21,-23,3,42,4,-22,-1,-15,-1,-4,-1,21,-35,1,-20,-61,12,30,-21,53,-27,-30,31,-33,-20,3,-34,-21,40,-43,0,-41,-26,-25,33,-2,-16,5,-48,-65,-58,-24,3,22,-20,-61,-18,6,-15,-43,-37,-12,-2,37,-14,30,-27,11,45,-49,-18,64,-33,3,40,-39,-38,-35,-78,-24,20,2,8,-51,-60,-45,-9,1,10,27,-49,-44,-25,3,-5,1,4,28,21,29,25,25,34,-4,4,3,28,-49,-37,-22,-37,16,4,-14,-29,-30,-74,-30,15,49,29,47,8,26,-45,-33,9,23,13,-1,12,3,23,23,6,7,3,23,3,-9,6,8,-12,-8,42,38,9,-33,22,-27,33,9,17,-9,-15,-33,17,-4,-15,16,-11,14,-29,-24,-21,-2,-31,-18,0,-14,-35,-23,-7,25,8,-45,48,15,-41,25,8,46,41,-62,35,16,44,64,34,0,31,40,38,-31,-26,-22,16,25,10,-23,28,14,16,32,2,-22,33,2,-5,3,42,18,-6,-22,-10,-51,-13,6,-10,-28,-6,-7,-28,-60,-43,-19,-53,5,-12,31,11,-24,-63,-62,14,-22,2,15,18,14,5,6,5,9,6,31,22,18,21,30,0,-15,-58,1,45,-25,12,-37,-60,18,-10,22,3,20,9,39,47,16,-8,-8,-16,-31,-30,-2,-30,-32,20,-26,16,-33,-21,35,-15,-60,-6,-49,-22,-14,-9,-1,51,-5,16,2,-18,14,43,-16,58,29,-15,-27,-14,11,10,7,8,-1,-14,-27,-4,9,-51,0,0,5,-40,4,7,2,3,0,28,-10,7,0,-15,-22,-14,-9,13,20,6,-11,1,64,-20,-49,-35,21,-35,-22,40,-5,-11,19,-30,-32,11,15,17,-3,-18,3,46,1,4,-27,25,-8,-4,5,37,-11,-15,-57,-54,-43,22,-14,-41,-16,-37,22,31,58,-17,7,29,-1,16,31,-13,-5,23,22,18,9,3,16,34,15,21,-19,12,-17,7,8,12,-9,-32,-31,-52,-23,-3,-17,-12,-1,13,13,0,-21,-2,-14,-2,17,-4,23,5,11,2,-8,25,2,9,-9,-19,34,36,16,11,9,17,-46,-14,-18,23,-3,-44,-16,28,-19,-23,-60,-41,-11,-14,-24,-26,-40,-6,30,1,-4,-18,17,-46,-54,-44,2,20,-9,-49,-6,2,-39,37,-28,33,1,11,6,-30,-24,34,-14,9,18,-3,-23,1,-65,-3,58,-8,33,-10,-83,-26,-25,-14,-30,-51,-20,-3,-9,54,6,-67,61,-9,-29,17,38,-1,4,35,-26,-50,-51,-40,18,8,15,11,-41,-32,-63,-18,9,17,28,-9,-9,-10,-11,10,1,18,-42,-18,31,13,9,54,11,1,45,5,1,4,-13,-13,-25,-13,-24,-20,-24,-1,-11,9,-39,-5,6,-25,-1,-21,-30,-15,27,16,14,-13,-4,-1,34,13,5,15,41,3,-7,-8,22,-19,26,21,-19,13,-28,-15,42,-44,21,-21,-14,-4,1,19,42,9,-3,29,-2,-11,-8,34,-17,2,10,-26,20,52,8,5,-26,5,-49,52,-7,3,29,-44,-33,4,-3,24,17,-5,-5,10,-38,30,4,-41,-17,-2,-15,17,10,-4,-26,-11,-4,-4,-15,27,-39,17,-26,-34,34,-10,-31,11,-58,-1,23,-19,-34,29,-3,26,-3,43,25,15,-2,13,0,-14,0,-11,19,9,68,-29,8,-6,24,32,24,1,-19,7,-8,24,-4,21,19,8,31,28,-10,14,2,7,-30,-23,-11,-53,-20,-19,-16,6,-33,-16,12,-9,-25,8,-16,-11,-3,-14,-2,10,13,16,17,8,-19,12,3,-3,-30,21,-24,-1,2,-16,2,-17,34,29,44,2,24,-18,6,35,18,-3,-27,-5,42,35,-7,-8,-11,9,16,21,-18,-13,4,20,-13,-5,10,-22,-62,0,1,-3,7,1,-29,-5,-3,-14,41,14,14,9,1,-18,-61,-11,-33,-17,-9,-38,-27,7,-35,-39,13,25,0,11,-6,18,26,-9,25,5,2,23,-18,3,-18,-54,-49,-41,1,45,-15,28,-23,-26,-8,-12,-27,15,36,61,5,-33,-69,-6,-67,-9,6,-17,14,-23,-17,-4,17,27,22,50,15,20,-26,-37,21,-11,-46,21,-42,-32,-40,-67,-44,-49,-25,-35,-19,-59,-31,-39,-27,-71,-4,12,-46,-9,26,35,-13,-21,12,-7,14,-20,-27,21,16,19,-16,-42,21,-30,-16,35,-58,2,-53,-29,-10,-18,-20,49,47,18,9,-6,-14,-62,32,10,-11,-2,13,9,0,-23,-33,-20,-9,7,-24,1,4,-25,-23,3,16,73,7,12,-6,-21,65,24,40,12,24,-9,-25,13,23,13,-4,15,21,10,-29,-1,-4,14,-26,8,-2,18,-25,-12,11,-45,-19,16,-16,-34,34,-28,4,17,-13,-52,-66,0,-22,31,22,4,-52,-38,-36,-6,26,-44,17,-32,-31,-26,},

                    {13,-2,-5,2,-7,10,6,22,19,11,-13,-5,-11,-12,-34,-9,33,-12,4,43,16,-8,-39,-10,-1,6,29,-3,-24,-18,-20,-5,3,1,6,11,12,28,9,8,-23,9,7,36,-9,44,-15,-2,75,47,-27,25,14,16,23,16,-36,31,-7,-3,-16,8,-19,1,19,-9,-45,-83,-21,9,41,24,15,-10,-22,-2,-2,-22,1,-2,33,18,-21,-4,-21,-13,17,66,35,15,-25,-19,21,2,-11,-1,-11,-1,-21,7,12,-18,-5,-56,-10,5,-4,-9,-6,-23,22,-11,42,30,-21,-14,-29,-15,-25,-19,-4,35,16,23,16,27,8,-9,36,12,15,-4,-18,-6,25,9,-4,-16,-10,-6,-23,8,12,-13,5,24,48,-2,24,-11,-13,9,-33,21,4,14,12,43,4,12,22,-7,-19,20,-8,15,-2,-13,-19,1,-16,-14,-10,-9,-11,-22,18,-8,-17,25,11,3,47,-19,-18,3,52,-3,4,-63,-24,-13,6,-4,-29,-29,-28,-1,-34,-46,0,-8,8,-29,17,-10,17,-4,-16,9,23,-27,14,6,23,13,20,55,20,-31,1,-9,25,27,-50,27,-8,-27,30,9,-34,-5,8,-39,-14,2,2,18,12,-20,17,49,30,31,15,2,26,6,17,8,31,27,35,15,0,10,14,9,-18,7,9,20,-3,6,9,-4,32,-7,-30,11,14,-17,-8,13,-10,-28,7,5,-1,39,11,-35,-24,-6,-24,18,12,-42,29,-19,-1,17,17,-10,6,-40,-29,-13,-8,5,-2,-61,-23,-9,15,17,-35,-15,-5,1,5,0,10,-16,-18,0,-31,-9,16,10,-11,0,4,14,-12,-39,-3,-5,-17,-2,44,1,11,9,26,1,-10,-8,0,-46,-5,-9,-7,-31,16,-3,-38,-2,2,25,5,11,11,-11,-16,0,17,20,17,-12,-6,48,2,23,-2,9,74,33,5,13,10,-12,2,21,10,-5,37,-43,-22,-4,19,15,-44,-23,-9,20,7,-14,6,0,7,-37,7,20,10,-2,-1,3,11,-5,0,8,11,-10,-23,31,7,26,-11,-33,-19,1,2,25,-19,-22,-14,-25,7,9,-18,-13,-28,20,0,14,6,59,4,-9,1,32,6,-1,-6,-25,4,-4,-11,29,-21,-13,20,-11,12,-33,-19,-5,6,-9,-4,22,17,22,-6,-65,-27,6,16,45,10,-14,-30,-12,13,27,-1,7,25,36,-2,-12,-21,10,21,-19,-31,7,38,2,11,-10,-22,-1,25,-29,-18,27,10,10,-57,-6,-2,21,-4,-28,-4,-9,-15,-1,20,38,-13,-20,25,6,-24,0,5,1,-9,-51,-41,-5,-8,6,48,5,5,12,5,2,-11,49,22,-10,-13,-38,-1,-3,-7,-8,-18,-14,13,12,39,18,14,5,48,37,25,-1,-5,38,22,19,19,-12,20,7,13,-34,-11,-24,-1,-12,20,-16,27,27,13,-16,-7,-4,16,13,12,-23,-1,-7,-12,24,0,20,2,-22,6,-11,-37,24,20,-15,-9,-15,8,7,-25,-41,1,-7,-28,3,25,13,20,19,11,15,-35,-12,-14,11,-21,-50,27,17,6,-3,31,-3,33,1,2,36,8,-24,16,-29,-25,-1,-26,-15,21,-13,-16,-18,-14,-11,-4,-39,-14,-17,-26,-20,14,-15,1,4,4,-53,12,29,27,23,7,-3,26,3,31,-13,19,10,-5,-9,-20,-13,46,-5,-2,-2,-7,-40,15,10,-6,-2,10,-29,-19,-7,13,25,13,15,22,7,-1,8,1,36,23,28,31,-6,4,9,25,-11,-13,2,8,-13,6,17,-11,-18,-8,-44,-57,3,25,-12,4,2,10,-14,2,15,-1,14,19,-29,-11,18,9,31,23,-4,-6,28,33,-7,34,18,16,-31,-51,-61,-3,24,-12,4,-7,-73,-41,-17,5,6,-20,-7,35,-3,22,3,22,1,-30,1,-5,24,-5,29,32,-11,-18,5,-6,-9,-4,-6,14,16,-11,-4,-11,2,2,-10,-20,6,21,6,-5,-45,13,63,0,-42,-8,13,-5,-13,-31,-4,-2,-35,0,-12,-8,0,12,-9,9,31,-6,-13,12,13,-30,-13,-8,-34,12,5,-36,18,38,9,14,14,3,18,-16,-34,23,-12,-4,-16,-29,-40,-2,-9,-8,-8,-14,27,54,32,-10,-9,26,-1,45,5,-6,11,1,-3,23,15,-8,-9,54,5,13,25,15,2,12,-2,-16,0,32,-18,4,-43,-33,16,-5,8,16,20,36,6,31,15,27,13,22,1,-5,-7,8,10,-12,9,-16,-56,-11,-21,-4,-26,9,8,7,1,-2,-1,-5,-16,-35,2,2,7,2,16,11,4,10,12,-14,4,-13,15,31,-13,17,-8,6,-39,13,-15,23,12,57,0,-35,10,23,36,-23,26,-17,-33,-14,-29,-7,25,-52,-23,-43,-20,-3,9,-9,-4,37,38,15,-13,-6,30,-18,-15,42,-3,-12,34,-20,-17,33,-11,9,-5,-11,-6,17,4,-10,-5,31,-35,0,10,1,-14,-1,7,6,-13,53,-3,-5,4,4,4,-4,-14,-5,-6,-42,-46,-11,-52,-17,-18,17,-10,-11,-21,36,9,8,-17,-4,-22,8,-19,-33,-63,-17,-13,-6,-5,37,8,23,29,4,-15,6,25,9,-5,-20,-32,7,7,0,0,1,11,-6,-9,22,1,-1,8,11,-17,12,22,-4,29,50,26,14,49,-4,0,56,33,7,-33,0,-4,4,48,-36,-26,-22,-29,-15,-12,6,-20,26,58,8,-11,-1,-6,7,25,20,25,3,12,8,6,-10,-16,-5,17,-26,0,-19,3,33,23,50,23,-16,14,24,18,25,12,-16,2,-2,41,-25,-7,56,58,-21,-18,-34,-15,-9,-21,8,-9,-18,-16,-20,-9,-17,-49,-1,-23,9,21,12,32,-9,14,49,9,21,-17,-19,-20,22,-26,14,-21,-7,5,-34,6,13,16,20,-27,17,3,8,26,7,-1,38,-27,-22,20,-11,19,30,-18,},

                    {-1,20,11,-5,-1,11,25,-16,12,18,-4,-24,-16,6,-31,-13,-26,-21,-15,-4,33,-19,-19,5,31,14,19,-32,27,33,-11,-8,-20,-20,10,33,28,15,27,-2,8,-18,36,10,-6,7,1,0,37,27,-26,46,-43,11,11,14,-12,38,-13,-8,9,-14,-11,2,-20,-8,32,0,14,-9,-21,8,-3,0,10,9,14,-12,20,18,39,40,-1,-59,-34,-30,-35,2,-17,-17,-32,-16,-1,-16,7,-11,21,5,1,-5,18,41,5,-11,-53,-53,-53,-18,-19,29,-18,-26,-5,0,-29,-61,3,8,3,8,9,3,4,-6,-2,6,2,-4,-1,13,-15,-9,-22,23,3,15,11,29,-12,16,-25,3,-21,9,3,29,16,36,10,-19,-4,-27,6,-10,0,-3,-3,44,-1,61,-23,3,7,21,-4,54,10,-19,-7,5,28,11,-5,-15,-3,9,32,2,-26,24,-12,-11,31,-1,-26,0,-2,-17,-17,0,1,-32,-4,-16,18,3,-33,-24,-25,-24,20,-15,-22,-43,3,-17,2,-24,-21,-18,2,-5,-6,1,8,44,53,-17,-1,-24,-19,-32,49,-8,-16,-10,-30,-8,26,19,-18,58,-15,-13,-2,-3,-12,26,5,-33,-22,16,11,12,5,-15,-23,-8,23,10,19,-7,-7,12,-7,-6,-27,-6,-19,-46,17,-11,-11,-32,19,0,18,-16,-38,-19,5,2,-8,10,-9,-32,-5,3,18,1,47,7,-35,-27,-18,38,19,10,-9,29,-9,21,13,-4,-33,14,5,-3,-3,19,-27,-16,9,-9,-1,5,-7,16,10,-22,15,-2,2,30,17,-3,4,-7,18,9,6,14,24,-4,18,63,21,-20,-19,-41,-31,16,14,-16,5,-58,8,7,19,-51,-8,-18,-13,-17,-23,-36,-25,35,-32,3,8,7,14,51,3,-11,11,-9,24,10,19,7,38,-13,-30,-36,36,5,28,16,-26,-34,17,17,5,-14,10,-46,-30,-5,-11,10,-18,37,-8,-23,-25,-11,-21,28,1,16,16,-17,-49,-35,3,14,25,16,3,-7,-2,-63,11,13,12,12,-6,-38,-51,-3,-35,10,-29,1,1,-27,-22,-38,-7,23,6,-15,-36,6,-40,17,21,13,49,69,21,0,14,-23,12,-4,-19,2,42,3,11,-31,7,-16,-31,-5,-13,-37,-35,19,-6,-4,-18,4,18,27,24,23,8,40,-8,-21,-22,-12,25,18,23,35,18,-7,-34,1,38,12,28,-8,0,-23,16,17,7,-9,19,-52,3,-2,11,18,-23,-17,1,20,-2,25,-12,-28,-4,7,22,25,-13,-18,-2,2,11,20,0,-14,11,-27,-1,-31,21,-8,-19,31,-13,18,-9,6,-11,13,20,8,-2,-20,-46,-3,-2,21,-15,-18,-2,-11,24,32,-41,-13,30,27,-4,-12,-24,-25,-23,-35,25,7,22,-4,2,20,4,-8,4,2,5,-1,-23,-27,-35,-14,-34,-4,19,-4,15,41,19,-22,1,28,19,51,9,44,1,-28,-26,-2,-14,-39,-11,-1,11,-6,-13,-42,27,18,-32,-6,-30,-12,-16,-40,-48,-36,-32,1,19,-4,-15,4,10,-12,6,4,31,18,3,-1,-14,19,5,-9,-25,4,-1,13,5,-15,-52,-23,-24,-38,23,10,-31,-19,13,-16,43,6,-3,-7,1,-23,-3,5,-10,24,7,10,28,-1,-8,32,12,5,-11,-29,20,14,-39,-64,-17,6,-7,33,-25,-17,17,10,-10,10,-3,50,24,-3,-21,6,12,9,-14,-6,-31,-13,35,19,-13,3,8,23,-6,16,-42,-38,-6,16,-6,-46,-48,1,13,10,-12,-6,-3,6,14,10,13,16,13,-45,-12,4,2,47,8,9,7,-12,8,-12,-2,16,-11,10,22,1,44,4,-5,-12,11,1,-5,16,4,4,39,-20,7,-18,18,7,-11,-24,-36,-21,-13,6,-6,-26,-14,-26,-19,2,-10,33,31,25,8,16,27,18,21,-3,9,2,16,22,1,-31,2,-1,14,8,-1,-30,-12,-34,8,-2,-21,-4,-14,5,18,-28,-29,-4,31,20,-9,-20,7,24,7,6,38,7,-22,17,21,5,-6,25,-13,-15,14,-7,10,3,28,-2,11,0,-1,20,32,-28,-27,-33,38,6,10,-17,-6,10,22,15,-12,13,46,13,17,-4,-2,-28,33,15,53,-4,-21,-64,4,8,2,43,2,-19,-17,-16,-10,10,-22,15,7,-18,19,-4,-7,32,-14,22,-5,-13,-18,12,1,15,20,18,13,-17,36,-6,-18,-8,9,15,-18,-35,22,1,-9,-4,-30,-25,-3,-16,-24,-29,-1,-5,6,-29,-41,0,3,-19,1,37,19,33,16,11,7,34,-18,-8,-5,28,24,6,0,-25,-3,-21,4,-8,11,-33,-21,-31,1,2,6,1,20,6,-32,-25,-12,-4,20,-13,-7,-35,-44,-10,9,24,28,11,11,-30,12,28,-13,37,37,-5,-9,30,21,16,-14,-18,2,2,4,-7,-18,-5,-7,-13,44,37,-14,-9,4,-3,22,0,2,11,-9,27,1,18,-1,6,10,8,17,22,-8,-35,-31,-50,-3,-30,2,-16,5,-5,12,11,25,10,-22,1,24,7,-8,0,-6,-7,-1,-17,15,-8,15,3,7,9,-70,0,27,-67,-28,16,-8,-5,-35,15,8,7,4,-33,4,1,0,-16,9,-20,-23,-14,-1,20,23,23,9,-29,-35,5,-12,29,-20,-1,12,5,-19,1,-12,-44,2,-30,-29,-8,20,-17,26,13,-27,4,13,10,-5,-5,-21,7,-26,-9,-7,-4,-14,25,-23,-15,-17,30,39,14,26,7,31,28,2,0,-3,38,47,53,-2,-22,-9,-4,23,19,29,0,-31,-12,21,-1,0,19,20,-8,2,-15,-17,-22,-10,10,-15,-41,-20,14,-4,28,40,5,-17,16,32,-16,14,11,22,-14,20,3,29,-16,-8,-34,15,17,35,10,-3,-30,-16,18,-10,17,3,15,-3,-32,5,7,5,19,},

                    {19,20,-55,-21,-39,-8,-13,-13,-47,12,32,21,-28,13,-1,35,16,-33,43,1,2,0,7,10,-9,27,-6,32,-34,-24,44,12,19,-15,-11,-47,11,22,22,-40,-4,-9,11,10,-100,-40,2,43,-47,-13,-18,4,2,26,-2,55,17,-15,-10,-5,18,37,-23,3,26,-30,-29,1,-19,28,-48,-8,3,-22,-58,-33,2,-17,5,-23,-13,28,24,20,-15,13,-1,42,30,-27,19,-6,-24,-5,15,-16,-44,-32,-7,23,4,-41,73,16,9,-8,-2,-21,3,-16,-15,3,33,25,15,26,-9,18,-6,20,18,-16,-1,0,5,13,0,-17,-1,9,3,-9,16,-18,1,-3,-6,-11,4,-31,-36,-11,2,-13,-6,25,19,-17,8,14,-2,-8,-48,-5,-7,27,-2,-15,-22,-16,3,19,-5,33,8,26,-10,-18,3,7,17,9,-11,-15,-2,4,-18,26,-15,25,-8,-37,16,12,-8,-4,8,18,17,37,-12,-65,-19,-20,-16,-3,-14,-2,33,1,20,-32,-7,-6,-21,19,11,14,14,11,7,16,-1,5,-35,-49,-3,9,-4,-8,-42,4,25,-18,-51,-43,20,33,-28,-11,23,19,7,21,41,17,10,18,8,1,24,-11,-22,13,-1,-1,37,1,15,12,-1,-16,13,-26,11,36,-21,-13,40,13,-25,17,-24,38,20,19,-36,6,-13,43,2,-2,-32,41,-5,-10,13,-24,12,41,31,-7,26,-16,-30,21,7,-9,-9,-74,-17,11,37,-6,27,-9,3,12,4,11,-11,39,9,33,4,9,56,41,-17,2,2,-12,2,-11,13,13,-43,-42,32,24,-26,-50,-57,-28,21,-7,45,-7,9,-30,7,16,27,-21,-11,-29,-14,-36,-27,1,15,22,0,-7,35,45,-23,-36,-15,13,58,15,20,-19,45,-23,-5,-12,-18,-36,24,-2,-37,-39,-41,-15,-39,-19,-8,-32,4,-3,-28,-34,-26,7,6,14,31,12,10,15,-32,-18,15,4,-8,-9,-20,-9,21,-24,4,10,-12,-22,4,15,-18,0,-8,51,22,7,36,6,6,23,26,-2,0,7,9,-7,7,39,11,-27,8,-9,4,9,-4,21,-22,-13,-12,7,-34,-52,-18,-93,10,-20,-34,-14,13,-12,28,-22,-19,-9,33,-14,-18,-27,1,21,51,-4,23,9,-3,-2,23,8,-10,11,-17,30,12,-63,-8,27,26,-22,-20,-54,17,6,-39,-12,-9,3,-7,-5,7,-2,-20,-14,-23,-32,-29,25,-6,35,28,-5,-20,15,-18,-2,-3,-9,-41,31,-23,8,19,-1,22,25,-24,-13,-6,-19,-1,-17,28,16,2,20,8,-13,-1,19,16,-11,-26,-14,12,24,-20,11,-26,-9,5,-30,10,5,-44,1,-12,-54,3,42,-37,7,-26,-3,21,-25,70,32,29,-8,39,4,28,25,-2,3,23,13,-24,42,12,14,-5,-3,7,-11,13,-14,5,-1,40,21,20,11,23,-5,-35,-31,-19,-31,6,-29,63,36,38,-14,13,-7,60,37,26,-41,24,3,-6,35,25,-25,-10,-16,-21,-7,-7,-41,-10,4,5,21,3,4,37,-6,-28,-28,-35,-31,4,-24,-17,6,27,22,-13,-28,8,43,44,-14,13,15,77,56,-23,-75,-16,14,-14,4,12,-20,16,-10,26,24,-25,-10,14,-13,-3,26,-8,-12,13,-35,-5,-34,-53,-17,21,-34,-19,-65,10,18,5,-17,-7,-23,3,-2,-6,-14,17,17,15,17,22,-17,13,-6,31,-7,18,-17,35,16,1,-57,15,-17,-11,11,4,16,42,-26,-29,-39,-1,2,15,1,-18,7,-61,10,15,-13,-6,-8,-8,58,25,-4,20,8,-13,-10,10,-15,-5,32,15,-16,-2,40,35,26,-17,45,22,29,43,10,-37,-41,7,-10,-14,-15,-8,-27,-11,-14,-10,21,-15,19,14,20,-2,34,32,6,22,8,-11,-21,-37,-10,15,8,6,-7,7,-25,3,8,-25,33,20,-39,-14,-7,-11,11,29,9,5,1,-19,-6,27,6,-27,-18,-28,8,31,-26,-28,15,12,-14,-58,-47,5,-3,-13,-6,0,2,15,-13,-16,0,30,46,-8,-25,-38,-25,3,16,17,18,-45,14,14,-17,37,-21,-33,-2,-45,-28,13,20,16,30,-27,-17,6,11,-58,4,-9,-15,8,1,-28,-15,-34,0,-34,-25,-10,-13,-35,-34,72,-47,5,4,-27,-15,-17,-22,-39,-37,-6,-5,71,4,57,-28,0,-12,4,-42,-9,17,20,8,-17,-9,46,40,31,-18,15,7,30,37,12,-6,7,-11,-10,14,-13,-32,-23,-1,18,11,21,-4,1,2,-1,-10,-54,-35,-5,-13,-40,-1,-9,-19,-2,-38,-49,1,16,40,-21,11,-5,34,39,15,8,-38,-9,1,-11,-21,-25,-6,-5,-6,18,-15,29,6,41,-12,28,10,-2,-6,25,-17,21,34,11,22,7,-34,34,-3,3,-23,5,-31,-7,-2,0,13,25,-21,-5,-32,-18,-4,-10,0,25,-2,-2,12,0,8,-4,-9,-18,-40,-33,-28,30,8,4,-28,10,36,15,-32,13,-10,32,40,22,-21,-7,4,25,1,3,-1,14,-21,11,13,-19,3,-20,21,-7,-13,-33,-68,8,2,-19,-2,-6,56,9,54,13,9,-16,20,32,14,-7,-42,-6,-3,21,35,-17,18,26,7,29,22,-9,10,-28,-14,44,-1,-45,31,24,0,32,6,-6,3,9,55,-6,23,17,45,20,2,28,-35,-35,1,-34,11,-13,8,9,27,15,-9,46,-5,-22,-12,23,2,-18,-9,-13,11,-2,-26,9,-39,2,22,3,-52,1,-25,-43,-77,-3,-26,-4,-14,28,-28,57,40,-4,27,60,9,-10,-8,30,-46,12,-14,22,21,-31,11,3,-4,-30,-72,0,10,6,23,-7,42,21,1,-66,-10,-4,-12,0,4,14,-8,-29,41,27,-2,37,-8,8,26,40,4,-1,14,6,-22,30,-6,6,30,9,-20,},

                    {-5,-22,19,-25,-9,12,9,3,-14,-14,-14,-26,42,41,11,15,21,24,12,19,24,75,17,-33,4,21,14,17,9,-39,-16,-5,-13,-41,-16,4,-17,29,18,4,-3,16,0,35,35,24,13,1,30,46,27,3,26,-4,12,5,-28,-7,-2,31,-18,-21,-51,38,57,-17,0,-25,2,3,-7,-39,20,40,-22,-3,-4,-6,-6,-18,7,1,20,23,42,21,15,13,-10,44,37,5,22,27,0,7,17,-13,22,42,-24,17,-25,-23,8,-6,2,-20,-6,-10,9,-1,31,26,-4,-21,-24,-19,-7,-9,-10,-7,-14,1,10,6,33,43,55,33,4,-16,26,26,0,28,10,-24,-24,21,-19,4,-13,-12,-7,18,-3,9,-16,15,-1,20,19,28,25,-7,45,52,33,5,15,-8,12,22,-40,-10,21,3,21,-18,-66,-9,44,-2,-22,-11,-32,31,-1,0,-22,7,19,24,30,39,2,31,-14,-14,-19,0,1,-15,16,2,8,-14,-8,-66,-50,-10,2,-9,25,-20,28,49,35,-4,-17,7,12,11,12,-21,18,40,-29,13,-2,39,3,-19,-14,14,32,0,8,-7,7,5,-10,-7,36,-3,14,-11,-1,27,38,35,-8,-57,11,-27,21,23,12,-9,-29,-25,-9,3,13,-2,-5,13,-18,-24,10,-5,-17,-3,-1,-11,-3,2,23,7,55,38,37,5,-15,14,21,29,-6,-60,-27,6,4,-1,-3,-42,-14,-17,42,48,-27,10,37,19,-31,-32,-36,-35,-14,-13,23,-27,1,-32,19,3,-20,2,22,4,37,4,37,21,20,29,0,22,-31,-6,-24,-10,-43,-25,-21,57,35,28,8,6,-4,-18,-20,15,23,33,-8,-42,13,16,-1,22,5,-21,-5,24,-20,7,19,-24,-26,-27,-5,-29,-3,21,-2,-22,-38,-37,-20,5,11,-13,13,5,27,3,-11,16,18,-21,19,30,59,30,17,1,-3,-6,-10,-18,-7,8,1,-17,0,12,-32,-6,-17,5,-38,-24,-6,-30,8,0,-18,7,24,38,-18,-23,-38,-17,-25,-4,7,25,-1,-7,12,21,44,37,19,59,45,4,-4,-3,15,11,-28,-32,3,13,5,-29,-78,-27,-21,32,9,-2,2,-2,6,-24,-12,-16,-10,4,12,6,0,-6,9,29,28,-3,3,66,50,13,19,-9,-10,-1,9,-22,-28,8,10,-20,-41,-11,7,4,8,16,5,47,21,-1,-22,-2,-4,11,6,16,2,2,-2,7,10,16,26,4,7,1,11,24,-6,-45,-13,14,-4,5,-15,-11,9,-19,5,40,-16,-49,-41,12,12,-10,-29,4,-2,8,19,33,10,7,0,0,-10,55,47,5,22,-22,29,10,34,-28,20,8,3,7,11,4,21,5,9,16,-3,33,-1,21,-8,-52,-22,-16,-6,-6,-33,-85,-6,-21,-12,-41,32,25,20,28,8,6,56,46,10,16,17,-28,-17,20,-22,-42,-36,-18,4,35,18,21,20,-6,2,-42,-37,-45,-39,22,-6,-61,-45,-23,-13,-6,31,1,6,9,-1,26,34,47,28,24,-8,-13,-1,17,30,-3,-7,-12,3,-9,-6,18,-14,11,9,0,17,12,-9,-59,21,-13,-20,-17,-31,53,-19,-98,-50,-25,35,-40,-7,-46,-4,16,13,-5,38,26,13,-5,7,-14,23,-31,18,24,9,-3,0,-12,-5,27,15,-10,-7,7,3,39,3,-18,38,13,-11,4,-10,9,23,27,-62,-17,52,4,26,6,-65,-24,10,-25,1,-14,5,26,-1,8,-18,-24,-10,-3,41,-25,-7,-15,-5,4,-13,3,51,51,-1,1,-7,8,22,16,-11,-1,14,-7,9,0,13,-24,18,-11,11,-21,-26,35,6,-67,-7,-25,-48,-55,-42,-10,-4,-36,-41,-34,-3,1,5,-41,-15,34,18,19,32,20,56,23,8,6,3,24,36,9,-5,-26,-14,-14,-6,-11,0,8,15,-17,12,13,-7,2,0,18,-32,3,-11,-5,-14,-13,-52,-9,10,20,31,32,15,30,15,-13,39,3,20,41,5,-13,10,-3,10,-22,28,12,-10,4,-20,8,-31,-32,13,-3,-12,8,-20,-17,4,29,28,-28,0,17,29,-2,-1,2,9,4,12,-30,-39,-12,-5,1,26,25,5,0,10,22,-18,-4,-22,21,28,14,7,17,23,-8,16,20,17,37,8,-3,-44,14,23,34,-2,-14,7,-5,3,-31,-43,-11,13,-17,29,-8,7,32,47,3,-4,-22,-47,-30,-21,22,14,-32,-12,-6,-20,18,18,-45,-30,38,-16,36,28,19,30,52,24,11,6,7,18,-9,-15,-27,3,35,8,12,26,49,24,-10,-16,6,8,23,7,-3,22,14,-12,7,-26,13,-5,-7,7,38,39,13,1,10,-13,-3,-26,1,-34,-8,14,-52,-3,1,43,2,-41,10,-3,32,-8,-13,2,-1,-9,39,-22,-19,7,-6,3,21,-54,-6,-8,-5,-15,-11,-57,-40,36,-7,5,10,-43,21,12,10,23,6,-15,-17,24,16,3,-17,6,10,-12,0,8,33,19,-18,-32,3,14,-12,3,3,22,4,11,-26,-16,-5,24,4,-3,5,-21,1,36,1,0,-4,7,-1,8,64,38,-49,-20,4,30,-4,45,-32,-12,15,24,42,11,47,29,23,4,17,31,45,18,-40,-3,-23,9,26,5,-47,-10,11,-14,-3,-25,-17,22,57,-2,-33,-54,-58,-40,-8,42,-29,2,15,14,29,30,47,66,29,-9,-7,17,30,28,-26,-32,-15,-12,-12,-9,-21,-6,-6,-10,-17,-10,11,-3,5,-18,28,26,48,-9,-3,26,28,-17,22,-4,-21,-19,-63,-109,-37,-8,8,-22,-43,-45,68,44,12,15,1,15,37,-1,-23,15,-14,1,0,-31,-1,16,-3,1,-4,21,-3,18,20,-9,-6,8,-37,45,13,12,7,-21,21,13,3,1,-46,6,-19,-9,46,1,-30,23,-14,},

                    {1,8,11,10,-8,8,-7,1,-6,-12,-1,-10,9,-6,-9,1,-11,-3,-12,-1,8,-6,-9,-8,-1,-2,9,5,8,-5,-14,1,4,8,-5,6,-8,-7,-2,10,-8,6,-5,0,5,-6,-3,-14,-9,6,4,-12,-9,-6,-5,-18,-12,4,-7,-8,-7,-12,11,-9,-9,-3,3,-8,5,-18,9,1,-2,-5,-11,-5,9,-6,3,-6,-7,-9,-16,-3,4,3,-5,-2,-6,5,-1,-3,5,-17,-12,3,-14,1,0,-8,-10,-4,8,-6,-4,-6,-11,-11,-6,-10,9,-13,1,-9,-12,-3,9,3,-12,5,-11,-8,-8,9,1,5,7,-11,-10,-10,-12,-7,1,9,2,1,-2,7,3,2,1,1,-1,-1,-13,-5,-9,-7,-7,-5,8,12,-3,-9,8,-18,8,-10,-2,3,-12,-5,8,1,8,2,-11,5,1,10,4,2,-1,5,4,1,-13,-15,4,-8,8,2,2,-12,-3,9,-8,-6,-1,-11,7,5,9,4,-8,-14,-12,5,-8,2,7,-11,-9,0,-13,3,-11,-12,2,-3,-7,-9,0,-2,6,9,-11,0,11,-2,-2,-1,7,-10,9,-12,-9,-2,1,6,-7,1,5,5,5,-13,-11,8,-13,-12,5,-3,11,5,-8,-11,-12,-2,-2,3,3,10,7,2,4,-5,-6,4,-3,9,-3,8,-11,-3,0,-8,-6,-13,2,-4,-12,-5,4,-9,-3,-10,-12,0,-4,-3,-12,4,-14,10,-3,-6,-4,-1,-5,-9,1,7,-6,5,7,-2,-5,-6,-6,-2,-5,-3,-6,-3,-8,2,-7,-11,-1,9,-4,-6,11,-5,-1,-7,3,8,-1,-6,-8,2,-1,-4,-11,-5,-7,1,11,4,-14,-4,-2,3,-1,-1,6,-10,-2,-9,-10,0,-6,4,-8,3,3,-15,6,-13,-5,0,-5,-8,-12,-15,-2,-4,-7,9,-2,-1,6,9,-3,-8,-9,9,-2,-11,0,5,-1,5,1,5,5,-3,-2,-3,-12,-9,4,-7,-18,-7,-8,-4,-3,5,9,-3,-11,6,-3,10,4,-10,10,-8,-2,-12,1,-1,0,-4,-18,-6,-2,-15,-12,-6,-14,-9,2,0,-7,-6,-7,-8,-7,1,-12,-1,7,-1,7,-6,-9,-10,-10,-10,-14,-4,-8,4,7,-2,-13,-9,3,-12,-3,-18,2,-11,5,3,6,-8,-6,-3,-13,-6,-3,-11,10,6,-3,6,-8,5,-9,-2,-8,-11,8,8,11,8,-8,2,2,10,-2,-10,-7,-4,5,-13,-14,-15,1,-14,-4,-3,1,-1,6,5,6,-9,7,-7,-8,5,-8,4,1,-5,6,-13,-9,0,7,-2,-13,-6,-10,-2,-5,-2,-5,7,0,8,-11,3,-12,11,-12,2,-2,-10,8,9,6,3,1,-6,-3,6,-15,9,7,-13,9,-8,-3,-5,-12,8,0,-2,-9,2,-11,-5,3,3,-1,1,1,7,2,-5,3,-7,-12,-4,-10,3,-8,2,-7,-9,0,8,2,-3,5,-5,-10,-3,-7,4,-3,10,-5,1,-8,7,-4,-10,0,1,11,4,-10,-8,-1,2,-4,10,-5,-15,-16,-12,-7,0,-10,-2,-17,-2,-15,2,2,4,-1,-11,4,-5,-15,9,-2,-8,-7,-4,-14,4,1,-11,-1,-6,-13,-4,-4,8,-6,-2,-12,1,-5,-3,-11,2,-9,-3,-16,-4,5,-3,-3,-14,10,1,-10,-1,3,8,1,10,-3,0,-7,1,3,-8,4,-7,-2,-10,-2,-5,-1,4,-8,-9,5,-12,-1,-15,2,7,0,8,-13,9,2,1,-2,-16,2,-1,-5,5,8,-5,3,9,-12,-1,-8,0,2,9,-3,-6,-10,3,-2,-3,-12,-10,-13,-2,12,-11,-1,-10,-7,1,1,-6,-8,10,-1,-12,0,-2,0,-8,2,8,-9,9,-1,-4,1,-9,3,-3,-12,6,-15,-6,-6,-15,2,-2,-5,8,-7,-15,-2,3,-12,-7,8,7,8,-6,-1,-9,3,-3,-9,-1,4,-12,-8,-2,-12,-14,-4,0,0,-9,-2,-9,-13,4,-15,7,-15,-7,-1,-11,1,-1,-8,5,6,-3,-1,-2,7,2,-12,4,10,9,-12,6,-8,-10,0,5,-6,6,-9,-13,-13,1,-11,-3,-2,-2,8,2,-11,-5,-8,-11,3,0,-9,-11,-3,6,9,-13,3,-3,-10,6,9,5,-6,8,-8,-6,11,-11,-3,3,-1,9,2,-12,3,-2,10,-3,11,6,1,-1,3,6,7,9,-6,-5,-6,7,-10,-2,-10,-6,3,-7,7,10,10,3,-1,1,-2,3,-1,-7,-1,-6,-3,-2,1,-5,-8,-13,-15,-12,-10,2,-9,-12,4,9,5,6,0,-2,-5,10,-5,-4,-7,1,0,7,4,7,9,11,-2,7,10,9,-7,10,7,-1,-1,1,5,-9,-2,4,-14,6,7,-10,8,7,-7,-10,-6,6,-5,5,-13,-10,-12,3,9,-10,-8,-5,-3,-5,1,5,-5,9,7,-11,9,6,10,8,-5,-5,8,6,10,-4,-11,-6,-1,-6,-12,8,7,3,2,-1,-11,-2,-9,0,2,2,-10,-9,-5,-5,-11,-9,-7,-11,-10,-14,5,-2,-14,-12,6,-4,4,-3,-2,-1,-13,-14,2,-4,-12,9,3,2,6,-10,7,-2,0,7,-9,3,-4,2,1,-12,5,-8,-11,-10,3,-5,8,-3,-14,2,1,1,9,-2,-7,4,-3,10,2,-12,3,7,-10,3,-13,-2,-4,-7,6,7,-11,4,2,-11,-5,7,-9,-3,3,-3,-7,4,-2,-9,5,6,-8,-5,5,-1,-1,0,-14,-7,-8,10,6,9,-4,8,-3,-2,3,-8,3,4,-11,5,-6,-2,2,-10,-17,1,-13,-16,-1,6,2,8,-5,10,11,-14,-9,-8,-3,2,-19,3,-12,-8,-6,-16,-10,7,-1,-15,5,4,-11,-4,-11,5,-4,7,-10,6,0,7,-1,8,-6,8,-4,-2,-5,8,6,-12,10,0,-7,5,-6,3,4,-4,-11,11,-7,9,9,5,6,-2,-9,7,7,-3,},

                    {-21,8,-20,-9,2,16,-3,3,-16,5,50,3,21,15,-16,0,-49,-3,4,40,39,-8,-17,-7,-31,13,12,1,-19,3,34,4,1,47,-31,12,-1,-39,-37,-8,-12,-7,-20,-27,-33,-29,-14,-14,-27,2,-11,1,9,13,57,16,66,11,-21,9,2,37,51,14,-1,27,-58,46,59,27,14,4,2,-8,-14,-1,6,10,-1,15,-3,-9,12,-16,21,6,7,-18,-3,7,-1,11,28,3,26,9,0,-4,-13,-24,20,-21,21,21,-9,-7,-12,-3,16,12,2,28,-29,-30,-13,-1,24,22,-7,28,24,7,43,-15,5,27,-5,34,43,-57,-3,18,11,-1,-35,-63,-1,4,15,16,-16,-12,-22,2,13,-35,-47,-25,-7,-13,-5,-23,-35,-29,-43,-9,-20,-8,10,37,1,8,13,33,62,17,4,0,-16,-1,51,28,0,18,9,11,57,37,30,-8,13,15,27,-13,6,-39,7,-21,-55,-19,15,13,-5,-26,-17,6,-47,7,-16,-48,-8,-9,23,26,6,24,24,21,-20,-16,-9,19,20,3,-19,-5,-38,-43,-6,-5,9,48,-10,-43,-14,-26,-23,-6,-4,33,46,15,30,13,10,31,6,-27,26,35,0,-9,-19,-14,15,26,-64,-3,27,21,6,25,17,-6,8,19,-1,-24,-1,-15,42,9,44,62,20,12,60,35,53,69,0,20,48,-30,11,13,-5,-25,-39,-47,0,-5,-17,13,-26,-14,15,36,-8,-48,-1,13,12,18,49,3,-9,-7,11,-5,16,7,3,5,-32,6,-8,16,10,-41,-34,-36,-45,-43,-50,-15,-41,-26,-3,-26,0,-43,-24,16,-3,-33,-40,-28,1,27,4,-2,-28,-49,-30,-25,-12,8,-22,16,-18,-17,8,3,7,11,3,-11,7,17,1,7,31,14,27,5,11,31,46,37,-8,-23,-18,2,28,47,-36,-7,-16,-15,20,2,3,16,-2,-16,-11,8,14,27,7,-13,-20,0,-6,69,30,-28,1,-2,43,5,35,12,-21,30,15,13,16,9,-13,-25,6,35,41,18,36,-4,26,-45,7,8,-12,28,-25,-24,14,-73,-65,-38,-24,-18,-12,-28,-64,-37,6,-13,11,-18,-94,-18,7,-8,-50,13,4,12,25,10,-7,-6,-11,18,16,9,7,-5,-39,-14,0,4,3,10,6,-17,-8,-5,-6,-5,-18,-28,17,4,5,-6,-11,-25,-30,-21,-3,-22,7,5,-19,2,-11,4,5,45,0,34,-1,-14,38,16,33,43,19,-6,21,2,15,20,3,-4,8,11,18,-12,9,26,-20,3,-1,-59,1,-10,-17,-1,8,3,-21,-34,4,2,11,1,-1,-9,-2,-3,-21,29,55,30,14,-22,-1,48,22,-7,-13,-24,-20,-4,-1,38,7,-5,-14,-65,40,-30,-20,-19,0,-20,7,1,19,53,-7,7,34,-7,-9,15,31,21,-35,-36,2,13,-6,-30,8,-19,-16,0,4,16,-5,-17,-17,-35,4,-45,-6,-29,-24,-18,21,3,-7,16,-10,17,29,-12,23,32,8,-9,23,22,5,-26,-14,-20,-11,22,25,-25,-17,-14,-8,17,-14,-49,-35,6,-8,7,17,13,24,31,26,14,23,17,18,19,10,-15,-43,-45,13,-13,-31,-45,-16,0,6,-33,24,19,-18,15,-12,1,-4,-25,-28,-47,-25,1,-11,-36,2,21,-43,8,-2,16,22,-6,-47,-11,7,19,29,-14,28,19,14,-5,31,17,51,9,-5,-25,18,37,17,20,-18,-26,85,91,26,-40,-16,-28,11,5,20,-32,-14,-6,23,31,52,10,20,-2,55,24,26,14,19,27,-30,-4,5,35,8,-21,-29,2,-3,20,37,6,-6,12,6,-9,14,31,-7,14,19,17,40,-10,-20,-6,-27,25,-7,-7,28,47,3,-8,6,4,45,39,-9,-13,4,4,4,-18,4,-31,-2,-7,-10,-36,-27,15,24,27,-12,1,7,41,4,-23,-20,-32,15,15,-7,5,0,-11,3,21,-1,2,24,-3,57,-13,12,-5,11,-11,6,-18,-19,14,19,-27,-8,-20,-4,14,-47,-36,-25,3,-3,-11,21,-20,33,6,-12,42,25,-15,51,20,21,11,-3,35,55,39,-4,-2,12,-26,-16,-5,-10,6,19,44,-4,9,-42,-8,-7,5,-2,25,-27,-16,-5,4,8,24,14,23,23,2,-16,-23,6,20,38,-3,37,-11,13,15,31,-17,-16,61,23,10,26,23,-20,9,-36,1,-4,9,-16,1,26,-1,-29,-19,1,19,21,6,-21,15,9,-7,1,-24,-16,-5,23,16,8,24,33,26,-14,-4,-18,4,-14,-27,-34,-13,-17,-30,-14,-18,6,13,-5,1,-11,7,-7,-14,13,17,-23,8,8,24,36,2,10,-15,-1,8,-39,39,-6,-18,5,16,40,17,9,24,-40,-10,12,15,-15,13,-5,-2,-11,-2,-21,-42,-18,-2,17,-19,23,43,-8,-5,18,42,54,33,19,2,12,43,40,27,-13,15,-12,-24,9,-6,3,12,19,-19,-7,-1,-6,-24,26,2,14,11,21,-8,2,-16,-21,14,-14,-36,15,-20,3,22,18,-18,3,-33,-34,-10,9,2,1,-15,6,-7,-46,-7,32,7,7,-6,3,-10,-4,28,-13,46,28,-16,3,0,13,19,4,14,-44,18,25,-54,-3,1,-37,-17,-14,-48,-24,-1,-36,-35,22,34,3,24,37,19,-9,36,18,5,-25,3,14,24,35,14,1,11,14,-37,-23,7,26,39,8,-56,-15,-3,-12,17,-34,-84,-15,-27,14,-30,2,-24,44,9,13,-24,-4,15,9,32,22,-7,-73,-18,-23,18,-13,-60,-49,-16,-1,-1,-5,-21,15,42,18,9,14,10,1,7,16,0,-46,29,44,36,-13,-18,-3,-23,-21,11,2,3,-14,-25,19,14,23,43,9,-2,43,-21,28,28,19,18,-20,-46,18,21,15,-16,-16,8,8,18,6,-11,11,21,16,1,},

                    {15,16,-1,6,32,-2,12,2,12,21,12,31,45,19,65,20,-3,43,5,23,1,-40,10,6,-6,-11,25,8,2,-26,11,10,-20,2,1,-25,18,-3,-23,72,22,9,14,-16,-3,-31,-36,-13,-13,-16,3,-26,-61,-37,2,-2,7,17,-53,5,-23,24,41,11,5,44,-13,12,6,-24,13,6,-2,-7,19,18,10,22,1,14,-27,-25,6,-11,2,-31,4,-11,-8,36,36,42,17,-11,0,16,1,16,-4,-25,24,21,-1,2,-4,29,49,42,10,-2,-28,-40,-32,-19,15,3,16,-25,-55,8,12,32,8,8,37,44,0,32,-31,-18,15,6,-21,-7,3,27,-20,-21,-4,19,14,-4,-1,-1,-7,16,-21,72,5,1,5,-13,13,-20,-59,-37,8,-27,12,0,-47,-67,5,-26,-24,20,-8,-3,2,24,11,-5,-15,19,13,32,6,-51,4,-4,-4,21,-32,-15,58,28,-40,-80,-49,39,54,48,-45,-62,-49,0,-15,13,25,12,10,-2,39,28,36,-20,-12,-1,-7,-26,-6,30,15,11,25,1,23,-33,-1,42,37,20,26,24,34,16,-45,-25,-3,48,32,28,-72,0,-11,-9,9,25,-3,16,19,-24,-3,-24,-29,24,-17,24,-12,-37,-34,-27,26,-2,-18,-64,4,-7,19,23,9,-41,-58,26,-2,30,3,-11,-11,50,-28,11,15,-13,28,45,1,-9,15,13,4,16,6,-1,9,-19,-41,-6,-17,-41,6,-5,-9,4,-35,-4,-9,3,11,-13,-24,5,19,64,67,23,26,-48,1,12,-11,-31,-14,23,-10,-6,17,14,-20,-6,2,9,16,-23,-4,-18,-28,-53,12,45,0,-13,-44,-18,17,32,8,-14,3,21,32,-3,21,43,-4,-35,42,15,5,31,-13,13,3,-9,5,14,20,0,-10,28,19,10,7,15,23,37,-18,0,9,-2,18,18,-11,5,-5,24,-43,-21,12,24,-16,-17,-55,-6,37,30,-18,1,-12,-12,18,72,-41,-17,3,53,13,-17,-23,-29,-20,-25,-10,-1,-14,-41,-5,-24,-20,-36,25,34,39,35,1,13,28,16,19,36,3,14,-1,27,49,-12,-48,-11,14,16,-26,-69,12,-38,12,8,12,24,44,-40,-21,-14,26,35,9,-2,28,6,21,28,-6,15,26,1,-31,-18,-6,28,3,-11,8,-10,2,5,-14,-3,15,-6,-4,-4,42,18,40,-7,12,23,22,13,-8,41,1,45,6,5,-33,-9,-4,4,1,-11,-7,0,28,-9,-12,-9,0,6,13,-1,-14,-48,-1,40,-12,-32,39,36,37,3,-7,18,-1,-9,-28,-24,-16,8,15,-7,-50,-52,43,-15,3,1,-12,-26,22,9,-5,3,-34,-21,-2,-25,-23,-26,-7,-8,-24,-71,-10,-84,-3,37,-15,-11,-7,14,24,26,-8,21,25,25,-6,53,23,-17,-7,1,22,15,-6,-2,14,7,-61,-26,-1,-17,22,8,-5,10,-2,-62,-33,-52,-6,28,-18,-12,-17,-25,11,31,-13,17,0,30,33,69,-3,7,-6,3,42,15,1,30,25,8,6,-29,-6,-11,20,20,-15,-8,11,23,8,-21,-14,7,-19,-34,-18,16,46,84,-33,-61,-31,2,49,29,-4,24,-22,7,60,-13,29,14,-22,-14,21,-47,-8,8,5,27,-8,-50,5,2,32,23,43,19,23,62,55,-35,-18,-16,34,41,28,-34,-80,-66,37,16,26,-42,-19,-30,-12,-15,11,-25,4,-4,-30,-20,7,-48,-26,7,10,-1,38,-32,-32,19,27,35,24,17,-49,13,30,18,28,13,-29,8,2,8,13,-6,-13,50,-14,-16,10,6,-11,45,27,-1,-3,-44,-81,-37,16,-6,-50,-6,9,9,-33,-54,-14,43,40,22,-34,-8,-14,72,26,6,20,-12,2,0,6,-9,-3,16,-6,-42,-25,-29,-6,-3,19,16,-17,-5,3,-10,49,53,36,63,-10,-45,-9,21,33,25,-36,-27,9,-32,-26,50,-8,13,32,-1,3,-9,-2,-4,11,-20,6,12,-9,10,14,0,8,11,-10,11,-9,54,12,-4,4,-9,22,0,15,-1,10,6,38,-36,-21,-18,4,-24,-5,7,4,-23,-16,16,-7,-6,8,19,-8,-9,14,-11,40,-11,18,23,61,52,14,-10,-5,17,14,38,13,28,8,12,17,32,-11,-50,11,28,-14,-39,-76,-28,56,-15,-6,-22,-38,18,9,-18,-72,20,-13,-1,14,3,-16,-19,23,48,-19,-37,8,17,28,13,-30,-29,-37,11,6,32,2,-4,-29,5,46,43,-9,-2,-6,-19,8,-43,0,-7,22,18,2,-10,0,10,37,33,20,23,6,6,-9,7,17,-3,7,8,-17,-27,-20,40,12,3,-3,-15,24,17,26,8,-1,-2,17,19,-3,-5,5,40,18,76,14,4,0,-3,9,20,-3,12,49,19,-39,-31,-3,-5,26,-13,-36,-19,-14,18,8,-7,25,-11,22,63,4,27,-33,-16,-1,-3,25,-18,8,6,-42,-5,1,7,-4,-15,-9,2,8,24,44,70,-25,-13,4,27,38,35,39,-16,-1,-34,-23,-23,-10,18,1,2,31,-28,-12,-3,-2,20,0,33,-12,6,11,-5,5,-36,-19,-7,17,-7,-32,-22,-19,0,23,3,-6,-30,6,0,13,41,22,30,-17,-4,3,29,-33,-6,-50,-2,19,6,-48,-48,7,-5,-3,-13,-5,-45,14,27,27,-7,-24,26,-7,52,33,-3,40,13,-10,40,-12,-9,5,-1,-11,1,16,26,-9,-43,-8,16,6,-43,-31,-13,-10,3,-13,21,64,61,-12,-17,-27,42,47,28,-7,-108,-47,-4,-52,-27,16,-19,28,8,-36,9,-10,11,-3,3,19,8,-42,13,13,17,22,19,14,-36,0,1,7,-11,12,17,16,21,-25,10,31,26,3,11,-34,11,-17,-2,27,-2,-36,43,4,-26,14,18,-1,32,20,-16,11,-30,-96,-14,},

                    {-2,8,0,18,19,2,0,21,-2,6,20,36,2,14,25,-23,-46,4,-20,-8,15,-25,6,13,22,-2,-1,24,13,1,-3,-29,-20,0,8,8,25,-32,-46,-31,15,-23,2,-42,-12,-60,-35,2,-11,-7,20,-36,-43,-12,-14,-17,47,19,-23,16,-5,16,58,4,7,23,28,6,27,-7,22,-11,-1,1,25,19,22,35,2,33,-23,6,2,-7,-28,-40,-26,-57,-34,44,-19,43,7,-34,-8,12,30,23,-13,11,10,15,-50,-47,6,27,24,49,8,17,-4,-5,-48,0,-15,0,47,3,-40,7,10,19,20,-18,14,-3,-5,7,-23,-24,11,-11,-10,-24,-6,-11,19,24,3,33,23,24,2,17,10,-28,-13,-30,-23,-1,7,-19,-3,-71,-61,-16,2,-26,-8,-21,-27,-18,-23,-29,17,-21,8,-3,4,39,46,-17,9,1,28,41,13,-37,3,0,5,22,-19,13,40,10,-14,-33,-40,38,54,33,8,-47,-27,24,11,-14,-2,22,-21,-45,4,27,4,-5,-12,-37,-30,-36,31,16,17,0,7,1,43,-28,3,7,-4,-18,10,2,22,-8,-14,6,25,39,42,14,-6,31,-7,-15,19,8,7,2,7,-19,13,-27,-14,-3,-13,26,44,-31,7,4,7,20,29,-22,-25,-7,3,5,74,-20,-48,11,2,16,30,20,4,15,-13,-1,4,-21,17,16,-12,-22,-11,-22,-9,50,-7,-2,18,-28,3,32,20,18,10,3,0,14,-25,11,29,21,8,13,-25,10,3,8,1,-48,-30,-59,-45,-13,-44,-17,5,16,26,-8,10,17,-18,3,19,26,30,28,-22,20,-11,-8,37,14,17,-20,-4,7,-2,3,7,-13,-40,13,0,17,-8,31,-17,1,81,47,-7,1,-52,8,9,-12,-3,20,9,12,22,50,21,7,-6,-21,34,30,16,9,-2,-33,-39,5,8,4,-18,-46,-25,4,-25,-11,64,12,48,1,33,29,40,10,-8,0,21,16,-20,1,16,29,27,11,0,2,-4,-7,-2,19,28,-5,-10,-17,-21,-20,16,-2,-12,-5,-10,-32,32,57,-4,0,4,-11,-17,15,31,1,-23,-9,-1,20,12,23,15,19,7,24,18,28,38,13,6,13,27,33,-17,-19,0,-36,10,11,-24,-8,37,-28,-37,24,17,37,9,-20,26,12,14,-2,-14,14,0,-4,9,-35,8,-8,28,-12,0,33,-15,-9,-19,-4,-7,27,-6,-27,1,-4,-6,-10,32,16,16,-36,27,-5,49,2,-2,-10,5,23,-1,-25,24,0,-11,-8,11,38,19,26,10,2,11,-44,-47,10,0,14,-20,-68,-43,-61,3,-34,18,-22,31,16,2,13,37,14,-5,-2,-10,-27,29,-6,-14,-3,-3,-12,-33,-31,-5,15,0,9,31,20,2,13,16,52,28,16,0,26,-23,-16,-2,-21,-8,38,9,-21,-33,-48,-71,-2,26,9,6,-4,-3,29,-2,-9,-3,-15,14,5,-7,29,14,28,12,10,-28,4,7,36,37,35,-33,-4,-34,-31,-1,2,0,-41,-21,-36,-16,10,14,17,8,15,-2,-11,19,31,14,4,17,34,-10,-23,-4,-13,26,29,-7,-38,-6,15,41,-2,-3,39,-17,-9,-3,-24,0,3,-30,-11,25,92,-8,-28,-25,13,-1,-23,-19,8,-17,8,-26,3,9,45,13,-40,-58,-23,11,43,-6,15,-28,5,8,18,22,36,28,-22,8,12,24,0,-1,-20,-14,20,24,11,-14,2,-9,21,18,-2,-33,24,22,27,81,41,-23,24,8,18,37,61,20,3,-7,-5,7,-10,-12,16,13,10,-12,-12,-15,65,12,27,-22,-6,-1,13,-10,-15,-27,-15,11,-26,4,3,22,39,18,-13,-18,-12,8,78,7,2,-19,24,-39,-19,-7,-8,-48,6,-29,-38,-47,0,9,23,-6,-19,-11,6,-4,13,54,14,13,18,-17,1,-12,28,46,20,-9,-8,3,-19,-34,30,-7,-6,15,-50,-46,9,-10,13,34,-25,-9,-15,34,-1,15,7,3,11,-16,11,-25,-15,26,3,-19,-1,19,-10,12,18,2,-5,-2,-24,-51,-38,-1,-22,-7,16,-6,7,-31,30,2,10,18,29,-5,4,-17,19,43,-5,12,1,-4,-14,-9,26,2,21,-7,3,-11,2,6,-1,-15,0,-31,-16,-26,12,18,-3,21,8,31,21,44,-2,-13,21,-4,28,-72,36,-11,0,5,-12,-5,1,-20,46,-17,1,-16,7,19,12,8,-8,-17,29,30,-7,11,37,-49,-62,2,34,-17,-14,-26,-25,-18,5,19,8,11,-8,3,8,1,15,20,18,8,10,24,24,-9,7,26,-1,-41,-14,-41,-54,-47,-3,15,-20,32,-25,-12,0,35,18,22,3,1,-4,6,-25,-3,16,-1,60,-4,29,-2,-7,-48,-13,-10,-9,63,-12,-48,-13,-6,-5,26,-8,-35,-6,-13,-4,22,10,10,5,5,21,14,-7,-26,-6,19,16,-14,4,-5,14,-8,2,7,-3,0,8,-11,6,7,30,48,25,-24,-1,-4,-37,-60,12,3,-10,3,-12,-24,-6,12,35,25,16,17,2,-17,-5,27,11,-4,97,16,20,32,1,2,-56,-12,-5,13,17,-25,-36,-11,33,15,34,-7,5,23,-29,-27,60,19,13,-2,-5,-6,-17,-25,-2,-34,-30,16,20,8,-16,10,15,8,-2,5,-15,9,12,28,16,1,24,-9,45,-1,-36,16,-48,-11,-5,-29,-29,7,-2,-15,-4,17,-21,15,24,-38,28,41,-5,-7,0,-4,13,-18,20,20,36,7,-19,-15,-9,22,17,-17,-58,-21,16,4,-16,10,36,42,23,-19,-15,-16,29,29,-17,-17,-3,-36,-1,-5,-6,-4,5,-9,-26,-22,13,-10,-14,-2,13,8,7,-24,19,2,12,12,42,29,35,3,10,10,-12,-15,-13,20,-8,-16,-22,-4,-2,6,26,4,-17,-21,21,},

                    {-6,-28,-17,-5,9,1,-3,-10,7,-9,1,10,-9,-12,13,40,19,45,-1,24,2,27,13,16,-10,-21,-17,34,-12,-49,-12,-47,4,-13,32,-4,-23,16,19,-24,10,48,-1,5,30,11,22,11,-33,-24,23,-10,10,-5,-43,-31,-23,7,11,-37,-12,18,6,-22,27,-3,38,-27,-18,-12,18,10,-18,-11,4,19,9,10,5,1,-20,-1,-15,17,-29,-25,-4,30,-21,-7,7,53,42,19,-33,7,-24,-11,2,-5,-7,16,-15,-21,-1,23,29,0,-27,17,4,17,15,-20,7,-11,-8,-11,-24,-18,-10,1,-22,3,12,22,9,-4,-32,-15,61,23,1,-5,13,54,4,-6,11,-3,52,24,19,-1,6,42,-4,2,-2,30,23,-1,12,3,-13,-3,-32,-55,-14,15,-10,-11,0,-52,-47,-1,-8,-24,7,33,-14,-11,3,5,28,-1,-47,-11,2,-8,-49,-11,-14,21,19,45,-58,-18,24,21,26,28,8,-8,-12,8,37,10,27,34,-6,-1,24,-6,-13,-21,-21,-16,16,-12,-5,-2,5,-1,6,-8,36,18,3,19,27,-1,-6,-6,23,1,28,-10,2,6,23,-21,-45,-25,1,2,30,-31,-17,-27,-20,35,46,-10,2,11,9,11,1,-14,-18,-12,-20,14,15,8,26,25,-11,-14,1,-23,-23,-3,-30,-29,-6,-38,-38,-47,-3,-25,1,-10,-29,6,5,30,47,-3,2,8,3,11,44,3,-30,-40,-16,6,-26,13,20,-2,-26,-7,10,16,-15,-14,-21,11,44,37,60,-2,15,-15,20,66,38,37,7,-29,12,9,7,20,-17,-15,25,12,-14,-11,-8,61,48,31,19,22,-14,7,2,4,1,18,4,-17,-29,17,24,8,-25,29,-14,15,27,-6,0,-4,-14,18,12,-1,-26,3,-16,4,-18,4,18,7,-12,-10,4,23,10,-7,15,24,-26,10,6,-21,3,15,-13,-45,-20,-1,46,27,19,-30,10,3,27,6,1,-7,-16,-12,-33,-36,50,23,-5,-16,-12,6,26,2,-12,-20,-15,-1,1,-30,-39,-9,18,18,39,-2,25,-11,21,106,91,48,4,-17,-28,13,76,8,-15,-55,-18,8,-42,-43,-20,26,8,-2,32,26,-36,-17,-6,4,4,-8,-15,-2,-19,8,65,27,-22,30,15,15,-17,8,38,-16,3,0,-20,-30,-8,-15,-30,-2,-9,22,11,-13,0,2,3,6,0,9,18,-9,-31,-9,8,-21,8,6,-37,-33,2,5,38,22,-4,-7,19,23,36,-21,2,6,-5,13,-21,-43,13,11,1,9,5,14,22,-24,12,-10,13,18,-26,-6,-1,-24,-2,19,4,-29,54,-6,-15,8,23,9,35,-46,-23,-9,13,23,17,10,-38,-3,10,-11,-28,15,-17,49,-3,31,7,-9,-6,32,18,-2,-4,0,-14,19,9,3,-23,-42,9,18,29,-23,27,10,16,23,-20,-43,-11,6,2,-33,-46,-21,-12,37,-2,39,31,-4,-9,-4,-8,12,28,-8,-11,0,-30,14,36,22,-29,-19,-10,-5,51,30,12,-3,-15,2,20,-2,-13,3,25,18,-3,-26,-10,-13,-5,-16,-13,-2,-23,-27,-23,-19,12,3,-9,31,62,30,49,27,28,58,-4,-5,39,8,-39,-33,-42,-20,38,16,-13,-2,16,26,-1,-31,-2,46,-2,12,30,26,-23,17,15,12,6,44,-17,32,8,-17,-90,1,12,26,-35,-50,-61,-7,13,74,-18,-24,33,-3,10,19,-20,-20,0,18,-5,51,41,33,11,57,-23,4,18,33,-15,36,-48,11,-9,-29,-29,-22,0,0,25,-51,-25,29,24,29,5,-9,15,10,-31,38,18,0,-23,-12,-5,-43,-13,21,-9,6,-31,14,13,35,62,5,14,-54,-56,57,37,11,-28,-31,-37,-34,14,9,-5,2,-28,25,-13,-8,-4,24,37,2,6,-40,-26,-14,36,1,13,28,-14,-22,1,33,27,-10,-9,-20,-18,3,-7,23,15,-10,37,8,-32,-22,-14,-9,2,12,-9,-1,6,-22,1,25,9,2,-1,9,28,10,34,-12,22,-15,12,9,-19,11,6,-4,-2,-11,-62,-42,-2,-25,16,18,-33,-10,-16,8,27,21,9,25,-10,24,-33,-35,-1,-14,33,-2,8,2,1,-2,-26,18,9,0,-22,21,-5,-8,-13,19,7,-35,5,21,2,36,-47,27,28,25,10,-22,-17,-44,26,-14,-21,-30,-11,1,-33,-39,5,-33,-2,41,-23,-24,8,37,36,-4,-20,13,-23,38,30,20,-24,12,-6,-11,26,25,-8,-10,-42,-10,7,-14,-13,-25,25,13,-15,-3,13,14,8,3,20,10,-2,-22,-12,0,-12,-5,-30,-18,-19,-17,-22,-19,-25,53,33,40,-18,29,37,17,44,32,-13,2,2,-9,-13,-5,18,34,-16,21,17,-10,-33,21,1,-10,64,38,-17,22,4,-6,-1,12,-27,3,-3,-12,-15,31,16,-25,15,-11,17,-3,6,-24,13,31,-38,15,6,23,-32,-3,9,13,7,29,-21,-15,-5,7,21,20,-33,3,28,10,18,54,8,74,28,-3,-4,-12,-22,-15,-5,-27,12,4,-28,-20,-17,-3,13,3,10,9,16,6,45,10,-11,-15,28,-60,-18,-41,14,-43,-2,-17,-33,-22,58,8,10,50,14,9,15,7,10,20,14,-2,18,0,5,-18,23,-30,-23,-2,14,-4,5,-3,37,-17,-8,-10,-23,-24,-16,-10,3,4,37,-32,13,-10,-25,48,44,18,10,4,21,63,25,19,-14,23,25,-16,-23,-20,-43,19,-8,-28,27,34,-12,-1,26,32,59,32,12,8,-4,21,30,19,59,29,29,-7,-26,-16,-24,12,8,22,29,-23,-4,0,4,19,16,4,10,16,15,-10,12,-4,2,14,4,7,9,-26,-32,17,-20,11,-17,0,-6,5,6,-26,-25,-2,19,31,0,-41,26,-2,-31,23,7,-21,-23,19,},

                    {57,-1,35,22,-15,-3,9,-8,-19,-51,-3,16,-40,-25,18,5,19,21,18,-49,16,-29,12,50,35,-23,-13,-10,28,25,33,-12,27,-3,-12,-19,9,40,45,18,73,23,24,29,38,16,28,22,-25,26,30,19,-36,-40,13,38,-32,-7,-10,-20,20,-6,-2,-7,-23,1,21,25,34,5,-36,-11,37,-2,12,0,11,21,6,-5,-19,5,-19,8,-15,-44,-12,5,4,-20,9,14,-11,-21,-16,-2,29,6,30,15,-14,20,26,36,53,-42,-3,-21,47,63,15,-2,6,9,19,-25,1,16,-34,-13,-11,-50,-44,18,-42,-23,9,-19,-17,29,-13,-5,5,5,-8,34,16,-7,18,-18,-14,-18,13,5,-1,64,81,34,61,29,-12,53,44,19,23,-26,-29,5,-6,-11,-1,-16,-8,-7,-16,17,-34,-5,26,20,15,11,-12,-42,29,24,27,11,-32,-10,-23,-6,-3,15,-8,33,28,37,66,40,10,20,10,48,23,9,-20,-34,-6,27,-21,8,32,13,-3,41,32,3,-3,7,14,8,-1,6,-4,20,71,58,61,43,23,-1,40,6,-27,31,12,-15,18,7,-10,14,4,-29,19,-2,-7,30,-15,4,1,5,-10,18,-5,-14,24,-5,27,42,16,-15,16,32,35,4,4,-3,22,-21,8,27,-45,-70,-27,-35,-35,-9,-53,-58,5,-17,-10,39,-54,-47,20,20,14,10,-2,-7,45,4,-12,-8,7,-1,43,63,14,-13,-27,-14,-29,-2,4,-8,19,-4,-33,38,3,-15,-18,6,-5,32,27,40,43,85,20,23,13,29,9,-1,30,29,24,-23,-33,-11,58,22,20,21,-29,-37,-5,-3,48,-14,13,-12,-7,24,-17,7,-5,13,-19,-2,25,9,-22,-7,14,21,22,12,0,18,-5,-5,13,-6,-14,-32,44,-1,16,25,25,4,-25,-15,-31,-10,12,13,-5,-23,-78,48,38,10,7,-14,-12,7,-26,1,-2,-16,-38,3,-3,11,11,-1,40,39,-15,11,40,34,21,5,-10,-3,-4,19,5,6,-39,-28,-22,56,-32,-9,-44,-40,30,22,26,52,7,48,40,14,-1,-45,20,16,28,8,-4,2,30,18,33,32,15,-10,-7,1,24,-18,-6,9,-4,18,-24,6,9,-31,-7,9,17,14,20,4,11,39,-1,13,-2,18,20,34,9,-14,-10,3,-17,3,41,29,-10,49,13,-3,26,10,-26,17,15,-6,-1,-43,-51,28,-14,-16,18,-20,-6,11,0,0,-12,0,5,27,-45,-2,-1,-19,30,-7,12,8,-34,13,41,15,7,-14,-14,5,16,19,7,-26,10,-1,-17,-19,16,-6,27,13,-28,3,-20,24,13,-8,-20,8,17,31,21,-8,-13,-16,-22,22,15,61,-19,-4,11,12,-16,40,39,16,-3,-1,-3,-4,-16,-39,-40,1,-32,-18,3,14,37,32,0,11,2,35,11,32,-3,3,24,-12,-12,6,29,63,2,13,10,-5,4,36,56,2,-9,-37,-11,24,-36,-22,-47,-17,-36,-24,-6,6,16,22,-5,-4,27,40,16,44,1,20,3,-7,-17,-2,-18,-10,-14,-14,-10,-23,-5,45,28,-6,11,-24,-16,50,73,102,19,44,27,55,8,-17,-30,38,-34,-6,18,-12,28,59,4,10,17,12,23,0,0,26,5,23,30,46,-22,3,-1,18,39,23,-12,-22,21,29,5,-28,-9,-5,5,9,1,28,12,4,-9,-23,-21,-13,-19,1,0,-1,-4,-40,18,44,19,9,-19,15,15,-3,5,39,-26,-20,-37,-30,-21,34,-35,-1,-3,10,7,22,-24,-13,31,30,14,0,1,14,5,-9,0,17,10,26,-6,31,62,42,-22,26,44,79,61,47,-16,-9,20,-16,-17,7,-20,3,-35,-45,-45,-14,-54,-55,22,-2,1,29,36,48,-4,-7,0,-1,4,4,3,23,-27,9,34,-19,27,-18,19,32,16,17,3,16,39,6,-23,-16,0,-13,-32,1,-27,-9,5,-3,9,18,-4,31,-3,21,12,4,-4,5,4,-23,44,1,22,2,26,28,-2,6,13,-24,4,-35,-17,2,1,-6,-10,28,5,51,20,36,11,18,17,27,-12,-11,16,3,-5,-13,-5,-31,20,-13,4,41,22,-5,17,-23,-22,19,-33,21,-31,-51,-32,47,14,18,15,-28,-7,13,-10,33,-18,-18,-24,-23,-4,-9,9,25,14,-4,19,4,-38,-37,-9,-38,0,-7,9,23,21,-5,-4,-33,2,39,22,-2,-27,-34,-29,-16,-33,-15,-6,8,3,16,35,28,23,-5,15,13,12,19,6,28,8,-23,10,19,25,-5,-11,-16,4,-14,12,12,-26,-16,-43,-20,-11,-41,13,-16,21,23,-17,0,-2,-7,8,31,-41,-4,11,4,62,-12,26,-19,-1,42,60,-11,28,1,16,64,24,56,26,-8,9,2,-7,23,11,-7,-8,-21,-42,28,-55,-22,-4,-20,13,21,0,-12,-2,9,53,15,-4,-9,24,-9,-11,-9,-6,15,-33,-17,-15,-18,-2,4,2,-7,46,41,13,30,-13,52,24,35,17,38,4,9,30,17,13,72,3,20,57,6,-14,-24,5,28,30,16,24,-23,23,19,33,9,-20,-35,2,-22,14,-19,1,-6,37,6,-2,13,-11,-9,10,21,-7,-15,-15,-11,57,-14,-62,19,-24,-14,41,57,53,6,-41,-3,36,-21,-14,0,-20,-45,-8,-39,-66,-22,-16,11,9,-9,-8,38,12,11,17,-13,-26,9,2,11,-1,-16,7,6,-65,-20,-3,1,0,-4,-24,8,-2,6,33,24,75,38,-20,65,82,-2,11,-29,5,47,-55,-15,-9,-13,8,-15,58,-5,13,8,-8,43,-9,-1,-13,-18,31,18,14,29,-16,29,55,-52,-16,32,-26,-20,-12,-21,-34,22,-19,-6,-5,-1,2,40,-20,-24,2,-1,-3,12,-5,3,-2,-2,-1,12,-5,17,},

                    {10,25,15,1,4,7,12,-31,11,-15,1,5,27,-15,-34,-29,0,-24,-18,-5,-8,39,-39,-29,19,10,-17,-29,-14,-21,-1,1,6,12,4,-4,-3,13,-19,8,-12,34,1,43,36,24,-34,8,14,31,15,-24,-27,-9,21,28,16,-60,-11,-8,-20,4,-21,4,-4,-7,-14,2,-16,-15,-8,6,-4,30,5,16,-1,9,22,-15,27,-36,-14,-10,-2,-1,-52,-11,-30,-45,-2,-23,-23,-15,22,1,-9,-76,-64,-31,-12,18,-2,-38,-55,3,-1,-30,6,26,23,-1,-1,-14,0,-13,-31,10,-3,18,14,-30,-24,32,10,21,-10,8,8,4,-35,-21,-35,-16,10,-8,-4,-21,7,15,14,18,-19,15,-5,37,4,-3,-32,29,5,-4,42,16,-33,-36,13,30,37,6,-18,7,9,28,0,-29,-18,-12,-7,-8,-31,17,-1,1,-17,-9,8,12,7,35,5,5,20,-2,19,-1,6,-14,-20,-29,2,4,-13,-8,-24,-33,-62,-14,-11,-54,-59,-6,-44,-34,14,-33,-83,-49,-10,2,-1,-23,-50,-1,17,22,2,15,-32,2,11,2,13,-9,7,-17,-6,14,-3,12,26,-46,12,-9,-10,11,35,-46,12,5,-12,22,37,-10,-8,-21,11,27,-44,-18,-31,-43,23,1,-2,-17,-1,18,9,5,-39,29,24,2,22,-10,-39,30,28,52,11,20,44,-35,54,24,17,7,25,-8,11,-6,10,-10,28,55,-66,-39,-19,-15,50,13,17,14,-28,-20,-22,-15,4,-3,6,-16,15,-5,-1,21,19,7,-23,-4,17,20,-20,-23,-23,53,1,-16,6,-42,-12,5,-10,0,13,19,33,10,14,4,2,-18,8,9,36,16,-25,-25,-32,37,16,13,6,-16,-38,9,-57,-47,12,-17,34,-7,-21,-16,0,-33,-4,-27,-18,-14,12,-5,27,13,-50,6,1,-21,39,5,-21,4,10,23,19,-29,-34,-27,-10,17,-68,-5,-23,-18,18,-18,-87,6,-2,-13,32,-15,-84,-17,3,-10,7,13,-13,36,3,17,-11,-25,-35,16,18,8,-5,-43,-49,26,36,16,-15,3,-26,-28,5,4,-8,-14,2,9,-20,-10,12,-4,0,26,2,-73,8,-7,-2,-10,6,20,37,19,-25,-2,-3,-7,21,-8,-47,-8,-18,-53,29,10,-19,2,-35,-28,31,23,-14,-48,-4,-7,-8,-25,-27,3,3,25,9,48,-3,9,-25,4,32,-3,37,-24,-6,-3,15,26,16,-66,-18,4,11,17,-7,-11,-26,-1,4,-24,-30,-8,-7,25,10,-23,-12,-22,-37,7,15,14,8,-11,-19,4,-14,8,7,23,-1,-29,5,31,18,33,-51,8,2,18,7,10,-46,-17,-20,-22,-59,11,-17,-27,-1,5,-6,-11,43,-24,25,-12,-7,-23,-4,-19,7,-43,-18,4,21,24,-33,-42,10,26,1,6,53,15,-38,-14,-20,2,15,4,21,5,37,-20,-5,-26,19,17,-11,16,16,12,25,2,6,-24,12,-29,7,28,23,40,-45,-31,0,3,-9,18,22,-32,-62,-1,-8,9,9,13,-2,4,16,3,-11,-14,8,23,22,16,15,8,13,10,-3,7,2,-6,-15,-48,-32,-20,-7,-30,-25,1,29,35,-17,-127,-34,14,45,-15,17,-68,-82,-7,-5,-51,28,-5,-32,15,23,26,26,8,14,-12,-20,27,22,23,-6,10,-15,-1,30,16,-11,-3,-44,5,18,-1,2,32,-15,6,11,-11,1,14,9,6,-9,-37,5,-67,-11,18,41,-26,-23,-22,22,-15,16,16,-24,-3,83,-17,3,20,-35,11,-10,8,45,40,60,35,20,12,21,9,69,-8,9,-40,6,-50,42,-46,-52,-19,7,22,-33,23,12,-26,-21,-22,29,25,26,14,-11,-44,10,26,23,9,-10,-81,-56,18,22,-7,21,-10,-20,21,4,-15,19,6,17,12,-14,-1,-9,10,3,35,-3,28,16,-10,5,10,12,11,-15,-34,-13,-17,-57,-31,-3,17,-55,-26,-23,-23,-5,22,-59,-29,-2,20,0,-2,-18,17,1,26,9,-11,29,0,-51,14,15,35,32,15,-56,1,-5,29,30,3,-8,10,-9,24,10,-8,-2,8,-7,23,-26,37,7,-11,-1,-6,-28,11,-11,-24,24,48,10,18,13,-5,-7,-3,41,-12,16,4,33,30,18,-42,-7,-24,44,-12,-47,22,-48,2,-14,-67,-32,1,26,33,-3,-23,-40,-23,35,4,7,35,14,12,8,-8,-1,-23,-4,-8,20,11,-9,-18,-14,20,11,44,-31,-88,-74,5,-1,-7,23,-30,-57,-8,12,-4,6,-13,-6,18,21,16,-5,4,46,-3,-14,0,13,0,19,-10,-17,5,6,7,-19,-37,-11,-29,21,20,-102,23,14,18,5,-17,-37,-39,-1,10,7,23,-25,-59,20,28,-1,13,55,21,-6,7,-2,9,2,25,6,3,-5,-6,-1,16,-59,-7,2,15,-25,-33,-11,-35,-8,-31,-15,-2,1,-15,13,12,-19,-23,19,20,-9,31,-1,6,3,1,11,-24,-14,-31,-32,-39,-20,-24,3,0,-13,11,23,-5,-26,-21,11,-27,-14,-20,-4,-19,-15,2,-6,-45,-10,28,58,-3,-1,22,8,20,-2,45,15,-9,-16,12,17,33,4,-18,5,-18,32,11,-11,21,57,4,-4,-9,-8,11,2,52,-19,0,-7,-8,25,26,-57,-24,-12,12,29,14,11,22,-10,-21,-13,9,-10,-22,7,-26,-5,9,-22,40,-4,-2,17,3,-53,6,-2,-12,-22,21,7,-13,25,16,22,24,-36,-10,9,-9,15,-29,3,46,-3,22,-3,25,21,2,24,-32,-11,-17,-70,-23,-6,-28,-21,-43,-21,-13,-23,7,-65,-37,18,16,16,-20,-58,-1,12,8,-2,-11,-19,-19,0,-7,16,8,-27,-33,70,19,27,14,-17,-35,-32,8,23,12,53,25,23,20,0,-24,40,-8,13,0,3,-37,19,-55,-70,-49,},

                    {4,33,-7,-10,-5,-5,4,-37,-13,-26,-9,12,-1,2,-2,-27,4,-23,-13,7,-13,-13,-43,-22,3,-10,1,6,1,10,-2,-17,-16,4,-40,4,-3,5,-7,-12,-13,-27,-18,-33,19,15,2,-6,14,-17,-41,-15,-30,-17,10,-26,-28,-8,-23,-9,-4,-24,5,-6,-31,1,1,0,-2,3,8,-15,9,-14,2,-27,-26,-14,0,-21,-12,20,9,11,6,-26,-3,-35,-17,-21,-5,-38,-21,-30,-10,5,-6,2,-5,22,3,-7,0,9,-6,10,-18,-15,28,18,4,-3,-15,-14,-20,17,21,-21,-15,1,-11,-1,47,32,-4,1,-15,12,13,9,0,5,-10,31,19,11,49,-8,3,35,-23,-52,-2,-6,-3,2,33,16,-4,-46,-3,-7,56,23,-19,-23,5,-15,-33,-6,-58,-22,-8,-8,-19,-13,-18,-2,0,-14,8,-12,-31,8,-5,-14,-3,7,-42,-30,11,33,18,-13,17,1,-7,-33,-29,-26,4,-7,-30,-31,-6,30,13,1,-6,6,-23,-6,-7,-11,-24,-32,-29,3,-2,26,7,9,13,-19,3,20,28,-14,56,-2,23,-1,-33,-45,29,15,-33,2,-10,-22,-4,21,-22,-6,3,6,6,4,-11,-13,7,32,17,7,5,-22,-16,19,17,16,-1,-23,21,40,22,19,-14,10,-12,22,47,3,17,4,-25,13,47,8,-11,-3,-21,-6,31,39,-19,-10,-22,28,12,55,37,-14,2,31,-1,18,42,10,13,-10,20,23,17,4,-26,5,-25,-12,-7,-8,-11,-6,-5,14,3,6,-9,-17,-11,-11,-5,-20,7,39,41,-12,-30,7,-11,6,-10,3,-16,-45,7,-33,-19,-18,-6,-31,13,-29,-14,1,37,-21,-24,-8,41,1,3,-38,-22,-48,-20,8,9,-18,-10,19,4,26,8,-14,-1,33,-4,-5,14,-18,-5,-2,3,1,-2,0,-22,-37,-12,-14,-16,-13,-17,-27,-13,-15,-19,2,-15,-9,-2,-7,5,22,-50,-1,-35,13,-25,-19,-3,13,-29,34,4,-7,39,6,10,12,10,4,-35,11,-7,0,-8,-3,-9,-28,8,11,1,15,0,33,17,45,-5,-19,-1,17,45,40,36,18,-19,14,17,17,25,27,15,-8,-13,-24,-13,-4,18,-31,-35,-28,-3,3,-25,-29,3,21,19,5,-6,-10,-29,-38,-50,-8,-5,7,-3,-4,-3,5,13,8,13,10,14,-10,-2,-2,-13,-3,-28,-14,-7,-22,23,21,-15,-1,-8,-2,-13,-13,-24,-15,-2,-21,-5,-24,-11,-11,2,7,6,4,-18,-15,4,3,-11,-2,-31,11,-16,8,52,-5,17,6,-27,3,13,31,5,-33,-26,-12,-17,-2,-49,-27,-7,-12,-30,-19,0,18,-8,-4,41,4,-1,15,-7,14,2,26,-40,-13,33,-3,69,-37,-17,-12,-1,23,17,33,-10,11,-39,29,49,15,-12,16,-25,-24,7,-15,10,6,6,33,10,16,-3,24,3,13,1,6,9,4,12,9,5,-26,28,11,7,18,-21,-14,2,-16,-29,-3,34,6,28,2,-3,-25,3,8,1,-3,-17,15,-4,31,18,7,12,16,16,3,21,-5,24,-7,11,-12,-8,0,-19,-18,-8,-19,-17,-1,15,-28,-22,-2,-14,-41,-27,22,36,23,-34,-8,-17,-24,-28,17,-23,-33,-23,26,3,4,-16,-9,5,24,5,0,15,1,14,7,17,-6,-11,-4,-13,-10,0,-19,-19,-3,-39,-61,5,10,-3,-34,-17,3,1,-21,8,-8,-16,20,24,-24,7,16,28,17,20,-10,-10,10,-3,23,57,4,0,16,-46,-28,21,-36,6,-5,-5,-26,22,13,-8,20,-14,13,6,21,-29,-6,6,10,4,1,-1,-33,-12,-12,2,16,33,8,13,7,-13,13,7,8,-18,-6,27,24,7,-4,-18,-17,-6,6,-30,14,-16,-6,-17,5,-19,-7,2,21,8,3,34,20,-8,9,-15,-45,-9,8,15,-39,-21,16,17,0,10,-16,12,14,17,5,3,-6,-19,-45,-27,-29,-8,-17,-28,-35,-2,-12,11,-1,-3,-13,-16,-7,-9,8,-17,-3,-1,-5,-13,-11,14,23,-1,1,10,-3,-8,-7,-27,-17,-10,-3,-13,-13,3,-16,-12,6,-20,-17,-10,-25,-7,0,-7,-12,-24,-8,-4,-1,6,14,-14,-5,-14,-33,26,13,-21,1,1,-3,-21,-22,3,-14,-4,-10,0,18,13,-7,2,-5,-23,-21,6,-21,-1,-2,35,-32,-3,5,22,4,32,-40,-22,-1,-1,-3,-5,-29,-22,-8,6,-30,24,20,13,-14,-28,-17,-11,-29,15,17,-13,-26,-10,-7,5,-6,-4,10,12,-10,20,10,10,-6,14,4,18,-23,0,-15,5,-13,-7,-1,-6,0,-19,-45,4,-11,4,-46,-23,-26,-20,-9,-8,-15,-29,0,-5,17,3,3,-21,12,15,-1,-11,-14,17,-19,12,-14,5,7,1,47,-9,-19,1,-15,3,40,-13,-20,-8,10,8,-15,-30,9,-6,14,-19,10,-8,9,-12,3,-8,-6,-6,9,14,-2,-9,-4,-29,-25,-21,-40,-14,-14,-8,15,-24,11,8,-12,-31,-19,-51,-12,-37,-35,-32,4,8,26,-7,2,-7,-19,-17,18,2,3,-15,-14,-7,29,39,2,0,9,-11,-10,38,4,-22,-27,4,-28,7,26,-17,-15,15,41,-12,31,22,-1,-4,7,56,16,26,13,-5,-8,31,18,-10,-9,44,27,15,36,-21,14,-36,-3,22,-1,2,7,-6,-14,23,47,-7,-2,-13,21,-11,-45,13,4,-16,27,22,-3,-8,6,10,25,-23,-32,-39,-8,-3,11,40,-18,-8,2,-28,-11,6,-6,32,2,15,-48,-16,32,-16,-8,-11,-21,-9,-43,-30,-15,7,14,-53,-20,-26,-29,-5,-16,7,2,-7,21,-3,21,4,11,32,6,-10,-21,58,7,-5,6,-5,-11,28,-37,14,-14,-13,4,12,-1,-14,-9,-9,21,2,4,-8,11,-4,-4,-2,-6,-6,-15,},

                    {16,-16,14,8,-6,11,46,20,-11,-1,16,14,8,18,8,18,25,-4,20,-33,-43,11,15,23,10,-6,-16,-3,23,2,5,29,44,13,-14,-32,2,-30,-33,-24,-28,-9,-6,-31,-7,19,26,6,-2,13,48,29,47,-7,6,34,40,-56,6,27,36,24,-27,11,-1,10,0,1,21,35,5,-28,16,23,-30,-10,4,11,44,11,-7,9,24,21,6,47,-8,-17,1,-8,25,-17,-50,-1,36,20,-40,-35,15,21,-11,-3,26,32,22,-7,-4,-14,-11,-5,24,25,11,2,39,22,-15,-11,25,-7,4,-19,-3,18,14,-6,-24,-15,39,2,-28,-17,21,-3,-3,6,-17,-22,3,-8,-29,0,13,-9,2,-35,-31,-36,-19,-5,14,20,-21,46,49,7,22,8,33,-15,32,29,13,51,33,-48,9,8,17,-24,-30,-9,6,10,-11,8,11,39,-1,13,-13,-5,-9,-10,-4,-51,27,59,40,-3,-38,-13,34,74,24,-3,-31,-33,15,-1,-23,-16,14,5,-18,45,0,-4,10,41,-16,-16,-9,-7,6,-29,-32,16,-12,-19,-19,43,-20,-4,4,14,23,56,-38,-25,-1,-10,35,15,9,-1,17,-25,1,42,39,-15,-2,14,20,-14,-1,6,3,25,8,-26,-9,-17,-5,-4,-35,8,39,21,3,7,19,15,4,3,-10,51,47,28,-1,17,-8,29,21,20,20,-6,-15,23,-23,-21,34,14,10,-10,-9,-37,16,39,29,-23,25,4,7,-17,11,10,-18,17,60,32,-2,-22,-25,2,-9,23,-11,-28,-13,8,-20,-13,-16,35,34,-36,-11,-41,0,13,-7,0,19,-2,13,11,-23,-16,2,26,4,-22,-20,21,-3,-16,-4,64,2,6,9,-1,39,-5,-8,-7,-14,-6,9,4,28,10,1,-8,4,22,-24,-51,-16,-15,-8,3,-9,23,-34,-9,-1,-8,19,24,-6,7,18,38,5,50,19,22,5,-29,14,48,-36,-2,14,8,19,12,-30,-23,36,20,-29,-3,18,14,36,7,4,20,24,28,-3,-9,2,7,49,38,-30,-16,0,-20,-8,-20,-5,-11,-12,-5,-27,-21,9,24,-4,-30,26,-10,-6,-2,2,-45,12,30,-7,16,-23,-25,5,8,6,4,-5,-25,42,48,-6,-21,-12,-45,21,-17,-18,-28,17,27,-26,-29,-5,-8,31,4,12,1,23,-7,-3,0,-27,-4,-37,-9,-3,8,0,6,1,32,6,62,-34,-7,14,-3,-4,63,25,15,-22,-33,36,44,20,-15,-22,27,27,14,13,4,25,3,2,-18,11,20,6,-37,-42,4,-6,53,-31,37,27,48,48,-18,-14,39,45,45,-24,12,2,20,0,14,10,5,9,-41,-8,17,4,21,-13,1,27,12,-25,38,5,-5,14,-39,-5,-7,-14,-20,3,5,3,-16,8,19,-8,-41,-11,12,34,16,44,42,5,-1,-4,8,24,21,-6,-4,-1,17,16,-34,13,-6,27,23,29,-41,17,5,8,-3,-20,9,30,-5,-26,-5,-20,-57,16,-30,0,16,3,5,-3,15,28,35,24,11,-37,-7,-25,0,-16,-11,3,14,24,-1,19,29,45,36,22,14,-8,-39,17,-2,-4,0,-101,-19,-3,-14,11,14,-4,-38,-34,-9,7,10,-1,-15,-8,-4,-15,-37,-5,-10,0,-56,-20,-37,-25,-30,-17,-30,-15,44,54,-12,6,-25,26,29,32,0,2,2,24,14,24,25,1,-11,-6,34,15,5,21,35,-8,-4,9,-22,-26,-24,-24,-37,2,-25,23,-5,-6,8,66,-10,17,-13,-28,23,-2,6,14,-7,-2,22,8,14,11,-2,26,16,-20,-28,21,-20,21,22,21,12,19,15,29,29,-29,-29,18,34,-19,-38,-39,-25,14,-2,8,-19,4,-21,8,-24,25,42,48,-2,6,-11,13,25,49,16,-20,-17,5,-25,-5,-10,1,13,-37,-15,-33,-27,8,11,7,-14,-33,-1,22,14,32,5,-12,-7,-16,11,-26,-38,36,23,1,-9,-22,-11,47,35,-5,5,-10,15,0,-11,0,-2,-51,-33,-2,43,-12,-6,2,26,16,24,-9,29,40,15,1,5,1,48,7,-41,-6,57,10,13,-23,-2,-8,0,-1,-1,20,-25,3,-11,-55,-11,-30,-16,15,61,2,11,-11,-5,32,63,8,15,11,-28,-17,44,29,8,-22,-35,24,-8,-14,-9,-52,11,42,7,23,-2,59,5,33,-6,-2,6,-39,35,44,-14,15,26,28,-13,-50,-16,31,18,-16,-5,-24,-16,12,-10,-6,9,-14,5,-25,24,25,40,33,21,-29,-5,-24,-19,-1,-33,-4,-5,-18,-41,-7,15,3,8,-14,27,11,37,13,50,25,38,-21,10,7,5,-40,-36,24,22,-3,-18,-11,13,-3,6,9,6,45,-2,16,-39,3,-4,6,4,-13,11,-7,-28,-42,-32,33,23,5,-7,19,5,0,21,1,21,20,-24,5,11,13,2,-60,-6,33,11,6,-4,-6,26,3,8,39,14,2,-16,-1,18,25,2,-10,-7,-16,-23,54,55,23,-13,-39,3,-31,21,-27,-2,6,7,-4,-22,-41,13,55,29,-6,-20,-29,19,-6,-35,1,3,-19,-9,10,40,12,38,34,49,27,24,41,-34,-23,-15,18,30,-22,0,1,-6,-3,7,-7,11,13,-23,-5,-41,13,37,7,16,-1,-8,13,3,-1,-20,18,41,39,11,-28,29,40,-19,12,-41,-41,-7,-2,51,-16,14,30,15,2,-37,1,18,2,-21,5,-25,-5,-2,8,11,22,-22,13,16,-35,-20,-37,-46,7,-2,-14,-31,-46,-21,-8,66,42,-1,-38,-21,-19,30,0,-12,19,11,-3,-12,6,2,4,48,4,-2,13,27,23,-19,-13,-21,-5,13,-35,10,9,-1,-15,13,-26,11,-10,-10,15,4,0,0,6,-12,-5,11,13,36,22,-18,-8,14,-32,-35,14,33,-4,12,25,-29,},

                    {17,11,19,25,-23,0,23,44,9,16,16,7,-26,-30,16,-21,11,-2,-26,26,8,-20,-10,-6,-22,15,2,-9,-16,-7,13,2,14,21,3,-9,20,1,63,66,47,-1,-16,15,36,7,-5,5,52,-7,-4,8,-1,-53,-28,-75,-10,-16,-2,-14,-24,-48,24,2,17,1,-57,-48,-3,-2,-4,9,6,-10,-11,-4,-10,27,-6,19,-6,-17,3,-12,-22,-40,43,22,-12,20,-26,-16,-9,-19,-7,6,8,19,22,-10,21,28,3,4,3,-20,2,20,50,9,12,-5,7,-12,17,22,-9,4,-30,10,-11,15,31,44,12,12,5,9,40,-7,28,0,-12,14,-6,-27,-6,4,13,-2,21,16,15,-8,4,-46,31,48,11,17,-33,39,56,17,9,19,12,8,-5,-16,4,-41,-16,-38,-45,26,15,-7,-8,-58,10,-7,15,-6,-19,-14,47,11,9,-23,8,33,-1,-21,14,-2,2,-17,-7,-1,11,33,4,-16,-33,-26,39,50,-13,20,-2,27,-18,-55,-10,11,7,7,0,5,36,20,44,14,11,7,33,40,41,23,44,12,62,33,21,31,-12,-35,44,-4,-20,-6,30,-22,-17,-24,-28,18,36,-15,5,-21,-27,9,12,30,6,5,7,15,-25,8,57,22,-23,-20,38,13,15,22,-1,-10,-29,-12,1,43,46,0,-1,-4,-2,14,26,42,8,9,4,-12,-28,13,-6,-3,-1,6,1,-23,-45,5,2,12,49,1,-12,7,58,-19,-12,-5,11,38,-31,-82,-42,17,6,9,0,-16,-15,9,20,10,23,27,-3,-9,-13,-5,-8,25,22,13,-13,-21,32,-43,-59,-8,3,43,27,-6,-5,10,10,43,13,16,11,-57,1,-7,-16,16,8,-29,-33,-13,21,0,3,-1,-3,4,-1,16,-2,-18,11,19,12,46,28,61,42,27,61,23,-42,7,43,19,2,-38,10,26,-1,-13,-29,-2,14,-38,-34,-28,-50,-6,2,-21,1,10,37,33,28,16,36,56,30,11,-15,-17,3,-13,13,12,-24,-26,-8,21,-43,-51,-26,-32,6,14,10,10,-23,-17,4,23,56,41,-1,-33,-36,0,26,22,18,-7,-21,-4,33,-40,5,1,23,-7,12,12,-19,2,0,38,-26,-18,-6,33,-16,26,-8,-23,10,10,-16,-33,-36,26,-17,-1,13,17,-11,21,26,24,-11,-11,3,-5,17,27,19,-19,40,-6,-28,21,55,21,11,-12,19,23,37,-23,-31,-35,6,5,-13,0,-24,-14,-21,-5,-8,-6,0,-23,8,16,20,13,23,-5,-1,12,6,33,-20,-31,7,10,-4,-3,-34,-5,13,-13,11,-44,-7,12,-3,-23,15,-14,13,-20,2,3,-3,-6,-10,-46,20,28,21,12,11,-5,-10,-14,-5,1,59,11,-18,-3,-9,7,-6,-15,-9,-2,50,24,-10,33,39,41,-34,-42,16,-18,-74,-22,-22,12,-42,21,24,-10,13,5,9,-42,-37,-43,-28,-1,46,-13,-23,-43,-19,-10,-25,11,-22,-33,8,59,-18,39,44,12,-16,-19,21,14,-17,-21,-18,-11,13,35,15,-5,10,11,20,4,-11,-3,25,8,14,-16,-17,13,-7,13,-10,-11,-34,14,18,13,3,8,-13,-11,-12,33,15,51,42,24,4,-27,8,34,25,22,6,19,43,14,27,31,70,24,25,-18,56,46,38,14,-21,-2,21,11,-38,-18,-43,-4,7,5,-12,-27,-33,-17,18,1,5,2,-26,-6,-20,-4,-16,-1,29,25,18,0,19,-17,25,22,33,-1,-29,34,-11,15,28,-16,-46,-10,-25,3,46,11,31,30,-25,-16,-48,5,-27,30,-18,23,-37,14,-28,28,4,23,8,-34,12,25,8,-37,-55,16,32,10,10,29,-35,7,29,46,25,24,39,17,-9,-10,6,-6,-31,-20,-22,-13,18,23,-2,-2,13,13,16,21,7,33,42,12,20,23,-8,-13,0,47,-11,-4,-39,-21,10,56,-3,-16,53,38,-27,-53,-2,10,-4,-2,12,10,-28,-9,8,10,-1,9,2,8,-11,26,-2,11,11,23,-1,-38,22,12,23,-13,2,6,30,-17,11,-26,-5,-18,1,-30,16,-6,5,-1,-5,4,7,-15,8,33,-16,6,9,-1,24,42,16,16,15,3,-35,24,35,13,-35,-15,20,-2,-3,24,-54,-11,6,-12,-6,-9,-26,-15,-9,-10,-3,10,-19,15,0,28,3,13,22,12,9,-21,-9,30,-10,3,-7,4,3,0,6,-14,-25,-33,34,38,-13,-1,11,36,2,-24,-15,-4,10,-5,-17,-3,15,35,14,-4,-5,-2,3,2,11,3,0,19,14,-2,-26,8,18,22,-31,-43,-4,2,20,9,-13,0,-19,-32,-16,-11,-13,23,-6,20,-2,27,-13,-5,18,17,13,21,11,-7,-21,-33,33,21,7,23,19,50,1,-18,-1,17,0,-1,22,10,-4,-25,-36,-12,-14,-15,21,-25,11,22,-13,-8,-3,-9,41,5,10,13,34,7,2,-4,-2,3,-13,-6,-13,-13,15,30,-28,-43,-37,19,29,-13,-25,-32,-33,-25,-8,4,22,47,52,15,-12,-14,-9,39,37,-14,11,-28,21,29,13,-7,13,-12,-2,14,-18,-39,-36,-45,-34,-5,32,3,-15,-10,24,7,23,9,46,18,23,-6,-5,10,-2,-6,19,-1,-7,26,3,3,44,5,25,-21,31,-10,14,3,-3,-15,-21,46,-8,53,34,50,47,-13,11,-10,13,-13,21,6,24,20,6,-21,-20,-19,14,22,-1,-3,-18,-8,9,-7,2,37,57,27,18,-36,27,29,74,69,-42,8,-51,-8,0,26,32,-66,-19,20,-33,-52,10,28,24,-25,7,-5,-48,-34,8,-6,10,14,52,-7,-6,-12,55,25,42,9,25,-3,0,1,-5,1,9,4,-24,20,-8,-12,42,21,-3,-7,-15,-1,-11,33,-6,24,1,42,-23,10,-22,8,},

                    {-11,-10,13,12,-14,8,-3,31,-4,-24,-16,24,22,-13,10,-29,13,22,29,37,11,49,-7,0,24,9,-55,-12,9,7,-7,-44,23,7,-7,25,-42,-33,35,30,22,24,-36,42,47,27,8,5,34,10,10,-2,3,11,27,-11,9,4,-14,-15,39,5,34,-4,-23,7,-14,-23,-8,12,16,4,-4,-9,-22,18,11,38,-16,-1,-31,-37,25,34,32,-12,37,-27,-11,33,52,51,30,1,-1,40,66,-14,-18,-12,-23,-1,-8,-25,8,-11,51,-20,-22,22,-9,-11,15,-7,13,18,-26,-6,-25,-19,26,15,-8,-39,-16,20,20,40,14,9,16,31,11,1,5,17,-2,0,5,20,-9,-21,12,11,2,-16,36,25,22,-20,-3,53,56,22,15,-11,14,25,-5,-13,19,-1,-17,-1,13,34,-5,-3,37,28,29,-11,9,2,22,20,14,11,2,2,20,28,28,37,34,-10,-4,-43,3,-32,-6,55,12,-55,-28,-17,13,35,-28,5,-1,14,11,36,33,7,4,5,5,41,17,-7,0,6,10,7,4,48,50,72,74,57,10,6,31,53,2,40,16,8,4,-1,13,30,-33,-14,28,16,-26,18,-7,15,18,-18,3,31,0,-22,21,5,-4,-2,-2,45,-22,7,31,-3,10,49,54,-26,-16,7,29,23,15,-8,-21,44,30,16,29,-5,3,7,11,-11,-7,-5,-34,19,-8,25,-23,18,-1,-6,-7,-12,0,-19,-36,-26,-2,-59,-8,-29,-32,-17,-20,-58,-36,-31,9,19,0,-10,31,6,5,7,31,-9,-2,11,42,63,-36,9,4,-17,39,30,-31,2,-38,45,-32,21,8,-23,-19,2,12,77,-1,-17,-29,-4,29,44,6,9,-14,29,1,27,-6,1,-34,22,2,-37,-25,16,6,30,19,22,-38,28,13,53,49,56,2,23,-6,7,41,57,15,2,4,-2,7,41,-37,24,32,-11,-22,13,19,79,18,0,-24,-29,20,-20,-8,-10,12,51,1,26,-28,-15,16,18,5,52,-34,-34,-36,9,-18,16,-7,-36,-4,8,3,1,37,35,2,31,-13,-27,-46,4,63,33,-27,2,-12,-19,-1,9,9,-24,-9,-12,13,28,27,19,-31,-35,-19,36,1,-16,19,-12,-27,55,12,44,22,23,9,3,13,3,10,-11,5,-7,16,-18,11,7,-24,23,-15,-3,17,16,-1,24,21,-6,-16,11,34,48,21,4,-2,-10,12,63,4,5,28,-5,-22,-4,22,17,25,-15,-16,-1,0,-27,16,-6,-16,3,-14,-15,-34,-56,-44,-24,-23,-31,24,33,13,2,-35,-7,0,-15,-16,10,1,7,-22,45,-11,5,-4,-24,-16,-5,-18,20,-25,8,30,-11,3,-7,-13,-8,-21,1,-20,-8,29,-23,-6,-33,8,23,2,-31,-50,-2,-3,28,18,3,-4,20,10,29,7,5,-7,12,-22,6,-29,-21,-3,1,12,11,-13,21,-9,-16,-3,-4,8,-20,-29,-56,-29,5,-7,-6,-63,-53,13,60,12,20,4,-9,31,77,28,7,-3,34,9,15,-15,-4,0,13,16,32,23,18,-12,-35,-14,37,18,-17,-5,12,18,33,-13,-46,-48,21,-13,19,-2,-17,-62,-29,-20,35,8,-11,-27,-20,-10,16,14,-10,-25,5,33,19,-6,-6,18,29,64,-28,7,2,65,83,53,8,30,15,36,27,24,-20,22,6,28,-11,-18,-60,13,27,30,-3,-2,-8,-24,-13,-15,7,-8,-3,1,-9,3,3,23,21,10,48,40,38,18,-1,11,13,25,1,-9,-31,3,-15,11,-12,3,6,-20,-6,3,3,4,15,33,0,-12,4,-6,30,-2,5,15,-16,-20,-25,-15,-24,-40,-17,30,-11,-29,-13,-43,54,6,33,35,23,-14,-16,45,32,28,8,27,-13,-37,17,13,19,7,-11,40,9,-12,-3,-10,-7,-2,27,-18,-41,-8,-21,4,34,7,4,-25,-12,8,37,-13,8,16,-3,-2,35,44,19,12,-8,-7,15,10,-29,4,11,4,16,4,30,14,2,14,1,-12,-2,9,-28,-19,26,7,17,8,1,-9,0,-20,10,25,-9,-34,1,-20,5,38,-6,-16,-3,1,8,7,19,7,-1,-15,-8,36,5,12,27,26,5,-32,40,75,72,15,4,5,4,46,69,6,31,55,-7,48,45,48,31,41,-3,-27,-18,29,-8,10,-8,6,-9,5,23,-5,13,34,47,-11,-5,-21,-22,-2,22,-4,8,-44,-31,-12,29,22,6,-23,-28,25,89,38,30,-5,25,19,31,14,-2,4,-23,44,27,-6,-39,26,10,0,32,18,-2,-14,-25,7,30,-3,-1,-12,-20,10,5,17,67,46,-8,-24,23,27,45,16,-3,-21,19,-13,-23,4,13,-17,6,6,-3,-43,1,24,-28,4,29,7,47,14,-10,-5,24,9,-15,23,11,-16,-8,24,69,36,-16,12,47,38,-6,-22,15,7,2,-35,17,-9,4,-30,-21,-20,-18,-20,11,8,-25,-41,-47,18,6,7,-1,-14,11,22,13,28,64,15,8,25,11,23,-15,-19,-26,6,20,-21,-25,-6,-47,-12,-10,3,20,-6,-23,40,-3,27,32,25,12,-10,18,-18,9,28,27,-4,3,6,-26,13,36,17,22,19,-16,-13,-5,-5,3,-12,14,38,-12,-17,3,-27,29,-26,-21,15,-42,0,-29,-56,-29,-16,-16,30,33,-1,-42,6,-8,8,-6,22,9,39,53,5,10,-8,3,-6,-3,-46,40,22,-3,-14,1,14,7,-13,31,31,31,5,-24,7,2,29,35,-11,-3,-50,7,4,11,1,-50,-31,-15,-5,-14,-13,7,-1,-14,-13,-18,-9,7,15,2,24,8,26,-12,4,8,12,15,27,-21,5,-5,6,9,32,-10,-11,35,21,23,-5,4,18,13,9,0,18,16,11,-23,-1,9,9,54,-15,-5,-7,24,},

                    {28,0,10,14,-11,4,18,5,8,-7,-26,29,-5,-3,-25,-5,-6,12,-3,-67,18,-18,3,28,-5,-16,8,16,52,29,19,0,32,29,6,13,-3,30,-29,-4,40,-1,14,-1,-14,5,6,29,-18,26,46,29,19,-14,-4,-14,10,8,6,-26,3,-24,14,-6,-30,-16,44,13,6,-43,-40,-25,18,16,-20,32,4,0,10,27,13,4,1,3,-3,-22,5,-17,9,10,-5,-16,-11,-22,-13,3,-1,-9,6,12,-7,9,6,8,-21,-5,-23,4,17,27,13,9,0,6,9,-33,-21,41,-10,9,-22,-38,-49,-37,0,-15,9,-4,-14,19,-31,24,12,-11,4,16,-27,7,7,-1,15,-7,12,-8,12,8,5,24,20,8,10,13,-15,5,9,7,-30,9,-2,12,13,1,19,-37,-8,4,-5,-24,8,-16,26,11,-5,-28,11,13,23,-11,-14,-7,-12,-5,-16,23,-26,-27,74,97,73,35,-8,-51,50,78,50,-14,4,23,-4,-1,10,-29,23,32,-29,-1,-13,-19,14,16,-13,14,8,17,-12,-1,27,21,14,14,9,40,-34,-16,-16,-5,9,63,-21,-8,-9,-20,34,-9,8,-24,16,4,3,-25,-12,-22,-1,0,-10,-37,24,8,28,1,-7,13,-6,4,-14,37,5,-12,-11,-26,-46,11,22,-20,-27,-31,-35,3,-2,-8,-43,-13,-8,31,-25,6,-17,-1,17,-6,-30,17,28,0,23,-23,11,26,70,67,3,-8,29,-22,-12,1,27,12,0,-13,29,8,-56,-1,0,3,29,10,-1,7,-7,10,18,7,49,26,-35,-36,13,35,23,35,36,47,53,8,40,2,-1,-21,25,16,26,-23,11,-29,-10,9,-13,-2,15,19,-24,11,56,33,-13,15,-32,-12,-22,-49,12,7,28,24,4,-21,-18,-5,17,6,-38,38,-22,17,0,2,-8,-6,2,15,38,-3,2,15,19,18,7,-10,0,28,17,28,-15,-5,3,3,-3,2,-13,26,15,-24,-4,-17,42,44,20,5,10,13,-17,-11,18,9,-14,-20,-14,-59,-104,-34,1,-47,4,8,-18,-11,-4,-1,3,18,46,-9,-6,-1,-31,30,-21,40,86,40,34,58,39,18,19,5,5,12,37,2,-30,-23,-13,30,27,-36,-13,10,-7,-16,-6,-47,30,62,-1,-2,-19,1,46,24,31,17,5,1,-10,40,-10,13,-21,20,4,-6,9,17,45,20,25,-4,-15,-34,-20,-13,19,20,-35,-40,-3,7,13,-4,-34,-9,17,30,-25,8,7,22,18,-13,-2,0,4,5,40,6,21,2,0,29,11,26,8,25,2,-30,-69,-20,31,33,4,-55,-56,-6,2,1,25,-22,-11,-2,18,1,24,-5,10,-10,-20,-10,30,56,-15,40,28,-42,-1,-6,18,23,4,5,12,-13,-10,26,-25,2,-35,7,-5,-4,54,12,-24,-6,-29,-53,-12,19,50,23,53,-15,40,50,44,39,35,55,3,-25,13,23,79,14,8,-62,8,-16,-22,6,9,6,-7,-27,-59,-20,21,29,-25,-23,-8,-19,-5,6,2,16,19,24,-3,21,11,-1,-9,-4,-10,-3,24,33,15,14,-7,-1,23,22,63,29,-65,-36,7,46,30,-11,27,30,10,39,55,23,45,52,-43,-45,-29,-11,6,-8,3,-3,-13,-15,16,-11,-16,-31,7,1,10,13,-11,-28,10,44,13,-11,-50,-16,8,45,11,0,-11,21,4,-15,-34,-26,14,9,2,-21,-17,3,-1,-5,-14,33,18,-20,2,-22,-11,46,29,-1,-30,-10,-24,44,1,-3,-58,-25,-14,-4,-45,-14,-9,-7,28,-34,-17,-9,17,-8,19,-19,23,16,3,20,67,35,-4,17,57,54,59,20,-11,-22,24,-17,-15,-17,2,-2,-14,-18,-39,15,23,34,-48,-46,-67,24,20,26,-19,17,15,4,9,9,3,7,-25,-27,-6,-27,23,24,14,33,26,-26,4,36,64,32,-14,-6,-8,-8,-1,-28,15,33,-7,-28,-35,4,4,-14,-6,30,23,2,-10,-17,-2,28,-8,-9,18,23,22,-4,-27,33,31,26,6,-18,-5,14,-8,-27,-18,-54,-23,35,20,-33,8,3,11,19,-7,-30,5,34,-6,25,21,-7,0,-14,-5,22,25,22,-12,5,6,-8,8,4,-14,-35,-7,32,35,9,-55,-51,-11,8,23,16,-38,7,-10,-31,16,-14,49,39,40,-34,12,-20,-7,2,13,21,-12,-42,57,76,53,7,0,-48,26,33,36,4,-28,2,-8,-2,-18,-52,19,32,-31,-14,-31,0,21,-10,-14,11,4,26,4,15,-9,7,-12,10,14,-67,-2,7,15,14,16,32,-1,38,27,21,-6,-8,-31,-51,6,-2,-6,22,-31,-9,16,21,-17,-6,27,44,37,-17,-28,-10,0,46,64,-5,20,-8,8,1,6,13,18,23,30,14,9,8,7,1,15,-20,-13,12,1,-17,-4,-22,-17,14,5,12,15,1,40,14,-18,24,69,8,6,12,-13,-13,-22,-12,21,-12,-11,-20,27,-12,34,-20,-4,30,-46,26,34,22,-4,-11,26,20,38,34,16,24,-23,-1,1,-2,0,56,2,18,-10,13,27,47,28,18,10,65,2,-6,-23,-57,-63,-31,25,-6,8,3,-25,-15,-15,-7,17,4,20,-9,-29,-21,-1,-10,-41,10,-11,-10,29,20,12,-9,21,19,9,-32,-9,37,42,-4,-24,-69,-89,-39,-22,2,-7,-4,-32,9,3,7,-6,-22,5,38,-26,21,-25,12,45,-4,5,-23,20,16,-22,-13,-23,-66,4,15,26,6,8,-4,-23,93,117,16,8,5,10,61,51,26,7,-8,33,-48,4,-7,-15,-8,-13,-7,29,10,-7,-7,8,9,41,42,-21,20,19,-9,-49,35,14,-13,-18,7,-33,37,28,7,-5,9,-5,11,-31,3,-18,4,5,-33,-5,-6,7,28,10,-40,24,44,},

                    {-23,-2,-6,1,-4,-21,-31,10,17,13,-22,-11,-7,-18,-21,-38,-48,-13,5,30,15,0,-13,24,-2,-1,-5,10,29,1,-18,-29,8,3,36,6,15,5,-45,-10,-6,-53,-4,17,-6,-31,-22,-58,14,22,-16,27,-34,-34,-28,-25,-17,48,1,22,-10,1,-13,11,19,10,37,5,26,22,3,17,-4,17,9,19,-6,-22,-34,26,-5,0,-44,-46,-19,-50,-17,3,-79,33,-28,31,-10,-8,-3,-2,-3,9,12,36,13,6,-16,-26,14,18,28,21,-27,-1,-10,-18,11,-10,-11,-36,18,13,-1,8,-10,15,4,-8,-20,-13,11,7,-17,-30,-5,-7,19,4,-4,-3,23,-2,7,27,-6,36,-24,9,13,-1,-44,-3,13,-13,-2,-38,23,-65,3,-20,3,48,4,53,-3,-12,-17,-10,-21,55,2,31,4,10,9,-24,10,14,15,-32,-5,6,18,8,26,10,39,33,40,11,-3,-41,-25,-3,18,9,-11,-34,-8,-12,-36,-25,6,-9,21,7,-10,-7,-2,-31,-44,-23,4,-3,23,-5,30,2,17,18,-9,-56,-9,-16,-9,-27,26,37,-2,8,-21,-21,12,13,12,37,-6,17,-6,-28,-4,8,-7,-4,7,20,54,-12,-33,22,5,-9,42,-9,-8,8,-24,16,21,-20,-9,-3,-10,-49,-12,1,17,52,-7,12,-20,-13,-10,27,-3,-9,15,-46,-2,-10,9,-3,6,-11,23,25,6,16,28,17,-13,7,4,0,-6,17,7,8,2,24,1,-14,-1,4,-19,-25,8,-25,-61,-34,-8,26,23,-24,-15,-12,-57,-31,2,18,-1,16,-12,28,3,31,51,25,-36,45,2,-8,47,1,8,-36,-2,-17,-15,-13,43,4,11,-15,3,-12,-15,-19,5,17,0,57,-24,-30,0,6,17,-1,20,9,27,-8,-26,50,14,-22,20,10,0,-51,27,22,13,9,-56,-76,9,-15,-4,-14,-15,-18,1,-11,17,21,-5,29,-4,-9,-3,14,20,-25,10,-2,-18,-22,-16,12,-14,-36,-8,-10,9,-25,-3,-20,17,14,4,-4,-21,-39,13,14,-10,-6,-17,15,-3,35,-24,-41,-16,5,-8,24,-30,-12,-57,11,7,20,14,19,-6,18,-18,-5,-20,-29,0,-17,4,-25,-28,-17,-23,-39,-28,-7,-59,-42,-12,-14,13,4,-54,4,7,16,-12,-24,42,-3,21,14,17,50,22,29,8,-23,13,2,8,-21,16,39,5,-16,-18,-21,-24,-9,19,-34,-1,16,-16,-2,9,2,-10,-41,14,1,43,-6,-4,-2,-4,7,-3,19,-25,13,-31,-3,-4,33,0,33,7,-33,-25,-68,1,-20,-19,19,10,-7,-28,-23,25,-17,54,30,28,37,10,13,70,21,9,-23,-21,26,19,27,7,-28,-35,2,-20,-41,-31,34,5,-10,36,26,26,-40,17,35,0,-43,-21,-18,-16,2,-8,9,-27,-14,-12,-6,-5,4,-40,-1,34,6,15,1,11,30,4,17,2,0,20,-10,-18,-34,-4,16,56,41,-13,-1,16,4,11,13,1,25,-3,6,-23,-15,-20,-22,-18,-34,-23,-8,10,12,24,24,13,5,5,2,-2,19,11,-8,-9,-39,-15,-21,-30,-21,9,-24,-14,-33,17,22,0,-5,12,-9,31,-14,-11,-41,-10,-8,-22,32,-41,-57,-42,17,39,-10,-7,22,-5,25,-47,-29,27,33,8,-31,-48,-31,40,20,-8,-3,31,-14,16,14,-18,22,36,-11,3,24,14,1,8,0,-13,11,18,-22,6,1,-22,23,-11,-6,-3,-17,10,-24,30,11,-25,-38,10,-12,6,-3,39,2,-5,16,-24,17,-33,-27,20,5,17,11,0,29,50,21,23,3,-26,-20,-11,-4,-44,17,31,-23,-11,-56,-3,46,26,-36,21,21,7,12,-8,4,-3,20,11,-24,-18,-11,-25,-22,-29,-47,-28,10,9,17,2,22,20,-9,-12,-18,43,31,19,36,-28,-14,14,21,19,-47,-13,-4,-23,-18,-31,-34,2,46,39,-12,-53,28,-5,18,-27,-1,9,-1,13,12,46,32,15,28,-18,-12,6,17,3,-9,-12,0,-2,11,-28,3,3,-7,21,-23,-43,-12,-16,-20,48,-31,-13,-9,-10,32,33,-13,19,22,4,-8,-5,0,9,-6,13,18,-6,-2,-31,-17,-14,24,16,54,-48,-31,5,-10,47,24,-42,6,-7,32,18,14,-20,-20,32,26,20,-11,-20,12,-16,-43,-28,15,18,17,22,16,54,0,-12,-8,-3,-36,-12,7,31,21,-15,-14,-11,-3,5,25,6,-6,13,5,-28,3,-7,-25,-33,-28,-9,7,17,-19,9,18,7,3,-2,7,33,42,39,-10,-22,30,13,11,-25,-43,-19,-27,-31,-65,-42,-17,-15,14,-13,-36,-3,-3,23,0,-9,29,22,-22,37,4,-9,-3,-31,44,-5,-10,-26,29,4,56,1,-12,8,-28,-44,4,-14,11,-23,13,-20,-10,-12,29,-11,15,-5,18,6,17,16,12,-31,17,4,-6,-16,4,32,-3,-32,6,-3,-10,-6,-20,-13,19,3,23,-25,-48,-12,-45,-9,-44,-36,16,22,-13,18,-8,3,4,-5,-11,-8,22,15,3,27,27,37,14,32,58,-15,-1,5,11,28,-14,-28,-33,-59,18,14,-1,-33,34,28,3,-8,-26,17,0,4,6,-6,3,-34,-25,26,27,-4,27,-24,5,62,30,-9,7,-30,-22,18,7,24,13,-31,-17,-12,-10,-2,-5,0,28,26,-14,-46,-29,-4,-16,-19,-1,-35,-24,-2,-5,6,29,-1,17,-30,28,-3,26,-1,2,14,-13,38,27,-22,57,12,13,8,35,-45,-49,19,-4,-41,8,2,-49,-13,-62,-23,26,-10,-31,-3,-21,-62,-10,12,16,-46,27,18,-9,1,-4,-19,-31,5,12,-27,1,-15,23,18,29,-1,18,-3,-6,14,1,30,-6,-8,18,-17,7,4,-18,21,21,34,-2,-6,17,36,13,33,-6,-5,15,},

                    {11,-1,-16,-15,11,1,-8,-24,35,-6,-50,-21,38,-2,11,-18,37,-10,3,20,44,42,2,13,67,-12,6,-8,6,29,-18,-25,-14,-54,49,44,-27,42,46,6,19,17,6,14,37,62,-5,-6,22,21,7,24,-1,0,39,44,34,19,1,-23,6,-4,-4,-10,-32,3,64,-14,-37,-15,-13,5,-2,0,6,20,10,-2,-28,-23,11,-2,-16,39,28,30,-19,4,-20,-7,14,18,4,16,0,-12,27,-3,1,-11,-7,21,-13,-31,6,-20,-16,29,-22,-30,22,0,7,-17,-39,3,-43,25,-17,-17,-42,-8,-64,-2,17,-5,16,-12,-43,22,12,27,13,23,15,7,9,40,-2,12,-11,24,-10,22,-6,32,27,35,28,7,25,-12,7,38,-26,6,10,29,23,26,-9,0,0,49,-13,26,11,-20,7,-6,0,-2,-14,-9,-4,2,-20,-17,-35,-7,10,-8,26,9,-7,34,-3,-9,7,11,5,-4,-21,9,23,14,-24,-32,-6,7,-5,-45,-39,-1,-2,5,23,5,8,14,12,7,6,-23,1,37,-26,26,-16,20,-11,-6,-29,-20,-21,-3,-3,-11,-23,-34,-38,-21,-22,-14,28,22,5,-32,-28,4,-10,12,14,5,2,16,23,-26,-20,18,9,13,-2,-22,11,18,-5,7,-37,-19,-46,16,-16,-59,-54,-53,-81,-43,-8,-68,27,-36,-43,-41,-45,23,0,39,18,-5,7,33,-22,-8,-10,49,25,56,1,47,9,2,12,-9,-61,-15,-28,-44,-23,-23,45,13,31,20,31,25,-24,28,7,26,56,29,-6,21,7,31,25,39,14,-20,-44,-6,-1,24,-1,48,41,31,5,-30,-31,12,-6,11,41,10,-16,-14,-24,30,17,-35,-14,-14,-16,3,-16,19,19,-3,36,7,9,39,-33,-27,-15,26,52,37,-3,14,12,15,-22,15,20,16,9,36,-4,29,9,17,20,12,12,-35,-1,27,51,26,22,21,13,-8,-21,0,-1,21,-9,-15,-40,-7,-9,-40,-53,-35,-2,6,9,15,-37,-20,-59,-7,-20,-40,-13,44,23,8,20,-5,-8,-17,-3,44,7,34,-19,-67,-29,-14,6,19,-21,15,-31,-51,45,69,-14,27,35,-12,-1,-4,-33,-23,1,-13,-14,-23,12,2,-20,-23,-1,-28,-6,31,39,2,-5,34,13,41,59,26,-6,21,-10,2,-17,-22,-4,36,9,14,28,0,9,23,13,-1,-3,-1,5,-25,-6,-2,10,22,-11,-41,42,34,34,12,-17,8,30,17,21,3,-19,-21,3,-34,-37,3,-32,-5,6,-9,-14,-29,-40,-2,11,-28,-19,6,-14,-18,6,-35,-4,38,1,34,9,38,17,-2,26,-22,-12,12,24,11,-5,-7,16,7,-43,7,-45,-6,11,45,-34,23,13,26,-40,-12,22,12,13,-28,-26,-60,-16,-39,-26,-43,-4,-24,2,-20,-9,13,-6,23,16,40,35,31,-22,-17,12,-18,24,21,4,64,22,19,16,-6,-52,7,-29,-25,-15,3,-22,-42,-23,-29,-28,-41,-12,-49,-42,-35,-18,14,-3,4,11,2,9,49,-10,-7,-6,13,20,29,-43,-21,-30,-14,-31,-11,-28,6,-11,-33,-37,-32,-27,27,13,5,-6,13,-26,-28,-7,-7,66,-6,-56,-89,-55,-23,25,55,20,18,30,22,77,58,-24,21,3,30,16,16,-30,-13,-26,-15,26,-14,1,3,-56,51,10,3,26,28,-10,26,-1,10,24,50,-13,-56,4,-15,-22,6,0,-49,9,-13,-10,-4,-7,7,-19,14,-19,-12,-25,-7,-17,-38,-25,-29,-54,-34,6,-30,42,21,-5,-36,14,-24,19,35,4,29,25,47,-3,-9,25,23,12,51,7,8,-1,-18,26,-50,-23,26,-19,38,7,19,-34,-7,-16,0,-35,-12,-34,-54,-71,-42,-15,19,15,24,28,10,8,54,-2,-5,2,24,33,44,-25,13,22,27,31,-30,10,-12,11,25,11,-15,-31,5,-7,-16,-38,-29,10,27,0,-7,-7,2,5,28,36,15,-4,-13,35,18,13,7,3,17,-9,-9,26,9,-4,36,12,-12,23,28,-45,-12,1,-28,6,8,4,-23,14,44,32,32,34,24,-9,9,15,41,0,24,-9,-36,-54,-23,-27,-10,9,-3,29,-6,11,26,-35,-22,27,21,6,-24,8,-11,55,26,47,1,31,54,22,-12,-26,-4,26,8,-3,-8,-19,-6,-9,-47,-55,-6,-15,-4,-31,34,-16,1,49,-21,-14,-10,-24,-22,-1,5,-11,-2,1,-23,-34,-35,2,-33,-12,-57,-32,13,26,1,4,-28,-4,49,26,-4,-1,3,25,47,-1,25,30,14,16,11,-34,-6,7,10,13,36,-6,-6,20,-35,-15,-51,-5,47,30,39,14,19,17,-21,20,-7,-20,-33,-9,-5,-10,-42,-27,-28,11,-7,15,24,-28,17,7,22,16,47,15,-13,11,-2,36,12,-26,-4,6,20,-25,32,-12,11,4,-12,-5,-23,3,-23,-13,37,-17,1,13,-25,12,-15,-26,-1,11,11,-50,-40,-11,-8,-29,-16,18,25,34,18,0,24,37,42,3,45,24,16,-8,-47,-39,-16,11,14,2,-37,-31,-48,4,48,-7,2,-14,10,-10,22,-15,-47,-37,-11,11,-13,9,-26,-14,-66,-11,11,1,-24,-8,-9,-42,6,0,-10,-4,2,-22,24,9,-22,-24,23,-24,22,-22,-15,-13,11,-17,9,-42,-8,-50,-30,-64,-39,-11,-19,-20,7,-26,23,24,-2,-4,33,40,17,-9,12,16,14,-18,34,-6,3,-28,33,-13,8,-14,-5,4,38,6,20,-7,15,79,72,-13,-7,15,59,51,27,7,-15,-32,-28,21,-14,10,-3,-29,-3,26,41,-18,-18,19,51,6,-17,-2,11,0,32,26,-4,-19,-16,-17,3,-8,4,10,-10,-22,27,-45,-35,34,-45,38,19,8,9,-13,-3,-3,41,-6,20,10,63,-9,6,-12,44,23,41,},

                    {-4,-16,-28,-27,2,-34,-15,-44,8,15,8,9,-57,-7,4,47,17,12,-5,-33,-38,-73,-17,-7,8,-15,32,11,29,-60,11,25,-10,40,-14,-26,-23,32,64,-1,-26,-17,12,11,38,21,-5,-8,-21,-26,-24,12,3,-14,-65,-22,-36,4,-19,-20,-49,-39,36,40,-35,-6,-16,64,52,-4,-43,-15,8,-6,-35,-21,-32,-22,-27,-20,-2,15,34,-16,-42,-4,27,21,6,-16,-9,-27,-32,-14,-8,7,-9,19,53,9,33,-18,12,64,9,-8,-24,-39,-3,11,32,1,-9,-25,-18,-10,31,17,26,-22,-15,-7,13,34,33,26,-14,-9,20,10,-4,-2,-21,-16,24,28,-16,-25,15,8,2,-21,-5,-9,1,-15,45,20,-68,-22,-5,14,26,4,-41,-40,-3,-45,-7,4,-11,-6,-20,-53,-3,12,-14,-17,6,-12,33,34,-48,-27,-12,-4,40,22,-37,-20,-21,-8,-4,-25,37,8,12,17,-18,2,-1,19,-18,8,22,-2,34,34,-11,49,1,22,7,13,24,-3,-27,8,37,-40,-37,-10,-21,-18,-21,-23,-17,16,60,11,-30,-28,-7,24,31,3,-41,-39,-27,-12,-46,-3,-56,7,15,-26,-35,-11,-57,-6,30,-51,29,20,-68,-23,4,-14,-3,33,-37,7,3,16,46,-28,-13,-7,-24,-2,-1,0,39,-34,-5,-16,-19,23,10,5,-23,-7,-5,-1,17,-23,4,-14,-3,20,-22,-9,19,4,-1,12,16,-4,-9,-46,-21,-38,-46,-8,2,40,-11,-10,-13,1,-71,-32,14,21,46,14,26,20,12,9,6,-45,-10,2,-19,-9,-4,-18,27,0,-15,-8,8,4,10,-14,-9,-26,-22,-8,-7,3,16,11,-20,16,-56,18,1,12,9,6,-19,13,42,-38,-15,-6,-10,-29,24,44,-2,-52,1,7,-2,-9,-16,-23,8,5,25,12,-43,-16,4,2,8,31,-11,-5,-45,28,10,16,1,2,-7,-12,-13,-15,-33,-29,4,-45,45,42,-30,-17,-37,47,26,-14,-30,17,20,21,26,-12,-32,-45,-33,2,39,29,18,-8,-42,1,-8,16,76,41,18,-4,-22,-8,-13,35,53,44,29,37,-20,2,40,40,16,47,47,21,4,-7,-4,-26,-7,-18,28,-19,6,-13,5,3,-74,8,-1,18,-14,37,-37,14,17,-18,-21,-31,-24,-27,-36,-15,-1,-22,4,41,-22,-9,3,-31,-2,14,5,-31,-21,-30,7,1,22,-2,-15,-17,-11,35,-4,-31,-7,12,-36,-27,-53,-26,-3,1,-18,0,24,-28,-61,13,16,-18,11,-6,-45,-11,23,-12,13,-4,4,2,-29,5,20,14,-30,-18,-12,-18,48,49,14,-8,17,-41,-41,-12,-60,-10,-22,38,26,9,-43,0,27,-35,-22,50,-30,2,-19,-8,4,-26,-17,-15,-3,12,-10,-18,-16,7,-6,6,20,43,23,41,-12,15,24,12,-14,29,-11,-32,-7,-34,-25,7,9,10,-25,9,6,-34,-11,-27,-14,-47,-5,8,-16,15,10,5,-8,9,-69,16,43,29,10,17,-31,21,30,30,7,21,-2,-5,-5,4,7,-27,0,20,-9,-14,18,-34,-10,-1,22,-31,-40,-1,-50,8,9,-20,6,16,-25,24,29,5,-10,29,-13,1,50,29,63,-1,29,55,40,16,30,10,-9,-29,-20,-9,-36,-44,21,11,33,-8,-39,22,-1,7,22,13,-29,-12,6,6,-16,-21,-44,17,-13,-26,-55,-56,-32,5,-37,-29,18,-18,-64,-61,17,-22,20,14,-48,-13,-5,46,26,-27,-29,14,-6,-13,8,-45,20,-6,5,-22,-32,-41,24,24,-53,-36,-5,21,-16,-14,-34,-35,39,30,-5,33,38,10,3,39,-43,-21,-15,23,-17,5,-44,-15,-15,22,29,29,23,27,-30,56,8,47,16,50,11,10,64,74,24,22,-7,-59,18,-4,21,-5,1,-24,-40,-8,8,-23,14,16,3,18,-33,18,18,-16,-3,-22,-16,0,-19,0,-2,0,26,14,-5,33,27,5,32,26,-2,-45,-35,18,-5,-11,2,16,4,-31,-5,-9,7,15,-28,-21,-13,-2,0,20,14,-8,-8,-10,-11,-16,32,24,34,-1,14,-35,-30,-44,-30,1,13,16,-6,-34,-37,16,-1,17,41,5,-27,22,-10,10,3,-9,-14,-2,-19,11,25,-22,4,-10,10,19,5,-4,18,-1,-26,-57,-1,-7,1,-24,-25,-41,47,41,-32,13,1,-11,57,32,-5,12,-14,-16,-19,-63,-9,-22,21,14,5,17,16,18,-24,-3,11,-8,-2,2,-36,29,42,54,25,38,11,-22,-6,4,4,-35,-1,2,-26,-26,-4,-20,-4,-17,-27,-33,-8,-11,-14,-3,5,-5,-39,26,-51,28,18,40,33,-16,-7,-34,7,-33,30,10,-10,-30,39,3,18,-13,29,38,22,5,7,12,11,1,37,26,7,5,6,-22,4,28,-44,-24,3,-40,10,30,13,0,-6,18,-9,33,-33,-22,0,3,-16,58,-15,-47,-4,-1,9,21,-21,-8,-14,-16,-33,-14,-15,-15,-10,-8,-17,-27,-1,17,-17,-9,-23,45,27,13,8,-34,-25,-32,-32,-27,-22,0,13,7,15,1,38,66,30,27,-33,-32,-1,14,36,24,-19,-49,-70,-11,4,23,15,27,-68,-17,-14,-28,11,14,21,-44,-27,-35,-8,-27,11,16,19,51,16,-46,1,12,1,19,31,-11,14,36,37,11,4,-39,-27,3,50,14,23,-2,-17,29,39,64,46,26,15,-16,18,-13,-37,10,-16,-36,13,11,-46,6,88,-24,20,7,-3,0,-8,-18,-26,-53,-11,-7,-34,18,-1,32,23,0,-21,-9,12,-6,15,8,-30,16,-24,30,54,42,9,36,3,46,8,-18,15,17,15,11,-49,-19,14,20,-1,-35,-11,-37,11,23,12,-39,-22,34,-9,-13,-27,-56,27,24,-15,-25,-20,27,-41,2,-9,-43,50,30,-17,21,8,-40,39,-2,-37,-16,},

                    {9,-23,10,-2,-15,-22,9,-19,-31,-3,-45,-44,0,-8,9,-12,33,31,30,-28,-29,11,-11,19,-7,-41,-12,-2,-35,-4,-6,-15,7,-26,-45,20,-23,51,44,3,15,14,-30,35,46,48,-20,-17,4,33,40,9,-10,-4,39,42,40,-46,0,-15,40,5,11,-16,16,13,-41,-23,13,-5,25,-14,30,-16,-24,-2,-20,-22,-14,-23,-20,-12,-19,-8,0,-5,8,-44,-2,13,22,8,15,4,-25,20,23,-13,5,-30,-50,-14,-17,5,25,-56,23,-12,26,27,38,33,-21,7,58,18,5,9,-29,-16,11,-4,-5,25,-17,-32,4,-11,18,27,-4,19,-14,2,5,21,1,9,-23,0,-33,-22,31,-12,-5,32,48,11,16,-28,13,105,60,77,22,5,10,32,2,8,-10,3,30,72,36,16,-18,-26,40,-7,-24,4,12,6,21,-6,24,11,21,32,-16,30,12,15,41,35,20,-6,-32,-60,-41,-54,32,17,10,14,-62,-20,4,42,-1,20,-5,43,1,60,-16,-14,-24,0,-6,-24,-28,-30,-27,18,34,53,84,62,47,1,44,3,31,51,19,35,4,-16,-15,-11,31,-6,6,-3,4,-29,16,47,-7,-34,4,12,42,11,2,-52,10,27,19,1,-3,27,42,49,5,14,50,13,35,35,-12,-36,13,-16,13,18,19,-29,-3,-27,4,4,1,19,-22,0,26,17,-24,1,-41,-10,28,-19,32,2,47,10,15,-27,-27,1,0,-21,-21,-32,-32,-29,21,-1,-19,11,34,21,2,24,31,12,34,45,9,22,19,61,37,-15,-33,-55,6,-12,-36,0,17,-31,12,16,4,2,22,-19,-36,-6,-26,-33,-40,-11,-1,-16,-19,10,15,22,-9,25,-19,-14,-6,18,-8,36,-32,-30,-46,7,-20,20,8,-10,8,34,11,18,-12,1,-5,-15,-24,31,10,4,19,-14,7,-6,-3,29,19,17,-20,-27,-19,38,-20,18,-7,29,41,11,-4,-21,37,21,34,-11,48,41,1,-6,-7,-14,70,38,12,-17,-7,-44,44,62,3,-1,22,11,-17,-5,0,11,-2,17,-12,-6,-17,-32,21,-18,25,-40,-33,-44,16,2,21,2,-26,-35,-15,4,33,16,-40,-19,-48,-61,27,7,34,-33,-7,17,46,15,-10,-21,18,25,9,34,-15,-13,-21,-4,-11,-14,-23,-50,-36,26,10,-8,9,5,15,1,7,-11,22,32,2,26,1,-6,24,-27,32,32,17,1,-6,-23,1,45,-28,-48,3,29,6,14,-15,-28,12,13,23,24,-4,-3,-19,-38,-17,-11,-1,9,10,92,-10,-8,24,-13,-2,70,11,10,-21,42,-20,8,-25,-13,-24,-30,-57,12,-4,26,9,-20,21,-5,22,7,26,37,17,-7,24,19,33,32,1,-25,-18,-15,-2,-19,6,35,-25,8,14,-1,22,29,-4,55,0,-18,-6,5,9,-5,-50,-13,8,2,-20,4,37,9,-5,-29,40,17,48,48,-12,-55,-46,-29,-3,1,-23,-15,-43,-34,23,3,-10,28,6,51,8,-4,-13,31,-13,-3,-49,-25,-20,6,10,6,47,-14,5,-28,-44,-28,38,27,-3,-8,20,6,22,2,5,23,4,74,18,17,12,-8,-19,13,17,20,0,10,-11,-7,0,7,-46,-17,21,15,-4,-6,22,-19,11,-14,-8,-12,64,51,37,17,-6,9,21,43,-13,-4,-9,2,24,34,-20,32,-34,8,4,2,1,32,-80,1,-19,34,15,-1,25,14,35,-3,2,3,4,25,42,-2,-9,-3,-19,-11,-4,8,-28,-23,-11,-17,38,-26,34,16,-36,-8,16,-1,-10,-6,-64,-11,3,15,13,26,4,-13,62,53,-18,-4,16,38,-40,-13,0,-4,-2,-34,1,38,-10,-21,24,-19,-11,2,11,3,20,-3,3,5,-10,15,-40,-4,-19,10,11,-12,-1,28,-29,14,18,-10,19,-50,-80,-34,-47,-44,31,6,35,-3,-63,-10,1,-2,-8,-13,22,4,4,49,-2,18,-3,35,-6,-16,6,-16,-23,2,18,7,0,3,2,8,24,-5,37,31,-8,39,21,-9,39,29,-6,-18,8,44,21,6,-5,70,-23,-37,-14,22,-1,5,-10,-10,14,10,9,-8,27,-30,4,-10,15,17,10,-32,-6,8,35,15,1,-20,26,-9,40,50,10,-2,0,0,5,-3,-52,-46,7,21,41,-9,-12,15,23,43,18,-6,26,-23,-10,-31,19,5,-15,23,-48,-69,-54,-48,46,12,-40,-16,-49,-29,33,-8,3,5,16,16,10,28,7,14,-15,-3,-16,-28,-20,8,29,9,10,-57,31,-19,-19,28,18,-11,-12,-10,-30,-23,19,20,24,-30,-11,1,28,43,28,5,0,-5,-11,10,35,32,-11,1,-22,19,22,11,38,-35,2,31,36,-19,33,18,-9,57,6,94,7,-8,-1,-9,44,28,-31,-1,4,-15,10,-4,-15,1,13,-19,-37,7,22,29,7,-3,-8,20,-18,-7,11,-24,-26,-18,-26,-16,-10,-11,-48,-36,-37,-32,23,28,31,18,27,66,-24,51,31,22,21,22,-7,-2,14,10,-8,-11,-38,-39,-27,-12,7,-6,2,-9,34,41,24,-2,82,37,69,16,-3,-11,10,4,7,1,9,16,-28,-20,-5,-8,4,7,-32,-15,-35,5,-9,0,13,-38,-49,-15,-6,-1,1,25,44,41,15,-3,74,-1,12,40,-24,-67,16,10,-2,21,-20,38,-8,-20,0,40,-7,38,-9,-11,-20,31,5,13,-27,-15,5,-30,18,-4,4,-2,-15,-17,13,-18,-12,-16,-6,16,8,-30,-44,61,14,15,-61,-34,8,29,6,-40,5,-3,10,30,32,-11,1,1,-48,18,6,0,7,20,18,47,32,21,-5,-24,57,-12,27,-39,-29,-36,6,-2,-2,20,-4,-24,7,-10,36,8,23,9,-15,-10,13,3,14,-11,-12,31,-1,28,5,24,},

                    {-2,1,1,-11,-7,15,2,0,1,7,37,22,-7,2,-1,14,3,0,-1,2,-17,5,-35,-38,-35,43,29,28,-44,-70,29,-5,49,24,-12,-72,14,12,-19,4,-16,6,29,-32,-71,-20,-29,14,18,7,2,-32,-17,-5,4,3,40,23,-5,-30,-5,21,-18,-2,31,1,-37,-54,-25,28,3,12,7,1,-32,8,3,0,-9,14,14,25,6,-13,-7,-6,-22,4,7,-18,4,-26,-20,21,10,-16,-36,-22,-1,11,-32,-22,-3,-5,21,36,32,-13,13,-4,17,13,-13,22,3,15,19,24,-38,18,-13,-35,0,46,38,17,17,13,12,-12,17,-1,4,-15,14,-7,-9,-7,-2,3,19,17,-4,8,2,-26,11,4,-10,31,-1,-23,-92,-32,-18,23,-15,8,-14,-11,15,4,-8,8,-6,8,3,-21,0,-27,-3,-3,18,-2,-11,-3,-54,-7,34,10,25,-36,9,4,20,-11,50,13,-15,-23,44,-4,5,-3,-28,-19,11,18,32,-38,12,-32,16,-17,34,17,49,6,-53,-45,4,19,4,6,-9,-12,-4,-18,-8,-10,-39,10,7,-76,-41,-30,26,15,9,8,42,4,16,-16,40,-10,50,3,-14,27,49,0,-28,1,6,0,46,46,-2,-11,2,4,18,11,30,20,-28,-3,13,-12,12,35,-16,33,-24,-38,13,54,4,20,-22,11,45,59,37,32,10,-9,12,32,-1,61,7,21,37,-3,-43,-11,-9,-38,2,-22,29,22,17,-22,-15,29,31,0,-17,-41,-17,40,-14,-20,48,-28,-71,-36,-67,-17,27,-4,-10,-31,-7,-52,-10,26,29,28,3,18,20,-21,20,-57,0,1,6,-31,22,12,5,-26,15,-7,18,4,-11,12,-19,17,76,70,43,-38,15,-9,14,4,-13,-34,36,8,-10,-11,6,53,34,4,-23,-10,-21,17,-10,-29,-13,-17,-17,-12,8,-5,28,25,-4,-4,34,-10,25,32,-5,-38,31,0,3,11,12,8,21,-33,-8,40,32,55,3,-9,-10,7,-27,8,3,-16,-22,22,19,10,-1,-81,-16,5,26,-9,51,36,-21,-4,13,13,12,35,19,30,1,-60,-4,17,-5,18,-27,-49,24,-25,-29,-13,-30,15,-16,-20,-5,6,9,20,-18,5,10,12,36,-10,12,-11,-7,-46,-16,-83,4,16,-19,-10,-60,-83,-22,11,47,24,-7,18,3,36,9,9,-1,6,10,-25,10,20,-27,26,-9,-15,-13,4,-2,0,-18,-10,-6,-1,29,3,-5,-26,-16,11,6,33,-13,14,21,9,11,15,19,3,28,22,38,25,1,41,5,-28,-7,1,-18,8,-26,-23,-9,22,-2,-11,-10,-23,5,-37,36,4,-13,-9,16,-8,-9,67,-11,7,44,42,8,15,37,6,-21,-8,33,0,1,17,-11,28,-7,21,14,34,-37,11,-29,-5,-12,-28,28,-24,17,20,1,-26,-56,-92,-5,46,17,-30,-38,-19,-5,-4,35,44,45,21,5,-30,24,-6,10,-4,23,-26,-5,29,-17,23,-21,-22,-22,-26,28,-12,16,-16,-14,-38,-40,-70,22,1,10,-11,-38,-30,-4,-18,1,30,14,3,2,-43,0,31,2,-7,17,-30,1,-2,-13,-15,21,29,-26,-6,14,-19,-9,10,9,-39,13,-52,17,4,14,6,-42,-47,26,-24,-7,4,-41,6,29,-29,6,-40,-22,-6,17,-24,10,-33,-8,-10,-28,14,37,9,14,19,9,-9,8,29,41,-9,41,20,-2,2,5,14,3,-15,-5,20,0,-25,18,-17,37,2,29,13,0,-8,22,11,-5,5,-16,6,27,17,-26,21,-6,-8,17,-35,19,12,0,20,-28,-15,-25,-4,5,17,9,54,8,25,10,-26,-28,4,16,4,16,-54,-31,59,-16,-4,-35,-30,-25,19,69,28,6,-9,11,-30,-37,-40,11,1,37,-3,-54,-6,11,7,-37,-12,-23,17,4,16,-17,18,34,-7,-6,13,-6,-1,-1,19,-3,-28,16,12,-10,-6,-6,14,-17,-15,-18,-44,-32,-12,1,39,0,9,-8,6,-1,5,37,-17,-7,-8,-12,37,35,-20,14,-18,-18,-1,0,3,7,-10,-29,20,12,-1,33,-18,-33,-9,35,14,-4,-9,-12,9,32,30,2,20,-2,17,5,-4,23,-7,4,2,-39,-12,-13,1,7,4,5,-15,9,-40,11,-15,-29,10,-15,-1,-23,-27,16,4,28,-17,23,-22,11,6,17,-9,12,6,-35,15,17,0,-11,-10,17,-14,-2,-12,29,-12,-20,13,-29,-37,-26,-24,21,-24,12,-5,5,-21,-66,-43,-26,19,16,-12,-65,-18,-1,13,9,-8,12,-13,-16,24,21,54,19,-27,4,8,-4,39,13,34,-26,-42,-1,33,-7,26,2,14,10,25,-6,14,-20,-30,45,28,52,-12,13,-39,-15,19,12,12,-7,17,-49,-37,-2,3,-7,14,-28,7,-16,13,12,16,9,30,10,-14,6,-7,-21,-32,6,-23,2,4,-11,18,-10,40,14,0,-15,-5,22,4,8,8,28,47,29,16,-16,-49,-9,-35,-13,-10,-1,-22,6,-55,-55,-44,26,5,-4,-24,7,-63,-36,22,44,12,9,-13,-8,-1,3,21,19,14,-18,14,0,1,-27,1,22,-55,-39,9,33,-13,22,58,33,70,-12,36,2,47,16,13,6,-3,10,38,13,14,10,-7,1,-3,23,6,31,0,-16,-13,34,21,36,26,-18,-70,-28,2,29,-7,10,28,3,1,12,-19,50,-17,13,-34,0,-43,-17,49,7,-35,-11,-14,20,-22,10,-13,-25,-9,4,6,-25,-40,4,-10,-3,16,12,-3,30,27,39,45,61,36,-5,-26,4,-20,53,28,-11,-39,-24,-15,17,30,3,6,8,22,17,10,-13,28,39,12,-34,-4,-12,20,8,19,31,-25,23,10,10,49,56,-39,-15,28,30,-8,21,-7,-5,16,20,36,-24,-8,-13,42,},

                    {-4,11,-1,-4,-1,-7,-2,-5,13,-4,-48,-2,21,-7,17,-9,19,4,2,5,22,43,15,17,52,7,8,24,-3,-15,-23,-11,11,-25,22,70,-1,-11,39,-20,-19,-8,1,43,18,41,-12,-18,39,-1,-37,-12,15,21,3,-40,-31,11,4,5,13,-13,26,-25,2,-27,40,-49,-27,-47,30,24,12,4,0,19,-18,14,-12,-5,19,17,-25,26,13,10,18,-19,6,33,27,38,19,24,5,17,58,27,-23,12,-24,2,-25,-55,-35,-21,16,-18,-30,-12,0,3,10,20,-14,-18,12,11,11,-34,19,6,25,-18,-29,-16,-6,1,0,9,26,17,-6,-14,6,53,8,8,-21,22,18,17,5,17,12,27,57,1,22,-36,15,41,38,13,0,5,13,-6,-36,2,21,-4,-47,-27,-7,14,-3,-22,25,27,4,-10,12,4,15,-30,-16,-36,-12,8,21,19,53,54,-13,3,0,1,6,-17,-5,-18,28,-4,-14,-2,7,-20,-18,-3,17,12,3,22,4,-25,-28,-20,22,21,48,-7,23,-12,18,13,18,49,2,34,16,-7,2,-18,5,2,19,31,9,-4,-22,-16,30,35,-33,-4,20,9,-13,-13,-33,29,41,-8,12,-7,39,9,26,-10,11,-4,-13,36,-11,31,27,5,-26,-6,5,22,16,-12,8,-10,13,-33,-9,-34,27,-12,-5,-39,-15,-4,3,23,8,2,1,26,3,-3,16,15,36,-3,16,46,-5,7,-16,-27,-7,-7,2,-7,-18,-18,20,-31,16,-17,-10,-25,-27,6,31,9,4,19,44,-18,16,33,16,26,-3,-6,-2,45,39,48,-13,64,30,34,-2,-29,2,-12,4,31,37,37,10,-9,13,-2,41,33,5,-20,-46,6,40,52,-5,-40,-54,-4,2,-2,-17,4,-12,11,34,21,-13,39,-2,6,-4,11,57,12,-1,32,-15,14,-5,-4,5,-20,33,37,-30,11,38,27,64,27,13,11,28,21,-17,-21,17,-8,-28,-15,-1,-24,-11,-4,-23,-15,16,15,16,-9,0,-7,-5,13,-4,39,14,11,-11,17,4,5,30,72,8,9,-19,-59,-31,4,45,11,-20,-16,-11,13,52,50,5,48,39,-24,-8,-1,0,17,-6,-22,-2,-30,-33,-16,-2,-14,13,19,16,23,24,-5,6,49,41,13,5,-6,14,18,3,-5,-22,1,-3,60,19,23,21,-15,-9,2,13,-4,-10,-16,5,6,29,-8,-13,-41,4,13,-10,25,36,11,-18,-22,20,32,48,-8,-5,-13,-15,18,3,33,13,-17,-6,6,-29,-17,5,-19,-3,-37,21,4,-34,-15,4,-10,-10,-31,-12,12,31,-22,-36,4,39,19,0,-28,6,10,29,8,-15,-10,38,-22,20,-26,22,39,-25,18,-16,3,12,7,18,14,13,-20,-14,-21,3,-5,-5,-19,22,-24,25,29,-1,18,10,-9,-22,4,5,12,18,-16,6,-15,-13,26,28,68,20,35,-4,-9,7,-5,-11,-13,-2,-23,-11,-7,-14,-25,-4,12,33,-3,25,10,-1,61,1,-21,-43,17,6,28,3,-9,14,11,29,16,21,5,-23,2,-8,4,16,26,13,-5,-36,-13,31,2,6,4,-22,-7,20,3,-12,-13,-28,-6,-4,-38,-43,3,4,47,4,-26,1,25,50,58,-6,20,10,14,2,-22,2,-11,-1,50,31,-1,-6,2,-49,21,33,8,10,9,-36,11,-3,-37,11,70,-3,-10,5,-27,-19,39,-18,-16,-1,46,-2,7,0,13,-24,-10,-20,7,30,16,-13,5,-30,-9,-28,9,-14,-17,25,-9,12,-25,11,-9,-6,34,20,14,35,-10,-29,-4,2,2,23,18,-12,-12,12,12,5,-20,-11,-2,-12,-19,-4,-5,-3,-10,-12,13,-19,-6,27,20,-13,-43,6,30,14,-8,12,17,10,40,-4,34,-3,20,47,1,-6,8,12,-3,-3,-15,-17,-15,1,5,-8,-26,-10,-3,3,17,-2,-7,-16,19,-12,1,-7,41,18,32,30,23,-8,22,39,2,13,-8,5,11,7,2,42,-3,-23,27,25,2,12,8,-45,6,19,-13,-13,-7,-51,-39,-38,9,21,26,-26,-27,-14,13,45,15,-9,-23,12,0,-17,3,40,6,32,17,21,-37,-3,9,12,-18,6,39,40,33,8,-19,-4,-33,48,57,7,33,41,12,11,45,39,47,40,30,-47,-9,-17,18,-39,46,-6,7,7,4,35,22,28,-7,-6,-9,-29,-13,-24,-21,14,-5,-2,-3,13,-8,25,10,-5,-6,-3,30,36,-11,-44,-1,-8,51,29,-5,12,0,41,50,15,17,-17,-1,-2,11,-6,-30,15,15,19,-4,-37,-13,37,-69,-4,13,0,64,47,8,-18,13,37,20,38,7,-18,-21,-16,13,-46,-34,-39,7,-8,22,27,17,-16,-30,12,27,-2,33,8,-4,10,23,4,-22,2,7,-12,-57,-2,50,24,19,4,-2,30,-9,-27,4,20,24,-20,20,2,-25,3,-14,-31,-8,-15,0,-8,-11,17,-2,-15,-32,10,57,25,-18,-14,12,24,48,22,49,31,32,14,13,3,2,-6,-27,-3,-38,9,-4,27,29,11,37,4,6,37,15,19,-16,1,13,15,19,14,-14,24,10,14,3,35,-37,-39,26,-2,13,-5,-24,-2,-13,16,28,-22,-12,2,8,-10,10,-35,-20,-12,-7,0,17,-10,-43,-25,4,-12,-29,31,25,19,-21,-36,-1,-20,-14,-14,13,51,37,-6,-7,10,40,20,30,-37,54,21,18,-33,6,23,5,34,41,-14,8,17,38,29,-6,-31,-15,32,32,-5,39,-6,20,2,-18,-20,-27,4,-12,-14,-28,-2,-8,-24,-20,8,-10,-5,-38,6,25,4,19,13,19,-14,15,25,-33,11,-10,-5,-11,25,-18,-9,29,27,10,-13,-20,29,-15,-5,-7,-28,9,18,-32,25,4,-15,35,8,3,6,11,},

                    {3,19,-32,-4,8,-18,8,4,27,12,2,-27,-4,6,-17,-13,-24,16,-46,24,29,13,16,-49,-43,8,34,-5,30,20,-6,33,-15,6,-20,9,16,31,-17,29,14,-9,43,18,2,-17,1,-39,2,-4,-36,-2,-12,-7,-34,-26,-36,19,-6,24,-15,-21,-17,24,-20,5,3,48,10,32,-13,-3,8,9,11,-3,-4,-42,18,16,18,7,-18,-42,-11,13,-22,0,-6,-1,-48,-15,25,47,22,-49,-53,33,37,-1,35,3,-9,2,15,0,-71,10,5,-33,-29,-31,14,-1,-17,2,-2,-17,9,13,-8,15,27,4,14,22,9,34,39,-14,-20,6,-11,23,-9,-36,3,25,3,3,-28,-11,-27,0,11,9,-21,16,6,3,12,-45,-18,-44,-8,-20,-7,24,-4,-3,-11,-10,2,-2,-15,-8,15,14,-19,-8,-29,34,-11,-9,-38,10,-6,9,-9,-4,15,-16,1,-26,-2,45,12,-12,-49,10,15,17,-39,-83,-18,11,-11,14,-13,-35,19,21,-6,5,5,-46,13,16,15,-19,-26,-9,18,10,-8,1,1,-20,-31,-47,-23,-41,-26,18,6,-7,-36,-80,8,4,11,12,-40,-24,7,-12,9,-5,-5,-24,-1,-6,-3,20,-6,22,-51,14,0,1,15,26,27,-33,-36,-37,-20,8,-36,-11,12,-30,18,5,9,13,40,1,2,0,8,10,31,-9,-21,-28,-7,-6,-45,-23,21,5,-11,-1,-52,12,-11,18,0,-13,-18,19,27,0,22,12,-5,7,3,-6,-8,-18,3,-1,-8,23,-5,6,-3,-9,25,9,-27,19,-34,-63,-27,-4,8,3,-6,-16,-22,-25,-6,19,-18,4,16,14,1,15,-30,-7,18,-18,22,2,15,-31,-23,-49,2,-9,16,-19,-24,-3,-4,1,9,6,7,42,6,4,23,-8,19,-7,5,3,16,-36,34,-19,6,42,12,15,-5,-66,-15,14,1,-8,-19,-53,12,-28,-36,-1,-32,12,-34,-23,22,6,-28,19,-5,29,20,-16,-30,-35,-20,-12,-1,-13,12,-21,-45,-50,20,14,18,0,-57,-41,-11,50,-1,11,-37,17,-23,-49,-18,-26,4,20,-12,-47,-114,-30,7,29,11,12,-46,13,4,-25,8,5,26,0,-43,-9,22,13,-1,-4,-18,-18,-8,2,0,-27,-4,-26,3,43,34,-39,-53,-20,9,38,-1,22,2,10,23,-1,1,-43,7,11,37,14,1,-2,5,15,5,14,-24,-63,17,35,30,9,-14,-35,3,-1,13,-11,1,-3,-16,38,8,3,-15,-16,-6,24,4,6,-6,-11,7,4,9,42,-22,21,-10,-36,-5,-45,32,-16,-7,13,23,6,-14,-12,-2,17,58,-14,-15,-16,-27,18,53,16,-5,-24,-4,1,19,36,-17,7,39,-45,-23,-16,-27,1,-40,-23,-2,-14,20,-40,13,14,-1,-29,2,2,7,39,12,-22,-43,-5,-15,19,-8,2,27,7,16,29,-24,-7,-18,-12,-2,10,2,-34,-18,35,-20,-47,-44,5,19,44,7,-16,21,23,-11,-9,19,19,36,6,-44,-64,-6,23,18,-20,-8,-8,-12,11,2,-19,-33,-10,-20,-14,-11,10,-3,-35,-18,-17,24,23,-1,17,-12,-74,-111,-47,63,47,-17,-36,-4,0,17,-1,11,2,25,26,-38,-36,2,45,15,-27,4,12,14,1,10,22,32,47,-3,20,9,-31,-53,-11,10,41,-18,-42,-13,9,6,10,-41,-7,6,3,-18,-44,-5,8,11,11,8,20,33,33,13,-7,25,-7,-23,-3,-18,26,-43,9,-17,-69,-22,-46,10,23,31,-32,20,29,5,29,-27,1,-15,-30,-14,-26,-35,15,22,15,21,-15,-17,8,10,1,-9,-12,-42,-41,32,-4,17,-41,-13,0,-1,32,-20,23,7,-55,-10,-12,10,33,40,2,-43,-26,-27,10,2,3,-11,-41,-15,9,-17,-14,-24,20,5,2,34,2,57,41,-3,29,11,-7,11,5,-6,-12,-4,1,-4,-44,-8,11,14,41,29,-13,6,-10,29,-17,12,-8,-8,15,3,-8,-10,-31,8,3,1,29,-6,13,-2,4,12,0,-11,-47,-15,-10,-2,-24,40,16,8,-3,3,-12,26,-16,-4,0,0,-21,12,3,-2,-2,18,6,-11,22,9,24,17,37,-6,-29,-2,5,26,5,-43,-68,18,21,24,13,-19,-9,-9,19,-26,-16,3,9,1,7,27,-3,-32,24,-22,-14,10,-3,5,15,-10,9,-5,-7,-8,2,13,-17,-29,-5,29,57,-43,-76,-4,16,17,16,1,9,31,21,-11,-29,-4,-4,35,3,-31,-43,-19,2,-4,-9,-19,-10,9,32,-31,30,16,26,19,5,37,17,-15,-49,16,-5,-11,-4,28,-5,-11,-42,-38,30,29,-6,-38,7,-23,-14,30,-8,10,3,-11,-5,-42,-36,-11,-10,5,-20,1,-6,1,-39,0,-28,1,-5,-1,-9,-15,20,-12,-28,-3,16,-25,-44,7,12,0,22,1,39,7,4,-20,-4,5,4,9,-11,20,17,6,3,15,-27,6,8,15,15,-15,7,-10,-22,-62,-30,27,-19,3,-90,13,30,16,-6,-21,21,13,0,-46,-19,34,21,22,-5,-8,-15,9,12,18,-17,-70,-46,-35,-55,-31,-5,-1,-7,-39,12,23,31,22,-22,-36,1,42,-34,-14,-22,-5,-7,-6,8,5,10,3,5,16,7,-5,13,14,-23,-3,-31,-16,-16,-47,-12,-8,-20,-20,27,-20,21,58,35,8,-56,18,10,42,-44,-51,-4,-29,24,12,-29,-19,24,34,-16,-34,26,32,37,22,-6,7,-6,34,8,16,26,18,34,-10,4,11,-67,-45,-26,-3,-9,-43,-67,-27,21,41,9,22,-11,-34,24,5,-6,22,50,16,-8,-32,-23,-7,4,3,-1,-9,-36,-31,17,27,-4,6,26,9,10,45,-64,4,-3,20,28,-16,-19,-12,-47,-15,-3,-20,-2,-11,7,3,-32,3,18,24,-9,},

                    {-10,-18,-9,-31,6,24,6,-4,4,3,14,22,-12,2,-30,5,3,41,12,35,4,0,1,31,-12,-37,-13,6,19,20,-1,9,-8,30,7,3,19,-19,-60,-95,-45,-28,10,-31,-44,-76,-4,-38,-38,-51,-18,-25,17,4,32,10,25,-4,8,22,32,22,-23,1,-2,9,65,21,11,-2,12,-16,-6,27,16,-6,11,4,13,0,-32,-24,-1,8,-26,13,2,-35,11,13,2,70,43,0,3,16,-30,7,9,18,-25,-19,-12,3,-10,27,-32,42,-22,2,-10,-12,-33,-18,19,-6,60,13,-20,44,-2,0,4,-18,-10,-3,4,-13,-42,-24,-11,-4,12,8,13,-3,-10,18,35,18,22,-1,-14,10,0,-40,-42,-56,-35,-28,17,-17,-59,-42,-17,-2,-20,-59,-51,-7,7,14,16,-20,0,-21,4,2,20,46,8,7,7,22,36,4,-21,2,25,-34,12,-32,-50,1,-4,-21,-39,18,38,53,48,13,21,11,-4,13,-16,-10,25,10,16,15,48,60,-4,-17,7,14,6,17,-45,-2,0,1,-23,-16,8,-53,-46,-63,-53,-12,13,-9,41,-12,20,8,-16,-7,13,32,-9,-1,9,17,2,-11,-9,9,10,26,2,8,-15,6,-22,-3,21,3,18,25,-37,-19,24,2,-25,-25,24,-24,60,0,33,4,4,-3,25,9,11,8,-13,-18,-47,-14,-15,1,23,2,-3,-42,-27,30,15,28,1,9,6,52,-6,-11,-23,44,31,20,-1,32,29,39,-5,12,-7,62,49,31,24,-3,8,9,9,4,-9,-15,-7,-20,5,-29,22,12,-7,2,32,16,13,13,-8,31,11,-14,-5,1,-31,26,-3,18,-37,-15,27,-33,2,15,-26,48,-5,21,12,-11,65,0,8,11,-16,-17,-21,-26,23,-2,-33,5,3,48,27,-24,-36,-67,-39,-45,-37,-1,-6,-19,-66,-35,31,-27,-27,4,-24,23,13,21,4,13,34,55,19,1,31,26,9,6,-28,-4,-12,5,-3,23,-3,-5,20,16,3,-27,10,-4,19,15,9,-18,10,25,32,33,-15,-25,11,5,5,9,-29,1,3,12,12,-27,-3,7,-18,-67,-1,4,13,-9,2,37,-1,10,-5,14,2,15,18,19,2,-8,18,-18,-42,-12,51,30,-27,28,10,8,20,27,40,-27,-5,-7,-23,-22,23,-30,-23,3,21,-24,-11,-17,-32,-42,4,-11,-15,39,28,-19,-27,-7,-20,-6,3,31,-19,22,0,3,7,4,26,-29,37,24,39,10,6,9,17,41,2,2,10,21,-26,13,22,33,29,17,47,-10,-5,-27,-18,19,-27,0,-49,12,24,10,41,-44,-35,-2,15,38,-5,23,21,5,10,12,54,2,-19,-7,-5,8,-44,11,2,-7,-15,-14,-47,15,14,30,12,-10,12,28,36,-23,-9,12,2,-13,-31,-26,11,26,10,12,-7,4,-14,14,38,-11,16,10,-28,-25,-23,9,4,7,8,4,-22,13,12,41,42,2,31,-8,18,14,1,3,-21,-8,-3,-10,14,20,-10,-13,13,-2,9,37,-5,0,4,-27,-34,-13,-15,19,11,6,1,6,-3,-42,-23,-7,49,50,-12,34,44,-25,32,-3,50,44,33,35,25,42,-14,-3,7,7,30,48,6,-2,9,-13,4,-9,-33,2,-14,-18,-98,10,-8,10,16,-49,-63,-19,-4,10,11,-1,-29,13,23,22,-32,-3,8,12,8,17,-40,25,-10,0,52,23,-3,35,12,-17,-54,21,46,-5,-24,28,15,10,64,0,4,6,16,2,55,3,13,5,-31,-28,-42,-53,-35,-12,22,5,-41,-6,-9,68,24,15,2,26,16,-5,10,-36,-20,15,-16,-40,-27,32,31,34,6,-8,35,-4,13,6,-12,-3,5,7,-4,-4,10,31,-3,13,-3,5,8,20,3,7,5,-13,0,24,-4,5,-1,-43,-20,13,-3,23,37,9,33,-25,3,-36,-17,-28,-17,33,30,4,32,-14,4,52,-6,-10,24,-1,18,-9,37,22,-25,-21,1,-20,1,12,-15,-3,46,-21,-11,7,10,7,-5,20,-3,3,5,10,-20,1,-1,-36,14,-3,15,2,-9,15,16,-20,5,21,-1,36,14,-27,24,5,-15,6,-14,-41,-2,-16,37,17,4,-48,-54,4,-7,-20,0,-3,-39,9,19,6,26,14,-21,57,51,28,-9,13,-14,15,16,-6,4,14,-3,-3,-6,-14,-40,-3,-39,-5,-30,-1,13,23,48,10,36,39,39,58,18,7,11,27,16,3,24,26,4,11,19,-23,23,17,-24,9,9,-12,5,-5,-8,28,-30,-13,-6,-11,-8,21,-28,-1,-17,-24,3,-22,-24,-11,-12,35,32,28,51,-15,-1,31,37,-3,23,20,4,-8,28,0,3,24,-27,29,9,27,-26,14,-17,-5,-1,-24,22,-37,-50,2,7,-51,-23,17,-6,11,13,-13,-7,18,-1,23,9,36,-2,11,-6,9,23,5,-23,2,-10,-14,-16,5,26,17,3,-2,28,26,-4,-2,38,29,-9,-5,39,-26,-17,-9,29,58,26,-28,-3,-9,-12,-25,-29,2,8,42,-6,-3,-12,-28,-38,58,-6,-36,6,-16,5,-31,6,8,24,38,-5,3,6,8,-9,6,6,7,34,-3,-30,-29,-11,2,-12,-10,-6,-56,12,-9,1,15,8,-7,34,-4,-31,-1,-16,6,-13,-25,37,34,22,19,-3,51,-6,7,-5,-3,13,-21,24,-23,-14,-10,5,-5,2,25,37,-4,8,-3,19,-28,32,-4,-7,26,2,-9,-35,-70,-60,-36,-13,-13,-44,-49,-48,-21,33,18,-15,-25,-12,-30,53,69,85,21,4,36,12,20,16,33,-10,7,18,17,-16,-16,-16,-19,-19,13,-14,-5,-18,-14,10,37,27,7,-20,0,-7,-23,57,-13,27,19,-12,-21,-6,-25,-41,-1,17,6,1,-27,-38,17,18,-36,12,-1,22,33,},

                    {27,17,51,36,28,18,4,-45,-17,35,-32,-2,15,-19,-1,10,-1,15,12,17,-10,-25,0,22,11,-17,-16,-7,-23,-22,-23,-36,-32,-15,-34,36,21,31,-11,-6,3,4,25,-34,38,22,-32,-19,15,-20,31,13,-24,25,3,-8,73,-9,8,23,-1,-9,22,-8,3,-39,-13,-53,9,24,23,-1,27,-30,3,12,26,-12,-4,-34,-18,16,-34,-28,29,-30,-6,-24,-26,-7,0,12,-60,-27,10,-25,-1,-18,-59,-37,-82,-38,11,-24,-41,-73,15,-42,26,48,6,-30,-3,-7,22,-50,10,44,-22,-9,-22,-17,22,16,1,-23,-19,7,17,15,-24,-15,-23,-14,-28,4,29,-4,-8,-17,-20,-48,11,2,1,-3,32,-11,-9,-21,9,2,80,10,4,-35,-2,-17,-5,31,-18,11,-6,4,65,20,-8,20,4,-8,26,16,9,16,13,-28,35,-2,-27,48,17,27,66,48,23,27,44,-68,-31,-18,49,2,12,-49,-40,-63,-44,-36,2,0,-4,2,8,38,14,-18,-52,-41,-45,-31,-17,-35,16,-20,-20,8,56,-31,49,11,-6,-14,10,-91,-9,10,-7,-6,28,-27,15,1,27,-17,-12,13,7,16,34,-18,-21,-11,4,26,38,-15,-10,-1,42,26,76,18,50,47,4,-12,-12,-12,13,-31,39,34,-10,-24,-33,-13,21,35,11,-10,-28,-18,34,21,24,5,-32,-18,26,49,58,12,-11,-11,28,16,57,-7,22,-44,-19,-1,-34,8,36,-37,-20,-3,33,-36,-25,12,-20,49,-1,-20,-46,-2,-22,35,0,-11,-14,-15,10,27,-44,-33,2,-35,-15,-8,17,-9,20,-55,-43,-15,25,35,41,-67,-2,34,68,-12,-60,-34,19,-25,24,27,-32,33,-32,-4,69,6,4,-52,19,25,-10,3,-17,-8,-3,0,49,-5,26,30,38,28,-6,-20,40,-105,-15,23,-33,0,-16,-64,16,-20,-16,12,7,34,-18,-4,52,-6,20,13,-28,-23,15,3,-36,-33,-11,50,24,-49,43,-3,10,-6,-4,7,-12,-43,0,6,-27,-18,6,-15,14,-3,31,24,1,-24,-38,-12,-31,1,-34,-50,-39,0,-24,-58,19,-29,-39,15,29,26,40,40,-42,-56,-4,62,28,-43,-46,-17,17,-11,-21,-64,23,10,-23,8,4,24,5,-48,10,56,-5,-3,-38,-1,-1,-59,-20,-34,3,-16,-32,47,-7,-14,12,-2,10,-17,-15,-38,9,7,1,-8,-5,-35,23,-11,31,-6,-14,2,4,14,47,0,1,-4,11,15,14,-12,-8,-23,-15,15,-17,7,26,-11,-12,-14,-31,-18,-19,-40,16,7,-2,-33,-21,1,-23,20,-26,48,0,10,4,13,6,17,-5,-14,-3,5,28,17,-1,-14,25,3,-37,14,36,-24,-9,-41,-29,2,46,1,5,-5,-9,8,-54,-22,0,-22,-2,14,-19,8,10,-1,-14,55,-19,-29,-2,28,-1,-46,-24,10,23,-14,-12,0,36,-5,-42,-8,30,45,45,-18,2,-20,10,17,-37,-29,-9,-29,-13,8,-34,23,-21,7,-1,40,-20,-26,-20,11,-27,-25,-33,-24,-30,3,0,-3,59,-32,11,2,16,-12,24,-54,-57,-45,-2,19,20,-23,-10,-55,4,7,-19,-11,-31,-2,-30,-5,-28,-28,-52,5,30,-35,15,-56,-40,-19,-71,-35,14,53,-6,2,-38,-17,1,14,15,-13,-12,-8,-20,-7,40,1,-11,12,-47,11,48,49,-1,69,-34,11,25,19,8,1,-39,18,19,35,1,38,43,49,-24,-17,-31,-27,35,5,44,-10,-33,-15,-44,-10,35,-20,13,-1,-32,9,40,17,17,-8,-19,9,27,8,-7,-12,-12,25,4,14,51,-31,11,-6,31,36,33,13,50,-41,-40,8,-12,38,-15,-64,-14,18,-18,-1,-48,-20,-49,-35,-30,-6,-35,-36,-18,-13,-53,3,-47,-11,-2,-1,11,-31,17,8,-5,19,-22,9,11,-45,-75,-25,17,5,10,-22,-2,-13,-41,10,-20,-25,2,-51,-27,45,4,7,-28,-31,-16,-80,-8,-25,27,-8,-19,6,-11,7,-16,-28,-32,-31,8,-18,0,28,9,-14,9,-9,20,34,23,-43,5,-4,27,33,60,13,1,-17,8,28,23,-28,7,-15,-13,26,12,-4,4,-19,10,-12,12,-15,-10,-40,22,12,-33,15,-19,-26,28,13,35,17,10,22,11,24,18,-18,-27,4,-23,-64,-2,-2,-2,-20,5,-31,-13,5,41,1,18,10,26,21,37,-13,-3,17,7,-7,21,-55,-32,-67,-30,-41,-15,-25,-50,-70,11,3,1,-23,-39,-33,-44,-3,-37,-25,-7,12,2,3,8,-26,2,9,0,-17,7,-53,-2,-2,-16,-17,-23,-17,6,-45,-26,-12,8,-16,-11,-1,14,3,17,1,-18,11,-46,-16,-26,-32,-20,-39,38,-17,8,29,21,0,16,-27,-9,-10,-12,92,-17,-4,-11,-7,-36,35,-4,9,3,-9,-12,20,-20,56,-8,-17,9,18,2,40,-3,-12,11,23,-12,27,41,-22,-27,5,31,-6,3,-59,-19,1,-35,-37,-30,-33,8,-27,-3,36,-36,1,-13,29,-41,-23,-39,-58,-19,-38,-70,-45,-17,-39,-5,-56,-1,-22,31,7,35,12,7,-25,-11,0,20,41,-7,3,36,-6,-5,26,-50,-4,-16,-33,-8,14,-15,-23,-41,-63,-37,10,1,-3,-7,3,-24,8,-14,24,30,0,39,18,-3,13,-8,-64,19,45,31,-36,-29,9,-45,10,-20,-7,-18,23,13,0,-47,5,-19,-4,-29,1,6,10,-3,20,-2,-58,-3,-12,47,-12,56,35,-5,19,10,-29,-8,62,3,-4,-30,-5,-21,5,-32,-17,-16,-42,17,-1,6,59,-7,4,-12,-25,-4,-80,-3,-27,4,19,-2,30,4,0,-28,-2,-13,9,8,-53,12,-18,-9,-13,3,-22,6,-4,24,-15,-10,34,20,12,12,-13,-7,6,5,-12,12,6,-25,-1,-4,-18,57,-10,},

                    {4,-25,-21,-44,-8,7,-2,-36,-6,12,17,7,-7,12,29,4,19,-8,0,-11,-4,-3,-16,-28,-29,11,20,-31,-29,-20,20,1,-31,-6,30,10,-4,-7,12,-22,-33,13,-11,47,10,-18,-7,-5,6,-18,-14,36,-44,-15,22,-32,9,32,9,24,-19,-49,30,34,-20,-10,4,8,55,21,-8,-13,-2,-43,-9,-18,-9,12,-4,-24,5,26,12,-18,-11,13,-16,-36,-14,-36,-35,-43,-25,0,-37,-71,-28,16,30,-16,-12,11,-20,-7,-11,-13,4,14,-17,18,-5,-31,29,-29,-37,-48,-29,-28,-23,53,-36,6,4,27,31,9,26,27,-2,-8,-13,-33,-23,48,42,1,4,3,12,10,3,12,-12,-16,6,-9,29,38,-15,21,8,16,-8,-28,-15,1,0,-26,6,60,-31,-27,1,-41,11,24,3,25,-12,-24,-25,25,9,0,5,16,56,4,12,-1,-15,13,3,-4,28,43,21,2,-46,-3,8,31,-35,-25,-58,-22,54,41,17,-37,11,3,4,-22,10,-3,30,-55,-44,-49,-46,-5,-17,-11,-42,-34,-22,39,-25,-17,-34,-4,15,-36,-30,0,-9,-39,-21,18,16,26,-17,-33,-16,-4,-1,-17,-19,-5,24,-38,-5,0,-7,18,-42,37,42,-1,-16,-3,-6,34,0,-36,-4,7,-28,-62,-5,-67,0,-28,-42,-16,33,16,-8,-17,-28,14,12,-18,-7,0,-9,40,-16,-22,0,2,-2,19,0,-20,-12,22,1,9,-52,-26,-15,16,-7,-7,-48,-5,21,-3,-9,-24,13,36,5,28,0,-6,6,15,41,19,-6,24,-30,-3,5,-27,-8,-5,29,-2,-12,-6,10,-3,-56,-8,22,52,-17,-22,-22,22,30,26,0,-38,7,-28,6,-1,22,5,7,-81,-25,-51,40,22,33,-50,-33,23,-2,12,14,-45,-23,9,-7,5,19,-42,0,46,8,-2,-25,39,-46,2,18,10,52,16,-13,-56,-3,-34,-1,-35,-15,-54,8,-100,16,-15,-5,-14,-14,42,41,-20,-6,29,-27,11,-32,-24,-6,11,-2,-29,-38,-2,15,0,-17,-55,-52,-5,-21,-24,13,14,-11,22,3,7,9,41,37,-10,-66,-31,6,11,66,-29,-1,-28,-6,2,-39,-48,-31,-12,-36,2,-49,-15,32,28,-2,-20,-9,16,-15,14,18,-9,-10,16,-65,-69,-16,-26,-8,-21,-72,-52,-2,-41,12,-2,-20,-33,-9,-27,-6,-8,26,-9,-6,-44,5,-10,8,3,-20,6,59,44,-21,-85,-39,5,26,-12,-16,-45,-19,-21,11,-3,1,-31,1,14,22,-14,-18,5,-20,-20,-27,32,0,37,-31,-12,21,-21,-15,9,-20,13,3,46,-34,-12,36,-16,48,25,-19,24,-22,3,-15,15,-9,2,-44,0,17,19,-5,10,-7,-21,-60,-4,-25,65,-29,-64,-35,-4,33,18,18,-70,9,-31,-15,32,11,30,11,-21,-22,-36,31,40,5,5,-43,-5,-18,10,14,-15,-21,-39,-20,-12,-50,-5,0,48,-40,-29,-98,-30,34,8,1,-70,-33,-33,-5,79,13,-4,27,11,-31,6,21,20,31,-11,-32,-14,-11,18,15,-26,-53,-50,-57,-16,-31,6,10,20,-17,-16,9,16,-12,7,-9,9,-99,-44,50,68,27,-19,-24,31,53,35,11,8,31,-9,15,1,3,32,19,-25,-28,-20,-22,16,12,32,-19,21,-49,-20,11,-26,-37,2,-8,27,15,3,-16,-3,25,39,-2,-20,5,19,-8,-32,-4,1,12,6,-5,11,4,31,13,-30,-25,35,6,-1,-36,2,-42,-29,-19,-34,-24,26,3,8,17,-17,72,20,-14,21,21,-8,-3,-12,-10,13,-10,-17,3,-22,21,5,-27,-9,-44,-11,0,-6,7,-18,-13,20,-30,-3,-54,29,14,1,-61,-43,-37,12,53,77,-9,-1,-7,-8,6,-8,-1,-17,-18,-39,-4,0,9,-10,-13,-17,-57,-46,-16,0,18,-12,4,22,-3,-34,-20,-5,35,50,0,-20,-53,-15,-13,21,4,-31,15,6,-44,-47,4,-12,2,-1,1,-80,-26,12,-4,16,-24,-40,4,2,0,-35,-3,2,-6,-26,0,3,-13,-31,-8,-35,7,28,15,-42,-6,17,12,19,13,-39,-7,10,12,16,50,-19,-6,1,20,14,-1,-4,1,-6,0,-8,14,-3,-37,-53,8,9,-46,5,-52,21,39,58,13,-61,-42,-1,12,-18,18,-12,-25,-31,6,-14,-2,-13,-8,18,-21,-31,-17,22,-21,8,-24,-10,25,50,-13,12,-59,-29,21,5,-48,-59,-52,-28,30,73,8,-15,10,26,-3,-21,25,25,50,-29,-40,-26,-27,-4,-21,-39,-44,-54,8,1,-33,-14,-1,43,-9,-11,3,20,34,29,29,-13,12,19,12,-46,-25,-6,-37,-22,-1,-71,-22,-20,14,-3,6,-1,14,15,28,-8,-7,24,-7,3,-4,-20,-3,22,12,6,-8,-2,-13,-10,4,-23,14,67,-6,3,0,-31,-18,40,-21,-6,-5,12,-20,35,9,14,-20,5,54,41,6,-33,-8,-34,-32,3,21,9,-52,-10,3,28,39,85,-26,-22,-7,31,-2,-37,22,-47,-63,-17,-18,-25,-24,1,-6,-9,-34,-25,4,22,24,38,1,29,-14,-2,-1,19,-8,-4,2,-49,-58,-58,-6,12,1,-29,-15,-2,15,-2,2,32,63,-4,-21,-4,-9,37,-7,-1,11,-10,8,1,4,23,1,2,-4,2,-8,-16,11,-35,-16,-39,-41,-13,-20,63,-16,-24,39,46,31,-33,33,25,16,-35,-73,-26,-20,-11,4,-21,-20,-14,24,-13,-14,16,-12,-11,-17,-38,-8,1,56,18,2,13,73,12,-14,27,31,10,-67,-29,8,-9,30,-32,-21,0,23,-3,-2,15,2,13,19,-21,-19,20,15,1,-1,-37,9,-10,-6,-34,13,-4,-21,-31,37,-21,17,21,-47,24,16,-58,58,-3,-54,35,25,-33,30,-13,-48,2,-22,2,25,-14,0,-31,24,0,-30,-1,},

                    {24,21,5,22,-22,-7,11,36,15,1,9,6,11,-9,10,4,8,8,-14,-8,-4,-2,-13,2,-22,22,10,5,-25,-2,-20,25,65,10,-10,-49,-22,5,44,30,-8,22,-3,53,8,27,45,11,20,25,13,21,35,-21,-1,24,0,-6,-13,-8,-32,9,15,-18,16,7,-84,-81,-12,38,1,9,11,12,0,-9,5,-22,34,4,7,14,-5,-8,18,-19,38,48,30,2,-16,2,-16,-12,2,14,4,8,11,-7,-10,-24,6,34,50,-4,15,-20,12,-16,8,23,42,20,27,27,3,-16,-26,-2,-9,17,18,12,11,23,18,-22,-2,50,26,15,-1,-1,-16,-27,-3,-2,7,3,5,-28,19,0,-5,33,62,-9,32,17,-22,56,-18,59,39,5,3,19,8,-23,47,-30,26,8,20,-7,3,-19,20,-38,37,-21,13,9,-18,-17,-11,-1,2,31,-11,8,2,-20,-26,23,30,20,12,-24,-44,-13,30,74,0,-4,1,27,12,20,-26,-40,-5,-25,-6,56,16,9,-28,15,12,-4,10,16,16,13,6,46,47,22,52,24,14,-11,-21,32,8,-28,16,-3,-61,-7,11,-17,-8,19,-23,5,5,16,10,8,5,9,29,4,31,4,23,21,2,-1,44,0,2,-20,21,1,18,30,-5,-19,-25,31,-2,-19,-4,-9,-42,-1,10,-21,-1,22,-6,7,5,4,-6,-13,-16,2,-11,1,-10,-19,-46,-29,34,5,33,-10,-18,3,25,-13,-17,-9,12,-8,12,10,-20,-27,5,26,-11,15,28,29,8,-9,14,16,-3,-3,10,-33,37,9,-30,-13,-32,-15,23,-33,-15,-11,28,24,15,10,7,-6,0,1,-2,33,-2,-24,-2,-3,-8,7,20,-9,-63,-47,5,39,16,14,-10,-12,-15,-8,19,62,-1,28,18,44,-1,29,36,33,-22,14,8,-15,47,9,26,6,-9,23,20,-2,-1,16,27,-14,-52,-60,-35,41,9,-13,-17,-3,-8,-5,56,26,22,28,13,-1,4,-5,-21,-2,40,29,-20,-7,8,-2,28,16,43,-25,-23,33,11,-21,9,22,52,17,4,1,-19,-31,47,45,66,15,-6,-18,-60,-38,35,2,4,-6,4,8,34,37,1,10,-12,-4,25,30,18,-29,25,24,9,8,16,-17,9,7,-20,-3,26,18,7,17,-13,27,40,17,10,-14,18,50,-30,-8,7,-1,-8,-17,-24,24,3,5,17,-4,-48,32,1,-14,-4,33,-7,18,-13,14,-10,-3,-17,8,-9,18,1,-8,12,-14,11,10,38,1,-4,-9,16,-38,10,20,11,23,-20,-10,14,35,16,5,44,-61,-26,34,-27,-5,17,-22,6,-30,-11,-27,-21,10,-6,-15,31,-8,4,18,57,26,17,-7,15,14,57,10,-17,-2,-37,31,-11,6,-23,-24,-9,21,-1,-11,42,12,22,13,-9,-26,-7,16,10,15,-10,-25,-16,22,-30,1,12,-38,-10,-43,-15,30,46,4,-5,-14,-34,-16,36,48,10,-43,-28,18,11,3,23,20,18,5,-18,2,6,19,21,-24,19,-4,-10,-12,-21,-2,24,7,11,13,8,-2,32,13,-3,-8,-10,-31,7,17,5,-14,-61,-25,30,42,-22,-41,-45,-14,-5,27,8,-21,-1,-63,-14,0,-11,6,-40,-8,18,5,7,-26,24,6,-13,-37,11,19,67,40,-26,-64,27,6,18,-3,-27,-19,27,-32,-27,-4,-2,-15,31,-2,21,17,-16,-20,6,21,1,-6,65,14,-13,-13,44,-2,3,-20,10,-2,24,33,-38,-40,-11,-21,-45,-1,2,-26,0,-4,-8,45,4,-7,25,-21,25,-14,-38,12,-4,13,-2,17,12,0,14,24,-13,30,43,29,-48,-71,-43,23,24,28,-13,-43,-9,-16,15,1,-1,3,15,12,26,3,12,33,-3,-21,-13,6,-22,-7,-8,-18,13,14,4,19,-28,28,7,17,-2,1,-53,-2,31,31,7,-4,35,16,3,-38,-18,-9,-5,-32,-5,12,10,-28,-23,22,1,-21,2,15,-2,-9,5,-13,25,13,2,-11,-4,20,-26,-16,2,-10,-9,5,-7,-6,-12,21,0,8,-14,0,9,-8,15,-9,-45,-14,5,-32,4,21,-4,-54,-8,13,0,13,-6,-5,40,22,39,-12,-30,11,46,16,18,6,-29,-22,24,-6,-21,-2,-3,18,6,2,-16,-22,1,-10,-8,-26,-2,-8,12,-33,8,3,16,-23,14,-8,0,33,18,21,-11,3,-45,-15,24,51,-9,-22,-11,-8,5,13,1,-2,8,-20,-29,29,-7,27,23,-4,-3,-7,-5,17,-7,-10,1,0,14,-14,-20,11,15,-5,1,-11,12,-21,9,8,7,25,19,30,-7,-3,13,-17,-41,-19,-13,2,-3,-11,-4,33,-8,-14,36,0,29,29,0,10,12,-10,26,-25,5,34,9,-51,20,2,1,14,-26,-48,58,-15,21,0,3,-7,14,-35,11,-35,31,-17,-25,11,15,-21,-18,-6,11,-8,29,22,2,8,-4,-3,22,8,-12,6,6,-41,12,8,-1,19,39,19,-27,-1,29,3,22,-3,4,22,43,2,-25,-25,24,20,-40,-24,22,-47,-8,3,-22,-15,1,19,45,46,13,-45,11,-4,40,-4,-6,34,-4,26,1,-5,-28,7,20,-12,0,4,-11,3,-20,11,24,29,-6,-12,7,-5,28,-30,-18,-25,7,9,15,21,-5,-15,12,-1,21,11,-21,10,41,13,-3,-7,-4,61,53,12,9,3,-27,-7,-12,-25,35,33,-17,-22,-36,0,-3,4,-2,6,-22,20,13,-9,-5,-35,10,23,-27,38,20,-3,29,42,10,13,-34,-38,-66,-61,8,-27,-35,-54,2,22,0,-65,-23,25,38,26,25,9,-4,2,43,4,2,-14,-43,-33,11,-13,-2,-16,-44,27,-36,20,22,-6,-5,-12,-2,35,-1,-4,34,-2,30,15,-15,22,9,16,7,0,},

                    {-11,17,1,27,34,1,41,8,-20,16,5,-13,-15,11,4,9,13,3,30,31,13,15,14,37,52,-63,-3,-26,0,19,7,9,-49,-35,3,55,27,-19,8,-10,-6,-22,-20,-15,2,-21,-4,-17,32,-7,-23,-3,9,-25,18,-31,22,-1,-5,-16,30,-24,7,32,-22,-15,44,38,35,13,-9,-24,-9,22,-24,-10,18,13,-3,-38,-2,26,0,2,11,40,29,-13,1,13,59,26,4,-16,-29,-2,-2,-15,7,-35,-42,-33,-14,24,-55,-76,-32,32,-4,30,-29,7,-39,-6,1,-2,10,5,-5,14,10,21,-1,0,-5,-8,11,-19,37,24,-6,23,18,-2,-10,-26,5,21,-1,-20,-22,-17,1,0,-7,-32,5,-33,0,3,-11,15,26,-2,-11,-10,22,-21,-26,11,12,-2,19,-29,-12,7,32,-5,0,-1,29,28,10,-36,27,19,44,39,-1,-34,26,26,34,-14,-30,-24,2,28,14,43,34,23,-28,-39,22,13,-5,8,-16,10,21,-3,-27,10,7,34,45,10,18,11,-18,16,-40,-48,-13,-12,-34,-17,-9,-6,-37,2,9,-4,-5,-15,-7,-9,11,-46,-29,-9,10,-8,5,-17,-23,5,35,15,29,-49,-15,43,23,20,-10,-6,27,52,5,42,9,6,-33,-4,-46,1,-2,10,9,47,-8,-27,5,22,7,34,5,-37,10,3,5,-14,19,30,-8,-3,-17,5,25,2,-6,-12,3,0,37,66,-30,12,-4,-8,0,-1,0,13,-16,-14,30,0,-2,-34,-32,4,1,-3,-18,38,58,48,42,21,-15,-14,-5,-18,-1,6,-25,-18,-2,-28,-19,36,-13,-8,-24,10,-17,-31,-10,-9,6,14,28,3,-14,-3,29,22,-13,7,5,-9,28,2,24,8,17,11,29,-19,11,67,-7,-41,-13,9,31,7,-18,6,7,12,0,-8,25,-2,-16,19,14,-10,-31,-15,-2,-17,12,8,17,34,1,-20,30,16,5,-44,-17,3,-51,32,-11,14,36,5,-16,-12,-4,7,-23,-5,6,-27,7,-19,4,-3,3,-1,-9,27,-18,-21,-47,-9,-27,7,-11,-7,-47,21,-32,-80,-37,-50,-59,16,12,4,4,-32,66,82,4,-34,12,17,28,-3,20,-26,-9,-17,6,-3,-2,-9,-2,18,-40,18,33,9,54,20,33,30,-2,6,24,0,0,37,-18,-27,-43,-50,-22,-8,-12,-26,-18,-5,17,9,-14,-15,-11,14,9,-15,-7,-11,17,8,12,5,24,15,1,13,12,25,23,16,-19,29,36,-7,10,-18,10,11,30,-8,-6,-14,-23,-3,1,47,-19,-36,6,10,20,15,13,13,1,7,26,29,15,25,19,-2,18,-24,-27,61,23,-8,12,-2,-5,-17,16,44,7,-15,17,6,-14,-5,7,-37,2,8,-5,-43,-6,22,13,-30,-12,-60,14,17,16,37,12,5,9,46,13,-29,-8,10,18,67,-10,-5,9,-3,46,9,15,13,-16,-31,5,-17,7,12,-18,-41,-16,18,-18,-24,-6,-38,-56,8,6,33,23,24,-26,27,32,39,40,20,10,26,-29,-38,-43,-40,-3,35,-6,-4,-1,10,13,18,-22,-11,24,5,-11,-19,-4,23,36,38,14,41,-23,-50,12,-10,-45,17,-19,-1,15,5,14,42,35,6,-24,-44,36,68,23,-33,9,11,-34,-18,-17,-29,5,19,0,-26,-18,-1,0,23,11,25,15,25,-3,26,40,22,13,-26,21,-4,-1,-10,-10,-12,44,22,25,-23,0,-9,-27,-28,-17,-6,-20,-2,3,23,-10,4,-4,4,14,-15,-10,16,4,-5,-12,19,3,-7,16,7,2,29,34,23,-12,2,35,31,26,32,4,6,19,3,-26,-18,13,7,3,37,-1,-14,-10,9,-43,-69,-2,32,-3,15,31,5,-14,12,5,16,26,15,36,12,-19,-33,-41,-7,11,35,-1,-5,-14,10,-9,-21,7,1,-21,-4,3,43,11,-24,-33,3,-19,-30,0,23,18,-20,11,42,33,11,41,16,-15,21,-11,11,-25,-48,-42,-16,1,12,-9,2,-35,31,-5,-17,-7,0,-3,4,5,-28,15,39,38,-9,10,13,0,17,57,-9,14,7,-4,-2,-17,6,0,-16,-6,26,10,5,-33,-7,-23,21,-13,21,-18,-27,-6,0,19,-16,-8,7,16,17,11,23,15,37,-7,-36,14,-3,-18,9,-26,19,-1,-8,-22,37,15,16,5,6,15,35,-10,26,1,-41,-21,25,5,-1,13,3,0,-36,5,4,-22,26,-1,6,52,14,-17,7,30,23,48,18,15,28,-6,2,-22,-43,8,24,-2,-8,-10,-10,10,-22,40,-16,-15,9,8,-3,-32,29,46,28,-1,-20,38,39,8,4,-14,-26,21,-52,-8,-1,-54,-1,-20,2,-4,-35,-17,-47,7,1,-16,18,-13,23,2,-17,-14,-21,17,-14,9,-4,-24,-3,10,4,-6,-16,-23,-21,19,15,9,-8,-6,-10,18,-6,5,17,26,26,9,-42,-11,13,-38,-7,11,-26,-8,-31,-11,0,-2,16,10,21,33,21,-23,-1,27,0,-2,33,-16,32,-12,-29,-56,-30,-59,5,-9,-31,-36,10,-47,17,-4,4,5,-1,6,-14,4,-35,-13,42,-25,-7,1,10,0,-17,-6,-3,-31,-13,-9,-40,-10,5,9,-7,-33,-9,10,17,26,-48,-20,60,8,27,-24,23,-22,31,-12,-41,-2,2,-8,10,10,0,-10,8,12,31,3,35,23,17,28,-2,13,31,-15,32,-8,-25,-4,-1,6,-37,7,46,14,18,2,-28,5,24,-8,-54,-6,14,24,4,1,11,47,16,-14,9,-35,4,-36,-60,-5,8,26,3,-17,0,54,4,-6,-20,49,20,-6,-14,-14,-24,-6,-20,-9,-1,-17,26,-8,9,14,25,-24,-3,13,-28,-7,-28,4,-15,-3,-12,1,23,-10,-2,-20,-7,7,28,25,7,-37,-6,45,64,38,12,},

                    {-28,-32,-49,1,25,10,12,-3,1,-10,-10,-10,21,-4,0,-62,8,46,-16,1,-7,1,22,-5,22,-12,-21,-9,-2,0,-22,9,-48,-14,-2,7,-23,-16,-25,-10,20,6,-18,8,28,-10,39,4,5,-34,-7,-6,-23,-4,-35,-30,-37,-13,-1,-1,-18,-7,-12,25,32,-6,44,29,22,37,27,6,-21,-32,-14,20,17,1,2,10,-16,-6,-2,-30,40,-13,10,-45,9,-32,-10,45,33,32,-40,-53,33,53,19,-21,-34,-4,-18,17,-11,3,-18,38,-17,-14,-34,-15,16,-33,-16,-15,-6,-23,-19,0,10,30,21,3,-13,-7,35,19,33,-6,22,24,4,-5,7,3,-1,38,4,22,12,24,-1,6,-16,-10,-20,-12,-15,16,-14,28,-24,-17,6,14,14,-30,-3,-7,-10,-8,-7,-6,-27,-19,-16,4,10,44,-31,10,24,18,-6,4,-15,29,37,-20,-56,26,-28,15,20,-10,-65,-35,-29,41,24,24,-45,-40,3,39,34,20,14,22,13,24,40,-15,14,-8,5,7,-13,-31,7,0,1,-19,-21,-8,-5,-19,-36,15,16,-9,4,49,46,53,28,-7,20,4,30,-9,-17,4,0,-19,6,-20,5,-26,10,-11,-47,-1,4,62,4,-8,-15,5,33,44,-17,-38,-18,5,12,-5,-2,-13,27,-37,-15,-39,-3,26,28,-11,4,-50,29,-9,28,-8,7,-53,18,-6,-17,-20,-11,24,-6,-4,-27,-7,27,65,-31,-22,-35,13,7,10,-15,-5,23,17,15,-3,1,-13,12,-1,13,10,-1,11,39,58,32,23,6,2,-7,-22,-3,46,31,-8,17,-4,-14,-21,-41,-9,-23,49,-9,37,-47,-9,-18,28,3,37,14,16,1,-54,-39,-1,21,3,-3,-36,-2,-6,17,-10,-21,-23,-27,-9,-10,7,2,16,18,42,-12,-13,-48,-13,50,-2,-20,4,15,18,-11,1,-10,0,0,-26,-15,-43,-8,-16,-11,-27,3,-39,-16,5,5,16,-8,-28,-2,9,20,14,35,47,-14,-45,-33,-24,30,-30,-3,-49,0,-30,-8,-16,-44,20,-1,-33,-10,-31,11,28,33,67,36,21,32,25,-16,14,18,24,17,-20,4,-10,9,25,-13,-14,-20,3,27,16,-42,-41,-9,-5,28,16,-27,-34,18,-11,-17,47,-3,-15,26,51,20,-24,13,-13,-26,-22,-36,-37,10,13,-1,-16,-36,-18,-4,-25,-10,9,30,-32,17,29,3,-3,13,-19,28,8,20,28,7,-28,15,-28,5,15,15,-37,11,6,19,-1,7,-8,-7,35,-10,-11,40,19,-18,-8,-13,47,36,17,-21,-5,-3,-21,7,9,-13,1,29,-8,27,-33,67,4,-13,9,-22,28,-7,-7,-1,8,-2,31,33,-5,-22,13,-1,13,-59,-32,-37,66,-17,10,-40,0,-21,4,18,-29,-3,35,-6,-11,12,-1,18,15,15,15,4,-14,42,12,8,2,25,-12,22,-3,-21,2,-2,-5,-43,-45,-64,16,34,-1,-48,-25,-48,-12,17,-14,-22,10,-9,-6,30,28,3,22,30,16,20,12,15,8,11,21,21,-2,15,23,4,-24,-8,8,-29,-24,-19,3,7,-6,-13,-26,-4,3,-22,5,-44,-24,-6,50,73,12,-3,22,34,40,3,40,28,43,25,-12,-15,13,20,38,26,-24,-8,6,-29,-32,24,25,73,26,-25,30,35,30,18,16,-10,64,15,7,-33,15,24,23,-32,-34,-33,9,22,-18,-14,-15,27,11,18,-12,-30,49,41,0,-31,-23,20,15,-13,14,-5,22,11,5,-35,0,2,22,9,-5,26,-44,-1,14,0,-20,-24,-6,21,-30,-36,9,8,74,20,5,-43,4,30,45,-16,-23,-12,-32,-32,-24,-79,-39,-11,38,32,-22,-1,-9,-8,12,42,23,24,46,18,-11,5,4,15,26,8,-1,-18,-11,18,5,-13,-2,-10,24,-9,-27,3,4,37,24,-10,-33,0,9,34,9,-22,1,-9,10,-16,24,3,31,34,35,-11,-8,15,35,25,-1,-30,-31,33,1,10,-19,-22,-29,-5,9,-39,30,33,-18,-14,5,23,14,9,6,5,-7,-2,15,-20,22,17,-34,7,4,-5,6,-14,18,14,25,29,26,1,11,19,20,10,-6,-5,-30,14,7,16,-23,-15,2,0,9,-17,-12,28,-5,3,-25,-6,53,-17,-1,-5,22,6,-28,39,20,25,7,-37,18,-6,-14,-14,17,0,14,-4,-32,13,-22,-41,7,-42,-19,-12,-3,17,7,-23,-34,-5,58,54,9,19,48,29,8,13,22,33,21,23,14,-13,-19,14,10,3,-16,6,31,4,-12,-35,22,15,2,15,-17,-4,-8,-8,-22,1,-32,3,-53,-23,-18,33,28,8,2,12,-19,36,27,20,11,-6,-26,9,-12,14,51,-5,43,9,22,-39,-19,-16,4,-1,-21,50,-12,4,18,8,22,30,7,-6,1,-4,-13,-26,19,-8,31,22,11,2,7,1,2,-10,12,3,10,-7,-1,-34,-46,-10,17,26,1,-36,9,17,8,27,38,-16,0,-19,-13,-22,-4,46,27,9,12,21,-13,-1,24,1,-22,-44,-12,48,46,32,-8,-38,8,-4,-21,-8,-12,2,-50,-24,-41,-12,-22,-9,20,-5,-5,44,-16,-14,-10,53,8,31,17,34,-7,23,-11,-17,-18,21,46,26,10,-12,-20,22,26,-27,-3,-46,-6,15,-30,3,-22,-4,11,-27,35,-9,26,54,41,13,-13,44,-6,15,-3,13,43,-22,-15,7,9,0,53,49,14,-16,10,3,-4,-40,-15,-10,10,21,12,-14,15,-4,-7,46,45,22,-31,-14,2,-15,-18,43,-15,-17,-38,0,-18,-1,81,4,2,-1,-33,52,23,8,21,-6,14,-4,-1,-15,6,-4,-41,-14,22,29,18,-11,4,19,-7,25,6,29,-13,-10,-20,3,-19,-15,-41,-9,-4,-13,-33,-4,27,-12,-47,0,22,6,46,},

                    {9,18,-17,-18,1,1,-14,0,27,-3,-18,-17,29,-2,7,34,1,11,-17,28,10,34,-4,-26,-14,22,16,-9,-49,-33,-7,-2,8,-7,0,-17,-23,-21,-40,-10,-15,7,-12,6,-12,11,11,-33,-64,5,-19,-5,15,37,2,17,23,-1,-23,2,25,14,32,-6,29,10,-7,-43,-18,-8,0,-14,0,12,24,10,9,-21,-4,-8,5,3,-19,-16,11,18,15,22,2,43,20,50,22,14,19,-23,-16,4,-62,-28,-10,-24,1,-30,-47,12,-12,-27,-27,-5,-44,30,-9,14,-18,-12,20,-17,21,-9,11,3,-13,-31,25,29,2,-5,-29,-14,11,23,3,-17,4,17,-11,-29,5,8,3,12,0,0,-7,22,-35,12,4,-2,0,3,-10,0,17,-14,-24,2,4,10,16,5,3,-12,19,-3,-9,1,3,-4,13,-11,18,6,13,-7,-27,-12,-20,9,17,-1,26,20,-4,61,-34,48,30,16,-21,-11,0,-6,-40,-11,2,-9,-22,-27,-24,-41,12,28,-28,-35,-14,-6,21,-5,3,-19,-3,0,29,25,-10,8,-25,24,19,3,-30,-10,-13,-16,3,-9,-22,21,13,21,-43,24,21,39,35,-14,-9,-17,-6,53,47,5,-12,-37,21,19,1,-32,-38,-39,-31,-26,-49,7,22,13,-31,-5,-30,-29,37,53,-2,-14,-3,-40,8,51,0,9,-6,-34,1,34,30,5,19,-15,-4,-12,0,-1,32,33,-52,-61,-14,10,9,-4,13,2,11,22,12,15,7,6,12,20,15,-4,32,8,-14,0,26,3,10,-25,9,-52,-12,-7,17,-3,-6,-15,-42,-6,24,31,-23,37,12,4,20,9,-14,56,13,-1,-22,-30,-17,-12,-43,45,19,16,9,-6,-51,-3,45,-24,-27,-22,-23,53,-10,-7,16,-11,26,-5,-17,-9,-7,19,-9,-9,0,1,-17,22,27,-1,-15,-37,-6,-2,15,40,-9,-15,-5,8,21,-13,9,-4,-15,30,24,18,-33,2,3,-29,-48,-78,-25,-11,-56,18,1,34,4,7,-23,-2,-7,7,15,19,-20,12,17,16,7,31,-22,-39,44,9,41,22,-27,-33,-45,-3,21,-33,-44,-39,-17,0,-48,-32,-28,-15,-12,-6,-5,9,28,29,16,17,24,-38,-2,19,-27,-22,42,-16,-18,31,11,7,26,-11,32,7,3,-8,-26,-23,6,-19,-7,5,20,18,16,30,5,-4,-1,9,8,-16,0,-8,-39,-6,9,10,10,2,-11,-12,5,46,10,-16,-17,-9,12,23,19,-28,-21,0,8,22,12,-15,-40,-15,-9,-10,0,19,13,-10,23,13,7,-17,-1,-37,12,11,8,21,0,-13,-11,-13,-6,3,-3,1,3,-25,2,-2,-1,-25,1,24,10,-12,13,-18,10,-52,4,-1,0,30,1,-15,20,24,29,7,0,-24,-31,0,-1,-24,10,-13,6,-12,14,11,9,-18,33,-3,-44,-53,3,-18,-14,-14,-21,15,-9,-3,0,2,1,26,-12,25,19,28,35,15,19,-1,-10,5,15,3,5,9,-24,-35,32,-4,-9,-6,-10,-13,-1,-15,6,-20,-3,10,20,-1,-20,29,8,11,0,23,-17,-4,-3,-17,17,2,2,58,34,-33,0,-6,3,-29,-79,-45,18,-63,-21,-51,-77,-5,24,-24,-7,-43,-30,1,-6,-6,0,-8,19,16,13,6,-17,-17,-22,-22,1,8,17,-15,-8,-14,-3,-11,16,20,-12,-19,-48,2,32,39,0,31,15,-2,29,0,30,9,-11,26,-6,-46,14,15,24,21,-24,-23,-33,1,30,23,-5,-10,-2,-7,-11,40,36,3,-17,-54,-11,28,1,18,32,23,22,-17,-3,5,50,-5,-55,-58,6,-46,-53,-8,21,20,3,72,43,-31,-11,21,-18,-23,-16,-12,9,-31,-6,-1,-51,-19,19,-25,7,-12,8,20,2,-2,31,-8,18,19,6,-39,-23,-5,26,15,-10,26,-4,6,20,24,-5,-24,6,-7,-33,3,-13,-30,-32,-23,-4,-19,18,8,-18,11,-13,-27,9,13,-2,-11,-27,8,11,13,-4,-2,33,20,-4,18,16,5,2,-3,-41,-27,-1,18,1,-9,-55,-13,-8,12,20,-15,-27,-36,-26,20,-9,-16,-32,-22,3,20,-8,-13,-2,3,10,21,21,-20,-16,-9,-6,17,0,-7,-52,-19,32,7,-1,1,-11,-32,35,24,43,41,-40,31,31,15,43,0,-39,-15,17,18,-33,-18,-25,-16,-26,8,-24,36,7,-6,-2,12,6,10,6,23,14,12,-9,11,6,24,-10,-23,-20,-34,18,13,5,-20,-46,-24,-13,-8,-3,-25,-4,13,13,21,10,16,18,-3,9,5,-16,5,-22,-6,-19,-44,-1,2,-11,7,8,24,-23,45,20,7,-5,3,0,0,9,-48,6,1,9,-20,-41,-25,-37,12,15,21,39,28,-38,-6,-9,9,-29,-19,15,-7,2,24,-14,-28,4,-27,-11,23,37,-1,5,-8,6,25,9,-8,16,-12,-14,-1,-37,-14,5,-22,-34,9,30,9,-6,-1,6,3,11,11,11,-13,1,13,20,-23,22,-1,15,56,48,-1,16,-41,10,-40,-52,-61,-1,-14,-17,-65,-63,3,-5,-44,-12,-9,-23,-3,12,53,-10,-28,-42,-27,32,23,0,0,11,8,15,18,15,3,9,23,-10,3,-16,-3,-3,14,6,-18,-30,13,65,3,-4,-46,-55,5,-34,11,-8,15,-11,4,-11,-29,5,-13,-5,31,-5,-1,4,-8,-18,1,4,28,3,-7,6,9,-9,-6,21,-20,-25,18,30,17,-3,-8,-2,6,1,-11,-31,34,-3,18,-4,9,-35,-5,22,-14,-30,-15,6,16,-23,-21,18,-25,1,47,-21,-55,-64,23,31,-1,8,-4,-14,8,-8,11,-5,-20,20,-4,3,9,-17,10,-42,-13,21,0,7,-4,-1,17,-28,46,23,14,22,-48,-8,32,27,-2,38,19,12,4,22,12,27,5,-44,-33,},

                    {3,20,-3,-10,-4,-6,-20,19,-9,32,25,20,35,8,20,30,28,15,-19,9,-22,41,50,-19,-17,26,-6,-1,-34,-34,5,21,-41,-9,-10,-6,-34,-24,51,30,-7,-12,-38,3,34,48,1,-20,0,8,-17,7,26,20,-28,-14,14,9,-3,11,7,-35,15,8,-7,-10,-43,6,-12,41,5,17,4,-7,3,1,-25,1,1,-20,6,19,-11,22,30,-23,32,33,26,18,-37,-8,11,32,25,-24,2,14,1,-32,-12,-25,31,-13,-28,-15,-9,-39,-32,7,-19,-19,30,19,-33,38,11,-28,4,6,25,17,22,9,11,30,-2,9,31,0,23,25,-26,-17,8,-5,-19,-1,-7,-11,-2,18,14,-5,-2,61,14,44,11,-12,0,1,17,25,-26,-26,26,7,13,23,24,0,-9,26,37,-4,17,-1,-4,-19,7,8,31,-4,-12,-28,-22,27,-9,12,2,38,13,8,11,28,-12,0,-9,-35,-36,26,-31,-24,-42,-12,-5,19,-15,13,-36,-42,9,11,-8,-3,-46,-29,19,-1,-7,-36,-12,16,11,5,-34,17,24,7,39,14,6,29,17,7,-6,5,6,-5,17,-22,-24,29,-56,-3,17,-2,-8,-5,-56,9,21,3,1,5,-62,6,20,17,-42,-31,6,-7,-54,-18,55,0,-30,53,15,-50,-11,30,8,30,47,-59,-58,36,26,9,26,-33,-25,14,-45,9,8,-7,20,-11,-19,-26,17,27,-26,-19,7,14,8,-17,0,-7,8,-25,-17,3,7,-9,20,-5,-2,-5,16,-15,-23,-24,-29,-28,-2,14,-37,-15,3,13,-13,-11,8,-42,-48,-15,7,10,-26,22,-12,25,6,2,13,14,2,-7,22,2,-4,27,-42,3,15,-4,-15,-16,-48,-23,-11,-27,-45,20,-41,-16,5,-28,-14,-8,33,-13,-12,-11,0,24,30,38,-8,26,-5,24,16,30,45,57,-46,14,7,10,30,-12,-32,-10,5,-23,19,-10,-37,3,22,-4,-27,-28,4,6,-10,-26,-34,-14,-42,7,9,-7,-5,16,5,-8,-7,-8,-3,1,-7,11,12,-2,29,48,-38,-17,20,-3,36,12,-11,-102,-23,-4,22,-9,20,-64,-42,9,-15,-20,-13,-21,17,-26,8,2,35,15,-34,2,15,22,2,21,7,-7,46,5,21,3,-7,-14,26,0,-23,-26,3,-21,-32,-32,0,16,-32,5,-16,-5,8,11,13,3,-34,21,-16,-14,17,-2,-12,39,49,5,-1,5,30,5,-22,15,15,30,-25,20,-40,6,37,2,-46,6,7,-15,-10,17,-35,-22,49,-26,-17,-25,-16,-21,-14,-50,35,45,-30,-12,-8,24,12,47,18,-20,-33,25,-16,22,30,7,10,-57,6,-7,8,-4,-31,5,3,-10,-14,-28,4,-16,-14,11,6,19,17,-21,-6,-26,46,28,5,1,2,30,50,-18,13,8,10,-24,7,22,-36,4,1,-29,-21,-19,-40,-16,-27,1,-31,0,-6,-3,-29,-23,-5,-7,9,-12,-18,-21,0,20,-5,22,3,-8,6,2,34,44,23,-12,3,18,-56,-15,-17,-19,-7,-8,-26,-30,17,15,2,-25,4,-7,5,5,2,20,6,-1,6,20,27,15,4,-28,-26,-18,21,21,-10,-4,-39,-19,-39,-65,5,-14,-92,-60,-25,-17,-42,-24,-28,-7,-21,-27,18,33,36,-6,33,8,-17,17,17,-2,51,7,-3,-2,15,-34,14,22,-18,7,9,-32,-31,-5,-20,18,32,-12,5,-1,-31,23,31,33,21,10,18,1,2,-25,31,6,-30,50,-27,-57,24,5,2,25,-2,-39,-49,35,6,5,24,-71,21,28,-3,7,15,8,11,-9,-44,5,22,7,-29,-18,2,-1,2,-13,22,24,29,9,-6,-43,3,20,-26,28,-9,-22,-5,3,9,31,-7,-7,4,-31,-20,3,1,4,8,14,-23,-22,5,8,2,-34,-12,-6,28,51,25,12,-1,10,-12,-29,-25,21,-5,7,-15,0,18,-18,-5,4,-13,-15,24,-7,1,-27,-21,-35,4,-4,-47,1,-20,1,3,-10,15,13,48,-14,-18,-7,22,16,12,-22,-25,18,4,29,13,-4,-4,-8,-7,29,10,15,34,-49,-17,-9,6,30,-17,-32,-12,3,1,35,-29,3,18,16,27,18,-6,9,-15,10,3,29,40,37,20,-1,-1,-42,31,9,-13,-2,8,14,2,27,-31,11,36,18,-17,-30,23,-5,8,-25,-9,-18,7,-7,18,-4,47,20,-16,36,-11,2,7,31,-20,9,-16,15,22,-9,19,19,-9,-5,28,10,-30,-11,-42,-16,-4,20,-32,-32,7,5,10,-9,2,33,1,1,11,36,1,-4,-17,11,5,-3,-6,4,1,7,-3,20,-17,1,14,26,10,-2,-50,19,61,-4,-30,9,5,13,-23,-26,-15,-31,2,-10,12,-15,-9,0,-1,14,27,33,11,-9,9,24,-12,-26,41,-2,-10,-50,49,11,23,6,-3,8,17,4,12,4,-1,-27,-35,-14,11,-30,3,16,-1,13,-17,1,5,-34,9,-11,12,-20,11,23,-1,3,46,12,-33,14,15,25,22,-33,-15,9,14,-40,-37,-82,25,-13,-65,-35,18,-50,6,15,18,-23,3,20,-2,-12,-8,-40,-32,15,-16,-5,11,21,-37,10,-37,-16,16,4,2,3,20,-36,-18,17,-9,22,-26,-23,37,-8,-4,4,-1,6,-6,-29,3,22,-40,4,-7,4,-14,-22,30,21,27,36,2,-12,-35,2,17,60,36,21,-69,-22,8,-7,-13,-21,25,-15,13,15,-43,-23,-27,28,3,15,25,24,12,5,0,20,1,27,-31,-46,-68,-34,26,31,-23,-46,-57,-40,2,16,7,17,-67,-38,36,-14,-51,-6,8,24,2,4,9,14,17,-15,33,26,-43,2,-15,-60,27,26,27,3,3,8,-29,48,-8,16,28,-29,2,17,-20,-5,41,0,19,6,-26,11,5,0,-24,-13,},

                    {-21,8,-42,-51,-20,-25,1,-6,-27,15,17,3,14,11,11,-4,-19,-6,16,-1,-16,29,23,41,-28,-48,36,-1,-41,10,-8,-46,9,-3,-14,-10,6,20,-21,-37,-3,1,7,-33,-75,-34,-28,-38,-51,2,-53,-11,-24,-13,36,2,-12,-30,-7,41,44,-44,-39,1,25,-15,38,-57,31,-2,16,-34,11,14,-26,-45,13,-30,2,3,-23,2,-25,21,0,16,-6,-6,-20,38,-9,20,4,-19,18,-23,-27,-17,11,-9,-5,-33,-24,-26,13,-23,-80,-34,-11,-6,-30,-45,-24,-13,24,2,19,73,14,15,14,55,12,-2,0,-8,-7,14,-35,-8,-36,-8,-6,4,-6,-38,8,3,-17,-25,-2,0,29,-2,-18,22,-31,-5,-4,-13,12,-31,-71,-1,-6,-45,-30,27,-46,-19,-17,-5,5,25,-24,-31,-29,-9,-10,-33,-48,4,51,6,24,3,30,2,49,-9,66,-25,-26,-12,-9,16,36,6,-20,11,-1,14,44,17,26,46,-4,4,-18,26,40,27,-28,30,-34,18,14,7,27,35,-14,-19,-10,-33,-49,-17,-2,-27,-30,-41,-30,-25,-18,-7,-50,-53,-27,-28,-6,26,5,19,9,0,-7,43,-14,2,57,33,-25,-31,-10,-5,36,-46,-33,-47,39,9,13,-29,-10,-25,-37,-43,-22,6,-12,-39,-21,14,32,36,22,36,-16,30,17,53,-25,27,-28,10,4,40,-39,4,-34,-55,-15,-18,-17,-35,32,19,-3,-16,45,20,-26,-76,-40,-32,29,8,16,-24,-22,-28,-24,88,61,35,41,40,-45,-22,-24,-31,15,9,-44,-13,-18,21,24,17,-46,-31,-24,-21,-25,-6,35,12,-37,-19,-5,-1,31,9,-25,1,16,-12,12,22,-1,30,41,52,23,24,-3,12,35,8,-28,-1,-1,25,-29,15,-44,-25,13,-38,-54,-21,28,-14,-42,-40,-5,-21,-11,19,-66,9,5,-22,30,-2,-35,-16,20,32,14,3,-35,-44,19,32,-14,-56,-11,33,20,-20,-26,-40,33,18,-39,-70,-4,-2,-33,-63,-30,-28,8,13,25,9,14,4,29,60,65,41,20,31,-33,-17,30,-47,-21,2,-54,-23,10,-55,-82,-14,-40,-61,-30,-5,-15,-60,13,30,-18,-55,-48,-5,36,27,2,-13,-22,-22,32,5,14,23,7,-24,9,8,0,3,33,42,-2,-14,14,12,-15,8,-10,-74,-4,-25,-62,-34,26,-21,15,-11,-10,4,-11,21,-45,-8,-26,-24,-22,-4,-27,-7,-17,-38,11,-2,-42,14,-9,-8,8,-17,11,33,35,-14,0,12,8,39,6,-20,-16,29,16,29,-2,-9,47,2,-31,36,40,-38,36,2,-64,-25,-8,-15,-19,18,-28,-34,-9,-21,0,24,8,1,57,11,11,-26,37,-14,32,32,10,-3,-38,-29,-2,7,3,-9,11,6,27,-14,50,-2,31,33,28,18,6,8,-14,-24,12,41,-49,9,-23,-17,0,52,-36,-24,4,2,-48,-34,40,-8,-18,-37,-20,-24,23,19,12,25,22,17,11,8,46,41,27,7,2,5,-8,-12,-5,35,-22,6,5,-1,19,45,-47,-20,-26,-40,-25,-12,12,36,-17,-32,-17,-15,8,21,5,-7,28,29,15,16,50,24,44,24,2,-16,6,0,9,-4,2,-9,4,13,-9,28,-55,4,9,-34,12,63,-7,-33,-66,-37,-52,-8,16,-18,-41,-11,-46,-28,37,-16,-83,-30,-8,-21,1,-9,18,15,-13,25,-32,34,-20,44,-16,-10,-4,20,23,14,-4,-39,-14,-44,-45,-40,-22,18,5,-22,-35,-63,-59,4,32,-18,23,26,6,44,15,12,-25,44,-1,-7,-22,17,-2,-17,-22,-35,0,-16,50,2,-9,-29,-4,-13,-19,-36,17,-12,36,-4,24,2,-6,50,1,25,22,18,34,-11,-5,26,-4,-17,10,9,0,28,20,23,12,46,-48,-29,-18,-14,-25,-1,21,3,-16,-28,-17,-6,13,29,25,-8,-11,-7,3,3,-4,-6,-23,-14,11,13,37,-3,-21,25,-23,-11,8,-4,-13,16,-22,-23,-25,-20,-28,-69,-8,-2,14,16,-18,1,2,-8,-37,-5,-8,-64,-17,12,-32,-34,12,-28,-8,-9,-16,-20,18,-22,-4,-37,15,-11,22,-66,-2,-33,-10,15,38,-25,1,-6,-16,-24,-13,-9,13,10,-50,9,-13,11,22,-4,2,19,-1,2,29,-29,-89,-30,-38,-17,-28,-46,39,27,17,11,-8,16,3,49,21,1,-5,32,-26,38,-13,-14,14,8,-1,31,19,6,34,-8,2,30,5,44,16,19,35,18,-3,15,-8,2,19,12,27,43,-49,-28,-22,-34,-11,23,0,-1,-19,-27,-17,3,26,27,-49,-32,-46,2,33,10,-26,-11,-7,4,24,-2,-20,-8,-11,6,-21,-18,-6,16,10,-8,-22,-29,2,-4,-51,-20,0,20,23,35,-19,0,-9,-11,-17,-35,19,-24,31,-38,-3,17,-27,-26,9,-7,10,30,-8,19,-5,-12,-46,-23,1,34,8,-2,-29,-38,22,-27,12,1,-26,-39,-18,-34,24,3,12,5,-11,8,40,28,70,37,20,34,-23,-15,-16,24,31,30,-61,-43,-16,2,-7,16,-69,-31,-10,-29,-37,18,-1,-25,-38,-54,-49,-19,-1,0,-3,37,37,-16,33,29,33,17,30,49,-19,-10,-13,-12,0,-1,-10,-10,-16,-81,-48,-20,-9,-21,-53,14,-16,-31,-52,3,-23,-35,-34,-7,18,7,6,31,8,20,24,29,-6,-45,-38,25,-13,2,-40,-32,-33,-40,-30,1,-26,-57,34,2,-54,-54,-5,10,37,10,31,-15,-52,12,-4,16,26,1,-30,-41,-34,-29,-21,29,-33,-3,-6,-35,-39,55,13,-12,-34,15,-30,-56,3,27,13,20,-58,-11,32,-9,-32,-40,-15,-18,-20,-1,-14,24,-17,-29,3,-47,-39,23,21,7,4,-28,-19,64,-1,20,-21,55,29,37,-2,10,-26,-3,7,-46,6,-19,9,12,12,-40,},

                    {8,33,8,-18,8,16,48,2,3,10,-2,15,36,34,30,-4,-3,29,-16,21,26,10,35,-6,-14,-19,32,-7,3,-3,-34,-40,-46,-8,6,17,-34,1,42,21,0,27,-11,41,30,-4,1,-10,9,19,-9,9,-39,-36,-8,16,4,-41,-19,16,-26,-11,-5,30,-14,7,-14,3,3,27,10,11,-7,3,-23,-7,2,38,23,0,10,-18,24,11,30,17,9,5,-13,26,17,9,0,1,10,0,-4,-10,22,-39,20,23,-25,-37,-18,-11,-21,8,14,2,-16,-36,21,-24,18,-13,-37,-32,-24,6,26,14,-1,1,7,28,-2,24,15,-32,-12,14,6,10,10,-8,20,11,-12,-20,13,-1,5,-7,-8,7,15,37,-26,-6,3,15,29,8,-20,-26,20,29,3,9,-6,-33,4,23,7,-2,-6,19,6,8,-10,23,21,-18,-23,-16,21,22,21,-13,14,25,-5,2,19,30,-14,-7,-22,-5,-6,59,-8,-47,2,-13,-9,30,3,3,7,5,-5,-1,-11,13,-18,-5,-2,-27,-16,3,16,-5,10,7,-4,10,7,30,26,10,23,42,23,9,-23,-10,26,33,12,19,-1,7,-1,1,-8,-21,10,3,18,-4,0,-16,2,18,-31,-7,-19,27,6,13,18,16,-32,-12,52,17,11,3,-23,-48,-26,22,47,50,3,-18,9,26,14,19,17,-18,19,4,15,2,10,-15,25,-11,-26,-12,9,22,-9,21,-29,-38,-18,-3,-7,-1,15,5,8,-22,2,9,27,6,-14,0,46,38,-4,-21,4,6,44,12,-18,26,-5,-10,-17,0,-71,-35,4,11,18,-22,-53,-30,-71,23,22,38,-1,-11,-36,-15,1,44,-15,-24,-9,-25,24,-21,34,6,-27,0,-16,13,19,16,35,31,-7,0,-31,-21,22,-18,-9,13,-16,0,27,1,12,59,2,8,1,18,62,44,-11,31,35,-4,-13,-16,11,17,-4,-42,-33,9,-4,-7,-4,-15,-18,10,-22,0,9,-26,-28,-16,-8,1,-37,-42,0,-14,3,17,5,-11,-15,-10,-17,-8,-33,-11,18,-5,-24,1,-8,-28,-11,1,16,-5,12,-22,-43,-7,-33,-20,-7,6,-31,22,-18,-44,-25,-31,8,0,13,-5,-12,-30,9,55,29,13,15,-3,-19,26,40,11,12,54,35,-6,-15,14,13,-2,11,-4,14,-48,-32,-19,3,4,-4,-9,40,-1,26,43,-3,5,5,10,21,24,34,52,31,-5,15,-3,27,22,18,-2,-7,14,9,-12,-29,-9,3,-20,8,9,-22,7,24,16,0,-29,-2,2,-20,-20,-28,-24,4,37,12,-23,0,3,24,38,-12,-39,-15,37,56,13,-8,-6,-10,14,10,-14,4,-10,-17,-23,-7,-9,7,-31,-45,-43,-55,-23,-13,22,-11,-57,0,-28,26,38,24,-9,-9,1,15,0,30,18,-19,-2,-8,9,17,6,10,7,20,2,-45,-26,-10,27,4,6,-19,-46,-63,-55,-27,-2,0,-26,2,-23,12,55,21,3,-2,-2,2,34,36,32,6,-1,3,-1,32,28,21,-15,-21,-45,-4,-1,10,9,25,12,14,7,-2,-27,6,32,21,-2,9,13,18,49,-24,-65,-31,11,38,79,-8,-49,-21,-31,7,-5,42,10,-24,7,9,-34,17,22,-11,-28,-20,-27,24,17,16,33,3,20,29,22,17,13,5,-11,18,38,-9,28,-14,-25,17,30,-35,6,-11,-1,-18,-19,-30,9,5,7,-56,-6,23,14,42,-20,46,15,4,-29,21,23,13,40,-54,-24,3,-12,37,37,-11,-5,11,3,14,28,3,-6,8,2,-5,-9,10,26,-27,36,19,-21,19,18,7,4,-3,-30,-64,8,-5,15,-30,-8,-1,6,44,35,-47,-20,2,-46,31,52,41,24,39,6,-16,-17,5,-1,-5,-44,2,-13,-5,-7,-2,1,-11,-5,-19,-5,17,8,40,33,-5,-4,-6,-4,8,44,-8,14,3,0,-15,-4,-14,31,17,7,12,1,18,-9,-18,-11,15,0,-10,-11,-16,-12,2,-2,3,-16,29,7,9,-5,3,8,8,-19,-6,-20,22,10,15,16,11,20,-2,37,13,-2,24,6,-4,14,-4,2,-10,25,-4,-14,1,32,22,-12,21,17,14,46,9,6,9,-5,-6,52,44,14,39,19,41,-1,-15,-18,19,26,-10,-24,-7,-30,16,-25,-37,-18,-36,5,-19,-6,-24,33,-10,-3,-5,-1,-30,-17,60,28,-21,0,-11,-18,-13,60,7,-28,-36,-32,29,42,25,2,11,25,16,25,1,14,21,7,5,-26,3,13,-2,3,19,4,9,-11,10,2,16,55,7,-8,-14,-17,16,27,12,29,7,-2,-1,-29,52,6,-25,1,19,0,6,-6,-6,-11,5,9,-12,-27,-25,-3,-9,8,-11,0,40,-16,-20,16,7,-19,16,45,-18,-22,-22,26,46,-17,-13,-14,-14,23,26,-16,-10,15,25,39,6,30,15,7,-18,-9,-24,-19,27,-26,-53,1,-18,-10,-3,-6,21,14,15,-7,22,49,30,16,-11,43,46,44,13,-25,-31,24,10,-14,-2,-21,-8,4,6,-21,-60,-21,-36,-10,13,-23,2,61,14,-8,-2,1,1,-9,-30,-11,-42,-20,-57,26,34,-19,-9,-11,-48,-1,29,-70,24,-3,33,-14,-5,4,4,27,-29,-60,8,11,-3,31,14,8,-21,-4,5,3,-8,-3,-35,-29,-48,23,25,38,27,-6,20,7,16,10,20,-15,-25,10,11,16,20,-27,22,29,-32,-26,-5,15,29,-11,-14,-25,-19,8,50,56,1,3,22,52,47,54,-16,-75,-12,-7,-26,-27,0,-56,-13,-9,-18,-20,-44,11,-59,-17,17,7,-15,-16,-5,0,14,4,23,7,-17,29,39,-15,4,10,-10,15,0,11,32,40,-2,-20,-16,25,22,5,11,-1,-14,-11,8,-8,0,42,6,7,-25,0,2,24,3,1,},

                    {32,19,13,-34,-48,-25,15,21,-26,-8,-16,-10,-12,-41,-17,39,48,35,11,-32,-38,4,1,-11,-1,-5,-1,-6,-9,-45,-17,-4,-2,1,-24,-24,-25,55,60,-10,-33,-71,23,52,66,18,-26,-4,-53,61,80,28,2,23,26,55,26,23,21,23,14,53,-10,-33,-11,15,-13,-23,-3,13,-6,5,14,20,-1,-32,-69,-10,29,-3,-39,-14,23,7,33,-48,-43,25,54,2,-2,-21,28,-5,2,22,-7,-29,-4,-13,-6,6,-5,-14,19,-4,-10,-27,36,0,-12,-21,-21,-3,24,13,-20,30,-4,21,27,-2,-3,-17,-28,15,-1,-4,-41,1,-2,3,-20,-2,-4,12,9,-2,11,-16,5,-21,25,-5,-14,73,56,37,-16,-48,-7,38,57,42,-16,-23,-25,35,33,6,-5,13,17,38,15,0,-19,31,30,25,2,-4,-7,17,10,-7,32,7,-4,29,6,11,-16,11,33,16,2,-8,-49,-42,-34,-50,-3,-15,-15,-2,0,-53,28,17,7,10,4,14,2,3,-13,-7,9,-6,-20,-21,-21,-19,-6,-1,30,55,67,39,-24,-53,48,42,29,10,5,-34,43,31,47,-3,-10,17,12,18,15,-18,-6,43,16,-11,11,-1,-17,12,-12,-56,6,16,-21,15,16,24,-4,-37,-30,-12,33,43,12,-8,-46,-19,16,4,15,-45,-12,6,11,2,2,-5,-29,18,-25,-6,4,-3,-9,-3,10,-12,-6,-25,11,-6,14,-37,-27,-1,-28,4,-3,-25,-2,-26,-28,-9,5,20,-8,19,69,45,-21,-50,-68,-32,0,26,-34,-26,-15,-15,9,-40,24,-9,5,-20,-27,-19,11,-15,35,-22,-17,2,7,-10,-45,-58,-49,-44,-28,-7,-22,-17,4,-23,8,5,30,56,16,37,3,-4,-12,25,-17,-3,-28,15,-8,6,-8,-18,5,40,39,-5,-79,-29,14,15,15,-3,29,28,15,-15,14,23,65,4,15,17,20,49,-18,35,1,-10,46,26,17,28,-24,-23,5,22,-9,3,37,28,10,-48,-87,-59,24,30,6,-43,-13,-22,50,28,2,-23,45,57,-28,-26,-52,-43,-21,2,5,-36,0,-25,-18,-22,8,-5,-31,-29,-19,-12,15,-8,13,-37,-20,-21,35,4,-60,-43,-4,-28,5,16,-23,-20,52,47,41,-19,-19,-11,39,6,0,-23,-32,-4,-3,9,11,-23,-17,-14,-7,-7,31,45,17,-30,-30,-22,42,9,42,12,9,-6,16,0,11,16,16,15,12,18,-10,19,-13,66,14,-29,4,12,-5,5,7,-32,6,11,7,16,24,-19,2,-14,-8,-21,-8,1,33,50,-32,-13,-4,31,33,41,-9,19,-12,54,0,-23,-5,16,-6,-5,-27,-1,-9,33,41,-37,-2,4,14,-2,51,-16,15,35,-31,-14,-2,5,-8,16,-34,-14,-5,23,-15,5,34,25,-26,0,-26,-10,21,27,-7,-8,-32,3,-25,9,2,-11,13,-23,16,2,33,8,1,5,19,12,20,9,-18,-48,-27,-48,5,7,-12,-24,15,14,-24,-33,-20,-25,6,-3,-26,-25,-16,-8,-8,-21,-5,-5,-14,-20,6,-9,15,16,-9,-67,-48,-23,28,-19,-29,9,81,59,-2,-36,-52,6,61,44,17,-9,-1,-24,-46,-70,3,-22,-10,-2,-1,-40,-35,-6,-12,3,14,-24,36,34,-13,-26,-2,-71,28,21,51,47,-6,-17,10,17,50,55,-30,-5,-23,11,26,48,-2,35,-23,22,19,14,8,11,-28,7,-2,20,-6,-30,30,27,27,22,1,-19,37,41,-8,-23,-75,10,3,22,0,-16,-12,22,19,-3,10,-1,27,9,14,-3,-27,19,4,-26,-22,0,-17,0,1,3,-17,15,63,47,0,-7,-1,29,-22,-61,-17,37,-1,-19,-5,-14,4,-20,3,-15,-14,-35,-18,-15,20,-19,-8,4,-13,6,-25,-11,-38,-2,-6,-30,7,25,2,2,-6,-4,-3,-3,-21,-55,-34,-70,3,12,10,12,6,1,28,14,6,18,28,-5,24,4,-48,-4,7,13,-1,-17,6,-12,-13,6,12,-14,54,-19,-25,-13,23,41,35,3,-33,21,4,28,18,10,4,25,-13,42,-5,0,19,18,-8,-9,-5,0,-6,8,-7,-10,13,35,-13,-2,62,29,11,-20,-34,-19,31,17,11,29,29,-3,15,-15,21,35,67,17,8,-10,-20,25,15,10,-14,-45,24,8,23,-32,-6,4,27,18,21,0,16,26,-14,-54,20,-10,-15,-10,-30,-54,-57,-34,-8,-6,-18,-15,12,-18,1,-13,-7,-2,22,-20,-3,-10,-7,7,-24,-45,-46,-32,-20,-15,-1,-19,12,0,-29,-31,-34,3,27,1,-43,-32,-4,-2,26,-26,-11,-9,47,16,31,-20,-13,40,4,32,-8,-8,33,0,4,-6,-17,2,-4,20,31,-15,-9,37,62,3,1,-19,10,47,59,41,-31,-10,13,10,24,-21,-23,14,20,-12,3,-16,-4,-10,6,-4,-7,27,8,-12,-2,-17,-27,11,-32,-21,6,28,-26,-59,-72,-21,-2,-46,-37,-36,3,15,20,-2,-7,57,105,58,-45,9,-4,-10,-26,-32,-16,-4,4,6,-1,-12,-13,-15,-5,-34,-13,18,30,40,41,-19,-57,-72,24,23,90,-2,-28,-20,30,15,11,-34,2,36,-18,-4,-16,-33,-24,-1,-38,1,-12,-25,-22,3,-3,-17,2,-20,-22,35,28,9,-7,-39,-40,4,27,12,5,31,11,13,41,2,-15,5,15,17,-16,-34,-40,29,9,-1,2,-35,-6,19,31,9,-30,-43,21,-40,-22,-14,18,3,-40,22,-24,-41,-1,-5,9,16,-17,-57,-70,-5,35,19,-7,8,37,69,48,-22,18,28,38,48,7,-8,10,-1,-20,-11,-11,-11,-31,-14,28,53,21,-12,-6,-15,38,4,17,-33,-55,-43,20,14,3,-22,-30,40,14,24,24,40,-29,13,4,12,1,17,2,-1,-7,-7,12,15,-23,7,},

                    {10,-2,21,45,-3,12,-6,16,17,-17,1,-23,-13,-4,0,-23,-4,-5,-29,-28,10,-16,-14,-33,-29,0,-12,3,-5,11,16,21,39,29,0,-42,0,49,17,76,29,1,5,-10,-21,0,-3,-7,42,-13,-32,-7,-37,-58,-38,-87,-58,0,-11,-26,-31,-41,-45,16,10,3,-30,-7,-18,26,27,19,5,-1,27,7,-8,4,15,39,2,-4,8,-46,10,-22,9,35,8,-5,-32,-49,-13,-2,-9,-18,-35,-28,19,4,50,33,8,49,65,48,32,42,49,12,14,-17,21,-13,-19,14,-22,-32,6,11,-19,10,16,29,7,-15,-2,30,2,16,31,-6,-22,4,10,10,20,15,26,-22,-9,-5,9,2,-8,19,4,51,16,38,-37,-12,0,2,-5,-8,-20,-17,-16,-8,-23,-42,22,-42,-36,10,-4,-12,-14,-55,-14,1,7,8,-5,12,-19,14,27,28,-28,-8,-14,-26,18,31,-24,9,2,14,26,27,-25,0,20,36,41,3,9,5,32,6,-25,-45,-10,-4,35,-5,-27,-46,-15,20,19,14,31,8,16,-8,9,-3,-44,-37,41,18,-3,36,-19,-41,6,0,-32,5,-44,-35,-13,-58,-15,22,20,-18,4,-49,-18,11,-1,35,18,-8,-17,-14,15,20,38,6,3,-18,-1,-6,6,3,-32,-33,-8,-31,3,-6,2,-30,-17,-19,-4,13,27,52,1,0,-22,-3,9,28,19,4,-17,-2,-15,-29,-28,-15,-5,-6,41,46,24,36,31,11,12,12,21,-2,-11,-33,-33,9,10,14,-7,-11,-8,37,42,14,1,30,-6,-28,-26,-3,26,46,11,-1,4,-40,18,-67,-18,23,15,35,8,16,-13,-6,-13,-19,34,21,34,-38,-15,-13,12,22,12,-27,-17,-40,1,-1,31,-2,-11,8,-7,-6,6,-9,5,8,12,-5,31,37,27,-10,16,18,-18,-20,-26,-57,-2,-4,8,12,-64,-78,1,-43,-18,-13,-53,-19,-40,-47,-33,11,3,2,5,14,36,41,50,13,13,-7,-7,-21,4,1,-1,-25,15,-7,-5,-7,-48,-92,-20,9,16,-11,4,30,-19,5,37,7,41,20,13,16,18,15,50,57,37,18,-50,-21,-11,-45,8,26,26,3,-23,0,21,-4,-6,6,-16,-4,5,63,-8,-2,-2,-40,-12,45,-23,-82,-45,-7,-14,-10,-7,-1,1,37,36,30,8,-24,-6,-18,24,23,49,-34,9,2,1,11,4,-39,1,-3,10,27,-40,-31,-37,-53,-14,-11,2,5,-14,-35,-31,18,-8,-4,19,-34,17,-12,16,11,25,2,27,45,29,40,-15,-14,-28,-16,-15,0,1,0,-25,-9,-26,-30,15,-18,20,-11,-9,-15,9,-32,-19,9,-7,-7,-3,7,-23,25,34,40,8,6,4,21,19,15,34,15,1,9,21,-18,20,4,-26,-8,31,-4,-17,22,21,31,-28,-44,0,1,-21,21,-6,-3,-21,15,-13,-17,22,5,-13,-32,-18,-21,16,18,4,7,9,-8,29,4,-7,6,10,-10,20,9,0,39,30,19,2,-51,10,5,11,19,6,-45,10,17,7,-10,4,-14,-8,-13,3,13,10,-40,1,-14,3,40,5,-1,6,-5,-27,31,89,7,-2,-3,24,-13,11,35,11,51,80,30,-15,-61,2,42,66,39,-6,-24,5,25,46,21,69,36,13,5,19,-14,-5,-10,-1,16,11,-85,-44,-17,-51,9,24,-28,-15,-12,-47,-38,12,-8,20,22,-9,-17,-17,11,19,24,25,53,30,-7,-8,1,-2,-14,14,4,-53,0,-13,10,27,-45,-18,-35,-56,12,35,30,4,-2,-52,-22,-24,2,1,6,-18,23,-41,-23,-9,-1,-9,1,7,-20,19,41,-26,-29,-16,34,44,20,1,18,-8,-7,20,38,11,26,24,29,-11,-4,-2,10,1,-11,-47,-58,-13,6,12,2,-34,-3,-11,-27,41,55,56,46,15,21,22,22,4,23,0,7,-9,22,0,12,13,-14,36,44,-35,-27,-13,-44,-1,-14,10,-7,2,-17,5,24,20,6,4,3,-23,24,57,13,-5,-2,-14,-30,11,-28,3,-21,-21,-17,-3,30,12,-38,-2,7,-18,24,-2,-25,-23,-21,-1,21,-3,-34,-6,7,15,30,-1,-7,36,62,10,-9,5,-6,-3,0,-61,-54,-11,5,15,32,-46,-8,-86,-39,-16,25,-35,-24,-14,-29,-18,-25,-3,21,15,-31,12,-6,24,22,1,0,21,-12,-24,52,3,30,11,9,40,16,-13,-18,12,2,21,14,-11,3,19,21,2,-35,-21,-5,27,6,1,-76,-13,14,12,6,-18,-26,4,8,41,21,17,26,20,13,14,-9,-3,-3,31,-3,9,34,10,-8,-19,-90,-46,4,22,-7,-34,-12,-38,12,24,25,4,-25,27,49,58,6,-2,-19,-12,-10,40,29,-14,-6,19,22,4,-22,-19,-8,-26,53,-11,-15,3,-4,-36,-3,-19,-3,21,4,-29,25,-8,-12,9,12,28,7,3,21,13,18,33,10,1,-2,5,13,19,19,-10,50,-20,-34,-47,0,15,-16,-39,-83,-24,-13,15,-11,5,7,20,6,-6,6,23,74,63,36,23,-16,9,21,25,-20,22,-11,-9,-24,-19,-40,-58,-34,-31,-12,-10,-12,-7,-33,15,13,55,18,25,12,41,0,8,26,36,4,15,36,-11,-41,19,-4,39,8,26,-8,16,-23,-40,18,6,-21,-3,33,-29,17,22,59,50,-17,2,18,2,-2,-13,-11,-6,10,8,12,-16,-7,47,16,-27,-10,6,-2,-8,0,4,1,72,36,16,-2,12,30,84,23,-20,-33,-16,13,24,-10,31,-39,-29,7,-26,-34,18,0,6,-10,2,-9,-5,-16,-31,10,21,12,19,-7,7,-20,12,13,2,22,35,26,-20,31,-17,10,38,-57,-13,-24,-23,-4,18,14,-15,-25,-49,-5,-7,-3,-1,5,9,-21,-18,-43,6,-13,},

                    {17,12,-3,-2,2,-8,25,-26,-6,2,11,-11,37,-18,-40,1,-33,-17,-23,-37,-21,-30,-54,-13,-28,-2,15,-35,19,-24,-9,-54,-2,-2,21,0,9,35,2,-5,-23,4,44,-9,25,-23,-10,12,-23,7,21,6,-16,-4,29,51,12,-35,7,18,25,12,-17,-8,1,19,-10,19,-24,47,6,-2,5,3,7,0,10,-24,27,-1,14,-6,5,-8,21,-9,-72,-13,-15,-48,7,-65,-21,-22,-39,15,-42,2,-14,-20,-1,-5,-1,-23,7,-2,30,-10,24,0,2,-9,10,-31,18,-9,-12,5,13,1,45,-2,13,15,-7,15,17,-12,-22,16,4,-11,-4,23,-6,-13,-8,19,1,28,-1,-4,-3,-3,13,52,8,0,-24,29,22,-29,9,0,-3,20,8,-13,26,5,-52,5,3,44,8,0,12,11,12,-11,-40,5,23,0,-9,27,-42,20,33,21,-22,8,16,6,23,32,-10,-51,-78,52,12,2,9,-11,-19,25,-6,-17,1,-38,-17,7,-13,-55,-20,5,-33,-36,-32,2,-6,0,5,-7,-16,-15,20,26,33,-55,31,-30,23,10,18,-16,-7,-29,12,25,42,-13,-3,3,64,48,16,-10,30,39,22,18,-14,19,13,18,-3,-10,-41,8,-2,2,10,19,17,-35,-37,20,6,5,7,-30,-38,-16,22,10,-6,0,-4,28,-3,45,30,5,20,-16,5,23,0,-16,69,33,-3,19,6,-26,20,24,35,-25,1,23,26,5,-6,-20,-4,-20,0,9,23,38,44,22,19,29,24,-59,-10,0,19,-6,-18,15,-36,-9,-13,-44,-51,-9,21,6,-10,-34,9,-11,22,-9,-4,-7,-10,-29,-52,-32,5,0,5,-40,2,16,-6,-22,-1,-11,-7,-21,-50,3,8,1,-5,0,18,16,-20,-11,-13,2,-21,-22,16,2,35,-21,-27,-12,0,-25,-4,22,-14,3,8,9,19,-4,-33,-29,40,-20,-67,-6,-16,18,-6,-30,-85,12,14,-25,-2,-39,-58,61,-3,-17,-30,0,-32,9,32,-27,18,13,37,9,3,-8,58,28,16,40,15,11,4,-6,-11,1,-8,-22,19,13,12,-15,-17,-24,-10,12,35,-9,-39,-30,-9,10,-24,8,4,-14,21,-3,-24,29,-2,-36,62,14,-28,-1,11,-43,36,10,-56,35,-41,-17,-7,38,-23,-34,12,-4,-6,-35,-4,7,-4,-8,11,14,31,-17,23,12,-6,13,32,-27,-25,7,2,38,32,-21,-9,-11,35,-1,-2,-11,26,16,43,-7,-50,3,23,-10,-3,-13,-16,10,8,26,-19,-24,6,6,-19,26,-15,21,-29,2,-38,22,24,4,22,6,-63,0,-21,35,51,-12,5,10,-39,6,-5,-18,13,1,-17,-18,-8,-10,3,9,5,-40,-28,-48,-10,12,-21,-14,-13,42,26,-6,26,12,33,41,14,-28,-4,20,-36,-20,9,-53,-16,32,-8,19,-8,6,-35,-5,12,-18,-12,-38,4,-21,-15,-33,-7,1,-22,-25,-35,0,28,20,40,-20,6,42,37,8,6,-26,-38,-10,-6,-31,2,7,2,-10,0,-23,3,-9,0,-17,-21,-28,-25,0,-21,-8,4,-10,30,16,-5,37,16,16,1,-34,-60,8,51,63,-13,-29,-4,32,82,-11,-28,-34,-3,21,2,-63,7,23,-17,-13,-28,-3,-10,38,-6,11,-34,6,3,22,-7,-46,-39,8,26,28,-2,33,-50,12,21,23,38,82,43,25,-11,-10,3,26,26,17,-52,-21,9,-21,40,-8,23,43,-11,-5,14,13,-15,3,1,-41,-5,-14,23,22,15,32,17,-20,19,29,30,13,21,7,8,0,-1,32,4,-26,11,-9,2,-30,27,4,6,-16,-4,-24,4,8,-19,-42,13,39,49,4,-7,-33,38,43,42,11,19,-22,28,-13,-6,-22,-1,-1,-6,4,-14,-6,-3,9,-9,14,-21,-26,13,13,41,28,25,7,1,-60,-9,40,-15,-17,24,25,-10,6,-22,-4,20,15,-40,-14,-59,-62,-3,-19,-25,-36,0,14,-3,-16,-3,10,-7,-16,2,-11,36,-10,-8,6,7,-11,17,-22,-25,-3,20,24,54,-15,16,15,-3,5,2,-6,28,30,-13,-12,3,24,22,-7,-14,-6,-17,-8,11,-28,47,12,5,-11,22,-23,2,-4,40,4,4,-15,23,17,46,11,-1,-34,41,-22,-40,10,-11,-13,0,-43,-41,6,32,-18,-36,-64,-2,45,-16,-12,-21,7,-5,22,38,2,-2,-47,-35,-4,16,42,12,-10,-34,47,24,7,22,-33,-28,25,-1,-23,-10,-6,-7,-40,10,-29,1,-9,-2,16,-15,-49,-7,-9,41,0,22,-13,10,4,-3,-3,-19,20,46,29,-47,-33,-12,-14,10,-33,-78,-24,9,-3,-4,-14,-40,-15,21,-14,-9,-28,-9,6,28,3,-11,39,44,1,-3,-7,7,11,10,70,-20,-13,16,-22,39,16,-75,-2,15,35,-6,-16,-13,7,-2,4,-27,-12,25,25,-2,5,-48,-6,27,40,-10,-24,-11,1,13,-13,24,5,-14,29,1,17,29,8,-1,22,13,0,-17,-53,-71,-13,14,-26,-18,2,-22,-8,18,-47,-67,-44,4,20,38,25,-4,16,33,-9,-13,-3,24,18,52,-28,-10,7,-1,19,19,-31,-9,-13,-2,4,46,-8,26,21,-17,-7,18,-14,-6,-1,6,-19,-16,-10,-11,1,14,-23,-21,-2,17,16,12,22,4,21,-29,22,54,-3,12,11,-30,26,5,-6,-19,-10,-30,-27,-1,-2,-11,-15,-35,-32,-22,4,-19,-30,33,-19,-20,-1,17,-7,18,45,14,5,-7,48,19,-14,-4,-53,-41,-1,-35,-14,7,8,36,-25,-60,-23,-26,5,17,-32,28,17,-17,0,-32,12,6,-9,4,5,16,-49,-9,-9,0,-25,40,-21,-13,-25,16,22,26,-31,-10,14,36,11,16,25,32,-13,36,-4,-43,18,-1,-16,21,4,-28,-11,-1,-5,},

                    {-1,32,5,-1,-2,38,1,-8,-32,28,17,50,8,14,28,-11,1,19,23,-33,-18,35,47,39,-15,-14,-38,-31,-10,-2,-9,-6,-56,10,-33,22,23,-67,15,-6,12,9,-5,-17,10,28,36,35,-30,-22,25,17,9,8,34,24,24,-12,-12,2,56,-8,46,-7,-3,-23,-30,28,35,7,32,-31,-3,-5,-27,-15,27,32,-5,-23,-19,11,11,45,21,-24,25,-36,21,8,7,-1,11,-1,-10,-13,25,6,14,-30,-52,-51,31,-12,-37,-45,-12,-21,-4,19,-34,-4,11,12,22,8,9,30,-13,-1,49,15,34,-35,-43,-18,-16,7,42,8,-23,21,-24,-18,-31,-26,-14,-1,11,-58,-6,-3,32,-1,5,-3,36,-16,-5,1,-3,27,47,12,37,1,9,-13,21,4,14,4,12,14,38,-25,11,-2,26,-33,23,26,18,-5,15,17,35,24,24,-7,28,11,-14,20,18,-14,-24,-7,-12,-20,-17,12,4,7,-4,19,-2,13,2,22,2,-8,38,41,3,63,-9,-17,-13,13,6,-30,-25,5,-19,-21,-24,3,25,24,49,53,-19,-2,19,29,-8,85,-17,-11,35,-8,39,53,-38,11,16,6,26,33,-10,-26,6,12,54,-30,-53,-17,15,35,21,-10,-10,-14,-17,4,52,5,14,28,46,-2,-12,43,27,31,47,7,16,36,16,0,32,10,-32,-19,-33,-4,-16,3,-28,-14,16,-35,9,-3,35,-3,-8,22,-10,-34,2,17,-16,-12,-12,-4,-29,-10,35,52,-5,1,-4,-15,-3,22,13,-3,15,5,23,-27,-21,-5,-27,-38,-26,-56,-24,-23,-3,15,16,-27,-53,21,-3,9,-18,-5,-6,-22,-3,28,-18,23,-27,14,15,32,10,7,13,21,3,9,-20,7,-28,-2,1,-29,-8,-14,43,47,7,-21,14,28,-8,16,24,64,-53,-27,-4,28,45,88,-6,-17,-13,-12,29,62,4,2,-35,-22,30,-1,-29,38,23,-17,13,-69,38,4,31,26,-4,-16,1,43,19,-17,-2,20,31,29,3,-13,-10,-30,53,76,23,-27,-8,-23,10,8,39,-11,-30,-11,-11,-61,-4,-51,-1,25,-17,-111,-56,22,9,-7,41,-3,8,-4,10,20,48,-17,-25,-12,2,13,42,29,31,-10,18,53,37,-19,3,10,58,68,-16,2,-4,-29,-10,-28,22,-4,-41,-5,-22,-2,-27,-10,-20,-13,-18,6,-19,-6,6,31,8,65,-4,-7,-7,0,14,74,-15,20,-22,12,5,20,-2,-44,12,23,21,-21,20,-28,7,37,12,-2,18,-19,-17,-35,2,3,0,8,33,24,31,27,23,18,3,15,20,5,3,19,-18,38,31,27,5,-18,-30,1,7,21,-25,-52,4,9,22,-18,4,-24,-4,-11,50,-21,-11,2,4,0,8,60,17,16,23,41,-9,-11,28,19,18,4,37,66,-26,-58,-22,-18,-8,32,-18,-30,16,27,34,-20,0,-38,-31,-33,-20,0,8,12,13,-9,3,-2,28,27,6,7,8,13,54,32,30,20,12,12,-32,6,6,-17,-18,22,-22,-48,-11,-21,-1,9,-8,10,-4,-17,10,49,34,24,20,0,26,17,-5,-6,20,18,2,4,26,45,22,-3,-70,20,41,30,-5,-43,22,47,-22,-42,-84,-66,-35,-9,8,-9,0,-17,6,-6,-2,-1,41,29,46,-5,-10,-25,35,29,46,13,-8,-15,7,33,6,15,3,-33,21,36,-13,23,-40,-27,42,57,33,-8,7,2,14,-18,19,-10,19,12,27,9,28,-5,20,4,23,26,-33,-5,8,-21,19,-31,51,38,-16,-21,-5,10,9,20,-21,-15,4,26,31,11,2,-22,54,16,-35,4,10,31,9,5,0,19,12,-9,8,24,11,18,50,35,25,17,5,-12,14,13,-21,13,22,0,-2,-33,-30,-20,3,-12,19,31,-23,18,-2,43,-8,-12,-23,-21,12,27,7,-2,33,12,1,21,-2,10,-15,-50,40,12,-5,23,-30,-37,-6,3,-48,18,-11,-28,-25,-32,4,19,-33,-24,-30,-8,-14,35,-1,-1,-3,54,-16,40,26,16,-22,20,-7,50,-17,9,24,15,-11,-27,3,5,-14,-29,6,35,22,22,7,-14,-33,-14,-14,-9,4,57,20,-5,-12,24,38,76,3,-11,-2,-35,11,69,-31,-12,-53,-7,76,-7,-34,-27,9,15,25,-24,20,10,22,23,-14,-11,-14,-22,-15,10,-4,-16,-28,24,0,3,-50,27,28,29,-10,7,30,22,47,17,10,3,28,25,6,41,-1,2,7,-6,-12,-35,-37,-16,0,9,-14,-2,-6,-32,10,28,1,-8,-14,11,-4,21,-9,10,-8,-21,-22,18,36,26,-6,-19,-10,-28,-34,-5,20,-1,-39,-44,16,25,5,-31,-44,-38,16,10,-1,19,-2,-20,5,16,39,13,20,10,21,4,50,-3,18,8,0,-37,29,6,3,22,9,10,-3,25,-6,31,5,-5,-28,-3,-2,-25,7,-25,-32,-23,11,14,19,-29,-11,-19,31,-3,37,50,53,20,43,22,-1,36,17,31,9,-15,5,0,0,-27,-17,-18,-4,-47,-36,-55,-55,-46,6,-1,-5,-5,-2,-5,31,58,37,53,-5,0,32,13,22,12,0,19,-8,-19,-9,1,-9,-24,4,-45,-20,-38,-15,-14,-14,-92,-27,46,22,6,-22,25,-3,-20,35,-17,22,24,-2,34,5,18,61,36,-17,-28,-25,17,-13,-4,18,27,25,23,-41,-4,-21,-23,15,-4,-17,-88,64,8,26,-11,-9,-10,2,13,9,-3,9,-11,-33,-28,11,41,-31,-19,-9,-9,-17,17,2,15,5,-29,-16,20,46,18,-10,-37,-12,14,-40,5,15,15,13,-4,-16,-2,10,13,36,-5,-7,1,10,4,11,2,2,-15,22,53,9,23,-9,-1,-3,-1,27,-37,-20,-10,-4,18,15,-7,10,-20,26,48,19,12,},

                    {4,19,-10,10,6,4,1,19,22,15,5,-26,1,-1,-12,2,-42,-7,10,-1,50,-34,-8,19,28,-9,17,-17,-8,50,-6,-18,-39,20,-10,25,35,-13,-45,-11,20,-4,22,-4,-43,-8,-3,1,-31,-18,-38,7,-17,-7,56,-24,20,35,-29,-14,44,-8,36,-1,-34,17,28,4,-4,-7,-26,9,7,47,28,-12,41,4,16,22,9,20,11,7,-26,-22,-37,-19,-15,29,20,63,39,-26,-1,-42,8,30,-14,-19,-5,20,6,-26,-45,-45,-40,-22,17,16,-18,2,-34,-11,9,-22,31,17,-17,7,29,15,25,-24,-33,2,10,-10,-36,-21,-4,-10,-11,-3,-15,-17,21,10,24,24,12,20,-12,9,17,5,-11,41,25,-17,-9,-10,-6,-25,-2,2,-20,26,-8,17,-4,2,23,-6,21,32,-7,-28,-3,-7,78,-8,-36,13,30,24,26,-19,-31,10,49,-15,40,22,25,13,-4,-17,-3,34,10,-51,-3,-2,21,-22,-32,15,-2,-23,11,-3,2,41,18,-11,1,7,-14,-13,14,19,28,16,-11,34,19,-34,-24,7,19,-21,17,-28,-13,-17,-17,-11,8,18,1,37,5,7,-16,-26,-25,39,-7,2,-6,4,36,-10,-14,-1,-19,1,30,6,21,18,1,-22,-36,-37,23,-14,-8,-19,4,-4,13,5,33,19,13,-29,-8,-8,4,-21,-22,-28,8,-10,2,-17,0,-16,8,18,4,11,31,39,45,37,17,38,24,-10,-43,-2,-11,13,6,-4,-16,-3,-16,43,35,31,-3,38,23,28,28,-16,-10,0,1,20,25,-11,15,-3,22,4,-4,-18,28,24,25,39,-21,-48,3,6,11,22,15,-7,9,-44,7,2,28,13,29,10,12,-18,-7,-14,18,0,-32,9,-7,31,11,11,20,5,10,8,10,15,31,2,-5,-2,3,33,-15,21,17,2,18,-30,7,-12,-27,1,11,11,-3,-29,30,5,7,55,34,17,23,10,-12,7,20,16,-29,-23,-52,-33,20,32,6,10,-24,-15,-2,-15,10,8,7,-20,40,14,47,-2,-51,-24,-37,6,41,-34,-57,-25,-10,-1,18,-39,-32,-17,-38,7,-11,7,35,64,22,15,21,-10,-21,6,21,13,32,0,-14,-12,25,-17,-12,-47,26,2,-20,21,15,-2,-22,37,14,24,10,30,8,-11,18,-9,-28,5,17,11,-12,-19,5,1,21,-23,-19,15,0,-15,-9,-31,4,7,-29,21,10,10,6,-9,-2,8,-9,-16,31,22,38,14,-18,-2,1,-4,4,14,-18,-13,-21,11,12,44,23,-4,47,-10,-3,-20,20,-2,15,5,-3,-9,7,-2,9,7,-11,19,-2,-24,-18,2,56,22,-10,5,22,-23,32,2,-54,16,26,-4,-23,-23,42,-1,2,-23,19,32,-23,-20,20,41,46,-21,-55,14,14,-17,-49,-29,-12,17,-24,-8,14,-21,-17,36,53,-15,17,25,45,23,22,27,-24,-27,19,12,-2,6,1,26,-2,-16,15,6,15,9,-44,-26,4,-5,-33,-50,-32,-12,-8,9,-5,-32,-13,15,28,4,13,10,31,15,25,17,-9,3,-7,5,1,2,11,-17,5,2,-17,-10,-15,-45,-14,-19,-1,21,33,-22,-9,11,30,-9,-41,-43,5,27,-11,-10,-33,-3,-4,-3,-3,8,-17,6,-9,-39,20,20,-20,-55,-33,-7,16,-11,-11,14,31,1,-10,-17,-23,56,38,6,-13,39,9,17,2,-27,-8,-15,42,41,-19,-16,-6,-22,-23,-21,-18,-3,33,-10,-14,10,-15,0,29,3,31,15,13,-22,-4,-15,-24,-6,14,-43,-22,4,-3,22,8,30,23,3,12,35,10,-13,10,-11,-5,10,14,13,20,19,13,38,-20,13,-5,-4,39,-31,-63,-33,2,-7,-25,-39,-15,13,-5,9,-16,-9,-22,-19,18,13,-1,17,31,19,22,26,45,24,3,-41,-3,12,18,16,3,-18,9,2,27,-26,-1,33,20,-18,-3,-23,14,30,8,15,28,-2,7,-17,24,22,-7,-27,12,29,-14,-6,7,-32,-24,24,11,4,5,19,-1,19,-4,5,-23,-10,29,13,-12,0,4,34,16,30,-28,30,42,-21,0,9,3,23,12,7,17,2,-20,-10,-14,-5,18,-23,24,-12,45,14,-11,-18,27,-37,3,60,-10,9,27,27,16,9,-16,-18,3,0,17,-17,16,26,14,9,-18,-14,-4,3,2,14,38,6,33,-5,22,5,-14,29,22,-31,13,-16,14,-5,-53,-15,13,3,-20,-47,-14,20,25,-5,2,-18,-26,-8,13,11,3,25,21,34,4,0,27,6,-19,-18,10,49,26,1,17,-22,-7,-12,-48,-15,-6,-8,23,16,59,-3,-8,-14,10,16,0,-32,-26,4,23,-5,-15,-34,-36,3,-4,11,4,18,28,-29,-7,-6,7,-1,14,10,12,-1,36,-25,0,-14,1,0,5,-12,2,13,-4,0,7,33,-21,-10,-6,18,26,-19,-17,-6,25,32,10,18,-10,9,15,4,-1,13,-2,-5,-12,-36,41,28,24,22,17,27,48,11,-19,4,-7,26,7,15,-6,34,-18,-42,-6,-32,-20,-2,3,5,-6,-5,-16,-24,2,1,6,18,20,-19,6,38,2,23,-14,-2,8,-35,-33,-17,2,7,4,-62,3,-22,-2,15,4,-36,-22,41,23,20,27,28,4,-9,-13,-22,3,-6,-1,-9,-21,-18,31,20,3,-63,-33,-23,-18,-12,-39,-44,-6,1,3,26,5,-19,-14,24,-36,-12,14,36,24,36,27,-3,17,44,9,-24,-6,22,13,22,-31,-10,-30,-27,8,8,11,11,-12,27,38,45,0,22,28,-32,7,32,-8,-10,-8,31,1,-8,-31,10,-7,-34,19,29,8,-20,6,-14,6,-3,-16,-5,27,-11,47,20,-18,-2,-2,2,-12,12,28,-29,-1,0,-19,42,-9,-2,13,-30,17,33,17,10,},

                    {-2,9,4,-11,-5,2,3,9,3,4,4,3,6,7,-1,7,-12,6,12,2,3,8,3,10,7,-15,2,-5,9,3,7,2,7,-1,-13,-11,-12,11,-2,-2,2,6,7,4,3,-7,-8,-4,-4,8,-9,2,-4,-13,4,2,-13,-10,-10,-2,3,4,10,-7,-14,9,8,-17,-9,-2,-6,-10,-1,-11,6,2,7,-6,-10,-10,-13,-1,8,-5,-8,7,4,-6,-1,-5,-2,3,0,7,-5,-1,-13,-3,-8,-4,1,4,-2,0,-2,4,1,2,5,2,0,10,-12,4,9,-5,10,-5,-4,2,-8,11,-11,-4,7,1,-2,7,2,-6,-6,-3,-3,-10,-10,-2,-7,-2,-11,-4,-8,10,6,7,-10,-11,-7,0,-3,7,-6,4,12,-11,-8,-5,-9,-4,3,-9,7,9,-9,-12,5,2,4,-4,5,-15,-14,7,-2,-1,-2,-12,2,7,-1,-8,-6,-3,2,6,7,13,-5,-6,4,-10,6,-12,-12,0,3,8,-2,-9,-11,1,-10,10,-7,9,0,-6,8,-5,5,1,-7,9,2,-9,8,-12,-12,7,-7,7,-6,-9,-9,-6,11,2,1,-9,-3,10,2,-9,-7,-12,-2,12,-2,0,8,-2,2,-1,-6,2,1,-7,-5,-6,-2,-8,-6,-1,-3,-6,-2,3,-11,-4,1,8,-5,4,7,-3,-3,-11,-13,-11,-10,10,-6,7,1,1,-4,11,-7,1,-9,9,3,-3,-5,9,5,-1,3,-2,8,-11,-7,-8,4,12,6,7,4,7,-4,-7,-4,-5,-11,-3,8,-10,-11,2,8,5,5,-14,3,0,1,-12,-13,-8,1,4,-8,-3,7,8,0,0,3,2,4,5,-9,3,-15,-11,8,4,4,-6,-14,8,-5,12,7,-6,10,4,-9,-5,-12,-8,-7,-3,-4,7,-1,-1,-4,0,-10,-3,-9,10,-3,-12,4,9,-9,0,2,-12,-6,4,-10,-17,2,0,-12,-3,-12,-1,-1,-15,-11,-10,-8,5,5,3,-5,-13,1,2,-17,-10,-9,3,-9,12,0,7,12,5,-3,-10,-18,3,-14,-8,2,6,-2,1,8,-10,-12,-11,1,-13,-7,-15,-12,3,-7,2,-1,-6,-9,5,-1,10,7,-1,-4,9,-12,-3,-3,11,7,-5,-5,-2,-4,-17,-10,-4,-16,-2,-12,1,12,0,-1,-18,-6,-12,-2,-9,3,-10,1,-9,4,-3,-2,-1,-3,7,-7,-9,11,9,2,-5,-2,-9,-8,-6,0,4,8,-6,8,-4,-2,1,-11,-9,6,3,9,1,-6,-5,-12,-2,2,1,-13,-8,6,7,-9,-9,0,2,2,5,-10,11,10,-5,4,11,4,-13,-7,-9,-1,1,2,3,5,3,-8,-6,0,7,1,-3,2,2,-13,6,11,-9,-9,-4,-3,12,-3,7,9,-10,6,-10,-11,2,-3,-5,-10,7,2,-2,-12,5,-7,-4,5,-9,-2,-14,2,1,2,-3,-1,-9,2,5,1,4,9,9,7,0,-12,-9,0,5,7,8,1,-4,6,6,6,-1,-13,-7,-13,7,4,10,-8,7,-5,-4,2,3,-3,-8,-11,-8,11,-11,4,-3,-10,3,0,-3,-9,-8,1,7,2,-18,-12,6,0,6,-12,-3,7,-4,-9,-11,-12,-15,-1,3,10,-4,-12,10,8,10,-8,6,-10,-12,-10,-3,-4,-4,-9,-9,1,-3,7,9,-10,7,1,-9,8,6,-9,8,7,-14,-2,0,-11,-6,-7,-12,-8,-13,8,-10,-4,-1,-8,-5,3,0,-10,-12,-13,-13,4,2,-11,3,0,8,-9,6,8,-9,-6,-10,9,-8,0,10,-10,-2,-2,8,-4,8,-9,-6,6,-1,7,11,9,-11,12,-13,1,10,-11,10,10,2,-2,-13,12,7,5,-8,-2,-12,-8,2,-6,-6,-2,11,-13,-13,0,-8,5,12,-2,2,1,-10,5,-8,8,4,4,-7,-18,3,-6,-12,-10,-2,-9,-9,1,-2,11,-5,4,-10,-9,-14,-5,-6,-13,1,5,-14,4,-8,13,-10,-8,-12,6,9,0,-14,-8,-10,1,-4,-3,9,-7,-3,10,-10,-5,-9,2,7,-4,-3,-1,5,-1,-2,-7,8,6,1,7,5,-4,-6,6,-2,-2,-1,0,1,-3,-8,-9,-11,3,0,-2,-12,-11,3,-2,3,-11,-12,0,1,6,3,6,9,-12,-2,-8,10,-7,-6,-8,-2,11,-5,9,-12,5,-7,-3,1,0,2,-10,-6,-7,-5,4,5,5,10,6,-6,10,1,5,-11,2,4,1,-6,-5,-5,-12,-14,-7,3,-11,-12,3,1,-9,2,-10,-5,-14,-14,-4,-1,-2,1,-10,-11,0,-13,4,10,-5,2,2,-8,-12,-7,8,-5,-4,11,-6,5,-3,-5,-5,-10,-8,-7,0,-9,8,2,0,-8,7,10,-5,9,-13,0,6,-4,6,0,10,9,-11,-11,-12,9,8,-9,-6,4,-3,-6,-13,-10,6,3,11,2,13,-1,6,5,-5,6,-13,7,4,-6,9,-7,-2,0,2,9,6,0,-9,-5,10,-3,-6,-10,-2,-5,2,7,-1,5,-12,7,3,3,12,1,-7,8,11,1,1,8,-5,3,-6,2,-7,4,10,-13,8,11,10,-4,-8,-10,3,-7,7,-2,-3,-5,9,-10,8,3,5,-11,-11,-1,1,3,-1,-8,-2,-2,6,5,2,3,1,-13,-1,0,-1,-8,5,10,12,0,11,-1,-11,-1,3,-6,8,5,10,0,-4,1,-12,-6,-10,-5,-11,8,-8,-12,-5,-4,9,-5,2,1,-2,-5,4,-6,-8,-9,-10,-9,-6,-11,-13,4,3,-1,-1,-15,-9,9,-2,4,1,8,2,-11,8,-12,-5,6,-15,2,-7,10,-13,-4,-6,-12,2,-10,-5,-5,1,5,-17,-7,0,-8,-10,0,-11,3,-10,-12,3,3,0,6,-1,-12,7,9,-9,11,-8,-9,-6,1,-11,9,-2,-11,-7,-4,-12,1,-7,-2,-7,-9,4,-10,-3,-11,10,3,-5,-7,},

                    {-16,-1,-14,14,10,-7,4,11,-10,-4,26,45,-8,3,24,-18,-30,10,17,7,-8,-29,5,28,22,-41,2,-15,-19,27,13,1,-33,-22,-33,33,-7,-38,-29,-11,20,-15,-32,-44,-33,-33,-5,-1,-63,-54,20,-29,21,7,33,22,55,-11,-9,6,58,37,80,4,-11,5,12,40,47,-11,-19,3,-15,12,9,-11,21,22,21,5,-27,-11,31,23,-4,11,0,-61,-12,40,49,32,13,-48,-2,4,45,26,-16,-27,-11,-22,10,0,-52,-29,-4,12,3,-1,-24,-23,-26,-9,10,-4,21,13,-8,-3,54,19,7,-3,2,21,-2,-3,-9,-28,18,12,-23,4,0,-51,-5,-8,14,-14,-3,-4,-7,1,12,-41,-23,-30,0,13,7,5,-12,-48,5,-16,-26,-29,-10,-9,15,10,8,-4,75,-20,14,7,31,28,71,25,13,10,19,29,56,5,-11,4,10,3,2,5,21,-34,-34,-39,25,5,-24,-14,3,-11,6,1,-6,7,1,-17,1,-10,19,54,10,48,3,-8,-19,17,20,34,-8,-3,-6,14,-23,-50,13,38,51,67,-28,-18,-33,7,11,29,2,9,2,26,50,30,-27,31,21,3,3,18,-10,3,15,2,8,36,-44,-3,13,15,-12,10,-8,-29,0,9,-5,-7,15,25,31,8,24,41,20,21,-11,27,41,18,-13,-6,-7,-21,34,-2,-9,-1,6,-44,4,19,-16,6,1,1,18,35,3,15,14,-37,-37,4,-1,0,-8,2,-5,-15,-1,68,48,13,-9,-13,-8,-2,39,-16,-24,-53,-24,13,28,-3,10,23,-1,-3,7,-17,29,20,-42,3,-48,-37,-24,10,-2,-2,16,8,-2,16,-13,3,-16,34,17,37,17,6,-15,-22,53,2,-12,10,-6,12,9,-9,29,1,17,17,5,49,-11,-3,-34,22,30,58,-63,-24,-1,-14,41,64,-10,-13,6,-19,3,68,25,28,22,-23,23,18,8,57,17,-28,-1,-35,51,30,10,6,-1,31,12,18,-3,9,-17,-18,7,25,7,3,20,-31,43,71,69,10,-40,-11,-43,-16,25,-20,-24,5,-1,-12,12,-6,-29,2,7,2,-6,8,11,9,27,-8,-12,9,-13,1,43,9,-16,-8,-4,8,48,-1,25,-25,-47,32,16,2,12,-36,-11,40,24,12,18,-1,3,-27,12,17,-17,-29,-3,27,-31,-33,5,-1,36,2,-37,-2,-14,-14,-2,64,16,1,-18,-11,19,60,15,36,13,6,29,-3,21,6,12,9,-6,8,26,-10,-21,10,20,26,-29,-36,-2,26,1,6,31,16,-24,-13,29,18,5,-14,-11,-33,17,-17,-11,-16,28,7,20,23,-29,26,18,-1,8,-5,-12,-47,-17,2,-4,-18,-10,-29,-19,-56,-17,-40,0,-24,0,18,-21,13,18,15,41,18,-23,27,13,-18,-7,-4,-1,56,-13,-38,-10,-27,-14,23,11,-36,3,4,12,31,-10,-41,-21,-59,-24,-37,5,10,17,-1,-28,-30,28,22,22,28,4,-9,42,22,-9,7,21,29,-1,5,9,-18,-18,30,16,-6,4,-10,-7,25,13,21,9,3,10,28,8,22,14,-20,-16,19,-3,4,31,-27,-60,-36,-12,30,8,1,-20,18,38,-15,-45,-25,10,41,-1,-4,-35,-30,-5,3,-13,-56,-17,-14,8,-15,-7,-7,-8,7,16,8,2,7,-7,31,25,13,28,6,-1,44,24,-14,2,5,35,19,-31,-5,-37,-20,45,39,-9,-20,-32,-28,8,-1,13,-21,10,9,8,56,52,-6,13,-11,-3,89,53,18,13,17,-32,17,16,21,-17,2,-2,-4,-5,43,-12,-11,7,28,-9,18,14,-34,-47,1,-11,-7,6,16,18,0,-60,-30,21,14,32,50,-10,-16,35,24,2,21,14,9,11,7,-33,-33,8,7,8,4,-7,-24,6,14,19,25,23,5,-10,13,-6,-4,17,-13,-11,-9,12,13,21,-25,-21,30,3,5,22,-65,34,7,4,11,20,-10,3,9,7,30,3,-24,-3,10,-6,16,-50,-9,-26,-11,-14,-22,-1,-2,16,52,-25,12,43,-28,-7,-12,-6,5,14,11,19,10,-45,20,-7,-20,15,17,-12,36,21,8,10,-13,-59,-30,-12,1,17,15,12,-1,-5,2,35,92,12,15,8,-9,-4,44,23,30,-7,-13,71,11,21,-14,13,-2,-31,6,12,2,6,28,3,-10,-14,-8,-15,23,-26,9,-10,-5,0,-2,-50,-39,30,28,-4,16,5,10,38,22,-21,-39,16,32,5,7,-6,-15,2,22,21,24,-1,-13,9,14,-3,2,-15,-8,10,-2,15,24,-15,5,14,15,-15,-6,5,-31,-24,10,63,30,3,-37,-16,-15,-2,7,12,-3,4,-6,11,22,-11,9,-31,27,11,1,-52,-7,-3,-34,8,-39,2,-34,-20,14,5,-18,30,-24,21,23,0,6,63,14,12,10,5,29,41,26,-32,3,17,-17,-14,-12,6,-27,4,-3,14,-22,-15,-16,23,21,0,13,40,9,35,28,52,-3,-5,-7,27,20,-1,-5,-5,-1,9,9,20,16,4,26,-3,-33,-30,-41,-32,-19,-15,-7,-32,19,-7,-37,33,27,16,23,43,11,-5,30,-10,33,20,14,-4,-7,20,7,14,19,-22,-47,-3,-21,-31,24,-51,-39,-5,29,0,17,24,26,-28,-9,-28,-28,20,27,20,39,42,16,34,32,-49,-43,-3,-10,-8,0,-6,-47,21,26,-6,16,-6,-34,-3,-10,-7,-15,7,-17,0,8,-7,4,-15,9,-10,13,9,-14,-29,-27,-5,7,3,-46,-7,6,8,-5,-18,13,21,-10,-12,-7,18,1,18,-24,-8,-9,-24,25,39,23,-9,-6,-9,-22,9,21,-3,-12,-13,-7,-10,38,1,10,-1,-26,-13,61,23,10,-3,-2,-35,25,16,18,8,-7,-29,25,-5,29,16,-9,1,36,-6,39,},

            }
    };
    Bias_t Dense_8_Bias[64]= {
            -71,-137,271,-365,366,-120,149,-173,-780,-385,-313,-370,142,615,431,133,-551,-354,464,-252,-549,350,195,-568,-103,-240,46,-38,-108,404,447,452,214,406,-431,-121,-33,-156,506,68,157,-9,-38,592,281,514,-340,-4,380,-413,69,200,-225,-10,-33,-7,-689,-245,-320,-21,554,157,-83,541,
    };
    Weights_t Dense_10_Weights[1][10][64]={
            {
                    {31,-6,7,-67,38,46,24,-11,-35,6,-71,-36,50,-57,54,38,21,-53,-76,42,46,47,16,68,-33,-32,37,46,39,11,35,15,-21,-89,57,-38,39,-75,-10,33,62,10,-42,5,42,3,-23,6,13,-72,-68,18,-73,9,-28,51,18,-92,-52,30,-30,12,-19,2,},

                    {-29,20,-44,2,39,-41,-18,40,15,-61,-70,-9,-18,44,20,17,2,15,35,-20,-30,-1,46,-19,18,33,31,-106,-3,31,28,19,-42,64,12,71,-36,16,1,57,31,29,-35,41,9,25,-101,-55,89,-9,15,17,-47,-75,-19,-45,-16,23,5,2,29,44,-10,25,},

                    {-15,24,17,32,-67,36,11,10,12,-47,-27,52,45,10,-92,18,0,-73,19,41,32,45,-14,37,11,19,-17,24,-28,-94,-105,33,39,28,-60,28,7,-78,22,51,47,55,-71,34,-7,57,-59,51,-92,-58,-30,4,58,1,-66,41,-94,-39,-111,-60,9,31,-5,12,},

                    {6,-25,-58,39,-56,-49,10,-31,3,56,30,40,-69,-95,-15,44,21,-49,45,50,41,-48,55,-49,31,-61,70,36,-30,-54,-36,-75,17,20,-9,-12,44,15,-73,45,-17,-72,6,29,50,-7,-51,9,-58,-50,54,-86,9,-28,-70,-70,-45,55,35,-40,-44,-69,-10,-48,},

                    {-8,17,26,44,-72,-13,11,31,-60,14,-29,24,5,44,54,-19,-57,20,-7,-16,30,-83,-87,66,19,-37,-67,41,-6,15,-47,-73,-63,-18,-9,8,41,28,28,-2,-48,18,56,42,-126,13,-6,-41,-5,-5,13,48,29,-61,32,-26,49,13,-6,-1,48,-21,-45,25,},

                    {-83,2,20,15,-19,-72,-16,-13,-32,49,-11,-51,43,-7,-24,5,-56,20,1,3,24,28,25,-54,-35,-63,-41,13,25,-10,67,43,46,0,-57,17,-48,26,8,-37,27,-56,41,-38,36,-8,-25,31,-53,62,-20,-47,49,-27,-41,-53,26,-45,56,3,-49,-57,4,21,},

                    {-9,-2,-28,-71,46,24,-68,36,11,14,-79,5,0,-42,-20,53,47,10,-83,-53,21,-14,10,-9,24,5,-19,41,-22,-63,31,-20,47,25,36,-24,-44,0,7,-57,36,54,-34,39,-24,17,-6,-80,-3,30,10,-47,15,8,34,-7,41,81,16,29,-69,-20,28,-79,},

                    {29,14,-62,13,27,-60,-65,19,17,37,36,-1,24,29,-90,-61,31,32,1,11,-18,-53,6,68,-23,22,41,-116,-40,26,-6,-9,0,56,-37,-55,40,-62,-68,51,-59,-68,-1,44,0,-34,-43,39,-35,-67,35,10,-9,7,-1,37,16,54,-68,84,59,44,-15,39,},

                    {28,-23,50,-15,-74,37,29,41,20,-44,28,55,-87,-76,22,37,-1,-16,-14,-30,4,-8,40,-7,40,-15,2,9,-40,23,37,30,25,-68,-39,-8,-44,5,27,-45,20,-65,-106,-54,29,22,-7,27,-63,-14,54,-58,20,13,61,-21,12,-30,-8,-89,27,13,38,20,},

                    {27,31,-13,46,0,-5,-19,-6,-34,-2,-3,39,-37,-29,32,-74,13,27,1,43,37,-74,14,16,23,35,2,24,4,24,1,-49,-62,-86,2,36,-4,9,-78,-74,44,66,17,-72,-4,-36,42,22,-28,79,-62,44,21,-40,-7,24,41,-127,49,22,-1,32,11,-9,},

            }
    };
    Bias_t Dense_10_Bias[10]={
            46,141,20,35,2,40,-349,-57,136,-57,
                };

    /*****************第4步:添加网络层**********************/
    OpenNNA_Add_Layer(Network, "Padding", "OpenNNA-Paper", Layer_Para_Base1,Layer_Para_Padding1, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base2,Layer_Para_Conv2d2, Conv2d_2_Weights, Conv2d_2_Bias);
    OpenNNA_Add_Layer(Network, "ReLU", "xddcore", Layer_Para_Base3,Layer_Para_ReLU3, NULL, NULL);
    OpenNNA_Add_Layer(Network, "MaxPool", "lululu~", Layer_Para_Base4,Layer_Para_MaxPool4, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "lalala~", Layer_Para_Base5,Layer_Para_Conv2d5, Conv2d_5_Weights, Conv2d_5_Bias);
    OpenNNA_Add_Layer(Network, "ReLU", "The", Layer_Para_Base6,Layer_Para_ReLU6, NULL, NULL);
    OpenNNA_Add_Layer(Network, "MaxPool", "Future", Layer_Para_Base7,Layer_Para_MaxPool7, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Dense", "Of", Layer_Para_Base8,Layer_Para_Dense8, Dense_8_Weights, Dense_8_Bias);
    OpenNNA_Add_Layer(Network, "ReLU", "Possible", Layer_Para_Base9,Layer_Para_ReLU9, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Dense", "Think", Layer_Para_Base10,Layer_Para_Dense10, Dense_10_Weights, Dense_10_Bias);
    OpenNNA_Add_Layer(Network, "Softmax", "Different", Layer_Para_Base11,Layer_Para_Softmax11, NULL, NULL);
    /*****************第5步:初始化神经网络**********************/
    OpenNNA_Init(Network);
    /*****************第6步:打印神经网络信息**********************/
    #if(DEBUG==1)
        OpenNNA_Print_Network(Network);
    #endif
    /*****************第7步:设置神经网络输入数据和输出数据**********************/
    Fmap_t NN_Input_Fmap[1][28][28]={//5
            {
                    {-127, -128, -128, -128, -128, -127, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -125, -128, -128, -128, -127, -126, -126, -128, -128, -128, -128, -128, -128, -122, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -127, -128, -128, -128, -128, -128, -128, -124, -127, -126, -124, -125, -124, -128, -125, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -125, -128, -128, -127, -127, -128, -128, -126, -126, -123, -126, -119, -123, -120, -121, -122, -124, -127, -122, -127, -128, -128, -128, -128, -128, },
                    {-127, -128, -128, -128, -128, -126, -127, -128, -127, -126, -127, -128, -121, -105, -108, -107, 7, 17, 52, -93, 46, 127, 124, 5, -128, -128, -128, -128, },
                    {-128, -128, -125, -128, -127, -126, -128, -125, -96, -89, -29, 31, 45, 127, 127, 127, 127, 127, 104, 48, 127, 116, 71, -63, -128, -128, -128, -128, },
                    {-127, -128, -127, -128, -127, -128, -125, -81, 113, 127, 127, 127, 127, 127, 127, 127, 127, 127, -25, -43, -42, -66, -87, -123, -128, -128, -128, -128, },
                    {-127, -128, -128, -127, -128, -128, -124, -114, 99, 127, 125, 125, 124, 127, 76, 66, 114, 115, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -128, -128, -128, -126, -44, 29, -19, 127, 122, 80, -116, -117, -87, 28, -127, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -109, -128, 23, 124, -42, -123, -122, -124, -124, -126, -125, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -126, -127, -128, -128, -128, -127, 11, 124, 60, -127, -122, -126, -123, -121, -126, -124, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -125, -127, -114, 60, 127, -57, -118, -123, -120, -123, -122, -125, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -90, 113, 102, 35, -17, -124, -125, -125, -125, -126, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -49, 112, 125, 127, -4, -100, -125, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -87, 57, 125, 126, 22, -98, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -114, -18, 127, 127, 66, -128, -127, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -114, 127, 127, 125, -59, -126, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -128, -124, -128, -128, -128, -128, -128, -128, -128, -87, -8, 69, 127, 127, 83, -128, -127, -128, -128, -128, -128, -128, -128, },
                    {-128, -125, -128, -128, -125, -125, -125, -126, -128, -128, -128, -128, -92, 16, 93, 123, 127, 127, 126, 54, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -125, -126, -128, -124, -123, -118, -101, -15, 93, 123, 126, 124, 126, 73, -51, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -125, -128, -127, -121, -126, -96, -56, 89, 126, 127, 126, 127, 76, -42, -127, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -123, -128, -121, -123, -108, 44, 100, 127, 127, 127, 127, 74, -41, -107, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -70, 49, 99, 127, 127, 127, 127, 120, 10, -105, -119, -116, -126, -127, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-126, -128, -127, -127, 9, 126, 127, 127, 84, 9, 5, -109, -127, -128, -128, -127, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -124, -128, -126, -126, -123, -124, -125, -126, -127, -125, -128, -127, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -128, -127, -125, -127, -126, -128, -126, -128, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -121, -128, -122, -128, -127, -126, -128, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
            },


    };
    Fmap_t NN_Input_Fmap_2[1][28][28]={//2 int8
            {
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -1, 112, 121, 55, -23, -24, -20, -12, -45, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, 86, 122, 119, 127, 127, 127, 127, 127, 122, 74, -51, -127, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -122, -14, 125, 126, 127, 127, 127, 127, 127, 127, 127, 127, -17, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -125, -94, 83, 127, 127, 127, 127, 127, 127, 127, 127, 127, 21, -127, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -124, -125, -124, -45, 23, 26, 44, 127, 127, 127, 127, 127, 67, -115, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, 28, 127, 127, 127, 127, 98, -104, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, 15, 127, 127, 127, 127, 20, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -110, 77, 127, 127, 127, 127, -68, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, 8, 126, 127, 127, 127, 119, -64, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, 91, 125, 127, 127, 127, 127, 46, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -127, -128, -102, -7, 127, 127, 127, 127, 127, -32, -106, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -127, -2, 96, 127, 127, 127, 127, 127, 62, -114, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, 41, 126, 126, 125, 127, 127, 64, -51, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -126, -118, -118, -46, 99, 127, 127, 127, 127, 94, 10, -118, -128, -116, -122, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -126, -121, -65, 108, 127, 127, 127, 117, 95, -86, -128, -128, -128, -126, -120, -105, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -50, 127, 125, 121, 122, 105, -75, -128, -128, -128, -128, -124, -5, 72, 11, -73, -120, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -125, -49, 127, 127, 125, 121, 123, 116, 118, 116, 111, 112, 120, 123, 119, 115, 124, -104, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -124, -57, 126, 124, 127, 127, 127, 124, 126, 119, 122, 122, 127, 127, 123, 125, 123, 27, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -125, -103, 58, 126, 127, 126, 127, 127, 125, 127, 126, 122, 127, 127, 127, 125, 110, -58, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -126, -128, -127, -109, 65, 127, 127, 123, 123, 127, 120, 122, 125, 127, 127, 127, 127, -68, -125, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -123, -123, -122, -126, -128, -128, -127, -126, -128, -124, -128, -128, -109, -114, -117, -123, -126, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
            },


    };
    Fmap_t NN_Input_Fmap_0[1][28][28]={//0
            {
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -125, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -124, -121, -128, -124, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -126, -128, -119, -51, 82, 127, 127, 40, -84, -122, -126, -124, -125, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -121, -110, 57, 126, 127, 127, 127, 127, 127, -99, -124, -125, -125, -127, -125, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -110, 55, 127, 127, 95, -26, 106, 127, 127, 53, -9, -125, -126, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -19, 125, 127, 35, -90, 39, 127, 127, 127, 127, 127, -10, -125, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -125, -111, 90, 127, 127, -35, -1, 124, 100, -1, -31, 116, 125, 121, -21, -128, -120, -122, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -124, -125, -128, -25, 127, 127, -7, -117, 12, 125, -36, -128, -127, -99, 68, 122, 119, -66, -128, -119, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -128, -123, -124, 42, 127, 127, -90, -122, -44, 103, -95, -128, -124, -126, -59, 121, 119, 83, -98, -121, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -125, -128, -89, 127, 127, 78, -107, -120, -128, -128, -128, -128, -128, -128, -127, -47, 124, 122, 42, -118, -128, -128, -128, -128, },
                    {-128, -128, -128, -124, -124, -120, -91, 124, 126, 38, -119, -126, -125, -128, -128, -128, -128, -128, -124, -120, 63, 122, 58, -118, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -119, -93, 127, 124, -44, -126, -126, -128, -128, -128, -128, -128, -128, -128, -128, 13, 122, 127, -89, -128, -128, -128, -128, },
                    {-128, -128, -128, -125, -120, -122, 9, 124, 122, -83, -124, -125, -128, -128, -128, -128, -128, -128, -128, -128, -87, 126, 127, -86, -128, -128, -128, -128, },
                    {-128, -128, -128, -124, -122, -120, 30, 127, 121, -86, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -85, 127, 127, -86, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -120, -120, -26, 127, 122, -33, -128, -128, -128, -128, -128, -128, -128, -126, -127, -128, -86, 126, 127, -81, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -124, -125, -87, 127, 123, 38, -128, -128, -128, -128, -128, -128, -128, -128, -128, -113, 77, 124, 85, -104, -128, -128, -128, -128, },
                    {-128, -128, -128, -125, -123, -124, -92, 115, 127, 48, -124, -126, -127, -128, -128, -128, -128, -128, -128, -89, 121, 123, 29, -125, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -126, -125, -128, 46, 125, 127, -95, -125, -128, -128, -128, -128, -128, -128, -95, 89, 120, 62, -113, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -121, -128, 44, 127, 127, -65, -127, -125, -128, -128, -128, -125, -70, 89, 127, 124, -61, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -126, -128, -128, -50, 127, 127, 110, -71, -128, -127, -128, -109, -1, 127, 127, 117, -34, -116, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -125, -125, 30, 127, 127, 114, -26, -8, 95, 99, 127, 127, 79, -48, -128, -128, -128, -126, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -128, -128, -128, -79, 114, 127, 127, 127, 127, 120, 123, 127, 78, -60, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
            },


    };

    Fmap_t NN_Input_Fmap_8[1][28][28]={//8
            {
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -122, -125, -126, -125, -128, -126, -126, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -128, -128, -125, -121, -120, -119, -120, -121, -119, -125, -128, -127, -128, -123, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -126, -79, 45, 127, 127, 127, 127, 110, 2, 3, -82, -123, -124, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -125, -128, 30, 124, 127, 127, 127, 127, 127, 127, 127, 127, 124, 39, -76, -125, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -127, -72, 114, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 111, -76, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -119, -29, 109, 117, 116, 89, 17, 18, 32, 50, 127, 127, 126, 127, 127, 62, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -122, 56, 120, 117, 120, -75, -127, -128, -122, -113, 58, 124, 125, 126, 127, -11, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -81, 96, 122, 117, 88, -99, -128, -122, -122, -107, 79, 121, 123, 121, 74, -57, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -109, 65, 120, 119, 67, -108, -127, -127, -74, 94, 122, 122, 120, 125, -29, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -123, -81, 107, 119, 127, -12, -96, -40, 60, 127, 126, 125, 114, -38, -109, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -124, -108, 65, 121, 127, -23, 70, 127, 127, 125, 127, 91, -85, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -3, 121, 124, 126, 127, 127, 127, 113, 36, -79, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -127, -128, 65, 118, 123, 127, 126, 127, 114, 29, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -8, 119, 125, 122, 125, 113, 28, -120, -124, -124, -125, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -127, -128, -128, -128, -127, -127, -127, -128, -38, 112, 126, 124, 125, 127, 106, -60, -127, -124, -122, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -128, -128, -128, -128, -34, 116, 123, 117, 124, 127, 127, 127, 112, -81, -122, -126, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -127, -128, -128, -124, -126, 98, 119, 120, 75, -31, 83, 124, 127, 121, -39, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -128, -124, -128, -6, 124, 113, 93, -94, -34, 127, 127, 123, 63, -122, -122, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -126, -128, -128, -124, 113, 122, 85, -44, 20, 108, 125, 122, 127, -56, -126, -126, -127, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -127, -126, -126, -63, 121, 121, 126, 124, 127, 124, 126, 126, 87, -96, -120, -122, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -126, -128, -128, -128, -13, 124, 126, 127, 127, 127, 127, 89, -12, -95, -123, -121, -125, -126, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -70, 120, 127, 127, 57, 127, 24, -97, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -126, -124, -126, -128, -122, -128, -128, -124, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -123, -128, -125, -128, -128, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
                    {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -128, -128, -128, -126, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, },
            },
    };

    Fmap_t NN_Output_Fmap[1][1][10]={0};
    
    /*****************第8步:神经网络推理**********************/
#if(DEBUG==1)
    OpenNNA_Printf("Begin Predict!\n");
#endif
    OpenNNA_Predict(Network, NN_Input_Fmap, NN_Output_Fmap);
    /*****************第9步:根据推理结果进行动作**********************/
    printf("\n推理结果:   \n");
    for(int i = 0;i<10;++i)
    {
        printf("[%d]%f,   ",i,NN_Output_Fmap[0][0][i]*100);
    }
    printf("\n");
    /*****************第10步:推理结束释放网络结构+申请的特征图堆内存**********************/
    OpenNNA_Free_Network(&Network);
    return 0;
}