/*
  code write for project:
  https://github.com/Ni3nayka/MicroMouse-2025

  run commands:
  g++ ExtraMazeSolver.cpp
  ./a.out

  author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
  write:  March 2025
  modify: March 2025
*/

/*
	run commands:
	g++ ExtraMazeSolver.cpp
	./a.out
*/

#define DEBUGER_CPP
#include "ExtraMazeSolver.h"

/*
v ?-?-?-? ?
|           |  |
? ?-?-?-?-?
|  |           |
? ? ?-?-? ?
|  |        |  |
? ?-?-? ? ?
|           |  |
?-? ?-?-? ?
|     |        |
?-?-?-?-?-?
*/

ExtraMazeSolver maze;

void maze_test(bool up, bool down, bool left, bool right, bool skip_turn=1) {
	maze.exploreCell(up,down,left,right); 
	maze.print();
	int a = maze.getNextMove();
	cout << "next_move: ";
	if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE) cout << "none" << endl;
	if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_FORWARD) cout << "forward" << endl;
	if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_LEFT) cout << "left" << endl;
	if (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_RIGHT) cout << "right" << endl;
	if (skip_turn && (a==EXTRA_MAZE_SOLVER_NEXT_MOVE_LEFT || a==EXTRA_MAZE_SOLVER_NEXT_MOVE_RIGHT)) maze_test(0,0,0,0);	
}

int main() {
	maze.setup();
	maze.x_finish = 3;
	maze.y_finish = 3;
	maze.print();	
	// maze.print(100,100);
	// maze.print(1,1);
	
	maze_test(0,1,0,0); // 0 0 ^ (x y dir)
	maze_test(1,1,0,0);
	maze_test(1,1,0,0);
	maze_test(1,1,0,0); // 0 3 v
	maze_test(1,1,1,0);
	maze_test(0,1,0,0);
	maze_test(0,1,1,1);
	maze_test(0,1,1,0);
	maze_test(1,1,0,0);
	maze_test(1,1,1,0);
	maze_test(1,1,0,0); // 3 5 < 
	//maze.print();
	maze_test(1,1,0,1);
	maze_test(0,1,0,1);
	maze_test(1,1,0,0);
	maze_test(0,1,1,0);
	maze_test(1,1,0,0);
	maze_test(0,1,1,0);
	maze_test(1,1,0,0);
	maze_test(0,1,0,0);
	maze_test(0,0,0,0); // возврат
	maze_test(0,0,0,0); //
	maze_test(0,0,0,0); //
	maze_test(0,0,0,0); //
	maze_test(0,0,0,0); //
	maze_test(0,0,0,0); //
	maze_test(0,0,0,0); //
	maze_test(0,0,0,0); //
	maze_test(1,1,0,0);
	maze_test(0,1,1,0);
	maze_test(1,1,0,0);
	maze_test(1,1,0,0);
	maze_test(1,1,0,0);
	maze_test(1,1,1,0);
	//maze_test(1,1,1,0); // fail algorytm
	maze_test(1,1,0,1);
	maze_test(1,1,0,0);
	maze_test(1,1,0,0);
	maze_test(0,1,1,0);
	maze_test(1,1,0,0);
	maze_test(0,1,1,0);
	maze_test(1,1,0,0);
	maze_test(0 ,1,0,0);
	
	//maze.dir = 2;
	//maze.createAllConnection();
	//ExtraMazeSolverCell cell{1,2,1,0,1,1,1};
	//maze.writeCell(cell);
	/*maze.x = 0; maze.y = 2; maze.exploreCell(0,1,0,1);
	maze.x = 6; maze.y = 4; maze.exploreCell(1,0,1,0);
	maze.x = 1; maze.y = 3; maze.exploreCell(0,0,1,0);
	maze.x = 4; maze.y = 2; maze.exploreCell(1,1,1,0);
	maze.x = 2; maze.y = 0; maze.exploreCell(0,1,0,1);
	maze.x = 3; maze.y = 1; maze.exploreCell(0,1,1,0);
	maze.x = 5; maze.y = 2; maze.exploreCell(1,0,0,1);
	maze.x = 3; maze.y = 0; maze.exploreCell(1,1,0,1);
	maze.x = 1; maze.y = 0;
	maze.print();	

	int a = -1;
	while (a!=EXTRA_MAZE_SOLVER_NEXT_MOVE_NONE) {
		// cout << maze.x << " " << maze.y << " " << maze.dir << endl;
		a = maze.getNextMove();
		cout << a << endl;
		// cout << maze.x << " " << maze.y << " " << maze.dir << endl << endl;
	}*/
	
}
