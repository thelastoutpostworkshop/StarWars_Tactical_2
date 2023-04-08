#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

void setup() {
  // Initialize the display
  tft.init();
  tft.setRotation(1); // Set screen rotation

  // Fill the screen with a color
  tft.fillScreen(TFT_RED);
  tft.println("test");
}

void loop() {
  // You can add your code here to update the display
}