
#define LEDPIN 38

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, LEDPIN, NEO_GRB);


void LED_setup(){
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}