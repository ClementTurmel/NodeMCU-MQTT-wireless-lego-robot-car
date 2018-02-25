#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Servo.h>

const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "mqtt_server";
const int   mqtt_server_port = 1883;
const char* mqtt_login = "mqtt_login";
const char* mqtt_pwd = "mqtt_pwd";

WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;

long lastMsg = 0;
char msg[50];
int value = 0;
int ammo;

int motorSpeedA = 1000;
int motorSpeedB = 900;
String lastMoveAction;

//Define motors PIN (NodeMCU Motors shield)
#define DIRA 0
#define PWMA 5

#define DIRB 2
#define PWMB 4

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  String payloadString;
  String topicString;
  
  //parsing payload from array to String
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    payloadString += (char)payload[i];
  }
  
  //parsing topic from array to String
  for(int i = 0; i < strlen(topic) ; i++){
    topicString += (char)topic[i];
  }
  
  
  Serial.println("topic : " + topicString + " | payloadString : " + payloadString);
  
  if(payloadString == "up"){ 
    carUp();
  }
  else if(payloadString == "stop"){ 
    carStop();
  }
  else if(payloadString == "left"){ 
    carLeft();
  }
  else if(payloadString == "right"){ 
    carRight();
  }
  else if(payloadString == "down"){ 
    carDown();
  }
  else if(payloadString == "space"){ 
    fire();
  }
  
  if(topicString=="robot-lego-car-speed"){
    Serial.print("Message with robot-lego-car-speed ! ");
    int speed = payloadString.toInt();  
    motorSpeedA = speed;
    motorSpeedB = (speed * 9) / 10 ;
    // carUp();
  }

     
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_login, mqtt_pwd)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("robot-lego-car");
      client.subscribe("robot-lego-car-speed");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);
  
  Serial.println("Attaching Servo");
  servo.attach(15); //D8
  servo.write(90);  // set servo to mid-point
  
  Serial.println("Preparing motor...");

  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  analogWrite(PWMA,0);
  digitalWrite(DIRA,1);
  analogWrite(PWMB,0);
  digitalWrite(DIRB,1);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
/*
   snprintf (msg, 75, "open");
   Serial.print("Publish message: ");
   Serial.println(message);
   client.publish("sensor/door", msg, true);
*/
}

// ***********************************************

void fire(){
  Serial.print("**** fire ****");
  if(ammo == 2){
    servo.write(0);
    delay(500);
    servo.write(40);
    ammo = ammo - 1;
  }else{
    servo.write(180);
    delay(500);
    servo.write(90);
    ammo = 2;
  }
}




void carUp(){
  Serial.println("**** carUp ****");
  digitalWrite(DIRA,1);
  digitalWrite(DIRB,1);
  analogWrite(PWMA,motorSpeedA);
  analogWrite(PWMB,motorSpeedB);
  //delay(100);
}

void carDown(){
  Serial.println("**** carDown ****");
  digitalWrite(DIRA,0);
  digitalWrite(DIRB,0);
  analogWrite(PWMA,motorSpeedA);
  analogWrite(PWMB,motorSpeedB);
  //delay(100);
}

void carLeft(){
  Serial.println("**** carLeft ****");
  digitalWrite(DIRA,0);
  digitalWrite(DIRB,1);
  analogWrite(PWMA,motorSpeedA);
  analogWrite(PWMB,motorSpeedB);
  //delay(100);
}

void carRight(){
  Serial.println("**** carRight ****");
  digitalWrite(DIRA,1);
  digitalWrite(DIRB,0);
  analogWrite(PWMA,motorSpeedA);
  analogWrite(PWMB,motorSpeedB);
  //delay(100);
}

void carStop(){
  Serial.println("**** carStop ****");
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}

