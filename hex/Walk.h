#ifndef WALK_H__
#define WALK_H__

#include <Arduino.h>
#include "Leg.h"
#include "Move.h"
#include "Ultra.h"

class Walk{
  private:
    Leg leg;
    Move mv;
    Ultra ultra;
    int stpMillis = 0;
    bool walkToggle = false;
    double xLast;
    double yLast;
    double zLast;
    int rnd = 0;
    int steps = 0;
  public:
    int onSpot(int stp, int spd);
    int moveInDirection(int stp, int spd, double yMove, double xMove, double zMove);
    int stepIn(int stp, int spd, double yMove, double xMove, double zMove);
    int walk(int stp, int spd, double yMove, double xMove, double zMove);
    int stepOut(int stp, int spd);
    int getSteps();
    void setSteps(int steps);
};

#endif
