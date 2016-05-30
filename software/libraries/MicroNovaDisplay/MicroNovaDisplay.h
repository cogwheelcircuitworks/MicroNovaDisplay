//
// Micronova SPI Display Driver
//

#ifndef MICRONOVA_H

#define MICRONOVA_H

#include "Arduino.h"
#include "SPI.h"              // SAMD SPI
#include "wiring_private.h"   // for pinPeripheral()
#include "MAX6957.h"

//
// mkr10k pin definitions for SPI1  - see packages/arduino/hardware/samd/1.6.6/variants/mkr1000/variant.h
//

// MICRONOVA_0 is the first SPI. Up to 4 Displays can be chained (CS0..CS3)
#define MICRONOVA_0_MOSI_PIN  (8u)  // Labelled MOSI on mkr10k
#define MICRONOVA_0_SCK_PIN   (9u)  // Labelled SCK on mkr10k
#define MICRONOVA_0_MISO_PIN  (10u) // Labelled MISO on mkr10k

#define MICRONOVA_0_CS0_PIN   (7u) // D7 on mkr10k
#define MICRONOVA_0_CS1_PIN   (6u) // D6 on mkr10k
#define MICRONOVA_0_CS2_PIN   (5u) // D5 on mkr10k
#define MICRONOVA_0_CS3_PIN   (4u) // D4 on mkr10k
            

// See the micronova board schematic; P31..P26 are high-side p-ch fet drivers for each digit

// TODO: define MICRONOVA_1 Note: SPI1 used by the WiFi, others are free  s
// see packages/arduino/hardware/samd/1.6.6/variants/mkr1000/variant.h
//
class MicroNovaDisplay {

  public:

    // total number of characters. Micronova is 6 per device, we have 4 Chip Select lines
    // so numchars should be 6,12,18,24, etc.. 
    uint8_t numchars; 

    uint8_t mode; // how to behave 
#   define MICRONOVA_MODE_NORM 0
#   define MICRONOVA_MODE_TEST_1 1
    
    void setup(void); // called once by mainline sketch
    void loop(void);  // called forever by mainline sketch. non-blocking.
    
    void muxhandler(void);

  private:
    void write_register(uint8_t,uint8_t);
    uint8_t read_register(uint8_t);

    
    // character control register maps 
    uint8_t *anode_reg_addrs;
#   define MICRONOVA_MAX_CHARS 24

    // segment control register maps
    uint8_t *seg_reg_addrs;
#   define MICRONOVA_MAX_SEGS 22

    void setup_max_registers(void);
    
    // display buffer
    uint32_t dispvals[MICRONOVA_MAX_CHARS];

};



extern SPIClass SPI;  
extern MicroNovaDisplay micronovadisplay;

#endif // MICRONOVA_H

