/*
  code write for project:
  https://github.com/Ni3nayka/Monster_car/tree/T2C
  and update for:
  https://github.com/Ni3nayka/MicroMouse-2025

  author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
  write:  March 2024
  modify: March 2025

  links:
  https://dronebotworkshop.com/radio-control-arduino-car/
  https://github.com/adafruit/Adafruit_VL53L0X/
*/

/*
// example
#include "lazer.h"
Lazer lazer_1(0x30,18);
Lazer lazer_2(0x31,19);
void setup() {
  Serial.begin(115200);
  firstSetupLazers();
  lazer_1.setup();
  lazer_2.setup();
}
void loop() {
  Serial.println(String(lazer_1.get()) + " " + String(lazer_2.get()));
  delay(100);
}
*/

#pragma once

#include "Adafruit_VL53L0X.h"

#define DISABLE_PIN_DEFAULT -1
#define ADDRESS_DEFAULT -1
#define MAX_LAZER_COUNT 10
#define MAX_LAZER_DISTANCE 1000

int global_lazer_disable_pins[MAX_LAZER_COUNT] = {0};
// int global_lazer_addresses[MAX_LAZER_COUNT] = {0};
int global_lazer_counter = 0;

class Lazer {
  public:
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();
    Lazer(int address = ADDRESS_DEFAULT, int disable_pin=DISABLE_PIN_DEFAULT) {
      global_lazer_disable_pins[global_lazer_counter] = disable_pin;
      global_lazer_counter++;
      Lazer::disable_pin = disable_pin;
      Lazer::enable = 0;
      Lazer::address = address;
    }
    void setup() {
      if (Lazer::disable_pin==DISABLE_PIN_DEFAULT) {
        Lazer::enable = lox.begin();
      } 
      else {
        // start this sensor
        digitalWrite(Lazer::disable_pin,1);
        delay(20);
        Lazer::enable = lox.begin(Lazer::address);
      }
      if (!Lazer::enable) {
        //Serial.println(F("Failed to boot VL53L0X"));
        Serial.print("Failed to boot VL53L0X: address - ");
        Serial.print(address);
        if (disable_pin!=DISABLE_PIN_DEFAULT) {
          Serial.print(" disable_pin - ");
          Serial.print(disable_pin);
        }
        Serial.println();
      } 
    }
    int get() {
      VL53L0X_RangingMeasurementData_t measure;
      Lazer::lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
      if(measure.RangeStatus != 4) {
        return constrain(measure.RangeMilliMeter,0,MAX_LAZER_DISTANCE);
      } 
      else {
        return MAX_LAZER_DISTANCE;
      }
    }
  private:
    int disable_pin, address;
    bool enable;
};

void firstSetupLazers() { // reset lasers
  for (int i = 0; i<global_lazer_counter; i++) {
    if (global_lazer_disable_pins[i]!=DISABLE_PIN_DEFAULT) {
      pinMode(global_lazer_disable_pins[i], OUTPUT);
    }
  }
  // all reset
  for (int i = 0; i<global_lazer_counter; i++) {
    if (global_lazer_disable_pins[i]!=DISABLE_PIN_DEFAULT) {
      digitalWrite(global_lazer_disable_pins[i], 0);
    }
  }
  delay(10);
  // all unreset
  for (int i = 0; i<global_lazer_counter; i++) {
    if (global_lazer_disable_pins[i]!=DISABLE_PIN_DEFAULT) {
      digitalWrite(global_lazer_disable_pins[i], 1);
    }
  }
  delay(10);
  // resetting all
  for (int i = 0; i<global_lazer_counter; i++) {
    if (global_lazer_disable_pins[i]!=DISABLE_PIN_DEFAULT) {
      digitalWrite(global_lazer_disable_pins[i], 0);
    }
  } 
  delay(10);
}
