#pragma once

#include "Particle.h"
#include "neopixel.h"

#define PIXEL_PIN   D8
#define PIXEL_COUNT 60
#define PIXEL_TYPE  WS2812B

void initLEDs(void);
void changeColor(uint32_t c);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);