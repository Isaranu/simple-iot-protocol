#include "mylibrary.h"

#define hi "call my library OK"

String mylibrary::setLEDblink(int pin, float timeon, float timeoff){

  _pin = pin;
  _timeon = timeon;
  _timeoff = timeoff;

  pinMode(_pin, OUTPUT);

  digitalWrite(_pin, LOW); // LED จะติด, เพราะ Espino ต่อ LED แบบ Pull-up V3.3
  delay(_timeon*1000);
  digitalWrite(_pin, HIGH); // LED จะดับ
  delay(_timeoff*1000);

  _response = "blink from my library OK";

  return _response;
}

String mylibrary::chkmyLib(){
  return hi;
}
