//RSENSE20_ANGOSTO_P4

#include <WiFi.h>

const char* ssid     = "RSENSE20_ANGOSTO_P4";
const char* password = "12345678";

const uint16_t TCPport = 455;
const char * TCPhost = "192.168.43.32";

const char* ntpServer = "pool.ntp.org";
const long  UTC_timezoneOFsset_sec = 3600;
const int   dayLightOffset = 3600;

struct tm timeinfo;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  int i = 0;

  for  (i = 0; i < 10; i++) {
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
  if (!client.connect(TCPhost, TCPport)) {
    Serial.println("Fallo en conexion a servidor");
    while (1);
  }
  Serial.println("Conexion correcta a TCP, NTP y red WiFi");

}

void loop() {
  if (getLocalTime(&timeinfo)) {
    Serial.println(&timeinfo, " %H:%M:%S");
    client.println(&timeinfo, " %H:%M:%S");
  }
  else {
    Serial.println("Fallo al conseguir la hora");
    client.println("Fallo al conseguir la hora");
  }
  delay(1000);
}
