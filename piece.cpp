#include "class_definitions.h"

Piece::Piece(int Type) {

  Shape = Type;
  Position = 0;
  using std::make_tuple;
  
  switch(Type) {
  case(I):
    Coordinates[0] = make_tuple(2,3);
    Coordinates[1] = make_tuple(2,4);
    Coordinates[2] = make_tuple(2,5);
    Coordinates[3] = make_tuple(2,6);
    break;
  case(Z):
    Coordinates[0] = make_tuple(2,3);
    Coordinates[1] = make_tuple(2,4);
    Coordinates[2] = make_tuple(3,4);
    Coordinates[3] = make_tuple(3,5);
    break;
  case(S):
    Coordinates[0] = make_tuple(3,3);
    Coordinates[1] = make_tuple(3,4);
    Coordinates[2] = make_tuple(2,4);
    Coordinates[3] = make_tuple(2,5);
    break;
  case(J):
    Coordinates[0] = make_tuple(2,4);
    Coordinates[1] = make_tuple(2,5);
    Coordinates[2] = make_tuple(2,6);
    Coordinates[3] = make_tuple(3,6);
    break;
  case(L):
    Coordinates[0] = make_tuple(3,4);
    Coordinates[1] = make_tuple(2,4);
    Coordinates[2] = make_tuple(2,5);
    Coordinates[3] = make_tuple(2,6);
    break;
  case(O):
    Coordinates[0] = make_tuple(2,4);
    Coordinates[1] = make_tuple(1,4);
    Coordinates[2] = make_tuple(2,5);
    Coordinates[3] = make_tuple(1,5);
    break;
  case(T):
    Coordinates[0] = make_tuple(1,4);
    Coordinates[1] = make_tuple(2,4);
    Coordinates[2] = make_tuple(2,5);
    Coordinates[3] = make_tuple(1,6);
    break;
  }
}
  
bool Piece::Down(int Graphical_Matrix[29][14]) {
  
  bool Ok_To_Move = true;
  
  for (auto [i,j] : Coordinates) {
    if ((Graphical_Matrix[i+1][j]==1) | (i == 28)) Ok_To_Move = false;
  }
  
  if (Ok_To_Move == true) {
    for (int i = 0; i < 4; i++) {
      int Y_Coordinate = std::get<0>(Coordinates[i]);
      int X_Coordinate = std::get<1>(Coordinates[i]);
      Graphical_Matrix[Y_Coordinate][X_Coordinate] = 0;
      std::get<0>(Coordinates[i])++;
    }
    for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
    return true;
  }
  else {
    for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 1;
    return false;
  }
}

void Piece::Left(int Graphical_Matrix[29][14]) {
    
  bool Ok_To_Move = true;
    
  for (auto [i,j]: Coordinates){
    if (Graphical_Matrix[i][j-1]==1) Ok_To_Move = false;
  }

  if (Ok_To_Move == true) {
    for (int i = 0; i < 4; i++) {
      int Y_Coordinate = std::get<0>(Coordinates[i]);
      int X_Coordinate = std::get<1>(Coordinates[i]);
      Graphical_Matrix[Y_Coordinate][X_Coordinate] = 0;
      std::get<1>(Coordinates[i])--;
    }
    for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
  }
}

  
void Piece::Right(int Graphical_Matrix[29][14]) {
    
  bool Ok_To_Move = true;
    
  for (auto [i,j]: Coordinates){
    if (Graphical_Matrix[i][j+1]==1 ) Ok_To_Move = false;
  }
    
  if (Ok_To_Move == true) {
    for (int i = 0; i < 4; i++) {
      int Y_Coordinate = std::get<0>(Coordinates[i]);
      int X_Coordinate = std::get<1>(Coordinates[i]);
      Graphical_Matrix[Y_Coordinate][X_Coordinate] = 0;
      std::get<1>(Coordinates[i])++;
    }
    for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
  }
}

void Piece::Clockwise(int Graphical_Matrix[29][14]) {

  using std::get,std::make_tuple;

  int Pivot_X_Coordinate,Pivot_Y_Coordinate;
  
  switch(Shape){
  case(I):
    Pivot_Y_Coordinate = get<0>(Coordinates[2]);
    Pivot_X_Coordinate = get<1>(Coordinates[2]);
    switch(Position){
    case(0):
      if (!(Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate] |
	    Graphical_Matrix[Pivot_Y_Coordinate-2][Pivot_X_Coordinate] |
	    Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate-2;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate-1;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate+1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 1;
      }
      break;
    case(1):
      if (!(Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate-1] |
	    Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate-2] |
	    Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate+1])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate-2;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 0;
      }
      break;
    }
    break;
  case(Z):
    switch(Position){
    case(0):
      Pivot_Y_Coordinate = get<0>(Coordinates[1]);
      Pivot_X_Coordinate = get<1>(Coordinates[1]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate+1] |
	    Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate+1])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate-1;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate+1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 1;
      }
      break;
    case(1):
      Pivot_Y_Coordinate = get<0>(Coordinates[2]);
      Pivot_X_Coordinate = get<1>(Coordinates[2]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate+1] |
	    Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate-1])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate+1;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate+1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 0;
      }
      break;
    }
    break;
  case(S):
    switch(Position){
    case(0):
      Pivot_Y_Coordinate = get<0>(Coordinates[2]);
      Pivot_X_Coordinate = get<1>(Coordinates[2]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate] |
	    Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate+1])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate-1;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate+1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 1;
      }
      break;
    case(1):
      Pivot_Y_Coordinate = get<0>(Coordinates[1]);
      Pivot_X_Coordinate = get<1>(Coordinates[1]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate-1] |
	    Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate+1;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate+1;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 0;
      }
      break;
    }
    break;
 case(J):
    switch(Position){
    case(0):
      Pivot_Y_Coordinate = get<0>(Coordinates[1]);
      Pivot_X_Coordinate = get<1>(Coordinates[1]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate-1] |
	    Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate]   |
	    Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate])) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate-1;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate+1;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate+1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 1;
      }
      break;
    case(1):
      Pivot_Y_Coordinate = get<0>(Coordinates[1]);
      Pivot_X_Coordinate = get<1>(Coordinates[1]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate+1] |
	    Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate-1] |
	    Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate-1] )) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate-1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 2;
      }
      break;
    case(2):
      Pivot_Y_Coordinate = get<0>(Coordinates[1]);
      Pivot_X_Coordinate = get<1>(Coordinates[1]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate] |
	    Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate] |
	    Graphical_Matrix[Pivot_Y_Coordinate-1][Pivot_X_Coordinate+1] )) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate+1;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate-1;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate-1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 3;
      }
      break;
    case(3):
      Pivot_Y_Coordinate = get<0>(Coordinates[1]);
      Pivot_X_Coordinate = get<1>(Coordinates[1]);
      if (!(Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate+1] |
	    Graphical_Matrix[Pivot_Y_Coordinate][Pivot_X_Coordinate-1] |
	    Graphical_Matrix[Pivot_Y_Coordinate+1][Pivot_X_Coordinate+1] )) {
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 0;
	get<1>(Coordinates[0]) = Pivot_X_Coordinate-1;
	get<0>(Coordinates[0]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[1]) = Pivot_X_Coordinate;
	get<0>(Coordinates[1]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[2]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[2]) = Pivot_Y_Coordinate;
	get<1>(Coordinates[3]) = Pivot_X_Coordinate+1;
	get<0>(Coordinates[3]) = Pivot_Y_Coordinate+1;
	for (auto [i,j] : Coordinates) Graphical_Matrix[i][j] = 2;
	Position = 0;
      }
      break;
    }
    break;
  }
}


void Piece::Counter_Clockwise(int Graphical_Matrix[29][14]) {

  bool Ok_To_Rotate = true;

    
}

