################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RaspberryServoControl.cpp \
../src/teleVRServoControl.cpp 

OBJS += \
./src/RaspberryServoControl.o \
./src/teleVRServoControl.o 

CPP_DEPS += \
./src/RaspberryServoControl.d \
./src/teleVRServoControl.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\SysGCC\Raspberry\arm-linux-gnueabihf\sysroot\usr\local\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


