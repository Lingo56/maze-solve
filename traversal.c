#pragma config(Motor,  motorA,          motorSensor,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorLeft,     tmotorEV3_Large, PIDControl)
#pragma config(Motor,  motorD,          motorRight,    tmotorEV3_Large, PIDControl)
#pragma config(Sensor, S2, ultrasonicSensor, sensorSONAR)

#include "stack.c"
#include "utilities.c"
#include "sensorLogic.c"

#define TARGET_DISTANCE_FORWARD 500
#define TARGET_DISTANCE_TURN 215
#define MOTOR_SPEED 25

#define MAX_ROWS 4
#define MAX_COLS 6
#define LEFT 0
#define FORWARD  1
#define RIGHT  2

typedef struct {
    int row;
    int col;
} Parent;

void BasicSolver();
void MoveForward();
void TurnLeft();
void TurnRight();

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
	return random(2);  // Assuming random() generates random number between 0 and n-1
}

void BasicSolver(){
	int dir = RandomDirection();
	int nextRow = CurrentPosRow, nextCol = CurrentPosCol;

  // Check if the move is valid before making a move
  if (!CheckWall(dir)) {
      switch (dir) {
          case FORWARD:
              MoveForward();
              break;
          case LEFT:
              TurnLeft();
              MoveForward();
              break;
          case RIGHT:
              TurnRight();
              MoveForward();
              break;
          default:
              break;
      }
  }

  sleep(2000);

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

		while(nMotorEncoder[motorRight] < TARGET_DISTANCE_TURN)//while encoderB is less than 720
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

		while(nMotorEncoder[motorLeft] < TARGET_DISTANCE_TURN)//while encoderB is less than 720
		{
			motor[motorLeft] = MOTOR_SPEED;//turn on motorB at 50% power
			motor[motorRight] = -MOTOR_SPEED;//turn on motorC at 50% power
		}

		motor[motorLeft] = 0; //Turn off motorB
		motor[motorRight] = 0; //Turn off motorC
}
