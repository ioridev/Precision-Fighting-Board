from inputs import get_gamepad
import time

prev_time = time.perf_counter() * 1000000

while True:
    events = get_gamepad()
    for event in events:
        current_time = time.perf_counter() * 1000000
        time_diff = current_time - prev_time
        prev_time = current_time
        print("Time difference:", time_diff, "μs")
        print(event.ev_type, event.code, event.state)
