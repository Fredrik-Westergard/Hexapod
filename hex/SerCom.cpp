#include "SerCom.h"
#include <Arduino.h>
#include <math.h>


void SerCom::checkSerial(){
  String serial;
  if(Serial.available() > 0){
    serial = Serial.readStringUntil('\n');
    Serial.println(serial);
  }
  else if(Serial5.available() > 0){
   serial = Serial5.readStringUntil('\n');
  }
  else{
    return;
  }
  if(serial.substring(0,3) == "arm"){
    Serial.println("armed");
    armed = true;
    return;
  }
  else if(serial.substring(0,3) == "dis"){
    Serial.println("disarmed");
    armed = false;
    return;
  }
  else if(serial.substring(0,3) == "mem"){
    switchMemory();
    return;
  }
  
  if(armed && serial.length() > 5){
    int neg = 1;
    int dir[3] = {0,0,0};
    int j = 0;
    
    if(serial.charAt(0) == 'c'){
      for(int i = 1; i < (int) serial.length()-1; i++){
        if(serial.charAt(i) == '-'){
          neg = -1;
        }
        else if(serial.charAt(i) == ',' || serial.charAt(i) == '\n'){
          dir[j] = dir[j]*neg;
          j++;
          neg = 1;
        }
        else{
          dir[j] = dir[j]*10;
          dir[j] += (int)serial.charAt(i)-48;
        }
        if(j == 3){
          break;
        }
      }
      if(j == 2){
        dir[2] = dir[2]*neg;
      }
      if(j != 2){
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
   double saX = abs(round(x/20))*2;
   double saY = abs(round(y/15))*2;
   double saZ = abs(round(z/10));
  
   int num = max(max(saX,saY),saZ);
   
   if(num != 0){
    double len1 = x/num;
    double len2 = y/num;
    double len3 = ((z/num)*1.275)+1; //(z+(1.4*(num*2)))/(num*2);
    
    Serial.print("Y: ");
    Serial.print(len1);
    Serial.print(" X: ");
    Serial.print(len2*2);
    Serial.print(" Z: ");
    Serial.print(len3);
    Serial.print(" S: ");
    Serial.println(num);

    if(memory){
      list->addToList(len1, len2, len3, num/2);
    }
    else{
      stepLength[0] = len1;
      stepLength[1] = len2*2;
      stepLength[2] = len3;
      stepAmount = num/2;
    }
   }   
}

void SerCom::switchMemory(){
  Serial.println("memory");
  memory = !memory;

  if(memory){
    list = new List();
  }
  else{
    delete list;
  }
}

int SerCom::serialMove(Walk* walk, int stp, int spd){
  if(walk->getSteps() > stepAmount-2){
    if(memory){
      if(list->getLength() > -1){
        Node* n = list->getElement(0);
        Serial.println(n->getAmount());
        stepLength[0] = n->getLength(0);
        stepLength[1] = n->getLength(1);
        stepLength[2] = n->getLength(2);
        stepAmount = n->getAmount();
        list->removeFromList();
        walk->setSteps(0);
      }
      else{
        stepLength[0] = 0;
        stepLength[1] = 0;
        stepLength[2] = 0;
        stepAmount = 0;
        walk->setSteps(0);
      }
    }
    else{
      stepLength[0] = 0;
      stepLength[1] = 0;
      stepLength[2] = 0;
      stepAmount = 0;
      walk->setSteps(0);
    }
  }
  return walk->moveInDirection(stp, spd, stepLength[1], stepLength[0], stepLength[2]);
}



bool SerCom::isArmed(){
  return armed;
}
