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

       }

     }
     return_string.append("|\n");
     return return_string;
}



void Terminal::update_terminal(Game game) {
  
  std::string tmp = "";
  
  for (int row_index = 0; row_index < GLOBAL_ROW_NUMBERS; row_index++) {
    //write(STDOUT_FILENO, "______________________\n", 23);
    tmp.append(update_row(game.graphical_matrix[row_index]));
  }

  std::this_thread::sleep_for(std::chrono::microseconds(16667));

  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  write(STDOUT_FILENO, "______________________\n", 23);
  
  write(STDOUT_FILENO,tmp.c_str(),23*GLOBAL_ROW_NUMBERS);

  write(STDOUT_FILENO, "|____________________|\n", 23);
}

