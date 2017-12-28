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

class myprotocol{

  public:
    bool begin(const char *ssid, const char *passw);
    String sayhi();
    String WriteDashboard(float val);
    String WriteDHT(float t, float h);
    String getVersion();

  private:
    const char *_ssid, *_passw, *_libversion;
    String _str, _res, _val, _t, _h;
    bool _conn;
};

#endif
