/**
  * @file    usb_descriptors.c
  * @brief   TinyUSBを使用したXInput USBデスクリプタの実装
  * @author  PFB Team
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_descriptors.h"
#include "tusb.h"

/* Private defines -----------------------------------------------------------*/

/* XInput specific descriptors and constants */
#define XINPUT_SUBCLASS              0x5D
#define XINPUT_PROTOCOL              0x01

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* XInput特有のディスクリプタに必要な構造体定義 */
typedef struct TU_ATTR_PACKED {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdXUSB;
  uint8_t  bType;
  uint8_t  bSubType;
  uint8_t  bMaxInputReportSize;
  uint8_t  bMaxOutputReportSize;
  uint16_t wAlternateProductId;
} microsoft_xinput_descriptor_t;

/* Private variables ---------------------------------------------------------*/

/* XInput Device Descriptor
 * BDevice Class: 0xFF (ベンダー固有)
 * BDevice SubClass: 0x5D (XInput固有)
 * BDevice Protocol: 0x01 (XInput固有)
 */
tusb_desc_device_t const desc_device = {
  .bLength            = sizeof(tusb_desc_device_t),
  .bDescriptorType    = TUSB_DESC_DEVICE,
  .bcdUSB             = 0x0200,
  .bDeviceClass       = 0xFF,
  .bDeviceSubClass    = XINPUT_SUBCLASS,
  .bDeviceProtocol    = XINPUT_PROTOCOL,
  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
  .idVendor           = USB_VID,
  .idProduct          = USB_PID,
  .bcdDevice          = 0x0114,  // Xbox 360コントローラーのバージョン
  .iManufacturer      = 0x01,
  .iProduct           = 0x02,
  .iSerialNumber      = 0x03,
  .bNumConfigurations = 0x01
};

// 言語ID (英語)
uint16_t const desc_string_language[1] = {
  0x0409  // 英語
};

// メーカー名
const char *string_desc_manufacturer = "PFB Team";

// 製品名
const char *string_desc_product = "Precision Fighting Board STM32H7";

// シリアル番号
const char *string_desc_serial = "00000001";

/* XInput構成ディスクリプタ */
uint8_t const desc_configuration[] = {
  // 構成ディスクリプタ
  0x09,                      // bLength
  TUSB_DESC_CONFIGURATION,   // bDescriptorType
  TU_U16_TO_U8S(0x0029),     // wTotalLength
  0x01,                      // bNumInterfaces
  0x01,                      // bConfigurationValue
  0x00,                      // iConfiguration (文字列インデックス)
  0x80,                      // bmAttributes (バスパワード)
  USB_MAX_POWER_MA / 2,      // bMaxPower (単位は2mA)

  // インターフェースディスクリプタ
  0x09,                      // bLength
  TUSB_DESC_INTERFACE,       // bDescriptorType
  XINPUT_INTERFACE,          // bInterfaceNumber
  0x00,                      // bAlternateSetting
  0x02,                      // bNumEndpoints
  0xFF,                      // bInterfaceClass (ベンダー固有)
  XINPUT_SUBCLASS,           // bInterfaceSubClass
  XINPUT_PROTOCOL,           // bInterfaceProtocol
  0x00,                      // iInterface (文字列インデックス)

  // Microsoft XInput固有のディスクリプタ
  0x10,                      // bLength
  TUSB_DESC_CS_INTERFACE,    // bDescriptorType (クラス固有)
  0x00,                      // bcdXUSB[0]
  0x01,                      // bcdXUSB[1]
  0x01,                      // bType
  0x25,                      // bSubType
  0x81,                      // bMaxInputReportSize
  0x01,                      // bMaxOutputReportSize
  0x00,                      // wAlternateProductId[0]
  0x00,                      // wAlternateProductId[1]

  // エンドポイントディスクリプタ（IN - デバイスからホストへ）
  0x07,                      // bLength
  TUSB_DESC_ENDPOINT,        // bDescriptorType
  XINPUT_IN_ENDPOINT,        // bEndpointAddress
  TUSB_XFER_INTERRUPT,       // bmAttributes
  TU_U16_TO_U8S(XINPUT_PACKET_SIZE), // wMaxPacketSize
  0x01,                      // bInterval (1ms)

  // エンドポイントディスクリプタ（OUT - ホストからデバイスへ）
  0x07,                      // bLength
  TUSB_DESC_ENDPOINT,        // bDescriptorType
  XINPUT_OUT_ENDPOINT,       // bEndpointAddress
  TUSB_XFER_INTERRUPT,       // bmAttributes
  TU_U16_TO_U8S(XINPUT_PACKET_SIZE), // wMaxPacketSize
  0x08                       // bInterval (8ms)
};

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* TinyUSB用コールバック関数群 */

// デバイスディスクリプタ取得コールバック
uint8_t const *tud_descriptor_device_cb(void) {
  return (uint8_t const *)&desc_device;
}

// 構成ディスクリプタ取得コールバック
uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
  (void) index;  // 引数未使用の警告を回避
  return desc_configuration;
}

// 文字列ディスクリプタ取得コールバック
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
  static uint16_t desc_str[32];
  uint8_t len;

  // 言語ID確認
  if (langid != desc_string_language[0]) {
    return NULL;
  }

  switch (index) {
    case 0: // 言語文字列
      memcpy(&desc_str[1], desc_string_language, 2);
      len = 1;
      break;

    case 1: // メーカー名
      len = tu_strlen(string_desc_manufacturer);
      for (uint8_t i = 0; i < len; i++) {
        desc_str[i+1] = string_desc_manufacturer[i];
      }
      break;

    case 2: // 製品名
      len = tu_strlen(string_desc_product);
      for (uint8_t i = 0; i < len; i++) {
        desc_str[i+1] = string_desc_product[i];
      }
      break;

    case 3: // シリアル番号
      len = tu_strlen(string_desc_serial);
      for (uint8_t i = 0; i < len; i++) {
        desc_str[i+1] = string_desc_serial[i];
      }
      break;

    default:
      return NULL;
  }

  // Bデスクリプタ先頭バイトはディスクリプタの長さ
  desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * len + 2);

  return desc_str;
}

/* XInput初期化関数 */
void xinput_init(void) {
  // TinyUSBの初期化は別途行う
}

/* XInputデータ転送完了コールバック */
bool xinput_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes) {
  (void) rhport;
  (void) result;
  (void) xferred_bytes;

  // エンドポイントアドレスによってIN/OUTの処理を分ける
  if (ep_addr == XINPUT_IN_ENDPOINT) {
    // INエンドポイント (デバイス→ホスト) の転送完了処理
    // 次のコントローラー状態を送信する準備など
  } else if (ep_addr == XINPUT_OUT_ENDPOINT) {
    // OUTエンドポイント (ホスト→デバイス) の転送完了処理
    // 振動コマンドなどの処理
  }

  return true;
}

/* PCからのレポート受信コールバック */
void xinput_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
  (void) instance;
  (void) report_id;
  (void) report_type;

  // PCからのレポート処理（振動コマンドなど）
  if (bufsize >= 8) {
    // 振動データの処理（XInputは左右の振動値を別々に指定）
    uint8_t left_motor = buffer[3];   // 左振動モーター（低周波）
    uint8_t right_motor = buffer[4];  // 右振動モーター（高周波）
    
    // ここで振動モーターの制御（実装されている場合）
  }
} 