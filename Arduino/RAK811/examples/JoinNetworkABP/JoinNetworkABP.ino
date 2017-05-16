

#include "RAK811.h"
#include "SoftwareSerial.h"
#define WORK_MODE LoRaWAN   //  LoRaWAN or LoRaP2P
#define JOIN_MODE ABP    //  OTAA or ABP
#if JOIN_MODE == OTAA
String DevEui = "60C5A8FFFE000001";
String AppEui = "70B3D57EF00047C0";
String AppKey = "5D833B4696D5E01E2F8DC880E30BA5FE";
#else JOIN_MODE == ABP
String NwkSKey = "3432567afde4525e7890cfea234a5821";
String AppSKey = "a48adfc393a0de458319236537a11d90";
String DevAddr = "00112233";
#endif
#define TXpin 1   // Set the virtual serial port pins
#define RXpin 0
SoftwareSerial mySerial(RXpin,TXpin);    // Declare a virtual serial port
char* buffer = "72616B776972656C657373";

RAK811 RAKLoRa(mySerial);



void setup() {
 Serial.begin(38400);
 while(Serial.read()>= 0) {}
 while(!Serial);
 Serial.println("StartUP");

 mySerial.begin(9600);

}

void loop() {
 
 Serial.println(RAKLoRa.rk_getVersion());
 delay(500);
 Serial.println(RAKLoRa.rk_getBand());
 delay(500);
 if(RAKLoRa.rk_setWorkingMode(WORK_MODE))
 {
  Serial.println("you set Working mode is OK!");
  if (RAKLoRa.rk_initABP(DevAddr,NwkSKey,AppSKey))
    {
      Serial.println("you init ABP parameter is OK!");
      if (RAKLoRa.rk_joinLoRaNetwork(JOIN_MODE))
       {
           Serial.println("you join Network is OK!");
           mySerial.setTimeout(8000);
           String ver = mySerial.readStringUntil('\n');
           Serial.println(ver);
           mySerial.setTimeout(2000);
           if (ver == STATUS_JOINED_SUCCESS)
           {
            while (RAKLoRa.rk_sendData(1,1,buffer))
            {
              Serial.println(RAKLoRa.rk_recvData());
            }
           }
        }
     }
 }
 delay(500);
}
