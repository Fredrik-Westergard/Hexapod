#include "Walk.h"
#include <Arduino.h>

/*
 * class for walking
 */

//function to walk on the spot
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

//function to move in chosen direction
int Walk::moveInDirection(int stp, int spd, double yMove, double xMove, double zMove){
  if(ultra.getDistance() < 25 && yMove > 0){
    yMove = 0;
  }
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

//function to take the first step
int Walk::stepIn(int stp, int spd, double yMove, double xMove, double zMove){
  rnd = 0;
  steps = 0;
  if(stp == 0 && (int) millis() > stpMillis + spd){   
    leg.setZOf(120,-20,120,0,100,0); //lift legs, three #1
    leg.setYOf(yMove,0,yMove,0,yMove,0); //move three #1 y-axis
    leg.setXOf(xMove,0,xMove,0,xMove,0); //move three #1 x-axis
    leg.setZAo(zMove,0,zMove,0,zMove,0);
    yLast = yMove;
    xLast = xMove;
    zLast = zMove;
    stpMillis = millis();
    stp++;
  }
  else if(stp == 1 && (int) millis() > stpMillis + spd){
    steps++;
    leg.setZOf(0,0,0,0,0,0); //put leg down
    leg.setYOf(0,-yLast,0,-yLast,0,-yLast); //move forward leg to 0 and ground leg to negative of what forward leg was, on three #1
    leg.setXOf(0,-xLast,0,-xLast,0,-xLast); //move side leg to 0 and ground leg to negative of what side leg was, on three #1
    leg.setZAo(0,-zLast,0,-zLast,0,-zLast);
    stpMillis = millis();
    walkToggle = !walkToggle;
    stp++;
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  
  return stp;
}

//function to walk
int Walk::walk(int stp, int spd, double yMove, double xMove, double zMove){
  rnd = 0;
  if(stp == 0 && (int) millis() > stpMillis + spd){    
    leg.setZOf(120,-20,120,0,100,0);
    leg.setYOf(yMove,-yLast,yMove,-yLast,yMove,-yLast); 
    leg.setXOf(xMove,-xLast,xMove,-xLast,xMove,-xLast);
    leg.setZAo(zMove,-zLast,zMove,-zLast,zMove,-zLast);
    yLast = yMove;
    xLast = xMove;
    zLast = zMove;
    stpMillis = millis();
    stp++;
  }
  else if(stp == 1 && (int) millis() > stpMillis + spd){
    steps++;
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(yLast,-yLast,yLast,-yLast,yLast,-yLast);
    leg.setXOf(xLast,-xLast,xLast,-xLast,xLast,-xLast);
    leg.setZAo(zLast,-zLast,zLast,-zLast,zLast,-zLast);
    stpMillis = millis();
    stp++;
  }
  if(stp == 2 && (int) millis() > stpMillis + spd){    
    leg.setZOf(0,100,0,120,-20,120);
    leg.setYOf(-yLast,yMove,-yLast,yMove,-yLast,yMove);
    leg.setXOf(-xLast,xMove,-xLast,xMove,-xLast,xMove);
    leg.setZAo(-zLast,zMove,-zLast,zMove,-zLast,zMove);
    yLast = yMove;
    xLast = xMove;
    zLast = zMove;
    stpMillis = millis();
    stp++;
  }
  else if(stp == 3 && (int) millis() > stpMillis + spd){
    steps++;
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(-yLast,yLast,-yLast,yLast,-yLast,yLast);
    leg.setXOf(-xLast,xLast,-xLast,xLast,-xLast,xLast);
    leg.setZAo(-zLast,zMove,-zLast,zMove,-zLast,zMove);
    stpMillis = millis();
    stp = 0;
  }
  leg.calculateAngles(120, 0, 0, 0, 0, 0);
  mv.moveLegs(&leg);
  
  return stp;
}

//function to take last step
int Walk::stepOut(int stp,int spd){
  if(stp == 0 && (int) millis() > stpMillis + spd){    
    leg.setZOf(120,-20,120,0,100,0);
    leg.setYOf(0,-yLast,0,-yLast,0,-yLast); 
    leg.setXOf(0,-xLast,0,-xLast,0,-xLast);
    leg.setZAo(0,-zLast,0,-zLast,0,-zLast);
    yLast = 0;
    xLast = 0;
    zLast = 0;
    stpMillis = millis();
    stp++;
    rnd++;
  }
  else if(stp == 1 && (int) millis() > stpMillis + spd){
    steps++;
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(yLast,-yLast,yLast,-yLast,yLast,-yLast);
    leg.setXOf(xLast,-xLast,xLast,-xLast,xLast,-xLast);
    leg.setZAo(zLast,-zLast,zLast,-zLast,zLast,-zLast);
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
    leg.setZOf(0,100,0,120,-20,120);
    leg.setYOf(-yLast,0,-yLast,0,-yLast,0);
    leg.setXOf(-xLast,0,-xLast,0,-xLast,0);
    leg.setZAo(-zLast,0,-zLast,0,-zLast,0);
    yLast = 0;
    xLast = 0;
    zLast = 0;
    stpMillis = millis();
    stp++;
    rnd++;
  }
  else if(stp == 3 && (int) millis() > stpMillis + spd){
    steps++;
    leg.setZOf(0,0,0,0,0,0);
    leg.setYOf(-yLast,yLast,-yLast,yLast,-yLast,yLast);
    leg.setXOf(-xLast,xLast,-xLast,xLast,-xLast,xLast);
    leg.setZAo(-zLast,zLast,-zLast,zLast,-zLast,zLast);
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

//getter of steps
int Walk::getSteps(){
  return steps;
}

//setter of steps
void Walk::setSteps(int steps){
  this->steps = steps;
}

//getter of distance from ultrasonci sensor
int Walk::getDistance(){
  return ultra.getDistance();
}
