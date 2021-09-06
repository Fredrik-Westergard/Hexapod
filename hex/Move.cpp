#include "Move.h"
#include "Leg.h"
#include <PCA9685.h>  //pca9685 the servo driver module
#include <nRF24L01.h> //nrf24l01 is the radio transceiver module
#include <Arduino.h>


PCA9685 driver0(B000000); //addresses and initializes the motor drivers, set to 0
PCA9685 driver1(B000001); //set to 1
PCA9685_ServoEval pwmServo(102, 470); //set the min and max servo movement, -90 to +90 degrees

//Move constructor
Move::Move(){
  //set the offsets for the servo to desired degrees
   for(int i=0; i<3; i++){
     this->servoOffset[0][i][0] = 0;
     this->servoOffset[0][i][1] = 187.74;
     this->servoOffset[0][i][2] = -100.27;
     this->servoOffset[1][i][0] = 0;
     this->servoOffset[1][i][1] = 187.74;
     this->servoOffset[1][i][2] = -100.27;
   } 
}

//initializes the motor drivers
void Move::initDrivers(){
  driver0.resetDevices(); //Software resets all PCA9685 devices on Wire line
  driver0.init();
  driver1.init();
  driver0.setPWMFrequency(50); //Set frequency to 50Hz
  driver1.setPWMFrequency(50);
}

//function to move the legs to desired angles
void Move::moveLegs(Leg* leg){

  //steps through the 18 servos, and sets angles according to calculations
  for(int i = 0; i < 3; i++){
    driver0.setChannelPWM(i*4, pwmServo.pwmForAngle(leg->getAngleC(i)+servoOffset[0][i][0]));
    driver0.setChannelPWM((i*4)+1, pwmServo.pwmForAngle(-leg->getAngleB(i)+servoOffset[0][i][1]));
    driver0.setChannelPWM((i*4)+2, pwmServo.pwmForAngle(leg->getAngleA(i)+servoOffset[0][i][2]));

    driver1.setChannelPWM(i*4, pwmServo.pwmForAngle(leg->getAngleC(3+i)+servoOffset[1][i][0]));
    driver1.setChannelPWM((i*4)+1, pwmServo.pwmForAngle(-leg->getAngleB(3+i)+servoOffset[1][i][1]));
    driver1.setChannelPWM((i*4)+2, pwmServo.pwmForAngle(leg->getAngleA(3+i)+servoOffset[1][i][2]));
  } 
}
