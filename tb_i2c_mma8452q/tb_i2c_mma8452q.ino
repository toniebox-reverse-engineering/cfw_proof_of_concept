#define POWER_PIN 61 //61 GPIO06
#define RESET_DAC_PIN 62 //62 GPIO07

#include <Wire.h>                 // Must include Wire library for I2C

#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
MMA8452Q accel;                   // create instance of the MMA8452 class

void setup() { 
  pinMode(RESET_DAC_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  
  digitalWrite(RESET_DAC_PIN, HIGH);
  digitalWrite(POWER_PIN, HIGH);
  delay(1000);
  
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  Serial.println("Connected.");
}

void loop() {
  if (accel.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    Serial.print(accel.getCalculatedX(), 3);
    Serial.print("\t");
    Serial.print(accel.getCalculatedY(), 3);
    Serial.print("\t");
    Serial.print(accel.getCalculatedZ(), 3);
    Serial.println();
  }
}
