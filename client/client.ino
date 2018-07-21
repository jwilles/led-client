#include <SoftwareSerial.h>
#define RX 10
#define TX 11

String AP = "ap";
String PASSWORD = "pass"

SoftwareSerial esp8266(RX,TX);

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  //esp8266.println(command);
  esp8266.println("AT+CWMODE=1");
  esp8266.println("AT+CWJAP=\"basement\",\"Timeplay49\"");
}

void loop() {

}
