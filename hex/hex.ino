#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include "Ch.h"
#include "Leg.h"
#include "Move.h"

RF24 radio(9,8); //CE, CSN
const byte address[6] = "00001"; //Radio address
char str[32]; //sring received from radio

Ch ch; //channel object
Leg leg; //leg object
Move mv; //move object

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

  //start serial
  Serial.begin(115200);
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
  //if robot is armed (button 0 is toggeled)
  if(ch.isButtonToggeled(0)){
    //calculates the angles
    leg.calculateAngles(ch);
    //move robot
    mv.moveLegs(&leg);
  }
}
