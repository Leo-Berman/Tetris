#include <string>
#include <cstdlib>
#include <tuple>
#include <vector>
#include <chrono>
#include <thread>


// for terminal
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#ifndef ROW_SIZE
#define ROW_SIZE

#define GLOBAL_ROW_SIZE 10
#define GLOBAL_ROW_NUMBERS 22
#endif

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
  std::tuple<int,int> coordinates[4];
  int shape;
  int position;
  
  bool down(int Graphical_Matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]);
  bool is_game_over(int Graphical_Matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]);
  void left(int Graphical_Matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]);
  void right(int Graphical_Matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]);
  void counter_clockwise(int Graphical_Matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]);
  void clockwise(int Graphical_Matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]);

};

#endif

#ifndef GAME_H
#define GAME_H

#define LEFT  0
#define DOWN  1
#define RIGHT 2

class Game {
public:
  Game();
  ~Game();
  int score;
  int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE];
  int level;
  int next_piece;
  int lines_cleared;
  Piece* active_piece;
  int frames_since_last_update;
  int drop_frame_rate;
  int current_action;
  void update_game();
  void shift_graphical_matrix(int row_do_dissapear);
  bool check_row(int row_to_check);
  bool is_game_over();
  int random_number();
};
#endif

#ifndef TERMINAL_H
#define TERMINAL_H

// set a macro that is a mask that uses the control key
//
#define CTRL_KEY(k) ((k) & 0x1f)

class Terminal {
public:
  struct termios original_terminal;
  struct termios terminal_info;
  struct winsize terminal_size;
  Terminal();
  ~Terminal();

  bool process_keystroke(Game game);
  void update_terminal(Game game);
  std::string update_row(int row[GLOBAL_ROW_SIZE]);

  void reset_terminal();
};

#endif
