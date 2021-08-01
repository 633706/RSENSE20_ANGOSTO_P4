//RSENSE20_ANGOSTO_P4

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <SPIFFS.h>
#include <time.h>

const char* ssid     = "RSENSE20_ANGOSTO_P4";
const char* password = "12345678";

const uint16_t TCPport = 455;
const char * TCPhost = "192.168.43.32";

const char* ntpServer = "pool.ntp.org";
long  UTC_timezoneOFsset_sec = 3600;
const int   dayLightOffset = 3600;

struct tm timeinfo;
int Hour, Minute, Second;
int Hour0 = 0, Minute0 = 0, Second0 = 0;
String TimeWeb;
char tempTimeWeb[255];
bool resetTime = false;
AsyncWebServer server(80);


String WebHandler(const String& placeholder) {
  if (placeholder == "STATE") {
    getLocalTime(&timeinfo);

    if (resetTime) {
      Hour0 = timeinfo.tm_hour;
      Minute0 = timeinfo.tm_min;
      Second0 = timeinfo.tm_sec;
    }

    Hour = timeinfo.tm_hour - Hour0;
    Minute = timeinfo.tm_min - Minute0;
    Second = timeinfo.tm_sec - Second0;


    if (Second < 0) {
      Second = Second + 60;
      --Minute;
    }//check overflow para segundos
    if (Minute < 0) {
      Minute = Minute + 60;
      --Hour;
    }//check overflow para minutos
    if (Hour < 0) Hour = Hour + 24; //check overflow para horas, no  implementa compensación al solo dar la hora.
    sprintf(tempTimeWeb, "%02d:%02d:%02d", Hour, Minute, Second);
    TimeWeb = String(tempTimeWeb);
    return TimeWeb;
  }
  return String();
}


void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("Error al montar el sistema de archivos");
    while (1);
  }

  WiFi.begin(ssid, password);
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

  Serial.println("Conexion correcta a NTP y red WiFi");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, WebHandler);
    resetTime = false;
    Serial.println("root");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
    Serial.println("css file");
  });


  server.on("/resetTime", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, WebHandler);
    resetTime = true;
    Serial.println("resetTime");
  });

  server.on("/currentTime", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, WebHandler);
    resetTime = false;
    Serial.println("css file");
  });

  server.begin();

  Serial.print("Server configurado, para leer la hora ve a:\t");
  Serial.println(WiFi.localIP());
}

void loop() {
}
