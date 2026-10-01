# RTOS-Based IoT Smart Home System

## Tổng quan
Project đầu tay vừa học vừa làm Embedded/IoT từ con số 0, hướng tới một ngôi nhà mà mọi thiết bị, mọi tác vụ trong căn nhà có thể nắm bắt và điều chỉnh trong lòng bàn tay.

## Features
- Environmental monitoring
- Smart lighting
- Motion detection
- Local display
- Manual control
- Remote monitoring/control via MQTT (planned)

## Thiết kế hệ thống
![System Architecture](docs/diagrams/block_diagram.png)

## Phần cứng
- ESP32 DevKit
- DHT11 Temperature & Humidity Sensor
- LDR (Photoresistor)
- HC-SR501 PIR Motion Sensor
- SSD1306 OLED Display
- 2-Channel Relay Module
- Servo Motor
- Buzzer
- Push Button
- LEDs
- Resistors (220Ω, 1kΩ, 10kΩ)
- Breadboard
- Jumper Wires

## Pin Mapping

| Device | ESP32 Pin | I/O | Interface | Purpose |
|---|---|---|---|---|
| Button | GPIO4 | Input | GPIO | Manual control |
| PIR | GPIO13 | Input | GPIO | Motion detection |
| LDR | GPIO34 | Input | ADC | Light intensity |
| DHT11 | GPIO23 | I/O | Digital | Temperature & humidity |
| Relay CH1 | GPIO18 | Output | GPIO | Light control |
| Relay CH2 | GPIO19 | Output | GPIO | Load control |
| Buzzer | GPIO25 | Output | GPIO / PWM | Alarm |
| Status LED | GPIO26 | Output | GPIO | System status |
| Servo | GPIO27 | Output | PWM | Actuator |
| OLED | GPIO21 / 22 | I/O | I2C | Local display |

## Cài đặt


## Cách sử dụng