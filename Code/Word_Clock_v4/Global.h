#ifndef GLOBAL_H
#define GLOBAL_H

#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DS1307.h>
#include <DallasTemperature.h>
#include "Colour.h"
#include "Buttons.h"

#define COLOURCTRLS 6

void clearColourRef(boolean top, boolean bottom, boolean noTemp);
byte getColourRef(byte i);
void setColourRef(byte i, byte r);
void saveColourRef();
void restoreColourRef();

unsigned long timeSince(unsigned long);
void setupColour(byte i, boolean dim);
void updateDisplay();
void saveSettings();
void readTimeAndButtons();
void readLightAndTemp(boolean);

enum DisplayMode:byte
{
  DM_WORDS = 0,
  DM_HM = 1,
  DM_MS = 2,
  DM_TEMP = 3,
  DM_TEST = 4
};

enum Settings:byte
{
  SET_HOUR = 0,
  SET_MINUTE = 1,
  SET_WEEKDAY = 2,
  SET_DAY = 3,
  SET_MONTH = 4,
  SET_YEAR = 5,
  SET_COLOURMODE = 6,
  SET_COLOURMODESETTING = 7,
  SET_BRIGHTNESS = 8
};

enum ColourMode:byte
{
  CM_SINGLE_USER = 0,
  CM_RANDOM = 1,
  CM_SINGLE_RANDOM_FADE = 2,
  CM_RANDOM_FADE = 3
};

extern Adafruit_NeoPixel leds;               // Object for writing to the LEDs.
extern DisplayMode displayMode;
extern Colour colours[];                     // Objects for displaying items in colour.
extern ColourMode colourMode;                // Which display mode is being used.
extern byte singleColour;                    // Wheel index indicating which colour to use when in single colour mode.
extern boolean singleColourWhite;            // Indicates if plain white is to be used for the display.
extern byte ledColourRef[];                  // Array of nibbles used to identify which colour element to display for each letter in the display.
extern DS1307 rtc;                           // Object to read and write the RTC.
extern DallasTemperature tempSens;           // Object to read the temperature sensor.
extern float tempC, tempF;
extern byte tempColourR;             // Colour representing the temperature.
extern byte tempColourB;
extern boolean tempBackground;               // Set no assigned pixels to a value representing the temperature.
extern boolean showTempF;
extern ButtonReader buttons;                 // Object to read the buttons.
extern boolean forceUpdate;                  // Force an update of the display. Normall only update when a change occurs.
extern unsigned int lightLevel;              // Current light level read from LDR.
extern byte llBrightness;                    // Brightness level % based on lightLevel. Check readLightAndTemp function in Word_Clock_v4.ini. 15%-80%.
extern byte brightness;                      // Manual brightness level. If 255, then uses llBrightness.
extern RandomMode fadeSpeed;

extern unsigned long currMillis;             // Current millis value. Read at the start of loop().
extern boolean timeReset;                    // Inidcates millis has rolled over since last time read.

#endif

