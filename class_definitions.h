#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <tuple>



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
  int Graphical_Matrix[29][14] = {};
  int Level;
  Piece* Active_Piece;
  Game();
  ~Game();
  void Update_Terminal();  
  WINDOW* Initialize_Window();
  int Random_Number();
  void Process_Command(bool Up, bool Down, bool Left, bool Right, bool Counter_Clockwise, bool Clockwise);
  void Advance_Frame();
};
  
#endif
