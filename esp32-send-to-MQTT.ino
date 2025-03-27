#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi config
const char* ssid = "ArkaOsi";
const char* password = "25011971";

// MQTT (Broker EMQX) config
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* topic_temperature = "120323430448/dht22/temp";
const char* topic_humidity = "120323430448/dht22/hum";

// DHT22 setup
#define DHTPIN 33
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// MQTT Client
WiFiClient espClient;
PubSubClient client(espClient);

// WiFi connection function
void setup_wifi() {
    Serial.print("Connecting to: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("\n.");
    }
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// MQTT Reconnect Function
void reconnect() {
    while (!client.connected()) {
        Serial.print("Trying to connect to MQTT...");
        if (client.connect("ESP32_DHT22_Client")) {
            Serial.println("Connected to MQTT Broker!");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Trying again in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Baca suhu dan kelembaban dari DHT22
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Periksa apakah pembacaan sensor valid
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read DHT22!");
        return;
    }

    // Cetak data ke Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Konversi float ke string
    char temperature_str[10];  
    char humidity_str[10];

    dtostrf(temperature, 6, 2, temperature_str);
    dtostrf(humidity, 6, 2, humidity_str);

    // Kirim data ke MQTT
    client.publish(topic_temperature, temperature_str);
    client.publish(topic_humidity, humidity_str);

    delay(5000); // Tunggu 5 detik sebelum membaca lagi
}
