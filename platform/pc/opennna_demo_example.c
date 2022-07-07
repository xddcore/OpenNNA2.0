//
// Created by 董程森 on 2022/7/7.
//
#include "opennna_core.h"
#include "stdio.h"
/*****************OpenNNA Example算子示例**********************/
/*
 * Example算子会实现输出特征图 = 输入特征图 + 1的功能
 */
int main() {
    /*****************第1步:创建神经网络对象**********************/
    struct layer * Network = OpenNNA_CreateNetwork();
    /*****************第2步:配置网络层参数**********************/
    Layer_Para_Base *Layer_Para_Base1 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Example *Layer_Para_Example1 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base1->Input_Fmap_Channel=2;
    Layer_Para_Base1->Input_Fmap_Row=2;
    Layer_Para_Base1->Input_Fmap_Col=5;
    Layer_Para_Base1->Output_Fmap_Channel=2;
    Layer_Para_Base1->Output_Fmap_Row=2;
    Layer_Para_Base1->Output_Fmap_Col=5;

    Layer_Para_Base *Layer_Para_Base2 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Example *Layer_Para_Example2 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base2->Input_Fmap_Channel=2;
    Layer_Para_Base2->Input_Fmap_Row=2;
    Layer_Para_Base2->Input_Fmap_Col=5;
    Layer_Para_Base2->Output_Fmap_Channel=2;
    Layer_Para_Base2->Output_Fmap_Row=2;
    Layer_Para_Base2->Output_Fmap_Col=5;

    Layer_Para_Base *Layer_Para_Base3 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Example *Layer_Para_Example3 = OpenNNA_Malloc(sizeof(Layer_Para_Example));
    Layer_Para_Base3->Input_Fmap_Channel=2;
    Layer_Para_Base3->Input_Fmap_Row=2;
    Layer_Para_Base3->Input_Fmap_Col=5;
    Layer_Para_Base3->Output_Fmap_Channel=2;
    Layer_Para_Base3->Output_Fmap_Row=2;
    Layer_Para_Base3->Output_Fmap_Col=5;
    /*****************第3步:添加网络层**********************/
    OpenNNA_Add_Layer(Network, "Example", "xdd1", Layer_Para_Base1,Layer_Para_Example1, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Example", "xdd2", Layer_Para_Base2, Layer_Para_Example2,NULL, NULL);
    OpenNNA_Add_Layer(Network, "Example", "xdd3", Layer_Para_Base3, Layer_Para_Example3,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "ReLU", "xdd4", NULL, NULL,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "Dense", "xdd5", NULL, NULL,NULL, NULL);
    //OpenNNA_Add_Layer(Network, "Softmax", "xdd6", NULL, NULL,NULL, NULL);
    /*****************第4步:初始化神经网络**********************/
    OpenNNA_Init(Network);
    /*****************第5步:打印神经网络信息**********************/
    OpenNNA_Print_Network(Network);
    /*****************第6步:设置神经网络输入数据和输出数据**********************/
    data_t NN_Input_Fmap[2][2][5]={\
    {
                                               {0, 1, 2, 3, 4},
                                               {10, 11, 12, 13, 14},
                                       },
    {
                                               {100, 101, 102, 103, 104},
                                               {110, 111, 112, 113, 114},
                                       },
    };
    data_t NN_Output_Fmap[2][2][5]={0};
    /*****************第6步:神经网络推理**********************/
    OpenNNA_Printf("Begin Predict!\n");
    OpenNNA_Predict(Network, NN_Input_Fmap, NN_Output_Fmap);
    /*****************第7步:根据推理结果进行动作**********************/
    printf("Input fmap[0][0][0] = %d, fmap[0][0][1] = %d, fmap[0][0][2] = %d, fmap[0][0][3] = %d,fmap[0][0][4] = %d\n",\
    NN_Input_Fmap[0][0][0], NN_Input_Fmap[0][0][1], NN_Input_Fmap[0][0][2], NN_Input_Fmap[0][0][3], NN_Input_Fmap[0][0][4]);
    printf("Input fmap[0][1][0] = %d, fmap[0][1][1] = %d, fmap[0][1][2] = %d, fmap[0][0][3] = %d,fmap[0][0][4] = %d\n",\
    NN_Input_Fmap[0][1][0], NN_Input_Fmap[0][1][1], NN_Input_Fmap[0][1][2], NN_Input_Fmap[0][1][3], NN_Input_Fmap[0][1][4]);
    printf("Input fmap[1][0][0] = %d, fmap[1][0][1] = %d, fmap[1][0][2] = %d, fmap[1][0][3] = %d,fmap[1][0][4] = %d\n",\
    NN_Input_Fmap[1][0][0], NN_Input_Fmap[1][0][1], NN_Input_Fmap[1][0][2], NN_Input_Fmap[1][0][3], NN_Input_Fmap[1][0][4]);
    printf("Input fmap[1][1][0] = %d, fmap[1][1][1] = %d, fmap[1][1][2] = %d, fmap[1][0][3] = %d,fmap[1][0][4] = %d\n",\
    NN_Input_Fmap[1][1][0], NN_Input_Fmap[1][1][1], NN_Input_Fmap[1][1][2], NN_Input_Fmap[1][1][3], NN_Input_Fmap[1][1][4]);
    printf("\n\n");
    printf("Output fmap[0][0][0] = %d, fmap[0][0][1] = %d, fmap[0][0][2] = %d, fmap[0][0][3] = %d,fmap[0][0][4] = %d\n",\
    NN_Output_Fmap[0][0][0], NN_Output_Fmap[0][0][1], NN_Output_Fmap[0][0][2], NN_Output_Fmap[0][0][3], NN_Output_Fmap[0][0][4]);
    printf("Output fmap[0][1][0] = %d, fmap[0][1][1] = %d, fmap[0][1][2] = %d, fmap[0][1][3] = %d,fmap[0][1][4] = %d\n",\
    NN_Output_Fmap[0][1][0], NN_Output_Fmap[0][1][1], NN_Output_Fmap[0][1][2], NN_Output_Fmap[0][1][3], NN_Output_Fmap[0][1][4]);
    printf("Output fmap[1][0][0] = %d, fmap[1][0][1] = %d, fmap[1][0][2] = %d, fmap[1][0][3] = %d,fmap[1][0][4] = %d\n",\
    NN_Output_Fmap[1][0][0], NN_Output_Fmap[1][0][1], NN_Output_Fmap[1][0][2], NN_Output_Fmap[1][0][3], NN_Output_Fmap[1][0][4]);
    printf("Output fmap[1][1][0] = %d, fmap[1][1][1] = %d, fmap[1][1][2] = %d, fmap[1][0][3] = %d,fmap[1][0][4] = %d\n",\
    NN_Output_Fmap[1][1][0], NN_Output_Fmap[1][1][1], NN_Output_Fmap[1][1][2], NN_Output_Fmap[1][1][3], NN_Output_Fmap[1][1][4]);
    /*****************第8步:推理结束释放网络结构+申请的特征图堆内存**********************/
    OpenNNA_Free_Network(Network);
    return 0;
}