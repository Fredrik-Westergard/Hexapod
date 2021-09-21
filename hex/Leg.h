#ifndef LEG_H__
#define LEG_H__

class Leg{
  private:
    const double SHIN = 120; //shin of robot leg constant
    const double TIBIA = 65; //tibia of robot leg constant
    const double HIP = 50; //hip of robot leg constant
    const double BODYX1 = 58; //body x length divided by two, for front and back legs
    const double BODYX2 = 90; //body x lenght divided by two, for middle legs
    const double BODYY = 107; //body y length divided by two
    const double BODYXY = 121.709; //body xy length, hypotenuse between BODYX1 and BODYY 
    const double BODYA = 61.541; //body angle from tan(BODYY/BODYX1)
    const double LEGLEN = 110; //leg length constant, the length the tip of the legs are from the hip joint, in mm

    const double ANG[6] = {45.0, 90.0, 135.0, 225.0, 270.0, 315.0}; //constant angles array for z rotation
    const double ZAY[6] = {131.408,0,-131.408,-131.408,0,131.408}; //constant y axis offset array for z rotation
    const double ZAX[6] = {131.408,200,131.408,-131.408,-200,-131.408}; //constant x axis offset array for z rotation
    
    double angleA[6]; //angle of shin motor
    double angleB[6]; //angle of tibia motor
    double angleC[6]; //angle of hip motor

    double zOf[6] = {0,0,0,0,0,0}; //individual z offset
    double xOf[6] = {0,0,0,0,0,0}; //individual x offset
    double yOf[6] = {0,0,0,0,0,0}; //individual y offset
    
    double lawOfCosinesSSS(double a, double b, double c); //calculate law of cosines when you have all sides 
    double lawOfCosinesSAS(double a, double b, double angle); //calculate law of cosines when you have two sides and one angle between them
    double radianConverter(double degree); //convert from degrees to radians
    double degreesConverter(double radian); //convert from radians to degrees
    double calculateDesiredLength(double zOffset, double dLen); //desired length calculator
    double calculateHeronsFormula(double a, double b); //calculate herons formula, get height of triangle. used on isoscelece triangle so only tow sides are needed
public: 
    void calculateAngles(double zOffset, double yOffset, double xOffset, double zAngle, double yAngle, double xAngle); //calculates all angles and sets them
    void setAngleA(double angleA, int pos); //set A angle, shin-tibia
    void setAngleB(double angleB, int pos); //set B angle, tibia-hip
    void setAngleC(double angleC, int pos); //set C angle, hip-body
    double getAngleA(int pos); //get A angle, shin-tibia
    double getAngleB(int pos); //get B angle, tibia-hip
    double getAngleC(int pos); //get C angle, hip-body
    void setZOf(double a, double b, double c, double d, double e, double f);
    void setYOf(double a, double b, double c, double d, double e, double f);
    void setXOf(double a, double b, double c, double d, double e, double f);
};

#endif
