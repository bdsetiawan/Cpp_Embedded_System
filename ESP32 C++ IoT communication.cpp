



#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing WiFi...");
  WiFi.mode(WIFI_STA);
  Serial.println("Setup done!");
}

void loop() {
  Serial.println("Scanning...");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Scan done!");
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println();
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}

//=========================================================================

OK: ESP32 as Server Code
[env:denky32]
platform = espressif32
board = denky32
framework = arduino


#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "aaaaa";
const char* password = "1234";

// Define the server port
const int serverPort = 12345;

WiFiServer server(serverPort);

void setup() {
  Serial.begin(115200);
  delay(1000); // Give time for Serial Monitor to open

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n'); // Read the message
        Serial.println("Received message: " + message);
      }
    }
    Serial.println("Client disconnected");
  }
}


Connected to Wi-Fi
IP Address: 192.168.11.111
Server started

//-----------------------------------------------------------


#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with the server IP address
const char* serverIP = "SERVER_IP_ADDRESS";
const int serverPort = 12345;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give time for Serial Monitor to open

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Connect to the server
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection to server failed");
  }
}

void loop() {
  if (client.connected()) {
    // Send a message to the server
    client.println("Hello from ESP32 client!");
    Serial.println("Message sent to server");
    delay(1000); // Send a message every second
  } else {
    Serial.println("Disconnected from server");
    delay(1000);
  }
}


//-----------------------------------------------------


//OK, Setting up BT the Transmitter (Sender) ESP32:


#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  // Initialize serial communication with the PC
  Serial.begin(115200);
  // Initialize Bluetooth Serial
  SerialBT.begin("ESP32_Sender"); // Name of the Bluetooth device
  Serial.println("Bluetooth Serial started. Ready to send messages.");
}

void loop() {
  // Check if data is available to send
  if (Serial.available()) {
    String message = Serial.readString(); // Read the message from serial monitor
    SerialBT.println(message);           // Send the message via Bluetooth
    Serial.println("Message sent: " + message);
  }
  delay(1000); // Optional: Add a delay to avoid flooding the receiver
}

-----------------------------------------------------
Setting up BT the Receiver (Receiver) ESP32


#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  // Initialize serial communication with the PC
  Serial.begin(115200);
  // Initialize Bluetooth Serial
  SerialBT.begin("ESP32_Receiver"); // Name of the Bluetooth device
  Serial.println("Bluetooth Serial started. Ready to receive messages.");
}

void loop() {
  // Check if data is available to read
  if (SerialBT.available()) {
    String message = SerialBT.readString(); // Read the message from Bluetooth
    Serial.println("Message received: " + message);
  }
  delay(1000); // Optional: Add a delay to avoid overloading the serial monitor
}
