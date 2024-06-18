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

bool Terminal::update_terminal() {

  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  write(STDOUT_FILENO, "______________________\n", 23);
  write(STDOUT_FILENO, "|                     |\n", 23);
  write(STDOUT_FILENO, "bal", 3);
  char command;

  read(STDIN_FILENO, &command,1);

  if (command == CTRL_KEY('q')){
    
    return false;
  }
  /*for (int line = 0; line < terminal_size.ws_col; line++) {
    write(STDOUT_FILENO, "Balls", 6);
    }*/
  return true;
}
