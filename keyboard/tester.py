import keyboard
import time

prev_time = time.time() * 1000000

def on_key_event(e):
    global prev_time
    current_time = time.time() * 1000000
    time_diff = current_time - prev_time
    prev_time = current_time
    print('Time difference:', time_diff, 'μs')

keyboard.on_press(on_key_event)
keyboard.wait()