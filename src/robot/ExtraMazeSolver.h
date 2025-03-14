/*
  code write for project:
  https://github.com/Ni3nayka/MicroMouse-2025

  author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
  write:  March 2025
  modify: March 2025
*/

#pragma once

/*

	run commands:
	g++ ExtraMazeSolver.cpp
	./a.out
*/

// #define DEBUGER_CPP

#ifdef DEBUGER_CPP
#include <iostream>
using namespace std;
#else
#define string String
#endif

#define EXTRA_MAZE_SOLVER_SIZE_X 7
#define EXTRA_MAZE_SOLVER_SIZE_Y 5 

#define EXTRA_MAZE_SOLVER_SIZE_TESTER(x,y) (x>=0 && x<EXTRA_MAZE_SOLVER_SIZE_X && y>=0 && y<EXTRA_MAZE_SOLVER_SIZE_Y)

#define EXTRA_MAZE_SOLVER_DIR_UP 0
#define EXTRA_MAZE_SOLVER_DIR_DOWN 2
#define EXTRA_MAZE_SOLVER_DIR_LEFT 1
#define EXTRA_MAZE_SOLVER_DIR_RIGHT 3

#define EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE 0
#define EXTRA_MAZE_SOLVER_NEXT_MOVE_FORWARD 1
#define EXTRA_MAZE_SOLVER_NEXT_MOVE_LEFT 2
#define EXTRA_MAZE_SOLVER_NEXT_MOVE_RIGHT 3

struct ExtraMazeSolverCell {
	int x,y;
	bool up, down, left, right,visited;
};

class ExtraMazeSolver {
	public:
		// byte:  up, down, left, right,visited,*,*,* (обратная запись)
		uint8_t maze[EXTRA_MAZE_SOLVER_SIZE_Y][EXTRA_MAZE_SOLVER_SIZE_X];
		int x, y, dir, x_finish,y_finish;
		bool warning; // была зафиксирована логическая ошибка
		void setup() {
			ExtraMazeSolver::createAllConnection();
			ExtraMazeSolver::x = 0;
			ExtraMazeSolver::y = 0;
			ExtraMazeSolver::dir = EXTRA_MAZE_SOLVER_DIR_UP;
			ExtraMazeSolver::warning = 0;
			ExtraMazeSolver::x_finish = ExtraMazeSolver::x;
			ExtraMazeSolver::y_finish = ExtraMazeSolver::y;
			ExtraMazeSolver::x_finish_save = ExtraMazeSolver::x;
			ExtraMazeSolver::y_finish_save = ExtraMazeSolver::y;
			ExtraMazeSolver::x_save = ExtraMazeSolver::x;
			ExtraMazeSolver::y_save = ExtraMazeSolver::y;
			ExtraMazeSolver::dir_save = ExtraMazeSolver::dir;
		}
		// ======================= ARRAY ==============================================================
		void createAllConnection() {
			for (int y=0; y<EXTRA_MAZE_SOLVER_SIZE_Y; y++) {
				for (int x=0; x<EXTRA_MAZE_SOLVER_SIZE_X; x++) {
					maze[y][x] = 0b00001111;
				}
			}
			for (int y = 0; y<EXTRA_MAZE_SOLVER_SIZE_Y; y++) {
				ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(0,y);
				cell.left = 0;
				ExtraMazeSolver::writeCell(cell);	
				cell = ExtraMazeSolver::getCell(EXTRA_MAZE_SOLVER_SIZE_X-1,y);
				cell.right = 0;
				ExtraMazeSolver::writeCell(cell);
			}
			for (int x = 0; x<EXTRA_MAZE_SOLVER_SIZE_X; x++) {
				ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(x,0);
				cell.up = 0;
				ExtraMazeSolver::writeCell(cell);	
				cell = ExtraMazeSolver::getCell(x,EXTRA_MAZE_SOLVER_SIZE_Y-1);
				cell.down = 0;
				ExtraMazeSolver::writeCell(cell);
			}
		}
		void destroyAllConnection() {
			for (int y=0; y<EXTRA_MAZE_SOLVER_SIZE_Y; y++) {
				for (int x=0; x<EXTRA_MAZE_SOLVER_SIZE_X; x++) {
					maze[y][x] = 0b00000000;
				}
			}
		}
		ExtraMazeSolverCell getCell(int x, int y) {
			ExtraMazeSolverCell cell{-1,-1,0,0,0,0,0};
			if (EXTRA_MAZE_SOLVER_SIZE_TESTER(x,y)) {
				cell.x = x;
				cell.y = y;
				int data = maze[y][x];
				cell.up      = (data>>0)&1;
				cell.down = (data>>1)&1;
				cell.left     = (data>>2)&1;
				cell.right  = (data>>3)&1;
				cell.visited = (data>>4)&1;
			}
			return cell;
		}
		void writeCell(ExtraMazeSolverCell cell, bool warning = 1) {
			if (EXTRA_MAZE_SOLVER_SIZE_TESTER(cell.x,cell.y)) {
				ExtraMazeSolver::maze[cell.y][cell.x] = (int(cell.up)<<0) + (int(cell.down)<<1) + (int(cell.left)<<2) + (int(cell.right)<<3) + (int(cell.visited)<<4);
			}
			else if (warning) {
				ExtraMazeSolver::debugPrint("WARNING: no this coordinate in maze: x = " + to_string(cell.x) + " y = " + to_string(cell.y));
				ExtraMazeSolver::warning = 1;
			}
		}	
		void print(int x = -1, int y = -1) {
			if (x>=0 && y>=0) ExtraMazeSolver::printCell(x,y);
			else {
				for (y=0; y<EXTRA_MAZE_SOLVER_SIZE_Y; y++) {
					for (x=0; x<EXTRA_MAZE_SOLVER_SIZE_X; x++) {
						ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(x,y);
						if (cell.up) ExtraMazeSolver::debugPrint(" | ",0);
						else ExtraMazeSolver::debugPrint("   ",0);
					}
					ExtraMazeSolver::debugPrint();
					for (x=0; x<EXTRA_MAZE_SOLVER_SIZE_X; x++) {
						ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(x,y);
						if (cell.left) ExtraMazeSolver::debugPrint("-",0);
						else ExtraMazeSolver::debugPrint(" ",0);
						if (ExtraMazeSolver::x==x && ExtraMazeSolver::y==y) { // printing robot
							 if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_UP) ExtraMazeSolver::debugPrint("^",0); 
							 else if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_DOWN) ExtraMazeSolver::debugPrint("v",0);
							 else if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_LEFT) ExtraMazeSolver::debugPrint("<",0);
							 else if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_RIGHT) ExtraMazeSolver::debugPrint(">",0);
							 else ExtraMazeSolver::debugPrint("o",0); // некорректное направление 
						}
						else if (cell.visited) ExtraMazeSolver::debugPrint("+",0);
						else ExtraMazeSolver::debugPrint("?",0);
						if (cell.right) ExtraMazeSolver::debugPrint("-",0);
						else ExtraMazeSolver::debugPrint(" ",0);
					}
					ExtraMazeSolver::debugPrint();
					for (x=0; x<EXTRA_MAZE_SOLVER_SIZE_X; x++) {
						ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(x,y);
						if (cell.down) ExtraMazeSolver::debugPrint(" | ",0);
						else ExtraMazeSolver::debugPrint("   ",0);
					}
					ExtraMazeSolver::debugPrint();
				}
			} 	
		}	
		// ======================= MOVE ==============================================================
		void exploreCell(bool up /* forward */, bool down /* backward */, bool left, bool right, int x = -1, int y = -1, int dir = -1) {
			// по дефолту - подтягиваем из памяти координату и направление
			if (x==-1 && y==-1) {
				x = ExtraMazeSolver::x;
				y = ExtraMazeSolver::y;
			}
			if (dir==-1) {
				dir = ExtraMazeSolver::dir;
			}
			// проверяем, не покинули ли мы лабиринт
			if (!EXTRA_MAZE_SOLVER_SIZE_TESTER(x,y)) {
				ExtraMazeSolver::debugPrint("WARNING: robot left maze: x = " + to_string(ExtraMazeSolver::x) + " y = " + to_string(ExtraMazeSolver::y));
				ExtraMazeSolver::warning = 1;
				return;
			}
			// проверяем направление на корректность
			if (dir!=EXTRA_MAZE_SOLVER_DIR_UP && dir!=EXTRA_MAZE_SOLVER_DIR_DOWN && dir!=EXTRA_MAZE_SOLVER_DIR_LEFT && dir!=EXTRA_MAZE_SOLVER_DIR_RIGHT) {
				ExtraMazeSolver::debugPrint("WARNING: unknow robot direction: " + to_string(ExtraMazeSolver::dir));
				ExtraMazeSolver::warning = 1;
				return;
			}
			// вращаем робота в связи с его направлением
			{
				int up_save = up, down_save = down, left_save = left, right_save = right;
				//if (dir==EXTRA_MAZE_SOLVER_DIR_UP)
				if (dir==EXTRA_MAZE_SOLVER_DIR_DOWN) {
					up = down_save;
					down = up_save;
					left = right_save;
					right = left_save;
				}
				if (dir==EXTRA_MAZE_SOLVER_DIR_LEFT) {
					up = left_save;
					down = right_save;
					left = down_save;
					right = up_save;
				}
				if (dir==EXTRA_MAZE_SOLVER_DIR_RIGHT) {
					up = right_save;
					down = left_save;
					left = up_save;
					right = down_save;
				}
			}
			// убираем невозможные связи в связи с границами лабиринта
			if (ExtraMazeSolver::y<=0 && up==1) {
				ExtraMazeSolver::debugPrint("WARNING: from this coordinate robot can't move up: x = " + to_string(ExtraMazeSolver::x) + " y = " + to_string(ExtraMazeSolver::y));
				ExtraMazeSolver::warning = 1;
				up = 0;
			}
			if (ExtraMazeSolver::y>=EXTRA_MAZE_SOLVER_SIZE_Y-1 && down==1) {
				ExtraMazeSolver::debugPrint("WARNING: from this coordinate robot can't move down: x = " + to_string(ExtraMazeSolver::x) + " y = " + to_string(ExtraMazeSolver::y));
				ExtraMazeSolver::warning = 1;
				down = 0;
			}
			if (ExtraMazeSolver::x<=0 && left==1) {
				ExtraMazeSolver::debugPrint("WARNING: from this coordinate robot can't move left: x = " + to_string(ExtraMazeSolver::x) + " y = " + to_string(ExtraMazeSolver::y));
				ExtraMazeSolver::warning = 1;
				left = 0;
			}
			if (ExtraMazeSolver::x>=EXTRA_MAZE_SOLVER_SIZE_X-1 && right==1) {
				ExtraMazeSolver::debugPrint("WARNING: from this coordinate robot can't move right: x = " + to_string(ExtraMazeSolver::x) + " y = " + to_string(ExtraMazeSolver::y));
				ExtraMazeSolver::warning = 1;
				right = 0;
			}
			// заносим проверенные данные в память
			ExtraMazeSolverCell cell{x,y,up,down,left,right,1};
			ExtraMazeSolver::writeCell(cell);
			cell = ExtraMazeSolver::getCell(x,y-1);
			cell.down = up;
			ExtraMazeSolver::writeCell(cell,0);
			cell = ExtraMazeSolver::getCell(x,y+1);
			cell.up = down;
			ExtraMazeSolver::writeCell(cell,0);
			cell = ExtraMazeSolver::getCell(x-1,y);
			cell.right = left;
			ExtraMazeSolver::writeCell(cell,0);
			cell = ExtraMazeSolver::getCell(x+1,y);
			cell.left = right;
			ExtraMazeSolver::writeCell(cell,0);
		}
		void robotMoveForward() {
			ExtraMazeSolver::repairDir();
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_UP) y--;	
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_DOWN) y++;	
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_LEFT) x--;	
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_RIGHT) x++;	
			if (EXTRA_MAZE_SOLVER_SIZE_TESTER(ExtraMazeSolver::x,ExtraMazeSolver::y)) {
				ExtraMazeSolver::debugPrint("WARNING: (robotMoveForward) robot left maze: x = " + to_string(ExtraMazeSolver::x) + " y = " + to_string(ExtraMazeSolver::y));
				ExtraMazeSolver::warning = 1;
				// тут возможно надо что-то сделать.....но пока алгоритмически не понятно что делать в таком случае
			}
		}
		void robotTurnLeft() {
			ExtraMazeSolver::dir++;
			ExtraMazeSolver::repairDir();
		}
		void robotTurnRight() {
			ExtraMazeSolver::dir--;
			ExtraMazeSolver::repairDir();
		}
		int getNextMove() {
			if (ExtraMazeSolver::x==ExtraMazeSolver::x_finish && ExtraMazeSolver::y==ExtraMazeSolver::y_finish) {
				// мы на финише
				return EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE;
			}
			else if (ExtraMazeSolver::x==ExtraMazeSolver::x_save && ExtraMazeSolver::x_finish==ExtraMazeSolver::x_finish_save && 
				     ExtraMazeSolver::y==ExtraMazeSolver::y_save && ExtraMazeSolver::y_finish==ExtraMazeSolver::y_finish_save &&
				     ExtraMazeSolver::dir_save==ExtraMazeSolver::dir) {
				// все ок, маршрут была ранее сгенерирован, мы с него никуда не сходили 
				// пока тестовая реализация, пока нет деикстры
				return ExtraMazeSolver::algorytmLeftArm();
			}
			else {
				// Мы как-то изменили маршрут, его надо перегенерировать
				ExtraMazeSolver::x_save==ExtraMazeSolver::x;
				ExtraMazeSolver::x_finish_save==ExtraMazeSolver::x_finish;
				ExtraMazeSolver::y_save==ExtraMazeSolver::y;
				ExtraMazeSolver::y_finish_save==ExtraMazeSolver::y_finish;
				ExtraMazeSolver::dir==ExtraMazeSolver::dir_save;
				// пока тестовая реализация, пока нет деикстры
				ExtraMazeSolver::next_move_save_for_algorytm_left_arm = EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE;
				return ExtraMazeSolver::getNextMove();
			}
			return EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE; // мало-ли багнет
		}
	private:
		int x_finish_save,y_finish_save,x_save,y_save, dir_save;
		int next_move_save_for_algorytm_left_arm;
		// ======================= NAVIGATOR ===========================================================
		void dijkstra() {} // ну мы да....
		int algorytmLeftArm() {
			// если было запомнено предыдущее действие
			if (ExtraMazeSolver::next_move_save_for_algorytm_left_arm!=EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE) {
				int a = ExtraMazeSolver::next_move_save_for_algorytm_left_arm;
				ExtraMazeSolver::next_move_save_for_algorytm_left_arm = EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE;
				return a;
			}
			// из памяти берем данные
			ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(ExtraMazeSolver::x,ExtraMazeSolver::y);
			// создаем переменные для алгоритма левой руки (1 - можно ехать, 0 - нет)
			bool forward = 0;
			bool left = 0;
			ExtraMazeSolver::repairDir(); // ну мало ли
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_UP) {
				forward = cell.up;
				left = cell.left;
			} 
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_DOWN) {
				forward = cell.down;
				left = cell.right;
			} 
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_LEFT) {
				forward = cell.left;
				left = cell.down;
			} 
			if (ExtraMazeSolver::dir==EXTRA_MAZE_SOLVER_DIR_RIGHT) {
				forward = cell.right;
				left = cell.up;
			} 
			// алгоритм левой руки
			if (left) {
				ExtraMazeSolver::next_move_save_for_algorytm_left_arm = EXTRA_MAZE_SOLVER_NEXT_MOVE_FORWARD;
				return EXTRA_MAZE_SOLVER_NEXT_MOVE_LEFT;
			}
			else if (forward) {
				return EXTRA_MAZE_SOLVER_NEXT_MOVE_FORWARD;
			}
			else {
				return EXTRA_MAZE_SOLVER_NEXT_MOVE_RIGHT;
			}
		}
		// ======================= ADDITION ===========================================================
		void repairDir() {
			// ради оптимальности забиваем на структуру:
			while (ExtraMazeSolver::dir>3) ExtraMazeSolver::dir -= 3;
			while (ExtraMazeSolver::dir<0) ExtraMazeSolver::dir += 3;
		}
		void printCell(int x, int y) {
			ExtraMazeSolverCell cell = ExtraMazeSolver::getCell(x,y);
			ExtraMazeSolver::debugPrint(
			                     "x = " + to_string(cell.x) 
							 + " y = " + to_string(cell.y) + ": " 
							 + " up = " + to_string(cell.up) 
							 + " down = " + to_string(cell.down) 
							 + " left = " + to_string(cell.left) 
							 + " right = " + to_string(cell.right) 
							 + " visited = " + to_string(cell.visited));	
		}
    #ifndef DEBUGER_CPP
    String to_string(long int a) {
      return String(a);
    }
    #endif
		void debugPrint(string s="", bool new_line = 1) {
			if (new_line) s += "\n";
			#ifdef DEBUGER_CPP
			cout << s;
			#else
			Serial.print(s);
			#endif
		}
};
