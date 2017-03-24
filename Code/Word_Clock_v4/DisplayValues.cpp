#include <EEPROM.h>
#include "Global.h"
#include "DisplayValues.h"

byte digitsOffsets[] = {
  DV_DIGIT_0,
  DV_DIGIT_1,
  DV_DIGIT_2,
  DV_DIGIT_3,
  DV_DIGIT_4,
  DV_DIGIT_5,
  DV_DIGIT_6,
  DV_DIGIT_7,
  DV_DIGIT_8,
  DV_DIGIT_9
};

// Monday will use Mo from settings above.
unsigned short weekdaysOffsets[] = {
  DV_SET_Mo,
  DV_WD_Tu,
  DV_WD_We,
  DV_WD_Th,
  DV_WD_Fr,
  DV_WD_Sa,
  DV_WD_Su
};

unsigned short hourOffsets[] = {
  DV_WORDS_H_TWELVE,
  DV_WORDS_H_ONE,
  DV_WORDS_H_TWO,
  DV_WORDS_H_THREE,
  DV_WORDS_H_FOUR,
  DV_WORDS_H_FIVE,
  DV_WORDS_H_SIX,
  DV_WORDS_H_SEVEN,
  DV_WORDS_H_EIGHT,
  DV_WORDS_H_NINE,
  DV_WORDS_H_TEN,
  DV_WORDS_H_ELEVEN
};

unsigned short minutesOffsets[] = {
  DV_WORDS_M_FIVE,
  DV_WORDS_M_TEN,
  DV_WORDS_M_A_QUARTER,
  DV_WORDS_M_TWENTY,
  DV_WORDS_M_TWENTYFIVE,
  DV_WORDS_M_HALF
};

void displayWordMinutes(byte m, byte start, byte colourRef)
{
  displayThing(minutesOffsets[m], start, colourRef);
}

void displayWordHour(byte h, byte start, byte colourRef)
{
  displayThing(hourOffsets[h], start, colourRef);
}

void displayDigit(byte digit, byte start, byte colourRef)
{
  displayThing((unsigned short)digitsOffsets[digit], start, colourRef);
}

void displayNumber(byte number, byte start, byte colourRef)
{
  if (number >= 100)
    displayDigit(number / 100, start, colourRef);
    
  if (number >= 10)
    displayDigit((number / 10) % 10, start + 4, colourRef);
    
  displayDigit(number % 10, start + 8, colourRef);
}

void displayWeekday(byte wd, byte start, byte colourRef)
{
  displayThing(weekdaysOffsets[wd - 1], start, colourRef); // DS1307 stores weekday as 1-7.
}

void displayThing(unsigned short memRef, byte start, byte colourRef)
{
  byte data, count;
  
  data = EEPROM.read((int)memRef);

  while (data != 255)
  {
    if ((data & 0x80) == 0)
      setColourRef(start + data, colourRef);
    else
    {
      data = (data & 0x7F);
      ++memRef;
      count = EEPROM.read((int)memRef);
      while (count > 0)
      {
        setColourRef(start + data, colourRef);
        ++data;
        --count;
      }
    }
    
    ++memRef;
    data = EEPROM.read((int)memRef);
  }
}

