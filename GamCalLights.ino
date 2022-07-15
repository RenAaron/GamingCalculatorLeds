#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 6
#define LED_COUNT 8
#define BRIGHTNESS 5

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t colors[13] = {0xff0000, 0xff4000, 0xff9900, 0xffd500, 0x99ff00, 0x3cff00, 0x00ffd5, 0x0084ff, 0x2600ff, 0x8000ff, 0xff00ee, 0xff007b, 0xff003c};
int state;

int counter = 0;

void bop(int ind, uint32_t c){

  int endl = 0;
  
  if(ind > LED_COUNT/2){
    endl = ind;
  } else{
    endl = LED_COUNT - ind;
  }

  strip.setPixelColor(ind - 1, c);
  strip.show();
  
  for(int i = 0; i < endl; i++){
    strip.setPixelColor((ind + i), c);
    strip.setPixelColor((ind + (i)*-1) - 2, c);
    strip.show();
    delay(50);
  }
}

void commandAndFunction(int lis, int whea){
  if(state == lis){
    Serial.println("hey");
    bop(whea, colors[counter]);
    counter++;
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

  commandAndFunction('1',1);
  commandAndFunction('2',2);
  commandAndFunction('3',3);
  commandAndFunction('4',4);
  commandAndFunction('5',5);
  commandAndFunction('6',6);
  commandAndFunction('7',7);
  commandAndFunction('8',8);
  
}
