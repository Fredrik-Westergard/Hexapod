#include "Leg.h"
#include <math.h>

//function to calculate law of cosines
double Leg::lawOfCosines(double a, double b, double c){
  return acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
}

//function to convert radians to degrees
double Leg::degreesConverter(double radian){
  return radian*(180.0/M_PI);
}

//function to calculate desired length
double Leg::calculateDesiredLength(double zOffset){
  return sqrt(pow(LEGLEN,2)+pow(zOffset,2));
}

//function to calculate all angles, might get split off into smaller functions later
void Leg::calculateAngles(double zOffset){

  for(int i=0; i<6; i++){
    double dlen = calculateDesiredLength(zOffset-zOf[i]);
    setAngleA(degreesConverter(lawOfCosines(TIBIA,SHIN,dlen)),i);
    setAngleB(
      360-(90+(degreesConverter(asin(LEGLEN/dlen))
      +degreesConverter(lawOfCosines(dlen,TIBIA,SHIN)))),i);
    setAngleC(0,i);
  }
}

//angle getters and setters
void Leg::setAngleA(double angleA, int pos){
  this->angleA[pos] = angleA;
}

void Leg::setAngleB(double angleB, int pos){
  this->angleB[pos] = angleB;
}

void Leg::setAngleC(double angleC, int pos){
  this->angleC[pos] = angleC;
}

double Leg::getAngleA(int pos){
  return this->angleA[pos];
}

double Leg::getAngleB(int pos){
  return this->angleB[pos];
}

double Leg::getAngleC(int pos){
  return this->angleC[pos];
}
