from evdev import InputDevice, categorize, ecodes, KeyEvent

dev = InputDevice('/dev/input/eventX')  # 'X'はデバイスの番号

for event in dev.read_loop():
    if event.type == ecodes.EV_KEY:
        key_event = categorize(event)
        if key_event.keystate == KeyEvent.key_down:
            print('Key pressed:', key_event.keycode)
