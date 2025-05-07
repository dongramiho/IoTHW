const int analogPin = 34; 

void setup() {
  Serial.begin(115200);    
}

void loop() {
  int analogValue = analogRead(analogPin);
  Serial.print("Analog Value: ");
  Serial.println(analogValue);

  delay(200); 
} 