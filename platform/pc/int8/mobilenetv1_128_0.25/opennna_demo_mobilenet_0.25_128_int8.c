//
// Created by 董程森 on 2022/7/13.
//
//
// Created by 董程森 on 2022/7/7.
//
#include "opennna_core.h"
#include "stdio.h"
#include "L14_Conv2d_Bias.h"
#include "L15_DwConv2d_Weights.h"
/*****************OpenNNA Mobilenet alpha=0.25 128*128 实现ImageNet 1001分类示例**********************/
/*
 * Note:
 * Fmap, Weights, Bias = uint8
 * 每个conv都有padding，且padding =1，填充128
 */
int main() {
    /*****************第1步:创建神经网络对象**********************/
    struct layer * Network = OpenNNA_CreateNetwork();
    /*****************第2步:配置网络层参数**********************/
    //所有Padding都有的属性，只定义一次
    struct Layer_Para_Padding *Layer_Para_Padding_All_Network = OpenNNA_Malloc(sizeof(Layer_Para_Padding));
    Layer_Para_Padding_All_Network->padding = 1;
    Layer_Para_Padding_All_Network->padding_value = 128;

    //Padding(1)+L0 Conv2d
    struct Layer_Para_base *Layer_Para_Base0_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base0_Padding->Input_Fmap_Channel=3;
    Layer_Para_Base0_Padding->Input_Fmap_Row=128;
    Layer_Para_Base0_Padding->Input_Fmap_Col=128;
    Layer_Para_Base0_Padding->Output_Fmap_Channel=3;
    Layer_Para_Base0_Padding->Output_Fmap_Row=130;
    Layer_Para_Base0_Padding->Output_Fmap_Col=130;
    struct Layer_Para_base *Layer_Para_Base0 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d0 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base0->Input_Fmap_Channel=3;
    Layer_Para_Base0->Input_Fmap_Row=130;
    Layer_Para_Base0->Input_Fmap_Col=130;
    Layer_Para_Base0->Output_Fmap_Channel=8;
    Layer_Para_Base0->Output_Fmap_Row=64;
    Layer_Para_Base0->Output_Fmap_Col=64;
    Layer_Para_Conv2d0->kernel_row=3;
    Layer_Para_Conv2d0->kernel_col=3;
    Layer_Para_Conv2d0->kernel_channel=3;
    Layer_Para_Conv2d0->filters=8;
    Layer_Para_Conv2d0->strides_row=2;
    Layer_Para_Conv2d0->strides_col=2;
    Layer_Para_Conv2d0->Si = 0.0078125;
    Layer_Para_Conv2d0->Sw = 0.008882409892976284;
    Layer_Para_Conv2d0->Sb = 0.00006939382728887722;
    Layer_Para_Conv2d0->So = 0.023528477177023888;
    Layer_Para_Conv2d0->Zi = 128;
    Layer_Para_Conv2d0->Zw = 157;
    Layer_Para_Conv2d0->Zb = 0;
    Layer_Para_Conv2d0->Zo = 0;

    //Padding(1)+L1 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base1_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base1_Padding->Input_Fmap_Channel=8;
    Layer_Para_Base1_Padding->Input_Fmap_Row=64;
    Layer_Para_Base1_Padding->Input_Fmap_Col=64;
    Layer_Para_Base1_Padding->Output_Fmap_Channel=8;
    Layer_Para_Base1_Padding->Output_Fmap_Row=66;
    Layer_Para_Base1_Padding->Output_Fmap_Col=66;
    struct Layer_Para_base *Layer_Para_Base1 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d1 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base1->Input_Fmap_Channel=8;
    Layer_Para_Base1->Input_Fmap_Row=66;
    Layer_Para_Base1->Input_Fmap_Col=66;
    Layer_Para_Base1->Output_Fmap_Channel=8;
    Layer_Para_Base1->Output_Fmap_Row=64;
    Layer_Para_Base1->Output_Fmap_Col=64;
    Layer_Para_DWConv2d1->kernel_row=3;
    Layer_Para_DWConv2d1->kernel_col=3;
    Layer_Para_DWConv2d1->kernel_channel=8;
    Layer_Para_DWConv2d1->filters=1;
    Layer_Para_DWConv2d1->strides_row=1;
    Layer_Para_DWConv2d1->strides_col=1;
    Layer_Para_DWConv2d1->Si = 0.023528477177023888;
    Layer_Para_DWConv2d1->Sw = 0.08940034359693527;
    Layer_Para_DWConv2d1->Sb = 0.0021034537348896265;
    Layer_Para_DWConv2d1->So = 0.023528477177023888;
    Layer_Para_DWConv2d1->Zi = 0;
    Layer_Para_DWConv2d1->Zw = 204;
    Layer_Para_DWConv2d1->Zb = 0;
    Layer_Para_DWConv2d1->Zo = 0;

    //Padding(1)+L2 Conv2d
    struct Layer_Para_base *Layer_Para_Base2_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base2_Padding->Input_Fmap_Channel=8;
    Layer_Para_Base2_Padding->Input_Fmap_Row=64;
    Layer_Para_Base2_Padding->Input_Fmap_Col=64;
    Layer_Para_Base2_Padding->Output_Fmap_Channel=8;
    Layer_Para_Base2_Padding->Output_Fmap_Row=66;
    Layer_Para_Base2_Padding->Output_Fmap_Col=66;
    struct Layer_Para_base *Layer_Para_Base2 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d2 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base2->Input_Fmap_Channel=8;
    Layer_Para_Base2->Input_Fmap_Row=66;
    Layer_Para_Base2->Input_Fmap_Col=66;
    Layer_Para_Base2->Output_Fmap_Channel=16;
    Layer_Para_Base2->Output_Fmap_Row=64;
    Layer_Para_Base2->Output_Fmap_Col=64;
    Layer_Para_Conv2d2->kernel_row=1;
    Layer_Para_Conv2d2->kernel_col=1;
    Layer_Para_Conv2d2->kernel_channel=8;
    Layer_Para_Conv2d2->filters=16;
    Layer_Para_Conv2d2->strides_row=1;
    Layer_Para_Conv2d2->strides_col=1;
    Layer_Para_Conv2d2->Si = 0.023528477177023888;
    Layer_Para_Conv2d2->Sw = 0.016090909019112587;
    Layer_Para_Conv2d2->Sb = 0.0003785945591516793;
    Layer_Para_Conv2d2->So = 0.023528477177023888;
    Layer_Para_Conv2d2->Zi = 0;
    Layer_Para_Conv2d2->Zw = 120;
    Layer_Para_Conv2d2->Zb = 0;
    Layer_Para_Conv2d2->Zo = 0;

    //Padding(1)+L3 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base3_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base3_Padding->Input_Fmap_Channel=16;
    Layer_Para_Base3_Padding->Input_Fmap_Row=64;
    Layer_Para_Base3_Padding->Input_Fmap_Col=64;
    Layer_Para_Base3_Padding->Output_Fmap_Channel=16;
    Layer_Para_Base3_Padding->Output_Fmap_Row=66;
    Layer_Para_Base3_Padding->Output_Fmap_Col=66;
    struct Layer_Para_base *Layer_Para_Base3 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d3 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base3->Input_Fmap_Channel=16;
    Layer_Para_Base3->Input_Fmap_Row=66;
    Layer_Para_Base3->Input_Fmap_Col=66;
    Layer_Para_Base3->Output_Fmap_Channel=16;
    Layer_Para_Base3->Output_Fmap_Row=32;
    Layer_Para_Base3->Output_Fmap_Col=32;
    Layer_Para_DWConv2d3->kernel_row=3;
    Layer_Para_DWConv2d3->kernel_col=3;
    Layer_Para_DWConv2d3->kernel_channel=16;
    Layer_Para_DWConv2d3->filters=1;
    Layer_Para_DWConv2d3->strides_row=2;
    Layer_Para_DWConv2d3->strides_col=2;
    Layer_Para_DWConv2d3->Si = 0.023528477177023888;
    Layer_Para_DWConv2d3->Sw = 0.047994449734687805;
    Layer_Para_DWConv2d3->Sb = 0.0011292363051325083;
    Layer_Para_DWConv2d3->So = 0.023528477177023888;
    Layer_Para_DWConv2d3->Zi = 0;
    Layer_Para_DWConv2d3->Zw = 204;
    Layer_Para_DWConv2d3->Zb = 0;
    Layer_Para_DWConv2d3->Zo = 0;

    //Padding(1)+L4 Conv2d
    struct Layer_Para_base *Layer_Para_Base4_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base4_Padding->Input_Fmap_Channel=16;
    Layer_Para_Base4_Padding->Input_Fmap_Row=32;
    Layer_Para_Base4_Padding->Input_Fmap_Col=32;
    Layer_Para_Base4_Padding->Output_Fmap_Channel=16;
    Layer_Para_Base4_Padding->Output_Fmap_Row=34;
    Layer_Para_Base4_Padding->Output_Fmap_Col=34;
    struct Layer_Para_base *Layer_Para_Base4 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d4 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base4->Input_Fmap_Channel=16;
    Layer_Para_Base4->Input_Fmap_Row=34;
    Layer_Para_Base4->Input_Fmap_Col=34;
    Layer_Para_Base4->Output_Fmap_Channel=32;
    Layer_Para_Base4->Output_Fmap_Row=32;
    Layer_Para_Base4->Output_Fmap_Col=32;
    Layer_Para_Conv2d4->kernel_row=1;
    Layer_Para_Conv2d4->kernel_col=1;
    Layer_Para_Conv2d4->kernel_channel=16;
    Layer_Para_Conv2d4->filters=32;
    Layer_Para_Conv2d4->strides_row=1;
    Layer_Para_Conv2d4->strides_col=1;
    Layer_Para_Conv2d4->Si = 0.023528477177023888;
    Layer_Para_Conv2d4->Sw = 0.04767826199531555;
    Layer_Para_Conv2d4->Sb = 0.001121796783991158;
    Layer_Para_Conv2d4->So = 0.023528477177023888;
    Layer_Para_Conv2d4->Zi = 0;
    Layer_Para_Conv2d4->Zw = 120;
    Layer_Para_Conv2d4->Zb = 0;
    Layer_Para_Conv2d4->Zo = 0;

    //Padding(1)+L5 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base5_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base5_Padding->Input_Fmap_Channel=32;
    Layer_Para_Base5_Padding->Input_Fmap_Row=32;
    Layer_Para_Base5_Padding->Input_Fmap_Col=32;
    Layer_Para_Base5_Padding->Output_Fmap_Channel=32;
    Layer_Para_Base5_Padding->Output_Fmap_Row=34;
    Layer_Para_Base5_Padding->Output_Fmap_Col=34;
    struct Layer_Para_base *Layer_Para_Base5 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d5 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base5->Input_Fmap_Channel=32;
    Layer_Para_Base5->Input_Fmap_Row=34;
    Layer_Para_Base5->Input_Fmap_Col=34;
    Layer_Para_Base5->Output_Fmap_Channel=32;
    Layer_Para_Base5->Output_Fmap_Row=32;
    Layer_Para_Base5->Output_Fmap_Col=32;
    Layer_Para_DWConv2d5->kernel_row=3;
    Layer_Para_DWConv2d5->kernel_col=3;
    Layer_Para_DWConv2d5->kernel_channel=32;
    Layer_Para_DWConv2d5->filters=1;
    Layer_Para_DWConv2d5->strides_row=1;
    Layer_Para_DWConv2d5->strides_col=1;
    Layer_Para_DWConv2d5->Si = 0.023528477177023888;
    Layer_Para_DWConv2d5->Sw = 0.034030552953481674;
    Layer_Para_DWConv2d5->Sb = 0.0008006871212273836;
    Layer_Para_DWConv2d5->So = 0.023528477177023888;
    Layer_Para_DWConv2d5->Zi = 0;
    Layer_Para_DWConv2d5->Zw = 149;
    Layer_Para_DWConv2d5->Zb = 0;
    Layer_Para_DWConv2d5->Zo = 0;

    //Padding(1)+L6 Conv2d
    struct Layer_Para_base *Layer_Para_Base6_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base6_Padding->Input_Fmap_Channel=32;
    Layer_Para_Base6_Padding->Input_Fmap_Row=32;
    Layer_Para_Base6_Padding->Input_Fmap_Col=32;
    Layer_Para_Base6_Padding->Output_Fmap_Channel=32;
    Layer_Para_Base6_Padding->Output_Fmap_Row=34;
    Layer_Para_Base6_Padding->Output_Fmap_Col=34;
    struct Layer_Para_base *Layer_Para_Base6 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d6 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base6->Input_Fmap_Channel=32;
    Layer_Para_Base6->Input_Fmap_Row=34;
    Layer_Para_Base6->Input_Fmap_Col=34;
    Layer_Para_Base6->Output_Fmap_Channel=32;
    Layer_Para_Base6->Output_Fmap_Row=32;
    Layer_Para_Base6->Output_Fmap_Col=32;
    Layer_Para_Conv2d6->kernel_row=1;
    Layer_Para_Conv2d6->kernel_col=1;
    Layer_Para_Conv2d6->kernel_channel=32;
    Layer_Para_Conv2d6->filters=32;
    Layer_Para_Conv2d6->strides_row=1;
    Layer_Para_Conv2d6->strides_col=1;
    Layer_Para_Conv2d6->Si = 0.023528477177023888;
    Layer_Para_Conv2d6->Sw = 0.023293426260352135;
    Layer_Para_Conv2d6->Sb = 0.0005480588297359645;
    Layer_Para_Conv2d6->So = 0.023528477177023888;
    Layer_Para_Conv2d6->Zi = 0;
    Layer_Para_Conv2d6->Zw = 61;
    Layer_Para_Conv2d6->Zb = 0;
    Layer_Para_Conv2d6->Zo = 0;


    //Padding(1)+L7 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base7_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base7_Padding->Input_Fmap_Channel=32;
    Layer_Para_Base7_Padding->Input_Fmap_Row=32;
    Layer_Para_Base7_Padding->Input_Fmap_Col=32;
    Layer_Para_Base7_Padding->Output_Fmap_Channel=32;
    Layer_Para_Base7_Padding->Output_Fmap_Row=34;
    Layer_Para_Base7_Padding->Output_Fmap_Col=34;
    struct Layer_Para_base *Layer_Para_Base7 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d7 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base7->Input_Fmap_Channel=32;
    Layer_Para_Base7->Input_Fmap_Row=34;
    Layer_Para_Base7->Input_Fmap_Col=34;
    Layer_Para_Base7->Output_Fmap_Channel=32;
    Layer_Para_Base7->Output_Fmap_Row=16;
    Layer_Para_Base7->Output_Fmap_Col=16;
    Layer_Para_DWConv2d7->kernel_row=3;
    Layer_Para_DWConv2d7->kernel_col=3;
    Layer_Para_DWConv2d7->kernel_channel=32;
    Layer_Para_DWConv2d7->filters=1;
    Layer_Para_DWConv2d7->strides_row=2;
    Layer_Para_DWConv2d7->strides_col=2;
    Layer_Para_DWConv2d7->Si = 0.023528477177023888;
    Layer_Para_DWConv2d7->Sw = 0.012287606485188007;
    Layer_Para_DWConv2d7->Sb = 0.0002891086624003947;
    Layer_Para_DWConv2d7->So = 0.023528477177023888;
    Layer_Para_DWConv2d7->Zi = 0;
    Layer_Para_DWConv2d7->Zw = 122;
    Layer_Para_DWConv2d7->Zb = 0;
    Layer_Para_DWConv2d7->Zo = 0;


    //Padding(1)+L8 Conv2d
    struct Layer_Para_base *Layer_Para_Base8_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base8_Padding->Input_Fmap_Channel=32;
    Layer_Para_Base8_Padding->Input_Fmap_Row=16;
    Layer_Para_Base8_Padding->Input_Fmap_Col=16;
    Layer_Para_Base8_Padding->Output_Fmap_Channel=32;
    Layer_Para_Base8_Padding->Output_Fmap_Row=18;
    Layer_Para_Base8_Padding->Output_Fmap_Col=18;
    struct Layer_Para_base *Layer_Para_Base8 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d8 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base8->Input_Fmap_Channel=32;
    Layer_Para_Base8->Input_Fmap_Row=18;
    Layer_Para_Base8->Input_Fmap_Col=18;
    Layer_Para_Base8->Output_Fmap_Channel=64;
    Layer_Para_Base8->Output_Fmap_Row=16;
    Layer_Para_Base8->Output_Fmap_Col=16;
    Layer_Para_Conv2d8->kernel_row=1;
    Layer_Para_Conv2d8->kernel_col=1;
    Layer_Para_Conv2d8->kernel_channel=32;
    Layer_Para_Conv2d8->filters=64;
    Layer_Para_Conv2d8->strides_row=1;
    Layer_Para_Conv2d8->strides_col=1;
    Layer_Para_Conv2d8->Si = 0.023528477177023888;
    Layer_Para_Conv2d8->Sw = 0.012042458169162273;
    Layer_Para_Conv2d8->Sb = 0.00028334069065749645;
    Layer_Para_Conv2d8->So = 0.023528477177023888;
    Layer_Para_Conv2d8->Zi = 0;
    Layer_Para_Conv2d8->Zw = 148;
    Layer_Para_Conv2d8->Zb = 0;
    Layer_Para_Conv2d8->Zo = 0;


    //Padding(1)+L9 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base9_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base9_Padding->Input_Fmap_Channel=64;
    Layer_Para_Base9_Padding->Input_Fmap_Row=16;
    Layer_Para_Base9_Padding->Input_Fmap_Col=16;
    Layer_Para_Base9_Padding->Output_Fmap_Channel=64;
    Layer_Para_Base9_Padding->Output_Fmap_Row=18;
    Layer_Para_Base9_Padding->Output_Fmap_Col=18;
    struct Layer_Para_base *Layer_Para_Base9 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d9 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base9->Input_Fmap_Channel=64;
    Layer_Para_Base9->Input_Fmap_Row=18;
    Layer_Para_Base9->Input_Fmap_Col=18;
    Layer_Para_Base9->Output_Fmap_Channel=64;
    Layer_Para_Base9->Output_Fmap_Row=16;
    Layer_Para_Base9->Output_Fmap_Col=16;
    Layer_Para_DWConv2d9->kernel_row=3;
    Layer_Para_DWConv2d9->kernel_col=3;
    Layer_Para_DWConv2d9->kernel_channel=64;
    Layer_Para_DWConv2d9->filters=1;
    Layer_Para_DWConv2d9->strides_row=1;
    Layer_Para_DWConv2d9->strides_col=1;
    Layer_Para_DWConv2d9->Si = 0.023528477177023888;
    Layer_Para_DWConv2d9->Sw = 0.030628934502601624;
    Layer_Para_DWConv2d9->Sb = 0.0007206521695479751;
    Layer_Para_DWConv2d9->So = 0.023528477177023888;
    Layer_Para_DWConv2d9->Zi = 0;
    Layer_Para_DWConv2d9->Zw = 102;
    Layer_Para_DWConv2d9->Zb = 0;
    Layer_Para_DWConv2d9->Zo = 0;


    //Padding(1)+L10 Conv2d
    struct Layer_Para_base *Layer_Para_Base10_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base10_Padding->Input_Fmap_Channel=64;
    Layer_Para_Base10_Padding->Input_Fmap_Row=16;
    Layer_Para_Base10_Padding->Input_Fmap_Col=16;
    Layer_Para_Base10_Padding->Output_Fmap_Channel=64;
    Layer_Para_Base10_Padding->Output_Fmap_Row=18;
    Layer_Para_Base10_Padding->Output_Fmap_Col=18;
    struct Layer_Para_base *Layer_Para_Base10 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d10 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base10->Input_Fmap_Channel=64;
    Layer_Para_Base10->Input_Fmap_Row=18;
    Layer_Para_Base10->Input_Fmap_Col=18;
    Layer_Para_Base10->Output_Fmap_Channel=64;
    Layer_Para_Base10->Output_Fmap_Row=16;
    Layer_Para_Base10->Output_Fmap_Col=16;
    Layer_Para_Conv2d10->kernel_row=1;
    Layer_Para_Conv2d10->kernel_col=1;
    Layer_Para_Conv2d10->kernel_channel=64;
    Layer_Para_Conv2d10->filters=64;
    Layer_Para_Conv2d10->strides_row=1;
    Layer_Para_Conv2d10->strides_col=1;
    Layer_Para_Conv2d10->Si = 0.023528477177023888;
    Layer_Para_Conv2d10->Sw = 0.01593947969377041;
    Layer_Para_Conv2d10->Sb = 0.0003750316973309964;
    Layer_Para_Conv2d10->So = 0.023528477177023888;
    Layer_Para_Conv2d10->Zi = 0;
    Layer_Para_Conv2d10->Zw = 89;
    Layer_Para_Conv2d10->Zb = 0;
    Layer_Para_Conv2d10->Zo = 0;


    //Padding(1)+L11 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base11_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base11_Padding->Input_Fmap_Channel=64;
    Layer_Para_Base11_Padding->Input_Fmap_Row=16;
    Layer_Para_Base11_Padding->Input_Fmap_Col=16;
    Layer_Para_Base11_Padding->Output_Fmap_Channel=64;
    Layer_Para_Base11_Padding->Output_Fmap_Row=18;
    Layer_Para_Base11_Padding->Output_Fmap_Col=18;
    struct Layer_Para_base *Layer_Para_Base11 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d11 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base11->Input_Fmap_Channel=64;
    Layer_Para_Base11->Input_Fmap_Row=18;
    Layer_Para_Base11->Input_Fmap_Col=18;
    Layer_Para_Base11->Output_Fmap_Channel=64;
    Layer_Para_Base11->Output_Fmap_Row=8;
    Layer_Para_Base11->Output_Fmap_Col=8;
    Layer_Para_DWConv2d11->kernel_row=3;
    Layer_Para_DWConv2d11->kernel_col=3;
    Layer_Para_DWConv2d11->kernel_channel=64;
    Layer_Para_DWConv2d11->filters=1;
    Layer_Para_DWConv2d11->strides_row=2;
    Layer_Para_DWConv2d11->strides_col=2;
    Layer_Para_DWConv2d11->Si = 0.023528477177023888;
    Layer_Para_DWConv2d11->Sw = 0.008241243660449982;
    Layer_Para_DWConv2d11->Sb = 0.0007206521695479751;
    Layer_Para_DWConv2d11->So = 0.023528477177023888;
    Layer_Para_DWConv2d11->Zi = 0;
    Layer_Para_DWConv2d11->Zw = 125;
    Layer_Para_DWConv2d11->Zb = 0;
    Layer_Para_DWConv2d11->Zo = 0;


    //Padding(1)+L12 Conv2d
    struct Layer_Para_base *Layer_Para_Base12_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base12_Padding->Input_Fmap_Channel=64;
    Layer_Para_Base12_Padding->Input_Fmap_Row=8;
    Layer_Para_Base12_Padding->Input_Fmap_Col=8;
    Layer_Para_Base12_Padding->Output_Fmap_Channel=64;
    Layer_Para_Base12_Padding->Output_Fmap_Row=10;
    Layer_Para_Base12_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base12 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d12 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base12->Input_Fmap_Channel=64;
    Layer_Para_Base12->Input_Fmap_Row=10;
    Layer_Para_Base12->Input_Fmap_Col=10;
    Layer_Para_Base12->Output_Fmap_Channel=128;
    Layer_Para_Base12->Output_Fmap_Row=8;
    Layer_Para_Base12->Output_Fmap_Col=8;
    Layer_Para_Conv2d12->kernel_row=1;
    Layer_Para_Conv2d12->kernel_col=1;
    Layer_Para_Conv2d12->kernel_channel=64;
    Layer_Para_Conv2d12->filters=128;
    Layer_Para_Conv2d12->strides_row=1;
    Layer_Para_Conv2d12->strides_col=1;
    Layer_Para_Conv2d12->Si = 0.023528477177023888;
    Layer_Para_Conv2d12->Sw = 0.013338613323867321;
    Layer_Para_Conv2d12->Sb = 0.0003138372558169067;
    Layer_Para_Conv2d12->So = 0.023528477177023888;
    Layer_Para_Conv2d12->Zi = 0;
    Layer_Para_Conv2d12->Zw = 158;
    Layer_Para_Conv2d12->Zb = 0;
    Layer_Para_Conv2d12->Zo = 0;


    //Padding(1)+L13 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base13_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base13_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base13_Padding->Input_Fmap_Row=8;
    Layer_Para_Base13_Padding->Input_Fmap_Col=8;
    Layer_Para_Base13_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base13_Padding->Output_Fmap_Row=10;
    Layer_Para_Base13_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base13 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d13 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base13->Input_Fmap_Channel=128;
    Layer_Para_Base13->Input_Fmap_Row=10;
    Layer_Para_Base13->Input_Fmap_Col=10;
    Layer_Para_Base13->Output_Fmap_Channel=128;
    Layer_Para_Base13->Output_Fmap_Row=8;
    Layer_Para_Base13->Output_Fmap_Col=8;
    Layer_Para_DWConv2d13->kernel_row=3;
    Layer_Para_DWConv2d13->kernel_col=3;
    Layer_Para_DWConv2d13->kernel_channel=128;
    Layer_Para_DWConv2d13->filters=1;
    Layer_Para_DWConv2d13->strides_row=1;
    Layer_Para_DWConv2d13->strides_col=1;
    Layer_Para_DWConv2d13->Si = 0.023528477177023888;
    Layer_Para_DWConv2d13->Sw = 0.029106900095939636;
    Layer_Para_DWConv2d13->Sb = 0.0006848410121165216;
    Layer_Para_DWConv2d13->So = 0.023528477177023888;
    Layer_Para_DWConv2d13->Zi = 0;
    Layer_Para_DWConv2d13->Zw = 122;
    Layer_Para_DWConv2d13->Zb = 0;
    Layer_Para_DWConv2d13->Zo = 0;


    //Padding(1)+L14 Conv2d
    struct Layer_Para_base *Layer_Para_Base14_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base14_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base14_Padding->Input_Fmap_Row=8;
    Layer_Para_Base14_Padding->Input_Fmap_Col=8;
    Layer_Para_Base14_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base14_Padding->Output_Fmap_Row=10;
    Layer_Para_Base14_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base14 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d14 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base14->Input_Fmap_Channel=128;
    Layer_Para_Base14->Input_Fmap_Row=10;
    Layer_Para_Base14->Input_Fmap_Col=10;
    Layer_Para_Base14->Output_Fmap_Channel=128;
    Layer_Para_Base14->Output_Fmap_Row=8;
    Layer_Para_Base14->Output_Fmap_Col=8;
    Layer_Para_Conv2d14->kernel_row=1;
    Layer_Para_Conv2d14->kernel_col=1;
    Layer_Para_Conv2d14->kernel_channel=128;
    Layer_Para_Conv2d14->filters=128;
    Layer_Para_Conv2d14->strides_row=1;
    Layer_Para_Conv2d14->strides_col=1;
    Layer_Para_Conv2d14->Si = 0.023528477177023888;
    Layer_Para_Conv2d14->Sw = 0.0071434746496379375;
    Layer_Para_Conv2d14->Sb = 0.00016807507199700922;
    Layer_Para_Conv2d14->So = 0.023528477177023888;
    Layer_Para_Conv2d14->Zi = 0;
    Layer_Para_Conv2d14->Zw = 134;
    Layer_Para_Conv2d14->Zb = 0;
    Layer_Para_Conv2d14->Zo = 0;


    //Padding(1)+L15 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base15_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base15_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base15_Padding->Input_Fmap_Row=8;
    Layer_Para_Base15_Padding->Input_Fmap_Col=8;
    Layer_Para_Base15_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base15_Padding->Output_Fmap_Row=10;
    Layer_Para_Base15_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base15 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d15 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base15->Input_Fmap_Channel=128;
    Layer_Para_Base15->Input_Fmap_Row=10;
    Layer_Para_Base15->Input_Fmap_Col=10;
    Layer_Para_Base15->Output_Fmap_Channel=128;
    Layer_Para_Base15->Output_Fmap_Row=8;
    Layer_Para_Base15->Output_Fmap_Col=8;
    Layer_Para_DWConv2d15->kernel_row=3;
    Layer_Para_DWConv2d15->kernel_col=3;
    Layer_Para_DWConv2d15->kernel_channel=128;
    Layer_Para_DWConv2d15->filters=1;
    Layer_Para_DWConv2d15->strides_row=1;
    Layer_Para_DWConv2d15->strides_col=1;
    Layer_Para_DWConv2d15->Si = 0.023528477177023888;
    Layer_Para_DWConv2d15->Sw = 0.030950011685490608;
    Layer_Para_DWConv2d15->Sb = 0.0007282065926119685;
    Layer_Para_DWConv2d15->So = 0.023528477177023888;
    Layer_Para_DWConv2d15->Zi = 0;
    Layer_Para_DWConv2d15->Zw = 165;
    Layer_Para_DWConv2d15->Zb = 0;
    Layer_Para_DWConv2d15->Zo = 0;


    //Padding(1)+L16 Conv2d
    struct Layer_Para_base *Layer_Para_Base16_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base16_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base16_Padding->Input_Fmap_Row=8;
    Layer_Para_Base16_Padding->Input_Fmap_Col=8;
    Layer_Para_Base16_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base16_Padding->Output_Fmap_Row=10;
    Layer_Para_Base16_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base16 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d16 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base16->Input_Fmap_Channel=128;
    Layer_Para_Base16->Input_Fmap_Row=10;
    Layer_Para_Base16->Input_Fmap_Col=10;
    Layer_Para_Base16->Output_Fmap_Channel=128;
    Layer_Para_Base16->Output_Fmap_Row=8;
    Layer_Para_Base16->Output_Fmap_Col=8;
    Layer_Para_Conv2d16->kernel_row=1;
    Layer_Para_Conv2d16->kernel_col=1;
    Layer_Para_Conv2d16->kernel_channel=128;
    Layer_Para_Conv2d16->filters=128;
    Layer_Para_Conv2d16->strides_row=1;
    Layer_Para_Conv2d16->strides_col=1;
    Layer_Para_Conv2d16->Si = 0.023528477177023888;
    Layer_Para_Conv2d16->Sw = 0.0076089780777692795;
    Layer_Para_Conv2d16->Sb = 0.00017902767285704613;
    Layer_Para_Conv2d16->So = 0.023528477177023888;
    Layer_Para_Conv2d16->Zi = 0;
    Layer_Para_Conv2d16->Zw = 134;
    Layer_Para_Conv2d16->Zb = 0;
    Layer_Para_Conv2d16->Zo = 0;


    //Padding(1)+L17 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base17_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base17_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base17_Padding->Input_Fmap_Row=8;
    Layer_Para_Base17_Padding->Input_Fmap_Col=8;
    Layer_Para_Base17_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base17_Padding->Output_Fmap_Row=10;
    Layer_Para_Base17_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base17 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d17 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base17->Input_Fmap_Channel=128;
    Layer_Para_Base17->Input_Fmap_Row=10;
    Layer_Para_Base17->Input_Fmap_Col=10;
    Layer_Para_Base17->Output_Fmap_Channel=128;
    Layer_Para_Base17->Output_Fmap_Row=8;
    Layer_Para_Base17->Output_Fmap_Col=8;
    Layer_Para_DWConv2d17->kernel_row=3;
    Layer_Para_DWConv2d17->kernel_col=3;
    Layer_Para_DWConv2d17->kernel_channel=128;
    Layer_Para_DWConv2d17->filters=1;
    Layer_Para_DWConv2d17->strides_row=1;
    Layer_Para_DWConv2d17->strides_col=1;
    Layer_Para_DWConv2d17->Si = 0.023528477177023888;
    Layer_Para_DWConv2d17->Sw = 0.021228810772299767;
    Layer_Para_DWConv2d17->Sb = 0.0007282065926119685;
    Layer_Para_DWConv2d17->So = 0.023528477177023888;
    Layer_Para_DWConv2d17->Zi = 0;
    Layer_Para_DWConv2d17->Zw = 120;
    Layer_Para_DWConv2d17->Zb = 0;
    Layer_Para_DWConv2d17->Zo = 0;


    //Padding(1)+L18 Conv2d
    struct Layer_Para_base *Layer_Para_Base18_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base18_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base18_Padding->Input_Fmap_Row=8;
    Layer_Para_Base18_Padding->Input_Fmap_Col=8;
    Layer_Para_Base18_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base18_Padding->Output_Fmap_Row=10;
    Layer_Para_Base18_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base18 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d18 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base18->Input_Fmap_Channel=128;
    Layer_Para_Base18->Input_Fmap_Row=10;
    Layer_Para_Base18->Input_Fmap_Col=10;
    Layer_Para_Base18->Output_Fmap_Channel=128;
    Layer_Para_Base18->Output_Fmap_Row=8;
    Layer_Para_Base18->Output_Fmap_Col=8;
    Layer_Para_Conv2d18->kernel_row=1;
    Layer_Para_Conv2d18->kernel_col=1;
    Layer_Para_Conv2d18->kernel_channel=128;
    Layer_Para_Conv2d18->filters=128;
    Layer_Para_Conv2d18->strides_row=1;
    Layer_Para_Conv2d18->strides_col=1;
    Layer_Para_Conv2d18->Si = 0.023528477177023888;
    Layer_Para_Conv2d18->Sw = 0.011091439984738827 ;
    Layer_Para_Conv2d18->Sb = 0.0002609647053759545;
    Layer_Para_Conv2d18->So = 0.023528477177023888;
    Layer_Para_Conv2d18->Zi = 0;
    Layer_Para_Conv2d18->Zw = 146;
    Layer_Para_Conv2d18->Zb = 0;
    Layer_Para_Conv2d18->Zo = 0;


    //Padding(1)+L19 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base19_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base19_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base19_Padding->Input_Fmap_Row=8;
    Layer_Para_Base19_Padding->Input_Fmap_Col=8;
    Layer_Para_Base19_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base19_Padding->Output_Fmap_Row=10;
    Layer_Para_Base19_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base19 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d19 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base19->Input_Fmap_Channel=128;
    Layer_Para_Base19->Input_Fmap_Row=10;
    Layer_Para_Base19->Input_Fmap_Col=10;
    Layer_Para_Base19->Output_Fmap_Channel=128;
    Layer_Para_Base19->Output_Fmap_Row=8;
    Layer_Para_Base19->Output_Fmap_Col=8;
    Layer_Para_DWConv2d19->kernel_row=3;
    Layer_Para_DWConv2d19->kernel_col=3;
    Layer_Para_DWConv2d19->kernel_channel=128;
    Layer_Para_DWConv2d19->filters=1;
    Layer_Para_DWConv2d19->strides_row=1;
    Layer_Para_DWConv2d19->strides_col=1;
    Layer_Para_DWConv2d19->Si = 0.023528477177023888;
    Layer_Para_DWConv2d19->Sw = 0.022778166458010674;
    Layer_Para_DWConv2d19->Sb = 0.0005359355709515512;
    Layer_Para_DWConv2d19->So = 0.023528477177023888;
    Layer_Para_DWConv2d19->Zi = 0;
    Layer_Para_DWConv2d19->Zw = 135;
    Layer_Para_DWConv2d19->Zb = 0;
    Layer_Para_DWConv2d19->Zo = 0;


    //Padding(1)+L20 Conv2d
    struct Layer_Para_base *Layer_Para_Base20_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base20_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base20_Padding->Input_Fmap_Row=8;
    Layer_Para_Base20_Padding->Input_Fmap_Col=8;
    Layer_Para_Base20_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base20_Padding->Output_Fmap_Row=10;
    Layer_Para_Base20_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base20 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d20 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base20->Input_Fmap_Channel=128;
    Layer_Para_Base20->Input_Fmap_Row=10;
    Layer_Para_Base20->Input_Fmap_Col=10;
    Layer_Para_Base20->Output_Fmap_Channel=128;
    Layer_Para_Base20->Output_Fmap_Row=8;
    Layer_Para_Base20->Output_Fmap_Col=8;
    Layer_Para_Conv2d20->kernel_row=1;
    Layer_Para_Conv2d20->kernel_col=1;
    Layer_Para_Conv2d20->kernel_channel=128;
    Layer_Para_Conv2d20->filters=128;
    Layer_Para_Conv2d20->strides_row=1;
    Layer_Para_Conv2d20->strides_col=1;
    Layer_Para_Conv2d20->Si = 0.023528477177023888;
    Layer_Para_Conv2d20->Sw = 0.007225683890283108;
    Layer_Para_Conv2d20->Sb = 0.00017000932712107897;
    Layer_Para_Conv2d20->So = 0.023528477177023888;
    Layer_Para_Conv2d20->Zi = 0;
    Layer_Para_Conv2d20->Zw = 131;
    Layer_Para_Conv2d20->Zb = 0;
    Layer_Para_Conv2d20->Zo = 0;


    //Padding(1)+L21 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base21_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base21_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base21_Padding->Input_Fmap_Row=8;
    Layer_Para_Base21_Padding->Input_Fmap_Col=8;
    Layer_Para_Base21_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base21_Padding->Output_Fmap_Row=10;
    Layer_Para_Base21_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base21 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d21 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base21->Input_Fmap_Channel=128;
    Layer_Para_Base21->Input_Fmap_Row=10;
    Layer_Para_Base21->Input_Fmap_Col=10;
    Layer_Para_Base21->Output_Fmap_Channel=128;
    Layer_Para_Base21->Output_Fmap_Row=8;
    Layer_Para_Base21->Output_Fmap_Col=8;
    Layer_Para_DWConv2d21->kernel_row=3;
    Layer_Para_DWConv2d21->kernel_col=3;
    Layer_Para_DWConv2d21->kernel_channel=128;
    Layer_Para_DWConv2d21->filters=1;
    Layer_Para_DWConv2d21->strides_row=1;
    Layer_Para_DWConv2d21->strides_col=1;
    Layer_Para_DWConv2d21->Si = 0.023528477177023888;
    Layer_Para_DWConv2d21->Sw = 0.018258025869727135;
    Layer_Para_DWConv2d21->Sb = 0.00042958356789313257;
    Layer_Para_DWConv2d21->So = 0.023528477177023888;
    Layer_Para_DWConv2d21->Zi = 0;
    Layer_Para_DWConv2d21->Zw = 147;
    Layer_Para_DWConv2d21->Zb = 0;
    Layer_Para_DWConv2d21->Zo = 0;


    //Padding(1)+L22 Conv2d
    struct Layer_Para_base *Layer_Para_Base22_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base22_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base22_Padding->Input_Fmap_Row=8;
    Layer_Para_Base22_Padding->Input_Fmap_Col=8;
    Layer_Para_Base22_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base22_Padding->Output_Fmap_Row=10;
    Layer_Para_Base22_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base22 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d22 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base22->Input_Fmap_Channel=128;
    Layer_Para_Base22->Input_Fmap_Row=10;
    Layer_Para_Base22->Input_Fmap_Col=10;
    Layer_Para_Base22->Output_Fmap_Channel=128;
    Layer_Para_Base22->Output_Fmap_Row=8;
    Layer_Para_Base22->Output_Fmap_Col=8;
    Layer_Para_Conv2d22->kernel_row=1;
    Layer_Para_Conv2d22->kernel_col=1;
    Layer_Para_Conv2d22->kernel_channel=128;
    Layer_Para_Conv2d22->filters=128;
    Layer_Para_Conv2d22->strides_row=1;
    Layer_Para_Conv2d22->strides_col=1;
    Layer_Para_Conv2d22->Si = 0.023528477177023888;
    Layer_Para_Conv2d22->Sw = 0.007789616007357836;
    Layer_Para_Conv2d22->Sb = 0.00018327780708204955;
    Layer_Para_Conv2d22->So = 0.023528477177023888;
    Layer_Para_Conv2d22->Zi = 0;
    Layer_Para_Conv2d22->Zw = 109;
    Layer_Para_Conv2d22->Zb = 0;
    Layer_Para_Conv2d22->Zo = 0;


    //Padding(1)+L23 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base23_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base23_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base23_Padding->Input_Fmap_Row=8;
    Layer_Para_Base23_Padding->Input_Fmap_Col=8;
    Layer_Para_Base23_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base23_Padding->Output_Fmap_Row=10;
    Layer_Para_Base23_Padding->Output_Fmap_Col=10;
    struct Layer_Para_base *Layer_Para_Base23 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d23 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base23->Input_Fmap_Channel=128;
    Layer_Para_Base23->Input_Fmap_Row=10;
    Layer_Para_Base23->Input_Fmap_Col=10;
    Layer_Para_Base23->Output_Fmap_Channel=128;
    Layer_Para_Base23->Output_Fmap_Row=4;
    Layer_Para_Base23->Output_Fmap_Col=4;
    Layer_Para_DWConv2d23->kernel_row=3;
    Layer_Para_DWConv2d23->kernel_col=3;
    Layer_Para_DWConv2d23->kernel_channel=128;
    Layer_Para_DWConv2d23->filters=1;
    Layer_Para_DWConv2d23->strides_row=2;
    Layer_Para_DWConv2d23->strides_col=2;
    Layer_Para_DWConv2d23->Si = 0.023528477177023888;
    Layer_Para_DWConv2d23->Sw = 0.005769345909357071;
    Layer_Para_DWConv2d23->Sb = 0.00013574391778092831;
    Layer_Para_DWConv2d23->So = 0.023528477177023888;
    Layer_Para_DWConv2d23->Zi = 0;
    Layer_Para_DWConv2d23->Zw = 125;
    Layer_Para_DWConv2d23->Zb = 0;
    Layer_Para_DWConv2d23->Zo = 0;


    //Padding(1)+L24 Conv2d
    struct Layer_Para_base *Layer_Para_Base24_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base24_Padding->Input_Fmap_Channel=128;
    Layer_Para_Base24_Padding->Input_Fmap_Row=4;
    Layer_Para_Base24_Padding->Input_Fmap_Col=4;
    Layer_Para_Base24_Padding->Output_Fmap_Channel=128;
    Layer_Para_Base24_Padding->Output_Fmap_Row=6;
    Layer_Para_Base24_Padding->Output_Fmap_Col=6;
    struct Layer_Para_base *Layer_Para_Base24 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d24 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base24->Input_Fmap_Channel=128;
    Layer_Para_Base24->Input_Fmap_Row=6;
    Layer_Para_Base24->Input_Fmap_Col=6;
    Layer_Para_Base24->Output_Fmap_Channel=256;
    Layer_Para_Base24->Output_Fmap_Row=4;
    Layer_Para_Base24->Output_Fmap_Col=4;
    Layer_Para_Conv2d24->kernel_row=1;
    Layer_Para_Conv2d24->kernel_col=1;
    Layer_Para_Conv2d24->kernel_channel=128;
    Layer_Para_Conv2d24->filters=256;
    Layer_Para_Conv2d24->strides_row=1;
    Layer_Para_Conv2d24->strides_col=1;
    Layer_Para_Conv2d24->Si = 0.023528477177023888;
    Layer_Para_Conv2d24->Sw = 0.009962311014533043;
    Layer_Para_Conv2d24->Sb = 0.00023439800133928657 ;
    Layer_Para_Conv2d24->So = 0.023528477177023888;
    Layer_Para_Conv2d24->Zi = 0;
    Layer_Para_Conv2d24->Zw = 113;
    Layer_Para_Conv2d24->Zb = 0;
    Layer_Para_Conv2d24->Zo = 0;


    //Padding(1)+L25 Depthwise Conv2d
    struct Layer_Para_base *Layer_Para_Base25_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base25_Padding->Input_Fmap_Channel=256;
    Layer_Para_Base25_Padding->Input_Fmap_Row=4;
    Layer_Para_Base25_Padding->Input_Fmap_Col=4;
    Layer_Para_Base25_Padding->Output_Fmap_Channel=256;
    Layer_Para_Base25_Padding->Output_Fmap_Row=6;
    Layer_Para_Base25_Padding->Output_Fmap_Col=6;
    struct Layer_Para_base *Layer_Para_Base25 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_DWConv2d *Layer_Para_DWConv2d25 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base25->Input_Fmap_Channel=256;
    Layer_Para_Base25->Input_Fmap_Row=6;
    Layer_Para_Base25->Input_Fmap_Col=6;
    Layer_Para_Base25->Output_Fmap_Channel=256;
    Layer_Para_Base25->Output_Fmap_Row=4;
    Layer_Para_Base25->Output_Fmap_Col=4;
    Layer_Para_DWConv2d25->kernel_row=3;
    Layer_Para_DWConv2d25->kernel_col=3;
    Layer_Para_DWConv2d25->kernel_channel=256;
    Layer_Para_DWConv2d25->filters=1;
    Layer_Para_DWConv2d25->strides_row=1;
    Layer_Para_DWConv2d25->strides_col=1;
    Layer_Para_DWConv2d25->Si = 0.023528477177023888;
    Layer_Para_DWConv2d25->Sw = 0.02579006366431713;
    Layer_Para_DWConv2d25->Sb = 0.0006068009533919394;
    Layer_Para_DWConv2d25->So = 0.023528477177023888;
    Layer_Para_DWConv2d25->Zi = 0;
    Layer_Para_DWConv2d25->Zw = 165;
    Layer_Para_DWConv2d25->Zb = 0;
    Layer_Para_DWConv2d25->Zo = 0;


    //Padding(1)+L26 Conv2d
    struct Layer_Para_base *Layer_Para_Base26_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base26_Padding->Input_Fmap_Channel=256;
    Layer_Para_Base26_Padding->Input_Fmap_Row=4;
    Layer_Para_Base26_Padding->Input_Fmap_Col=4;
    Layer_Para_Base26_Padding->Output_Fmap_Channel=256;
    Layer_Para_Base26_Padding->Output_Fmap_Row=6;
    Layer_Para_Base26_Padding->Output_Fmap_Col=6;
    struct Layer_Para_base *Layer_Para_Base26 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d26 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base26->Input_Fmap_Channel=256;
    Layer_Para_Base26->Input_Fmap_Row=6;
    Layer_Para_Base26->Input_Fmap_Col=6;
    Layer_Para_Base26->Output_Fmap_Channel=256;
    Layer_Para_Base26->Output_Fmap_Row=4;
    Layer_Para_Base26->Output_Fmap_Col=4;
    Layer_Para_Conv2d26->kernel_row=1;
    Layer_Para_Conv2d26->kernel_col=1;
    Layer_Para_Conv2d26->kernel_channel=256;
    Layer_Para_Conv2d26->filters=256;
    Layer_Para_Conv2d26->strides_row=1;
    Layer_Para_Conv2d26->strides_col=1;
    Layer_Para_Conv2d26->Si = 0.023528477177023888;
    Layer_Para_Conv2d26->Sw = 0.023383529856801033;
    Layer_Para_Conv2d26->Sb = 0.0005501788691617548;
    Layer_Para_Conv2d26->So = 0.023528477177023888;
    Layer_Para_Conv2d26->Zi = 0;
    Layer_Para_Conv2d26->Zw = 144;
    Layer_Para_Conv2d26->Zb = 0;
    Layer_Para_Conv2d26->Zo = 0;

    //L27 AvgPool
    struct Layer_Para_base *Layer_Para_Base27 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_AvgPool *Layer_Para_AvgPool27 = OpenNNA_Malloc(sizeof(Layer_Para_AvgPool));
    Layer_Para_Base27->Input_Fmap_Channel=256;
    Layer_Para_Base27->Input_Fmap_Row=4;
    Layer_Para_Base27->Input_Fmap_Col=4;
    Layer_Para_Base27->Output_Fmap_Channel=256;
    Layer_Para_Base27->Output_Fmap_Row=1;
    Layer_Para_Base27->Output_Fmap_Col=1;

    Layer_Para_AvgPool27->strides_col=2;
    Layer_Para_AvgPool27->strides_row=2;
    Layer_Para_AvgPool27->kernel_row=4;
    Layer_Para_AvgPool27->kernel_col=4;

    //Padding(1)+L28 Conv2d
    struct Layer_Para_base *Layer_Para_Base28_Padding = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    Layer_Para_Base28_Padding->Input_Fmap_Channel=256;
    Layer_Para_Base28_Padding->Input_Fmap_Row=1;
    Layer_Para_Base28_Padding->Input_Fmap_Col=1;
    Layer_Para_Base28_Padding->Output_Fmap_Channel=256;
    Layer_Para_Base28_Padding->Output_Fmap_Row=3;
    Layer_Para_Base28_Padding->Output_Fmap_Col=3;
    struct Layer_Para_base *Layer_Para_Base28 = OpenNNA_Malloc(sizeof(Layer_Para_Base));
    struct Layer_Para_Conv2d *Layer_Para_Conv2d28 = OpenNNA_Malloc(sizeof(Layer_Para_Conv2d));
    Layer_Para_Base28->Input_Fmap_Channel=256;
    Layer_Para_Base28->Input_Fmap_Row=3;
    Layer_Para_Base28->Input_Fmap_Col=3;
    Layer_Para_Base28->Output_Fmap_Channel=1001;
    Layer_Para_Base28->Output_Fmap_Row=1;
    Layer_Para_Base28->Output_Fmap_Col=1;
    Layer_Para_Conv2d28->kernel_row=1;
    Layer_Para_Conv2d28->kernel_col=1;
    Layer_Para_Conv2d28->kernel_channel=256;
    Layer_Para_Conv2d28->filters=1001;
    Layer_Para_Conv2d28->strides_row=1;
    Layer_Para_Conv2d28->strides_col=1;
    Layer_Para_Conv2d28->Si = 0.023528477177023888;
    Layer_Para_Conv2d28->Sw = 0.005540293175727129;
    Layer_Para_Conv2d28->Sb = 0.00013035465963184834;
    Layer_Para_Conv2d28->So = 0.023528477177023888;
    Layer_Para_Conv2d28->Zi = 0;
    Layer_Para_Conv2d28->Zw = 94;
    Layer_Para_Conv2d28->Zb = 0;
    Layer_Para_Conv2d28->Zo = 0;
    //Mobile net 0.25 128 END!!!
    /*****************第3步:设置神经网络输入数据和输出数据**********************/
#include "weights_bias_h/L0_Conv2d_Weights.h"
#include "weights_bias_h/L0_Conv2d_Bias.h"
#include "weights_bias_h/L1_DwConv2d_Weights.h"
#include "weights_bias_h/L1_DwConv2d_Bias.h"
#include "weights_bias_h/L2_Conv2d_Weights.h"
#include "weights_bias_h/L2_Conv2d_Bias.h"
#include "weights_bias_h/L3_DwConv2d_Weights.h"
#include "weights_bias_h/L3_DwConv2d_Bias.h"
#include "weights_bias_h/L4_Conv2d_Weights.h"
#include "weights_bias_h/L4_Conv2d_Bias.h"
#include "weights_bias_h/L5_DwConv2d_Weights.h"
#include "weights_bias_h/L5_DwConv2d_Bias.h"
#include "weights_bias_h/L6_Conv2d_Weights.h"
#include "weights_bias_h/L6_Conv2d_Bias.h"
#include "weights_bias_h/L7_DwConv2d_Weights.h"
#include "weights_bias_h/L7_DwConv2d_Bias.h"
#include "weights_bias_h/L8_Conv2d_Weights.h"
#include "weights_bias_h/L8_Conv2d_Bias.h"
#include "weights_bias_h/L9_DwConv2d_Weights.h"
#include "weights_bias_h/L9_DwConv2d_Bias.h"
#include "weights_bias_h/L10_Conv2d_Weights.h"
#include "weights_bias_h/L10_Conv2d_Bias.h"
#include "weights_bias_h/L11_DwConv2d_Weights.h"
#include "weights_bias_h/L11_DwConv2d_Bias.h"
#include "weights_bias_h/L12_Conv2d_Weights.h"
#include "weights_bias_h/L12_Conv2d_Bias.h"
#include "weights_bias_h/L13_DwConv2d_Weights.h"
#include "weights_bias_h/L13_DwConv2d_Bias.h"
#include "weights_bias_h/L14_Conv2d_Weights.h"
#include "weights_bias_h/L15_DwConv2d_Bias.h"
#include "weights_bias_h/L16_Conv2d_Weights.h"
#include "weights_bias_h/L16_Conv2d_Bias.h"
#include "weights_bias_h/L17_DwConv2d_Weights.h"
#include "weights_bias_h/L17_DwConv2d_Bias.h"
#include "weights_bias_h/L18_Conv2d_Weights.h"
#include "weights_bias_h/L18_Conv2d_Bias.h"
#include "weights_bias_h/L19_DwConv2d_Weights.h"
#include "weights_bias_h/L19_DwConv2d_Bias.h"
#include "weights_bias_h/L20_Conv2d_Weights.h"
#include "weights_bias_h/L20_Conv2d_Bias.h"
#include "weights_bias_h/L21_DwConv2d_Weights.h"
#include "weights_bias_h/L21_DwConv2d_Bias.h"
#include "weights_bias_h/L22_Conv2d_Weights.h"
#include "weights_bias_h/L22_Conv2d_Bias.h"
#include "weights_bias_h/L23_DwConv2d_Weights.h"
#include "weights_bias_h/L23_DwConv2d_Bias.h"
#include "weights_bias_h/L24_Conv2d_Weights.h"
#include "weights_bias_h/L24_Conv2d_Bias.h"
#include "weights_bias_h/L25_DwConv2d_Weights.h"
#include "weights_bias_h/L25_DwConv2d_Bias.h"
#include "weights_bias_h/L26_Conv2d_Weights.h"
#include "weights_bias_h/L26_Conv2d_Bias.h"
#include "weights_bias_h/L28_Conv2d_Weights.h"
#include "weights_bias_h/L28_Conv2d_Bias.h"

    /*****************第4步:添加网络层**********************/
    OpenNNA_Add_Layer(Network, "Padding", "Mobilenet(0.25,128)", Layer_Para_Base0_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base0,Layer_Para_Conv2d0, L0_Conv2d_Weights, L0_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base1_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base1,Layer_Para_DWConv2d1, L1_DwConv2d_Weights, L1_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base2_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base2,Layer_Para_Conv2d2, L2_Conv2d_Weights, L2_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base3_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base3,Layer_Para_DWConv2d3, L3_DwConv2d_Weights, L3_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base4_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base4,Layer_Para_Conv2d4, L4_Conv2d_Weights, L4_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base5_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base5,Layer_Para_DWConv2d5, L5_DwConv2d_Weights, L5_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base6_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base6,Layer_Para_Conv2d6, L6_Conv2d_Weights, L6_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base7_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base7,Layer_Para_DWConv2d7, L7_DwConv2d_Weights, L7_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base8_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base8,Layer_Para_Conv2d8, L8_Conv2d_Weights, L8_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base9_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base9,Layer_Para_DWConv2d9, L9_DwConv2d_Weights, L9_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base10_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base10,Layer_Para_Conv2d10, L10_Conv2d_Weights, L10_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base11_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base11,Layer_Para_DWConv2d11, L11_DwConv2d_Weights, L11_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base12_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base12,Layer_Para_Conv2d12, L12_Conv2d_Weights, L12_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base13_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base13,Layer_Para_DWConv2d13, L13_DwConv2d_Weights, L13_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base14_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base14,Layer_Para_Conv2d14, L14_Conv2d_Weights, L14_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base15_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base15,Layer_Para_DWConv2d15, L15_DwConv2d_Weights, L15_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base16_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base16,Layer_Para_Conv2d16, L16_Conv2d_Weights, L16_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base17_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base17,Layer_Para_DWConv2d17, L17_DwConv2d_Weights, L17_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base18_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base18,Layer_Para_Conv2d18, L18_Conv2d_Weights, L18_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base19_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base19,Layer_Para_DWConv2d19, L19_DwConv2d_Weights, L19_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base20_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base20,Layer_Para_Conv2d20, L20_Conv2d_Weights, L20_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base21_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base21,Layer_Para_DWConv2d21, L21_DwConv2d_Weights, L21_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base22_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base22,Layer_Para_Conv2d22, L22_Conv2d_Weights, L22_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base23_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base23,Layer_Para_DWConv2d23, L23_DwConv2d_Weights, L23_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base24_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base24,Layer_Para_Conv2d24, L24_Conv2d_Weights, L24_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base25_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Depthwise Conv2d", "Chengsen", Layer_Para_Base25,Layer_Para_DWConv2d25, L25_DwConv2d_Weights, L25_DwConv2d_Bias);
    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base26_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base26,Layer_Para_Conv2d26, L26_Conv2d_Weights, L26_Conv2d_Bias);

    OpenNNA_Add_Layer(Network, "AvgPool", "Future", Layer_Para_Base27,Layer_Para_AvgPool27, NULL, NULL);

    OpenNNA_Add_Layer(Network, "Padding", "Chengsen", Layer_Para_Base28_Padding,Layer_Para_Padding_All_Network, NULL, NULL);
    OpenNNA_Add_Layer(Network, "Conv2d", "Chengsen", Layer_Para_Base28,Layer_Para_Conv2d28, L28_Conv2d_Weights, L28_Conv2d_Bias);

    /*****************第5步:初始化神经网络**********************/
    OpenNNA_Init(Network);
    /*****************第6步:打印神经网络信息**********************/
    #if(DEBUG==1)
        OpenNNA_Print_Network(Network);
    #endif
    while(1);
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
        printf("[%d]%d,   ",i,NN_Output_Fmap[0][0][i]);
    }
    printf("\n");
    /*****************第10步:推理结束释放网络结构+申请的特征图堆内存**********************/
    OpenNNA_Free_Network(&Network);
    return 0;
}