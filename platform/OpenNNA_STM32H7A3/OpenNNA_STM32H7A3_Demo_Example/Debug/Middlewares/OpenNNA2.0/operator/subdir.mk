################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/OpenNNA2.0/operator/opennna_operator_avgpool.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_conv2d.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_dense.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_dwconv2d.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_example.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_leakyrelu.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_maxpool.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_padding.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_relu.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_relu6.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_softmax.c \
../Middlewares/OpenNNA2.0/operator/opennna_operator_tanh.c 

OBJS += \
./Middlewares/OpenNNA2.0/operator/opennna_operator_avgpool.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_conv2d.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_dense.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_dwconv2d.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_example.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_leakyrelu.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_maxpool.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_padding.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_relu.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_relu6.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_softmax.o \
./Middlewares/OpenNNA2.0/operator/opennna_operator_tanh.o 

C_DEPS += \
./Middlewares/OpenNNA2.0/operator/opennna_operator_avgpool.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_conv2d.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_dense.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_dwconv2d.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_example.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_leakyrelu.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_maxpool.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_padding.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_relu.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_relu6.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_softmax.d \
./Middlewares/OpenNNA2.0/operator/opennna_operator_tanh.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/OpenNNA2.0/operator/%.o Middlewares/OpenNNA2.0/operator/%.su: ../Middlewares/OpenNNA2.0/operator/%.c Middlewares/OpenNNA2.0/operator/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/core" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/model" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/operator" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-OpenNNA2-2e-0-2f-operator

clean-Middlewares-2f-OpenNNA2-2e-0-2f-operator:
	-$(RM) ./Middlewares/OpenNNA2.0/operator/opennna_operator_avgpool.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_avgpool.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_avgpool.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_conv2d.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_conv2d.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_conv2d.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_dense.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_dense.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_dense.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_dwconv2d.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_dwconv2d.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_dwconv2d.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_example.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_example.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_example.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_leakyrelu.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_leakyrelu.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_leakyrelu.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_maxpool.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_maxpool.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_maxpool.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_padding.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_padding.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_padding.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_relu.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_relu.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_relu.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_relu6.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_relu6.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_relu6.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_softmax.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_softmax.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_softmax.su ./Middlewares/OpenNNA2.0/operator/opennna_operator_tanh.d ./Middlewares/OpenNNA2.0/operator/opennna_operator_tanh.o ./Middlewares/OpenNNA2.0/operator/opennna_operator_tanh.su

.PHONY: clean-Middlewares-2f-OpenNNA2-2e-0-2f-operator

