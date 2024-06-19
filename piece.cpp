#include "header.h"

Piece::Piece(int Type) {

  shape = Type;
  position = 0;
  using std::make_tuple;
  
  switch(Type) {
  case(I):
    coordinates[0] = make_tuple(0,4);
    coordinates[1] = make_tuple(0,5);
    coordinates[2] = make_tuple(0,6);
    coordinates[3] = make_tuple(0,7);
    break;
  case(Z):
    coordinates[0] = make_tuple(0,5);
    coordinates[1] = make_tuple(0,6);
    coordinates[2] = make_tuple(1,6);
    coordinates[3] = make_tuple(1,7);
    break;
  case(S):
    coordinates[0] = make_tuple(1,5);
    coordinates[1] = make_tuple(1,6);
    coordinates[2] = make_tuple(0,6);
    coordinates[3] = make_tuple(0,7);
    break;
  case(J):
    coordinates[0] = make_tuple(0,4);
    coordinates[1] = make_tuple(0,5);
    coordinates[2] = make_tuple(0,6);
    coordinates[3] = make_tuple(1,6);
    break;
  case(L):
    coordinates[0] = make_tuple(1,5);
    coordinates[1] = make_tuple(0,5);
    coordinates[2] = make_tuple(0,5);
    coordinates[3] = make_tuple(0,6);
    break;
  case(O):
    coordinates[0] = make_tuple(1,5);
    coordinates[1] = make_tuple(0,5);
    coordinates[2] = make_tuple(1,6);
    coordinates[3] = make_tuple(0,6);
    break;
  case(T):
    coordinates[0] = make_tuple(0,4);
    coordinates[1] = make_tuple(0,5);
    coordinates[2] = make_tuple(1,5);
    coordinates[3] = make_tuple(0,6);
    break;
  }


}

bool Piece::is_game_over(int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]) {
    for (auto[i,j] : coordinates) {
      if (graphical_matrix[i+1][j]==1) {
	return true;
      }
    }
    return false;
}

bool Piece::down(int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]) {
  
  bool ok_to_move = true;
  for (auto [i,j] : coordinates) {
    if ((graphical_matrix[i+1][j]==1) | (i == GLOBAL_ROW_NUMBERS - 1)) ok_to_move = false;
  }
  
  if (ok_to_move == true) {
    for (int i = 0; i < 4; i++) {
      int Y_Coordinate = std::get<0>(coordinates[i]);
      int X_Coordinate = std::get<1>(coordinates[i]);
      graphical_matrix[Y_Coordinate][X_Coordinate] = 0;
      std::get<0>(coordinates[i])++;
    }
    for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
    return true;
  }
  else {
    for (auto [i,j] : coordinates) graphical_matrix[i][j] = 1;
    return false;
  }
}

void Piece::left(int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]) {
    
  bool ok_to_move = true;
    
  for (auto [i,j]: coordinates){
    if (graphical_matrix[i][j-1]==1) ok_to_move = false;
  }

  if (ok_to_move == true) {
    for (int i = 0; i < 4; i++) {
      int y_coordinate = std::get<0>(coordinates[i]);
      int x_coordinate = std::get<1>(coordinates[i]);
      graphical_matrix[y_coordinate][x_coordinate] = 0;
      std::get<1>(coordinates[i])--;
    }
    for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
  }
}

  
void Piece::right(int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]) {
    
  bool ok_to_move = true;
    
  for (auto [i,j]: coordinates){
    if (graphical_matrix[i][j+1]==1 ) ok_to_move = false;
  }
    
  if (ok_to_move == true) {
    for (int i = 0; i < 4; i++) {
      int y_coordinate = std::get<0>(coordinates[i]);
      int x_coordinate = std::get<1>(coordinates[i]);
      graphical_matrix[y_coordinate][x_coordinate] = 0;
      std::get<1>(coordinates[i])++;
    }
    for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
  }
}

void Piece::clockwise(int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]) {

  using std::get;

  int pivot_x_coordinate,pivot_y_coordinate;
  
  switch(shape){
  case(I):
    pivot_y_coordinate = get<0>(coordinates[2]);
    pivot_x_coordinate = get<1>(coordinates[2]);
    switch(position){
    case(0):
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate-2][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-2;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate-1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-2] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-2;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate-1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(Z):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate+1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate+1;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(S):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate+1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate+1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
 case(J):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate]   |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate+1;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate-1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate-1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 2;
      }
      break;
    case(2):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate-1;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 3;
      }
      break;
    case(3):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate+1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(L):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate]   |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate-1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate+1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 2;
      }
      break;
    case(2):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate+1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 3;
      }
      break;
    case(3):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate-1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(T):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate-1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate-1;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 2;
      }
      break;
    case(2):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate+1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 3;
      }
      break;
    case(3):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate+1;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  }
}


void Piece::counter_clockwise(int graphical_matrix[GLOBAL_ROW_NUMBERS][GLOBAL_ROW_SIZE]) {
  
  using std::get;

  int pivot_x_coordinate,pivot_y_coordinate;
  
  switch(shape){
  case(I):
    pivot_y_coordinate = get<0>(coordinates[2]);
    pivot_x_coordinate = get<1>(coordinates[2]);
    switch(position){
    case(0):
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate-2][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-2;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate-1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-2] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-2;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate-1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(Z):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate+1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate+1;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(S):
    switch(position){
    case(0):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate+1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate+1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
 case(J):
    switch(position){
    case(2):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate]   |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate+1;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(3):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate-1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate-1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 2;
      }
      break;
    case(0):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate-1;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 3;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate+1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(L):
    switch(position){
    case(2):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate]   |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate-1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(3):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate+1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 2;
      }
      break;
    case(0):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate] |
	    graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate+1;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 3;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[2]);
      pivot_x_coordinate = get<1>(coordinates[2]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] |
	    graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate-1;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  case(T):
    switch(position){
    case(2):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate+1][pivot_x_coordinate])) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate-1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate-1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate+1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 1;
      }
      break;
    case(3):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate-1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate+1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate-1;
	get<1>(coordinates[3]) = pivot_x_coordinate-1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 2;
      }
      break;
    case(0):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate-1][pivot_x_coordinate] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate;
	get<0>(coordinates[0]) = pivot_y_coordinate+1;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate+1;
	get<0>(coordinates[2]) = pivot_y_coordinate;
	get<1>(coordinates[3]) = pivot_x_coordinate;
	get<0>(coordinates[3]) = pivot_y_coordinate-1;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 3;
      }
      break;
    case(1):
      pivot_y_coordinate = get<0>(coordinates[1]);
      pivot_x_coordinate = get<1>(coordinates[1]);
      if (!(graphical_matrix[pivot_y_coordinate][pivot_x_coordinate+1] )) {
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 0;
	get<1>(coordinates[0]) = pivot_x_coordinate-1;
	get<0>(coordinates[0]) = pivot_y_coordinate;
	get<1>(coordinates[1]) = pivot_x_coordinate;
	get<0>(coordinates[1]) = pivot_y_coordinate;
	get<1>(coordinates[2]) = pivot_x_coordinate;
	get<0>(coordinates[2]) = pivot_y_coordinate+1;
	get<1>(coordinates[3]) = pivot_x_coordinate+1;
	get<0>(coordinates[3]) = pivot_y_coordinate;
	for (auto [i,j] : coordinates) graphical_matrix[i][j] = 2;
	position = 0;
      }
      break;
    }
    break;
  } 
}

