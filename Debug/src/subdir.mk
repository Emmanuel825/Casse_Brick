################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/App.c \
../src/Brick.c \
../src/Casse-birque.c \
../src/Container.c \
../src/Player.c \
../src/mobile.c 

C_DEPS += \
./src/App.d \
./src/Brick.d \
./src/Casse-birque.d \
./src/Container.d \
./src/Player.d \
./src/mobile.d 

OBJS += \
./src/App.o \
./src/Brick.o \
./src/Casse-birque.o \
./src/Container.o \
./src/Player.o \
./src/mobile.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/App.d ./src/App.o ./src/Brick.d ./src/Brick.o ./src/Casse-birque.d ./src/Casse-birque.o ./src/Container.d ./src/Container.o ./src/Player.d ./src/Player.o ./src/mobile.d ./src/mobile.o

.PHONY: clean-src

