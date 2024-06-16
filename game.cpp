#include "class_definitions.h"

Game::Game(){
  Game_Window =   Initialize_Game_Window();
  Future_Window = Initialize_Future_Window();
  Score_Window = Initialize_Score_Window();
  Score = 0;
  Next_Piece = Random_Number();
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
  delete Active_Piece, Game_Window, Future_Window,Score_Window;
}

void Game::Shift_Graphical_Matrix(int Row_To_Dissapear) {
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

WINDOW* Game::Initialize_Score_Window() {
  WINDOW* Return_Window = newwin(4, 12, 6, 22);
  refresh();
  box(Return_Window, 0, 0);
  wrefresh(Return_Window);
  return Return_Window;
}

WINDOW* Game::Initialize_Future_Window() {
  WINDOW* Return_Window = newwin(6, 12, 0, 22);
  refresh();
  box(Return_Window, 0, 0);
  wrefresh(Return_Window);
  return Return_Window;
}

WINDOW* Game::Initialize_Game_Window() {
  
    // initializes the ncurses
  initscr();

  // set no delay and no echo
  // nodelay(stdscr, TRUE);
  noecho();

  // sets it so special characters return a single int
  keypad(stdscr, TRUE);

  // removes buffering of characters
  cbreak();


  // creating a window - height = 27 chars, width = 22 chars, starting at 0,0
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

bool Game::Advance_Frame() {
  if(Active_Piece->Down(Graphical_Matrix)==false) {
    delete Active_Piece;
    Active_Piece = new Piece(Next_Piece);
    Update_Terminal(true);
    Next_Piece = Random_Number();
    return Is_Game_Over();
  }
  else Update_Terminal();
  return false;
}

bool Game::Is_Game_Over() {
  return Active_Piece->Is_Game_Over(Graphical_Matrix);
}

void Game::Game_Over() {
  for (int i = 0; i < 25; i++) {
    mvwprintw(Game_Window,i+1,5,"GAME OVER");
    wrefresh(Game_Window);
  }
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



void Game::Update_Terminal(bool Piece_Inserted) {

  mvwprintw(Score_Window,1,1,"Score :");
  mvwprintw(Score_Window,2,1,std::to_string(Score).c_str());
  wrefresh(Score_Window);
  if (Next_Piece == I) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"         ");
    mvwprintw(Future_Window,3,1," [][][][]");
    mvwprintw(Future_Window,4,1,"         ");
   
  }
  else if (Next_Piece == S) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"    [][] ");
    mvwprintw(Future_Window,3,1,"  [][]   ");
    mvwprintw(Future_Window,4,1,"         ");
  }
  else if (Next_Piece == Z) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"  [][]   ");
    mvwprintw(Future_Window,3,1,"    [][] ");
    mvwprintw(Future_Window,4,1,"         ");
  }
  else if (Next_Piece == T) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"  [][][] ");
    mvwprintw(Future_Window,3,1,"    []   ");
    mvwprintw(Future_Window,4,1,"         ");
  }
  else if (Next_Piece == L) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"  [][][] ");
    mvwprintw(Future_Window,3,1,"  []     ");
    mvwprintw(Future_Window,4,1,"         ");
  }
  else if (Next_Piece == J) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"  [][][] ");
    mvwprintw(Future_Window,3,1,"      [] ");
    mvwprintw(Future_Window,4,1,"         ");
  }
  else if (Next_Piece == O) {
    mvwprintw(Future_Window,1,1,"         ");
    mvwprintw(Future_Window,2,1,"   [][]  ");
    mvwprintw(Future_Window,3,1,"   [][]  ");
    mvwprintw(Future_Window,4,1,"         ");
  }


  wrefresh(Future_Window);
  
  std::vector<int> Filled_Rows;
  std::string Character_Rows[25];  
  for (int i = 0; i < 25; i++) {
    Character_Rows[i] = "";
    for (int j = 0; j < 10; j++) {
      if ((Graphical_Matrix[i+4][j+2] == 1)|(Graphical_Matrix[i+4][j+2] == 2)) Character_Rows[i]+="[]";
      else Character_Rows[i]+="  ";
    }   
  }


    
    
  for(int i = 0; i < 25; i++) if (Check_Row(i+4)) Filled_Rows.push_back(i);	  

  int Number_Of_Filled_Rows = Filled_Rows.size();

  if (Piece_Inserted) {
    Score+=Level*25;
    if (Number_Of_Filled_Rows >= 1) {
      Score+=Level*50*Number_Of_Filled_Rows ;
    }
    if (Number_Of_Filled_Rows >= 2) {
      Score+=Level*150*Number_Of_Filled_Rows;
    }
    if (Number_Of_Filled_Rows >= 3) {
      Score+=Level*300*Number_Of_Filled_Rows;
    }
    if (Number_Of_Filled_Rows == 4) {
      Score+=Level*500*Number_Of_Filled_Rows;
    }
    
  
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

