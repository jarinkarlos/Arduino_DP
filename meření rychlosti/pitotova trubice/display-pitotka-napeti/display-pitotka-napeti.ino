/*
 
A5 - SCL
A4 - SDA
 
*/
 
#include <Arduino.h>
#include <U8x8lib.h>
 
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
 
 
U8X8_SSD1306_128X64_NONAME_HW_I2C oled_display(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
int sensorPin = A0;
int sensorValue = 0;
 
void setup(void)
{  
 
  oled_display.begin();
  oled_display.setPowerSave(0);
  oled_display.setFont(u8x8_font_chroma48medium8_r);
  Serial.begin(9600);
 
 
}
 
void loop(void)
{
  sensorValue = analogRead(sensorPin);
  oled_display.print(sensorValue);
  delay(100);
  oled_display.clear();
  Serial.println(sensorValue);
  /*for (int x = 0; x < 100; x = x + 1) {
  oled_display.setCursor(0, 4);
  oled_display.print("cislo: ");
  oled_display.setCursor(7, 4);
  oled_display.print(x);
  delay(100);
  oled_display.clear();
  }*/
 
  //oled_display.drawString(2,2,"Test");  //sloupec, radek, text bez diakritiky
  //delay(2000);
}
