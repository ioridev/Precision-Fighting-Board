# [Precision-Fighting-Board](https://github.com/ioridev/Precision-Fighting-Board)
![board](https://github.com/ioridev/Precision-Fighting-Board/blob/main/PCB/KiCad%20Files/PrecisionFightingBoard.jpg)

We all need to use this board in 20XX.  
[Discussions](https://github.com/ioridev/Precision-Fighting-Board/discussions)  
## Description

This project aims to develop the fastest game controller by utilizing the power of [Teensy 4.0](https://www.pjrc.com/store/teensy40.html). We strive to achieve a polling rate of 8000Hz, delivering unparalleled responsiveness for an immersive gaming experience.

## Where to Buy
[![Booth](https://asset.booth.pm/assets/booth_logo-cd38e1da31e93676b081bd8f0aca2805f758f514c8e95dc3f1a8aac5e58dffec.svg)](https://iori-giken.booth.pm/)  
Available for purchase on Booth. Buying from this shop directly supports the developers. For international customers, shipping outside of Japan is possible using address forwarding services like Buyee and Tenso.  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/3c6b4f0f-4295-4715-977d-033639ead45e)

[https://iori-giken.booth.pm/](https://iori-giken.booth.pm/)


## Features

- High-speed USB communication using [Teensy 4.0](https://www.pjrc.com/store/teensy40.html)
- Targeting an impressive 8000Hz polling rate
- Precise and instantaneous input response
- X-input support
- No waiting time for debounce

## Installation
Open the PrecisionFightingBoard.TEENSY40.hex file in [Teensyduino 1.53](https://www.pjrc.com/teensy/td_158/TeensyduinoInstall.exe) and write to [Teensy 4.0](https://www.pjrc.com/store/teensy40.html).　
| Pin Number | Button      |
|------------|-------------|
| 0          | Up       |
| 1          | Down   |
| 2          | Left      |
| 3          | Right    |
| 4          | Home   |
| 5          | Back     |
| 6          | Start     |
| 7          | Y           |
| 8          | X           |
| 9          | RB         |
| 10         | LB         |
| 11         | A            |
| 12         | B            |
| 14         | RT         |
| 15         | LT          |
| 18         | L3          |
| 19         | R3          |
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/2e11a9c7-5acc-4e2c-a961-7881e0bbd49f)

### Tips
Not good at soldering or making wires?  
Some models are equipped with pins from the beginning, so you can skip this complicated process by using this type of wire and wire for Brook.  
[Teensy 4.0 Pins](https://www.pjrc.com/store/teensy40_pins.html)

  ![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/300528dc-192d-47a2-9785-b4b2bf61961f)
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/1cecc320-f41a-4cfc-9cd0-ea19618abd21)  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/c7bb9a22-68c5-4f2f-b32c-5b399d36c1a6)  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/05e4e47d-face-4540-9af4-2c46e392f367)

One GND with a pin is missing, so it must be branched with a breadboard or similar.　 

  
Or you can purchase Breakout Board on Amazon.  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/46e5d4a0-9250-4f9b-95c1-419c1af4948c)  
[Breakout Board for Teensy 4.0](https://www.amazon.com/dp/B0C5SXFTC1?_encoding=UTF8&psc=1&ref_=cm_sw_r_cp_ud_dp_3P4ZTVVE18NE8B7TW8SG)
  

## Setting Up the Development Environment
Install Arduino IDE 1.8.13 and Teensyduino 1.53.

Clone this repository and copy the x-input/ArduinoXinput_Teensy/teensy directory to C:\Program Files (x86)\Arduino\hardware.

Open PrecisionFightingBoard.ino with the Arduino IDE, go to Tools, change the USB Type to XInput, and then upload it to the Teensy 4.0.


## Benchmark
### Polling rate test results 
I caught the continuous X-input button loop in my Python program and confirmed that it was around 0.125 ms.  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/70222125-6ffb-46e5-9fc4-e5550e8782d6)  
The program used for the test is in Precision-Fighting-Board/x-input/tester and anyone can try it out.

### Comparison with PicoBoard
tester/gamepad_response_time_comparison.py  
Gamepad 1 is a Precision-Fighting-Board.  
Gamepad 2 is a gp2040-ce  

![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/ea221707-1144-472a-874f-9012942adb8c)  

### Comparison with Brook PS4+ Audio Fighting Board
Gamepad 1 is a Precision-Fighting-Board.  
Gamepad 2 is a Brook AFB  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/0a874cdd-4767-493d-a540-549eb6db1171)


### Use with WingmanFGC　
This is a test on a PC, but when used with WingmanFGC.  
Gamepad 1 is a Precision-Fighting-Board with WingmanFGC.  
Gamepad 2 is a gp2040-ce  
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/9faed4c7-3016-4b31-b0da-01b3768ef684)  
Good results with input lag of up to 5 ms.　　　


## Contributing

Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch.
3. Make your enhancements or bug fixes.
4. Test thoroughly.
5. Submit a pull request detailing your changes.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). Please see the `LICENSE` file for more information.

## Acknowledgements

We would like to express our gratitude to the developers and contributors of Teency 4.0 for their amazing work and support.

