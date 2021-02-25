################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Card.cpp \
../Deck.cpp \
../Dice.cpp \
../DiceRoller.cpp \
../Driver.cpp \
../Fortify.cpp \
../GameStart.cpp \
../Hand.cpp \
../Map.cpp \
../MapLoader.cpp \
../Player.cpp \
../Reinforce.cpp \
../StartupPhase.cpp 

OBJS += \
./Card.o \
./Deck.o \
./Dice.o \
./DiceRoller.o \
./Driver.o \
./Fortify.o \
./GameStart.o \
./Hand.o \
./Map.o \
./MapLoader.o \
./Player.o \
./Reinforce.o \
./StartupPhase.o 

CPP_DEPS += \
./Card.d \
./Deck.d \
./Dice.d \
./DiceRoller.d \
./Driver.d \
./Fortify.d \
./GameStart.d \
./Hand.d \
./Map.d \
./MapLoader.d \
./Player.d \
./Reinforce.d \
./StartupPhase.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


