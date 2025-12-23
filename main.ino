#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins (example placeholders)
#define ENC_A 2
#define ENC_B 3
#define BUTTON_PIN 4
#define BUZZER_PIN 5

Encoder encoder(ENC_A, ENC_B);

// Clock variables
int hours = 12;
int minutes = 0;
int alarmHour = 7;
int alarmMinute = 0;

// State variables
bool settingTime = false;
bool alarmRinging = false;
int volume = 5;

unsigned long lastTick = 0;
long lastEncPos = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  updateClock();
  readEncoder();
  checkButton();
  checkAlarm();
  drawScreen();
}
