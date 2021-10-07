#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

/*
 * This is a program to run the esp8266 webSerial server with two way communication
 * It is frankensteined together from multiple tutorials that I've now lost track of.
 */

#ifndef APSSID  
#define APSSID "ROBOTAP" //ssid
#define APPSK  "Abcd1234" //super safe password
#endif

AsyncWebServer server(80); //server object

const char* ssid = APSSID; //setting ssid
const char* password = APPSK; //setting password

IPAddress local_IP(192, 168, 1, 111); //setting static ip adress

//receive message function for webserial
void recvMsg(uint8_t *data, size_t len){
  String msg = "";
  for(int i=0; i < len; i++){
    msg += char(data[i]);
  }
  WebSerial.println(msg);
  Serial.println(msg);
}

//arduino setup
void setup() {
  Serial.begin(115200); //set serial to 115200 baud rate
  Serial.setTimeout(100); //set timeout to 100 ms
  
  WiFi.mode(WIFI_AP_STA); //set the wifi mode
  if (!WiFi.softAPConfig(local_IP, local_IP, IPAddress(255, 255, 255, 0))) { //sets static ip
    Serial.println("STA Failed to configure");
  }
  
  WiFi.softAP(ssid, password); //making the esp8266 an access point
  IPAddress myIP = WiFi.softAPIP(); //getting the ip, don't know if it's needed now, used for testing. 

  WebSerial.begin(&server); //begin webserial
  WebSerial.msgCallback(recvMsg); //sets function to call when message received
  server.begin(); //begins server
}

//arduino loop
void loop() {
  //if there is serial to read...
  if(Serial.available() > 0){
    String serial = Serial.readStringUntil('\n'); //read it until newline
    WebSerial.println(serial); //print the received string to webserial
  }
}
