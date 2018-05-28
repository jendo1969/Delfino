################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Example_2837xSSci_Echoback.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_examples_Cpu1/sci_echoback/cpu01/Example_2837xSSci_Echoback.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="Example_2837xSSci_Echoback.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_CodeStartBranch.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_DefaultISR.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_DefaultISR.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_DefaultISR.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_GlobalVariableDefs.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_Gpio.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_Gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_Gpio.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_PieCtrl.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_PieCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_PieVect.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_PieVect.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_SysCtrl.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_SysCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xS_usDelay.obj: D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/source/F2837xS_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/ccs700/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_headers/include" --include_path="D:/ti/controlSUITE/device_support/F2837xS/v180/F2837xS_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xS_usDelay.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


