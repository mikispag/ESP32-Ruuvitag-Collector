# ESP32-Ruuvitag-Collector
This software can be used to collect measurement data from [Ruuvitag](https://ruuvi.com) Bluetooth Low Energy devices (v3 and v5) and is meant to be uploaded to a ESP32 board with [PlatformIO](https://platformio.org).

It is a stripped down and updated fork of [hpirila/ESP32-Ruuvitag-Collector](https://github.com/hpirila/ESP32-Ruuvitag-Collector), with Influx and SD/SPIF functionalities removed, library updates and some improvements.

Features:
- **MQTT** publishing
- [MQTT Automatic discovery](https://www.home-assistant.io/docs/mqtt/discovery/) for Home Assistant
- Ruuvitag white list, collect measurements from listed Ruuvitags only.

## Configuration
Before compiling and uploading to the ESP32, you must fill in details in the `config.cpp` file.
