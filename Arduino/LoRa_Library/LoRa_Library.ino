#include "LoRa.h"

#define OTAA  0
#define ABP   1

#define JOIN_MODE OTAA   // set network mode, OTAA or ABP.
#if JOIN_MODE == OTAA
char* DevEui = "60C5A8FFFE000001";
char* AppEui = "70B3D57EF00047C0";
char* AppKey = "5D833B4696D5E01E2F8DC880E30BA5FE";
#else JOIN_MODE == ABP
char* NwkSKey = "3432567afde4525e7890cfea234a5821";
char* AppSKey = "a48adfc393a0de458319236537a11d90";
char* DevAddr = "00112233";
#endif
int port = 2;
char* data = "112233445566778899";

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 while(Serial.read()>= 0){}
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 Serial.println("Hello, world?");       
 mySerial.begin(115200);     
 mySerial.listen();
 //while(mySerial.read()>= 0){}

}


void loop() {
  // put your main code here, to run repeatedly:
int ret;

while(mySerial.read()>= 0){
  Serial.println(mySerial.read());
  }

ret = rk_getVersion();   // get module version 
if (ret !=0) {
   Serial.println("Get version failed");
}
delay(1000);
while(mySerial.read()>= 0){}

ret = rk_getBand();    // grt module band
if (ret !=0) {
   Serial.println("Failed to get the band");
  }
delay(1000);
while(mySerial.read()>= 0){}

#if JOIN_MODE == OTAA
rk_setConfigOTAA(DevEui,AppEui,AppKey);
delay(1000);
while(mySerial.read()>= 0){}
#else if JOIN_MODE == ABP
rk_setConfigABP(DevAddr,NwkSKey,AppSKey);
delay(1000);
while(mySerial.read()>= 0){}
#endif

rk_joinLoraNetwork(JOIN_MODE);   // join Network
delay(1000);
while(mySerial.read()>= 0){}

ret = rk_sendConfirmUplinkData(port,data);  // Send the data to be verified 
delay(1000);
while(mySerial.read()>= 0){}

ret = rk_sendUnConfirmUplinkData(port,data);   // Send data that does not need to be verified
delay(1000);
while(mySerial.read()>= 0){}
}


