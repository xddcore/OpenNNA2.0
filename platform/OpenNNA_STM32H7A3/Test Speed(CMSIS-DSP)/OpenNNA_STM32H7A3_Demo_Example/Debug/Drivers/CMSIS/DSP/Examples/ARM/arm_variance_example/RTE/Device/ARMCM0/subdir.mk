################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/startup_ARMCM0.s 

C_SRCS += \
../Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/system_ARMCM0.c 

OBJS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/startup_ARMCM0.o \
./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/system_ARMCM0.o 

S_DEPS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/startup_ARMCM0.d 

C_DEPS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/system_ARMCM0.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/%.o: ../Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/%.s Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/%.o Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/%.su: ../Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/%.c Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/core" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/model" -I"/Users/xdd/STM32CubeIDE/workspace_1.10.1/OpenNNA_STM32H7A3_Demo_Example/Middlewares/OpenNNA2.0/operator" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_variance_example-2f-RTE-2f-Device-2f-ARMCM0

clean-Drivers-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_variance_example-2f-RTE-2f-Device-2f-ARMCM0:
	-$(RM) ./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/startup_ARMCM0.d ./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/startup_ARMCM0.o ./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/system_ARMCM0.d ./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/system_ARMCM0.o ./Drivers/CMSIS/DSP/Examples/ARM/arm_variance_example/RTE/Device/ARMCM0/system_ARMCM0.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_variance_example-2f-RTE-2f-Device-2f-ARMCM0

