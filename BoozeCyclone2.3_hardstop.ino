   // Starting from "buttoncycler" example program from Neopixel library

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connectedt o the button.  This will be
// driven with a pull-up resistor so the switch should
// pull the pin to ground momentarily.  On a high -> low
// transition the button press logic will execute.

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 90

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_RGB + NEO_KHZ800);

bool mode = true;
int function; //1 is cyclone, 2 is stopped
bool strandnow = HIGH;
bool oldstrand = LOW;
void cyclone();
void stopped();
void roulette();
int i = 0;
int j = 0;
int k = 1;
int rouletteDelay = 0;
bool direction = true;
double speed = 0.75;

bool oldState = LOW;

boolean modeState;
int buttonState;

int led;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  bool newState = digitalRead(BUTTON_PIN);
  if (newState == HIGH && oldState == LOW) {
    delay((int)(20 / speed));
    newState = digitalRead(BUTTON_PIN);
    if (newState == HIGH){
    mode = !mode;
    }
  }
    else if (mode == true) {
      k = 0;
      cyclone();
    }
    else if (mode == false) {
      stopped();
    }
    oldState = newState;
  }

const int colors[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0},
    {255, 0, 255}, {0, 255, 255}};

int red(int idx) { return colors[idx % (sizeof(colors) / sizeof(colors[0]))][0]; }
int green(int idx) { return colors[idx % (sizeof(colors) / sizeof(colors[0]))][1]; }
int blue(int idx) { return colors[idx % (sizeof(colors) / sizeof(colors[0]))][2]; }

  void stopped() {
    static const int X = 16;
    j++;
    j %= 100;
    if (j % 100 >= 70 ) {
      strip.setPixelColor(led, red(led), green(led), blue(led));
    } else {
      strip.setPixelColor(led, 0, 0, 0);
    }
    delay(5);
    strip.show();
  }


  void cyclone() {
    strip.setPixelColor(i, 0, 0, 0);
    if (rand() % 500 == 0)
      direction ^= true;
    if (direction) i = (i + 1) % strip.numPixels();
    else i = (i == 0) ? (strip.numPixels() - 1) : (i - 1);
    strip.setPixelColor(i, red(i), green(i), blue(i));
    strip.show();
    delay(rand() % (int)(10 / speed));
     /*if (i%20 > 7) {
      delay(5);
     }*/
    /*if (i == (strip.numPixels())) {
      i = 0;
    }*/
    led = i;
  }

  void roulette() {
    if (k < rouletteDelay){
    i++;
    k = k+20;
    strip.setPixelColor(i, 255, 0, 0);
    strip.setPixelColor(i - 1, 0);
    strip.show();
    delay(k);
    led = i;
    if (i == (strip.numPixels())) {
      i = 0;
    }
    }
    if (k >= rouletteDelay){
      for (int i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0,0,0);
      }
      strip.setPixelColor(led, 0, 255, 0);
      strip.show();   
    }
  }



  /*
    void loop() {
    // Get current button state.
    bool newState = digitalRead(BUTTON_PIN);
    // Check if state changed from high to low (button press).
    if (newState == HIGH && oldState == LOW) {
      // Short delay to debounce button.
      delay(20);
      // Check if button is still low after debounce.
      newState = digitalRead(BUTTON_PIN);
      Serial.println(newState);
      delay(1);
      if (newState == HIGH && strandon == false) {
         digitalWrite(LED_BUILTIN, HIGH);
         strandon = true;
         for(uint16_t i=0; (i<=(strip.numPixels())); i++) {
          strip.setPixelColor(i, 255, 0, 0);
          strip.setPixelColor(i-1, 0);
          strip.show();
          delay(50);
            if (i == (strip.numPixels())){
              i = 0;
              }
         }
      }
      if (newState == HIGH && strandon == true){
        for(uint16_t i=0; (i<=(strip.numPixels())); i++) {
          strip.setPixelColor(i, 0, 0, 255);
          strip.show();
      }
    }
    }
    }
  */
  /*if (i==(strip.numPixels())-1) {
    newState == LOW;
    for(uint16_t (strip.numPixels()); (i>0)&& strandon == false; i--) {
    strip.setPixelColor(i, 0, 255, 0);
    strip.setPixelColor(i+1, 0);
    strip.show();
    delay(50);
    newState = digitalRead(BUTTON_PIN);
    if (newState == HIGH){
    break;
    }
    }
    }
  */
