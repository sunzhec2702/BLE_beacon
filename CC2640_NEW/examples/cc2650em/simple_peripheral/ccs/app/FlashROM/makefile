################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := 

# All of the sources participating in the build are defined here
-include sources.mk
-include TOOLS/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: simple_peripheral_cc2650em_app.out

# Tool invocations
simple_peripheral_cc2650em_app.out: 
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	256 0 "simple_peripheral_cc2650em_app.map" "simple_peripheral_cc2650em_app.out" /lib /include 10247-D 16002-D "simple_peripheral_cc2650em_app_linkInfo.xml"  "simple_peripheral_cc2650em_app.out"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_FILES)$(GEN_OPTS)$(OBJS)$(GEN_MISC_FILES)$(GEN_CMDS)$(GEN_MISC_DIRS) simple_peripheral_cc2650em_app.out
	-@echo ' '

post-build:
	--order MS --memwidth=8 --romwidth=8 --intel -o      simple_peripheral_cc2650em_app.hex simple_peripheral_cc2650em_app.out
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
