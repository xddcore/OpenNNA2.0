################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.c \
../Middlewares/OpenNNA2.0/model/opennna_demo_example.c 

OBJS += \
./Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.o \
./Middlewares/OpenNNA2.0/model/opennna_demo_example.o 

C_DEPS += \
./Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.d \
./Middlewares/OpenNNA2.0/model/opennna_demo_example.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.o: ../Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.c Middlewares/OpenNNA2.0/model/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -D__FPU_PRESENT=1 -D__FPU_USED=1 -D_TARGET_FPU_VFP -c -I../Core/Inc -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/core" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/model" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/operator" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/ARM/DSP/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/OpenNNA2.0/model/%.o Middlewares/OpenNNA2.0/model/%.su: ../Middlewares/OpenNNA2.0/model/%.c Middlewares/OpenNNA2.0/model/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -D__FPU_PRESENT=1 -D__FPU_USED=1 -D_TARGET_FPU_VFP -c -I../Core/Inc -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/core" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/model" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/operator" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/ARM/DSP/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-OpenNNA2-2e-0-2f-model

clean-Middlewares-2f-OpenNNA2-2e-0-2f-model:
	-$(RM) ./Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.d ./Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.o ./Middlewares/OpenNNA2.0/model/opennna_demo_conv(OpenNNA-Paper)-mnist.su ./Middlewares/OpenNNA2.0/model/opennna_demo_example.d ./Middlewares/OpenNNA2.0/model/opennna_demo_example.o ./Middlewares/OpenNNA2.0/model/opennna_demo_example.su

.PHONY: clean-Middlewares-2f-OpenNNA2-2e-0-2f-model

