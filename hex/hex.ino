#include <nRF24L01.h> //nrf24l01 is the radio transceiver module
#include <RF24.h>
#include "Ch.h"

RF24 radio(9,8); //CE, CSN
const byte address[6] = "00001"; //Radio address
Ch ch;

char str[32]; //sring received from radio

//standard setup function for arduino, runs only once
void setup() {
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
    Serial.println(str);
    ch.buildData(str);
  }
  if(ch.isArmed()){
    //move robot
  }
  
}
