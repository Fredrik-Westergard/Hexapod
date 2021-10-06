#include "Led.h"
#include "Ch.h"
#include <Arduino.h>

/*
 * class for led control
 */

//turns the led on with the right color
void Led::setColors(int r, int g, int b){
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

//sets the right color
void Led::toggleColors(Ch* ch){
  bool rec = ch->getMilRec()+200 > (int) millis();
  bool arm = ch->isButtonToggled(0);
  bool kin = ch->isButtonToggled(3);
  bool spt = ch->isButtonToggled(2);
  bool mov = ch->isButtonToggled(4);
  bool ser = serial;

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

//sets red
void Led::setRed(int red){
  this->red = red;
}

//sets blue
void Led::setBlue(int blue){
  this->blue = blue;
}

//sets green
void Led::setGreen(int green){
  this->green = green;
}

//gets red
int Led::getRed(){
  return red;
}

//gets blue
int Led::getBlue(){
  return blue;
}

// gets green
int Led::getGreen(){
  return green;
}

//set serial flag
void Led::setSer(bool serial){
  this->serial = serial;
}
