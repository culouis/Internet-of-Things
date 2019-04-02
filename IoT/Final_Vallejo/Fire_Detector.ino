/*
 * Omar Vallejo
 * 1/16/2018
 * Final Project 
 * 
 * Fire_Detector:
 * This device will read if there is a flame going
 * and will set off a LED pattern to alert of the fire
 *
 */

//Constants Bellow
const int led1= 3;
const int led2 = 4;
const int led3 = 5;

int sensorPin = A0;
int sensorValue = 8;

#include <SoftwareSerial.h>
#define _baudrate 115200
#define _rxpin 2
#define _txpin 3
SoftwareSerial debug(_rxpin, _txpin);

//defining the connectiong
#define SSID "IoT-One"
#define PASS "IoTL@BOne"
#define IP "192.168.0.10"
#define PORT 10329

void setup() {
  // put your setup code here, to run once:
  
  //pin assignments
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(_baudrate);
  debug.begin(_baudrate);

  //Test connection with database
  sendDebug("AT");
  delay(5000);
  if(Serial.find("OK")){
    debug.println("RECIEVED: OK");
    connectWifi();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  sensorValue = analogRead(sensorPin);
  String data;
  int timer= 0;
  //tests if there is a fire
  while (sensorValue<50){
    timer+=1;
    data = "Fire";
    delay(200);
    ledFlash();
    sensorValue= analogRead(sensorPin);
  }
  if (timer==0){
    data = "No Fire";
  }
  
  data= (data+ ", "+timer); ///////prints out data first//////////
  Serial.println(data+ "\n");
  updateGateway(data); //send data to updateGateway
  delay(10000);
}

//LED warning pattern . Timer turns up to be 300 value
void ledFlash(){
  int times =0;
  while (times<6){
    digitalWrite(led1, HIGH); //turn led1 on
    delay(50);
    digitalWrite(led1, LOW); //turn led1 off
    delay(50);
    digitalWrite(led2, HIGH); //turn led1 on
    delay(50);
    digitalWrite(led2, LOW); //turn led1 off
    delay(50);
    digitalWrite(led3, HIGH); //turn led1 on
    delay(50);
    digitalWrite(led3, LOW); //turn led1 off
    delay(50);
    times+=1;
    }
}

//send data to gateway
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
