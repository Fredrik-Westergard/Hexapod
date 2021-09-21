#ifndef LED_H__
#define LED_H__

#include "Ch.h"

class Led{
  private:
    int red = 0;
    int green = 0;
    int blue = 0;

  public:
    void setColors(int r, int g, int b);
    void toggleColors(Ch* ch);
    void setRed(int red);
    void setBlue(int blue);
    void setGreen(int green);
    int getRed();
    int getBlue();
    int getGreen();
     
};

#endif
