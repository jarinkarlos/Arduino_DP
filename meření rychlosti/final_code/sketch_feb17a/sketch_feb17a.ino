/*co je potřeba udělat:
  GPS: -záznam o poloze
       -záznam o času
  SD-karta - přidat záznam na SD kartu
     
*/
/*Zapojení
 * display: SCL - A5; SDA - A4;
 * karta: CS - 4; SCK - 13; MOSI - 11; MISO - 12;
 * GPS: TXD - 8; RXD - 9;
 * hall: OUT - 3;
 * pitotka: ANALOG - A0;
 */

/*//nastavení displaye
#include <Arduino.h>
#include <U8x8lib.h>
 
U8X8_SSD1306_128X64_NONAME_HW_I2C oled_display(/* clock=*/ //SCL, /* data=*/ //SDA, /* reset=*/ //U8X8_PIN_NONE);

//nastavení SD_karty
#include <SPI.h>
#include <SD.h>
int const pinSS = 10;
int const pinCS = 4;
File Slozka;

/*
//pitotova trubice:
float V_0 = 5.0; // supply voltage to the pressure sensor
float rho = 1.204; // density of air 
// parameters for averaging and offset
int offset = 0;
int offset_size = 10;
int veloc_mean_size = 20;
int zero_span = 2;
*/
/*
//tachometr:
const int interruptPin = 3; // cislo pinu kam pripojime halluv sensor nebo tlacitko
const int debounce = 50; // minimalni cas, ktery pulse muze mit. Odfiltruje to sum na tlacitku viz https://en.wikipedia.org/wiki/Switch#Contact_bounce
volatile long lastMillis = 0; // vsechny promene, ktere se maji menit ve funkci volane prerusenim, musi mit pred sebou 'volatile'
volatile long newMillis = 0;
volatile long pulseTime = 0; // sem ulozime rozdil casu mezi pulsy
volatile long millisDiff = 0; // sem budeme ukladat rozdil casu mezi pulsy nez rozhodneme, jestli to neni sum
float TachoSpeed = 0;
*/
/*
//GPS
#include <NMEAGPS.h>
#include <GPSport.h>

//BACHA na prehozeni barev !!! Cervena je zem a cerna je 5V
//rxd na gps - 9
//txd na gps - 8 (piny jsou definovány v knihovně)

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

float GPSpeed = (fix.speed_kph()/(3,6));
*/

// setup and calculate offset
void setup() {
  Serial.begin(9600);
/*
//display
  oled_display.begin();
  oled_display.setPowerSave(0);
  oled_display.setFont(u8x8_font_chroma48medium8_r);
*/
//SD_karta
   pinMode(pinSS, OUTPUT); //pin se nepoužívá, ale přesto musí být nastaven jako OUTPUT
 // pokud není karta dostupná, tak:
 if (!SD.begin(pinCS))
  {
    Serial.println("nedostupne");
    while (1);
  }
  Serial.println("dostupne");

  Slozka = SD.open("test2.txt", FILE_WRITE);
  // pokud se soubor načte a otevře, tak:
  if (Slozka)
  {
    // zapiš do souboru
    Slozka.print("Nazdar!");
    Slozka.close();
  }

/*
//pitotova trubice
  for (int ii=0;ii<offset_size;ii++){
    offset += analogRead(A0)-(1023/2);
  }
  offset /= offset_size;
*/
/*
//tachometr:
  pinMode(interruptPin, INPUT_PULLUP); // dokud neni tlacitko zmacknute bude pin ve stavu HIGH viz https://arduino.cz/arduino-zaklady-funkce-input_pullup/
  attachInterrupt(digitalPinToInterrupt(interruptPin), UpdatePulseTime, FALLING); // nastavime preruseni na pin 3, bude reagovat na klesajici napeti a bude volat funkci UpdatePulseTime
*/
/*
//GPS
  gpsPort.begin(9600);
  */
}


void loop() {
/*
//GPS
  while (gps.available(gpsPort)) {
    fix = gps.read();

   Serial.print("GPSeed: ");
    if (fix.valid.speed);
      //Serial.println(fix.speed_kph());
   Serial.print(GPSpeed);
   Serial.print(", ");
}
*/
/*  
// pitotova trubice:
  float adc_avg = 0; float veloc = 0.0;
  
// average a few ADC readings for stability
  for (int ii=0;ii<veloc_mean_size;ii++){
    adc_avg+= analogRead(A0)-offset;
  }
  adc_avg/=veloc_mean_size;
  
  // make sure if the ADC reads below 512, then we equate it to a negative velocity
  if (adc_avg>512-zero_span and adc_avg<512+zero_span){
  } else{
    if (adc_avg<512){
      veloc = -sqrt((-10000.0*((adc_avg/1023.0)-0.5))/rho);
    } else{
      veloc = sqrt((10000.0*((adc_avg/1023.0)-0.5))/rho);
    }
  }
  Serial.print("PitSpeed: ");
  Serial.print(veloc); // print velocity
  Serial.print(", ");
*/  
/*
//tachometr:
  //Serial.print("PULSE TIME: "); //vypis info bez noveho radku
  //Serial.print(pulseTime);  // vypis delku pulsu s novym radkem
  Serial.print("TachoSpeed:"); //vypis info bez noveho radku
  if (pulseTime == 0 || millis() - lastMillis > 3000) TachoSpeed = 0;
  else TachoSpeed = 3000/(float)pulseTime;
  Serial.println(TachoSpeed);
*/

//SD_karta
  Slozka = SD.open("test2.txt", FILE_WRITE);       // soubor, který chceme otevřít a psát do něj (FILE_WRITE) se jmenuje test.txt (popřípadě vložte celou cestu k souboru)

  // pokud se soubor načte a otevře, tak:
  if (Slozka)
  {
    // zapiš do souboru
   // Slozka.print(GPSpeed);
   // Slozka.print(veloc);
    Slozka.println("test");
    //Slozka.println(TachoSpeed);
    
    // zavři soubor
    Slozka.close();
  }

  Slozka = SD.open("test.txt");
  // pokud se soubor načte a otevře, tak:
  if (Slozka)
  {
    Serial.println("soubor obsahuje: ");

    // čti ze souboru, dokud je co
    while (Slozka.available())
    {
      Serial.write(Slozka.read());
    }
    // zavři soubor
    Slozka.close();
  }
  // pokud se nepodaří soubor načíst a otevřít, tak:
  else
  {
    Serial.println("soubor se nepodarilo otevrit");
  }


/*  
//display print
  oled_display.clear();
  oled_display.setCursor(0,0);
  oled_display.print("Air: ");
  oled_display.print(veloc);
  oled_display.setCursor(10,0);
  oled_display.print("m/s");
  
  oled_display.setCursor(0,2);
  oled_display.print("Bike: ");
  oled_display.print(TachoSpeed);
  oled_display.setCursor(11,2);
  oled_display.print("m/s");

  oled_display.setCursor(0,4);
  oled_display.print("GPS: ");
  oled_display.print(GPSpeed); //definováno pomocí float nahoře
  oled_display.setCursor(10,4);
  oled_display.print("m/s");
  
  delay(1000); // delay for stability
*/
}

/*
void UpdatePulseTime() {
  newMillis = millis(); // koukni na hodiny
  millisDiff = newMillis - lastMillis; // spocitej rozdil od posledniho ulozeneho casu
  if (millisDiff > debounce){ // pokud je vetsi nez 50ms, udelej nasledujici dva radky, pokud je mensi je to sum a nedelej nic
    pulseTime = millisDiff; // aktualizuj delku pulsu
    lastMillis = newMillis; // a aktualizuj posledni ulozeny cas
    }
}
*/
