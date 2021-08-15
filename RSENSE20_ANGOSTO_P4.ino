//RSENSE20_ANGOSTO_P4
#include "AdafruitIO_WiFi.h"

#define IO_USERNAME "Dangosto_RSENSE"
#define IO_KEY "aio_ftRH63NpFa7JSDhswK90yS8c7vhN"

const char* ssid     = "RSENSE20_ANGOSTO_P4";
const char* password = "12345678";

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
// Don't change the names of these #define's! they match the variant ones
#define SPIWIFI SPI
#define SPIWIFI_SS 10 // Chip select pin
#define NINA_ACK 9    // a.k.a BUSY or READY pin
#define NINA_RESETN 6 // Reset pin
#define NINA_GPIO0 -1 // Not connected
#endif

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, password, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, password);
#endif

AdafruitIO_Feed * temperatureFeed = io.feed("Temperature");
AdafruitIO_Feed * HuidityFeed = io.feed("Humidity");
AdafruitIO_Feed * ListenFeed = io.feed("RSENSE20_ANGOSTO_P4.8");
int temperature;
int humidity;

void handleMQTT(AdafruitIO_Data *data) {
  Serial.print("Recivido de RSENSE20_ANGOSTO_P4.8:\t");
  Serial.println(data->value());
}

void setup() {
  Serial.begin(115200);

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

  io.connect();
  ListenFeed->onMessage(handleMQTT);
  
  while (io.status() < AIO_CONNECTED)
  {
    Serial.println("Conectando MQTT");
    delay(500);
  }

  //handleMQTT->get();
  
}

void loop() {
  io.run();
  temperature = 25 + random(-5, 5);
  humidity = 50 + random(-10, 10);
  temperatureFeed->save(temperature);
  HuidityFeed->save(humidity);
  delay(5000);
}
