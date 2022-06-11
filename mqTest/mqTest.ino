void setup() {
  // put your setup code here, to run once:
pinMode(A1,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int a = analogRead(A1); //read analog input
Serial.print("Sensor Value: ");
Serial.print(a);

  if(a>400)
    {
      Serial.print(" | Smoke detected!");
    }
   Serial.println("");
   delay(2000); 
}
