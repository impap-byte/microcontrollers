#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object
const int sec_res_val = 0;
const int min_res_val = 25;
const int sec_res_val_break = 0;
const int min_res_val_break = 5;
const int sec_res_val_r = 0;
const int min_res_val_r = 20;
int seconds = sec_res_val;
int minutes = min_res_val;
int set = 1;
int buzzer = A1;
void setup() {
  pinMode(buzzer, OUTPUT);
  byte numDigits = 4;   
  byte digitPins[] = {10, 11, 12, 13}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4}; //Segments: A,B,C,D,E,F,G,Period
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  
}

void loop() {
  static unsigned long timer = millis();
  
  
  if (millis() - timer >= 1000) {
    timer += 1000;
    seconds--; // 100 milliSeconds is equal to 1 deciSecond
    if (seconds < 0)
    {
      seconds = 59;
      minutes--;
    }
    if (minutes < 0) { // Reset to 0 after counting for 1000 seconds.
      set++;
      if (set % 8 == 0)
      {
        digitalWrite(buzzer, HIGH);
        delay(400);
        digitalWrite(buzzer, LOW);
        minutes = min_res_val_r;
        seconds = sec_res_val_r;
      }
      else if (set % 2 == 0)
      {
        minutes = min_res_val_break;
        seconds = sec_res_val_break;
      }
      else
      {
        minutes = min_res_val;
        seconds = sec_res_val;
      }
      sevseg.blank();
      digitalWrite(buzzer, HIGH);
      delay(400);
      digitalWrite(buzzer, LOW);
    }
    int displaynum = (minutes * 100) + (seconds);
    sevseg.setNumber(displaynum, 2);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
