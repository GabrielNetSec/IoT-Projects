# Arduino Water Leak Detector (C++ / IoT)

[![Platform: ESP32](https://img.shields.io/badge/platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Language: C++](https://img.shields.io/badge/language-C++17-blue.svg)](https://en.cppreference.com/)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE)
[![IoT-Ready](https://img.shields.io/badge/IoT-ready-blue.svg)](#)
[![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-blue.svg)](https://www.arduino.cc/en/software)
[![Built with Arduino](https://img.shields.io/badge/built%20with-Arduino-lightgrey?logo=arduino)](https://www.arduino.cc/)

> **Modern C++ for IoT/Embedded: Real-time water tap monitoring, resilient wireless comms, and in-depth device analytics.  
> Academic project developed at [University of Victoria](https://www.uvic.ca/) for ECE-569A Internet of Things Analytics and Security.**

---

## 🌎 Project Overview

This IoT-based system provides **real-time monitoring of household water tap status** and remote notification over WiFi or GSM (future extension), combining robust C++ embedded programming with modern web-based status visualization.

- **Real-time water flow detection** using hardware interrupts on ESP32/Arduino.
- Status exposed via **HTTP web server**; view "Water On"/"Off" from any browser.
- **Resilient to power/internet failures** (UPS and GSM backup options described in report).
- Extensible for data analytics, smart home integration, and cloud connectivity.

---

## 🎯 Objectives

- **Instant leak/tap detection:** Immediate state updates ("On"/"Off") when water flows or stops.
- **Remote notification:** Designed to transmit status to devices over 2km away (via WiFi, GSM, or future LoRaWAN).
- **Emergency resilience:** System continues reporting during power or internet outages, using battery and GSM backup.

---

## 🏗️ System Architecture

**Key components:**
- ESP32/Arduino R4 (with integrated WiFi)
- YF-S201 water flow sensor (pulse output)
- Optional SIM800L GSM module for SMS backup
- UPS or power bank for continuous operation
- Home WiFi router (port forwarding or local access)

**How it works:**
1. Water flow triggers pulses on the YF-S201 sensor.
2. Hardware interrupt on ESP32 increments pulse count & updates status.
3. Web server (HTTP, port 80) serves real-time "On"/"Off" status to any client.
4. (Optionally) System can notify remotely via SMS if WiFi/internet fails.

---

## 🛠️ Code Highlights (C++ / Arduino)

- Fully written in modern, readable C++ (not Arduino C).
- Uses `volatile`, `constexpr`, and ISR best practices for embedded reliability.
- Modular functions (`serveWebPage()`, `increase()` ISR, etc.).
- HTML web page auto-refreshes every 30 seconds; easy to integrate into dashboards.
- **Credentials security:** WiFi credentials are externalized in `secrets.h` (not versioned).

**[View the code → `water_leak_detector.cpp`](./water_leak_detector.cpp)**

---

## 🚀 Quick Start

1. **Copy `secrets.h.example` to `secrets.h`** and insert your WiFi credentials.
2. Open `water_leak_detector.cpp` in [Arduino IDE](https://www.arduino.cc/en/software) or PlatformIO.
3. Select your ESP32 (or compatible) board.
4. Upload the code. Connect YF-S201 output to GPIO 2 (adjust as needed).
5. Open Serial Monitor for IP address.
6. Access the device's IP from any web browser—view status updates in real time!

---

## 🧪 Testing & Validation

- Tested in both **local LAN and remote (port-forwarded) scenarios**; up to 2km over internet/WAN.
- Real-world use cases: leak detection, remote tap monitoring, and integration with mobile dashboards.
- Battery/UPS operation validated for up to 8 hours continuous runtime.

---

## 🔗 Academic & Industry Context

This project was developed as part of the [ECE-569A Internet of Things Analytics and Security](https://www.uvic.ca/) course at the University of Victoria.

**Potential Extensions:**
- AI/ML analytics for predictive water use and leak detection
- LoRaWAN/5G for city-wide smart water management
- Integration with smart home hubs (e.g., Home Assistant, AWS IoT)

---

## 👔 About the Author

**Gabriel Naranjo Orozco**  
- Master’s Student in Telecommunications & IT, University of Victoria  
- 12+ years experience in nNetworking, Telecom, cybersecurity, and Python automation  
- Passionate about professional C++ coding for IoT & embedded systems

[![GitHub](https://img.shields.io/badge/GitHub-GabrielNetSec-black?logo=github)](https://github.com/GabrielNetSec)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-GabrielNaranjoOrozco-blue?logo=linkedin)](https://www.linkedin.com/in/gabriel-naranjo-orozco)

---

## 📝 License

This project is released under the [MIT License](./LICENSE).

---

_“Developed to showcase strong C++/IoT engineering skills for academic, portfolio, and professional industry use.”_
