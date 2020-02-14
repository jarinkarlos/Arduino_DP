/* Tento kód napíše na display zadaný text, podle toho, jestli hallova sonda registruje nebo neregistruje napětí.
 */


#include <Arduino.h>
#include <U8x8lib.h>
 
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X64_NONAME_HW_I2C oled_display(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

int hallPin = 8;
int hallstav = 0;

void setup() {
  oled_display.begin();
  oled_display.setPowerSave(0);
  oled_display.setFont(u8x8_font_chroma48medium8_r);
  Serial.begin(9600);
  pinMode(hallPin, INPUT);
}

void loop() {
  hallstav = digitalRead(hallPin);
 
  if (hallstav == 1)                    //jestliže, sonda neregistruje magnetické pole hallstav=1
  {oled_display.println("Zdar,Piskote");}        //jestliže hallstav = 1, display napíše "Off"
  //{Serial.println ("Off");}           //jestliže hallstav = 1, sériový monitor napíše "Off"

  if (hallstav == 0)                    //jestliže, sonda registruje magnetické pole hallstav=0
  {oled_display.println("Funguje to.");}         //jestliže hallstav = 0, display napíše "On"
  //{Serial.println("On");}             //jestliže hallstav = 0, sériový monitor napíše "On"

  //oled_display.print(hallstav);       //display napíše "1" nebo "2"
  delay(100);                           //inforamce bude na display 100 ms a pak se obnoví
  oled_display.clear();                 //display píše na jedno místo a ne za sebe nebo pod sebe
  //Serial.println(hallstav);           // sériový monitor napíše "1" nebo "2"
 }
