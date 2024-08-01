const int ScreenHeight =127;
const int ScreenWidth =177;

// Grid Size
#define MAX_ROWS 4
#define MAX_COLS 6

#define COLOR_VISITED  gray  // Using gray as a proxy for visited cells

typedef struct{
    int NorthWall;
    int EastWall;
    int SouthWall;
    int WestWall;
    bool visited;  // Add this line
} Cell;

Cell Grid[MAX_ROWS][MAX_COLS];

// Start in the 0,0 Cell
int StartPosRow=0; // Starting position
int StartPosCol=5;
int CurrentPosRow=StartPosRow; // Starting position
int CurrentPosCol=StartPosCol;
int TargetPosRow=3;
int TargetPosCol=0;
bool isPaused = true;

void GridInit();
void WallGen();
void GridDraw();
void DrawBot();
void DisplayStartandEnd();
void checkTogglePause();

//=====================================================================
void GridInit(){
    for(int i=0;i<MAX_ROWS;i++){
        for(int j=0;j<MAX_COLS;j++){
            Grid[i][j].NorthWall=0;
            Grid[i][j].EastWall=0;
            Grid[i][j].WestWall=0;
            Grid[i][j].SouthWall=0;
            Grid[i][j].visited = false;  // Initialize visited flag
        }
    }
}

//=====================================================================
void WallGen(){
	int i=0;
	int j=0;

	for(i=0;i<MAX_ROWS;i++){
		Grid[i][0].WestWall=1;
		Grid[i][MAX_COLS - 1].EastWall=1;
	}
	for(j=0;j<MAX_COLS;j++){
		Grid[0][j].SouthWall=1;
		Grid[MAX_ROWS - 1][j].NorthWall=1;
	}
}

//=====================================================================
//=====================================================================
void GridDraw(){
    int XStart=0;
    int YStart=0;
    int XEnd=0;
    int YEnd=0;

    for(int i=0;i<MAX_ROWS;i++){
        for(int j=0;j<MAX_COLS;j++){
            // Draw walls
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

            // Draw visited cells
            if (Grid[i][j].visited) {
                // Draw visited cell
                XStart = j * ScreenWidth / MAX_COLS;
                YStart = i * ScreenHeight / MAX_ROWS;
                XEnd = (j + 1) * ScreenWidth / MAX_COLS;
                YEnd = (i + 1) * ScreenHeight / MAX_ROWS;
                fillRect(XStart + 6, YStart + 6, XEnd - 6, YEnd - 6);
            }
        }
    }

    // Draw start and end points
    DisplayStartandEnd();
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

// Function to check the state of the middle button and toggle pause
void checkTogglePause() {
    // Assuming there's a function to check if the middle button is pressed
    if (getButtonPress(buttonUp)) { // Replace with actual function to check middle button
        isPaused = !isPaused; // Toggle pause state
        sleep(500);
    }
}
