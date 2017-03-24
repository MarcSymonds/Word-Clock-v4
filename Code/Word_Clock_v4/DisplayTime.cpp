#include <Arduino.h>
#include "Global.h"
#include "DisplayTime.h"
#include "DisplayValues.h"

void displayWords(boolean init, boolean force)
{
  static byte lastM = 99;
  byte h, m, f;
  
  m = rtc.getMinutes(true);
  
  f = m + 2;
  if (f > 59)
    f -= 60;
  
  f /= 5;
  
  if (lastM != m || init || force)
  {
    lastM = m;
    
    if (init)
    {
      setupColour(0, false);
      setupColour(1, false);
      setupColour(2, false);
      setupColour(3, false);
    }
    
    clearColourRef(true, true, false);

    displayThing(DV_WORDS_ITIS, 0, 0);
    h = rtc.getHours(true);

    if (f == 0)
      displayThing(DV_WORDS_H_OCLOCK, 0, 1);
    else
    {
      if (f > 6)
      {
        displayWordMinutes(11 - f, 0, 1);
        displayThing(DV_WORDS_H_TO, 0, 2);
      }
      else
      {
        displayWordMinutes(f - 1, 0, 1);
        displayThing(DV_WORDS_H_PAST, 0, 2);
      }
    }

    if ( h > 11)
      h -= 12;
    
    if (m > 32)
    {
      ++h;
      if (h > 11)
        h -= 12;
    }
    
    displayWordHour(h, 0, 3);    

    updateDisplay();
  }
}

void displayHMS(boolean init, boolean force)
{
  static byte lastValue = 99;
  byte s, mcr;
  //boolean needUpdate = false;
  
  if (displayMode == DM_HM)
    s = rtc.getMinutes(false);
  else
    s = rtc.getSeconds(false);
      
  if (init || force || s != lastValue)
  {
    lastValue = s;
    mcr = ((colourMode == CM_SINGLE_USER || colourMode == CM_SINGLE_RANDOM_FADE) ? 1 : 0);
    
    if (init)
    {
      setupColour(0, false);
      if (mcr == 0)
        setupColour(1, false);
      else
      {
        colours[1].fader = false;
        colours[1].dim = true;
      }
    }
    
    if (mcr == 1)
      colours[1].copyColourFrom(&colours[0]);//setColour(colours[0].getColour(), false);
      
    clearColourRef(true, true, false);

    displayDigit((s >> 4), 58, 0);
    displayDigit((s & 0x0F), 62, 0);
    
    if (displayMode == DM_HM)
      s = rtc.getHours(false);
    else
      s = rtc.getMinutes(false);

    displayDigit((s >> 4), 2, 1);
    displayDigit((s & 0x0F), 6, 1);
    
    updateDisplay();
  }
}

void displayTemp(boolean init, boolean force)
{
  static short lastValue = 99;
  short t, v, y;
  boolean neg = false;

  if (showTempF)
    t = (short)(tempF * 10);
  else
    t = (short)(tempC * 10);
    
  if (t != lastValue || init || force)
  {
    lastValue = t;

    if (init)
    {
      setupColour(0, false);
      setupColour(1, true);
    }
    
    y = t;
    if ( y < 0)
    {
      y = -y;
      neg = true;
    }
    
    clearColourRef(true, true, false);

    if ( y >= 1000) // 100 degrees + 
    {
      displayDigit(y / 1000, 0, 0);
      displayDigit((y / 100) % 10, 4, 0);
      displayDigit((y / 10) % 10, 8, 0);
    }
    else
    {
      v = y / 100;
      if (v > 0)
        displayDigit(v, 0, 0);
        
      v = (y / 10) % 10;
      displayDigit(v, 4, 0);
      
      v = y % 10;
      displayDigit(v, 8, 1);
    }
    
    if (neg)
      displayThing(DV_HYPHEN, 77, 1);
      
    displayThing((showTempF ? DV_SMALL_F : DV_SMALL_C), 74, 0);
    
    updateDisplay();
  }
}

void displayTest(boolean init, boolean force)
{
  int i;
  static unsigned long changeTime = 0;
  
  if (init || timeSince(changeTime) >= 10000)
  {
    for (i = 0; i < COLOURCTRLS; i++)
      colours[i].setRandomFadeDestination(RM_FAST, true, true);

    for (i = 0; i < 110; i++)
      setColourRef(i, (byte)random(0, COLOURCTRLS));
      
    changeTime = currMillis;
    
    init = true;
  }

  if (init || force)
    updateDisplay();
}

void rainbow(unsigned short j)
{
  unsigned short i;
 
  for(i = 0; i < leds.numPixels(); i++)
    leds.setPixelColor(i, colourWheel(((i * 256 / leds.numPixels()) + j) & 255, true));
}
