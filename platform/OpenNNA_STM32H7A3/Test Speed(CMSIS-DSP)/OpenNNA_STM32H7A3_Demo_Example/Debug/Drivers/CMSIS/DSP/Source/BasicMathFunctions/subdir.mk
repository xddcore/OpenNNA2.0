################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q7.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q15.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q7.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q7.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q15.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q7.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q7.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q15.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q7.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/BasicMathFunctions/%.o Drivers/CMSIS/DSP/Source/BasicMathFunctions/%.su: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/%.c Drivers/CMSIS/DSP/Source/BasicMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/core" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/model" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/operator" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-BasicMathFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-BasicMathFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q7.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q7.su
	-$(RM) ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q15.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q15.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q15.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.su ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q7.d ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q7.o ./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q7.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-BasicMathFunctions
