#include "Ch.h"

//constructor, not sure if necessary
Ch::Ch(){
  
}

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
  if(channel[0] == 0 && (milB[0]+1000 < (int)millis())){
    arm = !arm;
    Serial.println("armed");
    milB[0] = millis();
  }
}

//builder of data, compiles and interprets
void Ch::buildData(char* str){
  for(int i = 0; i < (int)sizeof(str); i++){
    this->str[i] = *(str+i);
  }
  compileData();
  interpretData();
}

//true if armed
bool Ch::isArmed(){
  return arm;
}
