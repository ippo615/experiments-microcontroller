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

// Required for the Hi-Tech C compiler
#include <htc.h>

// Configuration stuff
__CONFIG( INTIO & WDTDIS & PWRTDIS & MCLREN & BORDIS & UNPROTECT );

// The PIC's clock is 4 MHz so we need to define this to use the _delay macros
#define _XTAL_FREQ 4000000

// Constants for timing:
#define BASE_TIME 750
#define BASE 75000
#define X0    1
#define X1    2
#define X2  3
#define X3  4
#define X4  5
#define X5  6
#define X6  7
#define X7  8
#define X8  9
#define X9  10
#define X10 11
#define X11 12
#define X12 13
#define X13 14
#define X14 15
#define X15 16
#define X16 17

//////////////////////////////////////////////////////////// Note Functions ///
// The following are functions that play various notes.
// A spreadsheet was used to compute all of the note frequencies and
// appropriate times. The spreadsheet was also used to generate all of the 
// functions listed below.
// Each function has the form:
// unsigned long NOTEOCTAVE(unsigned long usec){
// 	// usec is the number of microseconds to play the note
// 	// Compute how many times we should repeat the note, in this example
//      // 61162 is the amount of time required for 1 note period
// 	unsigned long repeat_count = 1 + usec /61162;
//
// 	// Since the note will be played an integer number of times there will be
// 	// some extra time that will be skipped. We compute how many microseconds
// 	// off the time is
// 	unsigned long extra = usec %61162;
//
// 	//we repeat the number of times that we calculated
// 	while(repeat_count--){
// 		
// 		PORTC = 0x00;       // pulling the output low
// 		__delay_us(30581);  // wait half of the period
// 		PORTC = 0xFF;       // push the output high
// 		__delay_us(30534);  // wait half of the period
// 		// The 2nd delay is slightly different, that is due to the fact
// 		// the loop overhead adds additional time. I subtracted that extra 
// 		// time from this delay to give us a near 50% duty cycle
// 		
// 	}
//
// 	// Return the amount of time that we missed
// 	return extra;
// }
///////////////////////////////////////////////////////////////////////////////

unsigned long C0(unsigned long usec){unsigned long repeat_count = 1 + usec /61162;unsigned long extra = usec %61162;while(repeat_count--){PORTC = 0x00;__delay_us(30581);PORTC = 0xFF;__delay_us(30534);}return extra;}
unsigned long C_0(unsigned long usec){unsigned long repeat_count = 1 + usec /57736;unsigned long extra = usec %57736;while(repeat_count--){PORTC = 0x00;__delay_us(28868);PORTC = 0xFF;__delay_us(28821);}return extra;}
unsigned long D0(unsigned long usec){unsigned long repeat_count = 1 + usec /54496;unsigned long extra = usec %54496;while(repeat_count--){PORTC = 0x00;__delay_us(27248);PORTC = 0xFF;__delay_us(27201);}return extra;}
unsigned long D_0(unsigned long usec){unsigned long repeat_count = 1 + usec /51414;unsigned long extra = usec %51414;while(repeat_count--){PORTC = 0x00;__delay_us(25707);PORTC = 0xFF;__delay_us(25660);}return extra;}
unsigned long E0(unsigned long usec){unsigned long repeat_count = 1 + usec /48544;unsigned long extra = usec %48544;while(repeat_count--){PORTC = 0x00;__delay_us(24272);PORTC = 0xFF;__delay_us(24225);}return extra;}
unsigned long F0(unsigned long usec){unsigned long repeat_count = 1 + usec /45808;unsigned long extra = usec %45808;while(repeat_count--){PORTC = 0x00;__delay_us(22904);PORTC = 0xFF;__delay_us(22857);}return extra;}
unsigned long F_0(unsigned long usec){unsigned long repeat_count = 1 + usec /43252;unsigned long extra = usec %43252;while(repeat_count--){PORTC = 0x00;__delay_us(21626);PORTC = 0xFF;__delay_us(21579);}return extra;}
unsigned long G0(unsigned long usec){unsigned long repeat_count = 1 + usec /40816;unsigned long extra = usec %40816;while(repeat_count--){PORTC = 0x00;__delay_us(20408);PORTC = 0xFF;__delay_us(20361);}return extra;}
unsigned long G_0(unsigned long usec){unsigned long repeat_count = 1 + usec /38520;unsigned long extra = usec %38520;while(repeat_count--){PORTC = 0x00;__delay_us(19260);PORTC = 0xFF;__delay_us(19213);}return extra;}
unsigned long A0(unsigned long usec){unsigned long repeat_count = 1 + usec /36364;unsigned long extra = usec %36364;while(repeat_count--){PORTC = 0x00;__delay_us(18182);PORTC = 0xFF;__delay_us(18135);}return extra;}
unsigned long A_0(unsigned long usec){unsigned long repeat_count = 1 + usec /34318;unsigned long extra = usec %34318;while(repeat_count--){PORTC = 0x00;__delay_us(17159);PORTC = 0xFF;__delay_us(17112);}return extra;}
unsigned long B0(unsigned long usec){unsigned long repeat_count = 1 + usec /32394;unsigned long extra = usec %32394;while(repeat_count--){PORTC = 0x00;__delay_us(16197);PORTC = 0xFF;__delay_us(16150);}return extra;}
unsigned long C1(unsigned long usec){unsigned long repeat_count = 1 + usec /30582;unsigned long extra = usec %30582;while(repeat_count--){PORTC = 0x00;__delay_us(15291);PORTC = 0xFF;__delay_us(15244);}return extra;}
unsigned long C_1(unsigned long usec){unsigned long repeat_count = 1 + usec /28860;unsigned long extra = usec %28860;while(repeat_count--){PORTC = 0x00;__delay_us(14430);PORTC = 0xFF;__delay_us(14383);}return extra;}
unsigned long D1(unsigned long usec){unsigned long repeat_count = 1 + usec /27240;unsigned long extra = usec %27240;while(repeat_count--){PORTC = 0x00;__delay_us(13620);PORTC = 0xFF;__delay_us(13573);}return extra;}
unsigned long D_1(unsigned long usec){unsigned long repeat_count = 1 + usec /25714;unsigned long extra = usec %25714;while(repeat_count--){PORTC = 0x00;__delay_us(12857);PORTC = 0xFF;__delay_us(12810);}return extra;}
unsigned long E1(unsigned long usec){unsigned long repeat_count = 1 + usec /24272;unsigned long extra = usec %24272;while(repeat_count--){PORTC = 0x00;__delay_us(12136);PORTC = 0xFF;__delay_us(12089);}return extra;}
unsigned long F1(unsigned long usec){unsigned long repeat_count = 1 + usec /22910;unsigned long extra = usec %22910;while(repeat_count--){PORTC = 0x00;__delay_us(11455);PORTC = 0xFF;__delay_us(11408);}return extra;}
unsigned long F_1(unsigned long usec){unsigned long repeat_count = 1 + usec /21622;unsigned long extra = usec %21622;while(repeat_count--){PORTC = 0x00;__delay_us(10811);PORTC = 0xFF;__delay_us(10764);}return extra;}
unsigned long G1(unsigned long usec){unsigned long repeat_count = 1 + usec /20408;unsigned long extra = usec %20408;while(repeat_count--){PORTC = 0x00;__delay_us(10204);PORTC = 0xFF;__delay_us(10157);}return extra;}
unsigned long G_1(unsigned long usec){unsigned long repeat_count = 1 + usec /19264;unsigned long extra = usec %19264;while(repeat_count--){PORTC = 0x00;__delay_us(9632);PORTC = 0xFF;__delay_us(9585);}return extra;}
unsigned long A1(unsigned long usec){unsigned long repeat_count = 1 + usec /18182;unsigned long extra = usec %18182;while(repeat_count--){PORTC = 0x00;__delay_us(9091);PORTC = 0xFF;__delay_us(9044);}return extra;}
unsigned long A_1(unsigned long usec){unsigned long repeat_count = 1 + usec /17162;unsigned long extra = usec %17162;while(repeat_count--){PORTC = 0x00;__delay_us(8581);PORTC = 0xFF;__delay_us(8534);}return extra;}
unsigned long B1(unsigned long usec){unsigned long repeat_count = 1 + usec /16196;unsigned long extra = usec %16196;while(repeat_count--){PORTC = 0x00;__delay_us(8098);PORTC = 0xFF;__delay_us(8051);}return extra;}
unsigned long C2(unsigned long usec){unsigned long repeat_count = 1 + usec /15288;unsigned long extra = usec %15288;while(repeat_count--){PORTC = 0x00;__delay_us(7644);PORTC = 0xFF;__delay_us(7597);}return extra;}
unsigned long C_2(unsigned long usec){unsigned long repeat_count = 1 + usec /14430;unsigned long extra = usec %14430;while(repeat_count--){PORTC = 0x00;__delay_us(7215);PORTC = 0xFF;__delay_us(7168);}return extra;}
unsigned long D2(unsigned long usec){unsigned long repeat_count = 1 + usec /13620;unsigned long extra = usec %13620;while(repeat_count--){PORTC = 0x00;__delay_us(6810);PORTC = 0xFF;__delay_us(6763);}return extra;}
unsigned long D_2(unsigned long usec){unsigned long repeat_count = 1 + usec /12856;unsigned long extra = usec %12856;while(repeat_count--){PORTC = 0x00;__delay_us(6428);PORTC = 0xFF;__delay_us(6381);}return extra;}
unsigned long E2(unsigned long usec){unsigned long repeat_count = 1 + usec /12134;unsigned long extra = usec %12134;while(repeat_count--){PORTC = 0x00;__delay_us(6067);PORTC = 0xFF;__delay_us(6020);}return extra;}
unsigned long F2(unsigned long usec){unsigned long repeat_count = 1 + usec /11454;unsigned long extra = usec %11454;while(repeat_count--){PORTC = 0x00;__delay_us(5727);PORTC = 0xFF;__delay_us(5680);}return extra;}
unsigned long F_2(unsigned long usec){unsigned long repeat_count = 1 + usec /10810;unsigned long extra = usec %10810;while(repeat_count--){PORTC = 0x00;__delay_us(5405);PORTC = 0xFF;__delay_us(5358);}return extra;}
unsigned long G2(unsigned long usec){unsigned long repeat_count = 1 + usec /10204;unsigned long extra = usec %10204;while(repeat_count--){PORTC = 0x00;__delay_us(5102);PORTC = 0xFF;__delay_us(5055);}return extra;}
unsigned long G_2(unsigned long usec){unsigned long repeat_count = 1 + usec /9632;unsigned long extra = usec %9632;while(repeat_count--){PORTC = 0x00;__delay_us(4816);PORTC = 0xFF;__delay_us(4769);}return extra;}
unsigned long A2(unsigned long usec){unsigned long repeat_count = 1 + usec /9090;unsigned long extra = usec %9090;while(repeat_count--){PORTC = 0x00;__delay_us(4545);PORTC = 0xFF;__delay_us(4498);}return extra;}
unsigned long A_2(unsigned long usec){unsigned long repeat_count = 1 + usec /8580;unsigned long extra = usec %8580;while(repeat_count--){PORTC = 0x00;__delay_us(4290);PORTC = 0xFF;__delay_us(4243);}return extra;}
unsigned long B2(unsigned long usec){unsigned long repeat_count = 1 + usec /8100;unsigned long extra = usec %8100;while(repeat_count--){PORTC = 0x00;__delay_us(4050);PORTC = 0xFF;__delay_us(4003);}return extra;}
unsigned long C3(unsigned long usec){unsigned long repeat_count = 1 + usec /7644;unsigned long extra = usec %7644;while(repeat_count--){PORTC = 0x00;__delay_us(3822);PORTC = 0xFF;__delay_us(3775);}return extra;}
unsigned long C_3(unsigned long usec){unsigned long repeat_count = 1 + usec /7216;unsigned long extra = usec %7216;while(repeat_count--){PORTC = 0x00;__delay_us(3608);PORTC = 0xFF;__delay_us(3561);}return extra;}
unsigned long D3(unsigned long usec){unsigned long repeat_count = 1 + usec /6810;unsigned long extra = usec %6810;while(repeat_count--){PORTC = 0x00;__delay_us(3405);PORTC = 0xFF;__delay_us(3358);}return extra;}
unsigned long D_3(unsigned long usec){unsigned long repeat_count = 1 + usec /6428;unsigned long extra = usec %6428;while(repeat_count--){PORTC = 0x00;__delay_us(3214);PORTC = 0xFF;__delay_us(3167);}return extra;}
unsigned long E3(unsigned long usec){unsigned long repeat_count = 1 + usec /6068;unsigned long extra = usec %6068;while(repeat_count--){PORTC = 0x00;__delay_us(3034);PORTC = 0xFF;__delay_us(2987);}return extra;}
unsigned long F3(unsigned long usec){unsigned long repeat_count = 1 + usec /5728;unsigned long extra = usec %5728;while(repeat_count--){PORTC = 0x00;__delay_us(2864);PORTC = 0xFF;__delay_us(2817);}return extra;}
unsigned long F_3(unsigned long usec){unsigned long repeat_count = 1 + usec /5406;unsigned long extra = usec %5406;while(repeat_count--){PORTC = 0x00;__delay_us(2703);PORTC = 0xFF;__delay_us(2656);}return extra;}
unsigned long G3(unsigned long usec){unsigned long repeat_count = 1 + usec /5102;unsigned long extra = usec %5102;while(repeat_count--){PORTC = 0x00;__delay_us(2551);PORTC = 0xFF;__delay_us(2504);}return extra;}
unsigned long G_3(unsigned long usec){unsigned long repeat_count = 1 + usec /4816;unsigned long extra = usec %4816;while(repeat_count--){PORTC = 0x00;__delay_us(2408);PORTC = 0xFF;__delay_us(2361);}return extra;}
unsigned long A3(unsigned long usec){unsigned long repeat_count = 1 + usec /4546;unsigned long extra = usec %4546;while(repeat_count--){PORTC = 0x00;__delay_us(2273);PORTC = 0xFF;__delay_us(2226);}return extra;}
unsigned long A_3(unsigned long usec){unsigned long repeat_count = 1 + usec /4290;unsigned long extra = usec %4290;while(repeat_count--){PORTC = 0x00;__delay_us(2145);PORTC = 0xFF;__delay_us(2098);}return extra;}
unsigned long B3(unsigned long usec){unsigned long repeat_count = 1 + usec /4050;unsigned long extra = usec %4050;while(repeat_count--){PORTC = 0x00;__delay_us(2025);PORTC = 0xFF;__delay_us(1978);}return extra;}
unsigned long C4(unsigned long usec){unsigned long repeat_count = 1 + usec /3822;unsigned long extra = usec %3822;while(repeat_count--){PORTC = 0x00;__delay_us(1911);PORTC = 0xFF;__delay_us(1864);}return extra;}
unsigned long C_4(unsigned long usec){unsigned long repeat_count = 1 + usec /3608;unsigned long extra = usec %3608;while(repeat_count--){PORTC = 0x00;__delay_us(1804);PORTC = 0xFF;__delay_us(1757);}return extra;}
unsigned long D4(unsigned long usec){unsigned long repeat_count = 1 + usec /3406;unsigned long extra = usec %3406;while(repeat_count--){PORTC = 0x00;__delay_us(1703);PORTC = 0xFF;__delay_us(1656);}return extra;}
unsigned long D_4(unsigned long usec){unsigned long repeat_count = 1 + usec /3214;unsigned long extra = usec %3214;while(repeat_count--){PORTC = 0x00;__delay_us(1607);PORTC = 0xFF;__delay_us(1560);}return extra;}
unsigned long E4(unsigned long usec){unsigned long repeat_count = 1 + usec /3034;unsigned long extra = usec %3034;while(repeat_count--){PORTC = 0x00;__delay_us(1517);PORTC = 0xFF;__delay_us(1470);}return extra;}
unsigned long F4(unsigned long usec){unsigned long repeat_count = 1 + usec /2864;unsigned long extra = usec %2864;while(repeat_count--){PORTC = 0x00;__delay_us(1432);PORTC = 0xFF;__delay_us(1385);}return extra;}
unsigned long F_4(unsigned long usec){unsigned long repeat_count = 1 + usec /2702;unsigned long extra = usec %2702;while(repeat_count--){PORTC = 0x00;__delay_us(1351);PORTC = 0xFF;__delay_us(1304);}return extra;}
unsigned long G4(unsigned long usec){unsigned long repeat_count = 1 + usec /2552;unsigned long extra = usec %2552;while(repeat_count--){PORTC = 0x00;__delay_us(1276);PORTC = 0xFF;__delay_us(1229);}return extra;}
unsigned long G_4(unsigned long usec){unsigned long repeat_count = 1 + usec /2408;unsigned long extra = usec %2408;while(repeat_count--){PORTC = 0x00;__delay_us(1204);PORTC = 0xFF;__delay_us(1157);}return extra;}
unsigned long A4(unsigned long usec){unsigned long repeat_count = 1 + usec /2272;unsigned long extra = usec %2272;while(repeat_count--){PORTC = 0x00;__delay_us(1136);PORTC = 0xFF;__delay_us(1089);}return extra;}
unsigned long A_4(unsigned long usec){unsigned long repeat_count = 1 + usec /2146;unsigned long extra = usec %2146;while(repeat_count--){PORTC = 0x00;__delay_us(1073);PORTC = 0xFF;__delay_us(1026);}return extra;}
unsigned long B4(unsigned long usec){unsigned long repeat_count = 1 + usec /2024;unsigned long extra = usec %2024;while(repeat_count--){PORTC = 0x00;__delay_us(1012);PORTC = 0xFF;__delay_us(965);}return extra;}
unsigned long C5(unsigned long usec){unsigned long repeat_count = 1 + usec /1912;unsigned long extra = usec %1912;while(repeat_count--){PORTC = 0x00;__delay_us(956);PORTC = 0xFF;__delay_us(909);}return extra;}
unsigned long C_5(unsigned long usec){unsigned long repeat_count = 1 + usec /1804;unsigned long extra = usec %1804;while(repeat_count--){PORTC = 0x00;__delay_us(902);PORTC = 0xFF;__delay_us(855);}return extra;}
unsigned long D5(unsigned long usec){unsigned long repeat_count = 1 + usec /1702;unsigned long extra = usec %1702;while(repeat_count--){PORTC = 0x00;__delay_us(851);PORTC = 0xFF;__delay_us(804);}return extra;}
unsigned long D_5(unsigned long usec){unsigned long repeat_count = 1 + usec /1608;unsigned long extra = usec %1608;while(repeat_count--){PORTC = 0x00;__delay_us(804);PORTC = 0xFF;__delay_us(757);}return extra;}
unsigned long E5(unsigned long usec){unsigned long repeat_count = 1 + usec /1516;unsigned long extra = usec %1516;while(repeat_count--){PORTC = 0x00;__delay_us(758);PORTC = 0xFF;__delay_us(711);}return extra;}
unsigned long F5(unsigned long usec){unsigned long repeat_count = 1 + usec /1432;unsigned long extra = usec %1432;while(repeat_count--){PORTC = 0x00;__delay_us(716);PORTC = 0xFF;__delay_us(669);}return extra;}
unsigned long F_5(unsigned long usec){unsigned long repeat_count = 1 + usec /1352;unsigned long extra = usec %1352;while(repeat_count--){PORTC = 0x00;__delay_us(676);PORTC = 0xFF;__delay_us(629);}return extra;}
unsigned long G5(unsigned long usec){unsigned long repeat_count = 1 + usec /1276;unsigned long extra = usec %1276;while(repeat_count--){PORTC = 0x00;__delay_us(638);PORTC = 0xFF;__delay_us(591);}return extra;}
unsigned long G_5(unsigned long usec){unsigned long repeat_count = 1 + usec /1204;unsigned long extra = usec %1204;while(repeat_count--){PORTC = 0x00;__delay_us(602);PORTC = 0xFF;__delay_us(555);}return extra;}
unsigned long A5(unsigned long usec){unsigned long repeat_count = 1 + usec /1136;unsigned long extra = usec %1136;while(repeat_count--){PORTC = 0x00;__delay_us(568);PORTC = 0xFF;__delay_us(521);}return extra;}
unsigned long A_5(unsigned long usec){unsigned long repeat_count = 1 + usec /1072;unsigned long extra = usec %1072;while(repeat_count--){PORTC = 0x00;__delay_us(536);PORTC = 0xFF;__delay_us(489);}return extra;}
unsigned long B5(unsigned long usec){unsigned long repeat_count = 1 + usec /1012;unsigned long extra = usec %1012;while(repeat_count--){PORTC = 0x00;__delay_us(506);PORTC = 0xFF;__delay_us(459);}return extra;}
unsigned long C6(unsigned long usec){unsigned long repeat_count = 1 + usec /956;unsigned long extra = usec %956;while(repeat_count--){PORTC = 0x00;__delay_us(478);PORTC = 0xFF;__delay_us(431);}return extra;}
unsigned long C_6(unsigned long usec){unsigned long repeat_count = 1 + usec /902;unsigned long extra = usec %902;while(repeat_count--){PORTC = 0x00;__delay_us(451);PORTC = 0xFF;__delay_us(404);}return extra;}
unsigned long D6(unsigned long usec){unsigned long repeat_count = 1 + usec /852;unsigned long extra = usec %852;while(repeat_count--){PORTC = 0x00;__delay_us(426);PORTC = 0xFF;__delay_us(379);}return extra;}
unsigned long D_6(unsigned long usec){unsigned long repeat_count = 1 + usec /804;unsigned long extra = usec %804;while(repeat_count--){PORTC = 0x00;__delay_us(402);PORTC = 0xFF;__delay_us(355);}return extra;}
unsigned long E6(unsigned long usec){unsigned long repeat_count = 1 + usec /758;unsigned long extra = usec %758;while(repeat_count--){PORTC = 0x00;__delay_us(379);PORTC = 0xFF;__delay_us(332);}return extra;}
unsigned long F6(unsigned long usec){unsigned long repeat_count = 1 + usec /716;unsigned long extra = usec %716;while(repeat_count--){PORTC = 0x00;__delay_us(358);PORTC = 0xFF;__delay_us(311);}return extra;}
unsigned long F_6(unsigned long usec){unsigned long repeat_count = 1 + usec /676;unsigned long extra = usec %676;while(repeat_count--){PORTC = 0x00;__delay_us(338);PORTC = 0xFF;__delay_us(291);}return extra;}
unsigned long G6(unsigned long usec){unsigned long repeat_count = 1 + usec /638;unsigned long extra = usec %638;while(repeat_count--){PORTC = 0x00;__delay_us(319);PORTC = 0xFF;__delay_us(272);}return extra;}
unsigned long G_6(unsigned long usec){unsigned long repeat_count = 1 + usec /602;unsigned long extra = usec %602;while(repeat_count--){PORTC = 0x00;__delay_us(301);PORTC = 0xFF;__delay_us(254);}return extra;}
unsigned long A6(unsigned long usec){unsigned long repeat_count = 1 + usec /568;unsigned long extra = usec %568;while(repeat_count--){PORTC = 0x00;__delay_us(284);PORTC = 0xFF;__delay_us(237);}return extra;}
unsigned long A_6(unsigned long usec){unsigned long repeat_count = 1 + usec /536;unsigned long extra = usec %536;while(repeat_count--){PORTC = 0x00;__delay_us(268);PORTC = 0xFF;__delay_us(221);}return extra;}
unsigned long B6(unsigned long usec){unsigned long repeat_count = 1 + usec /506;unsigned long extra = usec %506;while(repeat_count--){PORTC = 0x00;__delay_us(253);PORTC = 0xFF;__delay_us(206);}return extra;}
unsigned long C7(unsigned long usec){unsigned long repeat_count = 1 + usec /478;unsigned long extra = usec %478;while(repeat_count--){PORTC = 0x00;__delay_us(239);PORTC = 0xFF;__delay_us(192);}return extra;}
unsigned long C_7(unsigned long usec){unsigned long repeat_count = 1 + usec /450;unsigned long extra = usec %450;while(repeat_count--){PORTC = 0x00;__delay_us(225);PORTC = 0xFF;__delay_us(178);}return extra;}
unsigned long D7(unsigned long usec){unsigned long repeat_count = 1 + usec /426;unsigned long extra = usec %426;while(repeat_count--){PORTC = 0x00;__delay_us(213);PORTC = 0xFF;__delay_us(166);}return extra;}
unsigned long D_7(unsigned long usec){unsigned long repeat_count = 1 + usec /402;unsigned long extra = usec %402;while(repeat_count--){PORTC = 0x00;__delay_us(201);PORTC = 0xFF;__delay_us(154);}return extra;}
unsigned long E7(unsigned long usec){unsigned long repeat_count = 1 + usec /380;unsigned long extra = usec %380;while(repeat_count--){PORTC = 0x00;__delay_us(190);PORTC = 0xFF;__delay_us(143);}return extra;}
unsigned long F7(unsigned long usec){unsigned long repeat_count = 1 + usec /358;unsigned long extra = usec %358;while(repeat_count--){PORTC = 0x00;__delay_us(179);PORTC = 0xFF;__delay_us(132);}return extra;}
unsigned long F_7(unsigned long usec){unsigned long repeat_count = 1 + usec /338;unsigned long extra = usec %338;while(repeat_count--){PORTC = 0x00;__delay_us(169);PORTC = 0xFF;__delay_us(122);}return extra;}
unsigned long G7(unsigned long usec){unsigned long repeat_count = 1 + usec /318;unsigned long extra = usec %318;while(repeat_count--){PORTC = 0x00;__delay_us(159);PORTC = 0xFF;__delay_us(112);}return extra;}
unsigned long G_7(unsigned long usec){unsigned long repeat_count = 1 + usec /300;unsigned long extra = usec %300;while(repeat_count--){PORTC = 0x00;__delay_us(150);PORTC = 0xFF;__delay_us(103);}return extra;}
unsigned long A7(unsigned long usec){unsigned long repeat_count = 1 + usec /284;unsigned long extra = usec %284;while(repeat_count--){PORTC = 0x00;__delay_us(142);PORTC = 0xFF;__delay_us(95);}return extra;}
unsigned long A_7(unsigned long usec){unsigned long repeat_count = 1 + usec /268;unsigned long extra = usec %268;while(repeat_count--){PORTC = 0x00;__delay_us(134);PORTC = 0xFF;__delay_us(87);}return extra;}
unsigned long B7(unsigned long usec){unsigned long repeat_count = 1 + usec /254;unsigned long extra = usec %254;while(repeat_count--){PORTC = 0x00;__delay_us(127);PORTC = 0xFF;__delay_us(80);}return extra;}

// A rest function (looks like a note but doesn't make a sound)
unsigned long REST(unsigned long usec){unsigned long repeat_count = 1 + usec /254;unsigned long extra = usec %254;while(repeat_count--){PORTC = 0x00;__delay_us(127);PORTC = 0x00;__delay_us(80);}return extra;}

// To make coding easier we are defining a type called NOTE
// The NOTE type is a pointer to a function that has 1 unsigned long argument
// and returns an unsigned long
// We will be able to use the NOTE type to create an array of notes to be played
typedef unsigned long (*NOTE)(unsigned long);

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

///////////////////////////////////////////////////////////// PLAY_STUCATTO ///
// const NOTE* NOTES: is an array of Notes that will be played
// const char* TIMES: is an array of the durations corresonding to how long
//                    each note should be played for
// int count: the total number of notes to be played
// TIMES are integers that represent multiples of the base time so if the note
// should be played for two times the base time then the char 2 should be used
// STUCATTO means "choppy" (or something like it) and that means the notes will
// be played quickly and not sustained ie if the TIME was 4 then the note would
// be played for 1 and then 3 rests would occure
///////////////////////////////////////////////////////////////////////////////
void PLAY_STUCATTO(const NOTE* NOTES, const char* TIMES, int count){

	// Compute a base duration determined by the value of the POT
	// this is used to dynamically control the speed of the music
	unsigned long base_duration = (unsigned long)BASE_TIME*(unsigned long)PollPortA(0);

	int i;
	unsigned long error = 0;

	// Play each note for the minimum ammount of time and rest
	// Keep track of any timing errors
	for(i=0; i<count; i+=1){
		error += NOTES[i]((unsigned long)X1*base_duration);
		error += REST((unsigned long)TIMES[i]*base_duration);
	}

	// try to correct the timing error that has accumulated
	// note that rest is not perfect either but has the theoretically smallest
	// error of all the note function
	REST(error);
	return;
}

////////////////////////////////////////////////////////// Mario Bros Theme ///
// Notice how easy it is to define arrays of the notes that we want to play
// by using function pointers. 

NOTE const DoDoDoNotes[7] = {E4,E4,E4,C4,E4,G4,G3};
char const DoDoDoTimes[7] = {X0,X1,X1,X0,X1,X3,X3};

NOTE const Vers1ANotes[9] = {C4,G3,E3,A3,B3,A_3,A3,G3,E4};
NOTE const Vers1BNotes[8] = {G4,A4,F4,G4,E4,C4,D4,B3};
char const Vers1ATimes[9] = {X2,X2,X2,X1,X1,X0,X1,X0,X1};
char const Vers1BTimes[8] = {X0,X1,X0,X1,X1,X0,X0,X2};

NOTE const Vers2ANotes[11] = {G4,F_4,F4,D_4,E4,G_3,A3,C4,A3,C4,D4};
char const Vers2ATimes[11] = {X0,X0,X0,X1,X1,X0,X0,X1,X0,X0,X0};
NOTE const Vers2BNotes[8] = {G4,F_4,F4,D_4,E4,C5,C5,C5};
char const Vers2BTimes[8] = {X0,X0,X0,X1,X1,X1,X0,X3};
NOTE const Vers2CNotes[3] = {D_4,D4,C4};
char const Vers2CTimes[3] = {X2,X2,X7};

NOTE const Vers3ANotes[6] = {C4,C4,C4,C4,D4,E4};
char const Vers3ATimes[6] = {X0,X1,X1,X0,X1,X0};
NOTE const Vers3BNotes[3] = {C4,A3,G3};
char const Vers3BTimes[3] = {X1,X0,X3};

NOTE const Verse4Notes[33] = {E4,C4,G3,G_3,A3,F4,F4,A3,B3,A4,A4,A4,G4,F4,E4,C4,A3,G3,E4,C4,G3,G_3,A3,F4,F4,A3,B3,F4,F4,F4,E4,D4,C4};
char const Verse4Times[33] = {X0,X1,X2,X1,X0,X1,X0,X3,X0,X0,X0,X1,X1,X0,X0,X1,X0,X3,X0,X1,X2,X1,X0,X1,X0,X3,X0,X1,X0,X0,X0,X1,X3};

NOTE const ShortRestNotes[1] = {REST};
char const ShortRestTimes[1] = {X2};

NOTE const MidRestNotes[1] = {REST};
char const MidRestTimes[1] = {X4};

NOTE const LongRestNotes[1] = {REST};
char const LongRestTimes[1] = {X8};

////////////////////////////////////////////////////////////////////// main ///
void main(void){


	TRISC = 0; //PORTC as output
	TRISA = 0; //PORTA as output
	PORTC = 0; //clear LEDs

	//loop forever
	while(1){

		//play the Mario Bros Theme
		PLAY_STUCATTO(DoDoDoNotes,DoDoDoTimes,7);
		
		PLAY_STUCATTO(Vers1ANotes,Vers1ATimes,9);
		PLAY_STUCATTO(Vers1BNotes,Vers1BTimes,8);
		PLAY_STUCATTO(Vers1ANotes,Vers1ATimes,9);
		PLAY_STUCATTO(Vers1BNotes,Vers1BTimes,8);
		PLAY_STUCATTO(ShortRestNotes,ShortRestTimes,1);
		PLAY_STUCATTO(Vers2ANotes,Vers2ATimes,11);
		PLAY_STUCATTO(ShortRestNotes,ShortRestTimes,1);
		PLAY_STUCATTO(Vers2BNotes,Vers2BTimes,8);
		PLAY_STUCATTO(ShortRestNotes,ShortRestTimes,1);
		PLAY_STUCATTO(Vers2ANotes,Vers2ATimes,11);
		PLAY_STUCATTO(ShortRestNotes,ShortRestTimes,1);
		PLAY_STUCATTO(Vers2CNotes,Vers2CTimes,3);
		PLAY_STUCATTO(ShortRestNotes,ShortRestTimes,1);

		PLAY_STUCATTO(Vers3ANotes,Vers3ATimes,6);
		PLAY_STUCATTO(Vers3BNotes,Vers3BTimes,3);
		PLAY_STUCATTO(Vers3ANotes,Vers3ATimes,6);
		PLAY_STUCATTO(MidRestNotes,MidRestTimes,1);

		PLAY_STUCATTO(DoDoDoNotes,DoDoDoTimes,7);
		PLAY_STUCATTO(Vers1ANotes,Vers1ATimes,9);
		PLAY_STUCATTO(Vers1BNotes,Vers1BTimes,8);
		PLAY_STUCATTO(Vers1ANotes,Vers1ATimes,9);
		PLAY_STUCATTO(Vers1BNotes,Vers1BTimes,8);
		
		PLAY_STUCATTO(Verse4Notes,Verse4Times,33);
		PLAY_STUCATTO(LongRestNotes,LongRestTimes,1);

	}

}