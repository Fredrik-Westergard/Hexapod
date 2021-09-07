#ifndef CH_H__
#define CH_H__

#include <Arduino.h>

class Ch{

  private:
    int milB[14]; //milliseconds for button presses
    int channel[16]; //channels of the controller
    char str[32]; //string received from radio
    bool arm = false; //arm boolean, if false the robot can't move
    double zOffset = 75; //height, set 75 default, change if signal is received
    double yOffset = 0;
    double xOffset = 0;
    
    void compileData(); //data compiler, converts radio string to channels
    void interpretData(); //data interpretor, maps channels to axes

  public:
    void buildData(char* str); //data builder, compiles and interprets
    bool isArmed(); //true if armed
    double getZOffset(); //getter of height
    double getYOffset();
    double getXOffset();
};
#endif
