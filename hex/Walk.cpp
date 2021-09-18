#include "Walk.h"
#include <Arduino.h>

int Walk::onSpot(int stp, int spd){
  if(stp == 1 && millis() > stpMillis + spd){
    leg.setZOf(120,0,120,20,100,20);
    stpMillis = millis();
    stp++;
  }
  else if(stp == 3 && millis() > stpMillis + spd){
    leg.setZOf(20,100,20,120,0,120);
    stpMillis = millis();
    stp++;
  }
  else if((stp == 0 || stp == 2) && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0);
    stpMillis = millis();
    stp++;
    Serial.println("hello");
  }
  leg.calculateAnglesWalk(140, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  if(stp > 3){
    stp = 0;
  }
  return stp;
}
