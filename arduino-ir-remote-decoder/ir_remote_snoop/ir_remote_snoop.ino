const int pinIR = 2;
const int pinLED=13;
int CODE = 0;

volatile boolean bounced = 0;
const int CODE_LEN = 50;
volatile unsigned long durations[CODE_LEN];
volatile int GroupCode = 0;
void setup(){
  pinMode(pinIR , INPUT);
  pinMode(pinLED, OUTPUT);
  //LOW to trigger the interrupt whenever the pin is low,
  //CHANGE to trigger the interrupt whenever the pin changes value
  //RISING to trigger when the pin goes from low to high,
  //FALLING for when the pin goes from high to low. 
  attachInterrupt(0, decodeIR, FALLING);
  //turn off led
  digitalWrite(pinLED, LOW);
  Serial.begin(9600);
}

void loop(){
  if(bounced == 1){
    int i;
    Serial.println("Starting");
    for(i=0; i<CODE_LEN; i+=1){
      Serial.println((unsigned long)durations[i]);
    }
    digitalWrite(pinLED, LOW);
    bounced = 0;
    }
}

void decodeIR(){
  if(bounced){return;}
  digitalWrite(pinLED, HIGH);
  bounced = 1;
  //stop all interrupts
  noInterrupts();

  int i;
  //for each "bit" in the code
  for(i=0; i<CODE_LEN; i+=1){
    //durations[i] = pulseIn(pinIR, LOW, 100000);
    //store the duration of the pulse (microseconds)
    durations[i] = pulseIn(pinIR, HIGH, 100000);
  }
  //enable interrupts
  interrupts();
}
