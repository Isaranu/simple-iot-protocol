/*
สร้าง library สำหรับ iot protocol
code.isaranu.com
coder : Isaranu Janthong
created : 2017.Nov.11
*/

#include "myprotocol.h"

#define host "35.198.221.246"
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

    _val = "val=" + val;

    WiFiClient client;
    if(client.connect(host, port)){
      _str = "POST /write/";
      _str += " HTTP/1.1\r\n";
      _str += "Host: ";
      _str += host;
      _str += ":";
      _str += port;
      _str += "\r\n";
      _str += "Cache-Control: no-cache\r\n";
      _str += "Content-Type: application/x-www-form-urlencoded";
      _str += "Content-Length: ";
      _str += _val.length();
      _str += "\r\n";
      _str += _val;

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
  return pn_libversion;
}

/*

https://github.com/esp8266/Arduino/issues/1390

client.println("POST /posts HTTP/1.1");
client.println("Host: jsonplaceholder.typicode.com");
client.println("Cache-Control: no-cache");
client.println("Content-Type: application/x-www-form-urlencoded");
client.print("Content-Length: ");
client.println(PostData.length());
client.println();
client.println(PostData);
*/
