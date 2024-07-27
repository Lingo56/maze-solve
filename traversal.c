#pragma config(Motor, port1, motorLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port4, motorRight, tmotorVex393_MC29, openLoop)

#include "stack.c"
#include "utilities.c"

#define MAX_ROWS 4
#define MAX_COLS 6
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

typedef struct {
    int row;
    int col;
} Parent;

void BasicSolver();
void DrawProgress();

bool algorithmFinished = false;

task main()
{
	GridInit();
	WallGen();

	while(!algorithmFinished){
		BasicSolver();
	}

	while(true){
		displayCenteredTextLine(5,"MAZE SOLVED !!");
		sleep(500);
		eraseDisplay();
		sleep(500);
	}
}

//=====================================================================

// Randomly moves the robot around
int RandomDirection() {
	return random(4);  // Assuming random() generates random number between 0 and n-1
}

void BasicSolver(){
	int dir = RandomDirection();
	int nextRow = CurrentPosRow, nextCol = CurrentPosCol;

  // Check if the move is valid before making a move
  if (CheckWall(dir)) {
      switch (dir) {
          case NORTH:
              currentPos.row++;
              break;
          case EAST:
              currentPos.col++;
              break;
          case SOUTH:
              currentPos.row--;
              break;
          case WEST:
              currentPos.col--;
              break;
          default:
              break;
      }

      // Move the robot in the chosen direction
      MoveForward();
  } else {
      // Turn randomly if wall is detected
      int turnDir = random(2);
      if (turnDir == 0) {
          TurnLeft();
      } else {
          TurnRight();
      }
  }

	if ((CurrentPosCol == TargetPosCol) && (CurrentPosRow == TargetPosRow))
	{
			algorithmFinished = true;
	}
}

// Move the robot forward based on current direction
void MoveForward() {
    // Implement the function to move forward
    // Example: drive forward a certain distance
}

// Turn the robot left
void TurnLeft() {
    // Implement the function to turn left
}

// Turn the robot right
void TurnRight() {
    // Implement the function to turn right
}

// Check if there is a wall in the given direction
bool CheckWall(int direction) {
    // Implement the function using sensors
    // Return true if no wall detected, otherwise false
    return true; // placeholder
}
