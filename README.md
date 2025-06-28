# Weather LoRa Communication System

This project demonstrates a simple LoRa-based weather data transmission system using Arduino. It includes two sketches:

- `weather_lora.ino`: Transmitter that sends weather sensor data (e.g., temperature, humidity) via LoRa.
- `rx.ino`: Receiver that captures and logs/display the incoming weather data.

## 📂 File Structure

```
weather_lora_project/
├── transmitter/       # Contains the transmitter sketch
│   └── weather_lora.ino
├── receiver/          # Contains the receiver sketch
│   └── rx.ino
```

## 🔧 Hardware Requirements

- 2x Arduino-compatible boards (e.g., Arduino UNO, Nano)
- 2x LoRa modules (e.g., SX1278)
- DHT11/DHT22 sensor or any weather sensor
- Jumper wires, breadboard

## 🔌 Libraries Required

Install the following libraries via Arduino Library Manager:

- `LoRa` by Sandeep Mistry
- `DHT sensor library` by Adafruit
- `Adafruit Unified Sensor`

You can install them in Arduino IDE:
```
Sketch → Include Library → Manage Libraries
```

## 🚀 How to Use

1. Flash `weather_lora.ino` to the transmitting Arduino.
2. Flash `rx.ino` to the receiving Arduino.
3. Connect LoRa modules correctly on both ends (SPI).
4. Monitor Serial output for sent/received data.

## 📝 Notes

- Ensure the frequency (433MHz, 868MHz, 915MHz) matches your LoRa module.
- Check pin definitions and adjust if needed.

## 📜 License

MIT License
