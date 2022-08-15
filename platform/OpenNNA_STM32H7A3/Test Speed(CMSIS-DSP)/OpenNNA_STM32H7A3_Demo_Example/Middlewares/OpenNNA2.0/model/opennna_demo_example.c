//
// Created by 董程森 on 2022/7/7.
//
#include "opennna_core.h"
#include "stdio.h"

#include "opennna_demo_example.h"
/*****************OpenNNA Example算子示例**********************/
/*
 * Example算子会实现输出特征图 = 输入特征图 * Weights + Bias
 */
int OpenNNA_Demo_Example() {
    /*****************第1步:创建神经网络对象**********************/
    struct layer * Network = OpenNNA_CreateNetwork();
    /*****************第2步:配置网络层参数**********************/
    struct Layer_Para_base *Layer_Para_Base1 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_example *Layer_Para_Example1 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base1->Input_Fmap_Channel=2;
    Layer_Para_Base1->Input_Fmap_Row=2;
    Layer_Para_Base1->Input_Fmap_Col=5;
    Layer_Para_Base1->Output_Fmap_Channel=2;
    Layer_Para_Base1->Output_Fmap_Row=2;
    Layer_Para_Base1->Output_Fmap_Col=5;

    struct Layer_Para_base *Layer_Para_Base2 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_example *Layer_Para_Example2 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base2->Input_Fmap_Channel=2;
    Layer_Para_Base2->Input_Fmap_Row=2;
    Layer_Para_Base2->Input_Fmap_Col=5;
    Layer_Para_Base2->Output_Fmap_Channel=2;
    Layer_Para_Base2->Output_Fmap_Row=2;
    Layer_Para_Base2->Output_Fmap_Col=5;

    struct Layer_Para_base *Layer_Para_Base3 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_example *Layer_Para_Example3 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base3->Input_Fmap_Channel=2;
    Layer_Para_Base3->Input_Fmap_Row=2;
    Layer_Para_Base3->Input_Fmap_Col=5;
    Layer_Para_Base3->Output_Fmap_Channel=2;
    Layer_Para_Base3->Output_Fmap_Row=2;
    Layer_Para_Base3->Output_Fmap_Col=5;
    /*****************第3步:设置神经网络输入数据和输出数据**********************/
    //Note:Demo Example的权重和偏置比较小，所以可以放在栈中
    data_t Example_Weights[2][2][5]={
    {
        {2, 2, 2, 2, 2},
        {2, 2, 2, 2, 2},
                                         },
    {
        {2, 2, 2, 2, 2},
        {2, 2, 2, 2, 2},
        },
    };
    data_t Example_Bias[2][2][5]={
       {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            },
        {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            },
    };
    /*****************第4步:添加网络层**********************/
    OpenNNA_Add_Layer(Network, "Example", "xdd1", Layer_Para_Base1,Layer_Para_Example1, Example_Weights, Example_Bias);
    OpenNNA_Add_Layer(Network, "Example", "xdd2", Layer_Para_Base2, Layer_Para_Example2,Example_Weights, Example_Bias);
    OpenNNA_Add_Layer(Network, "Example", "xdd3", Layer_Para_Base3, Layer_Para_Example3,Example_Weights, Example_Bias);
    //OpenNNA_Add_Layer(Network, "ReLU", "xdd4", NULL, NULL,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "Dense", "xdd5", NULL, NULL,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "Softmax", "xdd6", NULL, NULL,NULL, NULL);
    /*****************第5步:初始化神经网络**********************/
    OpenNNA_Init(Network);
    /*****************第6步:打印神经网络信息**********************/
#if(DEBUG==1)
    OpenNNA_Print_Network(Network);
#endif
    /*****************第7步:设置神经网络输入数据和输出数据**********************/
    data_t NN_Input_Fmap[2][2][5]={
    {
            {0, 1, 2, 3, 4},
            {5, 6, 7, 8, 9},
        },
    {
            {0, 1, 2, 3, 4},
            {5, 6, 7, 8, 9},
        },
    };
    data_t NN_Output_Fmap[2][2][5]={0};
    /*****************第8步:神经网络推理**********************/
#if(DEBUG==1)
    OpenNNA_Printf("Begin Predict!\n");
#endif
    OpenNNA_Predict(Network, NN_Input_Fmap, NN_Output_Fmap);
    /*****************第9步:根据推理结果进行动作**********************/
#if(DEBUG==1)
    printf("Input fmap[0][0][0] = %f, fmap[0][0][1] = %f, fmap[0][0][2] = %f, fmap[0][0][3] = %f,fmap[0][0][4] = %f\n",\
    NN_Input_Fmap[0][0][0], NN_Input_Fmap[0][0][1], NN_Input_Fmap[0][0][2], NN_Input_Fmap[0][0][3], NN_Input_Fmap[0][0][4]);
    printf("Input fmap[0][1][0] = %f, fmap[0][1][1] = %f, fmap[0][1][2] = %f, fmap[0][1][3] = %f,fmap[0][1][4] = %f\n",\
    NN_Input_Fmap[0][1][0], NN_Input_Fmap[0][1][1], NN_Input_Fmap[0][1][2], NN_Input_Fmap[0][1][3], NN_Input_Fmap[0][1][4]);
    printf("Input fmap[1][0][0] = %f, fmap[1][0][1] = %f, fmap[1][0][2] = %f, fmap[1][0][3] = %f,fmap[1][0][4] = %f\n",\
    NN_Input_Fmap[1][0][0], NN_Input_Fmap[1][0][1], NN_Input_Fmap[1][0][2], NN_Input_Fmap[1][0][3], NN_Input_Fmap[1][0][4]);
    printf("Input fmap[1][1][0] = %f, fmap[1][1][1] = %f, fmap[1][1][2] = %f, fmap[1][1][3] = %f,fmap[1][1][4] = %f\n",\
    NN_Input_Fmap[1][1][0], NN_Input_Fmap[1][1][1], NN_Input_Fmap[1][1][2], NN_Input_Fmap[1][1][3], NN_Input_Fmap[1][1][4]);
    printf("\n\n");
    printf("Output fmap[0][0][0] = %f, fmap[0][0][1] = %f, fmap[0][0][2] = %f, fmap[0][0][3] = %f,fmap[0][0][4] = %f\n",\
    NN_Output_Fmap[0][0][0], NN_Output_Fmap[0][0][1], NN_Output_Fmap[0][0][2], NN_Output_Fmap[0][0][3], NN_Output_Fmap[0][0][4]);
    printf("Output fmap[0][1][0] = %f, fmap[0][1][1] = %f, fmap[0][1][2] = %f, fmap[0][1][3] = %f,fmap[0][1][4] = %f\n",\
    NN_Output_Fmap[0][1][0], NN_Output_Fmap[0][1][1], NN_Output_Fmap[0][1][2], NN_Output_Fmap[0][1][3], NN_Output_Fmap[0][1][4]);
    printf("Output fmap[1][0][0] = %f, fmap[1][0][1] = %f, fmap[1][0][2] = %f, fmap[1][0][3] = %f,fmap[1][0][4] = %f\n",\
    NN_Output_Fmap[1][0][0], NN_Output_Fmap[1][0][1], NN_Output_Fmap[1][0][2], NN_Output_Fmap[1][0][3], NN_Output_Fmap[1][0][4]);
    printf("Output fmap[1][1][0] = %f, fmap[1][1][1] = %f, fmap[1][1][2] = %f, fmap[1][1][3] = %f,fmap[1][1][4] = %f\n",\
    NN_Output_Fmap[1][1][0], NN_Output_Fmap[1][1][1], NN_Output_Fmap[1][1][2], NN_Output_Fmap[1][1][3], NN_Output_Fmap[1][1][4]);
#endif
    /*****************第10步:推理结束释放网络结构+申请的特征图堆内存**********************/
    OpenNNA_Free_Network(&Network);
    return 0;
}
