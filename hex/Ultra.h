#ifndef ULTRA_H__
#define ULTRA_H__

/*
 * class for ultrasonic sensor
 */
class Ultra{
  private:
    int trig = 16; //trigger pin
    int echo = 17; //echo pin
  public:
    Ultra(); //constructor
    int getDistance(); //getter of distance
};

#endif
