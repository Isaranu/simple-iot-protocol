#ifndef mylibrary_h
#define mylibrary_h

#include "Arduino.h"

class mylibrary{

  public:
    String setLEDblink(int pin, float timeon, float timeoff); // Time ON-OF in second.
    String chkmyLib();

  private:
    int _pin;
    float _timeon, _timeoff;
    String _response;
};

#endif
