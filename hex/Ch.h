#ifndef CH_H__
#define CH_H__

#include <Arduino.h>

class Ch{

  private:
    int milB[14]; //milliseconds for button presses
    int channel[16]; //channels of the controller
    char str[32]; //string received from radio
    bool arm = false; //arm boolean, if false the robot can't move

    void compileData();
    void interpretData();

  public:
    Ch();
    void buildData(char* str);
    bool isArmed();
};
#endif
