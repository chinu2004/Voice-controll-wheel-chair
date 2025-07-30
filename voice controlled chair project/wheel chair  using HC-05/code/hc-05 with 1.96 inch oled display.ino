String readvoice;
String state;
#include <U8g2lib.h>
#include <Wire.h>
 
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int a=0;//for Start
int b=0;//for conversation
int speed1=9;
int speed2=10;
int x,y;

//#include <SoftwareSerial.h>
//#include <Servo.h>
//Servo Myservo;
//long duration, distance;

void setup() {

  Serial.begin(9600);
  u8g2.begin();  // Initialize the display
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  //pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);   
  //pinMode(trigPin, OUTPUT);       // Set Trig Pin As O/P To Transmit Waves
  //pinMode(echoPin, INPUT);        //Set Echo Pin As I/P To Receive Reflected Waves
  //Myservo.attach(10);

}
//-----------------------------------------------------------------------//  
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readvoice.length() > 0) {
    Serial.println(readvoice); 
    
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);   
  //digitalWrite(trigPin, HIGH);              // Transmit Waves For 10us
  //delayMicroseconds(10);
  //duration = pulseIn(echoPin, HIGH);        // Receive Reflected Waves
  //distance = duration / 58.2;               // Get Distance
  //Serial.println(distance);
  //delay(10);

  if (readvoice == "*start#"){
    a=1;
    u8g2.clearBuffer();                 // Clear the internal memory
    u8g2.setFont(u8g2_font_ncenB14_tr); // Choose a suitable font
    u8g2.drawStr(0, 24, "Chair is Start ");
    u8g2.sendBuffer();                  // Transfer internal memory to the display
    delay(1000);                        // Display for 1 second

  // Clear the display
    u8g2.clearBuffer();
    u8g2.sendBuffer();

  // Wait for 2 seconds before clearing the display
 
    u8g2.setFont(u8g2_font_ncenB14_tr); // Choose a suitable font
    u8g2.drawStr(0, 24, "I'am Ready...");
    u8g2.sendBuffer();                  // Transfer internal memory to the display
    delay(1000);                        // Display for 1 second

 // Clear the display
    u8g2.clearBuffer();
    u8g2.sendBuffer();

 

  }
  if (readvoice == "*switch off#"){
    u8g2.clearBuffer();                 // Clear the internal memory
    u8g2.setFont(u8g2_font_ncenB10_tr); // Choose a suitable font
    u8g2.drawStr(0, 24, "Turning OFF"); // Draw the string at position (0,24)
    u8g2.sendBuffer();                  // Transfer internal memory to the display
    delay(2000);                        // Display for 1 second

    // Clear the display
    u8g2.clearBuffer();
    u8g2.sendBuffer();

    a=0;
  }
  else if((readvoice == "*forward#") && (a==1))
  {
    motion(); 
  } 

  else if((readvoice == "*back#") && (a==1))
  {
    back();
  }
  else if((readvoice == "*turn back#") && (a==1))
  {
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
    digitalWrite(3,HIGH);

     delay (3000);

    digitalWrite(5,LOW);
    digitalWrite(3,LOW);

  }
  
  else if ((readvoice == "*left#") && (a==1))
  { 

    digitalWrite (6,HIGH);
    digitalWrite (5,LOW);
    digitalWrite (4,LOW);
    digitalWrite (3,LOW);
    delay (750);
     
    digitalWrite (6,LOW);
    delay (250);
 
    motion();
 
  }
    
 else if (( readvoice == "*right#") && (a==1))
 {
   digitalWrite (6, LOW);
   digitalWrite (5, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (3, LOW);
   delay (750);
   digitalWrite (4, LOW);
   delay (250);
 
   motion();
 
 }
 
 else if (((readvoice == "*left bend#")|| (readvoice == "*left band#") || (readvoice == "*left bent#")||(readvoice == "*lift bent#")||(readvoice == "*left belt#")||(readvoice == "*lift belt#")) && (a==1))
 {
   digitalWrite (6, HIGH);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (3, LOW);
   delay (1000);
   digitalWrite (6,LOW);
 
 }

 else if (((readvoice == "*right bend#")|| (readvoice == "*right band#")||(readvoice == "*right bent#"))&&(a==1))
 {
   digitalWrite (6, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (3, LOW);
   digitalWrite (5, LOW);
   delay (1000);

   digitalWrite (4,LOW);
 }

 else if ((readvoice == "*stop#")|| (readvoice == "*top#"))
 {
   digitalWrite (6, LOW);
   digitalWrite (5, LOW);
   digitalWrite (4, LOW);
   digitalWrite (3, LOW);
 

 }

readvoice="";}}//Reset the variable

// continuous motion
void motion(){
  digitalWrite(6, HIGH);
  digitalWrite (4, HIGH);
  digitalWrite(5,LOW);
  digitalWrite(3,LOW);
  for(x=0;x<=50;x++){    // Change the speed 
    analogWrite(speed1,x);
    analogWrite(speed2,x);
    delay(50);
  }
}
// backward motion 
void back(){
  digitalWrite(6, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);

  for(y=0;y<=20;y++){    //Change the speed
    analogWrite(speed1,y);
    analogWrite(speed2,y);
    delay(50);
  }
  
}

 

 
 