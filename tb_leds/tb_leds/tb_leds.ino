#define LED_RED 19 //19 TCK (??) //No digital pin, pin_layout unclear
#define LED_GREEN 13 //21 SOP2 (13+36) //Works fine
#define LED_BLUE 31 ///17 TDO (31+38) //Wiring unclear, signal needs to pull the led low put pulls it high.

void setup() {
  //pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("START!");
}

void loop() {
  //Serial.println("LOOP");
  /*
  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);
  delay(500);
  */
  digitalWrite(LED_GREEN, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);
  delay(500);
  
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  
}
