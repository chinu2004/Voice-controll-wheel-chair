#include <U8g2lib.h>

// Initialize the U8g2 library for SH1106
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

int speedMax = 15; // Maximum speed in km/h
const int centerX = 64;  // Center X position for the display
const int centerY = 40;  // Center Y position for the display

void drawSpeedometer(int speed) {
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

void setup() {
  u8g2.begin();
}

void loop() {
  // Example speed value, replace this with actual sensor data
  int speed = (millis() / 1000) % (speedMax + 1); // Simulate speed value between 0 and 15 km/h
  drawSpeedometer(speed);
  delay(100); // Update speed value every 100 milliseconds
}
