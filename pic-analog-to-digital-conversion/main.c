/////////////////////////////////////////////////////////////// Ippo's Code ///
// MICRO: PIC 16F690
// BOARD: DM164120 - Low Pin Count Demo Board
// HARDW: NONE
// TITLE: Simple Analogue to Digital Conversion with the PIC
// DESCR: This code shows how to read an analog input and convert to digital
// RESUL: Rotating the POT on the demo board will change the value displayed 
//        on the demo board's LEDs
// COPYR: (C) Andrew Ippoliti 2012 All Rights Reserved
// LICEN: Free to use/modify as long as you mention the author in your code
// WRNTY: No warranty whatsoever. Use at your own responsibility and risk.
///////////////////////////////////////////////////////////////////////////////

//included for the Hi-Tech C compiler
#include <htc.h>

//configuration stuff
__CONFIG( INTIO & WDTDIS & PWRTDIS & MCLREN & BORDIS & UNPROTECT );

////////////////////////////////////////////////////////////////// PollPortA //
// int Pin: integer respresting the pin on PORTA that will be read (0-5)
// This function returns the 8 highest bits of the A to D conversions as a char
///////////////////////////////////////////////////////////////////////////////
char PollPortA(char Pin){
	// if the PIN number is not valid (we only have 7 pins)
	// also not that some PICs don't have A/D on pins > 4
	if(Pin>7){
		return 0;
	}
	TRISA |= 1<<Pin; // enable the pin as input
	ANSEL |= 1<<Pin; // select the pin as an analogue input
	ADCON0 = 0b10000001 | (Pin<<2); // setup the A/D converter

	// begin the A to D conversion & wait for it to finish
	GODONE = 1;
	while(GODONE){};

	// the A to D converter has a resolution of 10 bits
	// we're taking those two "variables" and stuffing them into one as follows:
	//  ADRESH:ADRESL = ------HH:LLLLLLLL = FEDCBA98:76543210
	//  aToD          = ------XX:XXXXXX-- = 98765432
	char aToD;
	aToD = (ADRESH<<6)+(ADRESL>>2);
	return aToD;

	// According to the data sheet: pg 244
	// A/D Acquisition Time + Conversion Time is around 22 us or _delay(22)
	//  or 0.022 ms -> which i think is small enough to ignore
	//    0.00025 ms per clock cycle <- just for reference
	//    0.00100 ms per instruction cycle
}
///////////////////////////////////////////////////////////////////// main ////
///////////////////////////////////////////////////////////////////////////////
void main(void){
    char X;       //temporary variable
    TRISC = 0x00; //set PORTC (leds) as outputs
    while(1){
        //read the POT connected to PORTA pin 0
        X = PollPortA(0);
        //out the highest 4 bits of the A/D conversion
        PORTC = X>>4;
    }
}
