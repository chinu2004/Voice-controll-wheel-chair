#include <ESP32Servo.h>
String readvoice;
#include <Wire.h>
Servo myServo;  // Create a servo object

int servoPin = 18;  // Pin connected to the servo signal

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);  // Attach the servo to the specified pin
}

void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readvoice.length() > 0) {
    Serial.println(readvoice); 
  if (readvoice == "*start#"){
    cal();
  }
readvoice="";}}
void cal() {
  // Move the servo from 0 to 120 degrees
  for (int angle = 0; angle <= 120; angle++) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(15);  // Wait for 15 milliseconds for a smooth movement
  }
}
 
