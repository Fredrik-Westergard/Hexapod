#include "Ch.h"


/*
 * channel class to get controller data
 */

/* function to compile data from controller
 * As Radio transciever can only send 32 byte of data at a time
 * the transmission is split into A and B transmissions and compiled to
 * 16 channels.
 */
void Ch::compileData(){
  int i;
  int j = 0;
  if(str[0] == 'A'){
    for(i = 0; i < 10; i++){
      channel[i]  = (str[i+1]-48);
    }
  }
  else if(str[0] == 'B'){
    for(i = 0; i < 6; i++){
      channel[i+10] = 0;
      for(;(str[i+1+j]) != ','; j++){
          channel[i+10] = channel[i+10]*10;
          channel[i+10] += (str[i+1+j])-48;
      }
    }
  }
}

//function to interpret the data from the channels
void Ch::interpretData(){
  for(int i=0; i<10; i++){
    if(channel[i] == 0 && (milB[i]+1000 < (int)millis())){
      buttons[i] = !buttons[i];
      milB[i] = millis();
    }
  }
  
  zOffset = map(channel[12],0,1024,140,40);
  yOffset = map(channel[15],0,1024,40,-40);
  xOffset = map(channel[14],0,1024,40,-40);
  zAngle = map(channel[13],0,1024,25,-25);
  yAngle = map(channel[11],0,1024,20,-20);
  xAngle = map(channel[10],0,1024,-20,20);

  yMove = map(channel[12],0,1024,20,-20);
  xMove = map(channel[13],0,1024,20,-20);
  zMove = map(channel[10],0,1024,-15,15);
  milRec = millis();

  Serial.print(yMove);
  Serial.print(" ");
  Serial.print(xMove);
  Serial.print(" ");
  Serial.println(zMove);
}

void Ch::resetData(){
  for(int i = 0; i < 10; i++){
    channel[i] = 0;
  }
  for(int i = 10; i < 16; i++){
    channel[i] = 512;
  }
  interpretData(); 
}

//builder of data, compiles and interprets
void Ch::buildData(char* str){
  this->str = str;
  compileData();
  interpretData();
}

//true if armed
bool Ch::isButtonToggled(int num){
  return buttons[num];
}
//getter of height
double Ch::getZOffset(){
  return zOffset;
}

//getter of y offset, front and back
double Ch::getYOffset(){
  return yOffset;
}

//getter of x offset, side to side
double Ch::getXOffset(){
  return xOffset;
}
//getter of z Angle, yaw
double Ch::getZAngle(){
  return zAngle;
}

//getter of y angle, pitch
double Ch::getYAngle(){
  return yAngle;
}

//getter of x angle, roll
double Ch::getXAngle(){
  return xAngle;
}

//getter of yMove, for walking
double Ch::getYMove(){
  return yMove;
}

//getter of xMove, for walking
double Ch::getXMove(){
  return xMove;
}

//getter of zMove, for walking
double Ch::getZMove(){
  return zMove;
}

//getter of Milliseconds since robot last received something from the controller
int Ch::getMilRec(){
  return milRec;
}
