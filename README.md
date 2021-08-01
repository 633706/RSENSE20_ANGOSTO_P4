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

## Punto 2: Obtencion de hora desde servidor NTP.
Commit 75387348.

Conexión a red Wifi RSESENSE20_ANGOSTO_P4, se envía por puerto serie la IP. A través de servidor NTP se obtiene la hora y se envía cada segundo por puerto serie.
### Hiperterminal con datos del NTP.
![NTP time](./documentation/Punto2_TerminalCOM.png)

## Punto 3: Comunicación por TCP.
Commit e5fc11e8.

Usando Socket Test se prepara un servidor y cliente en el mismo equipo comoo prueba de funcinanmiento.
### Dos instancias de Socket test conmunicandose.
![Socket Test terminal](./documentation/Punto3_Socketest.png)

## Punto 4: Comunicación por TCP desde ESP32.
Commit 1a3486ad.

Usando Socket Test se prepara un servidor para envíar la hora cada segundo, también se envía por puerte serie. En el ESP2 se configura la IP del equipo y en SocketTest se configura como 0.0.0.0 para que funcione. Se usa el puerto 455.
### Hiperterminal y socketTest con datos del NTP.
![Socket Test SocketTests_COM](./documentation/Punto4_Socketest_COM.png)

## Punto 5:  Comunicación bidirecctional por TCP con ESP32.
Commit x.

Partiendo del commit 1a3486ad se implementan los comandos start y stop para el paro o reanudación del envío de mensajes.
### Hiperterminal y socketTest con datos del NTP y comandos.
![Socket Test SocketTests_COM](./documentation/Punto3_Socketest.png)
---
## Bibliografía:
* [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32)
* [Espressif API reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html).
* [Sockect test](http://sockettest.sourceforge.net/)
## Librerías de terceros:
* [ESP32 ping library](https://github.com/marian-craciunescu/ESP32Ping)
    * Usa el protocolo a nivel de red ICMP.
---
David Angosto Latorre, 633706
