#ifndef LED_H__
#define LED_H__

#include "Ch.h"

/*
 * class for led control
 */
class Led{
  private:
    int red = 0; //red variable
    int green = 0; //green variable
    int blue = 0; // blue variable
    bool serial = false; //serial flag

  public:
    void setColors(int r, int g, int b); //turns the led on with the set colors
    void toggleColors(Ch* ch); //sets the correct colors
    void setRed(int red); //setter for red
    void setBlue(int blue); //setter for blue
    void setGreen(int green); // setter for green
    int getRed(); //getter for red
    int getBlue(); // getter for blue 
    int getGreen(); //getter for green
    void setSer(bool serial); //setter of serial flag
     
};

#endif
