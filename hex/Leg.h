#ifndef LEG_H__
#define LEG_H__

#include "Ch.h"

class Leg{
  private:
    const double SHIN = 120; //shin of robot leg constant
    const double TIBIA = 65; //tibia of robot leg constant
    const double HIP = 50; //hip of robot leg constant
    const double BODYX1 = 58;
    const double BODYX2 = 90;
    const double LEGLEN = 110; //leg length constant, the length the tip of the legs are from the hip joint, in mm
    
    double angleA[6]; //angle of shin motor
    double angleB[6]; //angle of tibia motor
    double angleC[6]; //angle of hip motor

    double zOf[6] = {0,0,0,0,0,0}; //individual z offset
    double xOf[6] = {0,0,0,0,0,0}; //individual x offset
    double yOf[6] = {0,0,0,0,0,0}; //individual y offset
    
    double lawOfCosinesSSS(double a, double b, double c); //calculate law of cosines when you have all sides 
    double lawOfCosinesSAS(double a, double b, double angle); //calculate law of cosines when you have two sides and one angle between them
    double degreesConverter(double radian); //convert from radians to degrees
    double calculateDesiredLength(double zOffset, double dLen); //desired length calculator
    double calculateHeronsFormula(double a, double b);
public:
    void calculateAngles(Ch ch);  //calculates all angles and sets them
    void setAngleA(double angleA, int pos); //set A angle, shin-tibia
    void setAngleB(double angleB, int pos); //set B angle, tibia-hip
    void setAngleC(double angleC, int pos); //set C angle, hip-body
    double getAngleA(int pos); //get A angle, shin-tibia
    double getAngleB(int pos); //get B angle, tibia-hip
    double getAngleC(int pos); //get C angle, hip-body
};

#endif
