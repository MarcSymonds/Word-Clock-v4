#ifndef DISPLAYVALUES_H
#define DISPLAYVALUES_H

#include "Global.h"

#define DV_DIGIT_0 0
#define DV_DIGIT_1 11
#define DV_DIGIT_2 19
#define DV_DIGIT_3 28
#define DV_DIGIT_4 37
#define DV_DIGIT_5 46
#define DV_DIGIT_6 55
#define DV_DIGIT_7 65
#define DV_DIGIT_8 72
#define DV_DIGIT_9 83

#define DV_SET_Hr 93
#define DV_SET_Mi 109
#define DV_SET_Wd 127
#define DV_SET_Dy 149
#define DV_SET_Mo 166
#define DV_SET_Yr 188
#define DV_SET_Bt 201
#define DV_SET_Co 217
#define DV_SET_Fa 233
#define DV_SET_Tf 250

#define DV_SMALL_C 263
#define DV_SMALL_F 270
#define DV_HYPHEN 277

#define DV_WD_Tu 280
#define DV_WD_We 295
#define DV_WD_Th 317
#define DV_WD_Fr 331
#define DV_WD_Sa 344
#define DV_WD_Su 361

#define DV_WORDS_ITIS 378
#define DV_WORDS_M_FIVE 383
#define DV_WORDS_M_TEN 386
#define DV_WORDS_M_A_QUARTER 389
#define DV_WORDS_M_TWENTY 393
#define DV_WORDS_M_TWENTYFIVE 396
#define DV_WORDS_M_HALF 399
#define DV_WORDS_H_PAST 402
#define DV_WORDS_H_TO 405
#define DV_WORDS_H_TWELVE 408
#define DV_WORDS_H_ONE 411
#define DV_WORDS_H_TWO 414
#define DV_WORDS_H_THREE 417
#define DV_WORDS_H_FOUR 420
#define DV_WORDS_H_FIVE 423
#define DV_WORDS_H_SIX 426
#define DV_WORDS_H_SEVEN 429
#define DV_WORDS_H_EIGHT 432
#define DV_WORDS_H_NINE 435
#define DV_WORDS_H_TEN 438
#define DV_WORDS_H_ELEVEN 441
#define DV_WORDS_H_OCLOCK 444

#define DV_SET_Br 447
#define DV_AUTO 463

#define DV_COLOUR_MODE_WHITE 488
#define DV_COLOUR_MODE_SINGLE_USER 510
#define DV_COLOUR_MODE_RANDOM 529
#define DV_COLOUR_MODE_SINGLE_RANDOM_FADE 548
#define DV_COLOUR_MODE_RANDOM_FADE 567

void displayDigit(byte, byte, byte);
void displayNumber(byte, byte, byte);
void displayWeekday(byte, byte, byte);
void displayWordHour(byte h, byte start, byte colourRef);
void displayWordMinutes(byte m, byte start, byte colourRef);

void displayThing(unsigned short, byte, byte);

#endif
