#include "Global.h"
#include "Colour.h"

//void xxx(ColourBit *, char *);
//char *toHex(unsigned long);

void ColourBit::setRandomFadeColour(boolean primary, CB_STEPSTYPE steps)
{
  (void)random(0, 200);
  (void)random(0, 200);
  // At least one of the colours (RGB) will be picked as a primary and will be set to a high luminosity., so the pixel isn't too dim.
  dcolour = ((CB_TYPE) random((primary ? 160 : 0), 256)) << CB_ADJUST;

  calculateAdjust(steps);
}

void ColourBit::setFadeColour(byte colour, CB_STEPSTYPE steps)
{
  dcolour = ((CB_TYPE) colour) << CB_ADJUST;
  calculateAdjust(steps);
}

boolean ColourBit::fadeColourBit(boolean last)
{
  boolean adj = false;
  CB_TYPE orig = wcolour >> CB_ADJUST;

  if (last)
    wcolour = dcolour;
  else
    wcolour += acolour;
  
  if ((wcolour >> CB_ADJUST) != orig)
    adj = true;

  return adj;
}

void ColourBit::calculateAdjust(CB_STEPSTYPE s)
{
  if (s == 0 || wcolour == dcolour)
    acolour = 0;
  else
  {
    if (dcolour > wcolour)
      acolour = (dcolour - wcolour) / s;
    else
      acolour = ~((wcolour - dcolour) / s);
  }
}

void ColourBit::setColour(byte c)
{
  wcolour = (unsigned long) c << CB_ADJUST;
  dcolour = wcolour;
  acolour = 0;
}

byte ColourBit::getColour()
{
  return (byte)(wcolour >> CB_ADJUST);
}

void Colour::setRandomFadeDestination(RandomMode rmode, boolean autoR, boolean d)
{
  randomMode = rmode;
  
  setRandomSteps();

  byte p = random(1, 8);
  
  red.setRandomFadeColour(((p & 1) == 1), steps);
  green.setRandomFadeColour(((p & 2) == 2), steps);
  blue.setRandomFadeColour(((p & 4) == 4), steps);
  
  autoRestart = autoR;
  
  fader = true;
  dim = d;
}

void Colour::setRandomSteps()
{
  switch(randomMode)
  {
    case RM_FAST:
      steps = random(75, 125);
      stepDelayTime = random(5, 15);
      break;
      
    case RM_MEDIUM:
      steps = random(200, 350);
      stepDelayTime = random(20, 40);
      break;
      
    default:
      steps = random(350, 600);
      stepDelayTime = random(50, 150);
      break;
  }
}

void Colour::setFadeDestination(byte r, byte g, byte b, CB_STEPSTYPE steps, unsigned short stepDelay, boolean autoR, RandomMode rmode)
{
  this->steps = steps;
  stepDelayTime = stepDelay;
  
  randomMode = rmode;
  
  red.setFadeColour(r, steps);
  green.setFadeColour(g, steps);
  blue.setFadeColour(b, steps);

  autoRestart = autoR;
  
  fader = true;
  dim = false;
  
  nextFadeTime = currMillis;
}

boolean Colour::fadeColour()
{
  boolean adj = false;
  boolean last;
 
  if (steps > 0)
  {
    if (timeReset)
      nextFadeTime = 0;
  
    if (currMillis >= nextFadeTime)
    {
      last = (steps == 1);
      
      if (red.fadeColourBit(last))
        adj = true;
    
      if (green.fadeColourBit(last))
        adj = true;
    
      if (blue.fadeColourBit(last))
        adj = true;
        
      --steps;
      nextFadeTime = currMillis + stepDelayTime;
    }
  }
  
  if (steps == 0 && autoRestart)
    setRandomFadeDestination(randomMode, autoRestart, dim);

  return adj;
}

boolean Colour::stillFading()
{
  return (fader == true && steps > 0);
}

byte Colour::getRed()
{
  return getDisplayColour(red.wcolour);//(byte)(((red.wcolour / 100) * brightness) >> CB_ADJUST);
}

byte Colour::getGreen()
{
  return getDisplayColour(green.wcolour);//(byte)(((green.wcolour / 100) * brightness) >> CB_ADJUST);
}

byte Colour::getBlue()
{
  return getDisplayColour(blue.wcolour);//(byte)(((blue.wcolour / 100) * brightness) >> CB_ADJUST);
}

byte Colour::getDisplayColour(unsigned long c)
{
  boolean h = ((c & 0xFF000000) > 0);
  byte d;
  
  c = (c / 100) * brightness;
  if (dim)
    c = c / 10 * 4;
    
  d = (byte)(c >> CB_ADJUST);
  if (d == 0 && h)
    d = 1;
  
  return d;
}

unsigned long Colour::getColour()
{
  return (((unsigned long)getRed()) << 16) + (((unsigned long)getGreen()) << 8) + ((unsigned long)getBlue());
}

void Colour::setColour(byte r, byte g, byte b, boolean d)
{
  red.setColour(r);
  green.setColour(g);
  blue.setColour(b);

  dim = d;
  fader = false;
  steps = 0;
}

void Colour::setColour(unsigned long c, boolean d)
{
  byte r, g, b;
  r = (byte)(c >> 16);
  g = (byte)((c >> 8) & 0xFF);
  b = (byte)(c & 0xFF);
  
  setColour(r, g, b, d);
}

void Colour::copyColourFrom(Colour *c)
{
  red.setColour(c->red.getColour());
  green.setColour(c->green.getColour());
  blue.setColour(c->blue.getColour());
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// If the whole display was lit at full brightness, then it would draw ~2A, so the low parameter lowers the colour brightness so less power is drawn.
unsigned long colourWheel(byte WheelPos, boolean low)
{
  byte r, b, g;

  if(WheelPos < 85)
  {
    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
  }
  else if(WheelPos < 170)
  {
    WheelPos -= 85;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  }
  else
  {
    WheelPos -= 170;
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
  }
  
  if (low)
  {
    r /= 3;
    g /= 3;
    b /= 3;
  }
  
  return ((unsigned long) r << 16) | ((unsigned long) g <<  8) | (unsigned long) b;
}

