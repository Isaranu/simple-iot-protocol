/*
Code for Internet of things device
Simple connect WiFi.
Coder : Isaranu Janthong
Created : 2017.Nov.20
*/

#include "ESP8266WiFi.h"

const char *ssid = "your wifi name";
const char *passw = "your wifi passw";

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, passw);

  Serial.print("WiFi connecting..");

  while((WiFi.status() != WL_CONNECTED)){
    delay(200);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected !");
  }else{
    // Nothing..
  }
}

void loop() {
  // Do something..
}
