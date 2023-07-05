# Precision-Fighting-Board
![FzeHbvuaQAE3pPj](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/afc0e35b-ca20-4fe8-9133-83550cd0358d)


## Description

This project aims to develop the fastest game controller by utilizing the power of [Teensy 4.0](https://www.pjrc.com/store/teensy40.html). We strive to achieve a polling rate of 8000Hz, delivering unparalleled responsiveness for an immersive gaming experience.

**Note: This project is currently under development and not yet finalized.**  

## Features

- High-speed USB communication using [Teensy 4.0](https://www.pjrc.com/store/teensy40.html)
- Targeting an impressive 8000Hz polling rate
- Precise and instantaneous input response
- X-input support

## Installation
Open the PrecisionFightingBoard.TEENSY40.hex file in [Teensyduino 1.53](https://www.pjrc.com/teensy/td_158/TeensyduinoInstall.exe) and write to [Teensy 4.0](https://www.pjrc.com/store/teensy40.html).　
| Pin Number | Button      |
|------------|-------------|
| 0          | A           |
| 1          | B           |
| 2          | X           |
| 3          | Y           |
| 4          | LB          |
| 5          | RB          |
| 6          | Back        |
| 7          | Start       |
| 8          | L3          |
| 9          | R3          |
| 10         | Dpad Up     |
| 11         | Dpad Down   |
| 12         | Dpad Left   |
| 13         | Dpad Right  |
| A4         | Trigger L   |
| A5         | Trigger R   |
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/2e11a9c7-5acc-4e2c-a961-7881e0bbd49f)



## Setting Up the Development Environment
Install Arduino IDE 1.8.13 and Teensyduino 1.53.

Clone this repository and copy the x-input/ArduinoXinput_Teensy/teensy directory to C:\Program Files (x86)\Arduino\hardware.

Open PrecisionFightingBoard.ino with the Arduino IDE, go to Tools, change the USB Type to XInput, and then upload it to the Teensy 4.0.

## Polling rate test results 
I caught the continuous X-input button loop in my Python program and confirmed that it was around 0.125 ms.
![image](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/70222125-6ffb-46e5-9fc4-e5550e8782d6)  
The program used for the test is in Precision-Fighting-Board/x-input/tester and anyone can try it out.

## Todo
- [x] 8000Hz d-input
- [x] 8000Hz Keyboard input
- [x] 8000Hz X-input
- [x] Easy installer
- [ ] Input mode setting
- [X] Gameplay Testing
- [ ] Wingman FGC Testing
- [x] Debounce
- [ ] PS5 Support


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


