/*
sine graph on OLED

OLED wire connecction I2C OLED & UNO
OLED Pin	Arduino Uno / Mega
VCC	5V
GND	GND
SDA	A4 (Uno) / 20 (Mega)
SCL	A5 (Uno) / 21 (Mega)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define AMPLITUDE 20      // Height of sine wave (in pixels)
#define FREQUENCY 0.2     // Controls number of cycles across width
#define OFFSET_Y 32       // Vertical offset (middle of screen)
#define STEP 1            // Step per X axis

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    while (true);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();

  // Draw X-axis
  display.drawFastHLine(0, OFFSET_Y, SCREEN_WIDTH, SSD1306_WHITE);

  // Draw sine wave
  for (int x = 0; x < SCREEN_WIDTH - STEP; x += STEP) {
    float radians1 = x * FREQUENCY;
    float radians2 = (x + STEP) * FREQUENCY;

    int y1 = OFFSET_Y - AMPLITUDE * sin(radians1);
    int y2 = OFFSET_Y - AMPLITUDE * sin(radians2);

    display.drawLine(x, y1, x + STEP, y2, SSD1306_WHITE);
  }

  display.display();
  delay(1000); // Update every second
}
