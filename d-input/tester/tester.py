import joystickapi  
import msvcrt  
import time  

print("start")  

num = joystickapi.joyGetNumDevs()  
ret, caps, startinfo = False, None, None  
for id in range(num):  
  ret, caps = joystickapi.joyGetDevCaps(id)  
  if ret:  
    print("gamepad detected: " + caps.szPname)  
    ret, startinfo = joystickapi.joyGetPosEx(id)  
    break  
else:  
  print("no gamepad detected")  

run = ret  
prev_time = time.perf_counter() * 1000000
while run:  
  if msvcrt.kbhit() and msvcrt.getch() == chr(27).encode(): # detect ESC  
    run = False  

  ret, info = joystickapi.joyGetPosEx(id)  
  if ret:  
    current_time = time.perf_counter() * 1000000
    time_diff = current_time - prev_time
    prev_time = current_time
    print("Time difference:", time_diff, "μs")  # print the time difference

   
print("end")  
