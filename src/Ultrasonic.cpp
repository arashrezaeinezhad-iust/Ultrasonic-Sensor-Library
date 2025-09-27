#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo) {
  trigPin = trig;
  echoPin = echo;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// Read distance (cm or inch)
Ultrasonic::Distance Ultrasonic::readDistance(bool inInches) {
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse (timeout 30 ms)
  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return { -1, "cm" }; // No object detected

  float distanceCm = duration * 0.0343 / 2.0; // speed of sound ~343m/s

  if (inInches) {
    return { distanceCm / 2.54, "inch" };
  }
  return { distanceCm, "cm" };
}

// Check if object is closer than threshold
bool Ultrasonic::isObjectDetected(float thresholdCm) {
  Distance d = readDistance(false);
  if (d.value < 0) return false;
  return (d.value <= thresholdCm);
}

// Read with filtering (average over window)
Ultrasonic::Distance Ultrasonic::readFiltered(unsigned long windowMs, bool inInches) {
  float sum = 0;
  int valid = 0;

  unsigned long startTime = millis();
  while (millis() - startTime < windowMs) {
    Distance d = readDistance(inInches);
    if (d.value > 0) {
      sum += d.value;
      valid++;
    }
    delay(5);
  }

  if (valid == 0) return { -1, inInches ? "inch" : "cm" };

  return { sum / valid, inInches ? "inch" : "cm" };
}
