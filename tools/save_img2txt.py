import numpy as np
import tensorflow as tf
import tensorflow.keras as keras
from tensorflow.keras import models, layers, optimizers
import numpy as np

image_value_5 = tf.io.read_file('./3.png')

#解码为tensor
image_value_5 = tf.io.decode_jpeg(image_value_5,channels = 1)


image_value_5 = tf.image.resize(image_value_5, (32,32))#改变像素值为32*32


#tensor转array
image_value_5 = image_value_5.numpy()
loadData1 = np.swapaxes(image_value_5, 0, 2)
loadData2 = np.swapaxes(loadData1, 1, 2)

print(loadData2.shape)
col_number = 32

txtfile = open(r'image1.txt', 'w',encoding='UTF-8')
for i in range(0,1):
    txtfile.write("\t{\n")
    for j in range(0,col_number):
        txtfile.write("\t\t{")
        for k in range(0,col_number):
            #txtfile.write(str(loadData2[i][j][k])+", ") 
            txtfile.write("%8.20f"%(loadData2[i][j][k])+", ") 
        txtfile.write("},\n")
    txtfile.write("\t},\n\n")
txtfile.close()
