#include <Arduino.h>
#include "Global.h"
#include "ChangeSettings.h"
#include "DisplayValues.h"

byte changeValue(byte, unsigned short, byte, byte, byte);
byte changeWeekday(byte);
byte changeColour(byte);

boolean changeSettings()
{
  byte val, orig;
  boolean cancelled = false;
  boolean timeChanged = false;
  boolean dateChanged = false;
  boolean settingsChanged = false;
  boolean changes = false;
  
  colours[4].setColour(255, 255, 0, false);
  colours[4].brightness = 100;
  
  colours[5].setColour(0, 255, 255, false);
  colours[5].brightness = 100;
  
  orig = rtc.getHours(true);
  val = changeValue(0, DV_SET_Hr, orig, 0, 23);
  if (val == 255)
    cancelled = true;
  else if (orig != val)
  {
    rtc.setHours(val, true);
    timeChanged = true;
  }
  
  if (!cancelled)
  {
    orig = rtc.getMinutes(true);
    val = changeValue(0, DV_SET_Mi, orig, 0, 59);
    if (val == 255)
      cancelled = true;
    else
    {
      if (orig != val)
      {
        rtc.setMinutes(val, true);
        timeChanged = true;
      }
      
      if (timeChanged)
      {
        rtc.setSeconds(0, true);
        rtc.writeTimePart();
        
        changes = true;
      }
    }    
  }
  
  if (!cancelled)
  {
    orig = rtc.getWeekday();
    val = changeValue(1, DV_SET_Wd, orig, 1, 7);
    if (val == 255)
      cancelled = true;
    else if (val != orig)
    {
      rtc.setWeekday(val);
      dateChanged = true;
    }
  }
  
  if (!cancelled)
  {
    orig = rtc.getDay(true);
    val = changeValue(0, DV_SET_Dy, orig, 1, 31);
    if (val == 255)
      cancelled = true;
    else if (val != orig)
    {
      rtc.setDay(val, true);
      dateChanged = true;
    }
  }
  
  if (!cancelled)
  {
    orig = rtc.getMonth(true);
    val = changeValue(0, DV_SET_Mo, orig, 1, 12);
    if (val == 255)
      cancelled = true;
    else if (val != orig)
    {
      rtc.setMonth(val, true);
      dateChanged = true;
    }
  }
  
  if (!cancelled)
  {
    orig = rtc.getYear(true);
    val = changeValue(0, DV_SET_Yr, orig, 0, 99);
    if (val == 255)
      cancelled = true;
    else
    {
      if (val != orig)
      {
        rtc.setYear(val, true);
        dateChanged = true;
      }
      
      if (dateChanged)
      {
        rtc.writeDatePart();
        changes = true;
      }
    }
  }
  
  if (!cancelled)
  {
    orig = (tempBackground ? 1 : 0);
    val = changeValue(0, DV_SET_Bt, orig, 0, 1);
    if (val == 255)
      cancelled = true;
    else if (val != orig)
    {
      tempBackground = (val == 1);
      settingsChanged = true;
      changes = true;
    }
  }
  
  if (!cancelled)
  {
    orig = (showTempF ? 1 : 0);
    val = changeValue(0, DV_SET_Tf, orig, 0, 1);
    if (val == 255)
      cancelled = true;
    else if (val != orig)
    {
      showTempF = (val == 1);
      settingsChanged = true;
      changes = true;
    }
  }
  
  if (!cancelled)
  {
    clearColourRef(true, true, true);
    updateDisplay();
    
    orig = singleColour;
    val = changeValue(2, DV_SET_Co, orig, 0, 254);
    if (val == 255)
      cancelled = true;
    else
    {
      if (val != orig)
      {
        singleColour = val;
        settingsChanged = true;
        changes = true;
      }
    }
  }
  
  if (!cancelled)
  {
    orig = (byte)fadeSpeed;
    val = changeValue(0, DV_SET_Fa, orig, 0, 2);
    if (val == 255)
      cancelled = true;
    else if (val != orig)
    {
      fadeSpeed = (RandomMode) val;
      settingsChanged = true;
      changes = true;
    }
  }

  if (settingsChanged) 
    saveSettings();

  if (!cancelled)
  {
    do
    {
      readLightAndTemp(true);
      buttons.scanButtons();
      
      clearColourRef(true, true, true);
      displayNumber(llBrightness, 0, 0);
      displayNumber((byte)(lightLevel / 4), 55, 1);
      updateDisplay();
    } while (buttons.readButton(BUT_MODE) == false && buttons.readButton(BUT_SETTING) == false);
  }
  
  return changes;
}

byte changeValue(byte type, unsigned short headMemRef, byte num, byte low, byte high)
{
  boolean done = false;
  boolean chg = false;
  boolean sd = (high < 10);
  unsigned long c;

  clearColourRef(true, false, true);
  displayThing(headMemRef, 0, 4);
  updateDisplay();

  while (!done)
  {
    clearColourRef(false, true, true);
    switch(type)
    {
      case 0:
        if (!sd)
          displayDigit(num / 10, 57, 5);
        displayDigit(num % 10, 61, 5);
        updateDisplay();
        break;
        
      case 1:
        displayWeekday(num, 56, 5);
        updateDisplay();
        break;
        
      case 2:
        c = colourWheel(num, false);
        leds.setPixelColor(81, c);
        leds.setPixelColor(82, c);
        leds.setPixelColor(83, c);
        leds.setPixelColor(92, c);
        leds.setPixelColor(93, c);
        leds.setPixelColor(94, c);
        leds.show();
    }
    
    chg = false;
    while (!done && !chg)
    {
      buttons.scanButtons();
      
      if (buttons.readButton(BUT_MODE))  // Cancel
      {
        num = 255;
        done = true;
      }
      else if (buttons.readButton(BUT_SETTING))  // Accept
        done = true;
      else if (buttons.readButton(BUT_ADJUST))    // Adjust up
      {
        if (num >= high)
          num = low;
        else
          num++;
          
        chg = true;
      }
      else if (buttons.readButton(BUT_BRIGHTNESS))    // Adjust down
      {
        if (num <= low)
          num = high;
        else
          --num;
          
        chg = true;
      }
    }
  }
  
  return num;
}

