<h2 align="center">Cyber Physical Systems Security (CPSS)</h2>
<h3 align="center">ESP8266 NodeMCU Projects Collection</h3>

<p align="center">
  Arduino ESP8266 projects
  <br />
  <a href="#about-the-project"><strong>Explore the projects »</strong></a>
  <br />
  <br />
  <a href="https://github.com/ahmeddwalid/cpss/issues">Report Bug</a>
  ·
  <a href="https://github.com/ahmeddwalid/cpss/pulls">Request Feature</a>
</p>

<!-- ABOUT THE PROJECT -->

## About

This repository contains a collection of **ESP8266 NodeMCU** projects developed for the Cyber Physical Systems Security course. Each assignment demonstrates fundamental concepts in embedded systems and wireless communication. The projects progress from basic GPIO control to advanced and secure networked systems.

**Framework:** Arduino | **Build System:** PlatformIO

## Hardware Requirements

### Primary Development Board

**ESP8266 NodeMCU v2 (ESP-12E)**

- Microcontroller: ESP8266 (32-bit RISC CPU)
- Operating Voltage: 3.3V
- Flash Memory: 4MB
- RAM: 80KB
- WiFi: 802.11 b/g/n
- GPIO Pins: 17 available
- ADC: 1x 10-bit
- PWM: Software PWM on all GPIO pins

#### Components and modules

- LEDs (various colors)
- Resistors (220Ω or 330Ω)
- HC-SR04 Ultrasonic Sensor
- RC522 RFID Module & # 13.56MHz RFID cards
- SG90 Servo Motor
- 16x2 Chracter LCD with I2C module
- DHT11 Sensor
- IR Remote and IR Receiver
- Light Dependant Resistor (LDR)
- Breadboards and jumper wires
- USB cable for programming and providing power

## Software Requirements

### 💻 Development Environment

- **PlatformIO** or **Arduino IDE**

## Installation Steps

1. **Clone Repository:**
   
   ```bash
   git clone https://github.com/ahmeddwalid/cpss
   cd cpss
   ```

2. **Build and Upload:**
   
   ```bash
   # X is a placeholder for the assignment number
   cd "Assignment X/projectname"
   
   # Build and upload code
   pio run --target upload
   
   # For projects with filesystem
   pio run --target uploadfs
   ```

# Projects Overview

| Assignment       | Project Name                                          | Description                                                       |
| ---------------- | ----------------------------------------------------- | ----------------------------------------------------------------- |
| **Assignment 0** | [ESP8266 Traffic Lights](./Assignment%200)            | Automated traffic light system with timed LED sequences           |
| **Assignment 1** | [ESP8266 AP LED Control](./Assignment%201)            | Wireless LED control through a web interface in Access Point mode |
| **Assignment 2** | [ESP8266 Ultrasonic Distance Gauge](./Assignment%202) | Proximity detection system with visual LED feedback               |

# Getting Started

## Prerequisites

- Basic understanding of C/C++ programming
- Understanding of basic electronics (LEDs, resistors, ...etc)
- PlatformIO or Arduino IDE

# Contributing

Project's Link: [https://github.com/ahmeddwalid/cpss](https://github.com/ahmeddwalid/cpss)

Any contributions you make are **greatly appreciated**.

This repository is primarily for educational purposes.

## How to Contribute

If you'd like to contribute, please follow these steps:

1. **Fork the repository:** Create your own copy of the project
2. **Create a branch:** `git checkout -b feature/your-feature-name`
3. **Implement your contribution**
4. **Commit your changes:** `git commit -m "your descriptive commit message"`
5. **Push to the branch:** `git push origin feature/your-feature-name`
6. **Create a pull request:** Submit your changes for review

### Contribution Guidelines

- Follow existing code style and documentation standards
- Test thoroughly on actual hardware before submitting
- Update documentation for any new features or changes
- Include circuit diagrams for hardware modifications
- Provide clear commit messages and pull request descriptions
- Be respectful and considerate of other contributors

Thank you for your contributions!

# Academic Integrity Statement

This repository contains educational projects developed for academic coursework. Students using this code should:

- **Understand the Code:** Don't just copy & paste
- **Follow Course Policies:** Respect your institution's academic integrity guidelines
- **Cite Sources:** Properly attribute any code or concepts used from this repository

# Acknowledgments

* [PlatformIO Documentation](https://docs.platformio.org/)
* [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
* [NodeMCU Documentation](https://nodemcu.readthedocs.io/)
* [ESP8266 Pinout Reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
* [Arduino Community](https://www.arduino.cc/en/Main/Community)
* [Espressif Systems](https://www.espressif.com/)

<!-- LICENSE -->

# License

This project is distributed under the [Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/). See [`LICENSE`](/LICENSE) for more information.

<p align="right">(<a href="#top">back to top</a>)</p>
