#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#define I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;

void setup() {
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(TimesNewRoman16);
}

void loop() {
  oled.clear();
  oled.println("GPS: 10 m/s");
  oled.println("PIT: 10 m/s");
  oled.println("HAL: 10 m/s");
  delay(1000);
}
