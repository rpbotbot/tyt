//=====================================================
//     PROGRAM UNTUK PANEL PICK UP POINT
//=====================================================

#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ros.h>
#include <std_msgs/String.h>
#include "variabel.h"
#include "koneksi.h"

unsigned long lastWifiTime = 0;
unsigned long wifiDelay = 30000;

unsigned long lastCheckTime = 0;
unsigned long checkDelay = 6000;

unsigned long lastBuzzerTime = 0;
unsigned long buzzerDelay = 1000;

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
  pinMode(sensor7, INPUT);
  pinMode(sensor8, INPUT);
  pinMode(sensor9, INPUT);
  pinMode(sensor10, INPUT);

  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);

  WiFi.disconnect(true);

  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(out1, HIGH);
  digitalWrite(out2, HIGH);
  Serial.println("");

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());
  // Start to be polite
  nh.advertise(topik);

}

void loop() {

  int incity1 = digitalRead(sensor1);
  int incity2 = digitalRead(sensor2);
  int incity3 = digitalRead(sensor3);
  int outcity1 = digitalRead(sensor4);
  int outcity2 = digitalRead(sensor5);
  int outcity3 = digitalRead(sensor6);
  int inempty1 = digitalRead(sensor7);
  int inempty2 = digitalRead(sensor8);
  int outempty1 = digitalRead(sensor9);
  int outempty2 = digitalRead(sensor10);

  // WiFi check sequence
  if ((millis() - lastWifiTime) > wifiDelay) {

    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    lastWifiTime = millis();
  }

  // Check sequence
  if ((millis() - lastCheckTime) > checkDelay) {

    // Check incity line 1
    if (incity1 == LOW) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_incity1;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
    }

    // Check incity line 2
    if (incity2 == LOW) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_incity2;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
    }

    // Check incity line 3
    if (incity3 == LOW) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_incity3;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
    }

    // Check outcity line 1
    if (outcity1 == LOW) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_outcity1;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
    }

    // Check outcity line 2
    if (outcity2 == LOW) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_outcity2;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
    }

    // Check outcity line 3
    if (outcity3 == LOW) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_outcity3;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
    }
    
    // Check incity empty box
    if ((inempty1 == LOW) and (inempty2 == LOW)) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_icebox_blocked;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
      buzzState = true;
    }
    else {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_icebox_clear;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
      buzzState = false;
    }

    // Check outcity empty box
    if ((outempty1 == LOW) and (outempty2 == LOW)) {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_ocebox_blocked;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
      buzzState = true;
    }
    else {
      if (nh.connected()) {
        Serial.println("Connected");
        str_msg.data = topik_ocebox_clear;
        topik.publish( &str_msg );
      } else {
        Serial.println("Not Connected");
      }
      buzzState = false;
    }

    lastCheckTime = millis();
  }

  // Buzzer sequence
  if ((millis() - lastBuzzerTime) > buzzerDelay) {

    if (buzzState) {
      digitalWrite(out2, buzzState);
      digitalWrite(out3, buzz);
      buzzState = !buzzState;
    }
    else {
      digitalWrite(out2, HIGH);
    }

    lastBuzzerTime = millis();
  }

  nh.spinOnce();

}
