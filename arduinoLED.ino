#include <WiFi.h>
#include<PubSubClient.h>

// this is the port that the led is connected to on the breadboard
#define PIN_LED 2

// this is setting up the variables for the internet connection
const char *ssid_Router = "ROUTER_YOU_ARE_USING";
const char *password_Router = "PASSWORD_TO_ROUTER";
const char *mqtt_server = "EXTERNAL_IP_ADDRESS_SSH";
const char *mqtt_topic = "TOPIC_NAME_YOU_CHOSE";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() { // the first function that is called when the arduino runs the script
 pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883);
  setup_wifi();
  client.setCallback(callback);
}

// connecting to wifi/the router that you are using
void setup_wifi(){
  Serial.println("Setup start");
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Setup End");
}

// this callback function runs automatically once a publisher publishes something to a topic that this client has already subscribed to
void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages if needed and grabbing the message
  char message = (char)payload[0];
  //  String message;
  // for (int i = 0; i < length; i++) {
  //   message += (char)payload[i];
  // }
  // Serial.println();
  //  if (message == '1') {
  //   digitalWrite(PIN_LED, HIGH);
  // } else if (message == '2') {
  //   digitalWrite(PIN_LED, LOW);
  // }
  Serial.println();
  // depending on the output and input
   if (message == '1') {
    digitalWrite(PIN_LED, HIGH);
  } else if (message == '2') {
    digitalWrite(PIN_LED, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic); // Subscribe to the desired topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
