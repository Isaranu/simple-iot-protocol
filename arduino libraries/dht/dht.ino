/*
Code for Internet of things device
connect to server.
Coder : Isaranu Janthong
Created : 2017.Dec.11
*/

#include <myprotocol.h>
#include "DHT.h"

const char *ssid = "your-ssid";
const char *passw = "your-wifi-passw";

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float t,h;

String response; 
float value;

myprotocol myiot;

void setup() {

  Serial.begin(115200);
  dht.begin();
  
  bool conn = myiot.begin(ssid, passw);

  if(conn){
      Serial.println("myprotocol connected.");
    }else{
      Serial.println("re-connect again.");
     }

  response = myiot.sayhi();
  Serial.println("Are you ready ? :" + String(response)); 
  
  response = myiot.getVersion();
  Serial.println("myprotocol library version is " + String(response));  
}

void loop() {
  
  response = "";

  /* - DHT sensor reading - */
  t = dht.readTemperature();
  h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Temperature is " + String(t) + " celcuis");
  Serial.println("Humidity is " + String(h) + " %RH");
  Serial.println("----------------------------------------");

  response = myiot.WriteDHT(t,h);
  Serial.println(response);
  
  delay(5000);
}
