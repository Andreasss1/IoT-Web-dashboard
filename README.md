# IoT Temperature and Humidity Monitoring Dashboard 🌡️💧

This project is a **real-time IoT-based monitoring system** for temperature and humidity, visualized using **Chart.js** on a web dashboard. The system retrieves data from sensors via MQTT and displays it dynamically with charts.

## 🚀 Features
- 📡 **Real-time data monitoring** using MQTT protocol.
- 📊 **Interactive charts** for temperature and humidity (Chart.js).
- 📅 **Dynamic data** that updates automatically.
- ⚡ **Lightweight & responsive** web-based dashboard.

## 🛠️ Technologies Used
- **ESP32** (for sensor data acquisition)
- **DHT22** (temperature & humidity sensor)
- **MQTT Protocol** (via `broker.emqx.io`)
- **JavaScript + Chart.js** (for data visualization)
- **HTML + CSS** (for UI design)

## 📜 How It Works
1. **Sensor Data Collection**  
   - The ESP32 reads temperature and humidity from the DHT22 sensor.
   - The data is sent via MQTT to an online broker.

2. **Data Transmission & Processing**  
   - The web dashboard subscribes to MQTT topics.
   - Data is received, parsed, and displayed in charts and tables.

3. **Real-Time Visualization**  
   - Temperature and humidity data are plotted dynamically.
   - Old data points are automatically removed to keep the dashboard clean.

## 📊 Dashboard Display

