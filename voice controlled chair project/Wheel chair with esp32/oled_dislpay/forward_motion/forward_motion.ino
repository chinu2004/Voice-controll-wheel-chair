#include <U8g2lib.h>
#include <Wire.h>

// Initialize the SH1106 display with I2C communication
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Initial position and size for the triangle
int triangleX = 64; // Center X position of the display
int triangleY; // Current Y position of the triangle
int triangleSize = 20; // Size of the triangle

// Speed of the triangle's upward movement
int moveSpeed = 2;

void setup() {
  u8g2.begin(); // Initialize the display
  triangleY = 32; // Start the triangle from the center point
}

void drawUpwardTriangle(int x, int y, int size) {
  int halfSize = size / 2;

  // Draw the upward-pointing triangle
  u8g2.drawTriangle(
    x, y - halfSize,            // Top vertex
    x - halfSize, y + halfSize,  // Bottom left vertex
    x + halfSize, y + halfSize   // Bottom right vertex
  );
}

void loop() {
  u8g2.clearBuffer(); // Clear the internal buffer

  // Draw the upward-pointing triangle at the current position
  drawUpwardTriangle(triangleX, triangleY, triangleSize);

  // Update the position to move the triangle upward
  triangleY -= moveSpeed;

  // If the triangle moves off the top of the screen, reset to the center
  if (triangleY < 0 - triangleSize) {
    triangleY = 32; // Reset to the center of the display
  }

  // Draw the buffer to the display
  u8g2.sendBuffer();

  delay(30); // Delay to control the speed of the movement
}
