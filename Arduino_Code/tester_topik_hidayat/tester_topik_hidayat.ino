#include <WiFi.h>
#include <HTTPClient.h>
#include <ros.h>
#include <std_msgs/String.h>

const char* ssid = "Robot AI";
const char* password = "90002956";

IPAddress server(192, 168, 1, 157);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher topik("topik_hidayat", &str_msg);

char topik_incity1[14] = "incity1=req";
char topik_incity2[14] = "incity2=req";
char topik_incity3[14] = "incity3=req";
char topik_outcity1[15] = "outcity1=req";
char topik_outcity2[15] = "outcity2=req";
char topik_outcity3[15] = "outcity3=req";
char topik_icebox_clear[21] = "incityemptybox=clear";
char topik_ocebox_clear[22] = "outcityemptybox=clear";
char topik_icebox_blocked[23] = "incityemptybox=blocked";
char topik_ocebox_blocked[24] = "outcityemptybox=blocked";

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());
  // Start to be polite
  nh.advertise(topik);
}

void loop() {
  if (Serial.available() > 0)
  {
    int str = Serial.parseInt();
    Serial.print("Data yang masuk: ");
    Serial.println();
    switch (str) {
      case 1:
        if (nh.connected()) {
          Serial.println("Connected Topic 1");
          str_msg.data = topik_incity1;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 2:
        if (nh.connected()) {
          Serial.println("Connected Topic 2");
          str_msg.data = topik_incity2;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 3:
        if (nh.connected()) {
          Serial.println("Connected Topic 3");
          str_msg.data = topik_incity3;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 4:
        if (nh.connected()) {
          Serial.println("Connected Topic 4");
          str_msg.data = topik_outcity1;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 5:
        if (nh.connected()) {
          Serial.println("Connected Topic 5");
          str_msg.data = topik_outcity2;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 6:
        if (nh.connected()) {
          Serial.println("Connected Topic 6");
          str_msg.data = topik_outcity3;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 7:
        if (nh.connected()) {
          Serial.println("Connected Topic 7");
          str_msg.data = topik_icebox_clear;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
      case 8:
        if (nh.connected()) {
          Serial.println("Connected Topic 8");
          str_msg.data = topik_ocebox_clear;
          topik.publish( &str_msg );
        } else {
          Serial.println("Not Connected");
        }
        break;
    }
  }
  nh.spinOnce();
}
