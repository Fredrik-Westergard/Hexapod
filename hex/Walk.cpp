#include "Walk.h"
#include <Arduino.h>

int Walk::onSpot(int stp, int spd){
  if(stp == 1 && (int) millis() > stpMillis + spd){
    leg.setZOf(100,0,100,20,80,20);
    stpMillis = millis();
    stp++;
  }
  else if(stp == 3 && (int) millis() > stpMillis + spd){
    leg.setZOf(20,80,20,100,0,100);
    stpMillis = millis();
    stp++;
  }
  else if((stp == 0 || stp == 2) && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0);
    stpMillis = millis();
    stp++;
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  if(stp > 3){
    stp = 0;
  }
  return stp;
}

int Walk::moveInDirection(int stp, int spd, double yMove, double xMove, double zMove){
  if(!walkToggle && ((yMove > 5 || yMove < -5) || (xMove > 5 || xMove < -5) || (zMove > 5 || zMove < -5))){
    return stepIn(stp, spd, yMove, xMove, zMove);
  }
  else if(walkToggle && ((yMove > 5 || yMove < -5) || (xMove > 5 || xMove < -5) || (zMove > 5 || zMove < -5))){
    return walk(stp, spd, yMove, xMove, zMove);
  }
  else if(walkToggle && ((yMove < 5 || yMove > -5) || (xMove < 5 || xMove > -5) || (zMove < 5 || zMove > -5))){
    return stepOut(stp, spd);
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  return stp;
}

int Walk::stepIn(int stp, int spd, double yMove, double xMove, double zMove){
  rnd = 0;
  if(stp == 0 && (int) millis() > stpMillis + spd){    
    leg.setZOf(100,0,100,20,80,20); //lift legs, three #1
    leg.setYOf(yMove,0,yMove,0,yMove,0); //move three #1 y-axis
    leg.setXOf(xMove,0,xMove,0,xMove,0); //move three #1 x-axis
    yLast = yMove;
    xLast = xMove;
    stpMillis = millis();
    stp++;
  }
  else if(stp == 1 && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0); //put leg down
    leg.setYOf(0,-yLast,0,-yLast,0,-yLast); //move forward leg to 0 and ground leg to negative of what forward leg was, on three #1
    leg.setXOf(0,-xLast,0,-xLast,0,-xLast); //move side leg to 0 and ground leg to negative of what side leg was, on three #1
    stpMillis = millis();
    walkToggle = !walkToggle;
    stp++;
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  
  return stp;
}

int Walk::walk(int stp, int spd, double yMove, double xMove, double zMove){
  rnd = 0;
  if(stp == 0 && (int) millis() > stpMillis + spd){    
    leg.setZOf(100,0,100,20,80,20);
    leg.setYOf(yMove,-yLast,yMove,-yLast,yMove,-yLast); 
    leg.setXOf(xMove,-xLast,xMove,-xLast,xMove,-xLast);
    yLast = yMove;
    xLast = xMove;
    stpMillis = millis();
    stp++;
  }
  else if(stp == 1 && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(yLast,-yLast,yLast,-yLast,yLast,-yLast);
    leg.setXOf(xLast,-xLast,xLast,-xLast,xLast,-xLast);
    stpMillis = millis();
    stp++;
  }
  if(stp == 2 && (int) millis() > stpMillis + spd){    
    leg.setZOf(20,80,20,100,0,100);
    leg.setYOf(-yLast,yMove,-yLast,yMove,-yLast,yMove);
    leg.setXOf(-xLast,xMove,-xLast,xMove,-xLast,xMove);
    yLast = yMove;
    xLast = xMove;
    stpMillis = millis();
    stp++;
  }
  else if(stp == 3 && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(-yLast,yLast,-yLast,yLast,-yLast,yLast);
    leg.setXOf(-xLast,xLast,-xLast,xLast,-xLast,xLast);
    stpMillis = millis();
    stp = 0;
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  
  return stp;
}

int Walk::stepOut(int stp,int spd){
  if(stp == 0 && (int) millis() > stpMillis + spd){    
    leg.setZOf(100,0,100,20,80,20);
    leg.setYOf(0,-yLast,0,-yLast,0,-yLast); 
    leg.setXOf(0,-xLast,0,-xLast,0,-xLast);
    yLast = 0;
    xLast = 0;
    stpMillis = millis();
    stp++;
    rnd++;
  }
  else if(stp == 1 && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(yLast,-yLast,yLast,-yLast,yLast,-yLast);
    leg.setXOf(xLast,-xLast,xLast,-xLast,xLast,-xLast);
    stpMillis = millis();
    if(rnd > 0){
      stp = 0;
      rnd = 0;
      walkToggle = !walkToggle;
    }
    else{
      stp++;
    }
  }
  if(stp == 2 && (int) millis() > stpMillis + spd){    
    leg.setZOf(20,80,20,100,0,100);
    leg.setYOf(-yLast,0,-yLast,0,-yLast,0);
    leg.setXOf(-xLast,0,-xLast,0,-xLast,0);
    yLast = 0;
    xLast = 0;
    stpMillis = millis();
    stp++;
    rnd++;
  }
  else if(stp == 3 && (int) millis() > stpMillis + spd){
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(-yLast,yLast,-yLast,yLast,-yLast,yLast);
    leg.setXOf(-xLast,xLast,-xLast,xLast,-xLast,xLast);
    stpMillis = millis();
    if(rnd > 0){
      rnd = 0;
      walkToggle = !walkToggle;
    }
    stp = 0;
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  
  return stp;
}
