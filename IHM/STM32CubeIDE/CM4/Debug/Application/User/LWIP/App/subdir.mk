################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Dany/Documents/Github/ESE_Robotique/IHM/CM4/LWIP/App/lwip.c 

C_DEPS += \
./Application/User/LWIP/App/lwip.d 

OBJS += \
./Application/User/LWIP/App/lwip.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/LWIP/App/lwip.o: C:/Users/Dany/Documents/Github/ESE_Robotique/IHM/CM4/LWIP/App/lwip.c Application/User/LWIP/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../../../CM4/Core/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -I../../../CM4/LWIP/App -I../../../CM4/LWIP/Target -I../../../Middlewares/Third_Party/LwIP/src/include -I../../../Middlewares/Third_Party/LwIP/system -I../../../Drivers/BSP/Components/lan8742 -I../../../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../../../Middlewares/Third_Party/LwIP/src/include/lwip -I../../../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../../../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../../../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../../../Middlewares/Third_Party/LwIP/src/include/netif -I../../../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../../../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../../../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../../../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../../../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../../../Middlewares/Third_Party/LwIP/system/arch -I"C:/Users/Dany/Documents/Github/ESE_Robotique/IHM/STM32CubeIDE/CM4/Application/User/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-LWIP-2f-App

clean-Application-2f-User-2f-LWIP-2f-App:
	-$(RM) ./Application/User/LWIP/App/lwip.cyclo ./Application/User/LWIP/App/lwip.d ./Application/User/LWIP/App/lwip.o ./Application/User/LWIP/App/lwip.su

.PHONY: clean-Application-2f-User-2f-LWIP-2f-App

