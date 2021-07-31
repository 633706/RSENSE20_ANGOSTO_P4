# RSENSE20_ANGOSTO_P4

Desarrollado para la arduino IDE
Repositorio para la práctica P4 de redes de sensores.

## Programa base:
Commit 0fd2ed84.

Conexión a red Wifi RSESENSE20_ANGOSTO_P4, se envía por puerto serie la IP. PING a www.google.com y envío de tiempo medio por puerto serie.
### Montaje
![FotoMonaje](./documentation/ProgramaBase_FotoMontaje.png)

### Hiperterminal con datos del ping.
![Ping](./documentation/ProgramaBase_TerminalCOM.png)

## Punto 2:
Commit 0fd2ed84.
Conexión a red Wifi RSESENSE20_ANGOSTO_P4, se envía por puerto serie la IP. A través de servidor NTP se obtiene la hora y se envía cada segundo por puerto serie.


### Hiperterminal con datos del NTP.
Commit x.

También se muetra la hora del ordenador usado en el desarrollo.

![NTP time](./documentation/Punto2_TerminalCOM.png)
---
## Bibliografía:
* [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32)
* [Espressif API reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html).
## Librerías de terceros:
* [ESP32 ping library](https://github.com/marian-craciunescu/ESP32Ping)
    * Usa el protocolo a nivel de red ICMP.
---
David Angosto Latorre, 633706
