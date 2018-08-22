#include <SoftwareSerial.h>

#define RX 10
#define TX 11

String AP = "ap";
String PASSWORD = "password";

String HOST = "ttc-led.dwcptziupj.us-east-2.elasticbeanstalk.com";
String PORT = "80";

int countTrueCommand;
int countTimeCommand;
boolean found = false;

SoftwareSerial esp8266(RX,TX);

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\"" + PASSWORD + "\"", 20, "OK"); 
}

void loop() {

  String getData = "GET /routes";
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(getData.length()+4), 4, ">");
  sendRequest(getData, 2000, true);
  //esp8266.println(getData);
  //delay(500);
  
 
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
  delay(15000);
  

}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  
  while(countTimeCommand  < (maxTime*1))
  {
    esp8266.println(command);
    if(esp8266.find(readReplay))
    {
      found = true;
      break;
    }
    countTimeCommand++;
  }
  
  if (found == true)
  {
    Serial.println("OYI");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  if (found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}

void sendRequest(String command, int maxTime, boolean debug) {
    String response = "";
    
    esp8266.println(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+maxTime) > millis())
    {
      while(esp8266.available())
      {

        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.println(response);
    }
    
    //return response;
}

