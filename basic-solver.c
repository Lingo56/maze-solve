// Randomly moves the robot around
int RandomDirection() {
    return random(2);  // Assuming random() generates a random number between 0 and 1
}

void BasicSolver() {
    // Check walls in all three possible directions
    bool wallForward = IsWallInDirection(FORWARD);
    bool wallLeft = IsWallInDirection(LEFT);
    bool wallRight = IsWallInDirection(RIGHT);

    // Check if walls are detected in all three directions
    if (wallForward && wallLeft && wallRight) {
        TurnAround();  // Function to turn around
        return;  // Exit the function after turning around
    }

    int dir = RandomDirection();
    bool wallDetected = IsWallInDirection(dir);

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
