#include <TFT_eSPI.h>
#include "DisplayPrototyping.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
serialDisplay sDisplay(&tft);

#define COLOR_TACTICAL_DARK_BLUE 0xff
#define COLOR_TACTICAL_DARK_LIGHTBLUE 0x3eff

void setup()
{
    Serial.begin(115200);
    // Initialize the display
    tft.init();
    tft.setRotation(1); // Set screen rotation

    // Fill the screen with a color
    tft.fillScreen(0x0);
    tft.setTextColor(0x3eff);
    tft.fillRect(10, 10, 20, 4, 0x3eff);
    tft.setTextColor(0xff);
    tft.fillRect(10, 70, 40, 4, 0xff);
    drawMainGrid();
}

void drawMainGrid()
{
    tft.drawFastHLine(0, 85, 128, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastVLine(15, 0, 90, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastVLine(55, 0, 90, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastVLine(95, 0, 90, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastHLine(0, 5, 128, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastHLine(15, 90, 5, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastHLine(55, 90, 5, COLOR_TACTICAL_DARK_BLUE);
    tft.drawFastHLine(95, 90, 5, COLOR_TACTICAL_DARK_BLUE);
}

void loop()
{
    sDisplay.readCommandsFromSerial();
}