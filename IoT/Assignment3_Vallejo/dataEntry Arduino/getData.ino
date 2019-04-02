/**
 * Omar Vallejo
 * 1/12/2018
 * Assignment 3
 */

#include <SoftwareSerial.h>
#define _baudrate 115200
#define _rxpin 2
#define _txpin 3
SoftwareSerial debug(_rxpin, _txpin);

//defining the connectiong
#define SSID "IoT-One"
#define PASS "IoTL@BOne"
#define IP "192.168.0.10"
#define PORT 40003

//Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int sound=A1;       //button assigned to pin 7

int pValue;           // Store value from photoresistor (0-1023)
int sValue;           //Store value from button

void setup() {
  // put your setup code here, to run once:
  Serial.begin(_baudrate);
  debug.begin(_baudrate);

  sendDebug("AT");
  delay(5000);
  if(Serial.find("OK")){
    debug.println("RECIEVED: OK");
    connectWifi();
  }
  pinMode(pResistor, INPUT); // Set pResistor - A0 pin as an input (optional)
  pinMode(sound, INPUT);  //set button as input 
}

void loop() {
  // put your main code here, to run repeatedly loop
  
  pValue = analogRead(pResistor);  //allows the Aguino Board to read values
  sValue = digitalRead(sound);
  //Serial.println(pValue);
  //Serial.println(sValue);
  String photores = String(pValue); //convert to string
  String soundMod = String(sValue); //convert to string
  String data= (soundMod+ ", "+photores); ///////prints out photoresistor first//////////
  
  //Serial.println(data);
  updateGateway(data); //send data to updateGateway
  delay(5000);
}

void updateGateway(String data){

  //Setup connection to gateway
  String cmd = "AT+CIPSTART=\"UDP\",\"";
  cmd += IP;
  cmd += "\",";
  cmd += PORT;

  sendDebug(cmd);
  Serial.println("AT+CIFSR");
  delay(2000);
  if(Serial.find("Error")){
    debug.println("Recieved:Error");
    return;
  }

  cmd = data;

  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());

  if(Serial.find(">")){
    debug.print(">");
    debug.println(cmd);
    Serial.print(cmd);
  }
  else
  {
    sendDebug("AT+CIPCLOSE");
  }

  if(Serial.find("OK")){
    sendDebug("Recieved: OK");
    //may need to remove
    sendDebug("AT+CIPCLOSE");
  }
  else
  {
    sendDebug("Recieved: Error");
  }
}

void sendDebug(String cmd){
  debug.print("SEND: ");
  debug.println(cmd);
  Serial.println(cmd);
}

boolean connectWifi()
{
  Serial.println("AT+CWMODE=1");
  delay(2000);

  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";

  sendDebug(cmd);
  delay(8000);

  if(Serial.find("OK"))
  {
    debug.println("RECEIVED: OK");
    Serial.println("connected");
    return true;
  } else {
    debug.println("Recieved: Error");
    return false;
  }
}


