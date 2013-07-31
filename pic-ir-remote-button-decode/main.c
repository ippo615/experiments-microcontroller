/////////////////////////////////////////////////////////////// Ippo's Code ///
// MICRO: PIC 16F690
// BOARD: DM164120 - Low Pin Count Demo Board
// HARDW: TEAC-RC-505 infrared remote
//        Infrared recieve connected to PORTA PIN 5
// TITLE: PIC - IR Remote Button Decoding
// DESCR: This code shows how to decode a button press from a remote.
// RESUL: Waits for IR button press. When a number (0-9) is pressed it flashes
//        shows the number on the LED display.
// COPYR: (C) Andrew Ippoliti 2012 All Rights Reserved
// LICEN: Free to use/modify as long as you mention the author in your code
// WRNTY: No warranty whatsoever. Use at your own responsibility and risk.
///////////////////////////////////////////////////////////////////////////////

//included for the Hi-Tech C compiler
#include <htc.h>

//configuration stuff
__CONFIG( INTIO & WDTDIS & PWRTDIS & MCLREN & BORDIS & UNPROTECT );

/////////////////////////////////////////////////// Remote Control Protocol ///
//The IR remote timing: T = 550 us ~9 counts from GetDurationA
//	HEADER:
//		HIGH: 9.26ms 16 T - 17 T
//		LOW:  4.3 ms  7 T -  8 T
//	STOP CODE:
//		HIGH: 8.8 ms  or       or 16 T
//		LOW:  2.2 ms  or       or  4 T
//		HIGH: 0.55ms  or       or  1 T
//	BIT 1:
//		HIGH: 0.55ms or 1T
//		LOW:  1.65ms or 3T
//	BIT 0:
//		HIGH: 0.55ms or 1T
//		LOW:  0.55ms or 1T
//  OVERALL CODE:
//	HEADER
//	GROUP CODE:           16 Bits
//	BUTTON CODE:           8 Bits
//	BUTTON CODE XOR 0xFF:  8 Bits
//	STOP CODE
///////////////////////////////////////////////////////////////////////////////
#define CODE_LEN 32 //a constant to tell us how many bits are in the code

/////////////////////////////////////////////////////////////// GetDurationA //
// int Pin: integer respresting the pin on PORTA that will be monitored (0-5)
// int Level: the digital logic level that will be monitored (0 or 1)
// This function returns a count of how long the Pin on PORTA was at Level
// NOTE the function blocks and waits until the pin is no longer at Level
///////////////////////////////////////////////////////////////////////////////
int GetDurationA( int Pin, int Level);
int GetDurationA( Pin,  Level){
	//make sure the pin is configured as an input
	TRISA |= (1<<Pin);
	//start the count at 0
	unsigned long Count = 0;
	//prepare a mask for re-use later
	int mask = (1<<Pin);
	//as long as the level is the same as what we're measuring
	while((mask == (PORTA & mask)) == Level){
		//increase the count
		Count += 1;
	}
	//we should cast this to an int 
	return Count;
}
/////////////////////////////////////////////////////// WaitForFallingEdge ////
//int Pin: the pin on PORTA that will be monitored (0-5)
//This function blocks code execution (except interrupts) until Pin falls from
//HI to LOW
///////////////////////////////////////////////////////////////////////////////
int WaitForFallingEdge(int Pin);
int WaitForFallingEdge(int Pin){
	//we should make sure the pin is an input first
	//create a mask for use later
	int mask = 1<<Pin;
	//wait for a high (because we can't 'fall' from a low)
	while(mask != (PORTA & mask)){	}
	//as long as the thing is high: wait
	while(mask == (PORTA & mask)){	}
	//exit the function
	return 1;
}
//////////////////////////////////////////////////////// WaitForRisingEdge ////
//int Pin: the pin on PORTA that will be monitored (0-5)
//This function blocks code execution (except interrupts) until Pin rises from
//LOW to HI
///////////////////////////////////////////////////////////////////////////////
int WaitForRisingEdge(int Pin);
int WaitForRisingEdge(int Pin){
	//we should make sure the pin is an input first
	//create a mask for use later
	int mask = 1<<Pin;
	//wait for a low (because we can't 'rise' from a low)
	while(mask == (PORTA & mask)){	}
	//as long as the thing is low: wait
	while(mask != (PORTA & mask)){	}
	//exit the function
	return 1;
}
///////////////////////////////////////////////////////////////////// main ////
///////////////////////////////////////////////////////////////////////////////
void main(void){
	TRISC = 0; //set PORTC as an output
	PORTC = 0; //clear PORTC
	int X = 1; //X will be used for debugging errors
	
	//an array to store all of the measurements for decoding the IR signal
	int IRCODE[32];
	char GroupCodeFir = 0; //for storing the first  part of the group code
	char GroupCodeSec = 0; //for storing the second part of the group code
	int ButtonCode = 0;    //for storing the button code
	int CheckCode = 0;     //for storing a code to vertify the button code
	
	int i;    //temporary variable for iterating
	int CODE; //holds the button number after it has been decoded
	
	//repeat forever
	while(1){
		//wait for the header
		WaitForFallingEdge(5);
		WaitForFallingEdge(5);
		//gather the duration information
		for(i=0; i < CODE_LEN; i+=1){
			GetDurationA(5,0);
			IRCODE[i] = GetDurationA(5,1);
		}
		//wait for the stop code to pass
		GetDurationA(5,0);
		GetDurationA(5,1);
		GetDurationA(5,0);
		
		//decode the group code
		GroupCodeFir = 0;
		for(i=0; i < 8; i+=1){
			GroupCodeFir = (GroupCodeFir << 1) | (IRCODE[i] > 16); 
		}
		GroupCodeSec = 0;
		for(i=0; i < 8; i+=1){
			GroupCodeSec = (GroupCodeSec << 1) | (IRCODE[i+8] > 16); 
		}
		//decode the button code
		ButtonCode = 0;
		for(i=0; i < 8; i+=1){
			ButtonCode = (ButtonCode << 1) | (IRCODE[i+16] > 16); 
		}

		//An alternate way to decode the button code:
		/*
		if(IRCODE[15] > 16){X |= 0b00000001;}
		if(IRCODE[14] > 16){X |= 0b00000010;}
		if(IRCODE[13] > 16){X |= 0b00000100;}
		if(IRCODE[12] > 16){X |= 0b00001000;}
		if(IRCODE[11] > 16){X |= 0b00010000;}
		if(IRCODE[10] > 16){X |= 0b00100000;}
		if(IRCODE[ 9] > 16){X |= 0b01000000;}
		if(IRCODE[ 8] > 16){X |= 0b10000000;}
		*/

		//from the button code determine which number was pressed
		switch(ButtonCode){
			case 0x68: CODE = 0; break;
			case 0x48: CODE = 1; break;
			case 0xC8: CODE = 2; break;
			case 0x88: CODE = 3; break;
			case 0x08: CODE = 4; break;
			case 0xF0: CODE = 5; break;
			case 0x18: CODE = 6; break;
			case 0xE8: CODE = 7; break;
			case 0x28: CODE = 8; break;
			case 0xA8: CODE = 9; break;
			default: CODE = 0xFF; break;
		}
		
		//output the number that was pressed
		PORTC = CODE;
		
		//wait a little while
		int i;
		unsigned long j;
		for(i=0; i<4; i+=1){
			for(j=0; j<10000; j++){}
		}
	}
}

