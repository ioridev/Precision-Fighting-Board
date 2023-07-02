#define NUM_BUTTONS 15
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};


void setup()
{
    // set up buttons
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }
}
boolean button0State = false;

void loop()
{
    // Toggle the state of button 0
    button0State = !button0State;

    // read the digital inputs and set the buttons
    for (int i = 1; i < NUM_BUTTONS; i++)
    {
        if (i == 1)
        {
            Joystick.button(1, button0State);
        }
        else
        {
            Joystick.button(i, !digitalRead(BUTTON_PINS[i])); // active low buttons
        }
    }

    delayMicroseconds(125);
}