#include "CommLgc.h"
//#include "utility/wifi_utils.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <FS.h>
#include <Hash.h>
#include <ESP8266WebServer.h>

#define WIFI_LED 2
#define HOSTNAME "Arduino-Primo"

ESP8266WebServer server(80);    //server UI
bool SERVER_STOP = false;       //check stop server
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long interval = 250;        // will store last time LED was updated

void setup() {

  ArduinoOTA.begin();
  CommunicationLogic.begin();
  initWBServer();               //UI begin
  initMDNS();                   //set MDNS

}

void loop() {

  ArduinoOTA.handle();
  CommunicationLogic.handle();
  if(CommunicationLogic.UI_alert){			//stop UI SERVER){}
    if(!SERVER_STOP){
      server.stop();
      SERVER_STOP = true;
    }
  }
  else
    handleWBServer();
  // unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   // save the last time you blinked the LED
  //   previousMillis = currentMillis;
  //   if (ledState == LOW) {
  //     ledState = HIGH;
  //   } else {
  //     ledState = LOW;
  //   }
  //   digitalWrite(WIFI_LED, ledState);
  // }

}
