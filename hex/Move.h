#ifndef MOVE_H__
#define MOVE_H__

#include <Arduino.h>
#include "Leg.h"
#include <PCA9685.h>  //pca9685 the servo driver module

//Move class
class Move{
  private:
    Leg* leg = NULL; //leg object
    double servoOffset[2][3][3]; //servo offsets, the degrees to offset the servos to match real world angles to calculated ones

  public:
    Move(Leg* leg); //Move constructor
    void initDrivers(); //initializes the motor drivers
    void moveLegs(); //moves the legs

};

#endif
