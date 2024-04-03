#define LIGHT 7
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!Serial.available()) {
    return;
  }
  if (Serial.read() == 'o') {
    digitalWrite(LIGHT, 1);
  }
  else {
    digitalWrite(LIGHT, 0);
  }
}
