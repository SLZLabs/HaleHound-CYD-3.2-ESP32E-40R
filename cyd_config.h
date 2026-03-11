#ifndef CYD_CONFIG_H
#define CYD_CONFIG_H

// ═══════════════════════════════════════════════════════════════════════════
// HaleHound-CYD Master Pin Configuration
// Board: ESP32-32E 4.0" Resistive Touch (320x480 ST7796 + XPT2046)
// Created: 2026-02-06
// Updated: 2026-03-11 — Forked for ESP32-32E 4.0" Resistive CYD
// ═══════════════════════════════════════════════════════════════════════════
//
// This build is ONLY for the ESP32-32E 320x480 Resistive Touch CYD.
// Display: ST7796 (same as 3.5" CYD capacitive variant)
// Touch: XPT2046 resistive on SHARED HSPI bus (same SPI as display)
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// FIRMWARE VERSION — single source of truth
// ═══════════════════════════════════════════════════════════════════════════

#define FW_VERSION "v3.2.0"

#ifdef NMRF_HAT
  #define FW_EDITION   "CYD 4.0R-HAT Edition"
  #define FW_DEVICE    "HaleHound-CYD-40R-HAT"
#else
  #define FW_EDITION   "CYD 4.0R Edition"
  #define FW_DEVICE    "HaleHound-CYD-40R"
#endif

#define FW_FULL_VERSION FW_VERSION " " FW_EDITION

// ═══════════════════════════════════════════════════════════════════════════
// BOARD SETTINGS — ESP32-32E 4.0" 320x480 Resistive
// ═══════════════════════════════════════════════════════════════════════════

#define CYD_BOARD_NAME    "HaleHound-CYD 4.0\" R"
#define CYD_SCREEN_WIDTH  320
#define CYD_SCREEN_HEIGHT 480
#define CYD_TFT_BL        27    // Backlight on GPIO27

// ═══════════════════════════════════════════════════════════════════════════
// DISPLAY PINS (HSPI) — ST7796
// ═══════════════════════════════════════════════════════════════════════════
#define CYD_TFT_MISO    12
#define CYD_TFT_MOSI    13
#define CYD_TFT_SCLK    14
#define CYD_TFT_CS      15
#define CYD_TFT_DC       2
#define CYD_TFT_RST     -1    // Connected to EN reset

// ═══════════════════════════════════════════════════════════════════════════
// TOUCH CONTROLLER — XPT2046 on SHARED HSPI bus
// ═══════════════════════════════════════════════════════════════════════════
// On this board the XPT2046 shares the HSPI bus with the ST7796 display.
// Same MOSI/MISO/CLK as TFT (GPIO 13/12/14), own CS on GPIO33.
// The CYD28_TouchscreenR library is used in HARDWARE SPI mode (pass the
// HSPI SPIClass instance) instead of software bit-bang mode.
//
// ┌─────────────┐      ┌─────────────┐
// │  XPT2046    │      │  ESP32-32E  │
// │  Touch      │      │   (HSPI)    │
// ├─────────────┤      ├─────────────┤
// │ CLK ────────┼──────┤ GPIO 14     │ (shared with TFT)
// │ MOSI ───────┼──────┤ GPIO 13     │ (shared with TFT)
// │ MISO ───────┼──────┤ GPIO 12     │ (shared with TFT)
// │ CS ─────────┼──────┤ GPIO 33     │ (touch exclusive)
// │ IRQ ────────┼──────┤ GPIO 36     │ (touch interrupt)
// └─────────────┘      └─────────────┘

#define CYD_TOUCH_CS    33
#define CYD_TOUCH_IRQ   36

// Touch shares HSPI — these are the same pins as TFT
#define CYD_TOUCH_ON_HSPI          // Flag: touch uses hardware HSPI, not software SPI
#define CYD_TOUCH_MOSI  CYD_TFT_MOSI  // GPIO 13
#define CYD_TOUCH_MISO  CYD_TFT_MISO  // GPIO 12
#define CYD_TOUCH_CLK   CYD_TFT_SCLK  // GPIO 14

// ═══════════════════════════════════════════════════════════════════════════
// SHARED SPI BUS (VSPI) - SD Card, CC1101, and NRF24L01 share this bus
// Each device has its own CS pin - only one active at a time!
// ═══════════════════════════════════════════════════════════════════════════
#define VSPI_SCK        18    // Shared SPI Clock
#define VSPI_MOSI       23    // Shared SPI MOSI
#define VSPI_MISO       19    // Shared SPI MISO

// ═══════════════════════════════════════════════════════════════════════════
// SD CARD (Shares VSPI bus with radios)
// ═══════════════════════════════════════════════════════════════════════════
//
// WIRING DIAGRAM:
// ┌─────────────┐      ┌─────────────┐
// │  MicroSD    │      │     CYD     │
// │   Card      │      │   ESP32     │
// ├─────────────┤      ├─────────────┤
// │ VCC ────────┼──────┤ 3.3V        │
// │ GND ────────┼──────┤ GND         │
// │ CLK ────────┼──────┤ GPIO 18     │ (shared VSPI)
// │ MOSI ───────┼──────┤ GPIO 23     │ (shared VSPI)
// │ MISO ───────┼──────┤ GPIO 19     │ (shared VSPI)
// │ CS ─────────┼──────┤ GPIO 5      │ (SD exclusive)
// └─────────────┘      └─────────────┘
//
// NOTE: SD card on CYD is built-in (microSD slot on back of board)
// Perfect for storing DuckyScript payloads!
//
// ═══════════════════════════════════════════════════════════════════════════

#define SD_CS            5    // SD Card Chip Select (built-in slot)
#define SD_SCK          VSPI_SCK
#define SD_MOSI         VSPI_MOSI
#define SD_MISO         VSPI_MISO

// Legacy aliases for radio code
#define RADIO_SPI_SCK   VSPI_SCK
#define RADIO_SPI_MOSI  VSPI_MOSI
#define RADIO_SPI_MISO  VSPI_MISO

// ═══════════════════════════════════════════════════════════════════════════
// CC1101 SubGHz RADIO (Red HW-863 Module)
// ═══════════════════════════════════════════════════════════════════════════
//
// WIRING DIAGRAM:
// ┌─────────────┐      ┌─────────────┐
// │   CC1101    │      │     CYD     │
// │   HW-863    │      │   ESP32     │
// ├─────────────┤      ├─────────────┤
// │ VCC ────────┼──────┤ 3.3V        │
// │ GND ────────┼──────┤ GND         │
// │ SCK ────────┼──────┤ GPIO 18     │
// │ MOSI ───────┼──────┤ GPIO 23     │
// │ MISO ───────┼──────┤ GPIO 19     │
// │ CS ─────────┼──────┤ GPIO 26     │ (GPIO 27 = backlight)
// │ GDO0 ───────┼──────┤ GPIO 22     │ (P3 connector) TX to radio
// │ GDO2 ───────┼──────┤ GPIO 35     │ (P3 connector) RX from radio
// └─────────────┘      └─────────────┘
//
// IMPORTANT: GDO0/GDO2 naming is confusing!
// - GDO0 (GPIO22) = Data going TO the CC1101 (for TX)
// - GDO2 (GPIO35) = Data coming FROM the CC1101 (for RX)
// This matches the HaleHound fix for CiferTech's swapped pins.
//
// ═══════════════════════════════════════════════════════════════════════════

#define CC1101_CS     26    // Chip Select - GPIO 27 is backlight, use GPIO 26
#define CC1101_GDO0     22    // TX data TO radio - P3 connector
#ifdef NMRF_HAT
  #define CC1101_GDO2   22    // Hat: no GDO2 wire — GDO0 outputs same RX data
#else
  #define CC1101_GDO2   35    // RX data FROM radio - P3 connector (INPUT ONLY)
#endif

// SPI bus aliases
#define CC1101_SCK      RADIO_SPI_SCK
#define CC1101_MOSI     RADIO_SPI_MOSI
#define CC1101_MISO     RADIO_SPI_MISO

// RCSwitch compatibility (HaleHound pin naming)
// REMEMBER: CiferTech had TX/RX swapped - we fixed it!
#define TX_PIN          CC1101_GDO0   // GPIO22 - enableTransmit()
#define RX_PIN          CC1101_GDO2   // GPIO35 - enableReceive()

// ═══════════════════════════════════════════════════════════════════════════
// NRF24L01+PA+LNA 2.4GHz RADIO
// ═══════════════════════════════════════════════════════════════════════════
//
// WIRING DIAGRAM:
// ┌─────────────┐      ┌─────────────┐
// │  NRF24L01   │      │     CYD     │
// │  +PA+LNA    │      │   ESP32     │
// ├─────────────┤      ├─────────────┤
// │ VCC ────────┼──────┤ 3.3V        │ (add 10uF cap if unstable!)
// │ GND ────────┼──────┤ GND         │
// │ SCK ────────┼──────┤ GPIO 18     │ (shared with CC1101)
// │ MOSI ───────┼──────┤ GPIO 23     │ (shared with CC1101)
// │ MISO ───────┼──────┤ GPIO 19     │ (shared with CC1101)
// │ CSN ────────┼──────┤ GPIO 4      │ (was RGB Red LED)
// │ CE ─────────┼──────┤ GPIO 16     │ (was RGB Green LED)
// │ IRQ ────────┼──────┤ GPIO 17     │ (was RGB Blue LED) OPTIONAL
// └─────────────┘      └─────────────┘
//
// NOTE: The +PA+LNA version needs clean 3.3V power!
// Add a 10uF capacitor between VCC and GND at the module if you get
// communication errors or the module resets randomly.
//
// ═══════════════════════════════════════════════════════════════════════════

#ifdef NMRF_HAT
  // NM-RF-Hat: physical switch selects CC1101 or NRF24 on same two GPIOs
  #define NRF24_CSN     27    // Shared with CC1101_CS via hat switch
  #define NRF24_CE      22    // Shared with CC1101_GDO0 via hat switch
#else
  #define NRF24_CSN      4    // Chip Select - was RGB Red
  #define NRF24_CE      16    // Chip Enable - was RGB Green
  #define NRF24_IRQ     17    // Interrupt - was RGB Blue (OPTIONAL)
#endif

// SPI bus aliases
#define NRF24_SCK       RADIO_SPI_SCK
#define NRF24_MOSI      RADIO_SPI_MOSI
#define NRF24_MISO      RADIO_SPI_MISO

// ═══════════════════════════════════════════════════════════════════════════
// PN532 NFC/RFID MODULE (13.56 MHz)
// ═══════════════════════════════════════════════════════════════════════════
//
// WIRING DIAGRAM:
// ┌─────────────┐      ┌─────────────┐
// │  PN532 V3   │      │     CYD     │
// │ (Elechouse) │      │   ESP32     │
// ├─────────────┤      ├─────────────┤
// │ VCC ────────┼──────┤ 3.3V (CN1)  │
// │ GND ────────┼──────┤ GND  (CN1)  │
// │ SCK ────────┼──────┤ GPIO 18     │ (shared VSPI)
// │ MOSI ───────┼──────┤ GPIO 23     │ (shared VSPI)
// │ MISO ───────┼──────┤ GPIO 19     │ (shared VSPI)
// │ SS ─────────┼──────┤ GPIO 17     │ (was NRF24 IRQ — never used)
// └─────────────┘      └─────────────┘
//
// DIP SWITCHES: CH1=OFF, CH2=ON (SPI mode)
//
// NOTE: PN532 uses LSBFIRST SPI (all other VSPI devices use MSBFIRST).
// Safe because Adafruit library brackets every transfer with
// beginTransaction(LSBFIRST)/endTransaction(), and SPI manager
// ensures only one device is active at a time.
//
// ═══════════════════════════════════════════════════════════════════════════

#define PN532_CS        17    // Chip Select - was NRF24 IRQ (RGB Blue LED, unused)

// SPI bus aliases
#define PN532_SCK       RADIO_SPI_SCK
#define PN532_MOSI      RADIO_SPI_MOSI
#define PN532_MISO      RADIO_SPI_MISO

// ═══════════════════════════════════════════════════════════════════════════
// GPS NEO-6M MODULE (Software Serial)
// ═══════════════════════════════════════════════════════════════════════════
//
// WIRING: GT-U7 GPS connected to P1 JST connector
// ┌─────────────┐      ┌─────────────┐
// │   GT-U7     │      │  CYD P1     │
// │    GPS      │      │  Connector  │
// ├─────────────┤      ├─────────────┤
// │ VCC ────────┼──────┤ VIN         │
// │ GND ────────┼──────┤ GND         │
// │ TX ─────────┼──────┤ RX (GPIO 3) │ (ESP receives GPS data)
// │ RX ─────────┼──────┤ TX (GPIO 1) │ (not used)
// └─────────────┘      └─────────────┘
//
// NOTE: P1 RX/TX are shared with CH340C USB serial.
// When GPS is active, Serial RX from computer is unavailable.
// Serial.println() debug output still works (UART0 TX on GPIO1).
// Uses HardwareSerial UART2 remapped to GPIO3 for reliable reception.
//
// ═══════════════════════════════════════════════════════════════════════════

#define GPS_RX_PIN       3    // P1 RX pin - ESP32 receives from GPS TX
#define GPS_TX_PIN      -1    // Not used - GPS is receive-only
#define GPS_BAUD      9600    // GT-U7 default baud rate

// ═══════════════════════════════════════════════════════════════════════════
// UART SERIAL MONITOR
// ═══════════════════════════════════════════════════════════════════════════
// UART passthrough for hardware hacking - read target device debug ports
// P1 connector: Full duplex via UART0 GPIO3/1 (shared with USB serial)
// Speaker connector: RX only via GPIO26

#define UART_MON_P1_RX        3    // P1 RX pin (shared with USB Serial RX)
#define UART_MON_P1_TX        1    // P1 TX pin (shared with USB Serial TX)
#define UART_MON_SPK_RX      -1    // GPIO 26 is CC1101_CS on 4.0" — no speaker RX
#define UART_MON_DEFAULT_BAUD 115200
#define CYD_HAS_SERIAL_MON    1

// ═══════════════════════════════════════════════════════════════════════════
// BUTTONS
// ═══════════════════════════════════════════════════════════════════════════
// CYD boards only have BOOT button - use touchscreen for navigation

#define BOOT_BUTTON      0    // GPIO0 - active LOW, directly readable

// ═══════════════════════════════════════════════════════════════════════════
// TOUCH BUTTON ZONES (Virtual buttons on touchscreen)
// Coordinates for PORTRAIT orientation (320x480)
// ═══════════════════════════════════════════════════════════════════════════

// UP button - top left (starts below icon bar touch zone to avoid overlap)
#define TOUCH_BTN_UP_X1      0
#define TOUCH_BTN_UP_Y1     60
#define TOUCH_BTN_UP_X2    107
#define TOUCH_BTN_UP_Y2     80

// DOWN button - bottom left
#define TOUCH_BTN_DOWN_X1    0
#define TOUCH_BTN_DOWN_Y1  400
#define TOUCH_BTN_DOWN_X2  107
#define TOUCH_BTN_DOWN_Y2  480

// SELECT button - center
#define TOUCH_BTN_SEL_X1   107
#define TOUCH_BTN_SEL_Y1   200
#define TOUCH_BTN_SEL_X2   213
#define TOUCH_BTN_SEL_Y2   280

// BACK button - top right
#define TOUCH_BTN_BACK_X1  213
#define TOUCH_BTN_BACK_Y1    0
#define TOUCH_BTN_BACK_X2  320
#define TOUCH_BTN_BACK_Y2   80

// ═══════════════════════════════════════════════════════════════════════════
// FEATURE FLAGS
// ═══════════════════════════════════════════════════════════════════════════

#define CYD_HAS_CC1101      1     // CC1101 SubGHz radio connected
#define CYD_HAS_NRF24       1     // NRF24L01+PA+LNA 2.4GHz radio connected
#define CYD_HAS_GPS         1     // NEO-6M GPS module connected
#define CYD_HAS_SDCARD      1     // SD card ENABLED (shares VSPI with radios)
#define CYD_HAS_RGB_LED     0     // RGB LED DISABLED (pins used for NRF24)
#define CYD_HAS_SPEAKER     0     // Speaker DISABLED (pin used for GPS)
#define CYD_HAS_PCF8574     0     // No I2C button expander (unlike ESP32-DIV)
#define CYD_HAS_PN532       1     // PN532 NFC/RFID reader (13.56 MHz)

// ═══════════════════════════════════════════════════════════════════════════
// SPI BUS SHARING - ACTIVE DEVICES
// ═══════════════════════════════════════════════════════════════════════════
//
// HSPI Bus (GPIO 12/13/14) — DISPLAY + TOUCH (XPT2046):
//   ┌──────────┬──────────────┬───────────────────────────────┐
//   │ Device   │ CS Pin       │ Notes                         │
//   ├──────────┼──────────────┼───────────────────────────────┤
//   │ ST7796   │ GPIO 15      │ TFT display                   │
//   │ XPT2046  │ GPIO 33      │ Resistive touch controller    │
//   └──────────┴──────────────┴───────────────────────────────┘
//
// VSPI Bus (GPIO 18/19/23) — RADIOS + SD:
//   ┌──────────┬──────────────┬───────────────────────────────┐
//   │ Device   │ CS Pin       │ Notes                         │
//   ├──────────┼──────────────┼───────────────────────────────┤
//   │ SD Card  │ GPIO 5       │ Built-in slot, payload storage│
//   │ CC1101   │ GPIO 26      │ SubGHz radio                  │
//   │ NRF24    │ GPIO 4       │ 2.4GHz radio                  │
//   │ PN532    │ GPIO 17      │ NFC/RFID 13.56 MHz (LSBFIRST)│
//   └──────────┴──────────────┴───────────────────────────────┘
//
// IMPORTANT: Only ONE device active per bus at a time!
// Before using a device: Pull its CS LOW, all others HIGH
//
// ═══════════════════════════════════════════════════════════════════════════
// DISABLED/REPURPOSED PINS
// ═══════════════════════════════════════════════════════════════════════════
//
// RGB LED (DISABLED - pins used for NRF24):
//   RGB_RED   = GPIO 4  → NRF24_CSN
//   RGB_GREEN = GPIO 16 → NRF24_CE
//   RGB_BLUE  = GPIO 17 → PN532_CS (was NRF24_IRQ, never used)
//
// Speaker (DISABLED - pin used for GPS):
//   SPEAKER = GPIO 26 → GPS_RX_PIN
//
// LDR Light Sensor (AVAILABLE - not repurposed):
//   LDR = GPIO 34 (input only, 12-bit ADC)
//   Could use for: ambient light detection, battery voltage divider

// ═══════════════════════════════════════════════════════════════════════════
// GPIO 34 NOTE
// ═══════════════════════════════════════════════════════════════════════════
// GPIO 34 = LDR (Light Dependent Resistor) on stock CYD boards.
// Input only, 12-bit ADC. No battery voltage measurement available
// without external hardware (voltage divider from 5V rail).

// ═══════════════════════════════════════════════════════════════════════════
// LAYOUT HELPERS — Use these instead of hardcoded pixel values!
// All values compute at compile time from CYD_SCREEN_WIDTH / CYD_SCREEN_HEIGHT
// ═══════════════════════════════════════════════════════════════════════════

// Icon bar (top navigation strip — used in almost every module)
#define ICON_BAR_TOP      19                              // Top separator line Y
#define ICON_BAR_Y        20                              // Content start inside icon bar
#define ICON_BAR_BOTTOM   36                              // Bottom separator line Y
#define ICON_BAR_H        16                              // Icon bar height (16px icons)
#define CONTENT_Y_START   38                              // First usable Y below icon bar

// Icon bar TOUCH zones (generous for resistive touch)
#define ICON_BAR_TOUCH_TOP     0                          // Touch starts at very top
#define ICON_BAR_TOUCH_BOTTOM  55                         // Generous bottom for stylus/finger

// Padded content area
#define CONTENT_PADDED_X     5                            // Left padding (5px)
#define CONTENT_PADDED_W     (CYD_SCREEN_WIDTH - 10)      // Width with 5px padding each side
#define CONTENT_INNER_X      10                           // Wider left padding (10px)
#define CONTENT_INNER_W      (CYD_SCREEN_WIDTH - 20)      // Width with 10px padding each side

// Graph/visualization areas
#define GRAPH_FULL_W         (CYD_SCREEN_WIDTH - 4)       // Near full width (2px each side)
#define GRAPH_PADDED_W       (CYD_SCREEN_WIDTH - 10)      // Standard graph width

// Menu layout
#define MENU_COLUMN_W        (CYD_SCREEN_WIDTH / 2)       // Half-screen column
#define MENU_COL_LEFT_X      10                           // Left column start
#define MENU_COL_RIGHT_X     (MENU_COL_LEFT_X + MENU_COLUMN_W)

// Dialog boxes (centered)
#define DIALOG_W             (CYD_SCREEN_WIDTH - 20)      // Standard dialog width
#define DIALOG_X             10                           // Dialog left edge
#define DIALOG_CENTER_X      (CYD_SCREEN_WIDTH / 2)       // Horizontal center

// Bottom area positions (relative to screen height)
#define BOTTOM_HINT_Y        (CYD_SCREEN_HEIGHT - 45)     // Hint text area
#define BOTTOM_NAV_Y         (CYD_SCREEN_HEIGHT - 33)     // Navigation text

// Button bar
#define BUTTON_BAR_Y     (CYD_SCREEN_HEIGHT - 37)   // Bottom button bar top edge
#define BUTTON_BAR_H     37                          // Button bar height
#define STATUS_LINE_Y    (CYD_SCREEN_HEIGHT - 18)    // Status text near bottom
#define CONTENT_BOTTOM   (BUTTON_BAR_Y - 2)          // Last usable Y before button bar

// ═══════════════════════════════════════════════════════════════════════════
// LAYOUT SCALING — Converts 2.8" (240x320) coordinates to current screen size
// All values compute at COMPILE TIME (integer math, no runtime cost)
// On 4.0R (320x480): SCALE_Y(215) = 322, SCALE_X(175) = 233
// ═══════════════════════════════════════════════════════════════════════════

#define SCALE_Y(y)  ((y) * CYD_SCREEN_HEIGHT / 320)
#define SCALE_X(x)  ((x) * CYD_SCREEN_WIDTH / 240)
#define SCALE_W(w)  ((w) * CYD_SCREEN_WIDTH / 240)
#define SCALE_H(h)  ((h) * CYD_SCREEN_HEIGHT / 320)

// Menu button dimensions (auto-scale with column width)
#define MENU_BTN_W          (CYD_SCREEN_WIDTH / 2 - 20)
#define MENU_BTN_H          SCALE_H(60)
#define MENU_ICON_OFFSET_X  ((MENU_BTN_W - 16) / 2)
#define MENU_TEXT_OFFSET_Y  SCALE_H(30)

// Submenu layout
#define SUBMENU_Y_START     SCALE_Y(30)     // First item Y
#define SUBMENU_Y_SPACING   SCALE_Y(30)     // Gap between items
#define SUBMENU_LAST_GAP    SCALE_Y(10)     // Extra gap before "Back" item
#define SUBMENU_TOUCH_W     (CYD_SCREEN_WIDTH - 20)  // Touch hit area width
#define SUBMENU_TOUCH_H     SCALE_Y(25)     // Touch hit area height

// ═══════════════════════════════════════════════════════════════════════════
// TEXT SIZE — Scaled for display physical size
// 4.0" (320x480): size 1 = 6x8px chars, ~53 chars/line
// ═══════════════════════════════════════════════════════════════════════════

// Text size stays at 1 — setTextSize(2) pixel-doubles and looks bad.
// The 4.0" fills space via layout scaling (SCALE_Y/X), not font scaling.
#define TEXT_SIZE_BODY      1     // Body text, menu items, status info
#define TEXT_SIZE_SMALL     1     // Fine print, dense data, debug info
#define TEXT_LINE_H        12     // Line height for body text
#define TEXT_LINE_H_SMALL  12     // Line height for small text
#define TEXT_CHAR_W         6     // Character width at body size

// ═══════════════════════════════════════════════════════════════════════════
// DEBUG SETTINGS
// ═══════════════════════════════════════════════════════════════════════════

#define CYD_DEBUG           1
#define CYD_DEBUG_BAUD 115200

#endif // CYD_CONFIG_H
