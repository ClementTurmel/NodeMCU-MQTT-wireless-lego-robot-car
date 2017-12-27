#include <Wire.h> 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_SSID_PASSWORD";

ESP8266WebServer server(80);
Servo servo;

//Define motors PIN (NodeMCU Motors shield)
#define DIRA 0
#define PWMA 5

#define DIRB 2
#define PWMB 4

void handleRoot(){
  server.send(200, "text/html", "ok!");
}


void moveUp(){
  carUp();
  server.send(200, "text/html", "ok up");
  
}

void moveDown(){
  carDown();
  server.send(200, "text/html", "ok down");
  
}
void moveLeft(){
  carLeft();
  server.send(200, "text/html", "ok left");
  
}
void moveRight(){
  carRight();
  server.send(200, "text/html", "ok right");
  
}

void moveStop(){
  carStop();
  server.send(200, "text/html", "ok Stop");
  
}

void fire(){
  servo.write(20);
  delay(500);
  servo.write(0);
  server.send(200, "text/html", "ok Fire");
}

void carUp(){
  digitalWrite(DIRA,1);
  digitalWrite(DIRB,1);
  analogWrite(PWMA,1000);
  analogWrite(PWMB,900);
  //delay(100);
}

void carDown(){
  digitalWrite(DIRA,0);
  digitalWrite(DIRB,0);
  analogWrite(PWMA,1000);
  analogWrite(PWMB,900);
  //delay(100);
}

void carLeft(){
  digitalWrite(DIRA,0);
  digitalWrite(DIRB,1);
  analogWrite(PWMA,1000);
  analogWrite(PWMB,900);
  //delay(100);
}

void carRight(){
  digitalWrite(DIRA,1);
  digitalWrite(DIRB,0);
  analogWrite(PWMA,1000);
  analogWrite(PWMB,900);
  //delay(100);
}

void carStop(){
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}


void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");
  
  Serial.println("Attaching Servo");
  //servo.attach(2); //D4
  servo.attach(15); //D8
  servo.write(0);
  
  Serial.println("Preparing motor...");

  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  analogWrite(PWMA,0);
  digitalWrite(DIRA,1);
  analogWrite(PWMB,0);
  digitalWrite(DIRB,1);
  
  Serial.println("Connecting to Wifi...");
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  // Route
  server.on("/", handleRoot);
  server.on("/up", moveUp);
  server.on("/down", moveDown);
  server.on("/left", moveLeft);
  server.on("/right", moveRight);
  server.on("/stop", moveStop);
  server.on("/fire", fire);
  
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Starting Loop");
}

void loop() {
  server.handleClient();
}




