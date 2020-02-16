/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#ifndef TARGET_STM32F4
  #error "Oops! Select an STM32F4 board in 'Tools > Board.'"
#elif HOTENDS > 3 || E_STEPPERS > 3
  #error "BIGTREE SKR Pro V1.1 supports up to 3 hotends / E-steppers."
#endif

#define BOARD_INFO_NAME "BIGTREE SKR Pro 1.1" // redefined?

// Use one of these or SDCard-based Emulation will be used
#define SRAM_EEPROM_EMULATION   // Use BackSRAM-based EEPROM emulation
//#define FLASH_EEPROM_EMULATION  // Use Flash-based EEPROM emulation

//
// Servos
//
#define SERVO0_PIN         PA1

//
// Limit Switches
//
#define X_MIN_PIN          PB10
#define X_MAX_PIN          PE15
#define Y_MIN_PIN          PE12
#define Y_MAX_PIN          PE10
#define Z_MIN_PIN          PG8
#define Z_MAX_PIN          PG5

//
// Z Probe must be this pins
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  PA2
#endif

//
// Steppers
//
#define X_STEP_PIN         PE9
#define X_DIR_PIN          PF1
#define X_ENABLE_PIN       PF2

#define Y_STEP_PIN         PE11
#define Y_DIR_PIN          PE8
#define Y_ENABLE_PIN       PD7

#define Z_STEP_PIN         PE13
#define Z_DIR_PIN          PC2
#define Z_ENABLE_PIN       PC0

#define E0_STEP_PIN        PE14
#define E0_DIR_PIN         PA0
#define E0_ENABLE_PIN      PC3

#define E1_STEP_PIN        PD15
#define E1_DIR_PIN         PE7
#define E1_ENABLE_PIN      PA3

#define E2_STEP_PIN        PD13
#define E2_DIR_PIN         PG9
#define E2_ENABLE_PIN      PF0

#if HAS_TMC220x
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  //#define X_HARDWARE_SERIAL  Serial
  //#define X2_HARDWARE_SERIAL Serial1
  //#define Y_HARDWARE_SERIAL  Serial1
  //#define Y2_HARDWARE_SERIAL Serial1
  //#define Z_HARDWARE_SERIAL  Serial1
  //#define Z2_HARDWARE_SERIAL Serial1
  //#define E0_HARDWARE_SERIAL Serial1
  //#define E1_HARDWARE_SERIAL Serial1
  //#define E2_HARDWARE_SERIAL Serial1
  //#define E3_HARDWARE_SERIAL Serial1
  //#define E4_HARDWARE_SERIAL Serial1

  //
  // Software serial
  //
  #define X_SERIAL_TX_PIN  PC13
  #define X_SERIAL_RX_PIN  PC13

  #define Y_SERIAL_TX_PIN  PE3
  #define Y_SERIAL_RX_PIN  PE3

  #define Z_SERIAL_TX_PIN  PE1
  #define Z_SERIAL_RX_PIN  PE1

  #define E0_SERIAL_TX_PIN PD4
  #define E0_SERIAL_RX_PIN PD4

  #define E1_SERIAL_TX_PIN PD1
  #define E1_SERIAL_RX_PIN PD1

  #define E2_SERIAL_TX_PIN PD6
  #define E2_SERIAL_RX_PIN PD6

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN         PF4  // T1 <-> E0
#define TEMP_1_PIN         PF5  // T2 <-> E1
#define TEMP_2_PIN         PF6  // T3 <-> E2
#define TEMP_BED_PIN       PF3  // T0 <-> Bed

//
// Heaters / Fans
//
#define HEATER_0_PIN       PB1  // Heater0
#define HEATER_1_PIN       PD14 // Heater1
#define HEATER_2_PIN       PB0  // Heater1
#define HEATER_BED_PIN     PD12 // Hotbed
#define FAN_PIN            PC8  // Fan0
#define FAN1_PIN           PE5  // Fan1
#define FAN2_PIN           PE6  // Fan2

//
// SPI devices, buses and pins definition
//
#define NUM_SPI_BUSES 3   //number of SPI buses in the controller
#define SPI_HAS_HW_CRC    //board supports hardware CRC

const int SPI_BusConfig[NUM_SPI_BUSES][6] = {
// MOSI, MISO, SCK , Mode (def), Bit order (default)
  {PB5 , PA6 , PA5 , SPI_MODE_3, SPI_MSB, SPI_HALF_SPEED}, //BUS0: only connected to onboard SD
  {PB15, PB14, PB13, SPI_MODE_0, SPI_MSB, SPI_FULL_SPEED}, //BUS1: on EXT2 port
  {PC12, PC11, PC10, SPI_MODE_0, SPI_MSB, SPI_FULL_SPEED}  //BUS2: on SPI3 port (when not used by drivers)
};

#ifdef SD_DETECT_INVERTED
  #define ExtSDLV LOW
#else
  #define ExtSDLV HIGH
#endif

const int SPI_Devices[][9] = {
// Device type      BUS  Polarity Phase    Bit      MAX Supported  Selection Detect PIN Level when detected
//                  NR.                    Order    Speed          PIN        (SD only) (SD only)
  {DEVTYPE_SD     ,   0, SPI_PHI, SPI_STL, SPI_MSB, SPI_HALF_SPEED,     PA4,      PB11, LOW    },
  {DEVTYPE_SD     ,   1, SPI_PLO, SPI_LTS, SPI_MSB, SPI_FULL_SPEED,    PB12,      PF12, ExtSDLV},
  {DEVTYPE_SD     ,   2, SPI_PLO, SPI_LTS, SPI_MSB, SPI_FULL_SPEED,    PA15,        NC, NC     }, //optional external SD on SPI3
#if HAS_SPI_LCD
  {DEVTYPE_DISPLAY,   1, SPI_PLO, SPI_LTS, SPI_MSB, SPI_FULL_SPEED,    PD11,        NC, NC     },
#endif
//Drivers on this board are hard-wired.
//Users can't change the CS so we disallow the user-redefinition of the CS_PIN

// Device type      BUS  Polarity Phase    Bit      MAX Supported  Selection Type,            Index (for type)
//                  NR.                    Order    Speed          PIN       (Driver only)    (Driver only)
#if AXIS_HAS_SPI(X)         //NC = not change: use the default for the bus
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PA15, DRIVER_AXIS    , 0}, //Index 0 is X
#endif
#if AXIS_HAS_SPI(Y)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,     PB8, DRIVER_AXIS    , 1}, //Index 1 is Y
#endif
#if AXIS_HAS_SPI(Z)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,     PB9, DRIVER_AXIS    , 2}, //Index 2 is Z
#endif
#if AXIS_HAS_SPI(E0)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,     PB3, DRIVER_EXTRUDER, 0}, //E0
#endif
#if AXIS_HAS_SPI(E1)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PG15, DRIVER_EXTRUDER, 1}, //E1
#endif
#if AXIS_HAS_SPI(E2)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PG12, DRIVER_EXTRUDER, 2}, //E2
#endif
  {DEVTYPE_EEPROM ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PA15,              NC, NC} //optional external EEPROM on SPI3
};

#define NUM_SPI_DEVICES (sizeof(SPI_Devices) / sizeof(SPI_Devices[0])) //easier than defining it beforehand

#ifndef SD_SEARCH_ORDER
  #define SD_SEARCH_ORDER { 1, 0, 2 }
#endif

//
// Misc. Functions
//

/**
 *               _____                                             _____
 *           NC | · · | GND                                    5V | · · | GND
 *        RESET | · · | PF12(SD_DETECT)             (LCD_D7)  PG7 | · · | PG6  (LCD_D6)
 *   (MOSI)PB15 | · · | PF11(BTN_EN2)               (LCD_D5)  PG3 | · · | PG2  (LCD_D4)
 *  (SD_SS)PB12 | · · | PG10(BTN_EN1)               (LCD_RS) PD10 | · · | PD11 (LCD_EN)
 *    (SCK)PB13 | · · | PB14(MISO)                 (BTN_ENC)  PA8 | · · | PG4  (BEEPER)
 *               ￣￣                                               ￣￣
 *               EXP2                                              EXP1
 */

//
// LCDs and Controllers
//
#if HAS_SPI_LCD
  #define BEEPER_PIN        PG4
  #define BTN_ENC           PA8

  #if ENABLED(CR10_STOCKDISPLAY)
    #define LCD_PINS_RS     PG6

    #define BTN_EN1         PD11
    #define BTN_EN2         PG2

    #define LCD_PINS_ENABLE PG7
    #define LCD_PINS_D4     PG3

    // CR10_Stock Display needs a different delay setting on SKR PRO v1.1, so undef it here.
    // It will be defined again at the #HAS_GRAPHICAL_LCD section below.
    #undef ST7920_DELAY_1
    #undef ST7920_DELAY_2
    #undef ST7920_DELAY_3

  #else

    #define LCD_PINS_RS     PD10

    #define BTN_EN1         PG10
    #define BTN_EN2         PF11

    #define LCD_PINS_ENABLE PD11
    #define LCD_PINS_D4     PG2

    #if ENABLED(FYSETC_MINI_12864)
      #define DOGLCD_CS     PD11
      #define DOGLCD_A0     PD10
      //#define LCD_BACKLIGHT_PIN -1
      #define LCD_RESET_PIN PG2   // Must be high or open for LCD to operate normally.
      #if EITHER(FYSETC_MINI_12864_1_2, FYSETC_MINI_12864_2_0)
        #ifndef RGB_LED_R_PIN
          #define RGB_LED_R_PIN PG3
        #endif
        #ifndef RGB_LED_G_PIN
          #define RGB_LED_G_PIN PG6
        #endif
        #ifndef RGB_LED_B_PIN
          #define RGB_LED_B_PIN PG7
        #endif
      #elif ENABLED(FYSETC_MINI_12864_2_1)
        #define NEOPIXEL_PIN    PG3
      #endif
    #endif // !FYSETC_MINI_12864

    #if ENABLED(ULTIPANEL)
      #define LCD_PINS_D5   PG3
      #define LCD_PINS_D6   PG6
      #define LCD_PINS_D7   PG7
    #endif

  #endif

  // Alter timing for graphical display
  #if HAS_GRAPHICAL_LCD
    #define BOARD_ST7920_DELAY_1 DELAY_NS(96)
    #define BOARD_ST7920_DELAY_2 DELAY_NS(48)
    #define BOARD_ST7920_DELAY_3 DELAY_NS(600)
  #endif

#endif // HAS_SPI_LCD