#include <XInput.h>

#define NUM_BUTTONS 15
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

void setup()
{
    // Set up buttons
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }
    XInput.setAutoSend(false);
}

void loop()
{

    // D-pad handling (assuming buttons 10 to 13 are UP, DOWN, LEFT, RIGHT)
    bool up = !digitalRead(BUTTON_PINS[10]);
    bool down = !digitalRead(BUTTON_PINS[11]);
    bool left = !digitalRead(BUTTON_PINS[12]);
    bool right = !digitalRead(BUTTON_PINS[13]);

    XInput.setDpad(up, down, left, right);

    XInput.send();

    delayMicroseconds(125); // 800
}
