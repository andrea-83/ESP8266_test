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
#define HOSTNAME "Arduino-PrimoSPI"

ESP8266WebServer UIserver(80);    //server UI
unsigned long previousMillis = 0;        // will store last time LED was updated

void setup() {

  ArduinoOTA.begin();
  CommunicationLogic.begin();
  //WiFi.hostname(HOSTNAME);      //set hostname
  //MDNS.begin(HOSTNAME);         //set mdns
  //initWBServer();               //UI begin

}

void loop() {

  //ETS_SPI_INTR_DISABLE();
  //if (_state == OTA_RUNUPDATE)
  //ETS_SPI_INTR_DISABLE();
  ArduinoOTA.handle();
  //if (_state != OTA_RUNUPDATE)
  //ETS_SPI_INTR_ENABLE();
  //ETS_SPI_INTR_ENABLE();
  //manageOTA();
  CommunicationLogic.handle();
  if(CommunicationLogic.UI_alert){			//stop UI SERVER){}
    UIserver.stop();
  }
  else
    handleWBServer();
  //server.handleClient();
  // unsigned long currentMillis = millis();
  // if(currentMillis - previousMillis > 60000) {
  // //   // save the last time you blinked the LED
  //    previousMillis = currentMillis;
  //    ESP.restart();
  // //   Serial.println(ESP.getFreeHeap());
  // //
  //  }


}
