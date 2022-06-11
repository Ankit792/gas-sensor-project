// for gsm test

#include<SoftwareSerial.h>
SoftwareSerial gsm(7,8); //(gsmTX,RX) of arduino
void setup()
{
  Serial.begin(9600);
  gsm.begin(9600);
}
void loop()
{
  if(gsm.available())
  {
    Serial.write(gsm.read());
  }
  if(Serial.available())
  {
    byte a=Serial.read();
    if(a=='#')
    {
      gsm.write( 0x1a );  //hex of ctr+z
    }
    else
    {
      gsm.write(a);
    }
  }
}


// for message

//#include<SoftwareSerial.h>
//SoftwareSerial gsm(7,8);
//
//void setup()
//{
//  delay(10000);
//  Serial.begin(9600);
//  gsm.begin(9600);
//  gsm.println("AT+CMGF=1");   // AT+CMGF=1 turn on message send mode
//  delay(1000);
//  gsm.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); //replace x by your number 
//  delay(1000);
//  gsm.println("hello");
//  delay(100);
//  gsm.println((char)26);
//  delay(1000);
//}
//void loop()
//{
//  
//}


//// for call
//
//#include<SoftwareSerial.h>
//SoftwareSerial gsm(7,8);
//
//void setup()
//{
//  delay(10000);
//  Serial.begin(9600);
//  gsm.begin(9600);
//  gsm.println("ATDxxxxxxxxxx;"); //replace x by your number
//  delay(100);
//  gsm.println("ATH");     // to dissconect call, ATD to call last number 
//}
//void loop()
//{
//  
//}
 


