# Precision Fighting Board - STM32H7版

このプロジェクトはオリジナルのPrecision Fighting BoardをSTM32H7マイコンで実装したものです。Arduino版から移植することで、コスト削減と機能拡張を目指しています。

## 特徴

- STM32H7（STM32H743VIT6）マイコンを使用
- TinyUSBライブラリによるXInput（Xbox 360コントローラー互換）プロトコル対応
- デバウンス処理を実装して誤入力を防止
- SOCD（Simultaneous Opposite Cardinal Direction）クリーニング対応
- 全ボタン、DPADに対応

## ハードウェア要件

### 必要なコンポーネント

- STM32H7シリーズマイコン（推奨：STM32H743VIT6）
- 8MHz外部クリスタル
- USB Type-Bコネクタ（または使用するコネクタ）
- タクトスイッチ x 17（各種ボタン用）
- 抵抗、コンデンサ等の受動部品

### ピン配置

ボタン類は以下のGPIOに接続されています：

- BUTTON_A: GPIOE, PIN0
- BUTTON_B: GPIOE, PIN1
- BUTTON_X: GPIOE, PIN2
- BUTTON_Y: GPIOE, PIN3
- BUTTON_LB: GPIOE, PIN4
- BUTTON_RB: GPIOE, PIN5
- BUTTON_BACK: GPIOE, PIN6
- BUTTON_START: GPIOD, PIN0
- BUTTON_L3: GPIOD, PIN1
- BUTTON_R3: GPIOD, PIN2
- DPAD_UP: GPIOD, PIN3
- DPAD_DOWN: GPIOD, PIN4
- DPAD_LEFT: GPIOD, PIN5
- DPAD_RIGHT: GPIOD, PIN6
- BUTTON_XBOX: GPIOD, PIN7
- TRIGGER_L: GPIOC, PIN0
- TRIGGER_R: GPIOC, PIN1

## ソフトウェア環境

### ビルド環境

- STM32CubeIDE、またはMakefileベースの環境
- CMake対応（CMakeListsファイル提供）
- STM32 HALライブラリ
- TinyUSBライブラリ（自動的にダウンロードされます）

### インストール方法

1. リポジトリをクローン: `git clone https://github.com/your-username/stm32h7_pfb.git`
2. 必要なライブラリをインストール: STM32 HALドライバーを`Drivers`ディレクトリに配置
3. CMakeでビルド:
   ```
   mkdir build && cd build
   cmake ..
   make
   ```
4. 生成された`.bin`ファイルをSTM32H7にフラッシュ

## プロジェクト構造

```
stm32h7_pfb/
├── Inc/                      # ヘッダーファイル
│   ├── main.h               # メインヘッダー
│   ├── button.h             # ボタン処理
│   ├── xinput.h             # XInput関連
│   ├── usb_descriptors.h    # USB XInputデスクリプタ
│   └── tusb_config.h        # TinyUSB設定
├── Src/                      # ソースファイル
│   ├── main.c               # メイン処理
│   ├── button.c             # ボタン処理実装
│   ├── xinput.c             # XInput実装
│   ├── usb_descriptors.c    # USB XInputデスクリプタ実装
│   └── usb_xinput_device.c  # USB XInputデバイス実装
├── Drivers/                  # STM32ドライバー（要追加）
├── tinyusb/                  # TinyUSBライブラリ（ビルド時自動ダウンロード）
├── CMakeLists.txt            # CMakeビルド設定
└── README.md                 # プロジェクト説明（このファイル）
```

## TinyUSBについて

このプロジェクトでは、USB実装にTinyUSBライブラリを使用しています。TinyUSBは軽量で多機能なUSBスタックで、様々なマイコンに対応しています。

- XInput実装はTinyUSBのベンダー固有クラスを利用
- usb_descriptors.cでUSBデスクリプタを設定
- usb_xinput_device.cでXInputデバイスの具体的な実装

XInput対応により、Windows PCでXbox 360コントローラーとして認識され、多くのゲームで使用可能になっています。

## 使用方法

1. 基板を作成し、STM32H7とボタンを接続
2. ファームウェアをフラッシュ
3. USBケーブルでPCに接続
4. Xbox 360コントローラーとして自動認識される

## カスタマイズ方法

- `main.h`のピン定義でボタン配置変更可能
- `xinput.c`のレポート処理でボタン動作変更可能
- SOCD処理は`xinput.c`の`XINPUT_SetDPad`関数で調整可能
- `usb_descriptors.c`でUSBのVID/PIDなど変更可能

## ライセンス

[MIT License](LICENSE)

## 謝辞

- オリジナルのPrecision Fighting Boardプロジェクト
- nesvera氏のSTM32-X360-xinputプロジェクト
- STマイクロエレクトロニクスのSTM32 HALライブラリ
- TinyUSBプロジェクト (https://github.com/hathach/tinyusb) 