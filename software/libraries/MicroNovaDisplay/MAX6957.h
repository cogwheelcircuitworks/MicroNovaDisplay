//
// Maxim MAX6957 
//

// http://datasheets.maximintegrated.com/en/ds/MAX6957.pdf

#ifndef MAX6957_H 
#define MAX6957_H

#define MAX6957_SPI_MODE SPI_MODE0
#define MAX6957_SPI_SPEED_HZ 5000000

#define MAX6957_READ               0b10000000
#define MAX6957_CONFIG_NORMAL      0b00000001 // comes up in shutdown mode. Must set this first

// Contents of Register MAX6957_REG_GLOBAL_CURRENT
#define MAX6957_GLOBAL_CURRENT_MIN    0
#define MAX6957_GLOBAL_CURRENT_25PCT  4
#define MAX6957_GLOBAL_CURRENT_50PCT  8
#define MAX6957_GLOBAL_CURRENT_75PCT  12
#define MAX6957_GLOBAL_CURRENT_100PCT 15


// Per-port Configuration bits.  These go in MAX6957_REG_PORTS_*, 4 ports per register  
#define MAX6957_PORT_CONFIG_SEG_DRIVER     0b00
#define MAX6957_PORT_CONFIG_GPIO_OUT       0b01
#define MAX6957_PORT_CONFIG_GPIO_IN        0b10
#define MAX6957_PORT_CONFIG_GPIO_IN_PULLUP 0b11

//
// Register addresses
//
#define MAX6957_REG_NO_OP                   0x00 // No-Op R/W 
#define MAX6957_REG_GLOBAL_CURRENT          0x02 // Global Current R/W 
#define MAX6957_REG_CONFIG                  0x04 // Configuration R/W 
#define MAX6957_REG_TRANSITION_DETECT       0x06 // Transition Detect Mask R/W 
#define MAX6957_REG_DISPLAY_TEST            0x07 // Display Test R/W 

// There are two bits for each port in the Port Configuration register. These bits are used to define each port as an LED driver, output port, or input port with/without a pullup resistor. There are 7 Port Configuration registers corresponding to 28 ports.
#define MAX6957_REG_PORT_CONFIG_7_6_5_4     0x09 // Port Configuration P7 P6 P5 P4 R/W 
#define MAX6957_REG_PORT_CONFIG_11_10_9_8   0x0A // Port Configuration P11 P10 P9 P8 R/W 
#define MAX6957_REG_PORT_CONFIG_15_14_13_12 0x0B // Port Configuration P15 P14 P13 P12 R/W 
#define MAX6957_REG_PORT_CONFIG_19_18_17_16 0x0C // Port Configuration P19 P18 P17 P16 R/W 
#define MAX6957_REG_PORT_CONFIG_23_22_21_20 0x0D // Port Configuration P23 P22 P21 P20 R/W 
#define MAX6957_REG_PORT_CONFIG_27_26_25_24 0x0E // Port Configuration P27 P26 P25 P24 R/W 
#define MAX6957_REG_PORT_CONFIG_31_30_29_28 0x0F // Port Configuration P31 P30 P29 P28 R/W 

// There are four bits for each port in an Individual Current register. These bits are used to define the desired constant-current level of an individual port. The minimum increment is 1/16 of the maximum level set by the external resistor connected to the ISET pin.
#define MAX6957_REG_CURRENT054              0x12 // Current054 R/W 
#define MAX6957_REG_CURRENT076              0x13 // Current076 R/W 
#define MAX6957_REG_CURRENT098              0x14 // Current098 R/W 
#define MAX6957_REG_CURRENT0BA              0x15 // Current0BA R/W 
#define MAX6957_REG_CURRENT0DC              0x16 // Current0DC R/W 
#define MAX6957_REG_CURRENT0FE              0x17 // Current0FE R/W 
#define MAX6957_REG_CURRENT110              0x18 // Current110 R/W 
#define MAX6957_REG_CURRENT132              0x19 // Current132 R/W 
#define MAX6957_REG_CURRENT154              0x1A // Current154 R/W 
#define MAX6957_REG_CURRENT176              0x1B // Current176 R/W 
#define MAX6957_REG_CURRENT198              0x1C // Current198 R/W 
#define MAX6957_REG_CURRENT1BA              0x1D // Current1BA R/W 
#define MAX6957_REG_CURRENT1DC              0x1E // Current1DC R/W 
#define MAX6957_REG_CURRENT1FE              0x1F // Current1FE R/W 
// There are 29 Port I/O Value registers corresponding to each individual port (port 31 has two registers). There are 21 Port I/O Value registers that can be used to simultaneously define I/O values for a group of 8 different ports. The rest of the Port I/O Value registers can be used to simultaneously define a group of 2, 3, 4, 5, 6, or 7 different ports.
#define MAX6957_REG_PORT0_NOACTION          0x20 // Port 1 only (virtual port no action) R/W 
#define MAX6957_REG_PORT1_NOACTION          0x21 // Port 1 only (virtual port no action) R/W 
#define MAX6957_REG_PORT2_NOACTION          0x22 // Port 2 only (virtual port no action) R/W 
#define MAX6957_REG_PORT3_NOACTION          0x23 // Port 3 only (virtual port no action) R/W 
#define MAX6957_REG_PORT4                   0x24 // Port 4 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT5                   0x25 // Port 5 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT6                   0x26 // Port 6 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT7                   0x27 // Port 7 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT8                   0x28 // Port 8 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT9                   0x29 // Port 9 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT10                  0x2A // Port 10 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT11                  0x2B // Port 11 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT12                  0x2C // Port 12 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT13                  0x2D // Port 13 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT14                  0x2E // Port 14 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT15                  0x2F // Port 15 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT16                  0x30 // Port 16 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT17                  0x31 // Port 17 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT18                  0x32 // Port 18 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT19                  0x33 // Port 19 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT20                  0x34 // Port 20 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT21                  0x35 // Port 21 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT22                  0x36 // Port 22 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT23                  0x37 // Port 23 only (data bit D0. D7–D1 read as 0) R/W 
#define MAX6957_REG_PORT24                  0x38 // Port 24 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT25                  0x39 // Port 25 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT26                  0x3A // Port 26 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT27                  0x3B // Port 27 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT28                  0x3C // Port 28 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT29                  0x3D // Port 29 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT30                  0x3E // Port 30 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORT31                  0x3F // Port 31 only (data bit D0. D7–D1 read as 0) R/W 1 
#define MAX6957_REG_PORTS_4_TO_7            0x40 // 4 ports 4–7 (data bits D0–D3. D4–D7 read as 0)) R/W 
#define MAX6957_REG_PORTS_4_TO_8            0x41 // 5 ports 4–8 (data bits D0–D4. D5–D7 read as 0) R/W 
#define MAX6957_REG_PORTS_4_TO_9            0x42 // 6 ports 4–9 (data bits D0–D5. D6–D7 read as 0) R/W 
#define MAX6957_REG_PORTS_4_TO_10           0x43 // 7 ports 4–10 (data bits D0–D6. D7 reads as 0) R/W 
#define MAX6957_REG_PORTS_4_TO_11           0x44 // 8 ports 4–11 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_5_TO_12           0x45 // 8 ports 5–12 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_6_TO_13           0x46 // 8 ports 6–13 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_7_TO_14           0x47 // 8 ports 7–14 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_8_TO_15           0x48 // 8 ports 8–15 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_9_TO_16           0x49 // 8 ports 9–16 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_10_TO_17          0x4A // 8 ports 10–17 (data bits D0–D7) RW 
#define MAX6957_REG_PORTS_11_TO_18          0x4B // 8 ports 11–18 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_12_TO_19          0x4C // 8 ports 12–19 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_13_TO_20          0x4D // 8 ports 13–20 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_14_TO_21          0x4E // 8 ports 14–21 (data bits D0–D7) R/W 
#define MAX6957_REG_PORTS_15_TO_22          0x4F // 8 ports 15–22 (data bits D0–D7) R/W 

#endif // MAX6957_H

