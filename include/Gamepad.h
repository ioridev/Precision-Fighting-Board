#include <MPG.h>


class Gamepad : public MPG  {
public:
	Gamepad(int debounceMS = 5);
public:
    void read();
    void setup();

};
