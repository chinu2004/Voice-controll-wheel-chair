#include <U8g2lib.h>
#include <Wire.h>

// Initialize the SH1106 display with I2C communication
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Initial position and size for the triangle
int triangleX; // Current X position of the triangle
int triangleY; // Y position of the triangle (center of the display)
int triangleSize = 20; // Size of the triangle

// Speed of the triangle's rightward movement
int moveSpeed = 4;

void setup() {
  u8g2.begin(); // Initialize the display
  triangleX = 64; // Start the triangle from the horizontal center of the display
  triangleY = 32; // Start the triangle from the vertical center of the display
}

void drawRightTriangle(int x, int y, int size) {
  int halfSize = size / 2;

  // Draw the right-pointing triangle
  u8g2.drawTriangle(
    x + halfSize, y,            // Right vertex
    x, y - halfSize,            // Top vertex
    x, y + halfSize             // Bottom vertex
  );
}

void loop() {
  u8g2.clearBuffer(); // Clear the internal buffer

  // Draw the right-pointing triangle at the current position
  drawRightTriangle(triangleX, triangleY, triangleSize);

  // Update the position to move the triangle rightward
  triangleX += moveSpeed;

  // If the triangle moves off the right edge of the screen, reset to the center
  if (triangleX > 128 + triangleSize) {
    triangleX = 64; // Reset to the horizontal center of the display
  }

  // Draw the buffer to the display
  u8g2.sendBuffer();

  delay(20); // Delay to control the speed of the movement
}
