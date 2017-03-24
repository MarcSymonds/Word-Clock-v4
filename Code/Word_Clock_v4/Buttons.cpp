#include "DirectIO.h"
#include "Buttons.h"

Button::Button()
{
  state = false;
  pressed = false;
  mode = UNPRESSED;
  nextRepeat = 0;
}

ButtonReader::ButtonReader(byte t)
{
  tonePin = t;
  
  buts[BUT_MODE].pin = BUT_MODE_PIN;
  buts[BUT_SETTING].pin = BUT_SETTING_PIN;
  buts[BUT_ADJUST].pin = BUT_ADJUST_PIN;
  buts[BUT_BRIGHTNESS].pin = BUT_BRIGHTNESS_PIN;
  
  for (int i = 0; i < 4; i++)
  {
    buts[i].xx = 100 + i;
    pinMode(buts[i].pin, INPUT);
  }
  
  pinMode(tonePin, OUTPUT);
}
    
byte ButtonReader::scanButtons()
{
  byte i;
  Button *b;
  unsigned long t = millis();

  for (i = 0; i < 4; i++)
  {  
    b = &buts[i];
    if (digitalRead(b->pin) == HIGH)
    {
      if (b->mode == UNPRESSED)
      {
        b->mode = FIRSTPRESS;
        b->state = true;
        b->pressed = true;
        b->nextRepeat = t + BUT_DELAY_TIME;
      }
      else if (b->mode == DEBOUNCE)
      {
        b->mode = REPEATING;
        b->nextRepeat = t + BUT_REPEAT_TIME;
      }
      else if (t >= b->nextRepeat)
      {
        b->mode = REPEATING;
        b->nextRepeat = t + BUT_REPEAT_TIME;
        b->pressed = true; // Reset pressed flag.
      }
//    else
//      Delay until next key press.
    }
    else if (b->mode == FIRSTPRESS || b->mode == REPEATING)
    {
      b->mode = DEBOUNCE;
      b->nextRepeat = t + BUT_DEBOUNCE_TIME;
    }
    else if (b->mode == DEBOUNCE && t >= b->nextRepeat)
    {
      b->mode = UNPRESSED;
      b->pressed = false;
      b->state = false;
    }
  }
}

// Destructive read of the button state.

boolean ButtonReader::readButton(ButtonIndex but)
{
  Button *b = &buts[but];
  boolean p;
  
  p = b->pressed;
  b->pressed = false;

  if (p && tonePin <= 13)
    tone(tonePin, 100, 25);

  return p;
}

Button ButtonReader::getButton(ButtonIndex but)
{
  return buts[but];
}

