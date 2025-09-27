# Ultrasonic Sensor Library (Arduino)

This Arduino library provides a simple C++ class for ultrasonic distance sensors 
(SRF04, SRF05, HC-SR04). It supports measuring distances in **centimeters or inches**, 
object detection within a threshold, and filtered readings to reduce noise.

## Features
- Read distance in cm or inches
- True/False object detection based on threshold
- Noise reduction using filtered averaging
- Works with Arduino Uno, ESP32, and other boards

## Example
```cpp
#include <Ultrasonic.h>

Ultrasonic sensor(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  auto d = sensor.readDistance();
  Serial.println(d.value);
  delay(1000);
}
