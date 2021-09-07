#ifndef LEG_H__
#define LEG_H__

class Leg{
  private:
    const double SHIN = 120; //shin of robot leg constant
    const double TIBIA = 65; //tibia of robot leg constant
    const double HIP = 50; //hip of robot leg constant
    
    const double LEGLEN = 110; //leg length constant, the length the tip of the legs are from the hip joint, in mm
    
    double angleA[6]; //angle of shin motor
    double angleB[6]; //angle of tibia motor
    double angleC[6]; //angle of hip motor

    double zOf[6] = {0,0,0,0,0,0};
    double xOf[6] = {0,0,0,0,0,0};
    double yOf[6] = {0,0,0,0,0,0};
    
    double lawOfCosinesSSS(double a, double b, double c);
    double lawOfCosinesSAS(double a, double b, double angle);
    double degreesConverter(double radian);
    double calculateDesiredLength(double zOffset, double dLen);
public:
    void calculateAngles(double zOffset, double yOffset, double xOffset);
    void setAngleA(double angleA, int pos);
    void setAngleB(double angleB, int pos);
    void setAngleC(double angleC, int pos);
    double getAngleA(int pos);
    double getAngleB(int pos);
    double getAngleC(int pos);
};

#endif
