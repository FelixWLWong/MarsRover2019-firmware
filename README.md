# Mars Rover 2019 Firmware

## Platform: [STM32F091](https://www.st.com/resource/en/datasheet/stm32f091rc.pdf) / [NUCLEO-F091RC](https://os.mbed.com/platforms/ST-Nucleo-F091RC/)

Firmware for the 2019 University of Waterloo Mars Rover. Contains:
- Arm MBED SDK source ([lib/mbed](https://github.com/uwrobotics/MarsRover2019-firmware/tree/master/lib/mbed))
- additional external libaries ([lib/user](https://github.com/uwrobotics/MarsRover2019-firmware/tree/master/lib/user))
- additional libraries written by the team ([lib/user](https://github.com/uwrobotics/MarsRover2019-firmware/tree/master/lib/user))
- test applications for testing code components ([app/test_xxxx](https://github.com/uwrobotics/MarsRover2019-firmware/tree/master/app))
- applications for running on each board ([app](https://github.com/uwrobotics/MarsRover2019-firmware/tree/master/app))

## Best Contribution Practices and Tips

- Create a branch in the format `yourName/featureName` for every feature you are working on
- Rebase onto master and test on hardware before merging into master
- Create a pull request to merge any branch into master and select everyone else working on the feature as reviewers
  - Name the pull request `issueNumber: FeatureTitle`
- When merging a pull request that fixes an issue title the commit `Fixes #issueNumber: FeatureTitle`
  - Adding `Fixes #1: ...` will automatically closes the associated issue, in this example issue #1
- Clean binaries between making changes to the makefile
- There seems to be an annoying mix of CamelCase and snake_case in MBED but just try to be consistent with whatever code is nearby
- Squash when merging pull requests

## UWRT Firmware Development Instructions

1. Download the development toolchain (gcc and make) and serial interface software
   
   For Ubuntu
    - `sudo apt install gcc-arm-none-eabi`
    - `sudo apt install screen` for serial interfacing (or `minicom`)
		
	For Windows
    - Download [make for windows](http://gnuwin32.sourceforge.net/packages/make.htm) (choose Complete package, except sources)
    - Run the setup package to install make
    - Add make.exe to path (usually `C:\Program Files (x86)\GnuWin32\bin`). See [this tutoial](https://helpdeskgeek.com/windows-10/add-windows-path-environment-variable/) on how to add a folder to your 'path', which allows you to reference executable files in this folder from within any workspace.
    - Download [gcc-arm-none-eabi for windows](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) (windows 32 bit)
    - Extract the ZIP to something like `C:\Program Files (x86)\GNU Tools ARM Embedded\<version>`
    - Add gcc .exe files to path (`C:\Program Files (x86)\GNU Tools ARM Embedded\<version>\bin`)
    - Install [PuTTy](https://www.chiark.greenend.org.uk/~sgtatham/putty/) for serial interfacing
	
	For Mac
    - Open Command Line
    - Install Homebrew if not installed 
    	`/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
    - Download auto-run script, which will auto install <arm-none-eabi-gcc> with latest version
    	`brew tap ARMmbed/homebrew-formulae`
    - Install <arm-none-eabi-gcc> via HomeBrew
    	`brew install arm-none-eabi-gcc`
    - Install [ZOC](https://www.emtec.com/zoc/index.html) for serial interfacing

2. Verify the the toolchains were installed correctly

    Open a new Command Prompt / Terminal window and run the following commands:

    `make --version`  
    `arm-none-eabi-gcc --version`

3. Download source code

    `git clone https://github.com/uwrobotics/MarsRover2019-firmware.git`  
    `cd MarsRover2019-firmware`

4. Run make with the target application and board

    Ex. Compile the science application for the science board:  
    `make APP=science BOARD=science`

    Ex. Compile the CAN test application for the safety board:  
    `make APP=test_can BOARD=safety`
    
    Ex. Compile the Serial test application for the nucleo development board:  
    `make APP=test_serial BOARD=nucleo`
    
    After compiling an application you should see a message similar to the following:  
    `===== bin file ready to flash: ../build/test_serial/test_serial_nucleo.bin =====`
    
    *Note*: If you are going through this README as part of the firmware training tutorial you can now go back to where you left off in the document.

5. Deploy onto board (see below for how to connect to a board)

    Find the application .bin file, located in the build/app directory.

	For Ubuntu
		
    - Install libusb `sudo apt install libusb-1.0-0-dev`
    - Drag and Drop .bin file into NODE_F091RC device folder
	
	For Windows
    
    - Drag and Drop .bin file into NODE_F091RC device folder OR if this does not work or debugging is required:
    - Download [st-link utility](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link004.html). Scroll down to Get Software
    - connect USB to nucleo board and open st-link utility
    - load code by going to Target->Program and browse for .bin file
	
	For Mac
    - Drag and Drop .bin file into NODE_F091RC disk

    After deploying, the Nucleo will begin to flash red and green. Once the LED stays green, power-cycle the board by unplugging and replugging the 5V connector on the Nucleo.

- To clean the project workspace of app and library build files, run `make clean`
- To clean compiled MBED SDK files, run `make clean-mbed`

    
## Using the Nucleo Dev Board to Program the Rover Boards

In order to use the Nucleo development board as a programmer, the two jumpers (black caps) labelled NUCLEO - ST-LINK will need to be removed. This will sever the ST-LINK debugger portion of the Nucleo from the MCU side, allowing it to be used as a general debugger.

The ST-LINK debugger can then be connected via header CN4 (pins 1-5 with 1 nearest to the SWD label) to a rover board debug header (pins should be labelled) to program it according to the following table:

```
+-----------------------+-----------------------------------+
| Nucleo CN4 Pin Number | Rover Board Debug Header Pin Name |
+-----------------------+-----------------------------------+
| 1 (VREF)              | VCC                               |
| 2 (SWCLK)             | CLK                               |
| 3 (GND)               | GND                               |
| 4 (SWDIO)             | IO                                |
| 5 (NRST)              | RST                               |
| 6 (SWO)               | Not Connected                     |
+-----------------------+-----------------------------------+
```
![](https://github.com/uwrobotics/MarsRover2019-firmware/blob/master/Nucleo_Labels.PNG)

After deploying the binary to the board, the Nucleo's `LD1` LED will flash red and green. Programming is complete when the LED stays green, so don't powercycle the board before this.

## Serial Communication

The boards can be communicated with through the serial interface exposed through the debug pins. You can use the USB-serial interface built into the Nucleo dev boards to communicate with the control boards by connecting the TX pin to the board's RX pin and the RX pin to the board's TX pin (transmit to recieve and vice versa). 

On Ubuntu
- Run `screen /dev/serial/by-id/usb-STM* 115200` from the terminal

On Windows
- Device manager, go to Ports (COM & LPT) and find the name of the Nucleo port (ie COM4)
- Open PuTTy, select the Serial radio button, enter the COM port name and the baud rate (default 115200) and click open
