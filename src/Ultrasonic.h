#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic {
  private:
    int trigPin;
    int echoPin;

  public:
    struct Distance {
      float value;
      String unit;
    };

    Ultrasonic(int trig, int echo);

    Distance readDistance(bool inInches = false);
    bool isObjectDetected(float thresholdCm);
    Distance readFiltered(unsigned long windowMs = 100, bool inInches = false);
};

#endif
