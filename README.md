# Precision-Fighting-Board
![FzeHbvuaQAE3pPj](https://github.com/ioridev/Precision-Fighting-Board/assets/41247249/afc0e35b-ca20-4fe8-9133-83550cd0358d)


## Description

This project aims to develop the fastest game controller by utilizing the power of Teency 4.0. We strive to achieve a polling rate of 8000Hz, delivering unparalleled responsiveness for an immersive gaming experience.

**Note: This project is currently under development and not yet finalized.**  
At this time, to play sf6 at 8000 Hz, you must use keyboard input or D input via Steam-Input. However, the polling rate of Steam-Ipunt has not been tested.


## Features

- High-speed USB communication using Teency 4.0
- Targeting an impressive 8000Hz polling rate
- Precise and instantaneous input response
- Designed for ultimate gaming performance

## Installation
Install the Arduino IDE 1.8.13 and Teensyduino 1.53.

[https://github.com/dmadison/ArduinoXInput
](https://github.com/dmadison/ArduinoXInput_Teensy)

Each endpoint has an interval number. Set it to 1 for maximum polling rate.
For example, on the joystick interface you'll find these lines in teensy4/usb_desc.h.
```
  #define JOYSTICK_INTERFACE    3       // Joystick
  #define JOYSTICK_ENDPOINT     6
  #define JOYSTICK_SIZE         12      //  12 = normal, 64 = extreme joystick
  #define JOYSTICK_INTERVAL     2
```
## Todo
- [x] 8000Hz d-input
- [x] 8000Hz Keyboard input
- [ ] 8000Hz X-input
- [ ] d-input + Steam input 8000hz test
- [ ] Easy installer
- [ ] Gameplay Testing
- [ ] Wingman FGC Testing
- [ ] Bounce


## Usage


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


