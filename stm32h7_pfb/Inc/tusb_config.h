/**
  * @file    tusb_config.h
  * @brief   TinyUSBの設定ファイル
  * @author  PFB Team
  */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

// RHPORTはSTM32のUSBポート番号に依存
#ifndef BOARD_TUD_RHPORT
#define BOARD_TUD_RHPORT     0
#endif

#ifndef BOARD_TUD_MAX_SPEED
#define BOARD_TUD_MAX_SPEED  OPT_MODE_FULL_SPEED
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// USBスタックサイズ定義
#define CFG_TUSB_OS               OPT_OS_NONE
#define CFG_TUSB_MCU              OPT_MCU_STM32H7
#define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_DEVICE | BOARD_TUD_MAX_SPEED)

// STM32H7向けに推奨される設定
#define CFG_TUSB_MEM_SECTION      __attribute__((section(".RAM_D1")))
#define CFG_TUSB_MEM_ALIGN        __attribute__((aligned(4)))

// デバッグレベル設定
#define CFG_TUSB_DEBUG            0

// 使用するCDC, HID, MSC, VENDORクラスの数
#define CFG_TUD_CDC               0
#define CFG_TUD_MSC               0
#define CFG_TUD_HID               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_VENDOR            1  // ベンダー固有クラスとしてXInputを実装

//--------------------------------------------------------------------
// VENDOR SPECIFIC (Custom XInput)
//--------------------------------------------------------------------

// EPサイズ
#define CFG_TUD_ENDPOINT0_SIZE    64

// ベンダー固有のバッファサイズ
#define CFG_TUD_VENDOR_RX_BUFSIZE 64
#define CFG_TUD_VENDOR_TX_BUFSIZE 64

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */ 