#include "stack.c"
#include "utilities.c"

#define MAX_ROWS 4
#define MAX_COLS 6
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

void BasicSolver();
void DFSSolver();

task main()
{
	GridInit();
	WallGen();

	while( (CurrentPosRow!=TargetPosRow) || (CurrentPosCol!=TargetPosCol)){
		DFSSolver();
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

	// Update nextRow and nextCol based on the direction
	switch (dir) {
		case NORTH:
			nextRow++;
			if (nextRow < 4 && Grid[CurrentPosRow][CurrentPosCol].NorthWall == 0) {
				CurrentPosRow = nextRow;
			}
			break;
		case EAST:
			nextCol++;
			if (nextCol < 6 && Grid[CurrentPosRow][CurrentPosCol].EastWall == 0) {
				CurrentPosCol = nextCol;
			}
			break;
		case SOUTH:
			nextRow--;
			if (nextRow >= 0 && Grid[CurrentPosRow][CurrentPosCol].SouthWall == 0) {
				CurrentPosRow = nextRow;
			}
			break;
		case WEST:
			nextCol--;
			if (nextCol >= 0 && Grid[CurrentPosRow][CurrentPosCol].WestWall == 0) {
				CurrentPosCol = nextCol;
			}
			break;
		default:
			break;
	}
}

void DFSSolver(){
    int visited[MAX_ROWS][MAX_COLS];
    memset(visited, 0, sizeof(visited));  // Initialize visited array

    Stack stack;
    initStack(&stack);

    push(&stack, CurrentPosRow, CurrentPosCol);
    visited[CurrentPosRow][CurrentPosCol] = 1;

    while (!isEmpty(&stack)) {
        int row, col;
        top(&stack, &row, &col);

        // Check if we have reached the target
        if (row == TargetPosRow && col == TargetPosCol) {
            CurrentPosRow = row;
            CurrentPosCol = col;
            return;
        }

        // Find the next unvisited neighbor in DFS order
        int found = 0;
        for (int dir = 0; dir < 4; dir++) {
            int nextRow = row + (dir == NORTH) - (dir == SOUTH);
            int nextCol = col + (dir == EAST) - (dir == WEST);

            // Check bounds and walls
            if (nextRow >= 0 && nextRow < MAX_ROWS &&
                nextCol >= 0 && nextCol < MAX_COLS &&
                !visited[nextRow][nextCol] &&
                (dir == NORTH && !Grid[row][col].NorthWall ||
                 dir == EAST && !Grid[row][col].EastWall ||
                 dir == SOUTH && !Grid[row][col].SouthWall ||
                 dir == WEST && !Grid[row][col].WestWall)) {

                // Push to stack and mark as visited
                push(&stack, nextRow, nextCol);
                visited[nextRow][nextCol] = 1;
                found = 1;

                // Move the robot to the next cell
                CurrentPosRow = nextRow;
                CurrentPosCol = nextCol;

                break;
            }
        }

        // If no valid moves found, backtrack by popping from stack
        if (!found) {
            pop(&stack);
            if (!isEmpty(&stack)) {
            	top(&stack, &CurrentPosRow, &CurrentPosCol);
          	}
        }

        GridDraw();
				DisplayStartandEnd();
				DrawBot();
				sleep(250);
				eraseDisplay();
    }
}
