// This program unitlizes an ESP32 microcontroller and DHT11 temperature and humidity sensor.
// MCU connects to MQTT Broker to publish results to a UI in Node Red


#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Cabin";
const char* password = "NUNYA";

// MQTT setup
const char* mqtt_server = "test.mosquitto.org"; // server address
const int mqtt_port = 1883;
const char* client_id = "esp32";

// configuration for temp/humidity sensor
#define DHTPIN 4          // set to GPIO 4
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);

// Class declaration to communicate with arduino libraries
WiFiClient espClient;
PubSubClient client(espClient);

// wifi connection
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT connection
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(client_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again");
      delay(5000);
    }
  }
}

// initialization
void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();                   // attempts to reconnect to MQTT until success
  }
  client.loop();

  // Reads temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

 temperature = (temperature * 1.8) + 32;

  // Publish temperature and humidity to MQTT topics
  char temp_topic[50];
  char hum_topic[50];
  sprintf(temp_topic, "device/temperature/cody");
  sprintf(hum_topic, "device/humidity/cody");

  Serial.print("Publishing temperature: ");
  Serial.println(temperature);
  client.publish(temp_topic, String(temperature).c_str()); // convert float to string for MQTT

  Serial.print("Publishing humidity: ");
  Serial.println(humidity);
  client.publish(hum_topic, String(humidity).c_str()); // convert float to string for MQTT

  delay(5000); // Wait 5 seconds before publishing the next readings
}
