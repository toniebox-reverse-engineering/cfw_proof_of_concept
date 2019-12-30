#define LED_RED 19 //19 TCK (??) //No digital pin, pin_layout unclear
#define LED_GREEN 21 //21 SOP2 (13+36) //Works fine
#define LED_BLUE 17 ///17 TDO (31+38) //Power Pin needed

#define POWER_PIN 61 //61 GPIO06
#define RESET_DAC_PIN 62 //62 GPIO07
 
#include <Wire.h>
 
void setup()
{
  //pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
    
  pinMode(RESET_DAC_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  
  digitalWrite(RESET_DAC_PIN, HIGH);
  digitalWrite(POWER_PIN, HIGH);
  
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
 
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  
  
  Wire.begin();
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  Serial.print(" Scanning...");
  uint8_t error, address;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    Wire.write(1);  ///////////////////////////////////// sketch works ok when this line added
    error = Wire.endTransmission();
    if (error==0) {
      Serial.print("Found Address 0x");
      if (address<15) Serial.print('0');
      Serial.print(address,HEX);
      Serial.print(", ");
    }
    delay(10);
  }   
   
  Serial.println();  
 //while(1) { }
 
  delay(1000);           // wait 5 seconds for next scan
}
