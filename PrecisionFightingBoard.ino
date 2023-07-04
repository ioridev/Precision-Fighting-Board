#include <XInput.h>
#include <Bounce2.h>

const int Pin_ButtonA = 0;
const int Pin_ButtonB = 1;
const int Pin_ButtonX = 2;
const int Pin_ButtonY = 3;

const int Pin_ButtonLB = 4;
const int Pin_ButtonRB = 5;

const int Pin_ButtonBack = 6;
const int Pin_ButtonStart = 7;

const int Pin_ButtonL3 = 8;
const int Pin_ButtonR3 = 9;

const int Pin_DpadUp = 10;
const int Pin_DpadDown = 11;
const int Pin_DpadLeft = 12;
const int Pin_DpadRight = 13;

const int Pin_TriggerL = A4;
const int Pin_TriggerR = A5;

Bounce buttonA = Bounce();
Bounce buttonB = Bounce();
Bounce buttonX = Bounce();
Bounce buttonY = Bounce();

Bounce buttonLB = Bounce();
Bounce buttonRB = Bounce();

Bounce buttonBack = Bounce();
Bounce buttonStart = Bounce();

Bounce buttonL3 = Bounce();
Bounce buttonR3 = Bounce();

Bounce dpadUp = Bounce();
Bounce dpadDown = Bounce();
Bounce dpadLeft = Bounce();
Bounce dpadRight = Bounce();

Bounce triggerLeft = Bounce();
Bounce triggerRight = Bounce();

void setup()
{

  pinMode(Pin_TriggerL, INPUT_PULLUP);
  pinMode(Pin_TriggerR, INPUT_PULLUP);

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

  buttonA.attach(Pin_ButtonA, INPUT_PULLUP);
  buttonB.attach(Pin_ButtonB, INPUT_PULLUP);
  buttonX.attach(Pin_ButtonX, INPUT_PULLUP);
  buttonY.attach(Pin_ButtonY, INPUT_PULLUP);

  buttonLB.attach(Pin_ButtonLB, INPUT_PULLUP);
  buttonRB.attach(Pin_ButtonRB, INPUT_PULLUP);

  buttonBack.attach(Pin_ButtonBack, INPUT_PULLUP);
  buttonStart.attach(Pin_ButtonStart, INPUT_PULLUP);

  buttonL3.attach(Pin_ButtonL3, INPUT_PULLUP);
  buttonR3.attach(Pin_ButtonR3, INPUT_PULLUP);

  dpadUp.attach(Pin_DpadUp, INPUT_PULLUP);
  dpadDown.attach(Pin_DpadDown, INPUT_PULLUP);
  dpadLeft.attach(Pin_DpadLeft, INPUT_PULLUP);
  dpadRight.attach(Pin_DpadRight, INPUT_PULLUP);

  triggerLeft.attach(Pin_TriggerL, INPUT_PULLUP);
  triggerRight.attach(Pin_TriggerR, INPUT_PULLUP);

  buttonA.interval(1);
  buttonB.interval(1);
  buttonX.interval(1);
  buttonY.interval(1);

  buttonLB.interval(1);
  buttonRB.interval(1);

  buttonBack.interval(1);
  buttonStart.interval(1);

  buttonL3.interval(1);
  buttonR3.interval(1);

  dpadUp.interval(1);
  dpadDown.interval(1);
  dpadLeft.interval(1);
  dpadRight.interval(1);

  triggerLeft.interval(1);
  triggerRight.interval(1);

  XInput.setAutoSend(false);

  XInput.begin();
}

void loop()
{
  buttonA.update();
  buttonB.update();
  buttonX.update();
  buttonY.update();

  buttonLB.update();
  buttonRB.update();

  buttonBack.update();
  buttonStart.update();

  buttonL3.update();
  buttonR3.update();

  dpadUp.update();
  dpadDown.update();
  dpadLeft.update();
  dpadRight.update();

  triggerLeft.update();
  triggerRight.update();

  XInput.setButton(BUTTON_A, buttonA.read());
  XInput.setButton(BUTTON_B, buttonB.read());
  XInput.setButton(BUTTON_X, buttonX.read());
  XInput.setButton(BUTTON_Y, buttonY.read());

  XInput.setButton(BUTTON_LB, buttonLB.read());
  XInput.setButton(BUTTON_RB, buttonRB.read());

  XInput.setButton(BUTTON_BACK, buttonBack.read());
  XInput.setButton(BUTTON_START, buttonStart.read());

  XInput.setButton(BUTTON_L3, buttonL3.read());
  XInput.setButton(BUTTON_R3, buttonR3.read());

  // SOCD
  if (dpadRight.read() && dpadLeft.read())
  {
    dpadRight.write(false);
    dpadLeft.write(false);
  }
  if (dpadUp.read() && dpadDown.read())
  {
    dpadUp.write(false);
    dpadDown.write(false);
  }

  XInput.setDpad(dpadUp.read(), dpadDown.read(), dpadLeft.read(), dpadRight.read());

  XInput.setButton(TRIGGER_LEFT, triggerLeft.read());
  XInput.setButton(TRIGGER_RIGHT, triggerRight.read());

  XInput.send();
}