#pragma config(Motor,  motorA,          motorSensor,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorLeft,     tmotorEV3_Large, PIDControl)
#pragma config(Motor,  motorD,          motorRight,    tmotorEV3_Large, PIDControl)
#pragma config(Sensor, S2, ultrasonicSensor, sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define TARGET_DISTANCE_SENSOR 90
#define SENSOR_MOTOR_SPEED 90
#define WALL_SENSOR_DISTANCE 150

void MoveSensorClockwise(int target);
void MoveSensorDefault();
bool ScanForWall();
void CheckWallInDirection(int direction);

task main()
{
    CheckWallInDirection(1);
    sleep(1000);  // Pause between checks

    displayCenteredTextLine(5, "");
    MoveSensorDefault();
    sleep(400);
}

void MoveSensorClockwise(int target)
{
    nMotorEncoder[motorSensor] = 0;  // Reset encoder
    while (nMotorEncoder[motorSensor] <= target)
    {
        motor[motorSensor] = SENSOR_MOTOR_SPEED;
    }
    motor[motorSensor] = 0;  // Stop motor
}

void MoveSensorDefault()
{
    while (nMotorEncoder[motorSensor] >= 0)
    {
        motor[motorSensor] = -SENSOR_MOTOR_SPEED;
    }

    motor[motorSensor] = 0;  // Stop motor
}

bool ScanForWall()
{
    return SensorValue[ultrasonicSensor] < WALL_SENSOR_DISTANCE;
}

void CheckWallInDirection(int direction)
{
    int target = TARGET_DISTANCE_SENSOR * direction;

    MoveSensorClockwise(target);
    sleep(250);

    if (ScanForWall()) {
        displayCenteredTextLine(5, "Wall Found %s: %d cm", direction == 0 ? "Left" : (direction == 1 ? "Forward" : "Right"), SensorValue[ultrasonicSensor]);
        playSound(soundBeepBeep);
    } else {
        displayCenteredTextLine(5, "No Wall %s", direction == 0 ? "Left" : (direction == 1 ? "Forward" : "Right"));
    }
}
