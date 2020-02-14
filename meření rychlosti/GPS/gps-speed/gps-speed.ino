#include <NMEAGPS.h>
#include <GPSport.h>

//BACHA na prehozeni barev !!! Cervena je zem a cerna je 5V
//rxd na gps - 9
//txd na gps - 8

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

void setup()
{
  Serial.begin(9600);
  gpsPort.begin(9600);
}

void loop()
{
  while (gps.available(gpsPort)) {
    fix = gps.read();

   Serial.print(F("SPEED: "));
    if (fix.valid.speed)
      Serial.println(fix.speed_kph());
  }
}
