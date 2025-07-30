#include "BluetoothSerial.h"
#include <Arduino.h>
#include <U8g2lib.h>

 
// Initialize the display (ensure you use the correct constructor for your display)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
const int centerX = 64;  // Center X position for the display
const int centerY = 40;  // Center Y position for the display
 
int a=0;
int b=0;
int speed1=12; // enter the pins in esp32 for speed contrll
int speed2=13;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
int led = 2;
 

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32Circuit"); //BLUETOOTH DEVICE NAME
  Serial.println("The device started, now you can pair it with bluetooth!");
  u8g2.begin();
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(34, OUTPUT);
}

void loop() {

  if (SerialBT.available()) {
    String value = SerialBT.readStringUntil('\n');
    value.toLowerCase();
    Serial.println(value);
    if(value == "light on")  //CLICK MIC BUTTON AND SAY "LIGHT ON" IN THE APP
    {
       digitalWrite(led,HIGH);
    }
    if(value == "start") //CLICK MIC BUTTON AND SAY "LIGHT OFF" IN THE APP
    {
      a=1;
      cal();
    }
    if(value == "stop") //CLICK MIC BUTTON AND SAY "LIGHT OFF" IN THE APP
    {
      stop();  
    }
    if(value == "go") //CLICK MIC BUTTON AND SAY "LIGHT OFF" IN THE APP
    {
      forward();  
    }   
    if(value == "right") //CLICK MIC BUTTON AND SAY "LIGHT OFF" IN THE APP
    {
      right();  
    }    
    if(value == "left") //CLICK MIC BUTTON AND SAY "LIGHT OFF" IN THE APP
    {
      digitalWrite(led,LOW);  
    }    
    if(value == "back") //CLICK MIC BUTTON AND SAY "LIGHT OFF" IN THE APP
    {
      back();  
    }
 
  }
}
void cal() {
  // Display width and height
  int displayWidth = 128;
  int gaugeHeight = 8;
  int borderThickness = 2; // Thickness of the stationary border
  int gaugeYPosition = (64 - gaugeHeight) / 2; // Center the gauge vertically
  int radius = 4; // Radius for the curved ends
  int textYPosition = gaugeYPosition - 12; // Position for the text above the gauge

  // Draw the loading line gauge with curved ends
  for (int i = 0; i <= displayWidth; i += 16) { // Increase the increment size to make it faster
    u8g2.clearBuffer(); // Clear the internal memory

    // Draw "Starting..." text
    u8g2.setFont(u8g2_font_ncenB08_tr); // Set font (adjust as needed)
    u8g2.drawStr(0, textYPosition, "Starting..."); // Draw the text

    // Draw the stationary border with curved ends
    u8g2.drawRFrame(0, gaugeYPosition - borderThickness, displayWidth, gaugeHeight + 2 * borderThickness, radius);

    // Draw the loading gauge
    u8g2.drawRBox(0, gaugeYPosition, i, gaugeHeight, radius); // Draw a rounded rectangle
    u8g2.sendBuffer(); // Transfer internal memory to the display
    delay(62); // Decrease the delay to make it faster (half of the original delay)
  }

  // Wait for 2 seconds before clearing the display
  delay(500);
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

  u8g2.setFont(u8g2_font_ncenB14_tr); // Choose a suitable font
  u8g2.drawStr(10, 24, "Command ");
  u8g2.drawStr(50,48,"Me");
  u8g2.sendBuffer();                  // Transfer internal memory to the display
  delay(2000);                        // Display for 1 second
 
   
  
  // Stop the loop
  while (true);
}
void stop(){
  digitalWrite(16, LOW);
  digitalWrite (18, LOW);
  digitalWrite(17,LOW);
  digitalWrite(19,LOW);
 

}
void forward(){
  digitalWrite(16, HIGH);
  digitalWrite (18, HIGH);
  digitalWrite(17,LOW);
  digitalWrite(19,LOW);
  for(int x=98;x<=295;x++){ // change speed
    analogWrite(speed1,x);
    analogWrite(speed2,x);
    Speedometer(x);
    delay(15);
  }

}
void right(){
  
  digitalWrite (18, LOW);
  digitalWrite (17, LOW);
  digitalWrite (16, HIGH);
  digitalWrite (19, HIGH);
 
  delay (2500);
  digitalWrite (16, LOW);
  digitalWrite (19, LOW);
}
void back(){
  digitalWrite(3,HIGH);
  digitalWrite(16, LOW);
  digitalWrite(18, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(19, HIGH);
  for(int y=98;y<=150;y++){// change the speed
    analogWrite(speed1,y);
    analogWrite(speed2,y);
    Speedometer(y);
    delay(30);
  }
}

void Speedometer(int speed) {
  u8g2.clearBuffer();
  
  // Draw the speedometer title
  u8g2.setFont(u8g2_font_ncenB08_tr); // Select font
  u8g2.drawStr(centerX - 20, 10, "Speed:");
  
  // Draw the speed value
  u8g2.setFont(u8g2_font_ncenB18_tr); // Select font for larger text
  u8g2.setCursor(centerX - 30, centerY + 10); // Move the value a little lower
  u8g2.print(speed); // Print the speed value
  
  // Draw "km/h" label
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(centerX + 20, centerY + 10); // Move "km/h" label a little lower
  u8g2.print("km/h");

  u8g2.sendBuffer();
}


