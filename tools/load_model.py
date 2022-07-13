import tensorflow as tf
import tensorflow.keras as keras
from tensorflow.keras import models, layers, optimizers
import numpy as np
import datetime
#python 的标准库手册推荐在任何情况下尽量使用time.clock().
#只计算了程序运行CPU的时间，返回值是浮点数
import time
np.set_printoptions(threshold=np.inf)#取消打印长度限制
# 模型加载

model = tf.keras.models.load_model('./1660ti_cnn.h5')
 # 打印网络参数量
model.summary()      
image_value_5 = tf.io.read_file('./1.png')
image_value_2 = tf.io.read_file('./2.png')
image_value_0 = tf.io.read_file('./3.png')

#解码为tensor
image_value_5 = tf.io.decode_jpeg(image_value_5,channels = 1)
image_value_2 = tf.io.decode_jpeg(image_value_2,channels = 1)
image_value_0 = tf.io.decode_jpeg(image_value_0,channels = 1)

image_value_5 = tf.image.resize(image_value_5, (32,32))#改变像素值为32*32
image_value_2 = tf.image.resize(image_value_2, (32,32))#改变像素值为32*32
image_value_0 = tf.image.resize(image_value_0, (32,32))#改变像素值为32*32

#tensor转array
image_value_5 = image_value_5.numpy()/255.0
image_value_2 = image_value_2.numpy()
image_value_0 = image_value_0.numpy()
#转为三维数组
image_value_5 = image_value_5.reshape(-1,32,32,1)
image_value_2 = image_value_2.reshape(-1,32,32,1)
image_value_0 = image_value_0.reshape(-1,32,32,1)

for i in range(0,1):
    print("channel number:%d"%(i))
    print("\t\t{")
    for j in range(0,32):
        print("\t\t\t{",end="")
        for k in range(0,32):
           print(str(image_value_5[i][j][k])+", ",end="");
        print("\t\t\t}")
    print("\t\t}\n\n\n\n")
    
#其中Wclass_model为已经训练完毕的模型，这里获取该模型倒数第二层的输出
print(model.layers[0].output)
sub_model = tf.keras.models.Model(inputs = model.input,outputs = model.layers[6].output)
start =time.time()
predict_value_conv1 = sub_model.predict(image_value_2)
end = time.time()
sum_time = (end-start)
print((end-start))
loadData2 = predict_value_conv1.reshape(10)
'''
print("predict_value_conv1 shape:",predict_value_conv1.shape)
loadData1 = np.swapaxes(predict_value_conv1, 2, 3)
loadData2 = np.swapaxes(loadData1, 1, 2)
print("output fmap shape:",loadData2.shape)
#print(loadData2)
for i in range(0,32):
    print("channel number:%d"%(i))
    print("\t\t{")
    for j in range(0,6):
        print("\t\t\t{",end="")
        for k in range(0,6):
           print(str(loadData2[0][i][j][k])+", ",end="");
        print("\t\t\t}")
    print("\t\t}\n\n\n\n")
'''          
print("L6 Dense Result:")
print("{")
for i in range(0,10):
    print(str(loadData2[i])+", ");
print("}")
#输入模型进行预测
start =time.time()
predict_value_5 = model.predict(image_value_5,batch_size = None)
end = time.time()
sum_time = (end-start)
print((end-start))
predict_value_2 = model.predict(image_value_2,batch_size = None)
predict_value_0 = model.predict(image_value_0,batch_size = None)

print("")
print(np.argmax(predict_value_5))
print(np.argmax(predict_value_2))
print(np.argmax(predict_value_0))

















