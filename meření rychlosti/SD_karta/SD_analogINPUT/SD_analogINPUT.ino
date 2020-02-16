//vypíše hodnoty analogového vstupu (zkoušeno s pitotkou) na SD kartu
// využívá String

// připojení knihoven
#include <Wire.h>
#include <SPI.h>
#include <SD.h>


int const pinSS = 10;
int const pinCS = 4;
const int analogPin = A0;

File zapisDat;

void setup () {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  pinMode(pinSS, OUTPUT); //pin se nepoužíví, ale přesto musí být nastaven jako OUTPUT
  
  // kontrola připojené SD karty
  if (!SD.begin(pinCS)) {
    Serial.println("SD karta neni pripojena nebo je vadna!");
    return;
  }
}

void loop () {
  // vytvoření proměnné dataString pro uložení
  // zprávy, která bude zapsána na SD kartu
  String dataString = "Analog pin: ";
  // načtení analogové hodnoty z nastaveného pinu
  int sensor = analogRead(analogPin);
  // připsání hodnoty z pinu do zprávy dataString
  dataString += String(sensor);
  // otevření souboru na SD kartě s názvem mereni.txt
  zapisDat = SD.open("mereni.txt", FILE_WRITE);

  // v případě, že je soubor bez problémů vytvořen (pokud neexistuje),
  // nebo otevřen (pokud existuje), zapiš do něj dataString a ukonči zápis
  if (zapisDat) {
    zapisDat.println(dataString);
    zapisDat.close();
    Serial.println("Zapis na kartu uspesny.");
  }
  // v případě chyby při otevírání souboru vypiš chybu
  else {
    Serial.println("Chyba pri otevreni souboru mereni.txt !");
  }
  // pauza mezi výpisy
  delay(1000);
}
