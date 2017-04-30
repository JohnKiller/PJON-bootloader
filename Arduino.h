/*
	!!!NOTICE!!!
		
		THIS FILE IS A COMPLETE HACK.
		
	This is NOT the right way to do this thing.
	It's just here so I can quickly figure out if it's doable.
	When everything works, this file must be converted to a PJON interface (AVR?)
	This file is loaded because PJON thinks we are compiling on Arduino IDE,
	and we are implementing only the minium required functions.
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
int micros(){return 0;};
void delay(int a){};
void delayMicroseconds(int ms){};

//Random numbers generation
#define A0 0
int analogRead(int a){
	return 0; //reads A0 just to seed the RNG. Skip for now.
};
void randomSeed(int a){
	//TODO
};
int random(int a){
	//TODO
	return 0;
};