#ifndef SERCOM_H__
#define SERCOM_H__

#include "Walk.h"

class SerCom{
  private:
    bool armed = false;
    double stepLength[3] = {0,0,0};
    int stepAmount = 0;
    
    void applySerialInput(double x, double y, double z);
    
  public:
    void checkSerial();
    int serialMove(Walk* walk, int stp, int spd);
    bool isArmed();
};

#endif
