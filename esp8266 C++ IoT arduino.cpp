
[env:esp01]
platform = espressif8266
board = esp01
framework = arduino



[env:esp01_1m]
platform = espressif8266
board = esp01_1m
framework = arduino
upload_protocol = esptool


[env:esp01]
platform = espressif8266
board = esp01
framework = arduino
upload_protocol = esptool


A fatal error occurred: Failed to connect to ESP8266: Timed out waiting for packet header
*** [upload] Error 2



untuk esp8266-01:
1.Connect the GPIO0(Pin 5) to the GND(Pin 7) with a wire.
2.Restart the board(Power off/Power on).
3.Run the command:
sudo python esptool.py --port /dev/ttyUSB0 write_flash 0x00000 /opt/desarrollo/ESP8266/My_Firmware.ino.bin

Where:

ttyUSB0 is the computer port on the ESP is connected.

/opt/desarrollo/ESP8266/My_Firmware.ino.bin is the path of the compiled firmware.

------------------------------------------------------------
OK ESP8266-12E

UNTUK AWAL PRESS FLASH BUTTON, SELANJUTNYA TIDAK PERLU PRESS BUTTON

[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino


#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);  //RX,TX


void setup() {
  // put your setup code here, to run once:
      Serial.begin(9600);     // for communication with the host computer
    espSerial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
      // listen for data from the ESP8266 and then write it to the serial monitor
    if ( espSerial.available() ) {  
      Serial.write( espSerial.read() );  

    }
      Serial.println("send data1......");
      delay(500);
      Serial.println("send data2......");
      delay(500);
      espSerial.println("send data esp......");
      delay(500);
   
}


-----------------------------------------------------------------


[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino


#include <Arduino.h>
#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>

SoftwareSerial espSerial(2, 3);  //RX,TX


void setup() {
  // put your setup code here, to run once:
      Serial.begin(9600);     // for communication with the host computer
    espSerial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
      // listen for data from the ESP8266 and then write it to the serial monitor
      int state = Serial.parseInt(); //jika read bukan angka 
    if ( Serial.available() ) {  
      //Serial.write( espSerial.read() );  
      if (state == 10)    {      
      Serial.println("send data=1xxx ......");
      }
    }

    
    
      Serial.println("send data1......");
      delay(750);
      Serial.println("send data2......");
      delay(750);
      espSerial.println("send data esp......");
      delay(750);
      if (state == 10)  {      
      Serial.println("send data=1xxx ......");
      }
   
}

-----------------------------------------------
OK

berhasil konek ke wifi :  ESP8266-12


#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
 
const char* ssid = "aaaaa";//type your ssid
const char* password = "12345";//type your password
 
int ledPin = 2; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
   
  // Connect to WiFi network
  Serial.println();
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
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here turn the LED on pin 2 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}




output:
---- Opened the serial port COM6 ----
---- Closed the serial port COM6 ----
---- Opened the serial port COM6 ----
20:41:58:764 -> ........
20:42:02:990 -> WiFi connected
20:42:02:992 -> Server started
20:42:02:993 -> Use this URL to connect: http://192.168.1.12/

---------------------------------------