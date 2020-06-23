#define startGate 2
#define endGate 3


volatile long startTime = 0;
volatile long endTime = 0;
long bulletTime = 0;
float bulletSpeed = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(startGate, INPUT);
  pinMode(endGate, INPUT);
  attachInterrupt(digitalPinToInterrupt(startGate), UpdateTimeStart, FALLING);
  attachInterrupt(digitalPinToInterrupt(endGate), UpdateTimeEnd, FALLING);
}

void loop() {
  delay(1000);
  noInterrupts();
  bulletTime = endTime - startTime;
  //bulletSpeed = ((float)6,36)/(float)bulletTime;
  Serial.print("Start: ");
  Serial.print(startTime);
  Serial.print(" End: ");
  Serial.print(endTime);
  Serial.print(" Time: ");
  Serial.println(bulletTime);
  //Serial.print(" Speed: ");
  //Serial.print(bulletSpeed);
  //Serial.println(" mm/ms");
  interrupts();
}


void UpdateTimeStart() {
  startTime = micros();
}

void UpdateTimeEnd() {
  endTime = micros();
}
