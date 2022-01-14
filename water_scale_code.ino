#include "HX711.h"

#define calibration_factor -1450.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

HX711 scale;
int solenoidPin = 4;
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  pinMode(solenoidPin, OUTPUT);    

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
 scale.tare();
  Serial.println("Readings:");
  
}

void loop() {
  Serial.print("Reading: ");
 
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" g"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
   if(scale.get_units()<150){
    delay(3000);
    if(scale.get_units()<150){
     digitalWrite(solenoidPin, HIGH);  //Switch Solenoid ON
  Serial.println("On");
  while(scale.get_units()<400){
     scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" g "); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println("open solenoid");
   digitalWrite(solenoidPin, HIGH);
   delay(1000);
  }
   digitalWrite(solenoidPin, LOW);  //Switch Solenoid Off
  Serial.println("Off");
  }
  }
}