/*
สร้าง library สำหรับ iot protocol
code.isaranu.com
coder : Isaranu Janthong
created : 2017.Nov.11
*/

#ifndef myprotocol_h
#define myprotocol_h

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ArduinoJson.h"

class myprotocol{

  public:
    bool begin(const char *ssid, const char *passw);
    String sayhi();
    String WriteDashboard(float val);
    String getVersion();

  private:
    const char *_ssid, *_passw, *_libversion;
    float _val;
    String _res;
    bool _conn;
};

#endif
