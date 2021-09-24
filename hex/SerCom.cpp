#include "SerCom.h"
#include <Arduino.h>
#include <math.h>


void SerCom::checkSerial(){
  
  char serial[32];
  int index = 0;
  
  while(Serial.available() > 0){
    serial[index] = Serial.read();
    index++;
    if(index > 32){
      return;
    }
  }
  if(index >= 2){
    if(serial[0] == 'a' && serial[1] == 'r' && serial[2] == 'm'){
      armed = true;
      return;
    }
    else if(serial[0] == 'd' && serial[1] == 'i' && serial[2] == 's'){
      armed = false;
      return;
    }
  }
  
  if(index > 5){
    int neg = 1;
    int dir[3] = {0,0,0};
    int j = 0;
    
    if(serial[0] == 'c'){
      for(int i = 1; i < index-1; i++){
        if(serial[i] == '-'){
          neg = -1;
        }
        else if(serial[i] == ','){
          dir[j] = dir[j]*neg;
          j++;
          neg = 1;
        }
        else{
          dir[j] = dir[j]*10;
          dir[j] += (int)serial[i]-48;
        }
        if(j == 3){
          break;
        }
      }
      if(j != 3){
        return;
      }
            
      Serial.print("Y: ");
      Serial.print(dir[0]);
      Serial.print(" ");
      Serial.print("X: ");
      Serial.print(dir[1]);
      Serial.print(" ");
      Serial.print("Z: ");
      Serial.println(dir[2]);
    
      applySerialInput(dir[1], dir[0], dir[2]);
    }
  }
}

void SerCom::applySerialInput(double x, double y, double z){
   double saX = abs(x/20);
   double saY = abs(y/20);
   double saZ = abs(z/20);

   int num = max(max(saX,saY),saZ);

   if(num != 0){
    stepLength[0] = (x/num)/2;
    stepLength[1] = (y/num)/2;
    stepLength[2] = (z/num)/2;
    stepAmount = num;
    
    Serial.println(stepLength[1]);
    Serial.println(stepLength[0]);
    Serial.println(stepLength[2]);
    Serial.println(num);
   }   
}

int SerCom::serialMove(Walk* walk, int stp, int spd){
  if(walk->getSteps() > stepAmount-2){
    stepLength[0] = 0;
    stepLength[1] = 0;
    stepLength[2] = 0;
    stepAmount = 0;
    walk->setSteps(0);
  }
  
  return walk->moveInDirection(stp, spd, stepLength[1], stepLength[0], stepLength[2]);
}

bool SerCom::isArmed(){
  return armed;
}
