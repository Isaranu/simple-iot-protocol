#include "ESP8266WiFi.h"
#include "DHT.h"

#define DHTPIN 4 // GPIO4 pin
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float t,h;

void setup() {
  Serial.begin(115200);
  dht.begin();
}  

void loop() {
  
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
 
  delay(3000);
}
