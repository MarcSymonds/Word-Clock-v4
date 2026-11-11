#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

#define BUT_DELAY_TIME 750
#define BUT_REPEAT_TIME 300
#define BUT_DEBOUNCE_TIME 75

enum ButtonIndex:byte
{
  BUT_MODE = 0,      // Cancel
  BUT_SETTING = 1,
  BUT_ADJUST = 2,    // Adjust forward
  BUT_BRIGHTNESS = 3 // Adjust back
};

#define BUT_MODE_PIN 8
#define BUT_SETTING_PIN 9
#define BUT_ADJUST_PIN 10
#define BUT_BRIGHTNESS_PIN 11

enum ButtonMode:byte
{
  UNPRESSED = 0,
  PRESSED = 1,
  //REPEATING = 2,
  //DEBOUNCE = 3,
  DEBOUNCING = 2
};

class Button
{
  public:
    long xx;
    byte pin;
    boolean state; // Is the button physically pressed.
    boolean pressed; // Current read state of the button.
    unsigned long nextRepeat; // Time when keypress will repeat.
    ButtonMode mode;
    unsigned long debounceTime;
    unsigned long pressedTime;
    int repeatDelay;
    
    Button();

    void determineButtonState();
};

class ButtonReader
{
  private:
    byte tonePin;
    
    Button buts[4];

  public:
    byte scanButtons();
    boolean readButton(ButtonIndex but);
    Button getButton(ButtonIndex but);
    
    ButtonReader(byte tonePin);
};

#endif
