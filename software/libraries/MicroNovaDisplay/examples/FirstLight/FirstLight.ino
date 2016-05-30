#include <SPI.h>
#include <MicroNovaDisplay.h> 

// 
// MicroNova Display
//
MicroNovaDisplay micronovadisplay; 

void setup() {
  // the setup routine runs once at boot
  micronovadisplay.setup();
  micronovadisplay.mode = MICRONOVA_MODE_TEST_1;
  micronovadisplay.numchars = 1*6; // always x6
}

void loop() {
  // the loop routine runs over and over again forever
  micronovadisplay.loop();
}
