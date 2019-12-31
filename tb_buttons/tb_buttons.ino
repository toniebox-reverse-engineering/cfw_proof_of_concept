#define BTN1 57
#define BTN2 59

void setup() {
  Serial.begin(115200);
  Serial.println("START Button Test");
  
  MAP_PinModeSet(PIN_57, PIN_MODE_0); //BTN1 RX //TODO
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
}

int btn1_state = HIGH;
int btn2_state = HIGH;
void loop() {
  int btn1_read = digitalRead(BTN1);
  int btn2_read = digitalRead(BTN2);
  
  if (btn1_state != btn1_read) {
    btn1_state = btn1_read;
    Serial.print("BTN1: ");
    Serial.println(btn1_read);
    delay(500);
  }
  if (btn2_state != btn2_read) {
    btn2_state = btn2_read;
    Serial.print("BTN2: ");
    Serial.println(btn2_read);
    delay(500);
  }
}
