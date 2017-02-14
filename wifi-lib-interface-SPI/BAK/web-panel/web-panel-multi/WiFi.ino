
void initWiFi(int wifiMode, const char* hostname, const char* ssid, const char* password){
  if (!loadConfig())
    Serial.println("======== Failed to load configuration loaded ========");
  else 
    Serial.println("======== Configuration loaded ========");

    currentConf.net_mode = intToWifiMode(wifiMode);
    currentConf.hostname = (char*)hostname;
    currentConf.password = (char*)password;
    
 if(wifiMode==WIFI_AP_STA){
       currentConf.ssid = (char*)ssid;
   
   if (!saveConfig())
      Serial.println("Failed to save config");
    else
      Serial.println("Config saved");
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.hostname(hostname);
  WiFi.begin(ssid, password);
 } 
 else {
  if(strlen(ssid) == 0){
   byte mac[6];
   WiFi.macAddress(mac);
   String tmpString = String("Arduino-Primo-" +  String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX) );
   tmpString.toCharArray(softApssid, tmpString.length()+1);
   delay(1000);
   
    if (!saveConfig())
      Serial.println("Failed to save config");
    else
      Serial.println("Config saved");
   currentConf.ssid = (char*)softApssid;  
   WiFi.softAP(softApssid, password);
  }
  else {
   currentConf.ssid = (char*)ssid;
   if (!saveConfig())
      Serial.println("Failed to save config");
    else
      Serial.println("Config saved");
   WiFi.softAP(ssid,password);
  }
 }
 while ( WiFi.waitForConnectResult() != WL_CONNECTED ) {
  delay ( 5000 );
  Serial.print ( "." );
  ESP.restart();
 }
}
  

void initWiFi(){
      delay(8000); 
    if (!loadConfig())
      Serial.println("======== Failed to load configuration loaded ========");
    else 
      Serial.println("======== Configuration loaded ========");

    if (!loadConfig()) {
        Serial.println("Failed to load config");
      } else {
        Serial.println("Config loaded");
//        Serial.println(String(currentConf.net_mode) + " | " + String(currentConf.hostname) + " | " + String(currentConf.ssid) + " | " + String(currentConf.password));

        if(currentConf.net_mode==WIFI_AP_STA){
            WiFi.mode(currentConf.net_mode);
            WiFi.hostname(currentConf.hostname);
            WiFi.begin(currentConf.ssid, currentConf.password);
          }
         else{
          WiFi.hostname(currentConf.hostname);
          WiFi.softAP(currentConf.hostname, currentConf.password); //TODO Che nome usare : ssid o hostname ? 
         }

      }
}




