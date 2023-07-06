import pygame
import time

# Pygameを初期化
pygame.init()

# ジョイスティックが接続されているか確認
joystick_count = pygame.joystick.get_count()
if joystick_count < 2:
    print("2つ以上のゲームパッドが必要です。")
    exit()

# 2つのゲームパッドを設定
joystick1 = pygame.joystick.Joystick(0)
joystick1.init()

joystick2 = pygame.joystick.Joystick(1)
joystick2.init()

# 最後にボタンが押された時間を保存するための変数
last_pressed_time1 = 0
last_pressed_time2 = 0

# ボタンが押されたかをトラッキングするフラグ
button_pressed1 = False
button_pressed2 = False

print("ボタンを押してください...")

# メインループ
while True:
    # イベントを処理
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN:
            # 押されたボタンと時刻を記録
            if event.joy == 0:
                last_pressed_time1 = time.perf_counter()
                button_pressed1 = True
                print(f"Gamepad 1, Button {event.button} pressed at {last_pressed_time1 * 1000} ms")
            elif event.joy == 1:
                last_pressed_time2 = time.perf_counter()
                button_pressed2 = True
                print(f"Gamepad 2, Button {event.button} pressed at {last_pressed_time2 * 1000} ms")

            # 両方のゲームパッドでボタンが押された場合、レスポンスタイムを比較
            if button_pressed1 and button_pressed2:
                difference = abs(last_pressed_time1 - last_pressed_time2) * 1000
                print(f"Buttons were pressed on both gamepads. Time difference: {difference} ms")
                # フラグをリセット
                button_pressed1 = False
                button_pressed2 = False

