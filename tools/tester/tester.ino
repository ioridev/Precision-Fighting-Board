#include <XInput.h>

#define NUM_BUTTONS 16
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

boolean buttonAState = false;

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
    buttonAState = !buttonAState; // Toggle the state
    XInput.setButton(BUTTON_A, buttonAState);

    XInput.send();

    delayMicroseconds(125); // 800
}
