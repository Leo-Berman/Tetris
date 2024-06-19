#include "header.h"

int main() {;
  Terminal terminal = Terminal();
  Game game = Game();
  int frame_counter = 0;

  std::vector<std::thread> threads;
  threads.push_back(std::thread(&Terminal::update_terminal,std::ref(terminal),game));

  threads.push_back(std::thread(&Terminal::process_keystroke,std::ref(terminal),game));
  for (auto &th : threads) {
    th.join();
  }
  
  while(true) {


  
  
    if(terminal.process_keystroke(game) == false) break;

    terminal.update_terminal(game);

   
    }

}
