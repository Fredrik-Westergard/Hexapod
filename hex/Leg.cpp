#include "Leg.h"
#include "Ch.h"
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

double Leg::calculateHeronsFormula(double a, double b){
  double c = (a+a+b)/2;
  return sqrt(c*(c-a)*(c-a)*(c-b))/(0.5*a);
}

//function to calculate all angles, might get split off into smaller functions later
void Leg::calculateAngles(Ch ch){

  //get offsets and angles from Ch
  double zOffset = ch.getZOffset();
  double yOffset = ch.getYOffset();
  double xOffset = ch.getXOffset();
  double zAngle = ch.getZAngle();
  double yAngle = ch.getYAngle();
  double xAngle = ch.getXAngle();
  
  //negative modifier for if the angles are negative
  int xNt[6] = {1,1,1,1,1,1};
  int yNt[6] = {1,1,1,1,1,1};
  int xNr2[6] = {1,1,1,1,1,1};
  
  double yA[6];   //y angle
  double yLen[6]; //y leg length
  double yOt[6];  //y offset total

  double xA[6];   //x angle
  double xLen[6]; //x leg length
  double xOt[6];  //x offset total

  double yAd[6];  //second angle in y triangle

  double zOfr[6];
  double xOfr[6];
  double yOfr[6];

  //set x/yNt and make x/yOt positive
  for(int i=0; i<6; i++){
    double bodyX = (i == 1 || i == 4)?(BODYX2+LEGLEN):(BODYX1+(sin(45/(180.0/M_PI))*LEGLEN));
    int xNr = (xAngle < 0)?-1:1;
    xNr2[i] = (i < 3)?-1:1;
    
    double temp = 2*bodyX*cos(((180-(xAngle*xNr))/2)/(180.0/M_PI));
    zOfr[i] = calculateHeronsFormula(bodyX,temp)*xNr;
    xOfr[i] = sqrt(pow(temp,2)-pow(zOfr[i],2));
    
    xNt[i] = (xOffset+xOf[i]-(xOfr[i]*xNr2[i]*-1)<=0)?-1:1;
    yNt[i] = (yOffset+yOf[i]<=0)?-1:1;
    yOt[i] = (yOffset+yOf[i])*yNt[i];
    xOt[i] = (xOffset+xOf[i]-(xOfr[i]*xNr2[i]*-1))*xNt[i];
  }
  
  //calculate new leg length with y offfset
  yLen[0] = lawOfCosinesSAS(yOt[0],LEGLEN,(45*yNt[0])+90);
  yLen[1] = lawOfCosinesSAS(yOt[1],LEGLEN,90*yNt[1]);
  yLen[2] = lawOfCosinesSAS(yOt[2],LEGLEN,(45*yNt[2]*-1)+90);
  yLen[3] = lawOfCosinesSAS(yOt[3],LEGLEN,(45*yNt[3])+90);
  yLen[4] = lawOfCosinesSAS(yOt[4],LEGLEN,90*yNt[4]);
  yLen[5] = lawOfCosinesSAS(yOt[5],LEGLEN,(45*yNt[5]*-1)+90);

  //calculate new y angle
  yA[0] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[0],yOt[0]))*yNt[0]*-1;
  yA[1] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[1],yOt[1]))*yNt[1]*-1;
  yA[2] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[2],yOt[2]))*yNt[2]*-1;
  yA[3] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[3],yOt[3]))*yNt[3];
  yA[4] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[4],yOt[4]))*yNt[4];
  yA[5] = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen[5],yOt[5]))*yNt[5];

  //calculate second y angle to make caluclating x angle possible
  yAd[0] = 90+(degreesConverter(asin((sin(((45*yNt[0])+90)/(180.0/M_PI))*LEGLEN)/yLen[0]))*xNt[0]);
  yAd[1] = 90+(degreesConverter(asin((sin((90*xNt[1])/(180.0/M_PI))*LEGLEN)/yLen[1])));
  yAd[2] = 90+(degreesConverter(asin((sin(((45*yNt[2])+90)/(180.0/M_PI))*LEGLEN)/yLen[2]))*xNt[2]);
  yAd[3] = 90+(degreesConverter(asin((sin(((45*yNt[3])+90)/(180.0/M_PI))*LEGLEN)/yLen[3]))*xNt[3]*-1);  
  yAd[4] = 90+(degreesConverter(asin((sin((90*xNt[4])/(180.0/M_PI))*LEGLEN)/yLen[4]))*-1);
  yAd[5] = 90+(degreesConverter(asin((sin(((45*yNt[5])+90)/(180.0/M_PI))*LEGLEN)/yLen[5]))*xNt[5]*-1);

  //calculate new leg length for x triangle
  xLen[0] = lawOfCosinesSAS(xOt[0],yLen[0],yAd[0]);
  xLen[1] = lawOfCosinesSAS(xOt[1],yLen[1],yAd[1]);
  xLen[2] = lawOfCosinesSAS(xOt[2],yLen[2],yAd[2]);
  xLen[3] = lawOfCosinesSAS(xOt[3],yLen[3],yAd[3]);
  xLen[4] = lawOfCosinesSAS(xOt[4],yLen[4],yAd[4]);
  xLen[5] = lawOfCosinesSAS(xOt[5],yLen[5],yAd[5]);

  //calculate new x angle, angle C
  xA[0] = yA[0]-(degreesConverter(lawOfCosinesSSS(xLen[0],yLen[0],xOt[0]))*xNt[0]*-1);
  xA[1] = yA[1]-(degreesConverter(lawOfCosinesSSS(xLen[1],yLen[1],xOt[1]))*xNt[1]);
  xA[2] = yA[2]-(degreesConverter(lawOfCosinesSSS(xLen[2],yLen[2],xOt[2]))*xNt[2]);
  xA[3] = yA[3]-(degreesConverter(lawOfCosinesSSS(xLen[3],yLen[3],xOt[3]))*xNt[3]*-1);
  xA[4] = yA[4]-(degreesConverter(lawOfCosinesSSS(xLen[4],yLen[4],xOt[4]))*xNt[4]*-1);
  xA[5] = yA[5]-(degreesConverter(lawOfCosinesSSS(xLen[5],yLen[5],xOt[5]))*xNt[5]);
  
  for(int i=0; i<6; i++){
    double dLen = calculateDesiredLength(zOffset-zOf[i]-(zOfr[i]*xNr2[i]), xLen[i]); //set desired leg length
    
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
