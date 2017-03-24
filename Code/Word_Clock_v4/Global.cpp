#include <Arduino.h>
#include "Global.h"

Adafruit_NeoPixel leds = Adafruit_NeoPixel(110, 4, NEO_GRB + NEO_KHZ800);
Colour colours[COLOURCTRLS];
ColourMode colourMode = CM_SINGLE_USER;
byte singleColour = 0;
boolean singleColourWhite = true;
ButtonReader buttons = ButtonReader(13); // Tone.
OneWire oneWire(5);
DallasTemperature tempSens = DallasTemperature(&oneWire);
float tempC, tempF;
byte tempColourR;
byte tempColourB;
boolean tempBackground = true;
boolean showTempF = true;
DS1307 rtc;
RandomMode fadeSpeed = RM_MEDIUM;

byte ledColourRef[55]; // Use 4 bits per pixel to save a bit of mem.
byte ledColourRefSave[55];
boolean ledColourRefSaved = false;

byte brightness = 255; // 255 = Auto, else 100-0.

unsigned int lightLevel;
byte llBrightness = 80;

void clearColourRef(boolean top, boolean bottom, boolean noTemp)
{
  byte s, c, r;
  
  if (top && bottom)
  {
    s = 0;
    c = 110;
  }
  else
  {
    s = (top ? 0 : 55);
    c = 55;
  }
  
  r = (!noTemp && tempBackground ? 14 : 15); // 14 = temperature background, 15 = blank.
  
  while (c > 0)
  { 
    setColourRef(s, r);
    --c;
    ++s;
  }
}

byte getColourRef(byte i)
{
  if (i & 1)
    return(ledColourRef[i / 2] >> 4);
  else
    return ledColourRef[i / 2] & 0x0F;
}

void setColourRef(byte i, byte r)
{
  byte j = i / 2;
  byte t = ledColourRef[j];
  
  if (i & 1)
    ledColourRef[j] = (t & 0x0F) | ((r & 0x0F) << 4);
  else
    ledColourRef[j] = (t & 0xF0) | (r & 0x0F);
}

void saveColourRef()
{
  if (!ledColourRefSaved)
  {
    for (byte i = 0; i < 55; i++)
      ledColourRefSave[i] = ledColourRef[i];
    
    ledColourRefSaved = true;
  }
}

void restoreColourRef()
{
  if (ledColourRefSaved)
  {
    for (byte i = 0; i < 55; i++)
      ledColourRef[i] = ledColourRefSave[i];
      
    ledColourRefSaved = false;
  }
}  

void updateDisplay()
{
  byte r;
  int i;
  
  for (i = 0; i < 110; i++)
  {
    r = getColourRef(i);
    if (r == 15)
      leds.setPixelColor(i, 0, 0, 0);
    else if (r == 14)
      leds.setPixelColor(i, tempColourR, 0, tempColourB);
    else if (r < COLOURCTRLS)
      leds.setPixelColor(i, colours[r].getColour());
  }
  leds.show();
}

unsigned long timeSince(unsigned long time)
{
  if (timeReset)
    return (unsigned long)0xFFFFFFFF - time + currMillis;
  else
    return currMillis - time;
};

void setupColour(byte i, boolean dim)
{
  Colour *c;
  
  c = &colours[i];
  
  switch(colourMode)
  {
    case CM_SINGLE_USER:
      if (singleColourWhite)
        c->setColour(255, 255, 255, dim);
      else
        c->setColour(colourWheel(singleColour, false), dim);
      break;
      
    case CM_RANDOM:
      c->setColour(colourWheel(random(0, 256), false), dim);
      break;
      
    case CM_SINGLE_RANDOM_FADE:
    case CM_RANDOM_FADE:
      c->setRandomFadeDestination(fadeSpeed, true, dim);
      break;
  }
}
