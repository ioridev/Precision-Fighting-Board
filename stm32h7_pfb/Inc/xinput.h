/**
  * @file    xinput.h
  * @brief   XInput（Xbox 360コントローラー互換）機能を実装するためのヘッダファイル
  * @author  PFB Team
  */

#ifndef __XINPUT_H
#define __XINPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/**
  * @brief  XInput ボタン ID 定義
  */
typedef enum {
  XINPUT_BUTTON_DPAD_UP    = 0x0001,
  XINPUT_BUTTON_DPAD_DOWN  = 0x0002,
  XINPUT_BUTTON_DPAD_LEFT  = 0x0004,
  XINPUT_BUTTON_DPAD_RIGHT = 0x0008,
  XINPUT_BUTTON_START      = 0x0010,
  XINPUT_BUTTON_BACK       = 0x0020,
  XINPUT_BUTTON_L3         = 0x0040,
  XINPUT_BUTTON_R3         = 0x0080,
  XINPUT_BUTTON_LB         = 0x0100,
  XINPUT_BUTTON_RB         = 0x0200,
  XINPUT_BUTTON_XBOX       = 0x0400,
  XINPUT_BUTTON_UNUSED     = 0x0800,
  XINPUT_BUTTON_A          = 0x1000,
  XINPUT_BUTTON_B          = 0x2000,
  XINPUT_BUTTON_X          = 0x4000,
  XINPUT_BUTTON_Y          = 0x8000
} XINPUT_Button_TypeDef;

/**
  * @brief  XInput レポート構造体
  */
typedef struct {
  uint16_t buttons;     // ボタン状態のビットマスク
  uint8_t triggerLeft;  // 左トリガー値 (0-255)
  uint8_t triggerRight; // 右トリガー値 (0-255)
  int16_t thumbLX;      // 左スティックX (-32768 to 32767)
  int16_t thumbLY;      // 左スティックY (-32768 to 32767)
  int16_t thumbRX;      // 右スティックX (-32768 to 32767)
  int16_t thumbRY;      // 右スティックY (-32768 to 32767)
} XINPUT_Report_TypeDef;

/* Exported constants --------------------------------------------------------*/
// XInput USB定数
#define XINPUT_VID                  0x045E  // Microsoft ベンダーID
#define XINPUT_PID                  0x028E  // Xbox 360 コントローラーのプロダクトID

// XInput レポート定数
#define XINPUT_REPORTID_INPUT       0x00
#define XINPUT_REPORTID_OUTPUT      0x01

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void XINPUT_Init(void);
void XINPUT_SetButton(XINPUT_Button_TypeDef button, bool state);
void XINPUT_SetTrigger(bool isLeft, uint8_t value);
void XINPUT_SetThumbstick(bool isLeft, int16_t x, int16_t y);
void XINPUT_SendReport(void);

// DPADの特別な関数
void XINPUT_SetDPad(bool up, bool down, bool left, bool right);

#ifdef __cplusplus
}
#endif

#endif /* __XINPUT_H */ 