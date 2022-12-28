/*
Center Console for the financial game
*/

// RED: 5v
// BLACK: GND
// GREEN: A4
// YELLOW: A5

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define ALPH_VNTG_KEY "9LUF2R9E21D6WX65"

#define BUTTON 2

int touched = 0;

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String action[2] = {"UP", "DOWN"};
String assets[5] = {"manufacturing", "retail", "energy", "agriculture", "medical"};

void setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Investopoly!"); // text to display
  oled.display();               // show on OLED
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    touched++;
    Serial.println(touched);
    if (touched == 1) {
      oled.clearDisplay();
      oled.display();
      delay(1000);
      oled.clearDisplay();
      oled.setTextColor(WHITE);     // text color
      oled.setCursor(0, 10);        // position to display
      oled.println(action[random(2)]); // text to display
      oled.println(assets[random(5)]);
      oled.display();
    } else if (touched == 500) {
      oled.clearDisplay();
      oled.display();
      touched = 0;
      while (true) {
        Serial.println(touched);
        if (touched == 500) {
          Serial.println("FIVE HUNDRED");
          break;
        } else if (digitalRead(BUTTON) == HIGH) {
          touched++;
        } else if (digitalRead(BUTTON) == LOW) {
          touched = 0;
        }
      }
    }
  } else if (digitalRead(BUTTON) == LOW) {
    touched = 0;
  }
}