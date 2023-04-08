#include <TFT_eSPI.h>
#include "DisplayPrototyping.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
serialDisplay sDisplay(&tft);

void setup()
{
    Serial.begin(115200);
    // Initialize the display
    tft.init();
    tft.setRotation(1); // Set screen rotation

    // Fill the screen with a color
    tft.fillScreen(TFT_RED);
    tft.println("test");
}

void loop()
{
    sDisplay.readCommandsFromSerial();
}