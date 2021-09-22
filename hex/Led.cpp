#include "Led.h"
#include "Ch.h"
#include <Arduino.h>

void Led::setColors(int r, int g, int b){
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

void Led::toggleColors(Ch* ch){
  bool rec = ch->getMilRec()+200 > (int)millis();
  bool arm = ch->isButtonToggled(0);
  bool kin = ch->isButtonToggled(3);
  bool spt = ch->isButtonToggled(2);
  bool mov = ch->isButtonToggled(4);
  bool ser = false;

  if(!rec){
    setRed(0);
    setGreen(0);
    setBlue(0);
    if(ser){
      setRed(0);
      setGreen(255);
      setBlue(255);
    }
  }
  else{
    setRed(255);
    setGreen(255);
    setBlue(0);
    if(arm){
      setRed(255);
      setGreen(0);
      setBlue(0);
      if(kin && !spt && !mov){
        setRed(0);
        setGreen(255);
        setBlue(0);
      }
      else if(spt && !kin && !mov){
        setRed(255);
        setGreen(0);
        setBlue(255);
      }
      else if(mov && !spt && !kin){
        setRed(0);
        setGreen(0);
        setBlue(255);
      }
      else if(mov || spt || kin){
        setRed(255);
        setGreen(255);
        setBlue(255);
      }
    }
  }
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
