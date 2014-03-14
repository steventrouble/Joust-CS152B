################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bitmap.c \
../src/lcd.c \
../src/sleep.c \
../src/tft_demo.c \
../src/xtft.c \
../src/xtft_g.c \
../src/xtft_sinit.c 

OBJS += \
./src/bitmap.o \
./src/lcd.o \
./src/sleep.o \
./src/tft_demo.o \
./src/xtft.o \
./src/xtft_g.o \
./src/xtft_sinit.o 

C_DEPS += \
./src/bitmap.d \
./src/lcd.d \
./src/sleep.d \
./src/tft_demo.d \
./src/xtft.d \
./src/xtft_g.d \
./src/xtft_sinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../custom_bsp/microblaze_0/include -mxl-pattern-compare -mcpu=v7.30.b -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


