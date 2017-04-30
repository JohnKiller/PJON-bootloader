# PJON-bootloader
ATmega bootloader over [PJON](https://github.com/gioblu/PJON/) bus.

 - Using `boot.h` (thanks to [Optiboot](https://github.com/Optiboot/optiboot)) for programming functions
 - Using `PJON` (thanks to [Giovanni Blu Mitolo](https://github.com/gioblu/PJON/)) for the network layer
 - Using `oniudra-headers` (thanks to [esmil/oniudra-headers](https://github.com/esmil/oniudra-headers)) for serial debugging and helper functions
 - Also a big THANKS for the project [arduino-netboot](https://github.com/esmil/arduino-netboot) from wich i've learned much of how a bootloader works

----------
## About this project
The current goal is to program an ATmega328p (Arduino Nano) over PJON using `SoftwareBitBang` strategy.
Main problem is library size because bootloaders have a max size of about ~4000 bytes.

For this to work, you will need two Arduino Nano (one connected to the PC by USB serial, and the other is the target). The PC will send the HEX file to the first Arduino which in turn will send it over PJON bus to the bootloader.

## How to build
I'm using Ubuntu 16 LTS:

 1. Setup the environment: `sudo apt-get install git gcc-avr binutils-avr gdb-avr avr-libc avrdude`
 2. Clone the project: `git clone https://github.com/JohnKiller/PJON-bootloader`
 3. Cd into directory: `cd PJON-bootloader`
 4. Init submodules: `git submodule update --init --recursive`
 5. Build: `chmod +x build.sh && ./build.sh`
 6. Use avr to program the generated HEX file

You also have to set the fuses `BOOTSZ1`, `BOOTSZ0` and `BOOTRST`. Personally, I use `L 0xFF`, `H 0xD0` and `E 0x05` (as always, be VERY careful with fuses, you can brick the processor).

## WIP
This is still in the early stages. I've already created a simple serial bootloader and it works, so now I'm focusing on getting PJON running with AVR. Any help is appreciated.
