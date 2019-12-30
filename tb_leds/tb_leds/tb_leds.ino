#define LED_RED 19 //19 TCK (??) //No digital pin, pin_layout unclear
#define LED_GREEN 21 //21 SOP2 (13+36) //Works fine
#define LED_BLUE 17 ///17 TDO (31+38) //Power Pin needed

#define POWER_PIN 61 //61 GPIO06
#define RESET_DAC_PIN 62 //62 GPIO07

void setup() {

  pinMode(RESET_DAC_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  
  digitalWrite(RESET_DAC_PIN, HIGH);
  digitalWrite(POWER_PIN, HIGH);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("START!");
}

void loop() {
  Serial.println("LOOP");
  
  digitalWrite(LED_RED, HIGH);
  delay(250);
  digitalWrite(LED_RED, LOW);
  delay(250);
  
  digitalWrite(LED_GREEN, HIGH);
  delay(250);
  digitalWrite(LED_GREEN, LOW);
  delay(250);
  
  digitalWrite(LED_BLUE, HIGH);
  delay(250);
  digitalWrite(LED_BLUE, LOW);
  delay(250);
  
}
