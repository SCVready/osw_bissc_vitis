Vitis Unified 2024.1 - Workspace

Steps to run the app via JTAG:
- Create a new Platform Component in the workspace. Use the .xsa from the Vivado Project
- In osw_software: in vitis-comp.json/Switch Platform: select the new Platform
- In osw_software: in launch.json/Bitstream File: select the .bit from the Vivado Project
- In osw_software: create a new launch config, settings icon on the right of 'run', then New Launch Configuration
- In osw_software: run

Steps to build the boot image:
- In platform: in vitis-comp.json/platform/ps7_cortexa9_0/standalone_ps7_cortexa9_0/Board Support Package: in Suported Libraries, enable 'xilffs' and 'xilrsa'
- Create the Zync FSBL component using the examples
- Build zynq_fsbl
- In the top menu: Vitis/Create Boot Image/Zynq Create new BIF file:
    - Add: bootloader, select zynq_fsbl/build/zynq_fsbl.elf (not working, get it from vitis clasic zybo_osw/export/zybo_osw/sw/zybo_osw/boot/fsbl.elf)
    - Add: data file, select .bit from the Vivado Project
    - Add: data file, select osw_software/build/osw_software.elf