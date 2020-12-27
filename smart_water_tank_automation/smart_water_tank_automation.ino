//  smart water tank automation
//  Code Developer Aman Singh
//  Version 1.1

//  motor on 12
//  motor off 11
//  DR 10
//  TopLevel 9
//  MidLevel 8
//  LowLevel VCC

const int motorOnPin = 12;
const int motorOffPin = 11;
const int dryRunPin = 10;
const int topLevelPin = 9;
const int midLevelPin = 8;

bool waterRunning = false;

void setup() {
  // put your setup code here, to run once:
  pinMode (motorOnPin, OUTPUT);
  pinMode (motorOffPin, OUTPUT);
  pinMode (dryRunPin, INPUT);
  pinMode (topLevelPin, INPUT);
  pinMode (midLevelPin, INPUT);

  Serial.begin(9600);

  Serial.println("Water tank automation Started");
}

//function for turinig on motors
void MotorOn() {
  Serial.println("Pump is turning on");
  digitalWrite(motorOnPin, HIGH);
  delay(2000);
  digitalWrite(motorOffPin, LOW);
}

//function for turning off motors
void MotorOff() {
  Serial.println("Pump is turning off");
  digitalWrite(motorOffPin, HIGH);
  delay(2000);
  digitalWrite(motorOffPin, LOW);  
}

//function to check if water is coming or not 

bool dryRunTest(){
    Serial.println("checking if water from pump is coming or not:");
    for (int i = 0 ; i < 60; i++) {

      Serial.print("t minus ");
      Serial.print(60-i);
      Serial.print(" seconds \n");
      
        int test = digitalRead(dryRunPin);
        if (test == 1) {

            Serial.println("Water running from Pump Started");
            return true;
          }
          delay(1000);        
      }
     Serial.println("Water not running from pump");
     return false;
  }

void loop() {
  //this will ensure that the code will run every 1 second
  //delay(1000);
  int dryRun = digitalRead(dryRunPin);
  int topLevel = digitalRead(topLevelPin);
  int midLevel = digitalRead(midLevelPin);

   if (dryRun == 0 && topLevel == 0 && midLevel == 0){
    Serial.println("Tank is empty");
      MotorOn();
      waterRunning = dryRunTest();

      //this will turn off the motor if there is no water running withing 1 min.
      if (!waterRunning){
          MotorOff();
        }
      //remember that later to add some delay
    }
   
  //if water is running and it reached to mid level
  if (waterRunning && midLevel == 1){
      Serial.println("Water has reached to midLevel, Motor is on");
      //add leds here to make it more interactive
    }
  //if water is running and tank is full
  if (waterRunning && topLevel == 1){
    Serial.println("Tank is full so, turning off the motor");
      MotorOff();
    }
  //if water is not running and tank is full
  if (!waterRunning && topLevel == 1 ){
      Serial.println("Tank is full, motor is off");
      //MotorOff();
      //can blink some leds here
    }
  if (!waterRunning && midLevel == 1) {
    Serial.println("Tank is partially filled, motor is off");
      // do some stuffs here
    }
}
