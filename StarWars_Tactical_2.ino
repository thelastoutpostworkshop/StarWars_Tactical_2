#include <TFT_eSPI.h>
#include "DisplayPrototyping.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
serialDisplay sDisplay(&tft);

#define COLOR_TACTICAL_DARK_BLUE 0xff
#define COLOR_TACTICAL_DARK_LIGHTBLUE 0x34dd

#define BOTTOM_ZONE 90

struct PixelData
{
    int32_t x, y;
    uint16_t color;
};

PixelData pixels[5000]; // Array to store the pixel data

void setup()
{
    Serial.begin(115200);
    randomSeed(analogRead(0));

    tft.init();
    tft.setRotation(1);

    tft.fillScreen(0x0);
    drawMainGrid();
    drawLargeObjects();
    drawScanLine(8, 75, 0, 90, TFT_WHITE);
    tft.fillScreen(TFT_WHITE);
    Serial.println(tft.readPixel(20, 5));
    // moveScanLine(8, 75, 100, 0, 90, TFT_WHITE, 10);
}

void moveScanLine(uint32_t sideLength, uint32_t startX, uint32_t endX, uint32_t yPos1, uint32_t yPos2, uint16_t color, int delayTime)
{
    int numStoredPixels;
    uint32_t xPos = startX;

    while (xPos != endX)
    {
        // Save the pixel data before drawing the scan line
        numStoredPixels = 0;
        for (uint32_t x = xPos - sideLength; x <= xPos + sideLength; x++)
        {
            for (uint32_t y = yPos1; y <= yPos2; y++)
            {
                pixels[numStoredPixels].x = x;
                pixels[numStoredPixels].y = y;
                pixels[numStoredPixels].color = tft.readPixel(x, y);
                numStoredPixels++;
            }
        }

        // Draw the scan line at the current position
        drawScanLine(sideLength, xPos, yPos1, yPos2, color);
        delay(delayTime); // Delay for smooth movement

        // Restore the pixel data at the current position
        for (int i = 0; i < numStoredPixels; i++)
        {
            tft.drawPixel(pixels[i].x, pixels[i].y, pixels[i].color);
        }

        // Update the x position
        if (startX < endX)
        {
            xPos++;
        }
        else
        {
            xPos--;
        }
    }

    // Draw the scan line at the final position
    drawScanLine(sideLength, xPos, yPos1, yPos2, color);
}

void drawScanLine(uint32_t sideLength, uint32_t xPos, uint32_t yPos1, uint32_t yPos2, uint16_t color)
{
    // Calculate half the base and height of the triangles
    uint32_t halfBase = sideLength / 2;
    uint32_t height = sqrt(sideLength * sideLength - halfBase * halfBase);

    // First triangle pointing up
    tft.fillTriangle(xPos, yPos1 + height, xPos + halfBase, yPos1, xPos - halfBase, yPos1, color);

    // Second triangle pointing down
    tft.fillTriangle(xPos, yPos2 - height, xPos + halfBase, yPos2, xPos - halfBase, yPos2, color);

    // Draw a line joining the tips of both triangles
    tft.drawLine(xPos, yPos1 + height, xPos, yPos2 - height, color);
}

void drawLargeObjects(void)
{
    int current_x = 5;
    int current_y = 10;
    uint32_t color;
    int object_width, object_height;
    int max_height = 0;
    while (current_y < BOTTOM_ZONE - 10)
    {
        if (random(3) == 0)
        {
            color = ((random(2)) == 0) ? COLOR_TACTICAL_DARK_BLUE : COLOR_TACTICAL_DARK_LIGHTBLUE;
            object_width = ((random(2)) == 0) ? 10 : 17;
            if (random(4) == 0)
            {
                object_height = ((random(2)) == 0) ? 4 : 8;
            }
            else
            {
                object_height = 4;
            }
            if (object_height > max_height)
            {
                max_height = object_height;
            }
            tft.fillRect(current_x, current_y, object_width, object_height, color);
        }
        current_x += (object_width + 5 + random(10));
        if (current_x >= tft.width())
        {
            current_x = 5;
            current_y += (max_height + random(7));
            max_height = 0;
        }
    }
}

void drawMainGrid()
{
    int start = 15;
    int toggle = 1;
    int mini;
    tft.drawFastHLine(0, BOTTOM_ZONE - 5, tft.width(), COLOR_TACTICAL_DARK_BLUE);
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