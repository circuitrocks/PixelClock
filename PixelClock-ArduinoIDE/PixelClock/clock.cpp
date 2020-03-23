#include "main.h"
#include "chars.h"

NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt6Ws2812xMethod> strip(256, 19);

uint8_t colorSaturation = 16;

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

int8_t evenCorr[4] = {4, 12, 22, 30};
int8_t oddCorr[4] = {28, 20, 10, 2};
uint16_t pixelStart[4] = {128, 132, 137, 141};

Ticker colonTicker;

boolean colonVisible = false;

void initClock(void)
{
  strip.Begin();
  strip.Show();
  colonTicker.attach(0.5, setColon);
}

void updateClock(void)
{
  strip.Show();
}

void setNumber(uint8_t value, uint8_t digit)
{
  uint8_t *arrPtr;
  if ((digit == 0) && (value == 0))
  {
    arrPtr = blank;
  }
  else
  {
    arrPtr = number[value];
  }

  uint8_t pixel = pixelStart[digit];
  int16_t evenCorrVal = evenCorr[digit];
  int16_t oddCorrVal = oddCorr[digit];

  for (uint8_t row = 0; row < 9; row++)
  {
    for (uint8_t col = 0; col < 3; col++)
    {
      if (arrPtr[(row * 3) + col] == 1)
      {
        strip.SetPixelColor(pixel, green);
      }
      else
      {
        strip.SetPixelColor(pixel, black);
      }
      if (row % 2 == 0)
      {
        pixel++;
      }
      else
      {
        pixel--;
      }
    }
    if (row % 2 == 0)
    {
      pixel -= evenCorrVal;
    }
    else
    {
      pixel -= oddCorrVal;
    }
  }
}

void setDay(uint8_t value)
{
  uint8_t *day = daysOfWeek[value];
  for (int pixel = 160; pixel < 256; pixel++)
  {
    if (day[pixel - 160] == 1)
    {
      strip.SetPixelColor(pixel, blue);
    }
    else
    {
      strip.SetPixelColor(pixel, black);
    }
  }
}

void setColon(void)
{
  RgbColor colonColor = black;
  if (colonVisible)
  {
    colonColor = red;
  }
  colonVisible = !colonVisible;

  strip.SetPixelColor(39, colonColor);
  strip.SetPixelColor(40, colonColor);
  strip.SetPixelColor(55, colonColor);
  strip.SetPixelColor(56, colonColor);
  strip.SetPixelColor(87, colonColor);
  strip.SetPixelColor(88, colonColor);
  strip.SetPixelColor(103, colonColor);
  strip.SetPixelColor(104, colonColor);
  strip.Show();
}

void setBrightness(uint8_t newBrightness)
{
  colorSaturation = newBrightness;
  red = RgbColor(colorSaturation, 0, 0);
  green = RgbColor(0, colorSaturation, 0);
  blue = RgbColor(0, 0, colorSaturation);
  white = RgbColor(colorSaturation);
}
