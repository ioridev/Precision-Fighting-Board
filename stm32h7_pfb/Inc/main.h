/**
  * @file    main.h
  * @brief   Precision Fighting Board STM32H7 版のメインヘッダーファイル
  * @author  PFB Team
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
// ボタン定義
#define PIN_BUTTON_A        GPIOE, GPIO_PIN_0
#define PIN_BUTTON_B        GPIOE, GPIO_PIN_1
#define PIN_BUTTON_X        GPIOE, GPIO_PIN_2
#define PIN_BUTTON_Y        GPIOE, GPIO_PIN_3

#define PIN_BUTTON_LB       GPIOE, GPIO_PIN_4
#define PIN_BUTTON_RB       GPIOE, GPIO_PIN_5

#define PIN_BUTTON_BACK     GPIOE, GPIO_PIN_6
#define PIN_BUTTON_START    GPIOD, GPIO_PIN_0

#define PIN_BUTTON_L3       GPIOD, GPIO_PIN_1
#define PIN_BUTTON_R3       GPIOD, GPIO_PIN_2

#define PIN_DPAD_UP         GPIOD, GPIO_PIN_3
#define PIN_DPAD_DOWN       GPIOD, GPIO_PIN_4
#define PIN_DPAD_LEFT       GPIOD, GPIO_PIN_5
#define PIN_DPAD_RIGHT      GPIOD, GPIO_PIN_6

#define PIN_BUTTON_XBOX     GPIOD, GPIO_PIN_7

#define PIN_TRIGGER_L       GPIOC, GPIO_PIN_0
#define PIN_TRIGGER_R       GPIOC, GPIO_PIN_1

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */ 