################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
toogle\ led\ lab.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
toogle\ led\ lab.list \

OBJCOPY_HEX += \
toogle\ led\ lab.hex \

OBJCOPY_BIN += \
toogle\ led\ lab.bin \


# All Target
all: toogle\ led\ lab.elf secondary-outputs

# Tool invocations
toogle\ led\ lab.elf: $(OBJS) $(USER_OBJS) D:\Embedded\ Systems\keroles\material\unit_03\Assignments\Lesson\ 1\platform\ header\toogle\ led\ lab\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "toogle led lab.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Embedded Systems\keroles\material\unit_03\Assignments\Lesson 1\platform header\toogle led lab\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="toogle led lab.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

toogle\ led\ lab.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "toogle led lab.list"
	@echo 'Finished building: $@'
	@echo ' '

toogle\ led\ lab.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "toogle led lab.hex"
	@echo 'Finished building: $@'
	@echo ' '

toogle\ led\ lab.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "toogle led lab.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
