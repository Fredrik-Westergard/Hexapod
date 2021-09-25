#include "Ultra.h"
#include <Arduino.h>

Ultra::Ultra(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}


int Ultra::getDistance(){
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long dur = pulseIn(echo, HIGH);
  return dur*0.034/2;
}
