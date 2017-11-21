#include "mylibrary.h"

mylibrary me;
String response;

void setup() {

  Serial.begin(115200);

  response = me.chkmyLib();
  Serial.println(response);

}

void loop() {
  response = me.setLEDblink(16,2,2); /* LED OFF 2 sec., LED ON 2 sec.*/
  Serial.println(response);
}
