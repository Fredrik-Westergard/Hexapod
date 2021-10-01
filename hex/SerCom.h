#ifndef SERCOM_H__
#define SERCOM_H__

#include "Walk.h"
#include "List.h"
#include "Node.h"

class SerCom{
  private:
    List* list = new List();
    bool armed = false;
    bool memory = false;
    bool executing = false;
    double stepLength[3] = {0,0,0};
    int stepAmount = 0;
    void applySerialInput(double x, double y, double z);
    void switchMemory();
    
  public:
    void checkSerial();
    int serialMove(Walk* walk, int stp, int spd);
    bool isArmed();
};

#endif
