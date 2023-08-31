#include <MPG.h>
#include <Bounce2.h>
#include "Gamepad.h"


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

Bounce debouncerA = Bounce();
Bounce debouncerB = Bounce();
Bounce debouncerX = Bounce();
Bounce debouncerY = Bounce();

Bounce debouncerLB = Bounce();
Bounce debouncerRB = Bounce();

Bounce debouncerBack = Bounce();
Bounce debouncerStart = Bounce();

Bounce debouncerL3 = Bounce();
Bounce debouncerR3 = Bounce();

Bounce debouncerDpadUp = Bounce();
Bounce debouncerDpadDown = Bounce();
Bounce debouncerDpadLeft = Bounce();
Bounce debouncerDpadRight = Bounce();

Bounce debouncerTriggerL = Bounce();
Bounce debouncerTriggerR = Bounce();

Bounce debouncerXbox = Bounce();

Gamepad mpg = Gamepad();

void setup()
{
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

  pinMode(Pin_TriggerL, INPUT_PULLUP);
  pinMode(Pin_TriggerR, INPUT_PULLUP);

pinMode(Pin_ButtonXbox, INPUT_PULLUP);

  debouncerA.attach(Pin_ButtonA);
  debouncerB.attach(Pin_ButtonB);
  debouncerX.attach(Pin_ButtonX);
  debouncerY.attach(Pin_ButtonY);

  debouncerLB.attach(Pin_ButtonLB);
  debouncerRB.attach(Pin_ButtonRB);

  debouncerBack.attach(Pin_ButtonBack);
  debouncerStart.attach(Pin_ButtonStart);

  debouncerL3.attach(Pin_ButtonL3);
  debouncerR3.attach(Pin_ButtonR3);

  debouncerDpadUp.attach(Pin_DpadUp);
  debouncerDpadDown.attach(Pin_DpadDown);
  debouncerDpadLeft.attach(Pin_DpadLeft);
  debouncerDpadRight.attach(Pin_DpadRight);

  debouncerTriggerL.attach(Pin_TriggerL);
  debouncerTriggerR.attach(Pin_TriggerR);

  debouncerXbox.attach(Pin_ButtonXbox);


  debouncerA.interval(3);
  debouncerB.interval(3);
  debouncerX.interval(3);
  debouncerY.interval(3);

  debouncerLB.interval(3);
  debouncerRB.interval(3);

  debouncerBack.interval(3);
  debouncerStart.interval(3);

  debouncerL3.interval(3);
  debouncerR3.interval(3);

  debouncerDpadUp.interval(3);
  debouncerDpadDown.interval(3);
  debouncerDpadLeft.interval(3);
  debouncerDpadRight.interval(3);

  debouncerTriggerL.interval(3);
  debouncerTriggerR.interval(3);

debouncerXbox.interval(3);
 mpg.setup(); // Runs your custom setup logic
  mpg.read();  // Perform an initial button read so we can set input mode
}

void loop()
{
  debouncerA.update();
  debouncerB.update();
  debouncerX.update();
  debouncerY.update();

  debouncerLB.update();
  debouncerRB.update();

  debouncerBack.update();
  debouncerStart.update();

  debouncerL3.update();
  debouncerR3.update();

  debouncerDpadUp.update();
  debouncerDpadDown.update();
  debouncerDpadLeft.update();
  debouncerDpadRight.update();

  debouncerTriggerL.update();
  debouncerTriggerR.update();

  debouncerXbox.update();

  boolean buttonA = !debouncerA.read();
  boolean buttonB = !debouncerB.read();
  boolean buttonX = !debouncerX.read();
  boolean buttonY = !debouncerY.read();

  boolean buttonLB = !debouncerLB.read();
  boolean buttonRB = !debouncerRB.read();

  boolean buttonBack = !debouncerBack.read();
  boolean buttonStart = !debouncerStart.read();

  boolean buttonL3 = !debouncerL3.read();
  boolean buttonR3 = !debouncerR3.read();

  boolean dpadUp = !debouncerDpadUp.read();
  boolean dpadDown = !debouncerDpadDown.read();
  boolean dpadLeft = !debouncerDpadLeft.read();
  boolean dpadRight = !debouncerDpadRight.read();

  boolean buttonXbox = !debouncerXbox.read();

  // SOCD Cleaning
  if (dpadRight && dpadLeft)
  {
    dpadRight = false;
    dpadLeft = false;
  }

  if (dpadUp && dpadDown)
  {
    dpadUp = false;
    dpadDown = false;
  }

  // XInput.setButton(BUTTON_A, buttonA);
  // XInput.setButton(BUTTON_B, buttonB);
  // XInput.setButton(BUTTON_X, buttonX);
  // XInput.setButton(BUTTON_Y, buttonY);

  // XInput.setButton(BUTTON_LB, buttonLB);
  // XInput.setButton(BUTTON_RB, buttonRB);

  // XInput.setButton(BUTTON_BACK, buttonBack);
  // XInput.setButton(BUTTON_START, buttonStart);

  // XInput.setButton(BUTTON_L3, buttonL3);
  // XInput.setButton(BUTTON_R3, buttonR3);

  // XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

  // boolean triggerLeft = !debouncerTriggerL.read();
  // boolean triggerRight = !debouncerTriggerR.read();

  // XInput.setButton(TRIGGER_LEFT, triggerLeft);
  // XInput.setButton(TRIGGER_RIGHT, triggerRight);

  // XInput.setButton(BUTTON_LOGO, buttonXbox);

  // XInput.send();
}