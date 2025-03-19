/**
  * @file    button.c
  * @brief   ボタン入力のデバウンス処理の実装
  * @author  PFB Team
  */

/* Includes ------------------------------------------------------------------*/
#include "button.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ボタンの初期化
  * @param  button: ボタン状態管理構造体へのポインタ
  * @param  GPIOx: GPIOポート
  * @param  GPIO_Pin: GPIOピン
  * @param  debounce_time: デバウンス時間（ms）
  * @retval なし
  */
void BUTTON_Init(Button_TypeDef* button, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t debounce_time)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  button->GPIOx = GPIOx;
  button->GPIO_Pin = GPIO_Pin;
  button->debounce_time = debounce_time;
  button->last_change = 0;
  button->state = false;
  button->raw_state = false;
  
  // GPIOをプルアップ入力モードに設定
  GPIO_InitStruct.Pin = GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
  
  // 初期状態を読み取り
  button->raw_state = (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET);
  button->state = button->raw_state;
}

/**
  * @brief  ボタンの状態を読み取る（デバウンス処理後）
  * @param  button: ボタン状態管理構造体へのポインタ
  * @retval true: 押されている, false: 押されていない
  */
bool BUTTON_Read(Button_TypeDef* button)
{
  return button->state;
}

/**
  * @brief  ボタンの状態を更新する（デバウンス処理）
  * @param  button: ボタン状態管理構造体へのポインタ
  * @retval なし
  */
void BUTTON_Update(Button_TypeDef* button)
{
  // 現在の生の状態を読み取り（LOW = 押されている, HIGH = 押されていない）
  // GPIO入力がプルアップなので、押されたらLOW（GPIO_PIN_RESET）
  bool current_raw_state = (HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == GPIO_PIN_RESET);
  
  // 生の状態が変わった場合
  if (current_raw_state != button->raw_state)
  {
    button->raw_state = current_raw_state;
    button->last_change = HAL_GetTick();
  }
  
  // デバウンス時間が経過していれば、状態を更新
  if ((HAL_GetTick() - button->last_change) > button->debounce_time)
  {
    button->state = button->raw_state;
  }
} 