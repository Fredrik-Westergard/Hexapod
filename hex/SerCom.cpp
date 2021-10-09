#include "SerCom.h"
#include <Arduino.h>
#include <math.h>

/*
 * class for serial communication
 */

//constructor
SerCom::SerCom(){
  randomSeed(analogRead(6));
}

//function to check if there is serial to read and interprets it
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
    Serial5.println("armed");
    armed = true;
    return;
  }
  else if(serial.substring(0,3) == "dis"){
    Serial5.println("disarmed");
    armed = false;
    return;
  }
  else if(serial.substring(0,3) == "mem"){
    switchMemory();
    return;
  }
  else if(serial.substring(0,3) == "aut"){
    Serial5.println("autonomous movement");
    autonomous = !autonomous;
    autoToggle = true;
    return;
  }
  else if(serial.substring(0,3) == "cha"){
    Serial5.println("channel");
    channel = !channel;
    return;
  }
  else if(serial.substring(0,3) == "ult"){
    Serial5.println("ultra");
    ultra = !ultra;
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
            
      Serial5.print("Y: ");
      Serial5.print(dir[0]);
      Serial5.print(" ");
      Serial5.print("X: ");
      Serial5.print(dir[1]);
      Serial5.print(" ");
      Serial5.print("Z: ");
      Serial5.println(dir[2]);
    
      applySerialInput(dir[1], dir[0], dir[2]);
    }
  }
}

//function to apply the serial input
void SerCom::applySerialInput(double x, double y, double z){
   double saX = abs(round((x/20)))*2;
   double saY = abs(round(y/30))*2;
   double saZ = abs(round(z/10));
  
   int num = max(max(saX,saY),saZ);
   
   if(num != 0){
    double len1 = (x/num)-4;
    double len2 = (y/num)*1.3;
    double len3 = ((z/num)*1.285)+0.9;
    
    Serial5.print("Y: ");
    Serial5.print(len1);
    Serial5.print(" X: ");
    Serial5.print(len2);
    Serial5.print(" Z: ");
    Serial5.print(len3);
    Serial5.print(" S: ");
    Serial5.println(num/2);

    if(memory){
      list->addToList(len1, len2, len3, num/2);
    }
    else{
      stepLength[0] = len1;
      stepLength[1] = len2;
      stepLength[2] = len3;
      stepAmount = num/2;
    }
   }   
}

//function to switch memory on/off
void SerCom::switchMemory(){
  Serial5.println("memory");
  memory = !memory;

  if(memory){
    list = new List();
  }
  else{
    delete list;
  }
}

//function to use serial to move
int SerCom::serialMove(Walk* walk, int stp, int spd){
  if(autoToggle){
    stepLength[0] = 0;
    stepLength[1] = 0;
    stepLength[2] = 0;
    stepAmount = 0;
    walk->setSteps(0);
    autoToggle = false;
  }
  if(walk->getSteps() > stepAmount-2){
    if(memory){
      if(list->getLength() > -1){
        Node* n = list->getElement(0);
        Serial5.println(n->getAmount());
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
  int dist = getDistance(walk);
  if(dist < 25){
     stepLength[1] = 0;
     if(stepLength[0] <= 5 && stepLength[2] <= 5){
        stepLength[0] = 0;
        stepLength[2] = 0;
        stepAmount = 0;
        walk->setSteps(0);
     }
  }
  
  return walk->moveInDirection(stp, spd, stepLength[1], stepLength[0], stepLength[2]);
}

//function to move autonomously
int SerCom::autonomousMovement(Walk* walk, int stp, int spd){
  if((getDistance(walk) < 25 && stepLength[1] > 0)||((walk->getSteps() > stepAmount-2)&&(stepLength[1] > 5))){
    stepLength[0] = 0;
    stepLength[1] = 0;
    stepLength[2] = 0;
    stepAmount = 0;
    walk->setSteps(0);
    applySerialInput(0,0,((random(-1,1) > 0)?random(-45,-181):random(45,181)));
  }
  if((walk->getSteps() > stepAmount-2)&&(stepLength[1] < 5)){
    stepLength[0] = 0;
    stepLength[1] = 0;
    stepLength[2] = 0;
    stepAmount = 0;
    walk->setSteps(0);
    applySerialInput(0,1000,0);
  }
  return walk->moveInDirection(stp, spd, stepLength[1], stepLength[0], stepLength[2]);
}

//function to get a filtered distance
int SerCom::getDistance(Walk* walk){
  if(ultra){
    int tot = 0;
    for(int i = 0; i < 9; i++){
      distance[i] = distance[i+1];
      tot+= distance[i];
    }
    distance[9] = walk->getDistance();
    tot+=distance[9];
    return tot/10;
  }
  else{
    return 30;
  }  
}
 
//getter for armed flag
bool SerCom::isArmed(){
  return armed;
}

//getter for autonomous flag
bool SerCom::isAutonomous(){
  return autonomous;
}

bool SerCom::isCh(){
  return channel;
}
