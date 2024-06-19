#include "header.h"
#include <future>
int main() {;
  Terminal terminal = Terminal();
  Game game = Game();
  int frame_counter = 0;

  /*std::vector<std::thread> threads;
  threads.push_back(std::thread(&Terminal::update_terminal,std::ref(terminal),game));

  threads.push_back(std::thread(&Terminal::process_keystroke,std::ref(terminal),game));*/
  
   std::thread t1 = std::thread(std::thread(&Terminal::update_terminal,std::ref(terminal),game));
    
    t1.detach();
  while(true) {

    std::thread t2 = std::thread(&Terminal::process_keystroke,std::ref(terminal),game);
    t2.join();

   
    }

}
