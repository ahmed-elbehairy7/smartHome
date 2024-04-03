#define BUZZER 13
#define SENSOR 8

void setup() {
    Serial.begin(9600);
}
void loop() {
  handleGas();
}

void handleGas() {
  if (digitalRead(SENSOR)) {
      analogWrite(BUZZER, 0);
      return;
    }
    analogWrite(BUZZER, 255);
}