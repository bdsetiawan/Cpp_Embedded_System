
#include <SoftwareSerial.h>

// Create a software serial port
SoftwareSerial bluetoothSerial(10, 11); // RX, TX

void setup() {
  // Start serial communication with the PC
  Serial.begin(9600);
  
  // Start serial communication with the Bluetooth module
  bluetoothSerial.begin(9600);
  
  // Print a startup message to the Serial Monitor
  Serial.println("Bluetooth Serial Communication Initialized");
}

void loop() {
  // Check if data is available from Bluetooth module
  if (bluetoothSerial.available()) {
    char receivedChar = bluetoothSerial.read();
    Serial.print(receivedChar); // Print received data to Serial Monitor
  }

  // Check if data is available from Serial Monitor
  if (Serial.available()) {
    char dataToSend = Serial.read();
    bluetoothSerial.print(dataToSend); // Send data to Bluetooth module
  }
}
