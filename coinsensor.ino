const char* deviceID = "arduinoCoin";
const char* nextPuzzle = "ToDevice/arduinoNone";

const int coinPin = 2;
const int ledPin = 3;

volatile int pulse = 0;

boolean bInserted = false;

boolean startup = true;


void onSolve(){
  publish("arduinoCoin solved");
  Serial.println("Coin inserted");
}

void onReset(){
  publish("arduinoCoin reset");
  pulse = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EthernetSetup();
  delay(5000);
  attachInterrupt(digitalPinToInterrupt(coinPin),coinInterrupt, RISING);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if( bInserted  ){ 
     if (startup){
      startup = false;
      bInserted = false;
     }
     if(!startup){
      bInserted = false;
      digitalWrite(ledPin, HIGH);
      onSolve();    
      delay(1000);
      pulse = 0;
     }
  }else{

      digitalWrite(ledPin, LOW);
  } 
 mqttLoop();
}

void coinInterrupt(){
 
  pulse++ ;
  if (pulse == 5){
    bInserted = true; 
  }
 Serial.println( pulse );   
}
