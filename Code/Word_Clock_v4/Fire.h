/* This is based on the Fire2012 sketch in the FastLED example. */

#ifndef Fire_h
#define Fire_h

#include "Arduino.h"

class Fire;

class HeatColumn {
  public:
    // 10 is the height of the display.
    //
    uint8_t heat[10];

    HeatColumn();

    animate(Fire*);
};

class Fire {
  public:
    int cooling;
    int sparking;

    unsigned long lastFrameTime;

    // 11 is the number of columns in the display.
    //
    HeatColumn heatColumn[11];

    Fire();

    animate();
    display();
    bool timeForFrame();
};
#endif
