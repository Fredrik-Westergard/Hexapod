#include "Leg.h"
#include <math.h>
#include <Arduino.h>

//function to calculate law of cosines for side side side triangle
double Leg::lawOfCosinesSSS(double a, double b, double c){
  return acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
}

//function to calculate law of cosines for side angle side triangle
double Leg::lawOfCosinesSAS(double b, double a, double angle){
  return sqrt((pow(a,2)+pow(b,2))-(2*a*b*cos(radianConverter(angle))));
}

//function to convert radians to degrees
double Leg::degreesConverter(double radian){
  return radian*(180.0/M_PI);
}

//function to convert degrees to radians
double Leg::radianConverter(double degree){
  return degree*(M_PI/180.0);
}

//function to calculate desired length
double Leg::calculateDesiredLength(double zOffset, double dLen){
  return sqrt(pow(dLen,2)+pow(zOffset,2));
}

//function to calculate herons formula, gets height of triangle
double Leg::calculateHeronsFormula(double a, double b){
  double c = (a+a+b)/2;
  return sqrt(c*(c-a)*(c-a)*(c-b))/(0.5*a);
}

//function to calculate all angles, might get split off into smaller functions later
void Leg::calculateAngles(double zOffset, double yOffset, double xOffset, double zAngle, double yAngle, double xAngle){

  for(int i=0; i<6; i++){
    //set body constants
    double bodyX = (i == 1 || i == 4)?(BODYX2+LEGLEN):(BODYX1+(sin(radianConverter(45))*LEGLEN));
    double bodyY = (i == 1 || i == 4)?(LEGLEN):BODYY+(sin(radianConverter(45))*LEGLEN);
    double bodyZ = (i == 1 || i == 4)?(BODYX2+LEGLEN):(lawOfCosinesSAS(LEGLEN,BODYXY,45+BODYA));

    //set "negative-ify" modifiers
    int xNr = (xAngle < 0)?-1:1;
    int yNr = (yAngle < 0)?-1:1;
    int zNr = (zAngle < 0)?-1:1;
    int xN = (i < 3)?-1:1;
    int yNr2 = (i == 0 || i == 3)?-1:1;
    int yNt2 = (i == 2 || i == 5)?-1:1;
    int xNt2 = (i == 0 || i == 3 || i == 4)?-1:1;

    //calculate x rotation
    double temp = 2*bodyX*cos(radianConverter(((180-(xAngle*xNr))/2)));
    double zOfr = (calculateHeronsFormula(bodyX,temp)*xNr)*xN;
    double xOfr = sqrt(pow(temp,2)-pow(zOfr,2));

    //calculate y rotation
    double temp2 = 2*bodyY*cos(radianConverter(((180-(yAngle*yNr))/2)));
    double zOfr2temp = (i != 1 && i != 4)?(calculateHeronsFormula(bodyY,temp2)*yNr)*yNr2:0;
    double zOfr2 = zOfr2temp;
    double yOfr = sqrt(pow(temp2,2)-pow(zOfr2,2))*yNr*-1;

    //calculate z rotation
    double xOfr2 = ((((bodyZ*(sin(radianConverter((ANG[i]+(zAngle*zNr))))))-ZAX[i])*zNr))*xN;
    double yOfr2 = ((((bodyZ*(cos(radianConverter((ANG[i]+(zAngle*zNr))))))-ZAY[i])*zNr))*-1;    

    //combine all x and y offsets and make it positive if it's negative
    int yNt = (yOffset+yOf[i]+yOfr2-(yOfr*yNr2*-1)<=0)?-1:1;    
    int xNt = (xOffset+xOf[i]+xOfr2-(xOfr*xN*-1)<=0)?-1:1;
    double yOt = (yOffset+yOf[i]+yOfr2-(yOfr*yNr2*-1))*yNt;
    double xOt = (xOffset+xOf[i]+xOfr2-(xOfr*xN*-1))*xNt;

    //calculate y translation
    double yLen;
    double yAd;
    if(i == 1 || i == 4){
      yLen = lawOfCosinesSAS(yOt, LEGLEN, 90*yNt);
      yAd = 90+(degreesConverter(asin((sin(radianConverter((90*xNt)))*LEGLEN)/yLen))*xN*-1);
    }
    else{
      yLen = lawOfCosinesSAS(yOt, LEGLEN, (45*yNt*yNt2)+90);
      yAd = 90+(degreesConverter(asin((sin(radianConverter(((45*yNt)+90)))*LEGLEN)/yLen))*xNt*xN*-1);
    }
    double yA = degreesConverter(lawOfCosinesSSS(LEGLEN,yLen,yOt))*yNt*xN;

    //calculate x translation
    double xLen = lawOfCosinesSAS(xOt,yLen,yAd);
    double xA = yA-(degreesConverter(lawOfCosinesSSS(xLen,yLen,xOt))*xNt*xNt2);

    //calculate desired length of leg
    double dLen = calculateDesiredLength((zOffset-zOf[i])-(zOfr-zOfr2), xLen);

    //calculate and set angles for motors
    setAngleA(degreesConverter(lawOfCosinesSSS(TIBIA,SHIN,dLen)),i); //calculate and set angle A, shin-tibia joint
    setAngleB(
      360-(90+(degreesConverter(asin(xLen/dLen))
      +degreesConverter(lawOfCosinesSSS(dLen,TIBIA,SHIN)))),i); //calculate and set angle B, tibia-hip joint
    setAngleC(xA,i); //set angle C, hip-body joint
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

void Leg::setZOf(double a, double b, double c, double d, double e, double f){
  this->zOf[0] = a;
  this->zOf[1] = b;
  this->zOf[2] = c;
  this->zOf[3] = d;
  this->zOf[4] = e;
  this->zOf[5] = f;
}

void Leg::setYOf(double a, double b, double c, double d, double e, double f){
  this->yOf[0] = a;
  this->yOf[1] = b;
  this->yOf[2] = c;
  this->yOf[3] = d;
  this->yOf[4] = e;
  this->yOf[5] = f;
}

void Leg::setXOf(double a, double b, double c, double d, double e, double f){
  this->xOf[0] = a;
  this->xOf[1] = b;
  this->xOf[2] = c;
  this->xOf[3] = d;
  this->xOf[4] = e;
  this->xOf[5] = f;
}
