

 The position of Boot 1 to ground
 But the boot 0 jumper has to be set as 3.3V for programming mode and set to ground for operating mode.
 
 
 Jika untuk penggunaaan normal/setelah programming:
  The position of Boot 0& 1 to ground
 
[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
framework = arduino
board_build.mcu = stm32f103c8t6
upload_protocol = stlink


#include <Arduino.h>
//#include <HardwareSerial.h>
// put function declarations here:
//int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);
  pinMode(PC13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
  digitalWrite(PC13,0);
  delay(250);
  digitalWrite(PC13,1);
  delay(100);
  Serial.println("-----sudah menyala-----");
}

// put function definitions here:
//int myFunction(int x, int y) {
  //return x + y;
//}
--------------------------------------
stm32f103c8t6  LCD I2C



#include <Wire.h> 
//#include <HardwareSerial.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//LiquidCrystal_I2C lcd(PA6,PA5,PA4,PA3,PA2,PA1);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  pinMode(PC13,OUTPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  
}

void loop()
{
  // when characters arrive over the serial port...
  digitalWrite(PC13,0);
  delay(250);
  digitalWrite(PC13,1);
  delay(100);

      lcd.print("---TEST LCD---"); 
      //lcd.write("STM32 StarterKit"); 

  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }


  }
}


------------------------------------------------

OK, TIDAK MENGGUNAKAN LCD I2C
GUNAKAN LIBRARY: LiquidCrystal by Arduino


[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
framework = arduino
board_build.mcu = stm32f103c8t6
upload_protocol = stlink
lib_deps = 
	;locple/LiquidCrystal I2C Multilingual@^2.0.2
	arduino-libraries/LiquidCrystal@^1.0.7


#include <Arduino.h>
#include <LiquidCrystal.h> 
LiquidCrystal lcd(PA0, PA1,PA2,PA3,PA4,PA5); 
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
lcd.begin(16, 2);
lcd.setCursor(0, 0); 
lcd.print("Interfacing LCDQ BOCIL"); 
lcd.setCursor(0, 1); 
lcd.print("Board BOCIL"); 
}

void loop() {
}

---------------------------------------------------

OK, NON LCD I2C
GUNAKAN LIBRARY: LiquidCrystal by Arduino


[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
framework = arduino
board_build.mcu = stm32f103c8t6
upload_protocol = stlink
lib_deps = 
	;locple/LiquidCrystal I2C Multilingual@^2.0.2
	arduino-libraries/LiquidCrystal@^1.0.7

#include <Arduino.h>
#include <LiquidCrystal.h> 
LiquidCrystal lcd(PA0, PA1,PA2,PA3,PA4,PA5); 
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
lcd.begin(16, 2); //bisa ditaruh di void loop
}

void loop() {

lcd.setCursor(0, 0); 
lcd.print("Interfacing LCDQ BOCIL");
//lcd.clear();
delay(500);


lcd.setCursor(0, 1); 
lcd.print("LCD Board BOCIL"); 

delay(500);
lcd.clear();
delay(250);

}

-------------------------------------------------------



[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
framework = arduino
board_build.mcu = stm32f103c8t6
upload_protocol = stlink
lib_deps = 
	marcoschwartz/LiquidCrystal_I2C@^1.1.4
	;mathertel/LiquidCrystal_PCF8574@^2.2.0


 

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{


    lcd.clear();    
    lcd.setCursor(0, 0); 
    delay(500);
    lcd.print("TEST LCD I2C");

  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}

--------------------------------------------------------------
OK, LCD 12C
LiquidCrystal_PCF8574 by Matthias Hertel

PASTIKAN Lokasi PIN I2C DI MCU (stm32f103c8t6 lokapi pin I2C di PB6--SCL & PB7--SDA) kemudian hubungkan pin ini ke LCD I2C

[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
framework = arduino
board_build.mcu = stm32f103c8t6
upload_protocol = stlink
lib_deps = 
	;marcoschwartz/LiquidCrystal_I2C@^1.1.4
	mathertel/LiquidCrystal_PCF8574@^2.2.0




#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
                                   //ADDRESS ini tergantung dari harware masing2, bagaimana cara merubah lokasi address ini?? apakah ada program di dalam IC I2C??

int show = -1;

// 2 custom characters

byte dotOff[] = { 0b00000, 0b01110, 0b10001, 0b10001,
                  0b10001, 0b01110, 0b00000, 0b00000 };
byte dotOn[] = { 0b00000, 0b01110, 0b11111, 0b11111,
                 0b11111, 0b01110, 0b00000, 0b00000 };

void setup() {
  int error;

  Serial.begin(115200);
  Serial.println("LCD...");

  // wait on Serial to be available on Leonardo
  while (!Serial)
    ;

  Serial.println("Probing for PCF8574 on address 0x27...");

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(16, 2);  // initialize the lcd

    lcd.createChar(1, dotOff);
    lcd.createChar(2, dotOn);

  } else {
    Serial.println(": LCD not found.");
  }  // if

}  // setup()


void loop() {
  if (show == 0) {
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello LCD");
    delay(1000);

    lcd.setBacklight(0);
    delay(400);
    lcd.setBacklight(255);

  } else if (show == 1) {
    lcd.clear();
    lcd.print("Cursor On");
    lcd.cursor();

  } else if (show == 2) {
    lcd.clear();
    lcd.print("Cursor Blink");
    lcd.blink();

  } else if (show == 3) {
    lcd.clear();
    lcd.print("Cursor OFF");
    lcd.noBlink();
    lcd.noCursor();

  } else if (show == 4) {
    lcd.clear();
    lcd.print("Display Off");
    lcd.noDisplay();

  } else if (show == 5) {
    lcd.clear();
    lcd.print("Display On");
    lcd.display();

  } else if (show == 7) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** first line.");
    lcd.setCursor(0, 1);
    lcd.print("*** second line.");

  } else if (show == 8) {
    lcd.scrollDisplayLeft();
  } else if (show == 9) {
    lcd.scrollDisplayLeft();
  } else if (show == 10) {
    lcd.scrollDisplayLeft();
  } else if (show == 11) {
    lcd.scrollDisplayRight();

  } else if (show == 12) {
    lcd.clear();
    lcd.print("write-");

  } else if (show == 13) {
    lcd.clear();
    lcd.print("custom 1:<\01>");
    lcd.setCursor(0, 1);
    lcd.print("custom 2:<\02>");

  } else {
    lcd.print(show - 13);
  }  // if

  delay(1400);
  show = (show + 1) % 16;
}  // loop()


--------------------------------------------------

OK, LCD 12C
LiquidCrystal_PCF8574 by Matthias Hertel

PASTIKAN Lokasi PIN I2C DI MCU (stm32f103c8t6 lokapi pin I2C di PB6--SCL & PB7--SDA) kemudian hubungkan pin ini ke LCD I2C
LEBIH CEPAT LIHAT DI CUBE IDE


[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
framework = arduino
board_build.mcu = stm32f103c8t6
upload_protocol = stlink
lib_deps = 
	;marcoschwartz/LiquidCrystal_I2C@^1.1.4
	mathertel/LiquidCrystal_PCF8574@^2.2.0




#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display 
                                   //ADDRESS ini tergantung dari harware masing2, bagaimana cara merubah lokasi address ini?? apakah ada program di dalam IC I2C??

void setup()
{
    lcd.begin(16, 2);  // initialize the lcd
  Serial.begin(9600);
}

void loop()
{

    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello LCD");
    delay(500);

    lcd.setBacklight(0);
    delay(400);
    lcd.setBacklight(255);
    delay(200);
    lcd.blink();
	
	 lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("---bocilq LCD---");
    delay(500);

    lcd.setBacklight(0);
    delay(400);
    lcd.setBacklight(255);
    delay(200);
    //lcd.blink();
    lcd.noDisplay();
    delay(200);
    lcd.display();

  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}

-------------------------------------------------------------------

// STM32 Nucleo-C031C6 I2C Example


#include "LiquidCrystal_I2C.h"

#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, STM32!");

  lcd.init();
  lcd.backlight();

  lcd.setCursor(4, 0);
  lcd.print("Hello, STM32");
  lcd.setCursor(5, 2);
  lcd.print("Welcome to");
  lcd.setCursor(7, 3);
  lcd.print("Wokwi!");
}

void loop() {
}


-------------------------------------


 * HC-05 Configuration Example
 * 
 *  Description: Configure HC05 using simple user serial menu to manage AT 
 *              communications. Requires 2nd UART (Serial1) defined. Automatically 
 *              identifies device (HC-05 or HC-06), firmware version, baud and 
 *              parity settings. Serial1 automatically configured to match HC-05 
 *              UART settings. 
 * 
 *              HC-05 must be in configuration mode (AT mode) (LED blinking to 
 *              indicate Not Connected). 
 *              
 *                
 *    HC05 connections (for 5V boards - resistors not needed for 3V3):
 * 
 *                TXD -----------------> [Serial1 RX]
 *                RXD <----+---R_1K----- [Serial1 TX]
 *                         |
 *                         |
 *                       R_2K
 *                         |
 *                        \|/
 *                        Vss
 * 
 *    [additional connections for AT mode selection]
 * 
 *                STATE  -----------------> [State pin]
 *                EN/KEY <----+---R_1K----- [Mode pin]
 *                            |
 *                            |
 *                          R_2K
 *                            |
 *                           \|/
 *                           Vss
 * 
 *  Command mode (AT mode): 
 *   - Device LED should be blinking fast (> 2 Hz) when in command (AT) mode.
 *   - When LED is solid, device is paired and connected.
 *   - If LED is blinking slowly (HC-05), device is in fixed AT mode. In this 
 *       mode, UART baud rate is fixed at 38400 with no parity. This occurs 
 *       when EN/KEY pin is tied HIGH while power is connected. For this reason, 
 *       [Mode pin] will be set to INPUT mode when not communicating AT commands. 
 *       If LED is blinking slowly, try disconnecting and reconnecting power to 
 *       HC-05 device.
 * 
 *    Pin connections:
 *                    board        Mega    MKR   Uno WiFi  Zero    Due    MSP432
 *      -------------------+-------------------------------------------------------
 *        [Serial1 RX]    |        19      13      0        0      19       3 
 *        [Serial1 TX]    |        18      14      1        1      18       4 
 *      
 * 
 *      Author: ndroid
 *    Modified: 26-Aug, 2023
 */

#include <configureBT.h>

#define MODE_PIN    10
#define STATE_PIN    9

HCBT hc05(MODE_PIN, STATE_PIN);

void setup() {
  // configure Serial Monitor UART (57600 8N1)
  Serial.begin(57600);
  delay(1000);
  Serial.println("Will scan to automatically configure UART for connected device.");
  Serial.println("Enter any character when ready to scan.");
  while (Serial.available() < 1);
  delay(100);
  Serial.readString();   // clear buffer
  if (!hc05.detectDevice(true)) {
    Serial.println("Device not identified!");
    Serial.println("Check connections and restart to scan again.");
  }
}

void loop() {
  // Will display user menu to Serial and handle user selection
  hc05.commandMenu();
  Serial.println("\nEnter any character to return to menu.");
  while (Serial.available() < 1);
  delay(100);
  Serial.readString();   // clear buffer
}
