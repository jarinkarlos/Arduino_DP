int hallPin = 8;
int hallstav = 0;

void setup() {
  Serial.begin(9600);
  pinMode(hallPin, INPUT);
}

void loop() {
  hallstav = digitalRead(hallPin);

  if (hallstav == 1)
  {Serial.println ("Off");}

  if (hallstav == 0)
  {Serial.println("Je tu magnet");}
}
