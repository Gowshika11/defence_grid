# भारत Rakshak - Autonomous Cyber-Physical Defense Grid

This repository contains the complete prototype code for "Bharat Rakshak", an autonomous defense system designed to protect rural infrastructure from cyber-physical attacks.

## 🏗️ Project Architecture
- **Edge Nodes (ESP32):** Reads physical sensors (Flow, Current, Temp) and sends data via MQTT.
- **AI Engine (Raspberry Pi):** Calculates the C3-Index (Cyber-Physical Consistency Index) to detect attacks. Hosts a Flask API.
- **Dashboard (React):** Displays real-time data, C3-Index, and attack status in a dark-mode UI.

## 📂 Folder Structure
- `/esp32_firmware` - C++ code for the ESP32 water node.
- `/pi_backend` - Python code (C3-Index algorithm, Flask API).
- `/dashboard` - React.js frontend code.

## 🚀 How to Run the Prototype

### 1. Backend (Raspberry Pi / PC)
```bash
cd pi_backend
pip install -r requirements.txt
python app.py