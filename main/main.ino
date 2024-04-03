// Constants
#define SERVO 13
#define TRIG 12
#define ECHO 11
#define LIGHT 10
#define BUZZER 9
#define GAS 8
#define DISTANCE_THRESHOLD 50 // centimeters
#define CLOSEDOOR 165
#define OPENDOOR 70

// include servo liberary
#include <Servo.h>

// variables
Servo servo;
int duration, distance;

// used functions
void handleDoor();
void handleLight();
void handleGas();

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO);

  // defining pin modes
  pinMode(LIGHT, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Initializing the serial
  Serial.begin(9600);

  servo.write(CLOSEDOOR);
}

void loop() {
  // handling the door with ultrasonic sensor
  handleDoor();
  // handle the light bulb stuff
  handleLight();
  // handle the gas sensor
  handleGas();
  
  delay(200);
}

void handleGas() {
  if (digitalRead(GAS)) {
    digitalWrite(BUZZER, HIGH);
    return;
  }
  digitalWrite(BUZZER, LOW);
}

void handleLight() {
  if (!Serial.available()) {
    return;
  }
  switch (Serial.read()) {
    case 'o':
      digitalWrite(LIGHT, HIGH);
      break;
    case 'f':
      digitalWrite(LIGHT, LOW);
      break;
    default:
      return;
  }
}


void handleDoor() {
  
  // Send electricity for 10 microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // measure duration of pulse from ECHO pin
  duration = pulseIn(ECHO, HIGH);

  // calculate the distance
  distance = 0.017 * duration;

  // if distance less than DISTANCE_THRESHOLD centimeters
  if (distance < DISTANCE_THRESHOLD) {
    // open the door
    servo.write(OPENDOOR);
    return;
  }
  // make sure the door is closed
  servo.write(CLOSEDOOR);
}