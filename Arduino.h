/*
	!!!NOTICE!!!
		
		THIS FILE IS A COMPLETE HACK.
		
	This is NOT the right way to do this thing.
	It's just here so I can quickly figure out if it's doable.
	When everything works, this file must be converted to a PJON interface (AVR?)
	This file is loaded because PJON thinks we are compiling on Arduino IDE,
	and we are implementing only the minium required functions.
	___________________________________________________________________________

	Copyright 2017 @johnkiller

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

//Input output
#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
void pinMode(int a, int b){
	//TODO
};
int digitalRead(int a){
	//TODO
	return 0;
};
void digitalWrite(int a, int b){
	//TODO
};

//Thanks to http://stackoverflow.com/questions/23339587/similar-function-arduino-bitwrite
void bitWrite(uint8_t &x, unsigned int n, bool b){
    if(n <= 7 && n >= 0){
        if(b){
            x |= (1u << n);
        }else{
            x &= ~(1u << n);
        }
    }    
}

//Timing
//This will require timer0...
//COPY FROM ARDUINO ---- START
		#define clockCyclesPerMicrosecond ( F_CPU / 1000000L )
		#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
		#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
		#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
		// the fractional number of milliseconds per timer0 overflow. we shift right
		// by three to fit these numbers into a byte. (for the clock speeds we care
		// about - 8 and 16 MHz - this doesn't lose precision.)
		#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
		#define FRACT_MAX (1000 >> 3)

		volatile unsigned long timer0_overflow_count = 0;
		volatile unsigned long timer0_millis = 0;
		static unsigned char timer0_fract = 0;

		SIGNAL(TIMER0_OVF_vect)
		{
			unsigned long m = timer0_millis;
			unsigned char f = timer0_fract;

			m += MILLIS_INC;
			f += FRACT_INC;
			if (f >= FRACT_MAX) {
				f -= FRACT_MAX;
				m += 1;
			}

			timer0_fract = f;
			timer0_millis = m;
			timer0_overflow_count++;
		}
		int micros(){
			unsigned long m;
			uint8_t oldSREG = SREG, t;
			
			cli();
			m = timer0_overflow_count;
			t = TCNT0;

		  
			if ((TIFR0 & _BV(TOV0)) && (t < 255))
				m++;

			SREG = oldSREG;
			
			return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond);
		};
//COPY FROM ARDUINO ---- END


void delay(int a){
	//TODO
};
void delayMicroseconds(int ms){
	//TODO
};

//Random numbers generation
#define A0 0
int analogRead(int a){
	return 0; //reads A0 just to seed the RNG. Skip for now.
};
void randomSeed(int j){
	srand(j);
};
int random(int randMax){
	return (rand() % randMax) +1; //avoid doubles: THEY ARE HUGE, more than 1000 bytes OMG
};