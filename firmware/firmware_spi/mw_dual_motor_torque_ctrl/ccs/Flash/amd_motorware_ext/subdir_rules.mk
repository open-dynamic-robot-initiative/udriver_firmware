################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
amd_motorware_ext/utils.obj: /Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/src/utils.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware/sw/modules/hal/boards/boostxldrv8305_revA/f28x/f2806x/src/" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/user_config_f28069m_drv8305" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/mw_dual_motor_torque_ctrl/src" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/amd_motorware_ext/include" --include_path="/Users/jviereck/dev/blmc_udriver_firmware/udriver_firmware/motorware" -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="amd_motorware_ext/$(basename $(<F)).d_raw" --obj_directory="amd_motorware_ext" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


