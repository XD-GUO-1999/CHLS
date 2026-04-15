##
## Directives to run a sound filter on a Nexys video board
##

# Simple FIR - Single Multiplier Implementation

# Establish the location of this script and use it to reference all
# other files in this example
set sfd [file dirname [info script]]

# Reset the options to the factory defaults
#options default
options set Input/TargetPlatform x86_64
options set Input/SearchPath /usr/local/bin/Siemens_EDA/Catapult_Synthesis_2022.2_1-1019737/Mgc_home/shared/include

project new

flow package require /SCVerify

solution file add [file join $sfd fft.h] -type C++
solution file add [file join $sfd fft.cpp] -type C++
go analyze

solution library add mgc_Xilinx-ARTIX-7-3_beh -- -rtlsyntool Vivado -manufacturer Xilinx -family ARTIX-7 -speed -3 -part xc7a200tsbg484-3
solution library add Xilinx_RAMS
go libraries

directive set -CLOCKS {clk {-CLOCK_PERIOD 10.0 }}
go assembly

#directive set /top_level/FIR_FILTER/while -PIPELINE_INIT_INTERVAL 1
directive set /top_level/FIR_FILTER/while/SHIFT -UNROLL yes
directive set /top_level/FIR_FILTER/while/MAC -UNROLL no
go extract

flow run /SCVerify/launch_make ./scverify/Verify_rtl_v_msim.mk {} SIMTOOL=msim sim
