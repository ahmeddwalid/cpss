#include <Arduino.h>

// Pin definitions
#define RED_PIN    D5  // GPIO14
#define YELLOW_PIN D6  // GPIO12
#define GREEN_PIN  D7  // GPIO13

// Timing (milliseconds)
#define GREEN_TIME  10000  // 10 seconds
#define YELLOW_TIME 3000   // 3 seconds
#define RED_TIME    10000  // 10 seconds

// States
enum State {
  GREEN,
  YELLOW,
  RED
};

State currentState = GREEN;
unsigned long stateStartTime = 0;

// Function prototypes
void changeState(State newState);
void setLights(State state);

void setup() {
  Serial.begin(115200);
  Serial.println("\nTraffic Light Started");
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  stateStartTime = millis();
  setLights(GREEN);
}

void loop() {
  unsigned long elapsed = millis() - stateStartTime;
  
  switch(currentState) {
    case GREEN:
      if (elapsed >= GREEN_TIME) {
        changeState(YELLOW);
      }
      break;
      
    case YELLOW:
      if (elapsed >= YELLOW_TIME) {
        changeState(RED);
      }
      break;
      
    case RED:
      if (elapsed >= RED_TIME) {
        changeState(GREEN);
      }
      break;
  }
}

void changeState(State newState) {
  currentState = newState;
  stateStartTime = millis();
  setLights(newState);
  
  Serial.print("Changed to: ");
  Serial.println(newState == GREEN ? "GREEN" : 
                 newState == YELLOW ? "YELLOW" : "RED");
}

void setLights(State state) {
  digitalWrite(RED_PIN, state == RED ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, state == YELLOW ? HIGH : LOW);
  digitalWrite(GREEN_PIN, state == GREEN ? HIGH : LOW);
}
