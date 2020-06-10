#include<SocketIoClient.h>
#include<ESP8266WiFi.h>
#include<WebsocketsClient.h>
#include<SoftwareSerial.h>
#include <ArduinoJson.h>
//Socket client

SocketIoClient socket;
//Software Serial
const byte RX = 4 ;
const byte TX = 5 ;
SoftwareSerial mySerial(RX, TX);
String s;
void setup() {
  //Setup socket client and wifi
  WiFi.begin("TP-LINK_745E", "15284150");
  socket.begin("192.168.1.106", 3060);
  //Setup serial-UART
  Serial.begin(9600);
}

//Dinh dang tin nhan nhan duoc
//void msg(const char* payload, size_t length) {
//  Serial.println("Got message:%s \n", payload);
//}

uint64_t messageTimestamp;
void loop() {
  socket.loop();
  String AE_speed ;
  //Truyen data vs arduino- UART
  if (Serial.available()) {
    s = Serial.readStringUntil('\n');
    AE_speed = s;
    s = "";
  }
  //Truyen data len server-websocket
  uint64_t now = millis();
  if (now - messageTimestamp > 2000 ) {
    socket.emit("resSpeed", AE_speed.c_str());
    socket.on("setSpeedHardware", setSpeedA);
  }
}

void setSpeedA(const char* payload, size_t length) {
  Serial.println(payload);
}
