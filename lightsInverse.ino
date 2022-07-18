#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 6
#define LED_COUNT 8
#define BRIGHTNESS 5

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t colors[13] = {0x006eff, 0xff00bf, 0x006eff, 0xff00bf, 0x006eff, 0xff00bf, 0x006eff, 0xff00bf, 0x006eff, 0xff00bf, 0x006eff, 0xff00bf, 0x006eff};

uint32_t ledIndexColors[8] = {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};
int state;

int counter = 0;

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
  delay(3);
}

void commandAndFunction(int lis, int whea){
  if(state == lis){
    bop(whea, colors[counter]);
    if(counter > 12){
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

}

void loop() {

  if (Serial.available() > 0) {
    state = Serial.read();
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
  
}   
