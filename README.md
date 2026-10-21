# Smart Garbage Level Monitoring Syste

## Project Overview

The Smart Garbage Bin is an IoT-based project designed to monitor garbage levels inside a dustbin and detect when it is full.
It uses sensors and an ESP32 microcontroller to identify bin status and provide alerts, helping improve waste collection efficiency and maintain cleanliness.

## Project Files

- "SGC Final.pptx" – Project presentation
- "SGC.jpeg", "SGC.jpeg"-related images – Project images
- "sgb-demo-video.mp4" – Project demonstration video

##  Hardware Components

- ESP32 – Main microcontroller with Wi-Fi connectivity
- HC-SR04 Ultrasonic Sensor – Measures the garbage level
- Power Bank/Battery – Supplies power
- Jumper wires and connecting components

## Working Principle (Workflow)

1. The ultrasonic sensor measures the distance between the sensor and the garbage surface.
2. The ESP32 processes the sensor readings to determine the bin's fill status.
3. When the garbage reaches the predefined threshold, the bin is marked as FULL.
4. The buzzer alerts nearby users when the bin is full.
5. The ESP32 can transmit the bin status over Wi-Fi to a monitoring dashboard for remote monitoring.

## Author

Siddharth S
