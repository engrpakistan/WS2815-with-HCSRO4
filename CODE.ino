#include <Adafruit_NeoPixel.h>

// --- Pin Definitions ---
#define TRIG_PIN 7       // HC-SR04 Trigger pin
#define ECHO_PIN 15      // HC-SR04 Echo pin
#define LED_PIN  35      // WS2815 Data pin
#define NUM_LEDS 10      // Change this to the number of LEDs on your strip

// --- Constants ---
#define MAX_DISTANCE 50 // Maximum distance we want to track (in cm)

// Initialize NeoPixel object
// WS2815 usually uses GRB color order
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);

  // Initialize Ultrasonic Sensor Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize LED Strip
  strip.begin();
  strip.show();            // Initialize all pixels to 'off'
  strip.setBrightness(255); // Set brightness (0-255)
  
  Serial.println("System Initialized...");
}

void loop() {
  long distance = getDistance();
  
  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Visual Effect: Mapping distance to LED display
  displayDistanceOnStrip(distance);

  delay(50); // Small delay for stability
}

/**
 * Trigger the HC-SR04 and calculate the distance in cm
 */
long getDistance() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Set the trigger pin HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin (returns the sound wave travel time in microseconds)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout

  // Calculate distance: (speed of sound is 0.034 cm/us)
  // Divide by 2 because the sound goes out and back
  long distanceCm = duration * 0.034 / 2;

  // If distance is out of range, return max
  if (distanceCm <= 0 || distanceCm > MAX_DISTANCE) return MAX_DISTANCE;
  
  return distanceCm;
}

/**
 * Logic to control the LEDs based on distance
 * Closer = More Red
 * Further = More Green
 */
void displayDistanceOnStrip(long dist) {
  // Map distance (0 to MAX_DISTANCE) to number of LEDs to light up (0 to NUM_LEDS)
  // We flip it so closer objects light up more LEDs
  int numLedsToLight = map(dist, 10, MAX_DISTANCE, NUM_LEDS, 0);
  
  // Map distance to color (Red for close, Green for far)
  // dist 0 = Red(255,0,0), dist MAX = Green(0,255,0)
  uint8_t r = map(dist, 0, MAX_DISTANCE, 255, 0);
  uint8_t g = map(dist, 0, MAX_DISTANCE, 0, 255);
  uint8_t b = 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < numLedsToLight) {
      strip.setPixelColor(i, strip.Color(r, g, b)); // Set color based on calculation
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off remaining LEDs
    }
  }

  strip.show(); // Push the data to the strip
}