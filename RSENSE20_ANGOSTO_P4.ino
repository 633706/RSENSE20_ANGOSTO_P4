//RSENSE20_ANGOSTO_P4

#include <WiFi.h>
#include <ESP32Ping.h>

const char* ssid     = "RSENSE20_ANGOSTO_P4";
const char* password = "12345678";

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

  if (Ping.ping("www.google.com", 10)) {
    Serial.print("Ping OK, tiempo medio:\t");
    Serial.print(Ping.averageTime());
    Serial.print(" ms");
  } else
    Serial.println("Ping NOK");

}
void loop() {

}
