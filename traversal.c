#pragma config(Motor,  motorA,          motorSensor,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorLeft,     tmotorEV3_Large, PIDControl)
#pragma config(Motor,  motorD,          motorRight,    tmotorEV3_Large, PIDControl)
#pragma config(Sensor, S2, ultrasonicSensor, sensorSONAR)

#include "stack.c"
#include "utilities.c"
#include "sensor-logic.c"
#include "robot-movement.c"

// Direction Codes
#define LEFT 0
#define FORWARD  1
#define RIGHT  2
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

void BasicSolver();
void DrawProgress();

bool algorithmFinished = false;

task main()
{
	GridInit();
  WallGen();

	while(!algorithmFinished){
    if (!isPaused) {
        DrawProgress();
        BasicSolver();
    }
    checkTogglePause(); // Check if middle button is pressed
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
	return random(2);  // Assuming random() generates random number between 0 and n-1
}

void BasicSolver() {
    int dir = RandomDirection();
    bool wallDetected = CheckWall(dir);

    // Update grid based on current direction and wall detection
    switch (dir) {
        case FORWARD:
            if (wallDetected) {
                switch (RobotDirection) {
                    case 0: Grid[CurrentPosRow][CurrentPosCol].NorthWall = 1; break;
                    case 1: Grid[CurrentPosRow][CurrentPosCol].EastWall = 1; break;
                    case 2: Grid[CurrentPosRow][CurrentPosCol].SouthWall = 1; break;
                    case 3: Grid[CurrentPosRow][CurrentPosCol].WestWall = 1; break;
                }
            } else {
            		switch (RobotDirection) {
								  case 0: // North
								      CurrentPosRow++;
								      break;
								  case 1: // East
								      CurrentPosCol++;
								      break;
								  case 2: // South
								      CurrentPosRow--;
								      break;
								  case 3: // West
								      CurrentPosCol--;
								      break;
								}

                MoveForward();
            }
            break;
        case LEFT:
            if (wallDetected) {
                switch (RobotDirection) {
                    case 0: Grid[CurrentPosRow][CurrentPosCol].WestWall = 1; break;
                    case 1: Grid[CurrentPosRow][CurrentPosCol].NorthWall = 1; break;
                    case 2: Grid[CurrentPosRow][CurrentPosCol].EastWall = 1; break;
                    case 3: Grid[CurrentPosRow][CurrentPosCol].SouthWall = 1; break;
                }
            } else {
                TurnLeft();

                switch (RobotDirection) {
								  case 0: // North
								      CurrentPosRow++;
								      break;
								  case 1: // East
								      CurrentPosCol++;
								      break;
								  case 2: // South
								      CurrentPosRow--;
								      break;
								  case 3: // West
								      CurrentPosCol--;
								      break;
								}

                MoveForward();
            }
            break;
        case RIGHT:
            if (wallDetected) {
                switch (RobotDirection) {
                    case 0: Grid[CurrentPosRow][CurrentPosCol].EastWall = 1; break;
                    case 1: Grid[CurrentPosRow][CurrentPosCol].SouthWall = 1; break;
                    case 2: Grid[CurrentPosRow][CurrentPosCol].WestWall = 1; break;
                    case 3: Grid[CurrentPosRow][CurrentPosCol].NorthWall = 1; break;
                }
            } else {
                TurnRight();

                switch (RobotDirection) {
								  case 0: // North
								      CurrentPosRow++;
								      break;
								  case 1: // East
								      CurrentPosCol++;
								      break;
								  case 2: // South
								      CurrentPosRow--;
								      break;
								  case 3: // West
								      CurrentPosCol--;
								      break;
								}

                MoveForward();
            }
            break;
        default:
            break;
    }

    // Check if target is reached
    if ((CurrentPosCol == TargetPosCol) && (CurrentPosRow == TargetPosRow)) {
        algorithmFinished = true;
    }
}

void DrawProgress() {
    GridDraw();
    DisplayStartandEnd();
    DrawBot();
    sleep(2000);
    eraseDisplay();
}
