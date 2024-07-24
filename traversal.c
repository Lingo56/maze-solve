#include "stack.c"

const int ScreenHeight =127;
const int ScreenWidth =177;
#define MAX_ROWS 4
#define MAX_COLS 6
#define INT_MAX 2147483647
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3
int RobotDirection=0; // 0=North, 1=East, 2=South, 3=West

typedef struct{
	int NorthWall;
	int EastWall;
	int SouthWall;
	int WestWall;
}Cell;

Cell Grid[4][6];

// Start in the 0,0 Cell
int StartPosRow=0; // Starting position
int StartPosCol=0;
int CurrentPosRow=StartPosRow; // Starting position
int CurrentPosCol=StartPosCol;
int TargetPosRow=1;
int TargetPosCol=5;

void GridInit();
void WallGen();
void GridDraw();
void DrawBot();
void DisplayStartandEnd();
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
void GridInit(){
	for(int i=0;i<4;i++){
		for(int j=0;j<6;j++){
			Grid[i][j].NorthWall=0;
			Grid[i][j].EastWall=0;
			Grid[i][j].WestWall=0;
			Grid[i][j].SouthWall=0;
		}
	}
}

//=====================================================================
void WallGen(){
	int i=0;
	int j=0;

	for(i=0;i<4;i++){
		Grid[i][0].WestWall=1;
		Grid[i][5].EastWall=1;
	}
	for(j=0;j<6;j++){
		Grid[0][j].SouthWall=1;
		Grid[3][j].NorthWall=1;
	}

	Grid[0][0].NorthWall =1; Grid[1][0].SouthWall =1;
	Grid[0][1].NorthWall =1; Grid[1][1].SouthWall =1;
	Grid[0][3].EastWall =1; Grid[0][4].WestWall =1;
	Grid[1][2].EastWall =1; Grid[1][3].WestWall =1;
	Grid[1][3].EastWall =1; Grid[1][4].WestWall =1;
	Grid[1][4].EastWall =1; Grid[1][5].WestWall =1;
	Grid[1][5].NorthWall =1; Grid[2][5].SouthWall =1;
	Grid[3][0].EastWall =1; Grid[3][1].WestWall =1;
	Grid[3][4].SouthWall =1; Grid[2][4].NorthWall =1;

	for(j=1;j<4;j++){
		Grid[2][j].NorthWall=1;
		Grid[2][j].SouthWall=1;
		Grid[3][j].SouthWall=1;
		Grid[1][j].NorthWall=1;
	}
}

//=====================================================================
void GridDraw(){
	int XStart=0;
	int YStart=0;
	int XEnd =0;
	int YEnd =0;

	for(int i=0;i<4;i++){
		for(int j=0;j<6;j++){
			if(Grid[i][j].NorthWall==1){
				XStart= j *ScreenWidth/6;
				YStart=(i+1)*ScreenHeight/4;
				XEnd =(j+1)*ScreenWidth/6;
				YEnd =(i+1)*ScreenHeight/4;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
			if (Grid[i][j].EastWall==1){
				XStart=(j+1)*ScreenWidth/6;
				YStart=(i)*ScreenHeight/4;
				XEnd =(j+1)*ScreenWidth/6;
				YEnd =(i+1)*ScreenHeight/4;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
			if (Grid[i][j].WestWall==1){
				XStart= j *ScreenWidth/6;
				YStart=(i)*ScreenHeight/4;
				XEnd =(j)*ScreenWidth/6;
				YEnd =(i+1)*ScreenHeight/4;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
			if(Grid[i][j].SouthWall==1){
				XStart= j *ScreenWidth/6;
				YStart=(i)*ScreenHeight/4;
				XEnd =(j+1)*ScreenWidth/6;
				YEnd =(i)*ScreenHeight/4;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
		}
	}
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
		case 0: displayStringAt(RobotXpixelPos,RobotYpixelPos,"^");
			break; // Facing North
		case 1: displayStringAt(RobotXpixelPos,RobotYpixelPos,">");
			break; // Facing East
		case 2: displayStringAt(RobotXpixelPos,RobotYpixelPos,"V");
			break; // Facing South
		case 3: displayStringAt(RobotXpixelPos,RobotYpixelPos,"<");
			break; // Facing West
		default: break;
	}
}

//=====================================================================

// Randomly moves the robot around
int RandomDirection() {
	return random(4);  // Assuming random() generates random number between 0 and n-1
}

// Moves the robot based on EV3 controls
int ManualControl () {
	// Check button presses
	if (getButtonPress(buttonUp)) {
		return NORTH;
	} else if (getButtonPress(buttonDown)) {
		return SOUTH;
	} else if (getButtonPress(buttonRight)) {
		return EAST;
	} else if (getButtonPress(buttonLeft)) {
		return WEST;
	}

	return -1;
}

void BasicSolver(){
	int dir = RandomDirection(); // Change this to RandomDirection() for random movement
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

//=====================================================================
void DisplayStartandEnd(){
	int XpixelPos=0;
	int YpixelPos=0;

	if(StartPosCol==0){
		XpixelPos=ScreenWidth/12;
	}
	else{
		XpixelPos=(2*StartPosCol+1)*ScreenWidth/12;
	}

	if(StartPosRow==0){
		YpixelPos=ScreenHeight/8;
	}
	else{
		YpixelPos=(2*StartPosRow+1)*ScreenHeight/8;
	}

	displayStringAt(XpixelPos,YpixelPos,"S");
	if(TargetPosCol==0){
		XpixelPos=ScreenWidth/12;
	}
	else{
		XpixelPos=(2*TargetPosCol+1)*ScreenWidth/12;
	}

	if(TargetPosRow==0){
		YpixelPos=ScreenHeight/8;
	}
	else{
		YpixelPos=(2*TargetPosRow+1)*ScreenHeight/8;
	}

	displayStringAt(XpixelPos,YpixelPos,"E");
}
