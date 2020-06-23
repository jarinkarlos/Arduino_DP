
#include <IRremote.h>

#define PIN_IR 3
#define lightGate 2

const int debounce = 50;
volatile long lastMillis = 0;
volatile long newMillis = 0;
volatile long pulseTime = 0;
volatile long millisDiff = 0;

IRsend irsend;

void setup() {
  pinMode(lightGate, INPUT);
  attachInterrupt(digitalPinToInterrupt(lightGate), UpdatePulseTime, FALLING);
  irsend.enableIROut(36);
  irsend.mark(0);
  Serial.begin(9600);

}


void loop() {
  delay(1000); //cekej 1s
  noInterrupts(); //vypni preruseni at se neco neposere
  Serial.print("PULSE TIME: "); //vypis info bez noveho radku
  Serial.println(pulseTime);  // vypis delku pulsu s novym radkem
  interrupts(); //zase zapni preruseni

}

void UpdatePulseTime() {
  newMillis = millis(); // koukni na hodiny
  millisDiff = newMillis - lastMillis; // spocitej rozdil od posledniho ulozeneho casu
  if (millisDiff > debounce){ // pokud je vetsi nez 50ms, udelej nasledujici dva radky, pokud je mensi je to sum a nedelej nic
    pulseTime = millisDiff; // aktualizuj delku pulsu
    lastMillis = newMillis; // a aktualizuj posledni ulozeny cas
    }
}
