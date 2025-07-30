#include <Arduino.h>
#include <U8g2lib.h>

// Initialize the display (ensure to use the correct constructor for your display)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}

void loop() {
  // Draw the loading line gauge
  for (int i = 0; i <= 128; i += 8) {
    u8g2.clearBuffer(); // Clear the internal memory
    u8g2.drawBox(0, 30, i, 4); // Draw a filled box as the loading line
    u8g2.sendBuffer(); // Transfer internal memory to the display
    delay(125); // Delay for 0.125 seconds to create a 2-second animation
  }

  // Wait for 2 seconds before clearing the display
  delay(2000);
  u8g2.clearBuffer(); // Clear the display
  u8g2.sendBuffer();
  
  // Stop the loop
  while (true);
}
