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
  Piece(int Type);
  std::tuple<int,int> Coordinates[4];
  int Shape;
  int Position;
  
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

class Game {
 public:
  int score;
  int graphical_matrix[29][14] = {};
  int level;
  int next_piece;
  int lines_cleared;
  Piece* active_piece;
  void Shift_Graphical_Matrix(int Row_To_Dissapear);
  bool Check_Row(int Row_To_Check);
  bool Is_Game_Over();
  int Random_Number();
};
#endif

#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal {

  Terminal();
  ~Terminal();
  void update_terminal(std::string
  
}

#endif
