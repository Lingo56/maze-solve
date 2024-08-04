#define TARGET_DISTANCE_FORWARD 505
#define TARGET_DISTANCE_TURN 214
#define MOTOR_SPEED 25

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

void MoveForward();
void TurnLeft();
void TurnRight();

int RobotDirection = 0;

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
		RobotDirection = (RobotDirection + 3) % 4; // Update direction
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
		RobotDirection = (RobotDirection + 1) % 4; // Update direction
}

// Turn the robot 180
void TurnAround() {
    nMotorEncoder[motorLeft] = 0;//reset the value of encoder B to zero
		nMotorEncoder[motorRight] = 0;//reset the value of encoder C to zero

		while(nMotorEncoder[motorLeft] < TARGET_DISTANCE_TURN * 2)//while encoderB is less than 720
		{
			motor[motorLeft] = MOTOR_SPEED;//turn on motorB at 50% power
			motor[motorRight] = -MOTOR_SPEED;//turn on motorC at 50% power
		}

		motor[motorLeft] = 0; //Turn off motorB
		motor[motorRight] = 0; //Turn off motorC
		RobotDirection = (RobotDirection + 2) % 4; // Update direction
}

//=====================================================================
void DrawBot(){
	int RobotXpixelPos=0;
	int RobotYpixelPos=0;

	if (CurrentPosCol==0){
		RobotXpixelPos=ScreenWidth/12;
	}
	else{
		RobotXpixelPos=(2*CurrentPosCol+1)*ScreenWidth/12;
	}

	if (CurrentPosRow==0){
		RobotYpixelPos=ScreenHeight/8;
	}
	else{
		RobotYpixelPos=(2*CurrentPosRow+1)*ScreenHeight/8;
	}

	switch (RobotDirection){
		case NORTH: displayStringAt(RobotXpixelPos,RobotYpixelPos,"^");
			break; // Facing North
		case EAST: displayStringAt(RobotXpixelPos,RobotYpixelPos,">");
			break; // Facing East
		case SOUTH: displayStringAt(RobotXpixelPos,RobotYpixelPos,"V");
			break; // Facing South
		case WEST: displayStringAt(RobotXpixelPos,RobotYpixelPos,"<");
			break; // Facing West
		default: break;
	}
}
