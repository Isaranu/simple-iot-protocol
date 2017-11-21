#include "mylibrary.h"

mylibrary me;
String response;

void setup() {

  Serial.begin(115200);

  response = me.chkmyLib();

  response = me.setLEDblink(1,2,2);
  Serial.println(response);
}

void loop() {

}
