#pragma config(Motor, port1, motorLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port4, motorRight, tmotorVex393_MC29, openLoop)

#include "stack.c"
#include "utilities.c"

#define TARGET_DISTANCE_FORWARD 500
#define TARGET_DISTANCE_TURN 300
#define MOTOR_SPEED 30

#define MAX_ROWS 4
#define MAX_COLS 6
#define FORWARD 0
#define LEFT  1
#define RIGHT  2

typedef struct {
    int row;
    int col;
} Parent;

void BasicSolver();
void MoveForward();
void TurnLeft();
void TurnRight();
void CheckWall();

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
          case FORWARD:
              currentPos.row++;
              break;
          case LEFT:
              currentPos.col++;
              break;
          case RIGHT:
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
    nMotorEncoder[motorLeft] = 0;//reset the value of encoder B to zero
		nMotorEncoder[motorRight] = 0;//reset the value of encoder C to zero

		while(nMotorEncoder[motorLeft] < TARGET_DISTANCE_FORWARD)//while encoderB is less than 720
		{
			motor[motorLeft] = MOTOR_SPEED;//turn on motorB at 50% power
			motor[motorRight] = MOTOR_SPEED;//turn on motorC at 50% power
		}

		motor[motorLeft] = 0; //Turn off motorB
		motor[motorRight] = 0; //Turn off motorC
}

// Turn the robot left
void TurnLeft() {
    nMotorEncoder[motorLeft] = 0;//reset the value of encoder B to zero
		nMotorEncoder[motorRight] = 0;//reset the value of encoder C to zero

		while(nMotorEncoder[motorRight] < TARGET_DISTANCE)//while encoderB is less than 720
		{
			motor[motorLeft] = -MOTOR_SPEED;//turn on motorB at 50% power
			motor[motorRight] = MOTOR_SPEED;//turn on motorC at 50% power
		}

		motor[motorLeft] = 0; //Turn off motorB
		motor[motorRight] = 0; //Turn off motorC
}

// Turn the robot right
void TurnRight() {
    nMotorEncoder[motorLeft] = 0;//reset the value of encoder B to zero
		nMotorEncoder[motorRight] = 0;//reset the value of encoder C to zero

		while(nMotorEncoder[motorLeft] < TARGET_DISTANCE)//while encoderB is less than 720
		{
			motor[motorLeft] = MOTOR_SPEED;//turn on motorB at 50% power
			motor[motorRight] = -MOTOR_SPEED;//turn on motorC at 50% power
		}

		motor[motorLeft] = 0; //Turn off motorB
		motor[motorRight] = 0; //Turn off motorC
}

// Check if there is a wall in the given direction
bool CheckWall(int direction) {
    // Implement the function using sensors
    // Return true if no wall detected, otherwise false
    return true; // placeholder
}
