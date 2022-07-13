import numpy as np
import tensorflow as tf
import tensorflow.keras as keras
from tensorflow.keras import models, layers, optimizers
import numpy as np
# 模型加载
# HWCN

model = tf.keras.models.load_model('./1660ti_cnn.h5')

weights = model.get_weights() #获取整个网络模型的全部参数
#print(weights)
print("layer 1 weights:",weights[0].shape)  #第一层的w
print("layer 1 bias:",weights[1].shape)  #第一层的b
print("layer 2 weights:",weights[2].shape)  #第二层的w
print("layer 2 bias:",weights[3].shape)  #第二层的b
print("layer 3 weights:",weights[4].shape)  #第3层的w
print("layer 3 bias:",weights[5].shape)  #第3层的b
print("layer 3 weights:",weights[6].shape)  #第4层的w
print("layer 3 bias:",weights[7].shape)  #第4层的b
 
cwd = "./conv1_weights.txt"
L1_Kernel_size = 3 #卷积核大小
L1_Kernel_channel = 1 #卷积核通道
L1_Kernel_number = 16 #卷积核数量
L1_bias_number = 16  #偏置数量
loadData0 = np.swapaxes(weights[0], 0, 2)
loadData1 = np.swapaxes(loadData0, 1, 3)
loadData2 = np.swapaxes(loadData1, 0, 1)
print("L1 weights shape",loadData2.shape)
txtfile0 = open(r'conv1_weights.txt', 'w',encoding='UTF-8')
for i in range(0,L1_Kernel_number):
    txtfile0.write("\t{\n")
    for j in range(0,L1_Kernel_channel):
        txtfile0.write("\t\t{\n")
        for k in range(0,L1_Kernel_size):
            txtfile0.write("\t\t\t{")
            for w in range(0,L1_Kernel_size):
               #txtfile.write(str(loadData2[i][j][k][w])+", ") 
               txtfile0.write("%8.20f"%(loadData2[i][j][k][w])+", ") 
            txtfile0.write("\t},\n")  
        txtfile0.write("\t\t},\n")
    txtfile0.write("\t\t\t},\n\n")
txtfile0.close()

L1_bias_number=16  #偏置数量
cwd = "./conv1_bias.txt"
data = weights[1]
txtfile1 = open(cwd, 'w',encoding='UTF-8')
txtfile1.write("\t{")
for i in range(0,L1_bias_number):
    #txtfile1.write(str(data[i])+", ")
    txtfile1.write("%8.20f"%(data[i])+", ")
txtfile1.write("\t}")
txtfile1.close()
#print(weights[1].shape)
    
    
cwd = "./conv3_weights.txt"
L3_Kernel_size = 3 #卷积核大小
L3_Kernel_channel = 16 #卷积核通道
L3_Kernel_number = 32 #卷积核数量
L3_bias_number = 32  #偏置数量
print("weights[2] shape:",weights[2].shape)
loadData0 = np.swapaxes(weights[2], 0, 2)
loadData1 = np.swapaxes(loadData0, 1, 3)
L3_loadData2 = np.swapaxes(loadData1, 0, 1)
print("L3 weights shape",L3_loadData2.shape)
print(L3_loadData2)
txtfile2 = open(r'conv3_weights.txt', 'w',encoding='UTF-8')
for i in range(0,L3_Kernel_number):
    txtfile2.write("\t{\n")
    for j in range(0,L3_Kernel_channel):
        txtfile2.write("\t\t{\n")
        for k in range(0,L3_Kernel_size):
            txtfile2.write("\t\t\t{")
            for w in range(0,L3_Kernel_size):
               #txtfile.write(str(loadData2[i][j][k][w])+", ") 
               txtfile2.write("%8.20f"%(L3_loadData2[i][j][k][w])+", ") 
            txtfile2.write("\t},\n")  
        txtfile2.write("\t\t},\n")
    txtfile2.write("\t\t\t},\n\n")
txtfile2.close()

L3_bias_number=32  #偏置数量
cwd = "./conv3_bias.txt"
data = weights[3]
txtfile3 = open(cwd, 'w',encoding='UTF-8')
txtfile3.write("\t{")
for i in range(0,L3_bias_number):
    #txtfile1.write(str(data[i])+", ")
    txtfile3.write("%8.20f"%(data[i])+", ")
txtfile3.write("\t}")
txtfile3.close()

cwd = "./dense5_weights.txt"
L5_input_fmap_size = 1152 #全连接层输入特征图大小
L5_neure_number = 64 #神经元数量
L5_output_fmap_size = 64 #输出特征图大小
print("weights[4] shape:",weights[4].shape)
L5_loadData2 = np.swapaxes(weights[4], 0, 1)
print("L3 weights shape",L5_loadData2.shape)
print(L5_loadData2)
txtfile2 = open(cwd, 'w',encoding='UTF-8')
for i in range(0,L5_neure_number):
    txtfile2.write("\t{")
    for j in range(0,L5_input_fmap_size):
        txtfile2.write("%8.20f"%(L5_loadData2[i][j])+", ") 
    txtfile2.write("\t\t\t},\n")
txtfile2.close()


cwd = "./dense5_bias.txt"
data = weights[5]
txtfile3 = open(cwd, 'w',encoding='UTF-8')
txtfile3.write("\t{")
for i in range(0,L5_neure_number):
    #txtfile1.write(str(data[i])+", ")
    txtfile3.write("%8.20f"%(data[i])+", ")
txtfile3.write("\t}")
txtfile3.close()

cwd = "./dense6_weights.txt"
L6_input_fmap_size = 64 #全连接层输入特征图大小
L6_neure_number = 10 #神经元数量
L6_output_fmap_size = 10 #输出特征图大小
print("weights[6] shape:",weights[6].shape)
L6_loadData2 = np.swapaxes(weights[6], 0, 1)
print("L6 weights shape",L6_loadData2.shape)
print(L5_loadData2)
txtfile2 = open(cwd, 'w',encoding='UTF-8')
for i in range(0,L6_neure_number):
    txtfile2.write("\t{")
    for j in range(0,L6_input_fmap_size):
        txtfile2.write("%8.20f"%(L6_loadData2[i][j])+", ") 
    txtfile2.write("\t\t\t},\n")
txtfile2.close()


cwd = "./dense6_bias.txt"
data = weights[7]
txtfile3 = open(cwd, 'w',encoding='UTF-8')
txtfile3.write("\t{")
for i in range(0,L6_neure_number):
    #txtfile1.write(str(data[i])+", ")
    txtfile3.write("%8.20f"%(data[i])+", ")
txtfile3.write("\t}")
txtfile3.close()
