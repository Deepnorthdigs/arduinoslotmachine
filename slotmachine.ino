 #include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Library for the ST7735 TFT screen
#include <SPI.h>

// Define the pins for your display 
#define TFT_CS 35   // Chip select pin
#define TFT_RST 34  // Reset pin
#define TFT_DC 36   // Data/Command pin
#define TFT_BL 33   // Backlight pin (TFT_BL/IO33)
#define BUTTON_PIN 0   // BOOT button on the ESP32-S3

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// CONSTANTS
const int NUM_SYMBOLS = 5;
int reels[3];

// Symbol index
const int CIRCLE = 0;
const int SQUARE = 1;
const int STAR = 2;
const int BAR = 3;
const int SEVEN = 4;

// Global Variables
const char* symbol_names[5] = {"CIRCLE", "SQUARE", "STAR", "BAR", "SEVEN"}; 
const char* slot1 = symbol_names[reels[0]];
const char* slot2 = symbol_names[reels[1]];
const char* slot3 = symbol_names[reels[2]];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000); // Give the ESP32-S3 native USB time to register on your PC
  // Initialize the backlight pin
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);  // Turn on the backlight

  // Initialize the display

  tft.initR(INITR_BLACKTAB);    // Specific initialization for the ST7735 screen
  tft.fillScreen(ST77XX_WHITE); // clear screen with black background (colors are reversed)

  // Text Settings
  tft.setTextColor(ST77XX_BLACK); // Set text colour
  tft.setTextSize(2);             // Set text size
  tft.setCursor(10, 50);          // Set the position

  tft.print("PRESS A TO ROLL"); 

  pinMode(0, INPUT_PULLUP);
  while (digitalRead(0) == HIGH) { // check if a pressed
    delay(10);
  }

  tft.fillScreen(ST77XX_WHITE); 
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {   // button pressed
    spin();
    showreels();

    // wait here until the button is let go
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(10);
    }
    delay(50);
  }
}
void spin() {
  reels[0] = random(5);
  reels[1] = random(5);
  reels[2] = random(5);
}
void showreels() {
  slot1 = symbol_names[ reels[0] ];
  slot2 = symbol_names[ reels[1] ];
  slot3 = symbol_names[ reels[2] ];

  tft.fillScreen(ST77XX_WHITE); // clear screen with black background (colors are reversed)

  tft.setCursor(0, 20);      // x = 0, y = 20 pixels from the top (this is "line 1")
  tft.print(slot1);
  tft.print(" | ");
  tft.print(slot2);
  tft.print(" | ");
  tft.print(slot3);
}