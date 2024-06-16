// Library imports
#include <ncurses.h>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <thread>

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

    Piece(char Piece_Type) {
      switch(Piece_Type){
        case('I'):
 	  Piece_Coordinates[0] = std::make_tuple(4,0);
	  Piece_Coordinates[1] = std::make_tuple(4,1);
	  Piece_Coordinates[2] = std::make_tuple(4,2);
	  Piece_Coordinates[3] = std::make_tuple(4,3);
	  break;
	case('Z'):
	  Piece_Coordinates[0] = std::make_tuple(4,0);
	  Piece_Coordinates[1] = std::make_tuple(4,1);
	  Piece_Coordinates[2] = std::make_tuple(4,2);
	  Piece_Coordinates[3] = std::make_tuple(4,3);
      }
    }
};


std::vector<std::tuple<int,int>> Get_Active_Piece_Position(int Graphical_Matrix[29][10]) {

  std::vector<std::tuple<int, int>>  Active_Piece_Coordinates;

  for (int j = 0; j < 10; j++) {
    for (int i = 0; i < 29; i++) {
      if (Graphical_Matrix[i][j] == 2) Active_Piece_Coordinates.push_back(std::make_tuple(i,j));
    }
  }

  return Active_Piece_Coordinates;
}

void Move_Piece_Down(int Graphical_Matrix[29][10],std::vector<std::tuple<int,int>> Active_Piece_Position){

  bool Ok_To_Move = true;

  for (auto [i,j]: Active_Piece_Position){
      if ((Graphical_Matrix[i+1][j]==1) | (i == 28)) Ok_To_Move = false;
  }

  if (Ok_To_Move == true) {
    for (auto [i,j] : Active_Piece_Position) Graphical_Matrix[i][j] = 0;
    for (auto [i,j] : Active_Piece_Position) Graphical_Matrix[i+1][j] = 2;
  }
}

void Move_Piece_Left(int Graphical_Matrix[29][10],std::vector<std::tuple<int,int>> Active_Piece_Position) {

  bool Ok_To_Move = true;

  for (auto [i,j]: Active_Piece_Position){
    if ((Graphical_Matrix[i][j-1]==1 ) | (j == 0)) Ok_To_Move = false;
  }

  if (Ok_To_Move == true) {
    for (auto [i,j] : Active_Piece_Position) Graphical_Matrix[i][j] = 0;
    for (auto [i,j] : Active_Piece_Position) Graphical_Matrix[i][j-1] = 2;
  }
}

void Move_Piece_Right(int Graphical_Matrix[29][10],std::vector<std::tuple<int,int>> Active_Piece_Position) {

  bool Ok_To_Move = true;

  for (auto [i,j]: Active_Piece_Position){
    if ((Graphical_Matrix[i][j+1]==1 ) | (j == 9)) Ok_To_Move = false;
  }

  if (Ok_To_Move == true) {
    for (auto [i,j] : Active_Piece_Position) Graphical_Matrix[i][j] = 0;
    for (auto [i,j] : Active_Piece_Position) Graphical_Matrix[i][j+1] = 2;
  }

}

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
  while(true){

    int Keystroke = getch();

    std::vector<std::tuple<int,int>> Active_Piece_Position = Get_Active_Piece_Position(Graphical_Matrix);

    switch(Keystroke) {
      case(KEY_LEFT): Move_Piece_Left(Graphical_Matrix, Active_Piece_Position); break;
      case(KEY_RIGHT): Move_Piece_Right(Graphical_Matrix, Active_Piece_Position); break;
    }
    
    if (frame_counter == 59-game_level*5) {
      frame_counter = 0;
      Move_Piece_Down(Graphical_Matrix, Active_Piece_Position);
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
