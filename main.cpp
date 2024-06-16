// Library imports
#include <chrono>
#include <thread>
#include "SDL/SDL.h"
#include "class_definitions.h"



  
int main(){
  Game* Game_Instance = new Game();
  int Frame_Counter = 1;
  SDL_Event Keyboard_Event;
  bool Down_State = 0;
  bool Left_State = 0;
  bool Right_State = 0;
  bool Up_State = 0;
  bool Clockwise_State = 0;
  bool Counter_Clockwise_State = 0;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0) exit( -1 );
  if( !SDL_SetVideoMode( 250, 250, 0, 0 ) ){
    SDL_Quit();
    exit( -1 );
  }
  
  while(true){ 
    SDL_PollEvent( &Keyboard_Event );

    switch(Keyboard_Event.key.keysym.sym){
    case SDLK_DOWN:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Down_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Down_State = false;
      }
      break;
    case SDLK_UP:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Up_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Up_State = false;
      }
      break;
    case SDLK_LEFT:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Left_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Left_State = false;
      }
      break;
    case SDLK_RIGHT:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	Right_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Right_State = false;
      }
      break;
  case SDLK_q:
    if (Keyboard_Event.type == SDL_KEYDOWN) {
	Counter_Clockwise_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Counter_Clockwise_State = false;
      }
      break;
  case SDLK_e:
    if (Keyboard_Event.type == SDL_KEYDOWN) {
	Clockwise_State = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Clockwise_State = false;
      }
      break;
    }
if (Frame_Counter % 6 == 0) Game_Instance->Process_Command(Up_State,Down_State,Left_State,Right_State, Counter_Clockwise_State, Clockwise_State);
    
      if (Frame_Counter == 60-Game_Instance->Level*6) {
      Frame_Counter = 1;
      Game_Instance->Advance_Frame();
    }
    
    Frame_Counter++;
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
  }
  

  return 0;

}
