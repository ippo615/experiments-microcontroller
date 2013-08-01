#include <math.h>          /* required for cos function*/
#include "tonecfg.h"       /* auto-generated by CCStudio */
#include "dsk6713.h"       /* board support library */
#include "dsk6713_aic23.h" /* required for using the codec for audio in/output */
#include "notes.h"         /* pre-computed musical note frequencies */

/* We will be setting the coded to run at 8kHz which gives a
 * sample period of 1/8000 = 0.000125s */
#define SAMPLE_PERIOD 0.000125
#define PI 3.1415926535897932384626433832795

/* The cosOut outputs a cosine of frequency "freq" for "duration" seconds
 * to the codec with handle "hCodec" 
 * This is basically a utility function that busy-waits while generating
 * and outputting a cosine wave */
void cosOut(double freq, double duration, DSK6713_AIC23_CodecHandle hCodec){
	double i; int sample;
	for (i = SAMPLE_PERIOD; i < duration; i+=SAMPLE_PERIOD){
		sample = (int)(2048.0*cos(2*PI*freq*i));
		// Send a sample to the left channel 
		while (!DSK6713_AIC23_write(hCodec, sample ));
		//Send a sample to the right channel
		while (!DSK6713_AIC23_write(hCodec, sample ));
	}
	return;
}

/* Codec configuration settings */
DSK6713_AIC23_Config config = DSK6713_AIC23_DEFAULTCONFIG;

void main(){
    DSK6713_AIC23_CodecHandle hCodec;

	int i;

    /* Initialize the board support library, must be called first */
    DSK6713_init();

    /* Start the codec, set sample rate to 8kHz */
    hCodec = DSK6713_AIC23_openCodec(0, &config);
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_8KHZ);

	/* Output all the notes 2 times */
	for(i=0;i<2;i++){
		//#include "sequence.h"
	}
	//play Deck the Halls, based on the notes the DSK identified
	#include "sequence_deck.h"

    /* Close the codec */
    DSK6713_AIC23_closeCodec(hCodec);
}