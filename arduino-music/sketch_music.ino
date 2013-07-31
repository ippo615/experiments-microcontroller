const unsigned int nC0=16;
const unsigned int nC_0=17;
const unsigned int nD0=18;
const unsigned int nD_0=19;
const unsigned int nE0=21;
const unsigned int nF0=22;
const unsigned int nF_0=23;
const unsigned int nG0=25;
const unsigned int nG_0=26;
const unsigned int nA0=28;
const unsigned int nA_0=29;
const unsigned int nB0=31;
const unsigned int nC1=33;
const unsigned int nC_1=35;
const unsigned int nD1=37;
const unsigned int nD_1=39;
const unsigned int nE1=41;
const unsigned int nF1=44;
const unsigned int nF_1=46;
const unsigned int nG1=49;
const unsigned int nG_1=52;
const unsigned int nA1=55;
const unsigned int nA_1=58;
const unsigned int nB1=62;
const unsigned int nC2=65;
const unsigned int nC_2=69;
const unsigned int nD2=73;
const unsigned int nD_2=78;
const unsigned int nE2=82;
const unsigned int nF2=87;
const unsigned int nF_2=93;
const unsigned int nG2=98;
const unsigned int nG_2=104;
const unsigned int nA2=110;
const unsigned int nA_2=117;
const unsigned int nB2=123;
const unsigned int nC3=131;
const unsigned int nC_3=139;
const unsigned int nD3=147;
const unsigned int nD_3=156;
const unsigned int nE3=165;
const unsigned int nF3=175;
const unsigned int nF_3=185;
const unsigned int nG3=196;
const unsigned int nG_3=208;
const unsigned int nA3=220;
const unsigned int nA_3=233;
const unsigned int nB3=247;
const unsigned int nC4=262;
const unsigned int nC_4=277;
const unsigned int nD4=294;
const unsigned int nD_4=311;
const unsigned int nE4=330;
const unsigned int nF4=349;
const unsigned int nF_4=370;
const unsigned int nG4=392;
const unsigned int nG_4=415;
const unsigned int nA4=440;
const unsigned int nA_4=466;
const unsigned int nB4=494;
const unsigned int nC5=523;
const unsigned int nC_5=554;
const unsigned int nD5=587;
const unsigned int nD_5=622;
const unsigned int nE5=659;
const unsigned int nF5=698;
const unsigned int nF_5=740;
const unsigned int nG5=784;
const unsigned int nG_5=831;
const unsigned int nA5=880;
const unsigned int nA_5=932;
const unsigned int nB5=988;
const unsigned int nC6=1047;
const unsigned int nC_6=1109;
const unsigned int nD6=1175;
const unsigned int nD_6=1245;
const unsigned int nE6=1319;
const unsigned int nF6=1397;
const unsigned int nF_6=1480;
const unsigned int nG6=1568;
const unsigned int nG_6=1661;
const unsigned int nA6=1760;
const unsigned int nA_6=1865;
const unsigned int nB6=1976;
const unsigned int nC7=2093;
const unsigned int nC_7=2217;
const unsigned int nD7=2349;
const unsigned int nD_7=2489;
const unsigned int nE7=2637;
const unsigned int nF7=2794;
const unsigned int nF_7=2960;
const unsigned int nG7=3136;
const unsigned int nG_7=3322;
const unsigned int nA7=3520;
const unsigned int nA_7=3729;
const unsigned int nB7=3951;

#define PIN_SPEAKER 4
void setup(){
  pinMode(PIN_SPEAKER,OUTPUT);
}

const unsigned int BASE_TIME=100;
unsigned int DoDoDoNotes[7] = {nE4,nE4,nE4,nC4,nE4,nG4,nG3};
unsigned long DoDoDoTimes[7] = {0,1,1,0,1,3,3};

unsigned int Vers1ANotes[9] = {nC4,nG3,nE3,nA3,nB3,nA_3,nA3,nG3,nE4};
unsigned int Vers1BNotes[8] = {nG4,nA4,nF4,nG4,nE4,nC4,nD4,nB3};
unsigned long Vers1ATimes[9] = {2,2,2,1,1,0,1,0,1};
unsigned long Vers1BTimes[8] = {0,1,0,1,1,0,0,2};

unsigned int Vers2ANotes[11] = {nG4,nF_4,nF4,nD_4,nE4,nG_3,nA3,nC4,nA3,nC4,nD4};
unsigned long Vers2ATimes[11] = {0,0,0,1,1,0,0,1,0,0,0};
unsigned int Vers2BNotes[8] = {nG4,nF_4,nF4,nD_4,nE4,nC5,nC5,nC5};
unsigned long Vers2BTimes[8] = {0,0,0,1,1,1,0,3};
unsigned int Vers2CNotes[3] = {nD_4,nD4,nC4};
unsigned long Vers2CTimes[3] = {2,2,7};

unsigned int Vers3ANotes[6] = {nC4,nC4,nC4,nC4,nD4,nE4};
unsigned long Vers3ATimes[6] = {0,1,1,0,1,0};
unsigned int Vers3BNotes[3] = {nC4,nA3,nG3};
unsigned long Vers3BTimes[3] = {1,0,3};

unsigned int Verse4Notes[33] = {nE4,nC4,nG3,nG_3,nA3,nF4,nF4,nA3,nB3,nA4,nA4,nA4,nG4,nF4,nE4,nC4,nA3,nG3,nE4,nC4,nG3,nG_3,nA3,nF4,nF4,nA3,nB3,nF4,nF4,nF4,nE4,nD4,nC4};
unsigned long Verse4Times[33] = {0,1,2,1,0,1,0,3,0,0,0,1,1,0,0,1,0,3,0,1,2,1,0,1,0,3,0,1,0,0,0,1,3};

void loop(){
  	PLAY_REG(DoDoDoNotes,DoDoDoTimes,7);

	PLAY_REG(Vers1ANotes,Vers1ATimes,9);
	PLAY_REG(Vers1BNotes,Vers1BTimes,8);
	PLAY_REG(Vers1ANotes,Vers1ATimes,9);
	PLAY_REG(Vers1BNotes,Vers1BTimes,8);
	delay(BASE_TIME*2);
	PLAY_REG(Vers2ANotes,Vers2ATimes,11);
	delay(BASE_TIME*2);
	PLAY_REG(Vers2BNotes,Vers2BTimes,8);
	delay(BASE_TIME*4);
	PLAY_REG(Vers2ANotes,Vers2ATimes,11);
	delay(BASE_TIME*2);
	PLAY_REG(Vers2CNotes,Vers2CTimes,3);
	delay(BASE_TIME*2);

	PLAY_REG(Vers3ANotes,Vers3ATimes,6);
	PLAY_REG(Vers3BNotes,Vers3BTimes,3);
	PLAY_REG(Vers3ANotes,Vers3ATimes,6);
	PLAY_REG(Vers3BNotes,Vers3BTimes,3);
	delay(BASE_TIME*8);

	PLAY_REG(DoDoDoNotes,DoDoDoTimes,7);
	PLAY_REG(Vers1ANotes,Vers1ATimes,9);
	PLAY_REG(Vers1BNotes,Vers1BTimes,8);
	PLAY_REG(Vers1ANotes,Vers1ATimes,9);
	PLAY_REG(Vers1BNotes,Vers1BTimes,8);

	PLAY_REG(Verse4Notes,Verse4Times,33);
	delay(BASE_TIME*4);
	PLAY_REG(Verse4Notes,Verse4Times,33);
	delay(BASE_TIME*4);
	PLAY_REG(Vers3ANotes,Vers3ATimes,6);
	PLAY_REG(Vers3BNotes,Vers3BTimes,3);
	PLAY_REG(Vers3ANotes,Vers3ATimes,6);
	PLAY_REG(Vers3BNotes,Vers3BTimes,3);
	delay(BASE_TIME*16);
}
void PLAY_STUCATTO(unsigned int notes[], unsigned long times[], int count){
  int i=0;
  for(i=0; i<count; i+=1){
    tone(PIN_SPEAKER,notes[i]);
    delay(BASE_TIME);
    noTone(PIN_SPEAKER);
    delay(BASE_TIME*(times[i]+1));
  }
}
void PLAY_REG(unsigned int notes[], unsigned long times[], int count){
  int i=0;
  for(i=0; i<count; i+=1){
    tone(PIN_SPEAKER,notes[i]);
    delay(BASE_TIME*(times[i]+1));
    noTone(PIN_SPEAKER);
    delay(BASE_TIME);
  }
}
