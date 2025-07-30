#include <Arduino.h>
#include <U8g2lib.h>
String state;

// Initialize the display (ensure you use the correct constructor for your display)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  
  state="chinu";
  u8g2.begin();
}
void loop(){

  if (state=="chinu"){
    cal();
     
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

 // Clear the display
  u8g2.clearBuffer();
  u8g2.sendBuffer();
   
  
  // Stop the loop
  while (true);
}
