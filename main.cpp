#include "header.h"

int main() {
  Terminal terminal = Terminal();

  while(true) {
    if (terminal.update_terminal() == false) {
      break;
    }
  }

}
