#include <Keyboard.h>

boolean uKeyState = false;

void setup()
{
    // Start Keyboard
    Keyboard.begin();
}

void loop()
{
    uKeyState = !uKeyState; // Toggle the state

    if (uKeyState)
    {
        // Press 'U' key
        Keyboard.press(KEY_U);
    }
    else
    {
        // Release 'U' key
        Keyboard.release(KEY_U);

        // Delay to make the key press noticeable
        delayMicroseconds(125); // 800
    }
}
