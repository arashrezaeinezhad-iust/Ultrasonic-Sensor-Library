#include <Ultrasonic.h>

Ultrasonic sensor(9, 10); // TRIG = 9, ECHO = 10

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read distance in cm
  Ultrasonic::Distance d1 = sensor.readDistance();
  Serial.print("Distance: ");
  Serial.print(d1.value, 2);
  Serial.println(" " + d1.unit);

  // Object detection
  if (sensor.isObjectDetected(30)) {
    Serial.println("⚠️ Object detected within 30 cm!");
  } else {
    Serial.println("No object within 30 cm");
  }

  // Filtered reading (average over 100 ms)
  Ultrasonic::Distance d2 = sensor.readFiltered(100, false);
  Serial.print("Filtered: ");
  Serial.print(d2.value, 2);
  Serial.println(" " + d2.unit);

  delay(1000);
}
