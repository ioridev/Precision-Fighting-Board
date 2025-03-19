/**
  * @file    usb_xinput_device.c
  * @brief   TinyUSBを使用したXInputデバイス実装
  * @author  PFB Team
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_descriptors.h"
#include "xinput.h"
#include "tusb.h"
#include <string.h>

/* Private defines -----------------------------------------------------------*/
// XInputレポートの構造
#define XINPUT_REPORT_ID            0
#define XINPUT_REPORT_BUTTONS_LSB   1
#define XINPUT_REPORT_BUTTONS_MSB   2
#define XINPUT_REPORT_TRIGGER_L     3
#define XINPUT_REPORT_TRIGGER_R     4
#define XINPUT_REPORT_THUMB_LX_LSB  5
#define XINPUT_REPORT_THUMB_LX_MSB  6
#define XINPUT_REPORT_THUMB_LY_LSB  7
#define XINPUT_REPORT_THUMB_LY_MSB  8
#define XINPUT_REPORT_THUMB_RX_LSB  9
#define XINPUT_REPORT_THUMB_RX_MSB  10
#define XINPUT_REPORT_THUMB_RY_LSB  11
#define XINPUT_REPORT_THUMB_RY_MSB  12

/* Private variables ---------------------------------------------------------*/
// レポート送信用バッファ
static uint8_t xinput_report_buffer[XINPUT_PACKET_SIZE];

// PCからの振動データ
static uint8_t rumble_l = 0;
static uint8_t rumble_r = 0;

/* Private function prototypes -----------------------------------------------*/
static bool xinput_vendor_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  XInputデバイスの初期化
  * @param  なし
  * @retval なし
  */
void xinput_init(void)
{
  // レポートバッファをクリア
  memset(xinput_report_buffer, 0, sizeof(xinput_report_buffer));
  
  // レポートIDを設定（XInputの場合は0）
  xinput_report_buffer[XINPUT_REPORT_ID] = 0;
}

/**
  * @brief  TinyUSBベンダー固有クラスのコントロール転送コールバック
  * @param  rhport: ルートハブポート番号
  * @param  stage: セットアップ転送のステージ
  * @param  request: USBコントロールリクエスト
  * @retval 処理の成否
  */
static bool xinput_vendor_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request)
{
  // XInput固有のコントロールリクエスト処理
  // ここでは基本的なリクエストのみ実装
  
  // XInputの初期化リクエストなど特殊なリクエストの処理
  if (request->bmRequestType_bit.type == TUSB_REQ_TYPE_VENDOR)
  {
    if (stage == CONTROL_STAGE_SETUP)
    {
      // ベンダー固有リクエストの処理
      tud_control_status(rhport, request);
    }
    return true;
  }
  
  // サポートしていないリクエスト
  return false;
}

/**
  * @brief  TinyUSBベンダー固有クラスのデータ受信完了コールバック
  * @param  itf: インターフェース番号
  * @param  report: 受信データバッファ
  * @param  len: 受信データ長
  * @retval なし
  */
void tud_vendor_rx_cb(uint8_t itf, uint8_t const* report, uint16_t len)
{
  // PCからのレポート（振動データなど）を処理
  if (len >= 8)
  {
    // 振動データの解析
    rumble_l = report[3];  // 左モーター（低周波）
    rumble_r = report[4];  // 右モーター（高周波）
    
    // 振動に関する処理をここに追加（必要に応じて）
    // 例: 振動モーターを駆動するGPIOの設定など
  }
  
  // 次のOUTパケットを受け付ける準備
  tud_vendor_n_read_flush(itf);
}

/**
  * @brief  XInputレポートの送信
  * @param  report: レポート構造体
  * @retval 送信結果
  */
bool tud_xinput_send_report(XINPUT_Report_TypeDef *report)
{
  // TinyUSBが準備できているかチェック
  if (!tud_ready() || !tud_mounted() || tud_suspended())
  {
    return false;
  }
  
  // ベンダー固有エンドポイントがビジー状態でないことを確認
  if (tud_vendor_n_busy(0))
  {
    return false;
  }
  
  // レポートバッファにデータを構成
  xinput_report_buffer[XINPUT_REPORT_ID] = XINPUT_REPORTID_INPUT;
  
  // ボタン情報
  xinput_report_buffer[XINPUT_REPORT_BUTTONS_LSB] = (uint8_t)(report->buttons & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_BUTTONS_MSB] = (uint8_t)((report->buttons >> 8) & 0xFF);
  
  // トリガー情報
  xinput_report_buffer[XINPUT_REPORT_TRIGGER_L] = report->triggerLeft;
  xinput_report_buffer[XINPUT_REPORT_TRIGGER_R] = report->triggerRight;
  
  // 左スティック情報
  xinput_report_buffer[XINPUT_REPORT_THUMB_LX_LSB] = (uint8_t)(report->thumbLX & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_THUMB_LX_MSB] = (uint8_t)((report->thumbLX >> 8) & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_THUMB_LY_LSB] = (uint8_t)(report->thumbLY & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_THUMB_LY_MSB] = (uint8_t)((report->thumbLY >> 8) & 0xFF);
  
  // 右スティック情報
  xinput_report_buffer[XINPUT_REPORT_THUMB_RX_LSB] = (uint8_t)(report->thumbRX & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_THUMB_RX_MSB] = (uint8_t)((report->thumbRX >> 8) & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_THUMB_RY_LSB] = (uint8_t)(report->thumbRY & 0xFF);
  xinput_report_buffer[XINPUT_REPORT_THUMB_RY_MSB] = (uint8_t)((report->thumbRY >> 8) & 0xFF);
  
  // 残りのバイトはパディングまたは予約領域
  for (int i = 13; i < XINPUT_PACKET_SIZE; i++)
  {
    xinput_report_buffer[i] = 0;
  }
  
  // ベンダー固有エンドポイントを通じてデータを送信
  return tud_vendor_n_write(0, xinput_report_buffer, XINPUT_PACKET_SIZE);
}

/* TinyUSB用コールバック関数の実装 */

// ベンダー固有クラスのシステムレベルのコールバック
bool tud_vendor_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request)
{
  return xinput_vendor_control_xfer_cb(rhport, stage, request);
}

// XInputデータ転送完了コールバック
bool xinput_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes)
{
  (void) rhport;
  (void) result;
  (void) xferred_bytes;
  
  // エンドポイントアドレスに基づいて処理
  if (ep_addr == XINPUT_IN_ENDPOINT)
  {
    // INエンドポイント処理（送信完了）
  }
  else if (ep_addr == XINPUT_OUT_ENDPOINT)
  {
    // OUTエンドポイント処理（受信完了）
  }
  
  return true;
}

/**
  * @brief  振動値の取得
  * @param  left: 左モーター値を格納する変数へのポインタ
  * @param  right: 右モーター値を格納する変数へのポインタ
  * @retval なし
  */
void xinput_get_rumble(uint8_t *left, uint8_t *right)
{
  if (left != NULL)
  {
    *left = rumble_l;
  }
  
  if (right != NULL)
  {
    *right = rumble_r;
  }
} 