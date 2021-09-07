#include "Leg.h"
#include <math.h>
#include <Arduino.h>

//function to calculate law of cosines
double Leg::lawOfCosinesSSS(double a, double b, double c){
  return acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
}

double Leg::lawOfCosinesSAS(double b, double a, double angle){
  return sqrt((pow(a,2)+pow(b,2))-(2*a*b*cos(angle/(180.0/M_PI))));
}

//function to convert radians to degrees
double Leg::degreesConverter(double radian){
  return radian*(180.0/M_PI);
}

//function to calculate desired length
double Leg::calculateDesiredLength(double zOffset, double dLen){
  return sqrt(pow(dLen,2)+pow(zOffset,2));
}

//function to calculate all angles, might get split off into smaller functions later
void Leg::calculateAngles(double zOffset, double yOffset, double xOffset){

  int xNeg[6] = {1,1,1,1,1,1};
  int yNeg[6] = {1,1,1,1,1,1};
  
  double yA[6];
  double y[6];
  double yOt[6];
  double xOt[6];
  
  for(int i=0; i<6; i++){
    xNeg[i] = (xOffset+xOf[i]<=0)?-1:1;
    yNeg[i] = (yOffset+yOf[i]<=0)?-1:1;

    yOt[i] = (yOffset+yOf[i])*yNeg[i];
    xOt[i] = (xOffset+xOf[i])*xNeg[i];
    Serial.println(yOt[i]);
  }

  y[0] = lawOfCosinesSAS(yOt[0],LEGLEN,(45*yNeg[0])+90);
  y[1] = lawOfCosinesSAS(yOt[1],LEGLEN,90*yNeg[1]);
  y[2] = lawOfCosinesSAS(yOt[2],LEGLEN,(45*yNeg[2]*-1)+90);
  y[3] = lawOfCosinesSAS(yOt[3],LEGLEN,(45*yNeg[3])+90);
  y[4] = lawOfCosinesSAS(yOt[4],LEGLEN,90*yNeg[4]);
  y[5] = lawOfCosinesSAS(yOt[5],LEGLEN,(45*yNeg[5]*-1)+90);

  yA[0] = degreesConverter(lawOfCosinesSSS(LEGLEN,y[0],yOt[0]))*yNeg[0]*-1;
  yA[1] = degreesConverter(lawOfCosinesSSS(LEGLEN,y[1],yOt[1]))*yNeg[1]*-1;
  yA[2] = degreesConverter(lawOfCosinesSSS(LEGLEN,y[2],yOt[2]))*yNeg[2]*-1;
  yA[3] = degreesConverter(lawOfCosinesSSS(LEGLEN,y[3],yOt[3]))*yNeg[3];
  yA[4] = degreesConverter(lawOfCosinesSSS(LEGLEN,y[4],yOt[4]))*yNeg[4];
  yA[5] = degreesConverter(lawOfCosinesSSS(LEGLEN,y[5],yOt[5]))*yNeg[5];

  Serial.println(y[0]);
  Serial.println(yA[0]);
  
  for(int i=0; i<6; i++){
    double dLen = calculateDesiredLength(zOffset-zOf[i], y[i]);
    
    setAngleA(degreesConverter(lawOfCosinesSSS(TIBIA,SHIN,dLen)),i);
    setAngleB(
      360-(90+(degreesConverter(asin(y[i]/dLen))
      +degreesConverter(lawOfCosinesSSS(dLen,TIBIA,SHIN)))),i);
      setAngleC(0,i);
    setAngleC(yA[i],i);
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
