#pragma once
#include "define.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_NeoPixel pixels(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
