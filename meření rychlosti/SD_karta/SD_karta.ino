//Otázky:
  //Jak zaznamenávat čas na kartu?
  //Lze na kartu zaznamenat i souřadnice?
  //V jakém formátu by měl být soubor na kartě, do kterého se budou zaznamenávat údaje.(.txt, excel)

#include <SPI.h>
#include <SD.h>

File Slozka;
int const pinSS = 10;
int const pinCS = 4;

long int Time;


void setup()
{
  pinMode(pinSS, OUTPUT);           // i když se pin nepoužívá, musí být definován jako výstup!
  Serial.begin(9600);               // začátek sériové komunikace

  // pokud není karta dostupná, tak:
/* if (!SD.begin(pinCS))
  {
    Serial.println("nedostupne");
    while (1);
  }
  Serial.println("dostupne");
*/

  
}

void loop()
{
  Time = millis;
  Slozka = SD.open("test.txt", FILE_WRITE);       // soubor, který chceme otevřít a psát do něj (FILE_WRITE) se jmenuje test.txt (popřípadě vložte celou cestu k souboru)

  // pokud se soubor načte a otevře, tak:
  if (Slozka)
  {
    // zapiš do souboru
    Slozka.println(Time);   //zaznamenáví časovou značku, ale asi by tam šlo dát "časové razítko" jako v serial monitoru
    Slozka.print("Air:");
    Slozka.println(veloc);
    Slozka.print("Bike:");
    Slozka.println(TachoSpeed);
    Slozka.print("GPS:");
    Slozka.println(GPSpeed);
    
    // zavři soubor
    Slozka.close();
  } 
}
