#define NUM_BUTTONS 15
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

#define NUM_DPAD 4
const uint8_t DPAD_PINS[NUM_DPAD] = {23, 22, 21, 20};  // Up, Right, Down, Left

const int16_t HAT_MAP[16] = {
  -1, // 0000 All dpad buttons up (CENTERED)
  0, // 0001 direction UP
  90, // 0010 direction RIGHT
  45, // 0011 direction UP RIGHT
  180, // 0100 direction DOWN
  -1, // 0101 invalid
  135, // 0110 direction DOWN RIGHT
  -1, // 0111 invalid
  270, // 1000 direction LEFT
  315, // 1001 direction UP LEFT
  -1, // 1010 invalid
  -1, // 1011 invalid
  225, // 1100 direction DOWN LEFT
  -1, // 1101 invalid
  -1, // 1110 invalid
  -1 // 1111 invalid
};

void setup() {
  // set up buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  
  // set up dpad
  for (int i = 0; i < NUM_DPAD; i++) {
    pinMode(DPAD_PINS[i], INPUT_PULLUP);
  }
}

void loop() {
  // read the digital inputs and set the buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    Joystick.button(i + 1, !digitalRead(BUTTON_PINS[i]));  // active low buttons
  }

  // read the dpad states
  uint8_t dpad_bits = 0;
  for (unsigned i = 0; i < NUM_DPAD; i++) {
    if (!digitalRead(DPAD_PINS[i])) {  // active low
      dpad_bits |= (1 << i);
    }
  }
  int16_t hatValue = HAT_MAP[dpad_bits];
  Joystick.hat(hatValue);  // Set the hat switch to the calculated angle

 delayMicroseconds(125);
}
