/* 
This is a sketch to run two motors simultaneously, triggered by a momentary switch,
in order to launch paper airplanes. 

This project was inspired by a trip my daughter and I took to the Glazer Childrens Museum in Tampa, FL.

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select 'port'
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

//momentary button
const int buttonPin = 8;
int buttonState = 0;
int buttonStateCache = 0;
int buttonPushCounter = 0;

//Button LED
const int ledPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin,INPUT);
  pinMode(ledPin, OUTPUT);
  
  AFMS.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if(buttonState != buttonStateCache){
    if(buttonState == HIGH){ //button has been pressed
      buttonPushCounter++;  //increment button press counter
      Serial.println("on");
      Serial.println("button presses = ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("off");
    }
    delay(50);  //delay for de-bounce
  }
  buttonStateCache = buttonState; //save button state

//  Serial.println(buttonPushCounter%2);
  //check the button press count to determine if we turn the motor on or off
  //update LED state to match button state.
  if(buttonPushCounter % 2 == 0){
    stopMotors();
	  digitalWrite(ledPin, LOW);
    //TODO: add timer to stop button from being left on.
  } else {
    startMotors();
	  digitalWrite(ledPin, HIGH);
  }
}

void startMotors(){
    myMotor1->setSpeed(255);
    myMotor1->run(FORWARD);
    myMotor2->setSpeed(255);
    myMotor2->run(FORWARD);
}

void stopMotors(){
myMotor1->setSpeed(0);
  myMotor1->run(RELEASE);
  myMotor2->setSpeed(0);
  myMotor2->run(RELEASE);
}

