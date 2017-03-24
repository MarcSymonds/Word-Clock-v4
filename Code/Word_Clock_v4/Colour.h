#ifndef COLOUR_H
#define COLOUR_H

#include <Arduino.h>

#define CB_TYPE unsigned long
#define CB_STEPSTYPE unsigned short
#define CB_ADJUST  24

enum RandomMode:byte
{
  RM_FAST = 0,
  RM_MEDIUM = 1,
  RM_SLOW = 2
};

unsigned long colourWheel(byte, boolean);

class ColourBit
{
  public:
    CB_TYPE wcolour, dcolour, acolour;

    void setRandomFadeColour(boolean primary, CB_STEPSTYPE steps);
    void setFadeColour(byte colour, CB_STEPSTYPE steps);
    boolean fadeColourBit(boolean last);

    void setColour(byte c);
    byte getColour();
    
  private:
    void calculateAdjust(CB_STEPSTYPE steps);
};

class Colour
{
  public:
    ColourBit red, green, blue;
    byte brightness = 100; // 0-100%
    byte prevBrightness = 100;
    CB_STEPSTYPE steps;
    unsigned short stepDelayTime;
    boolean fader = false;
    boolean autoRestart = true;
    boolean dim = false;
    RandomMode randomMode = RM_SLOW;
    
    unsigned long nextFadeTime = 0;

    unsigned long prevColour = 0;

//    void setRandomFadeDestination(CB_STEPSTYPE steps, unsigned short stepDelay, boolean auto = true);
    void setRandomFadeDestination(RandomMode rmode, boolean automatic = true, boolean dim = false);
    void setFadeDestination(byte r, byte g, byte b, CB_STEPSTYPE steps, unsigned short stepDelay, boolean automatic = true, RandomMode rmode = RM_MEDIUM);
    boolean fadeColour();
    boolean stillFading();
    void setColour(byte r, byte g, byte b, boolean dim);
    void setColour(unsigned long c, boolean dim);
    
    byte getRed();
    byte getGreen();
    byte getBlue();
    byte getDisplayColour(unsigned long);
    unsigned long getColour();
    
    void copyColourFrom(Colour *);
    
  private:
    void setRandomSteps();
};

#endif

