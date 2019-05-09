#include <NewPing.h>
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>

#define COMMON_ANODE

//visitor counting
#define MAX_DISTANCE 400
int echo_pin1 = 13;              // Echo Pin of the ultrasonic sensor
int trigger_pin1 = 12;           // Trigger pin ofthe ultrasonic sensor
int echo_pin2 = 10;
int trigger_pin2 = 9;
NewPing sonar(trigger_pin1, echo_pin1, MAX_DISTANCE);
NewPing sonar2(trigger_pin2, echo_pin2, MAX_DISTANCE);

int currentState = 0;
int previousState = 0;
int currentState2 = 0;
int previousState2 = 0;
float duration1, distance1, duration2, distance2;
int counter = 0;


//led
int redPin = 3;
int yellowPin = 2;
bool redsetPinHigh = false, yellowsetPinHigh = false;
int redStartTime = 0, yellowStartTime, onTime = 200;

// Wifi setup
char ssid[] = "catchingafish";     //  your network SSID (name)
char pass[] = "tee4853yet7727ding";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// UDP setup
WiFiUDP Udp;
IPAddress outIp(192,168,1,153); //destination of outgoing OSC messages
IPAddress ip(192,168,1,187);    //local ip for winc1500 wifi module

const unsigned int outPort = 9001;  //arduino out port; match the input port of OF
const unsigned int inPort = 12000;  //arduino receiver port; match the output port of OF

void setup() {
   WiFi.setPins(1,0,2);      //wifi pin M0
   //WiFi.setPins(8,7,4);    //wifi pin uno
   Serial.begin(9600);
   pinMode(redPin, OUTPUT);
   pinMode(yellowPin, OUTPUT);

   if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

  // wait 10 seconds for connection:
  delay(10000);
  }
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
  
  //initialising UDP, passing in to the inPort
  Udp.begin(inPort);  
}

void loop() {
  // put your main code here, to run repeatedly:
  countingPeople();
}

void pingDist1() {
  delay(100);
  duration1 = sonar.ping();
  distance1 = (duration1 / 2) * 0.0343;
  Serial.print("distance1:");
  Serial.println(distance1);
  OSCMessage msgOUT("/distance/0");
  msgOUT.add((float)distance1);
  Udp.beginPacket(outIp, outPort);
  msgOUT.send(Udp);
  Udp.endPacket();
  msgOUT.empty();
  delay(20);
}

void pingDist2(){
  delay(100);
  duration2 = sonar2.ping();
  distance2 = (duration2 / 2) * 0.0343;
  Serial.print("distance2:");
  Serial.println(distance2);
  OSCMessage msgOUT("/distance/1");
  msgOUT.add((float)distance2);
  Udp.beginPacket(outIp, outPort);
  msgOUT.send(Udp);
  Udp.endPacket();
  msgOUT.empty();
  delay(20);
}

void countingPeople(){
  pingDist1();
  pingDist2();
 // object enter
  if (distance1 <= 20 && distance1 > 0){
    currentState = 1;
  } else {
    currentState = 0;
  }
  delay(100);
  if (currentState != previousState){
    while (currentState == 1){
       delay(100);  //put in delay if two sensors are far away
       pingDist2();
       if (distance2 <= 20 && distance2 > 0){
        currentState2 = 1;
       } else {
        currentState2 = 0;
       }
       if (currentState2 != previousState2){
        if (currentState2 == 1){
          counter = counter + 1;
//          digitalWrite(redPin, HIGH);
//          delay(100);
//          digitalWrite(redPin, LOW);
//          delay(100);
        } else {
          //Serial.println(counter);
        }
        Serial.println(counter);
        OSCMessage msgOUT("/people/0");
        msgOUT.add((int)counter);
        Udp.beginPacket(outIp, outPort);
        msgOUT.send(Udp);
        Udp.endPacket();
        msgOUT.empty();
        delay(20);
        //delay(1000);
        return;
       }
    }
  }

//object exit
  if (distance2 <= 20 && distance2 > 0){
    currentState2 = 1;
  } else {
    currentState2 = 0;
  }
  delay(100);

  if (currentState2 != previousState2){
    while (currentState2 == 1){
      delay(100);
      pingDist1();
      if (distance1 <= 20 && distance1 > 0){
        currentState = 1;
      } else {
        currentState = 0;
      }
      delay(100);

      if (currentState != previousState){
        if (currentState = 1){
          counter = counter - 1;
          //Serial.println(counter);
          //led signal
//          digitalWrite(yellowPin, HIGH);
//          delay(100);
//          digitalWrite(yellowPin, LOW);
//          delay(100);
        } else {
          //Serial.println(counter);
        }
        Serial.println(counter);
        OSCMessage msgOUT("/people/0");
        msgOUT.add((int)counter);
        Udp.beginPacket(outIp, outPort);
        msgOUT.send(Udp);
        Udp.endPacket();
        msgOUT.empty();
        delay(20);
        //delay(1000);
        return;
      }
    }
  }
}

//void setColor(int red, int green, int blue)
//{
//  #ifdef COMMON_ANODE
//    red = 255 - red;
//    green = 255 - green;
//    blue = 255 - blue;
//  #endif
//  analogWrite(redPin, red);     
//  analogWrite(greenPin, green);  
//  analogWrite(bluePin, blue);    
//}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}



