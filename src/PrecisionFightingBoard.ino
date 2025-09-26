#include <XInput.h>
#include <Bounce2.h>

namespace {

constexpr int kHallKeyCount = 4; // 上下左右の4方向のみを監視するため4個
constexpr int kHallPins[kHallKeyCount] = {14, 15, 16, 17}; // Teensy 4.x のA0〜A3を移動キーに割り当て済み
constexpr int kHallBaselineSamples = 128; // 起動時に約128msかけてアイドル電圧を平均化し安定値を得る
constexpr int kHallSampleDelayMs = 1; // サンプル間隔を1msにして電源ノイズを平均化
constexpr int kHallFilterWindow = 8; // 8サンプルの移動平均で瞬間ノイズを平滑化
constexpr int kHallNoiseMargin = 60; // ロガーで確認した±50程度のゆらぎに安全マージン10を足した閾値
constexpr int kHallMinStrokeCounts = 200; // フルストローク判定を200カウント以上にして、有意な押下のみ学習
constexpr int kHallDefaultTriggerDelta = 220; // まだ学習前でもノイズに負けない固定閾値（約0.2mm相当）
constexpr int kHallDefaultReleaseDelta = 180; // リリースはトリガより少し小さい差分で戻りを保証

constexpr float kHallTravelMm[kHallKeyCount] = {4.0f, 4.0f, 4.0f, 4.0f}; // 設計上の可動距離4mmを方向別に設定
constexpr float kHallTriggerMm[kHallKeyCount] = {0.2f, 0.2f, 0.2f, 0.2f}; // 0.2mmでオンにしたい要求仕様
constexpr float kHallReleaseMm[kHallKeyCount] = {0.4f, 0.4f, 0.4f, 0.4f}; // 0.4mmまで戻ったらオフにするためのヒステリシス

enum HallDirection {
  HallUp = 0,
  HallDown,
  HallLeft,
  HallRight
};

struct HallKey {
  int pin;
  uint8_t index;
  int baseline;
  int filtered;
  bool pressed;
  bool calibrated;
  int strokeMin;
  int triggerDelta;
  int releaseDelta;
};

HallKey hallKeys[kHallKeyCount];

void calibrateHallKey(HallKey &key) {
  long accumulator = 0;
  for (int i = 0; i < kHallBaselineSamples; ++i) {
    accumulator += analogRead(key.pin);
    delay(kHallSampleDelayMs);
  }

  key.baseline = accumulator / kHallBaselineSamples;
  key.filtered = key.baseline;
  key.pressed = false;
  key.calibrated = false;
  key.strokeMin = key.baseline;
  key.triggerDelta = kHallDefaultTriggerDelta;
  key.releaseDelta = kHallDefaultReleaseDelta;
}

void calibrateHallKeys() {
  for (int i = 0; i < kHallKeyCount; ++i) {
    HallKey &key = hallKeys[i];
    key.pin = kHallPins[i];
    key.index = static_cast<uint8_t>(i);
    pinMode(key.pin, INPUT);
    calibrateHallKey(key);
  }
}

bool processHallKey(HallKey &key) {
  int reading = analogRead(key.pin);
  key.filtered = ((key.filtered * (kHallFilterWindow - 1)) + reading) / kHallFilterWindow;

  if (!key.pressed) {
    if (key.filtered <= key.baseline - key.triggerDelta) {
      key.pressed = true;
      key.strokeMin = key.filtered;
    } else {
      key.strokeMin = key.baseline;
    }
  } else {
    if (key.filtered >= key.baseline - key.releaseDelta) {
      key.pressed = false;
      if (!key.calibrated) {
        int strokeDepth = key.baseline - key.strokeMin;
        if (strokeDepth >= kHallMinStrokeCounts) {
          float countsPerMm = strokeDepth / kHallTravelMm[key.index];
          int trigger = static_cast<int>(countsPerMm * kHallTriggerMm[key.index] + kHallNoiseMargin);
          int release = static_cast<int>(countsPerMm * kHallReleaseMm[key.index] + kHallNoiseMargin / 2);
          if (trigger < kHallDefaultTriggerDelta) {
            trigger = kHallDefaultTriggerDelta;
          }
          if (release >= trigger) {
            release = trigger - kHallNoiseMargin / 2;
          }
          if (release < kHallDefaultReleaseDelta / 2) {
            release = kHallDefaultReleaseDelta / 2;
          }
          key.triggerDelta = trigger;
          key.releaseDelta = release;
          key.calibrated = true;
          key.strokeMin = key.baseline;
        } else {
          key.strokeMin = key.baseline;
        }
      }
    }
    if (key.filtered < key.strokeMin) {
      key.strokeMin = key.filtered;
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

const int Pin_ButtonA = 11; // 基板上でAボタンがTeensyピン11へ配線されている
const int Pin_ButtonB = 12; // Bボタン信号がピン12に配線されている
const int Pin_ButtonX = 8; // Xボタンはピン8に引き出されている
const int Pin_ButtonY = 7; // Yボタンはピン7に割り当て

const int Pin_ButtonLB = 10; // LBボタンの配線先がピン10
const int Pin_ButtonRB = 9;  // RBボタンの配線先がピン9

const int Pin_ButtonBack = 5; // Backボタンはピン5に配線
const int Pin_ButtonStart = 6; // Startボタンはピン6に配線

const int Pin_ButtonL3 =  18; // L3スイッチはピン18に接続
const int Pin_ButtonR3 = 19; // R3スイッチはピン19に接続

const int Pin_DpadUp = kHallPins[HallUp];     // A0 / pin14 を上方向センサに使用
const int Pin_DpadDown = kHallPins[HallDown]; // A1 / pin15 を下方向センサに使用
const int Pin_DpadLeft = kHallPins[HallLeft]; // A2 / pin16 を左方向センサに使用
const int Pin_DpadRight = kHallPins[HallRight]; // A3 / pin17 を右方向センサに使用

const int Pin_ButtonXbox = 4; // Xboxガイドボタンはピン4に配線

const int Pin_TriggerL = 20; // LTスイッチは干渉しないピン20へ移設
const int Pin_TriggerR = 21; // RTスイッチはピン21へ移設

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
  calibrateHallKeys();

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
