//RSENSE20_ANGOSTO_P4

#include <WiFi.h>
#include "time.h"

const char* ssid     = "RSENSE20_ANGOSTO_P4";
const char* password = "12345678";

const char* ntpServer = "pool.ntp.org";
const long  UTC_timezoneOFsset_sec = 3600;
const int   dayLightOffset = 3600;
struct tm timeinfo;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  int i = 0;

  for  (i = 0; i < 10; i++) {
    if ( WiFi.status() == WL_CONNECTED)
      break;
    delay(1000);
    Serial.print("Intentando conectar a :\t");
    Serial.println(ssid);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Fallo en la conexion Wifi");
    while (1);
  }

  Serial.print("\r\nConectado a la red con IP:\t");
  Serial.println(WiFi.localIP());

  configTime(UTC_timezoneOFsset_sec, dayLightOffset, ntpServer);
}
void loop() {
  if (getLocalTime(&timeinfo))
    Serial.println(&timeinfo, " %H:%M:%S");
  else
    Serial.println("Fallo al conseguir la hora");
  delay(1000);
}
