#!/bin/bash

#remove last build files
rm pjonboot.hex
rm builderrors.log

#compile main program
avr-gcc -g -Os -mmcu=atmega328p -std=c++11 -I . -c pjonboot.cpp 2> builderrors.log

#echo first lines of errors (if present)
head -n 10 builderrors.log

#link
avr-gcc -g -Os -Wl,--relax -Wl,--gc-sections -nostartfiles -mmcu=atmega328p -Wl,--section-start=.text=0x7000 -o pjonboot.elf pjonboot.o

#convert
avr-objcopy -j .text -j .data -O ihex pjonboot.elf pjonboot.hex

#cleanup
rm pjonboot.o
rm pjonboot.elf

#done
avr-size pjonboot.hex
