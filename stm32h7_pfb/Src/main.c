/**
  * @file    main.c
  * @brief   Precision Fighting Board STM32H7版のメイン処理
  * @author  PFB Team
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "button.h"
#include "xinput.h"
#include "usb_descriptors.h"
#include "tusb.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define BUTTON_COUNT 17   // 管理するボタンの数

// TinyUSB タスクの実行間隔（ミリ秒）
#define TINYUSB_TASK_INTERVAL_MS 1

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
// システムクロック設定用変数
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

// ボタン管理用構造体配列
Button_TypeDef buttons[BUTTON_COUNT];

// USB送信用バッファ
static uint8_t usb_tx_buffer[XINPUT_PACKET_SIZE];

// 前回のTinyUSBタスク実行時間
static uint32_t tusb_task_last_time = 0;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void GPIO_Init(void);
static void Buttons_Init(void);
static void USB_Init(void);
static void USB_Task(void);
static void UpdateButtonStates(void);
static void PrepareXInputReport(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  プログラムのメインエントリポイント
  * @param  なし
  * @retval int (未使用)
  */
int main(void)
{
  // リセット後の初期化
  HAL_Init();
  
  // システムクロックの設定
  SystemClock_Config();
  
  // GPIO初期化
  GPIO_Init();
  
  // ボタン入力の初期化
  Buttons_Init();
  
  // USB初期化
  USB_Init();
  
  // XInput初期化
  XINPUT_Init();
  
  // メインループ
  while (1)
  {
    // TinyUSBタスク処理（定期的に呼び出し）
    USB_Task();
    
    // ボタン状態の更新
    UpdateButtonStates();
    
    // XInputレポート準備と送信
    PrepareXInputReport();
    
    // 短い遅延（ボタンチェック間隔）
    HAL_Delay(1);
  }
}

/**
  * @brief  システムクロックの設定
  * @param  なし
  * @retval なし
  */
static void SystemClock_Config(void)
{
  // STM32H7用の高速クロック設定
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  
  // PLL設定（具体的な値はSTM32H7のデータシートを参照）
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
  // クロック分周設定
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  GPIO初期化
  * @param  なし
  * @retval なし
  */
static void GPIO_Init(void)
{
  // GPIOクロックの有効化
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
}

/**
  * @brief  ボタン入力の初期化
  * @param  なし
  * @retval なし
  */
static void Buttons_Init(void)
{
  // 各ボタンの初期化
  BUTTON_Init(&buttons[0], PIN_BUTTON_A, BUTTON_DEBOUNCE_TIME);        // ボタンA
  BUTTON_Init(&buttons[1], PIN_BUTTON_B, BUTTON_DEBOUNCE_TIME);        // ボタンB
  BUTTON_Init(&buttons[2], PIN_BUTTON_X, BUTTON_DEBOUNCE_TIME);        // ボタンX
  BUTTON_Init(&buttons[3], PIN_BUTTON_Y, BUTTON_DEBOUNCE_TIME);        // ボタンY
  
  BUTTON_Init(&buttons[4], PIN_BUTTON_LB, BUTTON_DEBOUNCE_TIME);       // ボタンLB
  BUTTON_Init(&buttons[5], PIN_BUTTON_RB, BUTTON_DEBOUNCE_TIME);       // ボタンRB
  
  BUTTON_Init(&buttons[6], PIN_BUTTON_BACK, BUTTON_DEBOUNCE_TIME);     // ボタンBACK
  BUTTON_Init(&buttons[7], PIN_BUTTON_START, BUTTON_DEBOUNCE_TIME);    // ボタンSTART
  
  BUTTON_Init(&buttons[8], PIN_BUTTON_L3, BUTTON_DEBOUNCE_TIME);       // ボタンL3
  BUTTON_Init(&buttons[9], PIN_BUTTON_R3, BUTTON_DEBOUNCE_TIME);       // ボタンR3
  
  BUTTON_Init(&buttons[10], PIN_DPAD_UP, BUTTON_DEBOUNCE_TIME);        // DPAD上
  BUTTON_Init(&buttons[11], PIN_DPAD_DOWN, BUTTON_DEBOUNCE_TIME);      // DPAD下
  BUTTON_Init(&buttons[12], PIN_DPAD_LEFT, BUTTON_DEBOUNCE_TIME);      // DPAD左
  BUTTON_Init(&buttons[13], PIN_DPAD_RIGHT, BUTTON_DEBOUNCE_TIME);     // DPAD右
  
  BUTTON_Init(&buttons[14], PIN_BUTTON_XBOX, BUTTON_DEBOUNCE_TIME);    // Xboxボタン
  
  BUTTON_Init(&buttons[15], PIN_TRIGGER_L, BUTTON_DEBOUNCE_TIME);      // 左トリガー
  BUTTON_Init(&buttons[16], PIN_TRIGGER_R, BUTTON_DEBOUNCE_TIME);      // 右トリガー
}

/**
  * @brief  USB初期化
  * @param  なし
  * @retval なし
  */
static void USB_Init(void)
{
  // TinyUSB初期化
  tusb_init();
  
  // TinyUSB用XInput初期化
  xinput_init();
  
  // USB送信バッファ初期化
  memset(usb_tx_buffer, 0, XINPUT_PACKET_SIZE);
}

/**
  * @brief  USB処理タスク（定期的に呼び出し）
  * @param  なし
  * @retval なし
  */
static void USB_Task(void)
{
  // 前回実行からの経過時間を確認
  uint32_t current_time = HAL_GetTick();
  
  // 指定間隔ごとにTinyUSBタスクを実行
  if (current_time - tusb_task_last_time >= TINYUSB_TASK_INTERVAL_MS)
  {
    tusb_task_last_time = current_time;
    
    // TinyUSB内部タスク処理（デバイススタックの処理）
    tud_task();
  }
}

/**
  * @brief  ボタン状態の更新とXInputレポートへの反映
  * @param  なし
  * @retval なし
  */
static void UpdateButtonStates(void)
{
  // すべてのボタンの状態を更新
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    BUTTON_Update(&buttons[i]);
  }
  
  // 各ボタンの状態をXInputレポートに反映
  XINPUT_SetButton(XINPUT_BUTTON_A, BUTTON_Read(&buttons[0]));
  XINPUT_SetButton(XINPUT_BUTTON_B, BUTTON_Read(&buttons[1]));
  XINPUT_SetButton(XINPUT_BUTTON_X, BUTTON_Read(&buttons[2]));
  XINPUT_SetButton(XINPUT_BUTTON_Y, BUTTON_Read(&buttons[3]));
  
  XINPUT_SetButton(XINPUT_BUTTON_LB, BUTTON_Read(&buttons[4]));
  XINPUT_SetButton(XINPUT_BUTTON_RB, BUTTON_Read(&buttons[5]));
  
  XINPUT_SetButton(XINPUT_BUTTON_BACK, BUTTON_Read(&buttons[6]));
  XINPUT_SetButton(XINPUT_BUTTON_START, BUTTON_Read(&buttons[7]));
  
  XINPUT_SetButton(XINPUT_BUTTON_L3, BUTTON_Read(&buttons[8]));
  XINPUT_SetButton(XINPUT_BUTTON_R3, BUTTON_Read(&buttons[9]));
  
  // DPAD状態の設定（SOCD処理はXINPUT_SetDPad内部で行われる）
  XINPUT_SetDPad(
    BUTTON_Read(&buttons[10]),  // 上
    BUTTON_Read(&buttons[11]),  // 下
    BUTTON_Read(&buttons[12]),  // 左
    BUTTON_Read(&buttons[13])   // 右
  );
  
  XINPUT_SetButton(XINPUT_BUTTON_XBOX, BUTTON_Read(&buttons[14]));
  
  // トリガーの設定（デジタル入力なので、押されていれば最大値、そうでなければ0）
  XINPUT_SetTrigger(true, BUTTON_Read(&buttons[15]) ? 255 : 0);   // 左トリガー
  XINPUT_SetTrigger(false, BUTTON_Read(&buttons[16]) ? 255 : 0);  // 右トリガー
  
  // スティックは使用しないのでセンター位置に設定
  XINPUT_SetThumbstick(true, 0, 0);   // 左スティック
  XINPUT_SetThumbstick(false, 0, 0);  // 右スティック
}

/**
  * @brief  XInputレポートを準備して送信
  * @param  なし
  * @retval なし
  */
static void PrepareXInputReport(void)
{
  // XInput関数を呼び出してレポート送信
  XINPUT_SendReport();
  
  // TinyUSBがデバイスとして準備できていて、エンドポイントが利用可能な場合のみ送信
  if (tud_ready() && tud_mounted() && !tud_suspended())
  {
    // 他の転送が進行中でなければ、新しいデータを送信
    if (!tud_xinput_n_busy(0))
    {
      // ここでXInputのデータをTinyUSBに送信（実際の関数名はTinyUSBの実装による）
      // tud_xinput_n_report(0, XINPUT_IN_ENDPOINT, usb_tx_buffer, XINPUT_PACKET_SIZE);
      
      // 注: TinyUSBのXInput実装がない場合、ベンダー固有クラスとして実装する
      // tud_vendor_write(usb_tx_buffer, XINPUT_PACKET_SIZE);
    }
  }
}

/**
  * @brief  エラーハンドラ
  * @param  なし
  * @retval なし
  */
void Error_Handler(void)
{
  // エラー発生時の処理
  // 無限ループでシステムを停止
  while(1)
  {
  }
} 