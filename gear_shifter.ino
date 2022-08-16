#include "Joystick.h"

const int TOTAL_BUTTON_COUNT = 9;

// 6 speed gears
const int GEAR_1 = 1;
const int GEAR_2 = 0;
const int GEAR_3 = 2;
const int GEAR_4 = 3;
const int GEAR_5 = 4;
const int GEAR_6 = 5;
const int GEAR_REVERSE = 6;

// Sequential gears
const int GEAR_UP = 16;
const int GEAR_DOWN = 10;

// Pin map, should match buttonStates ordering
const int BUTTON_MAP [TOTAL_BUTTON_COUNT] = {
  GEAR_1, GEAR_2, GEAR_3,
  GEAR_4, GEAR_5, GEAR_6,
  GEAR_REVERSE, GEAR_UP, GEAR_DOWN
};

// 12 Digital pins, should match BUTTON_MAP ordering
int buttonStates [12] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};

Joystick_ Joystick(
    JOYSTICK_DEFAULT_REPORT_ID,
    JOYSTICK_TYPE_JOYSTICK,
    TOTAL_BUTTON_COUNT,
    0,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
);

/**
 * @brief Initialize pins for shifter
 */
void initPins() {
  // Init digital pins
  for (int pinNumber : BUTTON_MAP) {
    // Default value is HIGH
    pinMode(pinNumber, INPUT_PULLUP);
  }
}

/**
 * @brief Iterate an array of pins and set a gear
 */
void setTransmission() {
  int buttonIdx = 0;
  
  for (int i = 0; i < TOTAL_BUTTON_COUNT; i++) {
    int value = !digitalRead(BUTTON_MAP[i]);
    
    // New button state
    if (value != buttonStates[i]) {
      Joystick.setButton(i, value);
      buttonStates[i] = value;
      break;
    }
  }
}

void setup() {
  // Init pins
  initPins();

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  setTransmission();
  delay(50);
}
