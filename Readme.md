# Adafruit Sensor Extension Bring-up Tests
## Purpose
Exploration code for ReDI's InternetoPlants for kids workshop. Sensing plant related environmental paramters with Arduino and recording/plotting/processing them in Python.

## Preperation
### Arduino
+ install Arduino IDE and sensor librries
    + Add Adafruit board support: in the Arduino IDE Menu->Preferences add https://adafruit.github.io/arduino-board-index/package_adafruit_index.json to the "Additional Boards Manager URLs" line, confirm with OK
    + Install board drivers: in Arduino IDE Menu->Tools->Boards Manager search for "Adafruit samd boards" and select the 1.5.x version
    + Install sensor drivers: in the Arduino IDE Menu->Tools->Manage Libraries search and install "Adafruit Unified Sensor" (on the bottom), "Adafruit seesaw", "Adafruit TSL2591", "DHT sensor library" (by adafruit)
+ compile: press "verify" (check button in the top left) the sensor_stream library and check if everythings runs ok
+ compile and install: press "upload" (arrow right in the button top left)
+ open the serial monitor: in Arduino IDE Menu->Tools->Serial Monitor , data should be printed

### Python3
+ install requirements (jupyter, pandas, pyserial) using you package manager of choice (pip, conda)
+ check the serial connection of the Arduino device on your machine and and modify the `serial_port` variable
+ execute/process/visualise in the jupyter

## Todo
+ robustness
+ python env and dependencies
+ documentation