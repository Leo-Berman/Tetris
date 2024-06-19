#include "header.h"

Terminal::Terminal() {

  tcgetattr(STDIN_FILENO, &original_terminal);

  terminal_info.c_iflag = (IGNPAR | IGNBRK | INPCK | ISTRIP | IUCLC);
  terminal_info.c_oflag = (OPOST | OLCUC | ONLCR);
  terminal_info.c_cflag = (CS8 | CREAD);
  terminal_info.c_lflag = (0);
  
  terminal_info.c_cc[VMIN] = 0;
  terminal_info.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal_info);
  std::string tmp = "";
  tmp.append("\E[H\E[J________________________\n");

  for (int row_index = 0; row_index < GLOBAL_ROW_NUMBERS; row_index++) {
    tmp.append("|                      |\n");
  }
	
  tmp.append("________________________\n");

  printf("%s",tmp.c_str());
}

Terminal::~Terminal() {
  reset_terminal();
}

void Terminal::reset_terminal() {
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal);
}

bool Terminal::process_keystroke(Game game) {
  char command;
  
  read(STDIN_FILENO, &command,1);
  
  if (command == CTRL_KEY('q')) return false;

  return true;
}

std::string Terminal::update_row(int row[GLOBAL_ROW_SIZE]) {
  
  std::string return_string = "|";
  
     for(int column_index = 0; column_index < GLOBAL_ROW_SIZE; column_index++) {
       if (row[column_index] == 0) {
	 return_string.append("  ");
       }
       else {
	 return_string.append("[]");
	 if (row[column_index] == 2) {
	   }
       }

     }
     return_string.append("|\n");
     return return_string;
}




void Terminal::update_terminal(Game game) {

  int horizontal_conversion;
  char tmp[11];
  
  for (auto[i,j] : game.active_piece->coordinates) {
    
    
    if (j == 0) {
      horizontal_conversion = 1;
    }
    else {
      horizontal_conversion = (j*2)+1;
    }
    
    sprintf(tmp,"\x1b[%d;%dH",i+2,horizontal_conversion);
    //printf("\x1b[%d;%dH",i+2,horizontal_conversion);
    //printf("  ");
    write(STDOUT_FILENO,tmp,8);
    write(STDOUT_FILENO,"  ",2);
  }
  game.update_game();
  for (auto[i,j] : game.active_piece->coordinates) {
    
    if (j == 0) {
      horizontal_conversion = 1;
    }
    else {
      horizontal_conversion = (j*2)+1;
    }
    //printf("\x1b[%d;%dH,[]",i,j);
    //printf("\x1b[%d;%dH",i+2,horizontal_conversion);
    //printf("[]");
    sprintf(tmp,"\x1b[%d;%dH",i+2,horizontal_conversion);
    write(STDOUT_FILENO,tmp,8);
    write(STDOUT_FILENO,"[]",2);
  }

  printf("\x1b[%d;%dH",0,0);
  std::this_thread::sleep_for(std::chrono::microseconds(16667));
  
}

