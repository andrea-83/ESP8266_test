#include <ESP8266WiFi.h>


// struct boardConf               //need to 
// {
//     WiFiMode net_mode;
//     char* hostname;
//     char* ssid;
//     char* password;
//     char* ip;
//     char* dhcp;
//     char* staticip;
//     char* gateway;
//     char* netmask;
//     bool flag;
// };

const char* ssid = "YOUR_SSID_HERE";
const char* password = "YOUR_PASSWORD_HERE";
const char* http_username = "";
const char* http_password = "";
const char* host_name = "ArduINO";

boardConf currentConf;

void setup() {
  initSerial();
  initWebFS();
  initArduinoOTA();
  initWiFi(WIFI_STA, host_name, ssid, password);
}

void loop() {
  manageOTA();
}
