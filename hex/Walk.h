#ifndef WALK_H__
#define WALK_H__

#include <Arduino.h>
#include "Leg.h"
#include "Move.h"

class Walk{
  private:
    Leg leg;
    Move mv;
    int stpMillis = 0;
    bool walkToggle = false;
    double xLast;
    double yLast;
    double zLast;
    int rnd = 0;
  public:
    int onSpot(int stp, int spd);
    int moveInDirection(int stp, int spd, double yMove, double xMove, double zMove);
    int stepIn(int stp, int spd, double yMove, double xMove, double zMove);
    int walk(int stp, int spd, double yMove, double xMove, double zMove);
    int stepOut(int stp, int spd);
};

#endif
