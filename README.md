# Embedded Systems Engineer Assignment

## Overview

This project implements a complete embedded communication pipeline using MQTT and UART protocols. The system enables a user to send commands from a Python interface, which are transmitted over MQTT to an ESP32. The ESP32 then forwards these commands via UART to a microcontroller (emulated using Arduino), which executes actions such as LED control and motor simulation.

---

## System Architecture

```
User → Python → MQTT Broker → ESP32 → UART → Arduino (STM Emulator) → LED / Motor
```

### Description

* The Python script acts as the user interface.
* The MQTT broker handles message transmission.
* ESP32 serves as a bridge between MQTT and UART.
* Arduino emulates STM32 functionality by processing commands and controlling hardware.

---

## ⚙️ Components Used

### Hardware

* ESP32 (MQTT client + UART bridge)
* Arduino (used as STM32 emulator)
* LED (for output indication)

### Software

* Python (paho-mqtt library)
* Arduino IDE
* MQTT Broker: broker.hivemq.com (public broker)

---

## Working Principle

1. User enters a command in the Python script.
2. Python publishes the command to the MQTT topic.
3. ESP32 subscribes to the topic and receives the command.
4. ESP32 forwards the command via UART.
5. Arduino receives the command and processes it.
6. Based on the command:

   * LED is turned ON/OFF
   * Motor behavior is simulated using LED blinking

---

## 🧾 Command Format

The system supports simple text-based commands:

```
LED ON
LED OFF
MOTOR
```

### Features

* Case-insensitive command handling
* Extensible command structure

---

## 🔌 Hardware Connections

### UART Communication

| ESP32       | Arduino (STM Emulator)  |
| ----------- | ----------------------- |
| TX (GPIO17) | RX (Pin 0)              |
| RX (GPIO16) | TX (Pin 1) *(optional)* |
| GND         | GND                     |

> Note: Current implementation uses unidirectional UART (ESP32 → Arduino).

---

### LED Connection

```
Arduino GPIO (Pin 13) → Resistor → LED → GND
```

---

### Motor (Simulated)

* Stepper motor functionality is simulated using LED blinking.
* In a real implementation, a stepper driver (A4988/DRV8825) would be used.

---

### Power Considerations

* Common ground is maintained across ESP32 and Arduino.
* ESP32 operates at 3.3V, Arduino at 5V.
* External power supply would be required for actual motor operation.

---

## Assumptions & Design Decisions

* Arduino is used to emulate STM32L452REP due to hardware constraints.
* The firmware is designed to be hardware-agnostic and easily portable to STM32 platforms.
* Stepper motor control is simulated due to lack of physical hardware.
* A public MQTT broker is used for simplicity and rapid prototyping.

---

## How to Run

### 1. Python (MQTT Publisher)

Install dependency:

```
pip install paho-mqtt
```

Run the script:

```
python mqtt_sender.py
```

---

### 2. ESP32

* Upload ESP32 firmware using Arduino IDE
* Ensure WiFi credentials are correctly configured
* Open Serial Monitor (115200 baud)

---

### 3. Arduino

* Upload Arduino code
* Open Serial Monitor (9600 baud)

---

### 4. Test

Enter commands in Python terminal:

```
LED ON
LED OFF
MOTOR
```

---

## Project Structure

```
/python      → MQTT publisher script
/esp32       → ESP32 firmware
/arduino     → Arduino (STM emulator) code
```

---

## Conclusion

This project demonstrates a complete embedded communication system integrating IoT (MQTT) with microcontroller-based hardware control. The modular and protocol-driven design ensures scalability, portability, and ease of integration across different hardware platforms.
