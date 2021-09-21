#include "Led.h"
#include "Ch.h"
#include <Arduino.h>

void Led::setColors(int r, int g, int b){
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

void Led::toggleColors(Ch* ch){
  int r = (ch->isButtonToggled(0))?255:0;
  int g = (ch->isButtonToggled(3))?255:0;
  int b = (ch->isButtonToggled(2))?100:0;
  b = (ch->isButtonToggled(4))?255:b;
  setRed(r);
  setGreen(g);
  setBlue(b);
}

void Led::setRed(int red){
  this->red = red;
}

void Led::setBlue(int blue){
  this->blue = blue;
}

void Led::setGreen(int green){
  this->green = green;
}

int Led::getRed(){
  return red;
}

int Led::getBlue(){
  return blue;
}

int Led::getGreen(){
  return green;
}
