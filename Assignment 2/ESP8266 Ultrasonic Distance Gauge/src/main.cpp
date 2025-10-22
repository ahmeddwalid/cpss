/*
 * ESP8266 Proximity Distance Meter with NewPing Library
 * HC-SR04 Ultrasonic Sensor with 4 LED Visual Feedback
 * Uses median filter for improved accuracy
 * Author: Ahmed Walid
 * Date: October 2025
 */


#include <Arduino.h>
#include <NewPing.h>


// HC-SR04 Ultrasonic Sensor Pins
#define TRIGGER_PIN 12  // D6 on NodeMCU
#define ECHO_PIN 14     // D5 on NodeMCU


// LED Pins
const int LED1 = 5;   // D1 on NodeMCU - Nearest distance indicator
const int LED2 = 4;   // D2 on NodeMCU
const int LED3 = 0;   // D3 on NodeMCU
const int LED4 = 2;   // D4 on NodeMCU - Farthest distance indicator


// Distance thresholds in cm
const int DISTANCE_VERY_FAR = 50;    // All 4 LEDs lit when distance > 50cm
const int DISTANCE_FAR = 30;         // 3 LEDs lit when distance 30-50cm
const int DISTANCE_MEDIUM = 15;      // 2 LEDs lit when distance 15-30cm
// 1 LED lit when distance < 15cm


#define MAX_DISTANCE 400             // The NewPing library constructor requires a compile time constant (cm)
const int MEDIAN_ITERATIONS = 5;     // Number of samples for calculating the median
const int MEASUREMENT_DELAY = 100;   // (ms)

int distance;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


// Function prototypes
void updateLEDs(int dist);
void turnOffAllLEDs();


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  turnOffAllLEDs(); // Start with LEDs OFF
}


void loop() {
  // Measure distance using NewPing with median filter
  // ping_median takes multiple samples, removes invalid readings, and returns median
  distance = sonar.ping_cm(MAX_DISTANCE);
  
  if (MEDIAN_ITERATIONS > 1) {
    distance = sonar.ping_median(MEDIAN_ITERATIONS);
    distance = sonar.convert_cm(distance);  // Convert from microseconds to centimeters
  }
  
  // Handle invalid readings (0 means out of range or no echo)
  if (distance == 0) {
    turnOffAllLEDs();
  } else {
    updateLEDs(distance);
  }
  
  delay(MEASUREMENT_DELAY); // Wait before next measurement
}

void updateLEDs(int dist) {
  if (dist > DISTANCE_VERY_FAR) {
    // Object is very far: All 4 LEDs ON
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    
  } else if (dist > DISTANCE_FAR && dist <= DISTANCE_VERY_FAR) {
    // Object is far: 3 LEDs ON
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    
  } else if (dist > DISTANCE_MEDIUM && dist <= DISTANCE_FAR) {
    // Object is at medium distance: 2 LEDs ON
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    
  } else {
    // Object is near: 1 LED ON
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
}

void turnOffAllLEDs() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}
