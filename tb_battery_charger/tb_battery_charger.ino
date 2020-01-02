void setup() {
  Serial.begin(115200); 
  Serial.println("Battery + Charger Test");
  pinMode(8, INPUT);
}

void loop() {
  //4.22V -> 2927
  //3.925 -> 2718
  //Values only valid if charger is not connected
  
  Serial.print("Battery: ");
  Serial.println(analogRead(60));
  Serial.print("Charger: ");
  Serial.println(digitalRead(8));
  Serial.println("---");
  delay(1000);
}
