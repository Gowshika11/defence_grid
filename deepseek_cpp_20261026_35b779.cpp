#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define FLOW_SENSOR_PIN 4
#define CURRENT_SENSOR_PIN 16
#define DHT_PIN 17
#define RELAY_PIN 18

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "192.168.1.100"; // Raspberry Pi IP

volatile int flowPulseCount = 0;
DHT dht(DHT_PIN, DHT22);
WiFiClient espClient;
PubSubClient client(espClient);

void IRAM_ATTR flowPulse() { flowPulseCount++; }

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  
  if (msg == "SHUTDOWN") digitalWrite(RELAY_PIN, LOW);  
  else if (msg == "ACTIVATE") digitalWrite(RELAY_PIN, HIGH); 
}

void setup() {
  Serial.begin(115200);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowPulse, RISING);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      client.connect("water_node_1");
    }
    client.subscribe("commands/water1");
  }
  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 1000) {
    lastMsg = millis();
    
    float flowRate = (flowPulseCount * 60.0) / 450.0; 
    flowPulseCount = 0;

    int adcValue = analogRead(CURRENT_SENSOR_PIN);
    float voltage = (adcValue / 4095.0) * 3.3;
    float currentDraw = (voltage - 1.65) / 0.185; 
    
    float temperature = dht.readTemperature();

    StaticJsonDocument<200> doc;
    doc["flow"] = flowRate;
    doc["current"] = currentDraw;
    doc["temperature"] = temperature;

    char buffer[200];
    serializeJson(doc, buffer);
    client.publish("sensors/water1", buffer);
  }
}