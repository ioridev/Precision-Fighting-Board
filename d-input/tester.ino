
Joystick_ Joystick;

boolean buttonState = false;

void setup()
{
    // Initialize Button 0
    Joystick.begin();
    Joystick.setButtonCount(1);
}

void loop()
{
    // Toggle button state
    buttonState = !buttonState;

    // Update Button 0 state
    Joystick.setButton(0, buttonState);

    // Delay
    delay(500);
}
