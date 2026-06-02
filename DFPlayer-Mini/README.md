# DFPlayer Mini

DFRobot MP3 player module for Arduino / ESP32

<br>

## Hardware

- ESP32 board
- DFPlayer Mini module
- Speaker x 1
- Capacitor x 1 (optional)

<br>

## Software

- **Arduino IDE**
  - Library：[**DFRobotDFPlayerMini**](https://github.com/DFRobot/DFRobotDFPlayerMini)

<br>

## Reminds !!

### Naming rule

- Folders: 00 - 99

- Files: 000 - 999

In the second reference video, you can find the detail of naming rule for folder and files. This is very important because if the naming rule is not followed, the ESP might not be able to read the files correctly!!

<br>

## Wiring

| DFPlayer |  ESP32  | Speaker |
| :------: | :-----: | :-----: |
|    RX    | TX (26) |         |
|    TX    | RX (27) |         |
|   Vcc    |   Vin   |         |
|   Gnd    |   Gnd   |         |
|   SPK1   |         |    +    |
|   SPK2   |         |    -    |

<br />

## Reference

- [Wiring reference](https://www.hackster.io/munir03125344286/df-player-mini-interface-with-esp32-f1efca)

- [Code reference](https://www.youtube.com/watch?v=7WiSeQxb1bU&t=91s)

<br />
