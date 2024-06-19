#include "header.h"

Game::Game() {
  score = 0;
  level = 0;
  lines_cleared = 0;
  active_piece = new Piece(random_number());
  frames_since_last_update = 0;
  drop_frame_rate = 1;
  for (int row_index = 0; row_index < GLOBAL_ROW_NUMBERS; row_index++) {
    for(int column_index = 0; column_index < GLOBAL_ROW_SIZE; column_index++) {
      graphical_matrix[row_index][column_index] = 0;
    }
  }
}

void Game::shift_graphical_matrix(int row_to_dissapear) {
  for (int i = row_to_dissapear; i > 0; i--) memmove((void*) graphical_matrix[i],(void*)graphical_matrix[i-1],GLOBAL_ROW_SIZE*sizeof(int));
}

bool Game::check_row(int row_to_check) {
  for (int i = 0; i < GLOBAL_ROW_SIZE; i++) {
    if (graphical_matrix[row_to_check][i] == 0) return false;
  }
  return true;
}

bool Game::is_game_over() {
  return active_piece->is_game_over(graphical_matrix);
}

int Game::random_number() {  

  using namespace std;
  
  srand((unsigned) time(NULL));

  int random = rand();

  return random % 7;
  
}

Game::~Game() {
}

void Game::update_game() {
  frames_since_last_update++;

  if (frames_since_last_update >= drop_frame_rate) {
    if (active_piece->down(graphical_matrix) == false) {
      delete active_piece;
      active_piece = new Piece(random_number());
    }
    frames_since_last_update = 0;
    }
}
