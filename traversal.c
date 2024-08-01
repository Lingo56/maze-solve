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

typedef struct {
    int row;
    int col;
} Parent;

void DFSSolver();
int GetBacktrackDirection(int currRow, int currCol, int parentRow, int parentCol);
int CalculateTurnDirection(int currentDirection, int targetDirection);
void AlignAndMove(int targetDirection);
void DrawProgress();

bool algorithmFinished = false;
bool mazeSolved = false;

bool turned = false;

task main()
{
	GridInit();
  WallGen();

	while(!algorithmFinished){
    if (!isPaused) {
        DrawProgress();
        DFSSolver();
    }
    checkTogglePause(); // Check if middle button is pressed
	}

	while(mazeSolved){
		displayCenteredTextLine(5,"MAZE SOLVED !!");
		sleep(500);
		eraseDisplay();
		sleep(500);
	}

		while(true){
		DrawProgress();
		displayCenteredTextLine(2,"No More Moves");
		sleep(500);
	}
}

//=====================================================================

void DFSSolver(){
    int visited[MAX_ROWS][MAX_COLS];
    Parent parent[MAX_ROWS][MAX_COLS];  // Store parent coordinates
    memset(visited, 0, sizeof(visited));  // Initialize visited array

    Stack stack;
    initStack(&stack);

    push(&stack, CurrentPosRow, CurrentPosCol);
    visited[CurrentPosRow][CurrentPosCol] = 1;
    Grid[CurrentPosRow][CurrentPosCol].visited = true;  // Mark the cell as visited
    parent[CurrentPosRow][CurrentPosCol].row = -1;  // Start position has no parent
    parent[CurrentPosRow][CurrentPosCol].col = -1;

    while (!isEmpty(&stack)) {
    	  DrawProgress();
        int row, col;
        top(&stack, &row, &col);

        // Check if we have reached the target
        if (row == TargetPosRow && col == TargetPosCol) {
            // Path found, start backtracking
            break;
        }

        // Find the next unvisited neighbor in DFS order
        int found = 0;
        int foundDir = -1;

        for (int dir = 0; dir < 3; dir++) {
        		DrawProgress();
        		sleep(1000);
        	  bool wallDetected = CheckWall(dir);

            int nextRow = row + (RobotDirection == NORTH) - (RobotDirection == SOUTH);
            int nextCol = col + (RobotDirection == EAST) - (RobotDirection == WEST);

            switch (dir){
            	case FORWARD:
		            // Check bounds and walls
		            if (nextRow >= 0 && nextRow < MAX_ROWS && nextCol >= 0 && nextCol < MAX_COLS && !visited[nextRow][nextCol] && !wallDetected) {
				                found = 1;
				                foundDir = FORWARD;

		                		break;
		            } else if (wallDetected) {
		            		switch (RobotDirection) {
		                    case 0: Grid[CurrentPosRow][CurrentPosCol].NorthWall = 1; break;
		                    case 1: Grid[CurrentPosRow][CurrentPosCol].EastWall = 1; break;
		                    case 2: Grid[CurrentPosRow][CurrentPosCol].SouthWall = 1; break;
		                    case 3: Grid[CurrentPosRow][CurrentPosCol].WestWall = 1; break;
		                }
		                break;
		            }
		        	case LEFT:
		        		// Check bounds and walls
		            if (nextRow >= 0 && nextRow < MAX_ROWS && nextCol >= 0 && nextCol < MAX_COLS && !visited[nextRow][nextCol] && !wallDetected) {
				                found = 1;
				                foundDir = LEFT;

		               			break;
		            } else if (wallDetected) {
		            		switch (RobotDirection) {
		                    case 0:
			                    Grid[CurrentPosRow][CurrentPosCol].WestWall = 1;
			                    displayCenteredTextLine(2,"L Direction W: %d",  RobotDirection);
			                    break;
		                    case 1:
		                    	Grid[CurrentPosRow][CurrentPosCol].NorthWall = 1;
		                      displayCenteredTextLine(3,"L Direction N: %d",  RobotDirection);
		                    	break;
		                    case 2:
		                    	Grid[CurrentPosRow][CurrentPosCol].EastWall = 1;
		                    	displayCenteredTextLine(4,"L Direction E: %d",  RobotDirection);
		                    	break;
		                    case 3:
		                    	Grid[CurrentPosRow][CurrentPosCol].SouthWall = 1;
		                    	displayCenteredTextLine(5,"L Direction S: %d",  RobotDirection);
		                    	break;
		                }
		                break;
		            }
		        	case RIGHT:
		        		// Check bounds and walls
		            if (nextRow >= 0 && nextRow < MAX_ROWS && nextCol >= 0 && nextCol < MAX_COLS && !visited[nextRow][nextCol] && !wallDetected) {
				                found = 1;
				                foundDir = RIGHT;

		                		break;
		            } else if (wallDetected) {
		            		switch (RobotDirection) {
		                    case 0:
		                    	Grid[CurrentPosRow][CurrentPosCol].EastWall = 1;
		                    	displayCenteredTextLine(4,"R Direction E: %d",  RobotDirection);
		                    	break;
		                    case 1:
		                      Grid[CurrentPosRow][CurrentPosCol].SouthWall = 1;
		                    	displayCenteredTextLine(5,"R Direction S: %d",  RobotDirection);
		                    	break;
		                    case 2:
		                    	Grid[CurrentPosRow][CurrentPosCol].WestWall = 1;
			                    displayCenteredTextLine(2,"R Direction W: %d",  RobotDirection);
			                    break;
		                    case 3:
		                      Grid[CurrentPosRow][CurrentPosCol].NorthWall = 1;
		                      displayCenteredTextLine(3,"R Direction N: %d",  RobotDirection);
		                    	break;
		                }
		                break;
		            }
		        	default:
		        		break;
            }
        }

        if (found) {
        	  DrawProgress();
        		sleep(1000);

        		int nextRow = row + (RobotDirection == NORTH) - (RobotDirection == SOUTH);
            int nextCol = col + (RobotDirection == EAST) - (RobotDirection == WEST);

            push(&stack, nextRow, nextCol);
	          parent[nextRow][nextCol].row = row;
	          parent[nextRow][nextCol].col = col;
            visited[nextRow][nextCol] = 1;
	          Grid[nextRow][nextRow].visited = true;  // Mark the cell as visited

            switch (foundDir){
            	case FORWARD:
	              // Move the robot to the next cell
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
								turned = false;
	          		break;
		        	case LEFT:
                // Move the robot to the next cell
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
								turned = false;
           			break;
		        	case RIGHT:
	              // Move the robot to the next cell
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
								turned = false;
	          		break;
		        	default:
		        		break;
            }
        }

        // TODO: There's an issue with where this places the robot in the virtual
        // If no valid moves found, backtrack by popping from stack
        if (!found) {
        	  TurnAround();
        	  turned = true;

            pop(&stack);
            if (!isEmpty(&stack)) {
                int parentRow, parentCol;
                top(&stack, &parentRow, &parentCol);

                int backtrackDirection = GetBacktrackDirection(CurrentPosRow, CurrentPosCol, parentRow, parentCol);
						    AlignAndMove(backtrackDirection);
						    CurrentPosRow = parentRow;
						    CurrentPosCol = parentCol;
            }
        }

        DrawProgress();
    }

    playTone(1000, 25);
    algorithmFinished = true;

        // Check if target is reached
    if ((CurrentPosCol == TargetPosCol) && (CurrentPosRow == TargetPosRow)) {
        mazeSolved = true;
    }
}

int GetBacktrackDirection(int currRow, int currCol, int parentRow, int parentCol) {
    if (parentRow == currRow + 1) return SOUTH;  // Moving back from North
    if (parentRow == currRow - 1) return NORTH;  // Moving back from South
    if (parentCol == currCol + 1) return WEST;   // Moving back from East
    if (parentCol == currCol - 1) return EAST;   // Moving back from West
    return -1;  // Invalid direction
}

// Function to calculate the turn needed to align with the target direction
int CalculateTurnDirection(int currentDirection, int targetDirection) {
    int turnDirection = (targetDirection - currentDirection + 4) % 4;  // Normalize the result to [0, 3]

    // Determine how to turn (left or right)
    if (turnDirection == 1 || turnDirection == 3) {
        return (turnDirection == 1) ? RIGHT : LEFT; // Right turn if 1 step, left turn if 3 steps
    }
    return -1;  // No turn needed (0 steps)
}

// Move robot to face the target direction and update its position
void AlignAndMove(int targetDirection) {
    int turnDirection = CalculateTurnDirection(RobotDirection, targetDirection);

    DrawProgress();

    MoveForward();

		DrawProgress();

    if (turnDirection == RIGHT) {
        TurnRight();
    } else if (turnDirection == LEFT) {
        TurnLeft();
    }

    DrawProgress();
}

void DrawProgress() {
	  eraseDisplay();
    GridDraw();
    DisplayStartandEnd();
    DrawBot();
}
