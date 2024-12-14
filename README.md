# ESP_NOW-MQTT

## Flow diagram of Setup

![flow_diagram_of_setup_KsQ28eAds0](https://github.com/user-attachments/assets/c3792b38-94d4-4ffb-a3fc-ecd27cef493a)

---

##➡️ Node 1 & Node 2

These nodes collect temperature and humidity data from a DHT11 sensor and communicates the data wirelessly using ESP-Now protocol. It also enters deep sleep mode to save power, waking periodically to collect and transmit data.

##➡️ Master Node

This master node receives data from two slave nodes. ESP-NOW is a communication protocol by Espressif (makers of the ESP32) that allows devices to send data to each other without needing Wi-Fi.

##➡️ Python Script

This interface is between an ESP32 sending data over serial communication and an MQTT broker. It processes data received from the ESP32 and publishes the relevant information (temperature and humidity) to specific MQTT topics.
