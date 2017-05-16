

#include "RAK811.h"
#include "SoftwareSerial.h"
#define WORK_MODE LoRaP2P  //  LoRaWAN or LoRaP2P
#define CODE  PING  // PING or PONG 
#define TXpin 1
#define RXpin 0
SoftwareSerial mySerial(RXpin,TXpin);
char* buffer = "72616B776972656C657373";
String FREQ = "860000000";  // frequency     range:(860000000 - 1020000000)

RAK811 RAKLoRa(mySerial);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  while(Serial.read()>= 0) {}
  while(!Serial);
  Serial.println("StartUP");

  mySerial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(RAKLoRa.rk_getVersion());
  delay(500);
  Serial.println(RAKLoRa.rk_getBand());
  delay(500);
  if (RAKLoRa.rk_setWorkingMode(WORK_MODE))
  {
    Serial.println("you set Working mode is OK!");
    if (RAKLoRa.rk_initP2P(FREQ,7,0,1,8,14))
    {
      Serial.println("you init P2P parameter is OK!");
      while (1)
      {
        #if  CODE == PING
         if (RAKLoRa.rk_sendP2PData(1,"10",buffer))
         {
          String ver = RAKLoRa.rk_recvData();
          //Serial.println(ver);
          if (ver == STATUS_P2PTX_COMPLETE)
          {
            Serial.println("send success");
            if (RAKLoRa.rk_recvP2PData(1))
            {
              Serial.println("open recv");
              Serial.println(RAKLoRa.rk_recvData());
            }
          }
          else
          {
            Serial.println(ver);
            delay(2000);
          }
         }
        #else if CODE == PONG
        if (RAKLoRa.rk_recvP2PData(1))
         {
          Serial.println("open recv");
          Serial.println(RAKLoRa.rk_recvData());
          if (RAKLoRa.rk_sendP2PData(1,"10",buffer))
          {
            String ver = RAKLoRa.rk_recvData();
            if (ver == STATUS_P2PTX_COMPLETE)
            {
              Serial.println("send success");
            }
            else
            {
              Serial.println(ver);
              delay(2000);
            }
          }
         }
        #endif
      }
    }
  }

}
