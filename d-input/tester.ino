#define NUM_BUTTONS 15
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

#define NUM_DPAD 4
const uint8_t DPAD_PINS[NUM_DPAD] = {23, 22, 21, 20}; // Up, Right, Down, Left

const int16_t HAT_MAP[16] = {
    -1,  // 0000 All dpad buttons up (CENTERED)
    0,   // 0001 direction UP
    90,  // 0010 direction RIGHT
    45,  // 0011 direction UP RIGHT
    180, // 0100 direction DOWN
    -1,  // 0101 invalid
    135, // 0110 direction DOWN RIGHT
    -1,  // 0111 invalid
    270, // 1000 direction LEFT
    315, // 1001 direction UP LEFT
    -1,  // 1010 invalid
    -1,  // 1011 invalid
    225, // 1100 direction DOWN LEFT
    -1,  // 1101 invalid
    -1,  // 1110 invalid
    -1   // 1111 invalid
};

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