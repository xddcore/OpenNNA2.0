import os 
import tensorflow as tf 
from PIL import Image  #注意Image,后面会用到
import matplotlib.pyplot as plt 
import numpy as np

i = 0

cwd='./Fnt0_9/'
classes=[] #标签存储
for root, dirs, files in os.walk(cwd):
    print(dirs) #当前路径下所有子目录
    classes = dirs; #获取标签名
    break;
writer= tf.io.TFRecordWriter("Fnt0_9.tfrecords") #要生成的文件

for index,name in enumerate(classes):
    class_path = cwd + name + '/'
    for img_name in os.listdir(class_path): 
        img_path=class_path+img_name #每一个图片的地址
        '''
        img=Image.open(img_path)
        img= img.resize((32,32))
        img_float = img.astype('uint8')/255.0
        img_raw=img_float.tobytes()#将图片转化为二进制格式
        '''
        image_value = tf.io.read_file(img_path)

        #解码为tensor
        image_value_decode = tf.io.decode_jpeg(image_value,channels = 1)

        image_value_32b = tf.image.resize(image_value_decode, (32,32))#改变像素值为32*32

        #tensor转array
        #print(image_value_32b)
        #print(type(image_value_32b))
        image_value_32b_numpy = image_value_32b.numpy()
        #print(image_value_32b_numpy)
        #print(type(image_value_32b_numpy))
        img_raw = image_value_32b_numpy.tobytes()#将图片转化为二进制格式
        
        example = tf.train.Example(
        features=tf.train.Features(
        feature={
            "label": tf.train.Feature(int64_list=tf.train.Int64List(value=[index])),
            'img_raw': tf.train.Feature(bytes_list=tf.train.BytesList(value=[img_raw]))
        }
        )
        ) #example对象对label和image数据进行封装
        writer.write(example.SerializeToString())  #序列化为字符串
        i = i + 1
        print("已写入"+str(i)+"张图片")
writer.close()