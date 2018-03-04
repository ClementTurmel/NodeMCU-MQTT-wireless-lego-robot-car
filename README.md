# NodeMCU MQTT wireless lego robot car
A Wireless lego car based on NodeMCU (ESP8266) and MQTT

<p align="center">
  <img height="240" src="https://c1.staticflickr.com/5/4742/40611999981_4c5508cb0a_n.jpg">
  <img src="https://c1.staticflickr.com/5/4752/40611997171_6e66c80507_m.jpg">
  <img src="https://c1.staticflickr.com/5/4761/39901014364_4ce1162938_m.jpg">
</p>

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
 
 ## Architecture
 
 ![Architecture](https://raw.githubusercontent.com/Clemaul/NodeMCU-MQTT-wireless-lego-robot-car/master/img/NodeMCU%20MQTT%20robot%20lego%20car.png)
 

