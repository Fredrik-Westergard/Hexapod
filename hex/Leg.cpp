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
  //negative modifier for if the angles are negative
  int xNeg[6] = {1,1,1,1,1,1};
  int yNeg[6] = {1,1,1,1,1,1};
  
  double yA[6];   //y angle
  double yLen[6]; //y leg length
  double yOt[6];  //y offset total

  double xA[6];   //x angle
  double xLen[6]; //x leg length
  double xOt[6];  //x offset total

  double yAd[6];  //second angle in y triangle

  //set x/yNeg and make x/yOt positive
  for(int i=0; i<6; i++){
    xNeg[i] = (xOffset+xOf[i]<=0)?-1:1;
    yNeg[i] = (yOffset+yOf[i]<=0)?-1:1;

    yOt[i] = (yOffset+yOf[i])*yNeg[i];
    xOt[i] = (xOffset+xOf[i])*xNeg[i];
  }

  //calculate new leg length with y offfset
  yLen[0] = lawOfCosinesSAS(yOt[0],LEGLEN,(45*yNeg[0])+90);
  yLen[1] = lawOfCosinesSAS(yOt[1],LEGLEN,90*yNeg[1]);
  yLen[2] = lawOfCosinesSAS(yOt[2],LEGLEN,(45*yNeg[2]*-1)+90);
  yLen[3] = lawOfCosinesSAS(yOt[3],LEGLEN,(45*yNeg[3])+90);
  yLen[4] = lawOfCosinesSAS(yOt[4],LEGLEN,90*yNeg[4]);
  yLen[5] = lawOfCosinesSAS(yOt[5],LEGLEN,(45*yNeg[5]*-1)+90);

  //calculate new y angle
  yA[0] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[0],yOt[0]))*yNeg[0]*-1;
  yA[1] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[1],yOt[1]))*yNeg[1]*-1;
  yA[2] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[2],yOt[2]))*yNeg[2]*-1;
  yA[3] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[3],yOt[3]))*yNeg[3];
  yA[4] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[4],yOt[4]))*yNeg[4];
  yA[5] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[5],yOt[5]))*yNeg[5];

  //calculate second y angle to make caluclating x angle possible
  yAd[0] = 90+(degreesConverter(asin((sin(((45*yNeg[0])+90)/(180.0/M_PI))*LEGLEN)/yLen[0]))*xNeg[0]);
  yAd[1] = 90+(degreesConverter(asin((sin((90*yNeg[1])/(180.0/M_PI))*LEGLEN)/yLen[1]))*xNeg[1]);
  yAd[2] = 90+(degreesConverter(asin((sin(((45*yNeg[2])+90)/(180.0/M_PI))*LEGLEN)/yLen[2]))*xNeg[2]);
  yAd[3] = 90+(degreesConverter(asin((sin(((45*yNeg[3])+90)/(180.0/M_PI))*LEGLEN)/yLen[3]))*xNeg[3]*-1);  
  yAd[4] = 90+(degreesConverter(asin((sin((90*yNeg[4])/(180.0/M_PI))*LEGLEN)/yLen[4]))*xNeg[4]*-1);
  yAd[5] = 90+(degreesConverter(asin((sin(((45*yNeg[5])+90)/(180.0/M_PI))*LEGLEN)/yLen[5]))*xNeg[5]*-1);

  //calculate new leg length for x triangle
  xLen[0] = lawOfCosinesSAS(xOt[0],yLen[0],yAd[0]);
  xLen[1] = lawOfCosinesSAS(xOt[1],yLen[1],yAd[1]);
  xLen[2] = lawOfCosinesSAS(xOt[2],yLen[2],yAd[2]);
  xLen[3] = lawOfCosinesSAS(xOt[3],yLen[3],yAd[3]);
  xLen[4] = lawOfCosinesSAS(xOt[4],yLen[4],yAd[4]);
  xLen[5] = lawOfCosinesSAS(xOt[5],yLen[5],yAd[5]);

  //calculate new x angle, angle C
  xA[0] = yA[0]-(degreesConverter(lawOfCosinesSSS(xLen[0],yLen[0],xOt[0]))*xNeg[0]*-1);
  xA[1] = yA[1]-(degreesConverter(lawOfCosinesSSS(xLen[1],yLen[1],xOt[1]))*xNeg[1]);
  xA[2] = yA[2]-(degreesConverter(lawOfCosinesSSS(xLen[2],yLen[2],xOt[2]))*xNeg[2]);
  xA[3] = yA[3]-(degreesConverter(lawOfCosinesSSS(xLen[3],yLen[3],xOt[3]))*xNeg[3]*-1);
  xA[4] = yA[4]-(degreesConverter(lawOfCosinesSSS(xLen[4],yLen[4],xOt[4]))*xNeg[4]*-1);
  xA[5] = yA[5]-(degreesConverter(lawOfCosinesSSS(xLen[5],yLen[5],xOt[5]))*xNeg[5]);
  
  for(int i=0; i<6; i++){
    double dLen = calculateDesiredLength(zOffset-zOf[i], xLen[i]); //set desired leg length
    
    setAngleA(degreesConverter(lawOfCosinesSSS(TIBIA,SHIN,dLen)),i); //calculate and set angle A, shin-tibia joint
    setAngleB(
      360-(90+(degreesConverter(asin(xLen[i]/dLen))
      +degreesConverter(lawOfCosinesSSS(dLen,TIBIA,SHIN)))),i); //calculate and set angle B, tibia-hip joint
    setAngleC(xA[i],i); //set angle C, hip-body joint
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
