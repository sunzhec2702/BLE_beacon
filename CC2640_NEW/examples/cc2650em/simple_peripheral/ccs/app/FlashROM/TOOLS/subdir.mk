################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
C:/ti/simplelink/ble_sdk_2_02_01_18/examples/cc2650em/simple_peripheral/ccs/config/app_ble.cfg 


# Each subdirectory must supply rules for building sources it contributes
configPkg/linker.cmd: C:/ti/simplelink/ble_sdk_2_02_01_18/examples/cc2650em/simple_peripheral/ccs/config/app_ble.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"/xs" --xdcpath= xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC2640F128 -r release -c --compileOptions "$<"
	@echo 'Finished building: $<'
	@echo ' '


