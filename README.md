# WS2815-with-HCSRO4
# ESP32-S3 Distance-Reactive LED Visualizer (HC-SR04 & WS2815)
This project uses an ESP32-S3 and an HC-SR04 Ultrasonic Sensor to measure distance and provide real-time visual feedback using a WS2815 12V LED strip. As an object gets closer to the sensor, the LEDs change color (Green to Red) and the "bar" fills up.
🚀 Features
Real-time Distance Sensing: Accurate ultrasonic measurements via the HC-SR04.
Dynamic LED Feedback: WS2815 strip acts as a progress bar (Closer = More LEDs + Redder color).
High-Performance MCU: Built specifically for the ESP32-S3.
Fail-safe Logic: Includes code timeouts to prevent sensor hanging.
🛠 Hardware Required
Microcontroller: ESP32-S3 (e.g., DevKitC-1)
Sensor: HC-SR04 Ultrasonic Sensor
LED Strip: WS2815 (12V Addressable RGB)
Power Supply: 12V DC (for LEDs) and 5V/USB (for ESP32)
Logic Level Shifter: (Recommended) 3.3V to 5V for the LED data line.
Resistors: 1kΩ and 2kΩ (for Echo pin voltage divider).
🔌 Wiring Diagram
1. Ultrasonic Sensor (HC-SR04)
HC-SR04 Pin	ESP32-S3 Pin	Notes
VCC	5V / Vin	Power from ESP32 5V pin
Trig	GPIO 7	Digital Output
Echo	GPIO 15	Use Voltage Divider (to 3.3V)
GND	GND	Common Ground
2. LED Strip (WS2815)
WS2815 Wire	Connection Point	Notes
+12V (Red)	12V PSU (+)	Do NOT connect to ESP32
GND (White)	12V PSU (-)	Connect to PSU (-) AND ESP32 GND
DI (Data)	GPIO 35	Data signal from ESP32
BI (Backup)	GND	Tie to Ground if not used
⚠️ IMPORTANT: Always connect the Ground of your 12V power supply to the GND pin of the ESP32.
💻 Software Setup
1. Prerequisites
Install Arduino IDE.
Install the ESP32 Board Manager:
Go to File > Preferences.
Add https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json to Additional Boards Manager URLs.
Go to Tools > Board > Boards Manager, search for esp32, and install the latest version.
2. Libraries
Install the following library via Tools > Manage Libraries:
Adafruit NeoPixel by Adafruit
3. Configuration
Open the .ino file and adjust these variables if necessary:
code
C++
#define NUM_LEDS 30      // Set this to your actual LED count
#define MAX_DISTANCE 100 // Maximum distance to track in cm
📜 Code
The full source code is located in the main project file. It includes:
getDistance(): Handles the pulse timing for the ultrasonic sensor.
displayDistanceOnStrip(): Handles the math for mapping distance to color and LED count.
⚠️ Safety & Troubleshooting
Level Shifting: The ESP32-S3 outputs 3.3V signals. If your WS2815 strip flickers or doesn't respond, use a logic level shifter (like the 74HCT125) to boost the GPIO 35 signal to 5V.
Heat: Ensure your 12V power supply has enough Amps for your LED count (roughly 1A per 20 LEDs at full white).
Echo Pin: The Echo pin outputs 5V. To protect your ESP32-S3, use a voltage divider (1k resistor from Echo to GPIO 15, and 2k resistor from GPIO 15 to GND).
🛠 Author
Your Name - Initial Work - YourGitHubUsername
📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
How to use this on GitHub:
Create a new repository on GitHub.
Create a file named README.md.
Paste the text above into that file and save.
Upload your .ino code file to the same repository.
