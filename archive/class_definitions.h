#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <tuple>
#include <vector>
#include <chrono>
#include <thread>
#include <string.h>

#ifndef PIECE_H
#define PIECE_H

#define I 0
#define Z 1
#define S 2
#define J 3
#define L 4
#define O 5
#define T 6
class Piece {


public:
  std::tuple<int,int> Coordinates[4];
  int Shape;
  int Position;
  Piece(int Type);
  bool Down(int Graphical_Matrix[29][14]);
  bool Is_Game_Over(int Graphical_Matrix[29][14]);
  void Left(int Graphical_Matrix[29][14]);
  void Right(int Graphical_Matrix[29][14]);
  void Counter_Clockwise(int Graphical_Matrix[29][14]);
  void Clockwise(int Graphical_Matrix[29][14]);
  
};

#endif

#ifndef GAME_H
#define GAME_H

class Game{
 public:
  WINDOW* Game_Window;
  WINDOW* Future_Window;
  WINDOW* Score_Window;
  int Score;
  int Graphical_Matrix[29][14] = {};
  int Level;
  int Next_Piece;
  int Lines_Cleared;
  Piece* Active_Piece;
  Game();
  ~Game();
  void Shift_Graphical_Matrix(int Row_To_Dissapear);
  bool Check_Row(int Row_To_Check);
  bool Is_Game_Over();
  int Get_Frame_Rate();
  void Update_Terminal(bool Piece_Inserted = false);  
  WINDOW* Initialize_Game_Window();
  WINDOW* Initialize_Future_Window();
  WINDOW* Initialize_Score_Window();
  int Random_Number();
  void Process_Command(bool Up, bool Down, bool Left, bool Right, bool Counter_Clockwise, bool Clockwise);
  bool Advance_Frame();
  void Game_Over();
};
  
#endif
