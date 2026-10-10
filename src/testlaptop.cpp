
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


// GLOBAL DECLARATIONS

#define LENOVO_PWR_PIN 12

// WiFi credentials
const char* ssid = "#Turin.uz";
const char* password = "Turin_2024@!";

// MQTT Broker settings
const char* mqtt_broker = "mqtt.iotserver.uz";  // Free public MQTT broker
const int mqtt_port = 1883;
const char* mqtt_username = "lenovo";  // username given in the telegram group
const char* mqtt_password = "lenovopc";  // password given in the telegram group

const char* mqtt_topic_pub = "lenovo/esp32/publish";   // Topic to publish
const char* mqtt_topic_sub = "lenovo/esp32/pwr";    // Topic to subscribe


WiFiClient espClient;
PubSubClient mqtt_client(espClient);

unsigned long lastPublishTime = 0;
const long publishInterval = 5000;  // Publish every 5 seconds
int messageCounter = 0;

// Function to connect to WiFi
void connectWiFi();
// Callback function for received MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length);
// Function to connect/reconnect to MQTT broker
void connectMQTT();

/*************************
 * SETUP
 */
void setup() {

    pinMode(LENOVO_PWR_PIN, OUTPUT);
    digitalWrite(LENOVO_PWR_PIN, HIGH);  // Set the pin HIGH initially

    Serial.begin(115200);
    delay(1000);

    Serial.println("\n===== ESP32 - LENOVO CONNECTED =====");

    // Connect to WiFi
    connectWiFi();

    // Setup MQTT
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    mqtt_client.setCallback(mqttCallback);

    // Connect to MQTT broker
    connectMQTT();
}


/*************************
 * LOOP
 */
void loop() {
  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Reconnecting...");
    connectWiFi();
  }
  
  // Check MQTT connection
  if (!mqtt_client.connected()) {
    Serial.println("MQTT disconnected! Reconnecting...");
    connectMQTT();
  }
  
  // Process incoming MQTT messages
  mqtt_client.loop();
  
  // Publish message every 5 seconds
  unsigned long currentTime = millis();
  if (currentTime - lastPublishTime >= publishInterval) {
    lastPublishTime = currentTime;
    
    messageCounter++;
    String message = "Hello from ESP32! Count: " + String(messageCounter);
    
    Serial.print("Publishing message: ");
    Serial.println(message);
    
    if (mqtt_client.publish(mqtt_topic_pub, message.c_str())) {
      Serial.println("Message published successfully!");
    } else {
      Serial.println("Failed to publish message!");
    }
    Serial.println("---");
  }
}

/*************************
 * FUNCTIONS
 */
// Function to connect to WiFi
void connectWiFi() {
  Serial.println("\nConnecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Callback function for received MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  
  // Convert payload to String
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Message content: ");
  Serial.println(message);
  Serial.println("---");

  // IF msg is "ON" then turn on the laptop power button
  if (message == "ON") {
    Serial.println("Turning ON the laptop power button...");
    digitalWrite(LENOVO_PWR_PIN, LOW);  // Simulate button press
    delay(1000);  // Hold the button for 1 second
    digitalWrite(LENOVO_PWR_PIN, HIGH);  // Release the button
    Serial.println("Laptop power button pressed!");
  }

}

// Function to connect/reconnect to MQTT broker
void connectMQTT() {
  while (!mqtt_client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    
    String client_id = "esp32-client-" + String(WiFi.macAddress());
    
    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker!");
      
      // Subscribe to topic
      mqtt_client.subscribe(mqtt_topic_sub);
      Serial.print("Subscribed to topic: ");
      Serial.println(mqtt_topic_sub);
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.println(mqtt_client.state());
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
    }
  }
}


// #include "Arduino.h"

// #include "WIFI.h"

// #define LENOVO_PWR_PIN 12

// void dummy_readings(uint32_t millisec);

// /****************************************************/
// void setup(void) 
// {
//     // // pinMode(LENOVO_PWR_PIN, INPUT_PULLUP); // LENOVO POWER
//     // Serial.begin(115200);
//     // delay(1000);
//     // Serial.println("Starting test for Lenovo laptop power button");
    
//     pinMode(LENOVO_PWR_PIN, OUTPUT);
//     digitalWrite(LENOVO_PWR_PIN, HIGH);
//     delay(2000);
//     digitalWrite(LENOVO_PWR_PIN, LOW);
//     delay(1000);
//     digitalWrite(LENOVO_PWR_PIN, HIGH);

// }


// /****************************************************/
// void loop(void) 
// {
//     // static bool pwr_state = false;
    
//     // int pwr_val = analogRead(LENOVO_PWR_PIN);

//     // Serial.print("pwr_val = ");
//     // Serial.println(pwr_val);

//     // if (pwr_val >= 3000 && pwr_state == false) {
//     //     pwr_state = true;

//     //     pinMode(LENOVO_PWR_PIN, OUTPUT);

//     //     digitalWrite(LENOVO_PWR_PIN, LOW);
//     //     delay(1000);
//     //     pinMode(LENOVO_PWR_PIN, INPUT_PULLUP);

//     //     Serial.println("Laptop is powered on");

//     //     dummy_readings(2000);
        
//     // }
//     // else if (pwr_val < 1023 && pwr_state == true) {
//     //     pwr_state = false;

//     //     Serial.println("Laptop is powered off");
//     // }


//     // delay(1000);

// }

// // void dummy_readings(uint32_t millisec)
// // {
// //     uint32_t start_time = millis();
// //     while (millis() - start_time < millisec) {
// //         int pwr_val = analogRead(LENOVO_PWR_PIN);
// //         delay(100);
// //     }
// // }

