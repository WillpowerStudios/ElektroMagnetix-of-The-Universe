#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, PIN, NEO_GRB + NEO_KHZ800);
int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    float alpha = incomingByte / 5.0f;
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255 * alpha, 255 * alpha, 255 * alpha));
    }
  } else {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  strip.show();
}

// Please share your updates if you've made cool changes ^_^ 
