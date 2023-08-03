cmake_minimum_required(VERSION 3.10)
project(core C)

include_directories("./weights_bias_h")
include_directories("./")

set(CMAKE_C_STANDARD 99)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(core opennna_core.c opennna_core.h opennna_operator_example.c opennna_operator_example.h opennna_operator_dense.c opennna_operator_dense.h opennna_operator_relu.c opennna_operator_relu.h opennna_operator_softmax.h opennna_operator_softmax.c opennna_operator_conv2d.h opennna_operator_conv2d.c opennna_operator_padding.h opennna_operator_padding.c opennna_operator_maxpool.h opennna_operator_maxpool.c opennna_operator_avgpool.h opennna_operator_avgpool.c opennna_operator_relu6.h opennna_operator_relu6.c opennna_operator_dwconv2d.h opennna_operator_dwconv2d.c opennna_operator_leakyrelu.h opennna_operator_leakyrelu.c opennna_operator_tanh.h opennna_operator_tanh.c opennna_demo_mobilenet_0.25_128_int8.c opennna_demo_mobilenet_0.25_128_int8.c opennna_demo_mobilenet_0.25_128_int8.c opennna_demo_mobilenet_0.25_128_int8.c)

target_link_libraries(core m)
