################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-890920673:
	@$(MAKE) --no-print-directory -Onone -f TOOLS/subdir_rules.mk build-890920673-inproc

build-890920673-inproc: C:/ti/simplelink/ble_sdk_2_02_01_18/examples/cc2650em/simple_peripheral/ccs/config/app_ble.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/xs" --xdcpath= xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC2640F128 -r release -c --compileOptions "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-890920673 C:/ti/simplelink/ble_sdk_2_02_01_18/examples/cc2650em/simple_peripheral/ccs/config/app_ble.cfg
configPkg/compiler.opt: build-890920673
configPkg/: build-890920673


