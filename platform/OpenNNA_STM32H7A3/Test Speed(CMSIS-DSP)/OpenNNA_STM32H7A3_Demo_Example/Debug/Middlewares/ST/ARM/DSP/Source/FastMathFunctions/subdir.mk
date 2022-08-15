################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/FastMathFunctions.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_f32.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q15.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q31.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_f32.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q15.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q31.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q15.c \
../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/FastMathFunctions.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_f32.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q15.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q31.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_f32.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q15.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q31.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q15.o \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/FastMathFunctions.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_f32.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q15.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q31.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_f32.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q15.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q31.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q15.d \
./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/ARM/DSP/Source/FastMathFunctions/%.o Middlewares/ST/ARM/DSP/Source/FastMathFunctions/%.su: ../Middlewares/ST/ARM/DSP/Source/FastMathFunctions/%.c Middlewares/ST/ARM/DSP/Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/core" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/model" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/operator" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/ARM/DSP/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-ARM-2f-DSP-2f-Source-2f-FastMathFunctions

clean-Middlewares-2f-ST-2f-ARM-2f-DSP-2f-Source-2f-FastMathFunctions:
	-$(RM) ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/FastMathFunctions.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/FastMathFunctions.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/FastMathFunctions.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_f32.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_f32.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_f32.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q15.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q15.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q15.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q31.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q31.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_cos_q31.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_f32.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_f32.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_f32.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q15.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q15.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q15.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q31.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q31.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sin_q31.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q15.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q15.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q15.su ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q31.d ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q31.o ./Middlewares/ST/ARM/DSP/Source/FastMathFunctions/arm_sqrt_q31.su

.PHONY: clean-Middlewares-2f-ST-2f-ARM-2f-DSP-2f-Source-2f-FastMathFunctions

