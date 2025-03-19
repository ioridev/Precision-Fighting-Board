/**
  * @file    usb_descriptors.h
  * @brief   TinyUSBを使用したXInput USBデスクリプタの定義
  * @author  PFB Team
  */

#ifndef __USB_DESCRIPTORS_H
#define __USB_DESCRIPTORS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tusb.h"

/* Exported constants --------------------------------------------------------*/
// XInputのVIDとPID
#define USB_VID                      0x045E  // Microsoft VID
#define USB_PID                      0x028E  // Xbox 360 Controller PID

// USB最大パワー設定（mA）
#define USB_MAX_POWER_MA             500

// XInput構成設定
#define XINPUT_INTERFACE             0
#define XINPUT_OUT_ENDPOINT          0x01    // PCからの受信エンドポイント
#define XINPUT_IN_ENDPOINT           0x81    // PCへの送信エンドポイント

// XInputパケットサイズ
#define XINPUT_PACKET_SIZE           20

// XInput Configuration Index
#define XINPUT_DESC_CONFIGURATION    0

/* Exported functions prototypes ---------------------------------------------*/
// TinyUSBのコールバックのためのプロトタイプ宣言
void xinput_init(void);
bool xinput_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);
void xinput_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize);

#ifdef __cplusplus
}
#endif

#endif /* __USB_DESCRIPTORS_H */ 