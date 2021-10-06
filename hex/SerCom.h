#ifndef SERCOM_H__
#define SERCOM_H__

#include "Walk.h"
#include "List.h"
#include "Node.h"

/*
 * class for serial communication 
 */
class SerCom{
  private:
    List* list = new List(); //linked list for memory
    bool armed = false; //armed flag
    bool memory = false; //memory flag
    bool autonomous = false; //autonomous flag
    double stepLength[3] = {0,0,0}; //step length
    int distance[10] = {30,30,30,30,30,30,30,30,30,30}; //distance filter variable
    int stepAmount = 0; //amount of steps
    void applySerialInput(double x, double y, double z); //funtion to apply serial input
    void switchMemory(); //function to switch memory on/off
    
  public:
    SerCom(); //constructor
    void checkSerial(); //function to check if there's serial to read
    int serialMove(Walk* walk, int stp, int spd); //function to move based on serial command
    int autonomousMovement(Walk* walk, int stp, int spd); //function to move autonomously
    int getDistance(Walk* walk); //getter of filtered distance
    bool isArmed(); //getter of armed flag
    bool isAutonomous(); //getter of autonomous flag
};

#endif
