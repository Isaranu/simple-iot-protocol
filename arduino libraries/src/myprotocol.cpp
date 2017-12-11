/*
สร้าง library สำหรับ iot protocol
code.isaranu.com
coder : Isaranu Janthong
created : 2017.Nov.11
*/

#include "myprotocol.h"

#define host "your-server-ip-address"
#define port 4000
#define libversion "v1.0"

#define CONN_RETRY_LIMIT 30
#define LAG_TIME 100

bool myprotocol::begin(const char *ssid, const char *passw){
  _ssid = ssid;
  _passw = passw;

  int _cnt = 0;

  WiFi.begin(_ssid, _passw);
  Serial.print("myprotocol connecting..");

  while((WiFi.status() != WL_CONNECTED) && (_cnt <= CONN_RETRY_LIMIT)){
    delay(200);
    Serial.print(".");
    _cnt++;
  }

  if(WiFi.status() == WL_CONNECTED){
    _conn = true;
    Serial.println("Connected !");
  }else{
    _conn = false;
    Serial.println("Connection Timeout.");
  }

  return _conn;
}

String myprotocol::sayhi(){

  WiFiClient client;
  if(client.connect(host, port)){
    _str = "GET /";
    _str += " HTTP/1.1\r\n";
    _str += "Host: ";
    _str += host;
    _str += ":";
    _str += port;
    _str += "\r\n";
    _str += "Connection: keep-alive\r\n\r\n";

    client.print(_str);

    delay(LAG_TIME);

    while(client.available()){
      _res = client.readStringUntil('\r');
    }

    return _res;

  }else{
    //..
  }
}

String myprotocol::WriteDashboard(float val){

    _val = String(val);

    WiFiClient client;
    if(client.connect(host, port)){

      _str = "GET /write/";
      _str += _val;
      _str += " HTTP/1.1\r\n";
      _str += "Host: ";
      _str += host;
      _str += ":";
      _str += port;
      _str += "\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      client.print(_str);

      delay(LAG_TIME);

      while(client.available()){
        _res = client.readStringUntil('\r');
      }

      return _res;
    }else{
      //Nothing..
    }
}

String myprotocol::WriteDHT(float t, float h){

    _t = String(t);
    _h = String(h);

    WiFiClient client;
    if(client.connect(host, port)){

      _str = "GET /writedht/";
      _str += _t;
      _str += "/";
      _str += _h;
      _str += " HTTP/1.1\r\n";
      _str += "Host: ";
      _str += host;
      _str += ":";
      _str += port;
      _str += "\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      client.print(_str);

      delay(LAG_TIME);

      while(client.available()){
        _res = client.readStringUntil('\r');
      }

      return _res;
    }else{
      //Nothing..
    }
}

String myprotocol::getVersion(){
  return libversion;
}
