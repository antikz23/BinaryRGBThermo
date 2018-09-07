#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            6

#define NUMPIXELS      8
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int i;
void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");

  if (!tempsensor.begin()) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
}

void loop() {


#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin();

  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t");
  Serial.print(f); Serial.println("*F");
  if (f >= 90)
  {
    for (int x = 0; x < NUMPIXELS; x++)
    {
      if (bitRead((int)f, x) == true)
      {
        pixels.setPixelColor(x, pixels.Color(255, 0, 0)); // Moderately bright green color.

        pixels.show();
      }
      if (bitRead((int)f, x) == false)
      {
        pixels.setPixelColor(x, pixels.Color(0, 0, 0)); // Moderately bright green color.

        pixels.show();
      }
    }
  }

  if (f < 90 && f > 80)
  {
    for (int x = 0; x < NUMPIXELS; x++)
    {
      if (bitRead((int)f, x) == true)
      {
        pixels.setPixelColor(x, pixels.Color(255, 255, 255)); // Moderately bright green color.

        pixels.show();
      }
      if (bitRead((int)f, x) == false)

      {
        pixels.setPixelColor(x, pixels.Color(0, 0, 0)); // Moderately bright green color.

        pixels.show();
      }
    }
  }

  if (f <= 80)
  {
    for (int x = 0; x < NUMPIXELS; x++)
    {
      if (bitRead((int)f, x) == true)
      {
        pixels.setPixelColor(x, pixels.Color(0, 0, 255)); // Moderately bright green color.

        pixels.show();
      }
      if (bitRead((int)f, x) == false)
      {
        pixels.setPixelColor(x, pixels.Color(0, 0, 0)); // Moderately bright green color.

        pixels.show();
      }
    }
  }



  delay(1000);
}
