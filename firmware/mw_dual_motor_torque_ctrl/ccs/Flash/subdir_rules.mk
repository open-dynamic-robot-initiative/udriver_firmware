################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CodeStartBranch.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/cpu/src/32b/f28x/f2806x/CodeStartBranch.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

adc.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/adc/src/32b/f28x/f2806x/adc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

angle_comp.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/angle_comp/src/32b/angle_comp.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

clarke.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/clarke/src/32b/clarke.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

clk.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/clk/src/32b/f28x/f2806x/clk.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

cpu.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/cpu/src/32b/f28x/f2806x/cpu.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drv8305.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/drvic/drv8305/src/32b/f28x/f2806x/drv8305.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

enc.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/enc/src/32b/enc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

filter_fo.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/filter/src/32b/filter_fo.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

flash.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/flash/src/32b/f28x/f2806x/flash.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

gpio.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/gpio/src/32b/f28x/f2806x/gpio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hal_2mtr.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/hal_2mtr.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ipark.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/ipark/src/32b/ipark.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

memCopy.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/memCopy/src/memCopy.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

osc.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/osc/src/32b/f28x/f2806x/osc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

park.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/park/src/32b/park.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pid.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/pid/src/32b/pid.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pie.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/pie/src/32b/f28x/f2806x/pie.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pll.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/pll/src/32b/f28x/f2806x/pll.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pwm.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/pwm/src/32b/f28x/f2806x/pwm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pwr.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/pwr/src/32b/f28x/f2806x/pwr.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

qep.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/qep/src/32b/f28x/f2806x/qep.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

slip.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/slip/src/32b/slip.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

spi.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/spi/src/32b/f28x/f2806x/spi.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

svgen.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/svgen/src/32b/svgen.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timer.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/timer/src/32b/f28x/f2806x/timer.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

usDelay.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/usDelay/src/32b/f28x/usDelay.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

user_2mtr.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/user/src/32b/user_2mtr.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

wdog.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/drivers/wdog/src/32b/f28x/f2806x/wdog.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


