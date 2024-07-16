# Accident_Dectection_System_Using_IOT

## Overview

This project implements a Bank Account Management System using Arduino and various sensors and modules. It monitors gas levels, detects accidents using vibration sensors, and communicates data via GSM and IoT protocols. Data is also logged to an SD card for record-keeping.

## Components Used

- Arduino Uno
- LCD Display
- DHT Temperature and Humidity Sensor
- Gas Sensor
- GSM Module
- SD Card Module
- Vibration Sensor

## Setup

1. **Hardware Setup:**
   - Connect the Arduino Uno to the LCD, DHT sensor, Gas sensor, GSM module, and SD card module as per the circuit diagram.

2. **Software Dependencies:**
   - Libraries: Ensure you have the necessary libraries installed for the LCD, DHT sensor, SD card, and GSM module.

3. **Arduino IDE:**
   - Upload the provided sketch (`main.ino`) to the Arduino board using the Arduino IDE.

4. **Configuration:**
   - Update necessary configurations such as pins used for sensors and modules.

## Functionality

### Sensors Integration

- **Gas Sensor:** Monitors gas levels and displays status on the LCD.
- **DHT Sensor:** Measures temperature and humidity, displaying the values on the LCD.
- **Vibration Sensor:** Detects accidents (high vibration levels) and triggers GSM communication for emergency alerts.

### Communication

- **GSM Module:** Sends alerts and data updates via SMS or calls in case of accidents.
- **IoT Integration:** Sends sensor data (temperature, gas levels) to a remote server using IoT protocols.

### Data Logging

- **SD Card:** Logs gas levels and temperature/humidity data to an SD card for historical record-keeping.

## Usage

- Once the setup is complete, the system starts monitoring automatically.
- Check the LCD for real-time sensor readings and system status updates.
- Review the data log on the SD card for historical sensor data.


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

