//
// Micronova SPI Display Driver
//
// Display         : MICRONOVA DYSR00P401101 6 Alphanumeric Characters
// Driver Chip     : Maxim MAX6957 28 port constant current driver with SPI interface
// Driver board    : micronova25x4x6_RevX2
// Microcontroller : Arduino MKR10000
//
//
#include "MicroNovaDisplay.h"


// Led Common Anode Control 
// used to initialize  anode_reg_addrs in MicroNovaDisplay object
// one bit per port. LSB
// see schematic
static uint8_t _anode_reg_addrs[] =
{

  // Right-most Device

  // /CS0
  MAX6957_REG_PORT31,
  MAX6957_REG_PORT30,
  MAX6957_REG_PORT29,
  MAX6957_REG_PORT28,
  MAX6957_REG_PORT27,
  MAX6957_REG_PORT26,
  
  // TODO implement 
  // vvvvvvvvvvvvvvvvvv
 
  // /CS1
  MAX6957_REG_PORT31,
  MAX6957_REG_PORT30,
  MAX6957_REG_PORT29,
  MAX6957_REG_PORT28,
  MAX6957_REG_PORT27,
  MAX6957_REG_PORT26,
 

  // /CS2
  MAX6957_REG_PORT31,
  MAX6957_REG_PORT30,
  MAX6957_REG_PORT29,
  MAX6957_REG_PORT28,
  MAX6957_REG_PORT27,
  MAX6957_REG_PORT26,
 

  // Left-most device
  MAX6957_REG_PORT31,
  MAX6957_REG_PORT30,
  MAX6957_REG_PORT29,
  MAX6957_REG_PORT28,
  MAX6957_REG_PORT27,
  MAX6957_REG_PORT26,
 

  // /CS3
  MAX6957_REG_PORT31,
  MAX6957_REG_PORT30,
  MAX6957_REG_PORT29,
  MAX6957_REG_PORT28,
  MAX6957_REG_PORT27,
  MAX6957_REG_PORT26,
};

// Led Segment registers
// used to initialize  seg_reg_addrs in MicroNovaDisplay object
// one bit per port. LSB
// see schematic
static uint8_t _seg_reg_addrs[] =
{
  MAX6957_REG_PORT4, // 0
  MAX6957_REG_PORT5,
  MAX6957_REG_PORT6,
  MAX6957_REG_PORT7,
  MAX6957_REG_PORT8,
  MAX6957_REG_PORT9,
  MAX6957_REG_PORT10,
  MAX6957_REG_PORT11,
  MAX6957_REG_PORT12,
  MAX6957_REG_PORT13,
  MAX6957_REG_PORT14,
  MAX6957_REG_PORT15,
  MAX6957_REG_PORT16,
  MAX6957_REG_PORT17,
  MAX6957_REG_PORT18,
  MAX6957_REG_PORT19,
  MAX6957_REG_PORT20,
  MAX6957_REG_PORT21,
  MAX6957_REG_PORT22,
  MAX6957_REG_PORT23,
  MAX6957_REG_PORT24,
  MAX6957_REG_PORT25  // 21
};

void MicroNovaDisplay::setup(void) {
  //
  // the setup routine runs once at boot 
  // 
  seg_reg_addrs = _seg_reg_addrs; // initialize map to LED control registers
  anode_reg_addrs = _anode_reg_addrs; // initialize map to Segment control registers

  SPI.begin();
  // other stuff for first spi channel will have already been setup 
  // see packages/arduino/hardware/samd/1.6.6/variants/mkr1000/variant.[cpp,h]

  setup_max_registers();

  mode = MICRONOVA_MODE_NORM;

  for (uint8_t i = 0; i < MICRONOVA_MAX_CHARS; i++) {
    // initialize display buffer
    dispvals[i] = 0b00000000000000000000000000000000; // all off
  }
}

void MicroNovaDisplay::write_register(uint8_t addr, uint8_t data) {
  //
  // write 'data' to register 'addr'

  SPI.beginTransaction(SPISettings(MAX6957_SPI_SPEED_HZ, MSBFIRST, MAX6957_SPI_MODE));

  // high byte is address, low byte is data
  digitalWrite(MICRONOVA_0_CS0_PIN,0); // chip select low
  SPI.transfer16(addr << 8 | data);
  digitalWrite(MICRONOVA_0_CS0_PIN,1); // chip select high

  SPI.endTransaction();
}

uint8_t MicroNovaDisplay::read_register(uint8_t addr) {
  //
  // returns contents of register 'addr'
  //
  uint8_t read_byte;
  //
  // clockspeed, byte order, clock mode (idle low, clock data low->high)
  SPI.beginTransaction(SPISettings(MAX6957_SPI_SPEED_HZ, MSBFIRST, MAX6957_SPI_MODE));

  digitalWrite(MICRONOVA_0_CS0_PIN,0); // chip select low
  SPI.transfer16((MAX6957_READ | addr) << 8); // address and Read bit set
  digitalWrite(MICRONOVA_0_CS0_PIN,1); // chip select high

  // read back register contents  
  digitalWrite(MICRONOVA_0_CS0_PIN,0); // chip select low
  read_byte       = SPI.transfer(MAX6957_REG_NO_OP); // read data
                    SPI.transfer(MAX6957_REG_NO_OP); // dummy cycle
  digitalWrite(MICRONOVA_0_CS0_PIN,1);

  SPI.endTransaction();

  return read_byte;
}

void MicroNovaDisplay::setup_max_registers() {
  //
  // Do everything to setup the MAX6957 for operation
  //
  pinMode(MICRONOVA_0_CS0_PIN,OUTPUT);
  pinMode(MICRONOVA_0_CS1_PIN,OUTPUT);
  pinMode(MICRONOVA_0_CS2_PIN,OUTPUT);
  pinMode(MICRONOVA_0_CS3_PIN,OUTPUT);

  digitalWrite(MICRONOVA_0_CS0_PIN,1); // chip select high
  digitalWrite(MICRONOVA_0_CS1_PIN,1); // 
  digitalWrite(MICRONOVA_0_CS2_PIN,1); // 
  digitalWrite(MICRONOVA_0_CS3_PIN,1); // 

  // clockspeed, byte order, clock mode (idle low, clock data low->high)

  write_register(MAX6957_REG_GLOBAL_CURRENT, MAX6957_GLOBAL_CURRENT_100PCT);


  // per schematic micronova25x4x6_RevX2
  // Ports 4..25 are individual segment Cathodes
  // Ports 26..31 are per-digit LED Anodes to be configured as GPIO OUTPUTS
  //                                                  
  write_register(MAX6957_REG_PORT_CONFIG_7_6_5_4 ,   
      MAX6957_PORT_CONFIG_SEG_DRIVER << 0  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 2  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 4  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 6  );

  write_register(MAX6957_REG_PORT_CONFIG_11_10_9_8 , 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 0  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 2  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 4  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 6  );

  write_register(MAX6957_REG_PORT_CONFIG_15_14_13_12, 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 0  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 2  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 4  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 6  );

  write_register(MAX6957_REG_PORT_CONFIG_19_18_17_16, 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 0  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 2  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 4  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 6  );

  write_register(MAX6957_REG_PORT_CONFIG_23_22_21_20, 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 0  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 2  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 4  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 6  );

  write_register(MAX6957_REG_PORT_CONFIG_27_26_25_24, 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 0  | 
      MAX6957_PORT_CONFIG_SEG_DRIVER << 2  | 
      MAX6957_PORT_CONFIG_GPIO_OUT << 4  | 
      MAX6957_PORT_CONFIG_GPIO_OUT << 6  );

  write_register(MAX6957_REG_PORT_CONFIG_31_30_29_28, 
      MAX6957_PORT_CONFIG_GPIO_OUT << 0  | 
      MAX6957_PORT_CONFIG_GPIO_OUT << 2  | 
      MAX6957_PORT_CONFIG_GPIO_OUT << 4  | 
      MAX6957_PORT_CONFIG_GPIO_OUT << 6  );


  for (uint8_t i = 0; i < MICRONOVA_MAX_CHARS; i++) {
    // turn off all characters
    write_register(anode_reg_addrs[i],1);
  }

  // We come up in shutdown where all the pull-ups are hi-z'd
  // Change mode from power-up default shutdown
  // to Normal
  write_register(MAX6957_REG_CONFIG, MAX6957_CONFIG_NORMAL);
}




void MicroNovaDisplay::loop() {
  // the loop routine runs over and over again forever

  static uint8_t curdisp = 0;
  static uint8_t curseg = 0;
  static bool tog = true;


  switch(mode) {

    case MICRONOVA_MODE_TEST_1:

      // set all the bits in all the segs of all chars
      // then clear all the bits in all the segs of all chars

      if (tog)
        dispvals[curdisp] |= (1 << curseg);
      else
        dispvals[curdisp] &= ~(1 << curseg);

      if (curseg++ > MICRONOVA_MAX_SEGS) {
        curseg = 0;
        if (curdisp++ >= numchars) {
          curdisp = 0;
          tog = !tog;
        }
      }
      delay(10);

      break;

    case MICRONOVA_MODE_NORM:
      break;

    default:
      break;
  }

  return; 

}

void MicroNovaDisplay::muxhandler(void) {
  // 
  // Called from a timer interrupt at sufficient rate to avoid flicker
  //
  static uint8_t curchar   = 0;
  uint32_t curdispval;
  uint8_t i;

#if 0
  /*
   * slow it down so we can see muxing
   */
  const uint8_t div = 100;
  static uint8_t curdiv = div;

  if (--curdiv)
    return;

  curdiv = div;
#endif

  for (i = 0;i < numchars;i++) {
    // turn 'em all off
    micronovadisplay.write_register(anode_reg_addrs[i],1);
  }


  curdispval = dispvals[curchar];
  for (i = 0; i < MICRONOVA_MAX_SEGS; i++) {
    // for each bit in curdispval, turn on appropriate segment
    if (curdispval & (1 << i))
      micronovadisplay.write_register(seg_reg_addrs[i],1);
    else
      micronovadisplay.write_register(seg_reg_addrs[i],0);
  }

  for (i = 0;i < numchars;i++) {
    if (i == curchar)
      micronovadisplay.write_register(anode_reg_addrs[i],0);
    else
      micronovadisplay.write_register(anode_reg_addrs[i],1);
  }


  // done them all, do it again
  curchar++;
  if (curchar >= numchars)
    curchar = 0;

}


#ifdef __cplusplus
extern "C" {
#endif
  int sysTickHook(void) {
    // Arduino run-time has a 1ms interrupt setup..
    // Apps can get called using sysTickHook() 
    // like this:
    //
    // Gets called every 1 msec or so.. 
    //
    micronovadisplay.muxhandler();
    return 0; // 0 says yes run the default sysTick function after this.
  }
#ifdef __cplusplus
}
#endif


