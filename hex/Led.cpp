#include "Led.h"
#include "Ch.h"
#include <Arduino.h>

void Led::setColors(int r, int g, int b){
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

void Led::toggleColors(Ch* ch){
  (ch->isButtonToggeled(0))?setRed(255):setRed(0);
  (ch->isButtonToggeled(2))?setGreen(255):setGreen(0);
  (ch->isButtonToggeled(3))?setBlue(255):setBlue(0);
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
