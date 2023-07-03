from inputs import get_gamepad
import time

prev_time = time.perf_counter() * 1000000
last_event_code = None

while True:
    events = get_gamepad()
    if events:
        event = events[0]
        event_code = (event.ev_type, event.code)
        
        if event_code == ('Sync', 'SYN_REPORT'):
            last_event_code = event_code
        
        if event_code != last_event_code:
            current_time = time.perf_counter() * 1000000
            time_diff = current_time - prev_time
            prev_time = current_time
            print("Time difference:", time_diff, "μs", event_code)
            last_event_code = event_code
