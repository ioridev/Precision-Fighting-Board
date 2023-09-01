

#include "Gamepad.h"
#include <Arduino.h>



const int Pin_ButtonA = 11;
const int Pin_ButtonB = 12;
const int Pin_ButtonX = 8;
const int Pin_ButtonY = 7;

const int Pin_ButtonLB = 10;
const int Pin_ButtonRB = 9;

const int Pin_ButtonBack = 5;
const int Pin_ButtonStart = 6;

const int Pin_ButtonL3 =  18;
const int Pin_ButtonR3 = 19;

const int Pin_DpadUp = 0;
const int Pin_DpadDown = 1;
const int Pin_DpadLeft = 2;
const int Pin_DpadRight = 3;

const int Pin_ButtonXbox = 4;

const int Pin_TriggerL = 14;
const int Pin_TriggerR = 15;



Gamepad::Gamepad(int debounceMS) {
}

void Gamepad::setup() {

        pinMode(Pin_ButtonA, INPUT_PULLUP);
				pinMode(Pin_ButtonB, INPUT_PULLUP);
				pinMode(Pin_ButtonX, INPUT_PULLUP);
				pinMode(Pin_ButtonY, INPUT_PULLUP);
				pinMode(Pin_ButtonLB, INPUT_PULLUP);
				pinMode(Pin_ButtonRB, INPUT_PULLUP);
				pinMode(Pin_ButtonBack, INPUT_PULLUP);
				pinMode(Pin_ButtonStart, INPUT_PULLUP);
				pinMode(Pin_ButtonL3, INPUT_PULLUP);
				pinMode(Pin_ButtonR3, INPUT_PULLUP);
				pinMode(Pin_DpadUp, INPUT_PULLUP);
				pinMode(Pin_DpadDown, INPUT_PULLUP);
				pinMode(Pin_DpadLeft, INPUT_PULLUP);
				pinMode(Pin_DpadRight, INPUT_PULLUP);
				pinMode(Pin_ButtonXbox, INPUT_PULLUP);


}


void Gamepad::read() {

				state.buttons = 0
								| (digitalRead(Pin_ButtonA) ? GAMEPAD_MASK_B1 : 0)
								| (digitalRead(Pin_ButtonB) ? GAMEPAD_MASK_B2 : 0)
								| (digitalRead(Pin_ButtonX) ? GAMEPAD_MASK_B3 : 0)
								| (digitalRead(Pin_ButtonY) ? GAMEPAD_MASK_B4 : 0)
								| (digitalRead(Pin_ButtonLB) ? GAMEPAD_MASK_A1 : 0)
								| (digitalRead(Pin_ButtonRB) ? GAMEPAD_MASK_A2 : 0)
								| (digitalRead(Pin_ButtonBack) ? GAMEPAD_MASK_S1 : 0)
								| (digitalRead(Pin_ButtonStart) ? GAMEPAD_MASK_S2 : 0)
								| (digitalRead(Pin_ButtonL3) ? GAMEPAD_MASK_L3 : 0)
								| (digitalRead(Pin_ButtonR3) ? GAMEPAD_MASK_R3 : 0)
								| (digitalRead(Pin_DpadUp) ? GAMEPAD_MASK_UP : 0)
								| (digitalRead(Pin_DpadDown) ? GAMEPAD_MASK_DOWN : 0)
								| (digitalRead(Pin_DpadLeft) ? GAMEPAD_MASK_LEFT : 0)
								| (digitalRead(Pin_DpadRight) ? GAMEPAD_MASK_RIGHT : 0)
;




}

