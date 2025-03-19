/**
  * @file    button.h
  * @brief   ボタン入力のデバウンス処理を行うためのヘッダファイル
  * @author  PFB Team
  */

#ifndef __BUTTON_H
#define __BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/**
  * @brief  ボタン状態管理構造体
  */
typedef struct {
  GPIO_TypeDef* GPIOx;      // GPIOポート
  uint16_t GPIO_Pin;        // GPIOピン
  uint32_t debounce_time;   // デバウンス時間（ms）
  uint32_t last_change;     // 最後に状態が変わった時間
  bool state;               // 現在の状態（デバウンス後）
  bool raw_state;           // 生の状態（デバウンス前）
} Button_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define BUTTON_DEBOUNCE_TIME    3   // デフォルトのデバウンス時間(ms)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void BUTTON_Init(Button_TypeDef* button, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t debounce_time);
bool BUTTON_Read(Button_TypeDef* button);
void BUTTON_Update(Button_TypeDef* button);

#ifdef __cplusplus
}
#endif

#endif /* __BUTTON_H */ 