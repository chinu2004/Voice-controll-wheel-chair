#include <U8g2lib.h>
#include <Wire.h>
#include <math.h>

// Initialize the SH1106 display with I2C communication
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int angle = 0; // Angle for rotating the loading indicator
const int maxDotRadius = 4; // Maximum radius of the dots
const int minDotRadius = 2; // Minimum radius of the dots

unsigned long startTime; // Track the start time
enum State { LOADING, CHAIR_STARTED, READY } state; // Enum to manage states

void setup() {
  u8g2.begin();  // Initialize the display
  state = LOADING; // Start with the loading state
  startTime = millis(); // Initialize start time
}

void drawLoading() {
  int centerX = 64; // Center of the display
  int centerY = 32;
  int radius = 20; // Radius of the circular path for the dots

  // Draw a series of filled dots in a circular pattern
  for (int i = 0; i < 8; i++) { // Loop through all 8 dots
    int x = centerX + radius * cos((angle + i * 45) * PI / 180);
    int y = centerY + radius * sin((angle + i * 45) * PI / 180);

    // Calculate dot size based on position
    int dotSize = minDotRadius + (maxDotRadius - minDotRadius) * i / 7;
    u8g2.drawDisc(x, y, dotSize); // Draw a filled circle (disc) for each dot
  }

  // Increment the angle for the next frame
  angle = (angle + 20) % 360; // Increase the angle increment to make it faster
}

void loop() {
  u8g2.clearBuffer();  // Clear the internal buffer

  switch(state) {
    case LOADING:
      drawLoading();
      // Check if 2 seconds have passed
      if (millis() - startTime >= 2000) {
        state = CHAIR_STARTED;
        startTime = millis(); // Reset start time for next state
      }
      break;

    case CHAIR_STARTED:
      // Display "Chair is Started"
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 32, "Chair is Started");
      // Check if 1 second has passed
      if (millis() - startTime >= 1000) {
        state = READY;
        startTime = millis(); // Reset start time for next state
      }
      break;

    case READY:
      // Display "I am Ready!"
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 32, "I am Ready...");
      break;
  }
  // Draw the buffer to the display
  u8g2.sendBuffer();
  delay(50); // Small delay to avoid overwhelming the display update
}

