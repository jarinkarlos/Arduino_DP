//Routine for calculating the velocity from 
//a pitot tube and MPXV7002DP pressure differential sensor

#include <Arduino.h>
#include <U8x8lib.h>
 
 
U8X8_SSD1306_128X64_NONAME_HW_I2C oled_display(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
int sensorPin = A0;
int sensorValue = 0;

float V_0 = 5.0; // supply voltage to the pressure sensor
float rho = 1.204; // density of air 

// parameters for averaging and offset
int offset = 0;
int offset_size = 10;
int veloc_mean_size = 20;
int zero_span = 2;

// setup and calculate offset
void setup() {
  oled_display.begin();
  oled_display.setPowerSave(0);
  oled_display.setFont(u8x8_font_chroma48medium8_r);
  Serial.begin(9600);
  for (int ii=0;ii<offset_size;ii++){
    offset += analogRead(A0)-(1023/2);
  }
  offset /= offset_size;
}

void loop() {
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
  oled_display.print(veloc);
  delay(100);
  oled_display.clear();
  Serial.println(veloc); // print velocity
  delay(10); // delay for stability
}
