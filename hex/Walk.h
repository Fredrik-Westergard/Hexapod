#ifndef WALK_H__
#define WALK_H__

#include <Arduino.h>
#include "Leg.h"
#include "Move.h"
#include "Ultra.h"

/*
 * class for walking
 */
class Walk{
  private:
    Leg leg; //leg object
    Move mv; //move object
    Ultra ultra; //ultrasonic sensor object
    int stpMillis = 0; //milliseconds since last step
    bool walkToggle = false; //toggle for world
    double xLast; //last x value
    double yLast; //last y value
    double zLast; //last z value
    int rnd = 0; //round variable, used to properly step out
    int steps = 0; //steps counter
  public:
    int onSpot(int stp, int spd); //function to walk on spot
    int moveInDirection(int stp, int spd, double yMove, double xMove, double zMove); //function to move in chosen direction
    int stepIn(int stp, int spd, double yMove, double xMove, double zMove); //function to take first step
    int walk(int stp, int spd, double yMove, double xMove, double zMove); //function to walk
    int stepOut(int stp, int spd); //function to take last step
    int getSteps(); //getter of steps taken
    void setSteps(int steps); //setter of steps
    int getDistance(); //getter of distance from ultrasonic sensor
};

#endif
