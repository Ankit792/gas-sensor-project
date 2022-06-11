#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial SIM900(7, 8);              // gsm module connected here
String textForSMS;
int SmokeSensor = A1;                     // Flame Sensor
int Buzzer = 9;                          // Alarm/light can be connected with this Buzzer
int led = 10;
int ledyel = 6;

Servo myservo;                        // create servo object to control a servo
int potpin = 0;                      // analog pin used to connect the potentiometer
int val;                            // variable to read the value from the analog pin

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 
void setup() {

myservo.attach(13);               // attaches the servo on pin 9 to the servo object

randomSeed(analogRead(0));
Serial.begin(9600);
SIM900.begin(9600);               // original 19200. while enter 9600 for sim900A

lcd.begin(16, 2);
pinMode(SmokeSensor, INPUT); 
pinMode(Buzzer, OUTPUT); 

digitalWrite(Buzzer, LOW); 
delay(5000); // wait for 5 seconds
  
}
 
void loop() {
 
  int a = analogRead(SmokeSensor);            //read analog input
  if (a > 300) // 
  {
  textForSMS =  "\nFire Detected!";  
  digitalWrite(Buzzer, HIGH); 
  digitalWrite(led, HIGH);
  digitalWrite(ledyel, LOW);
  delay(1000);
  sendSMS(textForSMS);
  
  val = analogRead(potpin);             // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);      // scale it to use it with the servo (value between 0 and 180)                            
  myservo.write(val);                   // sets the servo position according to the scaled value
  delay(15);
   
  Serial.println(a);
  Serial.println(textForSMS);
  Serial.println("message sent."); 
  lcd.setCursor(0, 0);
  lcd.print(a);
  lcd.setCursor(0, 1);
  lcd.print("message sent.");
  delay(2000);
  }
  
  else
  {
  Serial.println("No Fire Detected"); 
  Serial.println(a);
  lcd.setCursor(0, 0);
  lcd.print("No Smoke Detected");
  digitalWrite(Buzzer, LOW);
  digitalWrite(led, LOW);
  digitalWrite(ledyel, HIGH);
  delay(2000);
  delay(1000);
  }
}
 
 
void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
 SIM900.println("AT+CMGS = \"+91xxxxxxxxxx\"");  // recipient's mobile number, in international format
 
  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS
}

