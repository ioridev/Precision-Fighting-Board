#include <XInput.h>

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

  XInput.setAutoSend(false);

  XInput.begin();
}

void loop()
{
  boolean buttonA = !digitalRead(Pin_ButtonA);
  boolean buttonB = !digitalRead(Pin_ButtonB);
  boolean buttonX = !digitalRead(Pin_ButtonX);
  boolean buttonY = !digitalRead(Pin_ButtonY);

  boolean buttonLB = !digitalRead(Pin_ButtonLB);
  boolean buttonRB = !digitalRead(Pin_ButtonRB);

  boolean buttonBack = !digitalRead(Pin_ButtonBack);
  boolean buttonStart = !digitalRead(Pin_ButtonStart);

  boolean buttonL3 = !digitalRead(Pin_ButtonL3);
  boolean buttonR3 = !digitalRead(Pin_ButtonR3);

  boolean dpadUp = !digitalRead(Pin_DpadUp);
  boolean dpadDown = !digitalRead(Pin_DpadDown);
  boolean dpadLeft = !digitalRead(Pin_DpadLeft);
  boolean dpadRight = !digitalRead(Pin_DpadRight);

  XInput.setButton(BUTTON_A, buttonA);
  XInput.setButton(BUTTON_B, buttonB);
  XInput.setButton(BUTTON_X, buttonX);
  XInput.setButton(BUTTON_Y, buttonY);

  XInput.setButton(BUTTON_LB, buttonLB);
  XInput.setButton(BUTTON_RB, buttonRB);

  XInput.setButton(BUTTON_BACK, buttonBack);
  XInput.setButton(BUTTON_START, buttonStart);

  XInput.setButton(BUTTON_L3, buttonL3);
  XInput.setButton(BUTTON_R3, buttonR3);

  // SOCD
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

  XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

  boolean triggerLeft = !digitalRead(Pin_TriggerL);
  boolean triggerRight = !digitalRead(Pin_TriggerR);

  XInput.setButton(TRIGGER_LEFT, triggerLeft);
  XInput.setButton(TRIGGER_RIGHT, triggerRight);

  XInput.send();
}