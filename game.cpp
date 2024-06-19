#include "header.h"

Game::Game() {
  score = 0;
  level = 0;
  lines_cleared = 0;
  active_piece = new Piece(random_number());

  for (int row_index = 0; row_index < GLOBAL_ROW_NUMBERS; row_index++) {
    for(int column_index = 0; column_index < GLOBAL_ROW_SIZE; column_index++) {
      graphical_matrix[row_index][column_index] = 0;
    }
  }
}

void Game::shift_graphical_matrix(int row_to_dissapear) {
  for (int i = row_to_dissapear; i > 0; i--) memmove((void*) graphical_matrix[i],(void*)graphical_matrix[i-1],14*sizeof(int));
}

bool Game::check_row(int row_to_check) {
  for (int i = 0; i < 10; i++) {
    if (graphical_matrix[row_to_check][i+2] == 0) return false;
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
