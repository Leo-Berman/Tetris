#include "class_definitions.h"

Game::Game(){
  Game_Window = Initialize_Window();
  Level = 8;
  Active_Piece = new Piece(Random_Number());
}

Game::~Game(){
  endwin();
}

void Game::Update_Terminal() {

  std::string Character_Rows[25];  

  for (int i = 0; i < 25; i++) {
    Character_Rows[i] = "";
    for (int j = 0; j < 10; j++) {
      if ((Graphical_Matrix[i+4][j] == 1)|(Graphical_Matrix[i+4][j] == 2)) Character_Rows[i]+="[]";
      else Character_Rows[i]+="  ";
    }
  }

  for (int i = 0; i<25; i++) mvwprintw(Game_Window,i+1,1,Character_Rows[i].c_str());

  wrefresh(Game_Window);
}

WINDOW* Game::Initialize_Window() {

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

int Game::Random_Number() {

  using namespace std;
  
  // Providing a seed value
  srand((unsigned) time(NULL));

  // Get a random number
  int random = rand();

  return random % 6;
}

void Game::Advance_Frame() {
  if(Active_Piece->Down(Graphical_Matrix)==false) {
    delete Active_Piece;
    Active_Piece = new Piece(Random_Number());
  }
  Update_Terminal();
}

void Game::Process_Command(bool Up, bool Down, bool Left, bool Right, bool Counter_Clockwise, bool Clockwise) {
  if (Up == 1) {
    ;
  }
  else if (Down & Left & Right & Counter_Clockwise & Clockwise) {
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Down & Left & Right & Counter_Clockwise) {
    Active_Piece->Counter_Clockwise(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Down & Left & Right & Clockwise) {
    Active_Piece->Clockwise(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Left & Right & Clockwise) {
    Active_Piece->Clockwise(Graphical_Matrix);
  }
  else if (Left & Right & Counter_Clockwise) {
    Active_Piece->Counter_Clockwise(Graphical_Matrix);
  }
  else if (Down & Left & Clockwise) {
    Active_Piece->Clockwise(Graphical_Matrix);
    Active_Piece->Left(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
    else if (Down & Right & Clockwise) {
    Active_Piece->Clockwise(Graphical_Matrix);
    Active_Piece->Right(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
    else if (Down & Left & Counter_Clockwise) {
    Active_Piece->Counter_Clockwise(Graphical_Matrix);
    Active_Piece->Left(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
    else if (Down & Right & Counter_Clockwise) {
    Active_Piece->Counter_Clockwise(Graphical_Matrix);
    Active_Piece->Right(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Down & Left & Right) {
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  
  else if (Down & Clockwise){
    Active_Piece->Clockwise(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }

  else if (Down & Counter_Clockwise){
    Active_Piece->Counter_Clockwise(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Down & Left){
    Active_Piece->Left(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Down & Right){
    Active_Piece->Right(Graphical_Matrix);
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Left & Right);
  else if (Down) {
    if(Active_Piece->Down(Graphical_Matrix)==false) {
      delete Active_Piece;
      Active_Piece = new Piece(Random_Number());
    }
  }
  else if (Right) {
    Active_Piece->Right(Graphical_Matrix);
  }
      
  else if(Left) {
    Active_Piece->Left(Graphical_Matrix);
  }  
  Update_Terminal();
}
