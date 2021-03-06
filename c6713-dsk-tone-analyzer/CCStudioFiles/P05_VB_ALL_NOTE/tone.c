#include <math.h> /* required for cos function*/
#include "tonecfg.h" /* auto-generated by CCStudio */
#include "dsk6713.h" /* board support library */
#include "dsk6713_aic23.h" /* required for using the codec for audio in/output */
#include "dsk6713_led.h" /* required for working with the LEDs */
#include "notes.h" /* pre-computed musical note frequencies for ease */
#include <rtdx.h>   /* For RTDX communication*/
#include "target.h" /* RTDX setup */

/* Declare and initialize an output channel called "ochan" */
RTDX_CreateOutputChannel(ochan);

/* We will be setting the coded to run at 8kHz which gives a
 * sample period of 1/8000 = 0.000125s */
#define SAMPLE_PERIOD 0.000125
#define PI 3.1415926535897932384626433832795

/* Codec configuration settings */
DSK6713_AIC23_Config config = DSK6713_AIC23_DEFAULTCONFIG;

/* Setup the variables which will be used for Goertzel analysis */
#define NOTE_COUNT 96   //we will work only some notes
#define BLOCK_SIZE 2000 //samples to process before output & reset
double Z1[NOTE_COUNT];  //the 1st delay element for each note
double Z2[NOTE_COUNT];  //the 2nd delay element for each note
double  S[NOTE_COUNT];  //the current value for each note
double RF[NOTE_COUNT];  //the actual frequency for each note
double NF[NOTE_COUNT];  //the normalized frequency for each note
double RW[NOTE_COUNT];  //2*cos(2*pi*normalizedFreq) for each note
double PO[NOTE_COUNT];  //power of each note
int i;                  //the iteration count
int f;                  //which note we're on
int maxNote;            //which note has the most power
double maxP;            //the max power measured
double totP;            //the total power measured
Uint32 sampleRead; //place to store value read from codec
double sampleDbl;  //used to convert value read from codec to double

void main(){
    DSK6713_AIC23_CodecHandle hCodec;

    /* Initialize the board support library, must be called first */
    DSK6713_init();
	/* Initialize the LED module of the BSL */
    DSK6713_LED_init();

    /* Start the codec, set sample rate to 8kHz */
    hCodec = DSK6713_AIC23_openCodec(0, &config);
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_8KHZ);

	/* RTDX Setup */
    TARGET_INITIALIZE();
    RTDX_enableOutput(&ochan);

	/* Initialize everything to the starting parameters */
	#include "note_setup.h"
	for(f=0; f<NOTE_COUNT; f++){
		Z1[f]=0;
		Z2[f]=0;
		NF[f]=RF[f]*SAMPLE_PERIOD;
		RW[f]=2*cos(2*PI*NF[f]);
	}

	while(1){
		/* Run Goertzel Algorithm */
		for(i=0; i<BLOCK_SIZE; i++){
			//read one channel
			while(!DSK6713_AIC23_read(hCodec, &sampleRead)){}
			sampleDbl = ((double)sampleRead)/16383.0;
			for(f=0; f<NOTE_COUNT; f++){
				S[f]  = sampleDbl + RW[f]*Z1[f] - Z2[f];
				Z2[f] = Z1[f];
				Z1[f] = S[f];
			}
			//compute the total power of the signal
			//this will be used to normalize the measurements later
			totP += sampleDbl*sampleDbl;
			//read other channel & ignore it
			while(!DSK6713_AIC23_read(hCodec, &sampleRead)){}
		}
		//this number was empirically determined
		//maximum normalized power squared must be more than:
		maxP = 50.0;
		maxNote = -1;
		for(f=0; f<NOTE_COUNT; f++){
			//calculate power, dont bother taking the square root
			//but do normalize it
			PO[f] = (Z2[f]*Z2[f] + Z1[f]*Z1[f] - RW[f]*Z1[f]*Z2[f])/totP;
			if(PO[f] > maxP){
				maxP = PO[f];
				maxNote = f;
			}
			//reset
			Z1[f]=0.0;
			Z2[f]=0.0;
		}
		totP = 0;

		//write to RTDX
		if ( !RTDX_write( &ochan, &maxNote, sizeof(maxNote) ) ) {
		//if ( !RTDX_write( &ochan, &maxP, sizeof(maxP) ) ) {
            //ERROR
        }
	}
	/* Stop RTDX */
	RTDX_disableOutput(&ochan);
    /* Close the codec */
    DSK6713_AIC23_closeCodec(hCodec);
}
