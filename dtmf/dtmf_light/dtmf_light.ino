#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    5    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 60
#define PIN_DTMF_STD 9
#define PINS_DTMF_DATA PINB
#define PINS_DTMF_DATA_LSB 2

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);



void setup()
{
  strip.begin();
  strip.setBrightness(64);
  strip.show(); // Initialize all pixels to 'off'
}



void loop()
{
  uint8_t dtmfValue, dtmfState;
  static uint8_t dtmfState_old = LOW;
  uint16_t value;

  dtmfState = digitalRead(PIN_DTMF_STD);
  if( (dtmfState == HIGH) && (dtmfState_old == LOW) )
  {
    dtmfValue = PINS_DTMF_DATA;
    dtmfValue = dtmfValue >> PINS_DTMF_DATA_LSB;

    switch(dtmfValue)
    {
       case 0:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       strip.show();
       break;

       case 1:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 0; i < 3; i++) 
       {
         strip.setPixelColor(i, strip.Color(0xFF, 0, 0));
       }
       strip.show();
       break;

       case 2:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 3; i < 6; i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0xFF, 0));
       }
       strip.show();
       break;

       case 4:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 6; i < 9; i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0xFF));
       }
       strip.show();
       break;

       case 8:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 9; i < 12; i++) 
       {
         strip.setPixelColor(i, strip.Color(0xFF, 0, 0xFF));
       }
       strip.show();
       break;

       case 0xF:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 0; i < 12; i++) 
       {
         strip.setPixelColor(i, strip.Color(0xFF, 0xFF, 0xFF));
       }
       strip.show();
       break;

       case 3:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 0; i < 6; i++) 
       {
         strip.setPixelColor(i, strip.Color(0xFF, 0xFF, 0));
       }
       strip.show();
       break;

       case 0xC:
       for (uint16_t i = 0; i < strip.numPixels(); i++) 
       {
         strip.setPixelColor(i, strip.Color(0, 0, 0));
       }
       for (uint16_t i = 6; i < 12; i++) 
       {
         strip.setPixelColor(i, strip.Color(0xFF, 0xFF, 0));
       }
       strip.show();
       break;
    }
    
    if(dtmfValue >= 10)
    {
      dtmfValue = 0;
    }
    value = DisplayValue;
    value = ((uint32_t)value * 10) % 10000;
    value += dtmfValue;
    DisplayValue = value;
  }
  dtmfState_old = dtmfState;
  
}
