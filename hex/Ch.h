#ifndef CH_H__
#define CH_H__

#include <Arduino.h>

class Ch{

  private:
    int milB[10] = {0,0,0,0,0,0,0,0,0,0}; //milliseconds for button presses
    int channel[16]; //channels of the controller
    char* str; //string received from radio
    bool buttons[10] = {false,false,false,false,false,
                        false,false,false,false,false}; //arm boolean, if false the robot can't move
    double zOffset = 75; //height global offset, set 75 default, change if signal is received
    double yOffset = 0; //fron/back translation global offset
    double xOffset = 0; //side/side translation global offset
    double zAngle = 0; //yaw angle
    double yAngle = 0; //pitch angle
    double xAngle = 0; //roll angle
    double yMove = 0;
    double xMove = 0;
    double zMove = 0;
    
    void compileData(); //data compiler, converts radio string to channels
    void interpretData(); //data interpretor, maps channels to axes

  public:
    void buildData(char* str); //data builder, compiles and interprets
    bool isButtonToggled(int num); //true if Toggeled
    double getZOffset(); //getter of height
    double getYOffset(); //getter of y offset
    double getXOffset(); //getter of x offset
    double getZAngle(); //getter of z angle
    double getYAngle(); //getter of y angle
    double getXAngle(); //getter of x angle
    double getYMove();
    double getXMove();
    double getZMove();
};
#endif
