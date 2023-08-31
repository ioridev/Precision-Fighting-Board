#include <MPG.h>


class Gamepad {
public:
	Gamepad(int debounceMS = 5);
public:
    void read();
    void setup();

};
