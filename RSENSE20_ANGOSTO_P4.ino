//RSENSE20_ANGOSTO_P4
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>

#include <WiFi.h>
#include <time.h>
#include <ESP32_FTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "RSENSE20_ANGOSTO_P4";
const char* passwordword = "12345678";

const char* ntpServer = "pool.ntp.org";
long UTC_timezoneOFsset_sec = 3600;
const int dayLightOffset = 3600;
struct tm timeinfo;

char timeStamp[255];
String timeStamp_string;

char dateStamp[255];
String dateStamp_string;

char fileName[255];
StaticJsonDocument<4000> JSON_docHandler;
char JSON_docHandler_cstr[1023];

float temperature;


char server[255] = "192.168.43.32";
char user[255] = "RSENSE20_ANGOSTO";
char password[255] = "RSENSE20";
ESP32_FTPClient ftp (server, user, password);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, passwordword);
  for  (int i = i = 0; i < 10; i++) {
    if ( WiFi.status() == WL_CONNECTED)
      break;
    delay(1000);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Fallo en la conexion a red WiFi");
    while (1);
  }

  configTime(UTC_timezoneOFsset_sec, dayLightOffset, ntpServer);

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Fallo al conseguir la hora");
    while (1);
  }
  ftp.OpenConnection();

  ftp.MakeDir("./tempeatureLog/");
  ftp.ChangeWorkDir("./tempeatureLog/");
}

void loop() {

  for (uint8_t i = 0; i < 30; i++) {
    temperature = 25 + random(-5, 5) ;
    JSON_docHandler["v"][i] = temperature;
    getLocalTime(&timeinfo);
    strftime(timeStamp, 255, "%T", &timeinfo);
    timeStamp_string = String(timeStamp);
    timeStamp_string.remove(timeStamp_string.indexOf(":"), 1);
    timeStamp_string.remove(timeStamp_string.indexOf(":"), 1);
    JSON_docHandler["t"][i] = timeStamp_string.toInt();
  }

    strftime(dateStamp, 255, "%F", &timeinfo);
    dateStamp_string = String(dateStamp);
    dateStamp_string.remove(dateStamp_string.indexOf("-"), 1);
    dateStamp_string.remove(dateStamp_string.indexOf("-"), 1);

  sprintf(fileName, "GRUPO_ANGOSTO_%s_%s.json", dateStamp_string.c_str(),timeStamp_string.c_str());

  ftp.InitFile("Type A"); //A = ascii (creo que json usa ascii)
  ftp.NewFile(fileName);
  serializeJson(JSON_docHandler, JSON_docHandler_cstr);
  delay(100);
  ftp.Write(JSON_docHandler_cstr);
  delay(100);
  ftp.CloseFile();

  delay(10000);

}
