#include "class_definitions.h"

Game::Game(){
  Game_Window = Initialize_Window();
  Level = 8;
  for (int i = 0; i < 29; i++) {
    Graphical_Matrix[i][0] = 1;
    Graphical_Matrix[i][1] = 1;
    Graphical_Matrix[i][12] = 1;
    Graphical_Matrix[i][13] = 1;
  }
  Active_Piece = new Piece(Random_Number());
}

Game::~Game(){
  endwin();
}

bool Game::Shift_Graphical_Matrix(int Row_To_Dissapear) {
  for (int i = Row_To_Dissapear; i > 0; i--) {
    //Graphical_Matrix[i] = Graphical_Matrix[i-1];
    memmove((void*)Graphical_Matrix[i],(void*)Graphical_Matrix[i-1],14*sizeof(int));
  }
}

bool Game::Check_Row(int Row_To_Check) {

  for (int i = 0; i < 10; i++) {
    if (Graphical_Matrix[Row_To_Check][i+2] == 0) return false;
  }
  return true;
}


void Game::Update_Terminal(bool Piece_Inserted) {
  std::vector<int> Filled_Rows;
  std::string Character_Rows[25];  
  for (int i = 0; i < 25; i++) {
    Character_Rows[i] = "";
    for (int j = 0; j < 10; j++) {
      if ((Graphical_Matrix[i+4][j+2] == 1)|(Graphical_Matrix[i+4][j+2] == 2)) Character_Rows[i]+="[]";
      else Character_Rows[i]+="  ";
    }   
  }
  
 
  
  

  if (Piece_Inserted) {
    for(int i = 0; i < 25; i++) if (Check_Row(i+4)) Filled_Rows.push_back(i);	  
  
    if (Filled_Rows.size() > 0) {
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[][][][][][][][][][]");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[][][][]    [][][][]");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[][][]        [][][]");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[][]            [][]");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[]                []");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"                    ");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[][][][][][][][][][]");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"                    ");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) mvwprintw(Game_Window,i+1,1,"[][][][][][][][][][]");
      wrefresh(Game_Window);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      for (auto i : Filled_Rows) Shift_Graphical_Matrix(i+4);


      
    }
  }
  
  
  for (int i = 0; i<25; i++) {
    mvwprintw(Game_Window,i+1,1,Character_Rows[i].c_str());
  }
  
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

  return random % 7;
}

void Game::Advance_Frame() {
  if(Active_Piece->Down(Graphical_Matrix)==false) {
    delete Active_Piece;
    Active_Piece = new Piece(Random_Number());
    Update_Terminal(true);
    //Active_Piece = new Piece(J);
  }
  else Update_Terminal();
}

void Game::Process_Command(bool Up, bool Down, bool Left, bool Right, bool Counter_Clockwise, bool Clockwise) {
  if (Up) {
    Update_Terminal();
    return;
  }
    if (Clockwise)         Active_Piece->Clockwise        (Graphical_Matrix);
    if (Counter_Clockwise) Active_Piece->Counter_Clockwise(Graphical_Matrix);
    if (Right)             Active_Piece->Right            (Graphical_Matrix); 
    if (Left)              Active_Piece->Left             (Graphical_Matrix); 
    if (Down)              Active_Piece->Down             (Graphical_Matrix); 
  Update_Terminal();
}
