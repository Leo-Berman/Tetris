#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <tuple>

void Update_Screen(WINDOW* Input_Window,int Graphical_Matrix[25][10]) {

  std::string character_rows[25];
  
  for (int i = 0; i < 25; i++) {
    character_rows[i] = "";
    for (int j = 0; j < 10; j++) {
      if ((Graphical_Matrix[i][j] == 1)|(Graphical_Matrix[i][j] ==2)) character_rows[i]+="[]";
      else character_rows[i]+="  ";
    }
  }
  for (int i = 0; i<25; i++) mvwprintw(Input_Window,i+1,1,character_rows[i].c_str());
}

void Update_Graphical_Matrix(int Graphical_Matrix[25][10]){

  bool Ok_To_Move_Down = true;
  std::vector<std::tuple<int, int>>  Active_Piece_Coordinates;
  for (int j = 0; j < 10; j++) {
    for (int i = 0; i < 25; i++) {
      if (Graphical_Matrix[i][j] == 2) {
	Active_Piece_Coordinates.push_back(std::make_tuple(i,j));
	if (Graphical_Matrix[i+1][j] == 1) Ok_To_Move_Down = false;
      }
    }
  }

  if (Ok_To_Move_Down == true) {
    for (auto [i,j] : Active_Piece_Coordinates) Graphical_Matrix[i][j] = 0;
    for (auto [i,j] : Active_Piece_Coordinates) Graphical_Matrix[i+1][j] = 2;
  }
}

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

int main(){

  WINDOW* Game_Window = Initialize_Window();
  sleep(1);
  
  int Graphical_Matrix[25][10] ={
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
    
  };
  
  while(true){
    Update_Graphical_Matrix(Graphical_Matrix);
    Update_Screen(Game_Window,Graphical_Matrix);
    wrefresh(Game_Window);
    sleep(1);
  }
  
  getch();
  endwin();
  delete Game_Window;
  return 0;

}
