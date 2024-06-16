// Library imports
#include <ncurses.h>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "SDL/SDL.h"

#define I_Piece 0
#define Z_Piece 1
#define S_Piece 2
#define J_Piece 3
#define L_Piece 4
#define O_Piece 5

WINDOW* Initialize_Window() {

  // initializes the ncurses
  initscr();

  // set no delay and no echo
  nodelay(stdscr, TRUE);
  noecho();

  // sets it so special characters return a single int
  keypad(stdscr, TRUE);

  // removes buffering of characters
  cbreak();

  // creating a window - height = 30 chars, width = 24 chars, starting at 0,0
  WINDOW* Return_Window = newwin(27, 22, 0, 0);
  refresh();

  // making box border with default border styles and setting the position of the cursor
  box(Return_Window, 0, 0);
  wmove(Return_Window, 1, 11);
  wrefresh(Return_Window);

  // return the window
  return Return_Window;  

}

int Random_Number() {

  using namespace std;
  
  // Providing a seed value
  srand((unsigned) time(NULL));

  // Get a random number
  int random = rand();

  return random%5;
}

void Update_Screen(WINDOW* Input_Window,int Graphical_Matrix[29][10]) {

  std::string Character_Rows[25];  

  for (int i = 0; i < 25; i++) {
    Character_Rows[i] = "";
    for (int j = 0; j < 10; j++) {
      if ((Graphical_Matrix[i+4][j] == 1)|(Graphical_Matrix[i+4][j] == 2)) Character_Rows[i]+="[]";
      else Character_Rows[i]+="  ";
    }
  }

  for (int i = 0; i<25; i++) mvwprintw(Input_Window,i+1,1,Character_Rows[i].c_str());
  
}

class Piece {
public:
  
  std::tuple<int,int> Piece_Coordinates[4];
  
  Piece(int Piece_Type) {
    switch(Piece_Type) {
    case(I_Piece):
      Piece_Coordinates[0] = std::make_tuple(2,3);
      Piece_Coordinates[1] = std::make_tuple(2,4);
      Piece_Coordinates[2] = std::make_tuple(2,5);
      Piece_Coordinates[3] = std::make_tuple(2,6);
      break;
    case(Z_Piece):
      Piece_Coordinates[0] = std::make_tuple(2,3);
      Piece_Coordinates[1] = std::make_tuple(2,4);
      Piece_Coordinates[2] = std::make_tuple(3,4);
      Piece_Coordinates[3] = std::make_tuple(3,5);
      break;
    case(S_Piece):
      Piece_Coordinates[0] = std::make_tuple(3,5);
      Piece_Coordinates[1] = std::make_tuple(3,4);
      Piece_Coordinates[2] = std::make_tuple(2,4);
      Piece_Coordinates[3] = std::make_tuple(2,3);
      break;
    case(J_Piece):
      Piece_Coordinates[0] = std::make_tuple(2,4);
      Piece_Coordinates[1] = std::make_tuple(2,5);
      Piece_Coordinates[2] = std::make_tuple(2,6);
      Piece_Coordinates[3] = std::make_tuple(3,6);
      break;
    case(L_Piece):
      Piece_Coordinates[0] = std::make_tuple(3,4);
      Piece_Coordinates[1] = std::make_tuple(2,4);
      Piece_Coordinates[2] = std::make_tuple(2,5);
      Piece_Coordinates[3] = std::make_tuple(2,6);
      break;
    case(O_Piece):
      Piece_Coordinates[0] = std::make_tuple(2,4);
      Piece_Coordinates[1] = std::make_tuple(1,4);
      Piece_Coordinates[2] = std::make_tuple(2,5);
      Piece_Coordinates[3] = std::make_tuple(1,5);
      break;
    }
  }
  
  bool Move_Piece_Down(int Graphical_Matrix[29][10]) {

    bool Ok_To_Move = true;
    
    for (auto [i,j] : Piece_Coordinates) {
      if ((Graphical_Matrix[i+1][j]==1) | (i == 28)) Ok_To_Move = false;
    }

    if (Ok_To_Move == true) {
      for (int i = 0; i < 4; i++) {
	int Y_Coordinate = std::get<0>(Piece_Coordinates[i]);
	int X_Coordinate = std::get<1>(Piece_Coordinates[i]);
	Graphical_Matrix[Y_Coordinate][X_Coordinate] = 0;
	std::get<0>(Piece_Coordinates[i])++;
      }
      for (auto [i,j] : Piece_Coordinates) Graphical_Matrix[i][j] = 2;
      return true;
    }
    else {
      for (auto [i,j] : Piece_Coordinates) Graphical_Matrix[i][j] = 1;
      return false;
    }
  }

  void Move_Piece_Left(int Graphical_Matrix[29][10]) {
    
    bool Ok_To_Move = true;
    
    for (auto [i,j]: Piece_Coordinates){
      if ((Graphical_Matrix[i][j-1]==1 ) | (j == 0)) Ok_To_Move = false;
    }

    if (Ok_To_Move == true) {
      for (int i = 0; i < 4; i++) {
	int Y_Coordinate = std::get<0>(Piece_Coordinates[i]);
	int X_Coordinate = std::get<1>(Piece_Coordinates[i]);
	Graphical_Matrix[Y_Coordinate][X_Coordinate] = 0;
	std::get<1>(Piece_Coordinates[i])--;
      }
      for (auto [i,j] : Piece_Coordinates) Graphical_Matrix[i][j] = 2;
    }
  }

  
  void Move_Piece_Right(int Graphical_Matrix[29][10]) {
    
    bool Ok_To_Move = true;
    
    for (auto [i,j]: Piece_Coordinates){
      if ((Graphical_Matrix[i][j+1]==1 ) | (j == 9)) Ok_To_Move = false;
    }
    
     if (Ok_To_Move == true) {
      for (int i = 0; i < 4; i++) {
	int Y_Coordinate = std::get<0>(Piece_Coordinates[i]);
	int X_Coordinate = std::get<1>(Piece_Coordinates[i]);
	Graphical_Matrix[Y_Coordinate][X_Coordinate] = 0;
	std::get<1>(Piece_Coordinates[i])++;
      }
      for (auto [i,j] : Piece_Coordinates) Graphical_Matrix[i][j] = 2;
    }
  }

  void Rotate_Piece(int Graphical_Matrix[29][10]) {

    bool Ok_To_Rotate = true;

    
  }
};



  
int main(){

  WINDOW* Game_Window = Initialize_Window();
  
  int Graphical_Matrix[29][10] = {
    {0,0,0,0,2,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0},
    {0,0,0,0,2,2,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
  };
  
  int Frame_Counter = 1;
  int Game_Level = 8;
  Piece Active_Piece = Piece(Random_Number());
  SDL_Event Keyboard_Event;
  bool Down_State = 0;
  bool Left_State = 0;
  bool Right_State = 0;
  bool Up_State = 0;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0) exit( -1 );
  if( !SDL_SetVideoMode( 250, 250, 0, 0 ) ){
    SDL_Quit();
    exit( -1 );
  }
  
  while(true){ 
    SDL_PollEvent( &Keyboard_Event );

    switch(Keyboard_Event.key.keysym.sym){
    case SDLK_DOWN:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Down_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Down_State = false;
      }
      break;
    case SDLK_UP:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Up_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Up_State = false;
      }
      break;
    case SDLK_LEFT:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Left_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Left_State = false;
      }
      break;
    case SDLK_RIGHT:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Right_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Right_State = false;
      }
      break;
    }
      if (Frame_Counter % 6 == 0) {
	
	if (Up_State == 1) {
	  ;
	}
	else if (Down_State & Left_State & Right_State) {
	if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	  Active_Piece = Piece(Random_Number());
	}
      }
      else if (Down_State & Left_State){
	Active_Piece.Move_Piece_Left(Graphical_Matrix);
	if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	  Active_Piece = Piece(Random_Number());
	}
      }
      else if (Down_State & Right_State){
	Active_Piece.Move_Piece_Right(Graphical_Matrix);
	if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	  Active_Piece = Piece(Random_Number());
	}
      }
      else if (Down_State) {
	if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	  Active_Piece = Piece(Random_Number());
	}
      }
      else if (Right_State) {
	Active_Piece.Move_Piece_Right(Graphical_Matrix);
      }
      
      else if(Left_State) {
	Active_Piece.Move_Piece_Left(Graphical_Matrix);
      }

    }
    
    if (Frame_Counter == 60-Game_Level*6) {
      Frame_Counter = 1;
      if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	Active_Piece = Piece(Random_Number());
      }
    }
    Update_Screen(Game_Window,Graphical_Matrix);
    wrefresh(Game_Window);
    Frame_Counter++;
    std::this_thread::sleep_for(std::chrono::milliseconds(17));
  }
  

  endwin();
  delete Game_Window;
  return 0;

}
