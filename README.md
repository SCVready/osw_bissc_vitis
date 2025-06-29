Vitis Unified 2024.1 - Workspace

Steps to run the app via JTAG:
- Create a new Platform Component in the workspace. Use the .xsa from the Vivado Project
- In osw_software: in vitis-comp.json/Switch Platform: select the new Platform
- In osw_software: in launch.json/Bitstream File: select the .bit from the Vivado Project
- In osw_software: create a new launch config, settings icon on the right of 'run', then New Launch Configuration
- Change JUMPER to JTAG
- In osw_software: run

Steps to build the boot image:
- In Platform: Sources/zynq_fsbl/fsbl.h add the line '#define XPAR_PS7_QSPI_LINEAR_0_BASEADDR XPAR_PS7_QSPI_LINEAR_0_BASEADDRESS' see https://adaptivesupport.amd.com/s/question/0D54U00008a69dPSAQ/zynq-7000-fsbl-project-fails-with-vitis-unified-ide-vitis-classic-still-works?language=en_US
- In Platform: build
- In osw_software: Create Boot Image:
    - Change the .bit with the file the Vivado Project
- In top menu: Program Flash Memory/search choose BOOT.bin and click program
- Change JUMPER to QSPI