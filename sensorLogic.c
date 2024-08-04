#define TARGET_DISTANCE_SENSOR 90
#define SENSOR_MOTOR_SPEED 40
#define WALL_SENSOR_DISTANCE 150

bool CheckWall(int direction);
void MoveSensorClockwise(int target);
void MoveSensorDefault();
bool ScanForWall();

bool CheckWall(int direction)
{
    int target = TARGET_DISTANCE_SENSOR * direction;

    MoveSensorClockwise(target);
    sleep(250);

    bool scanResult = ScanForWall();

    MoveSensorDefault();

    if (scanResult) {
        displayCenteredTextLine(5, "Wall @ Spot %d: %d cm", direction, SensorValue[ultrasonicSensor]);
        playSound(soundBeepBeep);
        return(scanResult);
    } else {
        displayCenteredTextLine(5, "No Wall @ Spot %d", direction);
        return(scanResult);
    }
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
