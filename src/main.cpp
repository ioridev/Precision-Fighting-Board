#include <MPG.h>
#include <Bounce2.h>
#include "Gamepad.h"


Gamepad mpg = Gamepad();

void setup()
{
 mpg.setup(); // Runs your custom setup logic
  mpg.read();  // Perform an initial button read so we can set input mode
    InputMode inputMode = mpg.options.inputMode;

    inputMode = INPUT_MODE_XINPUT;
      mpg.options.inputMode = inputMode;
      	setupHardware(mpg.options.inputMode);

}

void loop()
{
	static const uint8_t reportSize = mpg.getReportSize();  // Get report size from Gamepad instance
	static GamepadHotkey hotkey;                            // The last hotkey pressed

	mpg.read();                                             // Read raw inputs
	mpg.debounce();                                         // Run debouncing if enabled
	hotkey = mpg.hotkey();                                  // Check hotkey presses (D-pad mode, SOCD mode, etc.), hotkey enum returned
	mpg.process();                                          // Perform final input processing (SOCD cleaning, LS/RS emulation, etc.)
	sendReport(mpg.getReport(), reportSize);                // Convert and send it!        // Process the raw inputs into a usable state
}