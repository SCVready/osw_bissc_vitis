**Work In progress**

This is the software implementation of the OSW BISSC project. For the FPGA implementation, see [https://github.com/SCVready/osw_bissc_vivado](https://github.com/SCVready/osw_bissc_vivado)

This project extends the original Open Sim Wheel project from 2014 (MIGE + Ionicube 1x + STM32f4 discovery board + MMOS firmware), replacing the incremental encoder with a higher-resolution BISS-C encoder.
To integrate the new encoder, I'm using the Xilinx ZYBO board:
- The FPGA handles the reception of the position data from the BISS-C encoder and generates the PWM for the servo driver.
- The microprocessor implements the USB HID (with the HID extension for FFB).

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
