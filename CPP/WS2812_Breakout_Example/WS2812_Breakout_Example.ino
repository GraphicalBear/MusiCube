/* SparkFun WS2812 Breakout Board Example
  SparkFun Electronics
  date: July 25, 2013
  license: GNU GENERAL PUBLIC LICENSE
  
  Requires the Adafruit NeoPixel library. It's awesome, go get it.
  https://github.com/adafruit/Adafruit_NeoPixel
  
  This simple example code runs three sets of animations on a group of WS2812
  breakout boards. The more boards you link up, the better these animations
  will look. 
  
  For help linking WS2812 breakouts, checkout our hookup guide:
  https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide
  
  Before uploading the code, make sure you adjust the two defines at the
  top of this sketch: PIN and LED_COUNT. Pin should be the Arduino pin
  you've got connected to the first pixel's DIN pin. By default it's
  set to Arduino pin 4. LED_COUNT should be the number of breakout boards
  you have linked up.
*/
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 3
#define LED_COUNT 5

// Create an instance of the Adafruit_NeoPixel class called "leds".
// That'll be what we refer to from here on...
Adafruit_NeoPixel led_matrix = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);


void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    led_matrix.setPixelColor(i, 0);
  }
  led_matrix.show();
}

void lowOn() {
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 26, 122, 232);
  }
  led_matrix.show();
}

void beat()  {
   for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 0, 255, 255);
  }
  led_matrix.show();
  delay(850);
  clearLEDs();
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 230, 0, 255);
  }
  led_matrix.show();
  delay(180);
  clearLEDs();
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 0, 255, 60);
  }
  led_matrix.show();
  delay(950);
  clearLEDs();
  led_matrix.show();
}

void oppBeat() {
  led_matrix.setPixelColor(4, 255, 90, 233);
  led_matrix.setPixelColor(0, 0, 0, 255);
  led_matrix.setPixelColor(2, 0, 0, 255);
  led_matrix.show();
  delay(1005);
  clearLEDs();
  led_matrix.setPixelColor(4, 255, 90, 233);
  led_matrix.setPixelColor(1, 240, 120, 0);
  led_matrix.setPixelColor(3, 240, 120, 0);
  led_matrix.show();
  delay(1005);
  clearLEDs();
  led_matrix.show();
}

void fullBeat() {
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255, 174, 0);
  }
  led_matrix.show();
  delay(1030);
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 0, 0, 255);
  }
  led_matrix.show();
  delay(950);
  clearLEDs();
  led_matrix.show();
}

void pulse() {
  led_matrix.setPixelColor(4, 255, 255, 255);
  led_matrix.setPixelColor(0, 0, 0, 255);
  led_matrix.show();
  delay(250);
  clearLEDs();
  led_matrix.setPixelColor(4, 255, 255, 255);
  led_matrix.setPixelColor(1, 0, 0, 255);
  led_matrix.show();
  delay(250);
  clearLEDs();
  led_matrix.setPixelColor(4, 255, 255, 255);
  led_matrix.setPixelColor(2, 0, 0, 255);
  led_matrix.show();
  delay(250);
  clearLEDs();
  led_matrix.setPixelColor(4, 255, 255, 255);
  led_matrix.setPixelColor(3, 0, 0, 255);
  led_matrix.show();
  delay(250);
  clearLEDs();
  led_matrix.show();
}

void Still_Alive() {
  lowOn();
  delay(1000);
  for (int i = 0; i <= 29; i++) {
    pulse();
  }
  lowOn();
  delay(500);
  for (int i = 0; i <= 6; i++) {
    beat();
  }
  for (int i = 0; i <= 18; i++) {
    oppBeat();
  }
  for (int i = 0; i <= 10; i++) {
    fullBeat();
  }
  for (int i = 0; i <= 15; i++) {
    pulse();
  }
  for (int i = 0; i <= 7; i++) {
    oppBeat();
  }
  for (int i = 0; i <= 7; i++) {
    fullBeat();
  }
  for (int i = 0; i <= 20; i++) {
    pulse();
  }
  led_matrix.setPixelColor(4, 255, 255, 255);
  for (int i = 0; i < LED_COUNT - 1; i++) {
    led_matrix.setPixelColor(i, 255, 0, 0);
  }
  led_matrix.show();
  delay(3000);
  for (int i = 0; i < LED_COUNT - 1; i++) {
    led_matrix.setPixelColor(i, 0, 0, 0);
  }
  led_matrix.show();
  delay(10000);
  clearLEDs();
  led_matrix.show();
}

void QuarterNote(float pitch) {
  clearLEDs();
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255 * pitch, 0, 0);
  }
  led_matrix.show();
  delay(60);
  clearLEDs();
  led_matrix.show();
  delay(100);
}

void HalfNote(byte pitch) {
  clearLEDs();
  for (int i = 0; i < LED_COUNT; i++) {
    led_matrix.setPixelColor(i, 255 * pitch, 0, 0);
  }
  led_matrix.show();
  delay(60);
  clearLEDs();
  led_matrix.show();
  delay(260);
}

void QuarterRest() {
  clearLEDs();
  led_matrix.show();
  delay(160);
}

void HalfRest() {
  clearLEDs();
  led_matrix.show();
  delay(160);
}

void Mario_Overworld() {
  led_matrix.setPixelColor(0,244, 245,0);
  led_matrix.setPixelColor(1,244, 245,0);
  led_matrix.setPixelColor(2,244, 245,0);
  led_matrix.setPixelColor(3,244, 245,0);
  led_matrix.setPixelColor(4,255, 0,0);
  led_matrix.show();
  delay(81500);
  clearLEDs();
  
  
  
}

void setup()
{
  led_matrix.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  led_matrix.show();   // ...but the LEDs don't actually update until you call this.
}

void loop()
{
   Mario_Overworld();
  
//  // Ride the Rainbow Road
//  for (int i=0; i<LED_COUNT*10; i++)
//  {
//    rainbow(i);
//    delay(100);  // Delay between rainbow slides
//  }
//  
//  // Indigo cylon
//  // Do a cylon (larson scanner) cycle 10 times
//  for (int i=0; i<10; i++)
//  {
//    // cylon function: first param is color, second is time (in ms) between cycles
//    cylon(INDIGO, 500);  // Indigo cylon eye!
//  }
//  
//  // A light shower of spring green rain
//  // This will run the cascade from top->bottom 20 times
//  for (int i=0; i<20; i++)
//  {
//    // First parameter is the color, second is direction, third is ms between falls
//    cascade(MEDIUMSPRINGGREEN, TOP_DOWN, 100); 
//  }
}

// Implements a little larson "cylon" sanner.
// This'll run one full cycle, down one way and back the other


// Sets all LEDs to off, but DOES NOT update the display;
// call leds.show() to actually turn them off after this.

// Prints a rainbow on the ENTIRE LED strip.
//  The rainbow begins at a specified position. 
// ROY G BIV!


// Input a value 0 to 191 to get a color value.
// The colors are a transition red->yellow->green->aqua->blue->fuchsia->red...
//  Adapted from Wheel function in the Adafruit_NeoPixel library example sketch


