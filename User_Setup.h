// ═══════════════════════════════════════════════════════════════════════════
// HaleHound-CYD User_Setup.h
// TFT_eSPI Configuration for ESP32-32E 4.0" Resistive Touch CYD
// ST7796 display, 320x480, XPT2046 touch on shared HSPI
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// USER DEFINED SETTINGS - TFT_eSPI Library Configuration
// ═══════════════════════════════════════════════════════════════════════════

#define USER_SETUP_INFO "HaleHound-CYD-40R"

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 1: DISPLAY DRIVER — ST7796 (same as 3.5" CYD)
// ═══════════════════════════════════════════════════════════════════════════

#define ST7796_DRIVER
#define TFT_WIDTH  320
#define TFT_HEIGHT 480

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 2: DISPLAY SPI PINS (HSPI)
// ═══════════════════════════════════════════════════════════════════════════

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST  -1   // Connected to EN/RST

// Backlight
#define TFT_BL   27   // 4.0" backlight on GPIO27
#define TFT_BACKLIGHT_ON HIGH

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 2B: TOUCH CONTROLLER — XPT2046 on SHARED HSPI
// ═══════════════════════════════════════════════════════════════════════════
// On the ESP32-32E 4.0" Resistive CYD, the XPT2046 shares the HSPI bus
// with the ST7796 display. Touch CS = GPIO33, IRQ = GPIO36.
// TFT_eSPI's built-in XPT2046 support is NOT used — we use the
// CYD28_TouchscreenR library in hardware SPI mode instead (passed the
// HSPI SPIClass* instance). This avoids bus contention issues.

#define TOUCH_CS 33
#define CYD_TOUCH_SEPARATE_SPI 0   // Touch shares HSPI with display

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 3: FONTS
// ═══════════════════════════════════════════════════════════════════════════

#define LOAD_GLCD    // Font 1. Original Adafruit 8 pixel font
#define LOAD_FONT2   // Font 2. Small 16 pixel high font
#define LOAD_FONT4   // Font 4. Medium 26 pixel high font
#define LOAD_FONT6   // Font 6. Large 48 pixel font (numbers only)
#define LOAD_FONT7   // Font 7. 7 segment 48 pixel font (numbers only)
#define LOAD_FONT8   // Font 8. Large 75 pixel font (numbers only)
#define LOAD_GFXFF   // FreeFonts - 48 Adafruit_GFX free fonts

#define SMOOTH_FONT

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 4: SPI SETTINGS
// ═══════════════════════════════════════════════════════════════════════════

// Display SPI frequency
#define SPI_FREQUENCY  40000000  // 40MHz for ST7796

// Touch SPI frequency (XPT2046 requires slower speed)
#define SPI_TOUCH_FREQUENCY  2500000  // 2.5MHz

// Read frequency
#define SPI_READ_FREQUENCY  16000000  // 16MHz — safer for all panel variants

// Use HSPI port for display
#define USE_HSPI_PORT

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 5: ADDITIONAL SETTINGS
// ═══════════════════════════════════════════════════════════════════════════

// Color order - try BGR if colors look wrong
//#define TFT_RGB_ORDER TFT_RGB
//#define TFT_RGB_ORDER TFT_BGR

// Inversion - uncomment if display colors are inverted
//#define TFT_INVERSION_ON
//#define TFT_INVERSION_OFF
