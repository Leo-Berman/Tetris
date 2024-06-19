#include "header.h"

int main() {;
  Terminal terminal = Terminal();
  Game game = Game();
  while(true) {
    if(terminal.process_keystroke(game) == false) break;
    terminal.update_terminal(game);
    }

}
