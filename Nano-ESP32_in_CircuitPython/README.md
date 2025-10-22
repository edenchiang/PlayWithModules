# Turn an Arduino Nano ESP32 into a pyboard of CircuitPython

This article shows how to flash an Arduino Nano ESP32 to a pyboard in CircuitPython via [offcial product page](https://circuitpython.org/board/arduino_nano_esp32s3/)

<br />

## Preparation

1. Arduino Nano ESP32

2. A jumper wire for shortage GND and B1 pin

<br />

## Flash Arduino Nano ESP32 into a pyboard

1. Connect Arduino Nano ESP32 and switch it to **programming mode** - the onboard LED will be **dark purple** - [here shows how to](#how-to-switch-arduino-nano-esp32-to-programming-mode)<br />

2. Open [offcial product page](https://circuitpython.org/board/arduino_nano_esp32s3/), and click "**OPEN INSTALLER**" below the **DOWNLOAD** buttons<br />
![official page](images/Nano-ESP32_download_page.jpg)

3. Choose "**Install CircuitPython 9.2.4 Bin Only**", the version will change by the updating of CircuitPython<br />
![install bin file](images/Nano-ESP32_choose_bin-file.jpg)

4. "**Next**"<br />
![declaration](images/Nano-ESP32_description.jpg)

5. "**Connect**"<br />
![prepare to connect](images/Nano-ESP32_connect_prepare.jpg)

6. Choose the correct COM port, and click "**Connect**" to get Arduino Nano ESP32 connected. <br />
On windwos, you can always check the COM port via "**Device Manager**" -> Ports (COM & LPT) <br />
![port selection](images/Nano-ESP32_connect_port-chosen.jpg)

7. Choose "**Continue**" to start writing firmware<br />
![confirmation](images/Nano-ESP32_update_confirm.jpg)

8. Processing... <br />
![processing](images/Nano-ESP32_update-process.jpg)

9. "**Close**" and done. Then the "**CIRCUITPY**" folder of the pyboard storage will pop up <br />
![done](images/Nano-ESP32_update_done.jpg)

<br />

## Usage

The pyboard would automatically execute the files named with "**code.py**" after it starts up, so place the codes, which needs to <br />
be executed automatically, into the file.

<br />

### Check MAC address

Check the MAC address of the board in the CircuitPython console with the commands below:

<pre>
# check MAC address of the board
>>> import wifi
>>> print("My MAC addr:", [hex(i) for i in wifi.radio.mac_address])

# output example, the exact MAC address should be 34:85:18:7a:e6:6c
My MAC addr: ['0x34', '0x85', '0x18', '0x7a', '0xe6', '0x6c']
</pre>

### How to copy a file to pyboard with Thoony

[Please check here](../ESP32_to_Pyboard/README.md#how-to-copy--upload-a-file--folder-to-pyboard-with-thoony)

## Recover an ESP32 pyboard as a normal ESP32 for Arduino

Try to upload any Arduino code to the ESP32 pyboard, then test whether the ESP32 is working as an Arduino ESP32.

<br />

## Others

### How to switch Arduino Nano ESP32 to programming mode?

1. Connect Arduino Nano ESP32 to computer<br />
![connect to computer](images/mode-initial.jpg)

2. Short the GND and B1 pins with jumper wire, they are right next to each other, then the onboard LED will turn to **GREEN** <br />
![shortage GND and B1 pins](images/mode-shortage.jpg)

3. Click the RST button, the onboard LED stays **GREEN**<br />
![click onboard button](images/mode-reset.jpg)

4. Remove the jumper wire for shortage B1 and GND pins, then the onboard LED will turn to **DARK PURPLE** <br />
![remove shortage jumper wire](images/mode-programming.jpg)

1. Done, and the window named "CIRCUITPY" for the storage of the board will pop up

### Reference

* [Official CircuitPython Page](https://circuitpython.org/)

* [Programming in CircuitPython](https://learn.adafruit.com/welcome-to-circuitpython)
