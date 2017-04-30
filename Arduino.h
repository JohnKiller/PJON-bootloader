/*
	!!!NOTICE!!!
		
		THIS FILE IS A COMPLETE HACK.
		
	This is NOT the right way to do this thing.
	It's just here so I can quickly figure out if it's doable.
	When everything works, this file must be converted to a PJON interface (AVR?)
	This file is loaded because PJON thinks we are compiling on Arduino IDE,
	and we are implementing only the minium required functions.
*/

//Arduino Defines
#define A0 0
#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1

//Unimplemented functions
void pinMode(int a, int b){};
void delay(int a){};
void delayMicroseconds(int ms){};
int digitalRead(int a){return 0;};
void digitalWrite(int a, int b){};
int micros(){return 0;};
int random(int a){return 0;};

//Done
void randomSeed(int a){};
int analogRead(int a){return 0;};
void bitWrite(uint8_t &x, unsigned int n, bool b){
    if(n <= 7 && n >= 0){
        if(b){
            x |= (1u << n);
        }else{
            x &= ~(1u << n);
        }
    }    
}