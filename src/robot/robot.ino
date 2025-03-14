/*
  code write for project:
  https://github.com/Ni3nayka/MicroMouse-2025

  author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
  write:  March 2025
  modify: March 2025
*/

#include "pins.h"

#define ENC_SAVE_MODE
#include <arduino_encoder.h>
Encoder enc1;
Encoder enc2;

// #include <AVOCADO_esp.h>
// #include <easy_arduino_navigator.h>

#include <HNR-252_DCv0_1.h>
MotorShield motors;

#include "ExtraMazeSolver.h"
ExtraMazeSolver maze;

#include "lazer.h"
Lazer lazer_1(LASER_ADDRESS_1, LASER_PIN_1);
Lazer lazer_2(LASER_ADDRESS_2, LASER_PIN_2);
Lazer lazer_3(LASER_ADDRESS_3, LASER_PIN_3);
Lazer lazer_4(LASER_ADDRESS_4, LASER_PIN_4);
Lazer lazer_5(LASER_ADDRESS_5, LASER_PIN_5);

#define MOVE_STABILISATION_TIME 200
#define MOVE_STABILISATION_ENC_POROG 100

#define MOVE_FORWARD_SPEED 20
#define TURN_SPEED 16
#define ONE_MAZE_CELL_CM 20

#define LAZER_MAX_VALUE 100
#define LAZER_WALL_VALUE 200

#define MOVE_FORWARD_ENC_PID_P 0.1 // enc
#define MOVE_FORWARD_ENC_PID_I 0
#define MOVE_FORWARD_ENC_PID_D 0

#define TURN_ENC_PID_P 0.1 // enc
#define TURN_ENC_PID_I 0
#define TURN_ENC_PID_D 0

#define ENC_PARROT_TO_CM 74
#define ENC_PARROT_TO_ANGLE 5.21

#define MOVE_FORWARD_LAZER_PID_P 0.1 // 0.05
#define MOVE_FORWARD_LAZER_PID_I 0
#define MOVE_FORWARD_LAZER_PID_D 0

void setup() {
  Serial.begin(115200);
  motors.setup();  // motors.runs(100,100);
  firstSetupLazers();
  lazer_1.setup();  // lazer_1.get()
  lazer_2.setup();
  lazer_3.setup();
  lazer_4.setup();
  lazer_5.setup();
  enc1.setup(ENC1_PIN_1, ENC1_PIN_2);  // enc1.reverse();  enc1.get();  enc1.clear();
  enc2.setup(ENC2_PIN_1, ENC2_PIN_2);
  Main();
  motors.runs();
}

void Main() {
  // forwardEnc(100);
  // turnEnc(3600);
  forwardLazer(30); // ONE_MAZE_CELL_CM
  // motors.runs(100,100);
  // delay(1000);
  // motors.runs();
  // delay(100);
  // motors.runs(-100,-100);
  // delay(1000);
  // motors.runs();
}

void loop() {
  // Serial.println(String(lazer_1.get()) + " " + String(lazer_2.get()) + " " + String(lazer_3.get()) + " " + String(lazer_4.get()) + " " + String(lazer_5.get()));
  //Serial.println(String(enc1.get()) + " " + String(enc2.get()));
  delay(100);
}

void runMaze() {
  maze.x = 0;
  maze.y = 0;
  maze.x_finish = 5;
  maze.y_finish = 5;
  int a = -1;
  bool backward = 0;
  while (a!=EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE) {
    maze.exploreCell(lazer_3.get()>LAZER_WALL_VALUE,backward,lazer_1.get()>LAZER_WALL_VALUE,lazer_5.get()>LAZER_WALL_VALUE);
    backward = 1;
    a = maze.getNextMove();
    if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_FORWARD) forwardLazer(ONE_MAZE_CELL_CM);
    if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_LEFT) turnEnc(90);
    if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_RIGHT) turnEnc(-90);
  }
}

void forwardLazer(long int distance) {
  distance *= ENC_PARROT_TO_CM;
  enc1.clear();
  motors.runs(MOVE_FORWARD_SPEED,MOVE_FORWARD_SPEED);
  long int e, e_old, p, d, i, pid;
  while (distance > enc1.get()) {
    e = constrain(lazer_2.get(),0,LAZER_MAX_VALUE) - constrain(lazer_4.get(),0,LAZER_MAX_VALUE);
    //e = lazer_1.get() + lazer_2.get() - lazer_4.get() - lazer_5.get();
    Serial.println(e);
    // Serial.println(enc1.get());
    p = e;
    d = e - e_old;
    e_old = e;
    i = i * 0.95 + e;
    pid = p * MOVE_FORWARD_LAZER_PID_P + i * MOVE_FORWARD_LAZER_PID_I + d * MOVE_FORWARD_LAZER_PID_D;
    // pid = constrain(pid,MOVE_FORWARD_SPEED,MOVE_FORWARD_SPEED);
    motors.runs(MOVE_FORWARD_SPEED+pid,MOVE_FORWARD_SPEED-pid);
  }
  motors.runs(-50,-50);
  delay(50);
  motors.runs();
}

void forwardEnc(long int distance) {
  distance *= ENC_PARROT_TO_CM;
  enc1.clear();
  enc2.clear();
  long int t = millis() + MOVE_STABILISATION_TIME, e, e_old, p, d, i, pid, e_lazer = 0;
  while (2*distance - enc1.get() - enc2.get() > 0) { // (t > millis())
    // if (abs(distance - enc1.get()) + abs(distance - enc2.get()) > MOVE_STABILISATION_ENC_POROG) {
    // if (2*distance - enc1.get() - enc2.get() > 0) {
    //   t = millis() + MOVE_STABILISATION_TIME;
    // }
    //e_lazer = 
    e = enc1.get() - enc2.get() + e_lazer;
    p = e;
    d = e - e_old;
    e_old = e;
    i = i * 0.95 + e;
    pid = p * MOVE_FORWARD_ENC_PID_P + i * MOVE_FORWARD_ENC_PID_I + d * MOVE_FORWARD_ENC_PID_D;
    // pid = constrain(pid,MOVE_FORWARD_SPEED,MOVE_FORWARD_SPEED);
    motors.runs(MOVE_FORWARD_SPEED+pid,MOVE_FORWARD_SPEED-pid);
    // motors.runs(pid,pid);
  }
  // motors.runs();
  // delay(100);
  motors.runs(-50,-50);
  delay(50);
  motors.runs();
}

void turnEnc(long int distance) {
  distance *= ENC_PARROT_TO_ANGLE;
  int sign = 1;
  if (distance<0) sign *= -1;
  enc1.clear();
  enc2.clear();
  long int t = millis() + MOVE_STABILISATION_TIME, e, e_old, p, d, i, pid;
  while (abs(distance) - abs(enc1.get()) > 0) {
    e = enc1.get() + enc2.get();
    p = e;
    d = e - e_old;
    e_old = e;
    i = i * 0.95 + e;
    pid = p * TURN_ENC_PID_P + i * TURN_ENC_PID_I + d * TURN_ENC_PID_D;
    // pid = constrain(pid,MOVE_FORWARD_SPEED,MOVE_FORWARD_SPEED);
    motors.runs(sign*TURN_SPEED-pid,-sign*TURN_SPEED-pid);
    // motors.runs(pid,pid);
  }
  // motors.runs();
  // delay(100);
  motors.runs(-TURN_SPEED*sign,TURN_SPEED*sign);
  delay(50);
  motors.runs();
}
