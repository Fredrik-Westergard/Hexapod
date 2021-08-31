#include "Ch.h"

Ch::Ch(){
  
}

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

void Ch::interpretData(){
  if(channel[0] == 0 && (milB[0]+1000 < (int)millis())){
    arm = !arm;
    Serial.println("armed");
    milB[0] = millis();
  }
}

void Ch::buildData(char* str){
  for(int i = 0; i < (int)sizeof(str); i++){
    this->str[i] = *(str+i);
  }
  compileData();
  interpretData();
}

bool Ch::isArmed(){
  return arm;
}
