#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include "Ch.h"
#include "Leg.h"
#include "Move.h"
#include "Walk.h"
#include "Led.h"
#include "SerCom.h"

/*
 * This is the main arduino file for the hexapod robot
 */

RF24 radio(9,8); //CE, CSN
const byte address[6] = "00001"; //Radio address
char str[32]; //sring received from radio

int rPin = 4; //red pin for rgb light
int gPin = 3; //green pin for rgb light
int bPin = 2; //blue pin for rgb light

Ch ch; //channel object
Leg leg; //leg object
Move mv; //move object
Walk walk; //walk object
Led led; //led object
SerCom ser; //serial communication object

int stpOS = 0; //step on spot sequence variable
int stp = 0; //step sequence variable
int spd = 300; //speed for stepping/walking, increse to make timing of movement higher

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

  //setting up the rgb pins
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
  //if there is signal loss
  if(ch.getMilRec()+350 < (int) millis() && ch.getMilRec()+1000 > (int) millis()){
    //reset data
    ch.resetData();
  }
  //check if there is anything on serial
  ser.checkSerial();
  
  //sets serial flag
  led.setSer(ser.isArmed());
  //toggles which color should be on
  led.toggleColors(&ch);
  //sets colors, turns led on with right color
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
      //walk on spot, mostly for testing sequence timings
      stpOS = walk.onSpot(stpOS,spd);
    }
    else if(!ch.isButtonToggled(3) && !ch.isButtonToggled(2) && ch.isButtonToggled(4)){
      //walk
      stp = walk.moveInDirection(stp, spd, ch.getYMove(), ch.getXMove(), ch.getZMove());
    }
  }
  else if(ser.isArmed()){
    if(!ser.isAutonomous()){
      //walk through serial command
      stp = ser.serialMove(&walk, stp, spd);
    }
    else{
      //autonomous movement
      stp = ser.autonomousMovement(&walk, stp, spd);
    }
  }
}
