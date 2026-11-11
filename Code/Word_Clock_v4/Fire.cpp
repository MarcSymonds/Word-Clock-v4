/* This is based on the Fire2012 sketch in the FastLED example. */

#include "Global.h"
#include "Fire.h"

HeatColumn::HeatColumn() {
  for (int i = 0; i < 10; i++)
    heat[i] = 0;
}

HeatColumn::animate(Fire *fire) {
  for (int i = 0 ; i < 10; i++) {
    int h = (int)heat[i] - random(0, ((fire->cooling * 10) / 10) + 2);

    if (h < 0) 
      h = 0;

    heat[i] = h;
  }

  for (int i = 9; i >= 2; i--) 
    heat[i] = (heat[i - 1] + heat[i - 2] + heat[i - 2]) / 4;

  if (random(0, 255) > fire->sparking) {
    int y = random(0, 4);
    int h = (int)heat[y] + random(160, 255);

    if (h > 255) 
      h = 255;

    heat[y] = h;
  }

  if (heat[0] == 0) 
    heat[0] = random(1, 255);
}

Fire::Fire() {
  cooling = 55;
  sparking = 120;

  lastFrameTime = 0;

  for (int i = 0; i < 11; i++) 
    heatColumn[i] = HeatColumn();
}

bool Fire::timeForFrame() {
  return millisPassed(lastFrameTime) > 60;
}

Fire::animate() {
  for (int i = 0; i < 11; i++) 
    heatColumn[i].animate(this);

  lastFrameTime = millis();
}

Fire::display() {
  int idx = 0;
  unsigned long colour = colours[0].getColour();
  unsigned long r = colours[0].getRed();
  unsigned long g = colours[0].getGreen();
  unsigned long b = colours[0].getBlue();

  for (int i = 0; i < 110; i++) 
    leds.setPixelColor(i, 0);

  for (int c = 0; c < 11; c++) {
    for (int h = 0; h < 10; h++) {
      uint8_t heat = heatColumn[c].heat[h];

      unsigned long cr = r * heat / 255;
      unsigned long cg = g * heat / 255;
      unsigned long cb = b * heat / 255;

      idx = ((9 - h) * 11) + c;

      leds.setPixelColor(idx, ((cr & 0xff) << 16 ) + ((cg & 0xff) << 8) + (cb & 0xff));
    }
  }

  leds.show();
}
