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
  public:
    int onSpot(int stp, int spd);
  
};

#endif
