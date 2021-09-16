#include "Ch.h"


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
  
  zOffset = map(channel[12],0,1024,120,40);
  yOffset = map(channel[15],0,1024,30,-30);
  xOffset = map(channel[14],0,1024,30,-30);
  zAngle = map(channel[13],0,1024,30,-30);
  yAngle = map(channel[11],0,1024,25,-25);
  xAngle = map(channel[10],0,1024,-25,25);
}

//builder of data, compiles and interprets
void Ch::buildData(char* str){
  this->str = str;
  compileData();
  interpretData();
}

//true if armed
bool Ch::isButtonToggeled(int num){
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
