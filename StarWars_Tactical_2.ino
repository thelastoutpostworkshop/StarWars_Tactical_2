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
    tft.fillScreen(0xffff);
    tft.setTextColor(0x3eff);
    tft.fillRect(10, 10, 20, 4, 0x3eff);
    tft.setTextColor(0x3eff);
    tft.fillRect(10, 80, 40, 4, 0x3eff);
    tft.drawFastHLine(10, 85, 200, 0x3eff);
}

void loop()
{
    sDisplay.readCommandsFromSerial();
}