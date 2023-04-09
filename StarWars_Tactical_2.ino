#include <TFT_eSPI.h>
#include "DisplayPrototyping.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
serialDisplay sDisplay(&tft);

#define COLOR_TACTICAL_DARK_BLUE 0xff
#define COLOR_TACTICAL_DARK_LIGHTBLUE 0x3eff

#define BOTTOM_ZONE 90
#define LARGE_OBJECT_X_SPACING 20
#define LARGE_OBJECT_Y_SPACING 30

void setup()
{
    Serial.begin(115200);

    tft.init();
    tft.setRotation(1); 

    tft.fillScreen(0x0);
    drawMainGrid();
    drawLargeObjects();
}

void drawLargeObjects(void)
{
    int current_x = 5;
    int current_y =10;
    while (current_x < tft.width())
    {
        tft.fillRect(current_x, 70, 40, 4, COLOR_TACTICAL_DARK_BLUE);
        current_x += LARGE_OBJECT_X_SPACING;
        current_y += LARGE_OBJECT_Y_SPACING;
        if (current_y >= BOTTOM_ZONE)
        {
            current_y = 10;
        }
        
    }
}

void drawMainGrid()
{
    int start = 15;
    int toggle = 1;
    int mini;
    tft.drawFastHLine(0, BOTTOM_ZONE-5, tft.width(), COLOR_TACTICAL_DARK_BLUE);
    for (int i = 0; i < 3; i++)
    {
        tft.drawFastVLine(start, 0, BOTTOM_ZONE, COLOR_TACTICAL_DARK_BLUE);
        if (toggle == -1)
        {
            mini = start - 5;
        }
        else
        {
            mini = start;
        }
        tft.drawFastHLine(mini, BOTTOM_ZONE, 5, COLOR_TACTICAL_DARK_BLUE);
        tft.drawFastHLine(mini, 0, 5, COLOR_TACTICAL_DARK_BLUE);

        start += 40;
        toggle *= -1;
    }
    tft.drawFastHLine(0, 5, tft.width(), COLOR_TACTICAL_DARK_BLUE);

    // tft.drawFastVLine(55, 0, 90, COLOR_TACTICAL_DARK_BLUE);
    // tft.drawFastVLine(95, 0, 90, COLOR_TACTICAL_DARK_BLUE);
    // tft.drawFastHLine(55, 90, 5, COLOR_TACTICAL_DARK_BLUE);
    // tft.drawFastHLine(95, 90, 5, COLOR_TACTICAL_DARK_BLUE);
}

void loop()
{
    sDisplay.readCommandsFromSerial();
}