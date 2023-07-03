#include <XInput.h>

#define NUM_BUTTONS 22
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 15, 16, 17, 18, 19, 20, 21, 22};

void setup()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  XInput.setAutoSend(false);
}

void loop()
{
  bool up = !digitalRead(BUTTON_PINS[10]);
  bool down = !digitalRead(BUTTON_PINS[11]);
  bool left = !digitalRead(BUTTON_PINS[14]);
  bool right = !digitalRead(BUTTON_PINS[15]);

  XInput.setDpad(up, down, left, right);

  XInput.setButton(BUTTON_A, !digitalRead(BUTTON_PINS[0]));
  XInput.setButton(BUTTON_B, !digitalRead(BUTTON_PINS[1]));
  XInput.setButton(BUTTON_X, !digitalRead(BUTTON_PINS[2]));
  XInput.setButton(BUTTON_Y, !digitalRead(BUTTON_PINS[3]));

  XInput.setButton(BUTTON_LB, !digitalRead(BUTTON_PINS[4]));
  XInput.setButton(BUTTON_RB, !digitalRead(BUTTON_PINS[5]));
  XInput.setTrigger(TRIGGER_LEFT, !digitalRead(BUTTON_PINS[6]));  // L2
  XInput.setTrigger(TRIGGER_RIGHT, !digitalRead(BUTTON_PINS[7])); // R2
  XInput.setButton(BUTTON_BACK, !digitalRead(BUTTON_PINS[8]));    // SELECT
  XInput.setButton(BUTTON_START, !digitalRead(BUTTON_PINS[9]));
  XInput.setButton(BUTTON_L3, !digitalRead(BUTTON_PINS[18]));
  XInput.setButton(BUTTON_R3, !digitalRead(BUTTON_PINS[19]));

  XInput.send();

  delayMicroseconds(125); // 800
}
