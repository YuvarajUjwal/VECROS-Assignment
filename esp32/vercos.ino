#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "Leo";
const char* password = "00000000";

// MQTT broker
const char* mqtt_server = "broker.hivemq.com";

// UART pins
#define RXD2 16
#define TXD2 17

WiFiClient espClient;
PubSubClient client(espClient);

// 🔥 Callback: MQTT → UART
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";

  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  // Print to Serial Monitor
  Serial.print("Received from MQTT: ");
  Serial.println(msg);

  // 🔥 Send to Arduino via UART
  Serial2.println(msg);
}

// 🔥 Connect to MQTT
void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");

    String clientId = "ESP32Client-" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected ✅");

      // Subscribe after connecting
      client.subscribe("Vecros/commands");
      Serial.println("Subscribed to topic: Vecros/commands");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // 🔥 UART init (for Arduino communication)
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected ✅");

  // Setup MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Initial MQTT connect
  connectMQTT();
}

void loop() {
  // Maintain MQTT connection
  if (!client.connected()) {
    Serial.println("MQTT disconnected. Reconnecting...");
    connectMQTT();
  }

  client.loop();

  delay(10); // stability
}