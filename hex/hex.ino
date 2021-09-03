#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include "Ch.h"
#include "Move.h"

RF24 radio(9,8); //CE, CSN
const byte address[6] = "00001"; //Radio address
char str[32]; //sring received from radio

Ch ch; //channel object
Leg leg(&ch); //leg object
Move mv(&leg); //move object

//standard setup function for arduino, runs only once
void setup() {
  Wire.begin();
  Wire.setClock(400000);

  mv.initDrivers();
  //setup for radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  //start serial
  Serial.begin(115200);
}

//standard main loop
void loop() {
  if(radio.available()){
    radio.read(&str, sizeof(str));
    //Serial.println(str);
    ch.buildData(str);
  }
  if(ch.isArmed()){
    //calculates the angles
    leg.calculateAngles();
    //move robot
    mv.moveLegs();
  }
}
