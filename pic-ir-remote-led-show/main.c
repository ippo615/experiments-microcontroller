/////////////////////////////////////////////////////////////// Ippo's Code ///
// MICRO: PIC 16F690
// BOARD: DM164120 - Low Pin Count Demo Board
// HARDW: TEAC-RC-505 infrared remote
//        Infrared recieve connected to PORTA PIN 5
// TITLE: PIC - IR Remote Controlled LED Show (Multi-tasking)
// DESCR: This code shows how to do a task while polling for input.
// RESUL: Waits for IR button press. When a number (0-9) is pressed it flashes
//        the number at a certain rate. When "<<" is pressed it flashes the
//        number more slowly. When ">>" is pressed it flashes the number more
//        quickly.
// COPYR: (C) Andrew Ippoliti 2012 All Rights Reserved
// LICEN: Free to use/modify as long as you mention the author in your code
// WRNTY: No warranty whatsoever. Use at your own responsibility and risk.
///////////////////////////////////////////////////////////////////////////////

// included for the Hi-Tech C compiler
#include <htc.h>

// configuration stuff
__CONFIG( INTIO & WDTDIS & PWRTDIS & MCLREN & BORDIS & UNPROTECT );

// The PIC's clock is 4 MHz so we need to define this to use the _delay macros
#define _XTAL_FREQ 4000000

// If we are checking the IR signal from within our display function then we
// will have missed the first falling edge and we'll need to take that into
// account. WAIT_FIRST will be used tell us which case we should decode
int WAIT_FIRST = 1;

/////////////////////////////////////////////////////////////// GetDurationA //
// int Pin: integer respresting the pin on PORTA that will be monitored (0-5)
// int Level: the digital logic level that will be monitored (0 or 1)
// This function returns a count of how long the Pin on PORTA was at Level
///////////////////////////////////////////////////////////////////////////////
long GetDurationA( int Pin, int Level);
long GetDurationA( Pin,  Level){
	TRISA |= (1<<Pin); // make pin an input
	long Count = 0;    // start the count at 0
	int mask = (1<<Pin); // create a mask for easier checking later

	// instead of waiting for a level change, limit the maximum count
	// limiting the maximum count to 128 (arbitrary) prevents the PIC from
	// getting stuck while trying to measure a duration
	for(Count = 1; Count < 128; Count+=1){
		// if the pin has risen or fallen
		if( (mask == (PORTA & mask)) == Level ){
			break;
		}
	}

	// return the number of iterations of the loop
	return Count;
}

/////////////////////////////////////////////////////// WaitForFallingEdge ////
//int Pin: the pin on PORTA that will be monitored (0-5)
//This function blocks code execution (except interrupts) until Pin falls from
//HI to LOW
///////////////////////////////////////////////////////////////////////////////
int WaitForFallingEdge(int Pin);
int WaitForFallingEdge(int Pin){
	
	TRISA |= (1<<Pin); // make sure the pin is configured as an input
	int mask = 1<<Pin; // create a mask for easier checking later

	// wait for a high (because we can't 'fall' from a low)
	while(mask != (PORTA & mask)){	}
	// as long as the thing is high: wait
	while(mask == (PORTA & mask)){	}

	return 1;
}

//////////////////////////////////////////////////////////////// FlashLEDs ////
//int num: the number that you want to flash (0x00 - 0x0F)
//int rate: arbitrary number controlling how fast/slow to flash the number
//int pin: the pin on PORTA that will be monitored (0-5) for IR activity
// This function flashes puts num on the LEDs for a certain amount of time. It
// then puts the bitwise invertion of num (ie NOT num) on the LEDs for a
// roughly equal amount of time. This process repeats indefinitely until it
// sees the the specified pin fall low. When the pin falls low the function
// exits
///////////////////////////////////////////////////////////////////////////////
void FlashLEDs(int num,int rate,int pin);
void FlashLEDs(num,rate,pin){
	
	int mask = 1<<pin; // create a mask for easier checking later
	int i;

	// only flash the LEDs when the pin is HIGH
	while(mask == (PORTA & mask)){

		// display the original number
		PORTC = num;

		// repeat this a somewhat arbitrary number of times to create a delay
		for(i=0; i<rate; i+=1){

			// we specify a 1ms delay but it may not be that accurate
			__delay_ms(1);

			// if we have a button code coming in from the IR sensor
			if( mask != (PORTA & mask)){
				// we just got the first falling edge so count one less falling
				// edge when decoding the IR code
				WAIT_FIRST = 0;
				return;
			}
		}

		// display the inverse of the original number
		PORTC = ~num;

		// similar to portion above
		for(i=0; i<rate; i+=1){
			__delay_ms(1);
			if( mask != (PORTA & mask)){WAIT_FIRST = 0; return;}
		}
	}
	return;
}

// the length of the code from the IR remote is 32 bits long
#define CODE_LEN 32

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

	int i;                 //temporary variable for iterating
	unsigned long j;       //temporary variable for iterating
	int CODE;              //holds the button number after it has been decoded
	int RATE = 128;        //speed for flashing the LEDs
	int VALID_CODE = 0;    //to tell us if we have got an error-free IR signal
	
	while(1){

		//we'll start by assuming we have a valid code
		//if an error occurs along the way we'll set it to 0
		VALID_CODE = 1;

		// if we nee to wait for the first falling edge
		if(WAIT_FIRST==1){
			// wait for the header
			WaitForFallingEdge(5);
		}
		// reset the WAIT_FIRST 
		WAIT_FIRST = 1;

		//let the header pass
		WaitForFallingEdge(5);
		WaitForFallingEdge(5);

		//for every bit in the code
		for(i=0; i < CODE_LEN; i+=1){
			IRCODE[i]  = GetDurationA(5,0); // get the duration of the low
			IRCODE[i] += GetDurationA(5,1); // add the duration of the high
		}

		// instead of decoding the stop code
		// we'll just wait 1/10th of a second
		__delay_ms(100);
		
		// Decode the first part of the group code (8 bits)
		GroupCodeFir = 0;
		for(i=0; i < 8; i+=1){
			// shift the currently decoded sequence to the left by 1
			// the 'or' it with a 0 if the corresponding IRCODE is short
			// otherwise 'or' it with 1 if the corresponding IRCODE is longer
			// than 16. 16 Is a constant determined by checking the output
			// of the GetDurationA function when decoding a know 0 or 1 from
			// the remote
			GroupCodeFir = (GroupCodeFir << 1) | (IRCODE[i] > 16); 
		}

		// Decode the second part of the group code (8 bits)
		GroupCodeSec = 0;
		for(i=0; i < 8; i+=1){
			GroupCodeSec = (GroupCodeSec << 1) | (IRCODE[i+8] > 16); 
		}

		// Decode the button code
		ButtonCode = 0;
		for(i=0; i < 8; i+=1){
			ButtonCode = (ButtonCode << 1) | (IRCODE[i+16] > 16); 
		}
		
		//depending on the button code change one of the variables
		switch(ButtonCode){
			//valid button codes
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
			case 0x30: RATE = RATE/2; break;
			case 0xB0: RATE = RATE*2; break;
			//if we didn't get a valid button code flag it
			default: CODE = 0xFF; VALID_CODE = 0; break;
		}
		
		// If we decoded a valid code
		if(VALID_CODE == 1){
			// flash the LEDs appropriately
			FlashLEDs(CODE,RATE,5);
		}else{
			// output some debugging information
			// in this case we're ouputing the measured duratino of the first
			// recieved bit
			X = IRCODE[0];
			// iterate over each 4-bit portion of X
			for(i=0; i<5; i+=4){
				// output a particular 4-bit portion
				PORTC = X>>i;
				// wait
				for(j=0; j<10000; j++){}
			}
			// clear the LEDs
			PORTC = 0;
		}
	}
}
