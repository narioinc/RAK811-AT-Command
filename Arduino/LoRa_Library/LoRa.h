#include<SoftwareSerial.h>
#define TXpin 1   // Set the virtual serial port pins
#define RXpin 0
SoftwareSerial mySerial(RXpin,TXpin);    // Declare a virtual serial port
char buffer[128];

void cleanbuf()
{
  memset(buffer,0,sizeof(buffer));
}

int rk_getVersion(void)
{
 // This function is used to get the module version
  char* offest;
 mySerial.write("at+version\r\n"); 
  delay(100);
 while (mySerial.available()>0) {
  delay(100);
  int numdata = mySerial.available();  
  mySerial.readBytes(buffer,numdata);
  //Serial.println(buffer); 
  if (0==strncmp(buffer,"OK",2)){
      offest = strstr(buffer,"\r\n");
      offest[0]= 0;
      Serial.print("rk get version:");
      Serial.println(&buffer[2]);
      cleanbuf();
      return 0;
   } else {
      return -1;
   }
 }
}

int rk_getBand(void)
{
  //This function is used to get the frequency band of the module
  char* offest;
  mySerial.write("at+band\r\n");    
  delay(100);
  while (mySerial.available()>0) {
  delay(100);
  int numdata = mySerial.available();  
  mySerial.readBytes(buffer,numdata);
  //Serial.println(buffer); 
  if (0==strncmp(buffer,"OK",2)){
      offest = strstr(buffer,"\r\n");
      offest[0]= 0;
      Serial.print("rk get band:");
      Serial.println(&buffer[2]);
      //strcpy(vers,&buffer[2]);
      cleanbuf();
      return 0;
   } else {
      return -1;
   }
 }
}

void rk_setConfigOTAA(char* devEUI, char* appEUI, char* appKEY)
{
  // This function is used to set the necessary parameters for module OTAA
  char Str[128] = {};
  sprintf(Str,"at+set_config=dev_eui:%s&app_eui:%s&app_key:%s\r\n",devEUI,appEUI,appKEY);
  
  Serial.print(Str);
  mySerial.write(Str); 
  delay(500);
  while (mySerial.available()>0) {
  delay(100);
  int numdata = mySerial.available();  
  mySerial.readBytes(buffer,numdata);
  Serial.println(&buffer[0]); 
  cleanbuf();
 }  
}

void rk_setConfigABP(char* devADDR, char* nwksKEY, char* appsKEY)
{
  // This function is used to set the required parameters for module ABP
  char Str[128] = {};
  sprintf(Str,"at+set_config=dev_addr:%s&nwks_key:%s&apps_key:%s\r\n",devADDR,nwksKEY,appsKEY);
  
  Serial.print(Str);
  mySerial.write(Str); 
  delay(500);
  while (mySerial.available()>0) {
  delay(100);
  int numdata = mySerial.available();  
  mySerial.readBytes(buffer,numdata);
  Serial.println(&buffer[0]); 
  cleanbuf();
 }  
}

void rk_joinLoraNetwork(int mode)
{
  // This function is used to join the network
  char Str[20] = {};
  if (mode == 0)
  sprintf(Str,"at+join=otaa\r\n");
  else if (mode == 1)
  sprintf(Str,"at+join=abp\r\n");
      
  Serial.print(Str);
  mySerial.write(Str);
  delay(500);
  while(mySerial.available()>0) {
    delay(100);
    int numdata = mySerial.available();  
    mySerial.readBytes(buffer,numdata);
    Serial.println(&buffer[0]); 
    cleanbuf();
  }  
   
  delay(8000);   // Wait for the result to be returned
  while(mySerial.available()>0) {
    delay(1000);
    int numdata = mySerial.available();  
    mySerial.readBytes(buffer,numdata);
    Serial.println(&buffer[0]); 
    cleanbuf();  
  }
}

int rk_sendConfirmUplinkData(int port, char* data)
{
  // This function is used to send the data to be verified
  char Str[128] = {};
  sprintf(Str,"at+send=1,%d,%s\r\n",port,data);
  Serial.print(Str);
  mySerial.write(Str);    
  delay(500);
  while(mySerial.available()>0) {
    delay(200);
    int numdata = mySerial.available();  
    mySerial.readBytes(buffer,numdata);
    Serial.println(&buffer[0]);
    cleanbuf(); 
  }     
}

int rk_sendUnConfirmUplinkData(int port, char* data)
{
  // This function is used to transmit data need not check
  char Str[128] = {};
  sprintf(Str,"at+send=0,%d,%s\r\n",port,data);
  Serial.print(Str);
  mySerial.write(Str);    
  delay(500);
  while(mySerial.available()>0) {
    delay(200);
    int numdata = mySerial.available();  
    mySerial.readBytes(buffer,numdata);
    Serial.println(&buffer[0]); 
    cleanbuf();
  }     
}
