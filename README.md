# NodeMCU-wireless-lego-car
A Wireless lego car based on NodeMCU (ESP8266) and MQTT

## Hardware
* NodeMCU (ESP8266)
* NodeMCU motor shield
* Legos
* Two Lego M-Motor (for control)
* Servo motor (for shoot)
* 6 AA battery pack
* 6 AA batteries

* Raspberry V3 (to install mqtt broker)

## Software

### Arduino
 * Use ESP8266WiFi.h library and PubSubClient.h for using MQTT

### Raspberry
 * Mosquitto Broker with :
   * authentification
   * adding to mosquitto.conf :
     * listenner on ports 1883 & 1884
     * adding protocol websockets
 
### Web
 * HiveMQ mqttws31.js library, for using MQTT with Websocket
 * Jquery
 * Boostrap
 

