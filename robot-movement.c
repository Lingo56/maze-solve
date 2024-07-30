#define TARGET_DISTANCE_FORWARD 500
#define TARGET_DISTANCE_TURN 215
#define MOTOR_SPEED 25

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
