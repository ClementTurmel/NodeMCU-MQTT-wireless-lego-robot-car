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
 
  ## Web page
 
 ![Webpage](https://raw.githubusercontent.com/Clemaul/NodeMCU-MQTT-wireless-lego-robot-car/master/img/webpage.PNG)
 
  ## troubleshooting
  
First I wase using for power only 6 AA battery pack for motors shield AND for the nodemcu board (with a jumper between "vim" and "vm" pins on the motors shield). It work very well but, with time, **car was not responding after few second of work**. 
  
**Why ?** I think is because of shared alimentation between motors and nodemcu board. Motors make a **drop in voltage** affecting Nodemcu board.
  
**Solution : use a dedicated alimentation for the nodemcu board** and keep 6 AA battery pack only for motors. I recently purchase a 18650 Li-ion battery with 18650 shield and it works great. I plugged 18650 shield on Nodemcu board through USB port. 
Next step will be to wire it through vin/gnd pins.

## Upgrades
* adding camera to car using Raspberry 0 with Camera V2 (same as the Raspberry with Mosquitto broker ont it)
* adding a dedicated battery to the Raspberry 0 for camera (maybe another 18650 shield ?)
* adding camera view to webpage (adding video component form UV4L)
