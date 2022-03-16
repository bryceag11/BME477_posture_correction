#include "time.h"
#include <Arduino_LSM9DS1.h>


//momentarty switch pin
//const int buttonPin = 12;
//int buttonState = 0; 
//Mapped sensor value
int backPos;
//Value for the "normal position"
int basePos = 40;


//vibration motor digital pin
//int vibePin = 9;

//buzzer digital pin
int buzzerPin = 2;
//length of delay between alarms 
long intervalAlarm = 400;
// will store last time buzzer was updated
long previousMillisAlarm = 0;

int value, value2 ;
//long time=0;
int periode = 100;
int displace = 500;

void setup() {
  Serial.begin(9600);
  //Initialize the appropriate pins to outputs or inputs 
  pinMode(buzzerPin, OUTPUT);
 // pinMode(buttonPin, INPUT);    
  pinMode(3, OUTPUT); //green LED 1
  pinMode(5, OUTPUT); //RED LED 1
} 



void loop() {

  //Start reading the y axis values coming from the accelerometer. 
  int yAxis = analogRead(A0);
  // map the values to a range that is easyer to work with (1-100).
  backPos = map(yAxis, 240,400,0,100);

  //start reading the button state
//buttonState = digitalRead(buttonPin);
  //if the button is pressed set the value of base position to the current back position 
  // this sets a "normal" state that the code will then measure a difference from. 
    
  basePos = backPos; 
 // } 

  //if backPos is in a bad postion
  if(backPos > basePos + 5){
  
    //turn on the piezo buzzer 
    alarm();
    digitalWrite(5, HIGH); // turn LED on
    digitalWrite(3, LOW);

  }
  //otherwise turn off the motor and buzzer
  else{
    digitalWrite(buzzerPin, LOW);
    digitalWrite(5,LOW); // turn LED off
    digitalWrite(3, HIGH); // turn GREEN on
  }
}

//fuction that controls the piezo buzzer
void alarm(){
  //use blink with out delay logic and tone library to pulse the alarm. 
  unsigned long currentMillisAlarm = millis();
  if(currentMillisAlarm - previousMillisAlarm > intervalAlarm) {
    //reset the "timer"
    previousMillisAlarm = currentMillisAlarm;
    //turn on buzzer
    tone(buzzerPin, 105,400);
  }
}
