/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

//momentary button
const int buttonPin = 8;
int buttonState = 0;
int buttonStateCache = 0;
int buttonPushCounter = 0;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  pinMode(buttonPin,INPUT);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
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
  if(buttonPushCounter % 2 == 0){
    stopMotors();
  } else {
    startMotors();
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

