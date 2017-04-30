#!/bin/bash

#remove last build files
rm pjonboot.hex
rm builderrors.log

#compile main program
avr-gcc -g -Os -mmcu=atmega328p -std=c++11 -I . -c pjonboot.cpp 2> builderrors.log

#echo first lines of errors (if present)
head -n 10 builderrors.log

#link
avr-gcc -g -mmcu=atmega328p -Wl,--section-start=.text=0x7000 -o pjonboot.elf pjonboot.o

#convert
avr-objcopy -j .text -j .data -O ihex pjonboot.elf pjonboot.hex

#cleanup
rm pjonboot.o
rm pjonboot.elf

#done
avr-size pjonboot.hex

#this comes from Optiboot, some options should be tried to reduce size of bootloader
#avr-gcc -g -Wall -Os -fno-inline-small-functions -fno-split-wide-types -mshort-calls -mmcu=atmega328p -DF_CPU=16000000  -DBAUD_RATE=115200 -DLED_START_FLASHES=3 -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe -Wl,--relax -Wl,--gc-sections -nostartfiles -nostdlib -o optiboot_atmega328.elf optiboot.o