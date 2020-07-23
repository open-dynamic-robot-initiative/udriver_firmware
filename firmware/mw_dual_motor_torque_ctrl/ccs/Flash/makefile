################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
-lrts2800_ml.lib \
"/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/fast/lib/32b/f28x/f2806x/2806xRevB_FastSpinROMSymbols.lib" \
"/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/iqmath/lib/f28x/32b/IQmath.lib" \
"./CodeStartBranch.obj" \
"./adc.obj" \
"./angle_comp.obj" \
"./clarke.obj" \
"./clk.obj" \
"./cpu.obj" \
"./drv8305.obj" \
"./enc.obj" \
"./filter_fo.obj" \
"./flash.obj" \
"./gpio.obj" \
"./hal_2mtr.obj" \
"./ipark.obj" \
"./memCopy.obj" \
"./osc.obj" \
"./park.obj" \
"./pid.obj" \
"./pie.obj" \
"./pll.obj" \
"./pwm.obj" \
"./pwr.obj" \
"./qep.obj" \
"./slip.obj" \
"./spi.obj" \
"./svgen.obj" \
"./timer.obj" \
"./usDelay.obj" \
"./user_2mtr.obj" \
"./wdog.obj" \
"./amd_motorware_ext/utils.obj" \
"./src/canapi.obj" \
"./src/dual_motor_torque_ctrl.obj" \
"./src/main_helper.obj" \
"./src/spintac.obj" \
"./src/virtualspring.obj" \
"/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/fast/lib/32b/f28x/EST_getIdq_pu.lib" \
"/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/ide/ccs/cmd/f2806x/F28069M.cmd" \
"/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/spintac/lib/32b/SpinTAC.lib" \
"/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src/F2806x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include amd_motorware_ext/subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include amd_motorware_ext/subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
dual_motor_torque_ctrl.out \

EXE_OUTPUTS__QUOTED += \
"dual_motor_torque_ctrl.out" \

BIN_OUTPUTS += \
dual_motor_torque_ctrl.hex \

BIN_OUTPUTS__QUOTED += \
"dual_motor_torque_ctrl.hex" \


# All Target
all: dual_motor_torque_ctrl.out

# Tool invocations
dual_motor_torque_ctrl.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number -z -m"dual_motor_torque_ctrl.map" --stack_size=0x3B0 --warn_sections -i"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/lib" -i"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --priority --reread_libs --disable_auto_rts --diag_suppress=16002 --xml_link_info="dual_motor_torque_ctrl_linkInfo.xml" --rom_model -o "dual_motor_torque_ctrl.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

dual_motor_torque_ctrl.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/hex2000"  -o "dual_motor_torque_ctrl.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "CodeStartBranch.obj" "adc.obj" "angle_comp.obj" "clarke.obj" "clk.obj" "cpu.obj" "drv8305.obj" "enc.obj" "filter_fo.obj" "flash.obj" "gpio.obj" "hal_2mtr.obj" "ipark.obj" "memCopy.obj" "osc.obj" "park.obj" "pid.obj" "pie.obj" "pll.obj" "pwm.obj" "pwr.obj" "qep.obj" "slip.obj" "spi.obj" "svgen.obj" "timer.obj" "usDelay.obj" "user_2mtr.obj" "wdog.obj" "amd_motorware_ext/utils.obj" "src/canapi.obj" "src/dual_motor_torque_ctrl.obj" "src/main_helper.obj" "src/spintac.obj" "src/virtualspring.obj" 
	-$(RM) "adc.d" "angle_comp.d" "clarke.d" "clk.d" "cpu.d" "drv8305.d" "enc.d" "filter_fo.d" "flash.d" "gpio.d" "hal_2mtr.d" "ipark.d" "memCopy.d" "osc.d" "park.d" "pid.d" "pie.d" "pll.d" "pwm.d" "pwr.d" "qep.d" "slip.d" "spi.d" "svgen.d" "timer.d" "user_2mtr.d" "wdog.d" "amd_motorware_ext/utils.d" "src/dual_motor_torque_ctrl.d" "src/main_helper.d" "src/spintac.d" "src/virtualspring.d" 
	-$(RM) "src/canapi.d" 
	-$(RM) "CodeStartBranch.d" "usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

