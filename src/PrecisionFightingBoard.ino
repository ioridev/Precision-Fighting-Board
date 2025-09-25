#include <XInput.h>
#include <Bounce2.h>

namespace {

constexpr int kHallKeyCount = 4;
constexpr int kHallPins[kHallKeyCount] = {14, 15, 16, 17};
constexpr float kHallTriggerRatio = 0.05f;   // 0.2 mm / 4 mm travel
constexpr float kHallReleaseRatio = 0.10f;   // 0.4 mm / 4 mm travel
constexpr int kHallCalibrationSamples = 200;
constexpr int kHallCalibrationDelayMs = 1;
constexpr int kHallMinimumRange = 60;
constexpr int kHallDefaultRange = 160;
constexpr int kHallMinimumTrigger = 6;
constexpr int kHallReleaseSeparation = 4;

enum HallDirection {
  HallUp = 0,
  HallDown,
  HallLeft,
  HallRight
};

struct HallKey {
  int pin;
  int minValue;
  int maxValue;
  int trigger;
  int release;
  int value;
  int reference;
  bool pressed;
  bool hasFullTravel;
};

HallKey hallKeys[kHallKeyCount];

void updateHallThresholds(HallKey &key) {
  int range = key.maxValue - key.minValue;
  if (range < kHallMinimumRange) {
    range = key.hasFullTravel ? kHallMinimumRange : kHallDefaultRange;
  }

  int trigger = static_cast<int>(range * kHallTriggerRatio);
  if (trigger < kHallMinimumTrigger) {
    trigger = kHallMinimumTrigger;
  }

  int release = static_cast<int>(range * kHallReleaseRatio);
  if (release <= trigger) {
    release = trigger + kHallReleaseSeparation;
  }

  if (release > range) {
    release = range;
  }

  key.trigger = trigger;
  key.release = release;
}

void initHallKey(int index) {
  HallKey &key = hallKeys[index];
  key.pin = kHallPins[index];
  pinMode(key.pin, INPUT);

  int minValue = 4095;
  int maxValue = 0;

  for (int i = 0; i < kHallCalibrationSamples; ++i) {
    int reading = analogRead(key.pin);
    if (reading < minValue) {
      minValue = reading;
    }
    if (reading > maxValue) {
      maxValue = reading;
    }
    delay(kHallCalibrationDelayMs);
  }

  key.minValue = minValue;
  key.maxValue = maxValue;
  key.reference = maxValue;
  key.value = maxValue;
  key.pressed = false;
  key.hasFullTravel = false;

  const int cushion = (maxValue - minValue) * 2;
  key.minValue = max(0, key.minValue - cushion);
  key.maxValue = min(4095, key.maxValue + cushion);
  key.reference = key.maxValue;

  updateHallThresholds(key);
}

void initHallKeys() {
  for (int i = 0; i < kHallKeyCount; ++i) {
    initHallKey(i);
  }
}

void balanceHallKey(HallKey &key) {
  if (key.pressed) {
    if (key.value < key.minValue) {
      key.minValue = key.value;
      key.hasFullTravel = true;
      updateHallThresholds(key);
    }
  } else {
    if (key.value > key.maxValue) {
      key.maxValue = key.value;
      key.reference = key.maxValue;
      updateHallThresholds(key);
    }
    if (key.value < key.minValue) {
      key.minValue = key.value;
      updateHallThresholds(key);
    }
  }
}

bool processHallKey(HallKey &key) {
  key.value = analogRead(key.pin);
  balanceHallKey(key);

  if (!key.pressed) {
    if (key.value <= key.reference - key.trigger) {
      key.pressed = true;
    }
  } else {
    if (key.value >= key.reference - key.release) {
      key.pressed = false;
      key.reference = key.maxValue;
    }
  }

  return key.pressed;
}

void updateHallKeys() {
  for (int i = 0; i < kHallKeyCount; ++i) {
    processHallKey(hallKeys[i]);
  }
}

} // namespace

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

const int Pin_DpadUp = kHallPins[HallUp];
const int Pin_DpadDown = kHallPins[HallDown];
const int Pin_DpadLeft = kHallPins[HallLeft];
const int Pin_DpadRight = kHallPins[HallRight];

const int Pin_ButtonXbox = 4;

const int Pin_TriggerL = 20;
const int Pin_TriggerR = 21;

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

Bounce debouncerTriggerL = Bounce();
Bounce debouncerTriggerR = Bounce();

Bounce debouncerXbox = Bounce();

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

  debouncerTriggerL.interval(3);
  debouncerTriggerR.interval(3);

  debouncerXbox.interval(3);

  analogReadResolution(12);
  initHallKeys();

  XInput.setAutoSend(false);
  XInput.begin();
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

  debouncerTriggerL.update();
  debouncerTriggerR.update();

  debouncerXbox.update();

  updateHallKeys();

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

  boolean dpadUp = hallKeys[HallUp].pressed;
  boolean dpadDown = hallKeys[HallDown].pressed;
  boolean dpadLeft = hallKeys[HallLeft].pressed;
  boolean dpadRight = hallKeys[HallRight].pressed;

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

  XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

  boolean triggerLeft = !debouncerTriggerL.read();
  boolean triggerRight = !debouncerTriggerR.read();

  XInput.setButton(TRIGGER_LEFT, triggerLeft);
  XInput.setButton(TRIGGER_RIGHT, triggerRight);

  XInput.setButton(BUTTON_LOGO, buttonXbox);

  XInput.send();
}

