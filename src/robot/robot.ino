/*
  code write for project:
  https://github.com/Ni3nayka/MicroMouse-2025

  author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
  write:  March 2025
  modify: March 2025
*/

#include <arduino_encoder.h>
// #include <AVOCADO_esp.h>
#include <easy_arduino_navigator.h>
#include <HNR-252_DCv0_1.h>
#include "ExtraMazeSolver.h"
#include "lazer.h"
Lazer lazer_1(0x30,15);
Lazer lazer_2(0x31,16);
Lazer lazer_3(0x32,17);
Lazer lazer_4(0x33,5);
// Lazer lazer_2(0x34,19);

void setup(){
  Serial.begin(115200);
  firstSetupLazers();
  lazer_1.setup();
  lazer_2.setup();
  lazer_3.setup();
  lazer_4.setup();
}

void loop() { 
  Serial.println(String(lazer_1.get()) + " " + String(lazer_2.get()) + " " + String(lazer_3.get()) + " " + String(lazer_4.get()));
  delay(100);
}


