#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 6
#define LED_COUNT 50
#define BRIGHTNESS 20

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t colors[13] = {0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff};

uint32_t ledIndexColors[8] = {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};
int state;

int counter = 0;

int timer = 0;

void cont(){
  rv = true;
  for(int i = 0; i < 7; i++){
   if(ledIndexColors[i] != 0x000000){
    return true;
   }
  }
 
 return false;
}

void bop(int ind, uint32_t c){
  ledIndexColors[ind - 1] = c;
  
}

void updateLEDs(){
  for(int i = 0; i < 8; i++){

    //define R from hex to RGB as variable
    byte r = ledIndexColors[i] >> 16;
    
    //define G from hex to RGB as variable
    byte g = (ledIndexColors[i] & 0x00ff00) >> 8;
    //define B from hex to RGB as variable
    byte b = (ledIndexColors[i] & 0x0000ff);

    if(r > 0){
      ledIndexColors[i] -= 0x010000;
    }

    if(g > 0){
      ledIndexColors[i] -= 0x000100;
    }

    if(b > 0){
      ledIndexColors[i] -= 0x000001;
    } 
    strip.setPixelColor(i, ledIndexColors[i]); 
  }

  strip.show();
}

void commandAndFunction(int lis, int whea){
  if(state == lis){
    bop(whea, colors[counter]);
    if(counter > 11){
      counter = 0;
    } else{
      counter++;
    }
    state = 9;

  }
}

void setup() {
  Serial.begin(9600);

      #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  for(int i = 1; i < 8; i++){
    bob(i, colors[counter]);
    updateLEDs();
  }
 
  for(int i = 8; i < 1; i++){
    bob(i, colors[counter]);
    updateLEDs();
  }
 
  while(cont(){
   updateLEDs();
  }
 

}

void loop() {

  if(timer > 3000){
    rainbow(30);
  }
  

  if (Serial.available() > 0) {
    state = Serial.read();
    timer = 0;
  }

  updateLEDs();

  commandAndFunction('1',1);
  commandAndFunction('2',2);
  commandAndFunction('3',3);
  commandAndFunction('4',4);
  commandAndFunction('5',5);
  commandAndFunction('6',6);
  commandAndFunction('7',7);
  commandAndFunction('8',8);
  

  timer++;

  
}

void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    if (Serial.available() > 0) {
      timer = 0;
      break;
    }
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
    
  }
}
