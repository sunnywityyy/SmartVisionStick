// Include LowPower library
#include <LowPower.h>

// Define pins
const int trigPin = 9;  // Trigger pin of the ultrasonic sensor
const int echoPin = 10; // Echo pin of the ultrasonic sensor
const int buzzerPin = 11; // Pin for the buzzer
const int vibrationMotorPin = 12; // Pin for the vibration motor

// Define variables
long duration;
int distance;
const int alertDistance = 30; // Distance threshold in centimeters

void setup() {
  pinMode(trigPin, OUTPUT); // Set Trigger pin as output
  pinMode(echoPin, INPUT);  // Set Echo pin as input
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  pinMode(vibrationMotorPin, OUTPUT); // Set vibration motor pin as output
  Serial.begin(9600); // Initialize Serial communication at 9600 baud for debugging
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Debugging info
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if distance is less than the threshold
  if (distance > 0 && distance <= alertDistance) {
    digitalWrite(buzzerPin, HIGH); // Turn on buzzer
    digitalWrite(vibrationMotorPin, HIGH); // Turn on vibration motor
    delay(200); // Short alert duration
    digitalWrite(buzzerPin, LOW); // Turn off buzzer
    digitalWrite(vibrationMotorPin, LOW); // Turn off vibration motor
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off buzzer
    digitalWrite(vibrationMotorPin, LOW); // Turn off vibration motor
  }

  // Put Arduino in low-power mode for 1 second
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
}