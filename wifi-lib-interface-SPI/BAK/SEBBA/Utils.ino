#include <ArduinoJson.h>
#include <FS.h>
extern "C" void system_set_os_print(uint8 onoff);
extern "C" void ets_install_putc1(void* routine);

String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

String toStringWifiMode(int mod) {
  String mode;
  switch (mod) {
    case 0:
      mode = "OFF";
      break;
    case 1:
      mode = "STA";
      break;
    case 2:
      mode = "AP";
      break;
    case 3:
      mode = "AP+STA";
      // statements
      break;
    case 4:
      mode = "----";
      break;
    default:
      // statements
      break;
  }
  return mode;
}

WiFiMode intToWifiMode(int mod) {
  WiFiMode mode;
  switch (mod) {
    case 0:
      mode = WIFI_OFF;
      break;
    case 1:
      mode = WIFI_STA;
      break;
    case 2:
      mode = WIFI_AP;
      break;
    case 3:
      mode = WIFI_AP_STA;
      break;
    case 4:
      break;
    default:
      break;
  }
  return mode;
}

String toStringWifiStatus(int state) {
  String status;
  switch (state) {
    case 0:
      status = "connecting";
      break;
    case 1:
      status = "unknown status";
      break;
    case 2:
      status = "wifi scan completed";
      break;
    case 3:
      status = "got IP address";
      // statements
      break;
    case 4:
      status = "connection failed";
      break;
    default:
      // statements
      break;
  }
  return status;
}

String toStringEncryptionType(int thisType) {
  String eType;
  switch (thisType) {
    case ENC_TYPE_WEP:
      eType = "WEP";
      break;
    case ENC_TYPE_TKIP:
      eType = "WPA";
      break;
    case ENC_TYPE_CCMP:
      eType = "WPA2";
      break;
    case ENC_TYPE_NONE:
      eType = "None";
      break;
    case ENC_TYPE_AUTO:
      eType = "Auto";
      break;
  }
  return eType;
}



IPAddress stringToIP(String address) {
  int p1 = address.indexOf('.'), p2 = address.indexOf('.', p1 + 1), p3 = address.indexOf('.', p2 + 1); //, 4p = address.indexOf(3p+1);
  String ip1 = address.substring(0, p1), ip2 = address.substring(p1 + 1, p2), ip3 = address.substring(p2 + 1, p3), ip4 = address.substring(p3 + 1);

  return IPAddress(ip1.toInt(), ip2.toInt(), ip3.toInt(), ip4.toInt());
}


static void _u0_putc(char c) {
  while (((U0S >> USTXC) & 0x7F) == 0x7F);
  U0F = c;
}

void initSerial() {
  Serial.begin(9600);
  ets_install_putc1((void *) &_u0_putc);
  system_set_os_print(1);
}


bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  const char* Jssid = json["ssid"];
  const char* Jpassword = json["password"];
  const char* Jhostname = json["hostname"];
  const char* Jip = json["ip"];
  const char* Jmode = json["mode"];
  const char* Jgateway = json["gateway"];
  const char* Jnetmask = json["netmask"];
  const char* Jdhcp = json["dhcp"];
  const char* Jstaticip = json["staticip"];

  currentConf.ssid = (char*)Jssid;
  currentConf.hostname = (char*)Jhostname;
  currentConf.password = (char*)Jpassword;
  currentConf.ip = (char*)Jip;
  currentConf.net_mode = intToWifiMode((int)Jmode);
  currentConf.dhcp = (char*)Jdhcp;
  currentConf.gateway = (char*)Jgateway;
  currentConf.netmask = (char*)Jnetmask;
  currentConf.staticip = (char*)Jstaticip;

//    Serial.print(currentConf.ssid); Serial.print(" | "); Serial.print(currentConf.hostname); Serial.print(" | "); Serial.print(currentConf.ip); Serial.print(" | "); Serial.print(currentConf.net_mode); Serial.print(" | "); Serial.print(currentConf.gateway); Serial.print(" | "); Serial.print(currentConf.netmask); Serial.print(" | "); Serial.print(currentConf.dhcp); Serial.print(" | ");  Serial.println(currentConf.staticip);
  return true;
}

bool saveConfig() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();

  json["ssid"] = currentConf.ssid;
  json["hostname"] = currentConf.hostname;
  json["ip"] = currentConf.ip;
  json["mode"] = toStringWifiMode(currentConf.net_mode);
  json["gateway"] = currentConf.gateway;
  json["netmask"] = currentConf.netmask;
  json["dhcp"] = currentConf.dhcp;
  json["staticip"] = currentConf.staticip;

//    Serial.print(currentConf.ssid); Serial.print(" | "); Serial.print(currentConf.hostname); Serial.print(" | "); Serial.print(currentConf.ip); Serial.print(" | "); Serial.print(currentConf.net_mode); Serial.print(" | "); Serial.print(currentConf.gateway); Serial.print(" | "); Serial.print(currentConf.netmask); Serial.print(" | "); Serial.print(currentConf.dhcp); Serial.print(" | ");  Serial.println(currentConf.staticip);

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return true;
}
