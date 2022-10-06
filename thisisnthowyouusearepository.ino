#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 6
#define LED_COUNT 50
int BRIGHTNESS = 255;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t colors[13] = {0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff};

uint32_t ledIndexColors[8] = {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};
int state;

int counter = 0;

int timer = 0;
int timer2 = 0;

bool cont(){
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

void updateLEDsVTwoTokyoDrift(){
  for(int i = 0; i < 8; i++){
    if((ledIndexColors[i] >> 16) > 0){
      ledIndexColors[i] -= 0x010000;
    }
    if(((ledIndexColors[i] & 0x00ff00) >> 8) > 0){
      ledIndexColors[i] -= 0x000100;
    }
    if((ledIndexColors[i] & 0x0000ff) > 0){
      ledIndexColors[i] -= 0x000001;
    } 
    strip.setPixelColor(i, ledIndexColors[i]); 
  }
  strip.show();
}

void updateLEDs(){
  for(int i = 0; i < 8; i++){
    if((ledIndexColors[i] >> 16) > 0){
      ledIndexColors[i] -= 0x010000;
    }
    if(((ledIndexColors[i] & 0x00ff00) >> 8) > 0){
      ledIndexColors[i] -= 0x000100;
    }
    if((ledIndexColors[i] & 0x0000ff) > 0){
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
  randomSeed(analogRead(0));

      #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  
  for(int i = 1; i < 9; i++){
    bop(i, colors[1]);
    counter++;
    updateLEDs();
    delay(30);
  }

  while(cont()){
    updateLEDs();
  }
 
  for(int i = 9; i > 0; i--){
    bop(i, colors[0]);
    counter++;
    updateLEDs();
    delay(30);
  }
 
  while(cont()){
    updateLEDs();
  }

  delay(2000);
 
}

void loop() {

  if(timer > 3000){
    rainbow(40);
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
  uint32_t colors[13] = {0xff006a, 0x0084ff, 0xff006a, 0x0084ff, 0xff006a, 0x0084ff, 0xff006a, 0x0084ff, 0xff006a, 0x0084ff, 0xff006a, 0x0084ff, 0xff006a};
  
  uint32_t ledIndexColors[8] = {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};

  timer2 = 0;
 
  while (true){
   
    updateLEDsVTwoTokyoDrift();
    timer2++;
     
    if(timer2 == 550){
      bop(random(1,9),colors[random(1,9)]);
      timer2 = 0;
    }
    
    if (Serial.available() > 0) {
      timer = 0;
      timer2 = 0;
      uint32_t colors[13] = {0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff, 0xff005d, 0x0073ff};

      uint32_t ledIndexColors[8] = {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};
      break;
    }
  
  }
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    
}
