// Library imports
#include <ncurses.h>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <thread>
#include <random>

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
    case(0):
      Piece_Coordinates[0] = std::make_tuple(0,3);
      Piece_Coordinates[1] = std::make_tuple(0,4);
      Piece_Coordinates[2] = std::make_tuple(0,5);
      Piece_Coordinates[3] = std::make_tuple(0,6);
      break;
    case(1):
      Piece_Coordinates[0] = std::make_tuple(0,3);
      Piece_Coordinates[1] = std::make_tuple(0,4);
      Piece_Coordinates[2] = std::make_tuple(1,4);
      Piece_Coordinates[3] = std::make_tuple(1,5);
      break;
    case(2):
      Piece_Coordinates[0] = std::make_tuple(1,5);
      Piece_Coordinates[1] = std::make_tuple(1,4);
      Piece_Coordinates[2] = std::make_tuple(0,4);
      Piece_Coordinates[3] = std::make_tuple(0,3);
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
  
  int frame_counter = 0;

  int game_level = 8;

  Piece Active_Piece = Piece(rand() % static_cast<int>(2 + 1));

  while(true){

    int Keystroke = getch();

    switch(Keystroke) {
      case(KEY_LEFT): Active_Piece.Move_Piece_Left(Graphical_Matrix); break;
      case(KEY_RIGHT): Active_Piece.Move_Piece_Right(Graphical_Matrix); break;
      case(KEY_DOWN):
	if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	  Active_Piece = Piece(rand() % static_cast<int>(2 + 1));
	};
	break;
      default:
	if (GetKeyState(VK_MENU) & 0x8000)
    }
    
    if (frame_counter == 59-game_level*5) {
      frame_counter = 0;
      if(Active_Piece.Move_Piece_Down(Graphical_Matrix)==false) {
	Active_Piece = Piece(rand() % static_cast<int>(2 + 1));
      }
    }
    Update_Screen(Game_Window,Graphical_Matrix);
    wrefresh(Game_Window);
    frame_counter++;
    std::this_thread::sleep_for(std::chrono::milliseconds(17));
  }
  

  endwin();
  delete Game_Window;
  return 0;

}
