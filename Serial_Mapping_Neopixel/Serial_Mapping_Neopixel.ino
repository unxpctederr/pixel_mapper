// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>

#define NUM_STRIPS 2
#define NUM_LEDS_PER_STRIP 200
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 10
  FastLED.addLeds<NEOPIXEL, 10>(leds[0], NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 11
  FastLED.addLeds<NEOPIXEL, 9>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(10);
  
  Serial.begin(9600);

}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.parseInt();

    if(incomingByte == -1){
      FastLED.clear();
      FastLED.show();
    }else if(incomingByte == -2){
      fill_solid(leds[0], NUM_LEDS_PER_STRIP, CRGB::White);
      fill_solid(leds[1], NUM_LEDS_PER_STRIP, CRGB::White);
      FastLED.show();
    } else {
      FastLED.clear();
      FastLED.setBrightness(10);
      int ledStrip = incomingByte % NUM_LEDS_PER_STRIP;
      int index = incomingByte - (ledStrip * NUM_LEDS_PER_STRIP);

      leds[ledStrip][index] = CRGB::White;
      FastLED.show();
      FastLED.setBrightness(10);
    }
  }
}
