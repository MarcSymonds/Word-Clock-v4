#include <Adafruit_NeoPixel.h>
#include <BCDUtil.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <DS1307.h>
#include <EEPROM.h>

#include "Global.h"
#include "DisplayValues.h"
#include "DisplayTime.h"
#include "ChangeSettings.h"
#include "DirectIO.h"

byte lastReadSecond = 99;
DisplayMode displayMode;

unsigned long currMillis;
boolean timeReset; // millis has rolled over since last read. Happens ~49.7 days.

void setup() {
  //Serial.begin(115200);
  analogReference(DEFAULT);
  
  leds.begin();
  
  Wire.begin(); // Needed for DS1307 RTC.
  tempSens.begin();
  tempSens.setResolution(10); // Don't need highest resolution for temperature sensor. Higher resolution = slower reading.
  
  rtc.changeControl(true, 0); // Enable SQWE, and set rate to 1Hz. Used for flashing LED.
  rtc.changeClockHalt(false); // Set the clock running (if not already).
  rtc.change24Hour(true); // Switch to 24 hour mode (if not already). If change occurs, the hours may change.
  
  rtc.readTime();

  // Use the current time as a seed for the random number generator.

  randomSeed(((long) rtc.getSeconds()) + (((long) rtc.getMinutes()) << 8) + (((long) rtc.getHours()) << 16));
  
  loadSettings();
}

void loop()
{
  static boolean modeInit = true;
  unsigned long time;  
  boolean refreshDisplay = false;
  boolean settingChanged = false;
  static byte changedSetting = 0;
  static unsigned long changeSettingTime = 0;
  
  (void) random(0, 255);

  time = currMillis;
  currMillis = millis();
  timeReset = (currMillis < time);
  
  readTimeAndButtons();
  
  if (buttons.readButton(BUT_SETTING))
  {
    if (changeSettings())
    {
      saveSettings();
      modeInit = true;
      refreshDisplay = true;
    }
    
    changedSetting = 0;
  }
  else
  {
    if (buttons.readButton(BUT_MODE))
    {
      switch(displayMode)
      {
        case DM_WORDS:
          displayMode = DM_HM;
          break;
        
        case DM_HM:
          displayMode = DM_MS;
          break;
          
        case DM_MS:
          displayMode = DM_TEMP;
          break;
          
        case DM_TEMP:
          displayMode = DM_TEST;
          break;
          
        default:
          displayMode = DM_WORDS;
          break;
      }
      
      saveSettings();

      modeInit = true;
      refreshDisplay = true;
      
      changedSetting = 0;
    }
    else if (buttons.readButton(BUT_BRIGHTNESS))
    {
      if (brightness > 100)
        brightness = 100;
      else if (brightness <= 1)
        brightness = 255;  // Auto brightness
      else if (brightness <= 5)
        brightness = 1;
      else
        brightness -= 5;
        
      saveSettings();
      setBackgroundTempColour();
      refreshDisplay = true;
      
      changedSetting = 1;
      settingChanged = true;
    }
    else if (buttons.readButton(BUT_ADJUST))
    {
      switch(colourMode)
      {
        case CM_SINGLE_USER:
          if (singleColourWhite)
            singleColourWhite = false;
          else
            colourMode = CM_RANDOM;
          break;
          
        case CM_RANDOM:
          colourMode = CM_SINGLE_RANDOM_FADE;
          break;
          
        case CM_SINGLE_RANDOM_FADE:
          colourMode = CM_RANDOM_FADE;
          break;
          
        default:
          colourMode = CM_SINGLE_USER;
          singleColourWhite = true;
          break;
      }
      
      saveSettings();
      
      modeInit = true;
      refreshDisplay = true;
      
      changedSetting = 2;
      settingChanged = true;
    }
    
    if (settingChanged)
    {
      saveColourRef();
      
      changeSettingTime = currMillis;

      colours[4].setColour(128, 0, 128, false);
      colours[4].brightness = 100;
  
      colours[5].setColour(192, 128, 64, false);
      colours[5].brightness = 100;
      
      clearColourRef(true, true, true);
      
      if (changedSetting == 1)
      {
        displayThing(DV_SET_Br, 0, 4);
        
        if (brightness == 255)
          displayThing(DV_AUTO, 55, 5);
        else
          displayNumber(brightness, 55, 5);
      }
      else if (changedSetting == 2)
      {
        displayThing(DV_SET_Co, 0, 4);
        
        unsigned short t;
        switch(colourMode)
        {
          case CM_SINGLE_USER:
            if (singleColourWhite)
              t = DV_COLOUR_MODE_WHITE;
            else
              t = DV_COLOUR_MODE_SINGLE_USER;
            break;
          
          case CM_RANDOM:
            t = DV_COLOUR_MODE_RANDOM;
            break;
          
          case CM_SINGLE_RANDOM_FADE:
            t = DV_COLOUR_MODE_SINGLE_RANDOM_FADE;
            break;
          
          default:
            t = DV_COLOUR_MODE_RANDOM_FADE;
            break;
        }
        
        displayThing(t, 55, 5);
      }
      else
        changedSetting = 0;
        
      updateDisplay();
    }
  
    if (changedSetting > 0)
    {
      if (timeSince(changeSettingTime) > 2000)
      {
        changedSetting = 0;
        refreshDisplay = true;

        restoreColourRef();
      }
    }
    
    if (changedSetting == 0)
    {
      if (performFades())
        refreshDisplay = true;
      
      switch(displayMode)
      {
        case DM_WORDS:
          displayWords(modeInit, refreshDisplay);
          break;
          
        case DM_HM:
        case DM_MS:
          displayHMS(modeInit, refreshDisplay);
          break;
          
        case DM_TEMP:
          displayTemp(modeInit, refreshDisplay);
          break;
          
        default:
          displayTest(modeInit, refreshDisplay);
          break;
      }
      
      modeInit = false;
    }
  }
  
  readLightAndTemp(false);
}

boolean performFades()
{
  static unsigned long brightnessAdjTime = 0;
  boolean colourChanged = false;
  Colour *c;
  int i;
  unsigned long newColour;
  unsigned long brightnessTime;
  unsigned long brightlevel;
  boolean brightnessAdj;
  
  if (timeReset)
    brightnessAdjTime = 0;

  brightnessTime = timeSince(brightnessAdjTime);
  brightnessAdj = (brightnessTime >= 200);
  
  brightlevel = (brightness == 255) ? llBrightness : brightness;
  
  for (i = 0; i < COLOURCTRLS; i++)
  {
    c = &colours[i];
      
    if (brightnessAdj)
    {
      if (c->brightness > brightlevel)
        --c->brightness;
      else if (c->brightness < brightlevel)
        ++c->brightness;
    }

    if (c->fader)
      c->fadeColour();
        
    newColour = c->getColour();
    if (newColour != c->prevColour)
    {
      colourChanged = true;
      c->prevColour = newColour;
    }
  }

  if (brightnessAdj)
    brightnessAdjTime = currMillis + 200;

  return colourChanged;
}

void readTimeAndButtons()
{
  buttons.scanButtons();
  rtc.readTime();
}

void readLightAndTemp(boolean forceLight)
{
  boolean secondPast = false;
  byte val;
  float temp;
  
  val = rtc.getSeconds(true);
  if (lastReadSecond != val)
  {
    secondPast = true;
    lastReadSecond = val;
  }

  if (forceLight || secondPast && (val % 10) == 0)
  {
    // Read light level and temp every 10 seconds. These calls are relatively slow.

    lightLevel = analogRead(0);
  
    #define LLB_MIN 30
    #define LLB_MAX 80
    llBrightness = (lightLevel / (1024 / (LLB_MAX - LLB_MIN))) + LLB_MIN;

    tempSens.requestTemperatures();

    temp = tempSens.getTempFByIndex(0);
    if (temp > -10.0)
      tempF = temp;
    
    temp = tempSens.getTempCByIndex(0);
    if (temp > -10.0)
      tempC = temp;
    
    setBackgroundTempColour();
  }
}

void setBackgroundTempColour()
{
  //float temp;
  short temp;
  
  temp = (short)tempSens.getTempCByIndex(0) / 5;

  if (temp < 0)
    temp = 0;
  else if (temp > 5)
    temp = 5;
  
  tempColourR = (byte)(temp * (brightness == 255 ? llBrightness : brightness) / 100);
  tempColourB = (byte)((5 - temp) * (brightness == 255 ? llBrightness : brightness) / 100);
  
  if (tempColourR == 0 && tempColourB == 0)
  {
    if (temp < 3)
      tempColourB = 1;
    else
      tempColourR = 1;
  }
}

/*float diff(float a, float b)
{
  if (a > b)
    return a - b;
  else
    return b - a;
}*/

// We will use the RAM of the DS1307 to save some of the settings if power is lost.

void saveSettings()
{
  byte buf[9];
  
  buf[0] = 0x55; // Header to indicate what is read back are the settings.
  buf[1] = displayMode;
  buf[2] = brightness;
  buf[3] = colourMode;
  buf[4] = singleColour;
  buf[5] = singleColourWhite ? 1 : 0;
  buf[6] = tempBackground ? 1 : 0;
  buf[7] = fadeSpeed;
  buf[8] = showTempF ? 1 : 0;
  
  rtc.writeData(DS1307_RAM, buf, 9);
}

void loadSettings()
{
  byte buf[9];
  
  rtc.readData(DS1307_RAM, buf, 9);

  if (buf[0] == 0x55)
  {
    displayMode = (DisplayMode)buf[1];
    brightness = buf[2];
    colourMode = (ColourMode)buf[3];
    singleColour = buf[4];
    singleColourWhite = (buf[5] != 0);
    tempBackground = (buf[6] != 0);
    fadeSpeed = (RandomMode) buf[7];
    showTempF = (buf[8] != 0);
  }
}

