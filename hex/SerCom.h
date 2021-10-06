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
    bool autonomous = false;
    double stepLength[3] = {0,0,0};
    int distance[10] = {30,30,30,30,30,30,30,30,30,30};
    int stepAmount = 0;
    void applySerialInput(double x, double y, double z);
    void switchMemory();
    
  public:
    SerCom();
    void checkSerial();
    int serialMove(Walk* walk, int stp, int spd);
    int autonomousMovement(Walk* walk, int stp, int spd);
    int getDistance(Walk* walk);
    bool isArmed();
    bool isAutonomous();
};

#endif
