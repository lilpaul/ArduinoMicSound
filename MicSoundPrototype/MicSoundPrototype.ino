#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    10

CRGB leds[NUM_LEDS];

#define ANALOGMIC A0

float minVol;
float maxVol;

void setup() {
  // put your setup code here, to run once:
  minVol = 9000;
  maxVol = 0;
  Serial.begin (9600);
  pinMode(ANALOGMIC, INPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Raw;
  float Analog;
  Raw = analogRead (ANALOGMIC);
  Analog = Raw * (5.0 / 1023.0);
  if (Analog < minVol)
  {
    minVol = Analog;
  }
  if (Analog > maxVol)
  {
    maxVol = Analog;
  }
  float diff = maxVol - minVol;
  float increment = diff / 10;
  
  Serial.print ("Min: "); 
  Serial.print (minVol, 4);
  Serial.print (" Max: "); 
  Serial.print (maxVol, 4);
  Serial.print (" Raw: "); 
  Serial.print (Raw, 4);
  Serial.print (" Vol: "); 
  Serial.println (Analog, 4);

  for (int idx = 0; idx < 10; idx++)
  {
    if ((minVol + idx * increment) < Analog)
    {
      leds[idx] = CRGB(50, 70, 20);
    }
    else
    {
      leds[idx] = CRGB(0, 0, 0);
    }
  }  

  FastLED.show();
  //delay(10);
}
