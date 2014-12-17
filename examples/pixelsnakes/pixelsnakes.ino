// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

#define BRIGHTNESS 1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
int colors[2];
int colorswitch = 0;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

// starting points of the snakes
float pixelsnake1[] = { 0, 1, 2, 3, 4 };
float pixelsnake2[] = { 8, 9, 10, 11, 12};

void rotatesnake(float snake[5], boolean forwards, float spd) {
  if(forwards) {
    for(int i=0;i<5;i++){
      if((snake[i]+spd) >= 16) {
        snake[i] = ((snake[i] - 16) + spd);
      } else {
        snake[i] = (snake[i] + spd);
      }
    }
  } else {
    for(int i=0;i<5;i++){
      if((snake[i]-spd) < 0) {
        snake[i] = 16 - abs(snake[i] - spd);
      } else {
        snake[i] = (snake[i] - spd);
      }
    }
  }
}

// return color of led pixel based on the snake
void snakecolor(float snake1[5], float snake2[5], int index) {
  int calc1 = 0;
  int calc2 = 0;
  for(int i=0; i<5; i++) {
    if(int(snake1[i]) == index) {
      calc1 = BRIGHTNESS * (i+1); 
    }
    if(int(snake2[i]) == index) {
      calc2 = BRIGHTNESS * (i+1);
    }
  }
  colors[0] = calc1;
  colors[1] = calc2; 
}

void loop() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<NUMPIXELS;i++){
    snakecolor(pixelsnake1, pixelsnake2, i);
    if(colorswitch == 0) {
      pixels.setPixelColor(i, pixels.Color(colors[1], 0, colors[0]));
    } else if(colorswitch == 1) {
      pixels.setPixelColor(i, pixels.Color(0, colors[1], colors[0]));
    } else if(colorswitch == 2) { 
      pixels.setPixelColor(i, pixels.Color(colors[1], colors[0], 0));
    } else if(colorswitch == 3) {
      pixels.setPixelColor(i, pixels.Color(0, colors[1], colors[1] + colors[0]));
    }
    pixels.show();
  }
  delay(delayval); // Delay for a period of time (in milliseconds).
  rotatesnake(pixelsnake1, true, 0.3);
  rotatesnake(pixelsnake2, true, 0.2);
}
