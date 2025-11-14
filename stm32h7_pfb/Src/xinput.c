/**
  * @file    xinput.c
  * @brief   XInput（Xbox 360コントローラー互換）機能の実装
  * @author  PFB Team
  */

/* Includes ------------------------------------------------------------------*/
#include "xinput.h"
#include "usb_descriptors.h"
#include "main.h"
#include "tusb.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
// XInput レポートサイズ
#define XINPUT_INPUT_REPORT_SIZE     20  // XInputからPCへのレポートサイズ
#define XINPUT_OUTPUT_REPORT_SIZE    6   // PCからXInputへのレポートサイズ

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
// XInput レポート
static XINPUT_Report_TypeDef xinput_report;

// USB送信用バッファ
static uint8_t xinput_tx_buffer[XINPUT_INPUT_REPORT_SIZE];

// USB受信用バッファ
static uint8_t xinput_rx_buffer[XINPUT_OUTPUT_REPORT_SIZE];

/* Private function prototypes -----------------------------------------------*/
// USB Vendor経由のXInput送信（実際の実装はusb_xinput_device.cで行われる）
extern bool tud_xinput_send_report(XINPUT_Report_TypeDef *report);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  XInput機能の初期化
  * @param  なし
  * @retval なし
  */
void XINPUT_Init(void)
{
  // レポート構造体の初期化
  xinput_report.buttons = 0;
  xinput_report.triggerLeft = 0;
  xinput_report.triggerRight = 0;
  xinput_report.thumbLX = 0;
  xinput_report.thumbLY = 0;
  xinput_report.thumbRX = 0;
  xinput_report.thumbRY = 0;
  
  // 送信バッファの初期化
  for (int i = 0; i < XINPUT_INPUT_REPORT_SIZE; i++)
  {
    xinput_tx_buffer[i] = 0;
  }
  
  // 受信バッファの初期化
  for (int i = 0; i < XINPUT_OUTPUT_REPORT_SIZE; i++)
  {
    xinput_rx_buffer[i] = 0;
  }
}

/**
  * @brief  XInputボタンの状態を設定
  * @param  button: ボタンID
  * @param  state: ボタンの状態 (true: 押されている, false: 押されていない)
  * @retval なし
  */
void XINPUT_SetButton(XINPUT_Button_TypeDef button, bool state)
{
  if (state)
  {
    // ボタンがONの場合、対応するビットを立てる
    xinput_report.buttons |= button;
  }
  else
  {
    // ボタンがOFFの場合、対応するビットを下げる
    xinput_report.buttons &= ~button;
  }
}

/**
  * @brief  DPADの状態を設定
  * @param  up: 上ボタンの状態 (true: 押されている, false: 押されていない)
  * @param  down: 下ボタンの状態 (true: 押されている, false: 押されていない)
  * @param  left: 左ボタンの状態 (true: 押されている, false: 押されていない)
  * @param  right: 右ボタンの状態 (true: 押されている, false: 押されていない)
  * @retval なし
  */
void XINPUT_SetDPad(bool up, bool down, bool left, bool right)
{
  // SOCD (Simultaneous Opposite Cardinal Direction) クリーニング
  // 左右同時押しの場合、両方キャンセル
  if (left && right)
  {
    left = false;
    right = false;
  }
  
  // 上下同時押しの場合、両方キャンセル
  if (up && down)
  {
    up = false;
    down = false;
  }
  
  // DPADの状態をセット
  XINPUT_SetButton(XINPUT_BUTTON_DPAD_UP, up);
  XINPUT_SetButton(XINPUT_BUTTON_DPAD_DOWN, down);
  XINPUT_SetButton(XINPUT_BUTTON_DPAD_LEFT, left);
  XINPUT_SetButton(XINPUT_BUTTON_DPAD_RIGHT, right);
}

/**
  * @brief  トリガーの値を設定
  * @param  isLeft: トリガーの選択 (true: 左トリガー, false: 右トリガー)
  * @param  value: トリガーの値 (0-255)
  * @retval なし
  */
void XINPUT_SetTrigger(bool isLeft, uint8_t value)
{
  if (isLeft)
  {
    xinput_report.triggerLeft = value;
  }
  else
  {
    xinput_report.triggerRight = value;
  }
}

/**
  * @brief  スティックの値を設定
  * @param  isLeft: スティックの選択 (true: 左スティック, false: 右スティック)
  * @param  x: X軸の値 (-32768 to 32767)
  * @param  y: Y軸の値 (-32768 to 32767)
  * @retval なし
  */
void XINPUT_SetThumbstick(bool isLeft, int16_t x, int16_t y)
{
  if (isLeft)
  {
    xinput_report.thumbLX = x;
    xinput_report.thumbLY = y;
  }
  else
  {
    xinput_report.thumbRX = x;
    xinput_report.thumbRY = y;
  }
}

/**
  * @brief  XInputレポートをUSB経由で送信
  * @param  なし
  * @retval なし
  */
void XINPUT_SendReport(void)
{
  // TinyUSBのベンダー固有クラスを通じてXInputレポートを送信
  tud_xinput_send_report(&xinput_report);
} 