#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include "Ch.h"
#include "Leg.h"
#include "Move.h"
#include "Walk.h"
#include "Led.h"
#include "SerCom.h"

RF24 radio(9,8); //CE, CSN
const byte address[6] = "00001"; //Radio address
char str[32]; //sring received from radio

int rPin = 4;
int gPin = 3;
int bPin = 2;

Ch ch; //channel object
Leg leg; //leg object
Move mv; //move object
Walk walk;
Led led;
SerCom ser;

int stpOS = 0;
int stp = 0;
int spd = 300;

//standard setup function for arduino, runs only once
void setup() {
  //set up wire and wire clock for i2C motor drivers
  Wire.begin();
  Wire.setClock(400000);
  
  //initialize motor drivers
  mv.initDrivers();
  
  //setup for radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  //start serial
  Serial.begin(115200);
  Serial5.begin(115200);
  Serial.setTimeout(20);
  Serial5.setTimeout(20);
}

//standard main loop
void loop() {
  //if there is new data from the radio
  if(radio.available()){
    //read it
    radio.read(&str, sizeof(str));
    //print it
    Serial.println(str);
    //and compile it
    ch.buildData(str);
  }

  ser.checkSerial();

  led.setSer(ser.isArmed());

  led.toggleColors(&ch);
  led.setColors(rPin, gPin, bPin);
  
  //if robot is armed (button 0 is toggeled)
  if(ch.isButtonToggled(0)){
    if(ch.isButtonToggled(3) && !ch.isButtonToggled(2) && !ch.isButtonToggled(4)){
      //calculates the angles
      leg.calculateAngles(ch.getZOffset(), ch.getYOffset(), ch.getXOffset(), ch.getZAngle(), ch.getYAngle(), ch.getXAngle());
      //move robot
      mv.moveLegs(&leg);
    }
    else if(!ch.isButtonToggled(3) && ch.isButtonToggled(2) && !ch.isButtonToggled(4)){
      stpOS = walk.onSpot(stpOS,spd);
    }
    else if(!ch.isButtonToggled(3) && !ch.isButtonToggled(2) && ch.isButtonToggled(4)){
      stp = walk.moveInDirection(stp, spd, ch.getYMove(), ch.getXMove(), ch.getZMove());
    }
  }
  else if(ser.isArmed()){
    if(!ser.isAutonomous()){
      stp = ser.serialMove(&walk, stp, spd);
    }
    else{
      stp = ser.autonomousMovement(&walk, stp, spd);
    }
  }
}
