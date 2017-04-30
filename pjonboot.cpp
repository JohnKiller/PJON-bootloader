/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

___________________________________________________________________________

Thanks to Giovanni Blu Mitolo <gioscarab@gmail.com> for the amazing PJON project
___________________________________________________________________________

This project is an attempt to create an ATmega bootloader over PJON bus.

Note that in this early phase, my main concern is about hex size,
because it's limited to ~4000 bytes. Also, this will run over SWBB.
*/

//Currently tested only on Arduino Nano
#define F_CPU 16000000UL

//For testing only. This (and the "-I ." command line parameter) tricks PJON to load Arduino.h from our directory
//Here we will redefine standard Arduino functions
#define ARDUINO

//AVR includes
#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//oniudra-headers
#include <arduino/pins.h>
#include <arduino/serial.h>

//optiboot
#include "boot.h"

//PJON
#define PJON_INCLUDE_ASYNC_ACK false
#define PJON_MAX_PACKETS 1
#define PJON_PACKET_MAX_LENGTH 128
#define PJON_INCLUDE_SWBB
#include "PJON/PJON.h"
//TODO load bus id from EEPROM
PJON<SoftwareBitBang> bus(PJON_NOT_ASSIGNED);

static inline int __attribute__((noreturn)) exit_bootloader(void){
	__asm__ __volatile__ ("jmp 0\n");
	__builtin_unreachable();
}

void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info){
	//just a test for now
	switch(payload[0]){
		case 'E':
			exit_bootloader();
			break;
	}
}

int main(void){
	//we don't care about reset reason
	MCUSR = 0;
	
	/*
		NOTICE: here I am calling every PJON function I will use just to get them compiled,
		thus getting overall program size. The code is expected to not work, just compile.
	*/
	bus.strategy.set_pin(12);
	bus.set_receiver(receiver_function);
	bus.begin();
	char buf[] = "HELLO";
	bus.send_packet(1, buf, 5);
	bus.receive();
	
	//obv this will just reset since there is no program loaded on address 0
	return exit_bootloader();
}