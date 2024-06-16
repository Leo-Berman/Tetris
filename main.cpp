// Library imports
#include <chrono>
#include <thread>
#include "SDL/SDL.h"
#include "class_definitions.h"



  
int main(){
  Game* Game_Instance = new Game();
  SDL_Event Keyboard_Event;
  int Delay_Auto_Shift = 16;
  int Frames_Until_Fall = Game_Instance->Level;
  
  bool First_Hit = false;
  bool Down_State = false;
  bool Left_State = false;
  bool Right_State = false;
  bool Up_State = false;
  bool Clockwise_State = false;
  bool Counter_Clockwise_State = false;

  bool Down_Previous_State = false;
  bool Left_Previous_State = false;
  bool Right_Previous_State = false;
  bool Up_Previous_State = false;
  bool Clockwise_Previous_State = false;
  bool Counter_Clockwise_Previous_State = false;

  
  
  if( SDL_Init( SDL_INIT_VIDEO ) < 0) exit( -1 );
  if( !SDL_SetVideoMode( 250, 250, 0, 0 ) ){
    SDL_Quit();
    exit( -1 );
  }
  
  while(true){ 
    SDL_PollEvent( &Keyboard_Event );

    switch(Keyboard_Event.key.keysym.sym){
    case SDLK_DOWN:
      if (Keyboard_Event.type == SDL_KEYDOWN) Down_State = true;
      else if (Keyboard_Event.type == SDL_KEYUP) Down_State = false;
      break;
    case SDLK_UP:
      if (Keyboard_Event.type == SDL_KEYDOWN)  Up_State = true;
      else if (Keyboard_Event.type == SDL_KEYUP) Up_State = false;
      break;
    case SDLK_LEFT:
      if (Keyboard_Event.type == SDL_KEYDOWN) Left_State = true;
      else if (Keyboard_Event.type == SDL_KEYUP) Left_State = false;
      break;
    case SDLK_RIGHT:
      if (Keyboard_Event.type == SDL_KEYDOWN) Right_State = true;
      else if (Keyboard_Event.type == SDL_KEYUP) Right_State = false;
      break;
  case SDLK_q:
    if (Keyboard_Event.type == SDL_KEYDOWN) Counter_Clockwise_State = true;
      else if (Keyboard_Event.type == SDL_KEYUP) Counter_Clockwise_State = false;
      break;
  case SDLK_e:
    if (Keyboard_Event.type == SDL_KEYDOWN) Clockwise_State = true;
      else if (Keyboard_Event.type == SDL_KEYUP) Clockwise_State = false;
      break;
    }

    if ((Right_State>Right_Previous_State) | (Left_State>Left_Previous_State)) Delay_Auto_Shift = 16;

    if ((Right_State>Right_Previous_State) | (Left_State>Left_Previous_State) | (Up_State>Up_Previous_State) | (Down_State>Down_Previous_State) | (Clockwise_State>Clockwise_Previous_State) | (Counter_Clockwise_State>Counter_Clockwise_Previous_State)) First_Hit=true;
    else First_Hit = false;
    
    if (First_Hit == true) {
	Game_Instance->Process_Command(Up_State,Down_State,Left_State,Right_State, Counter_Clockwise_State, Clockwise_State);
	if(Delay_Auto_Shift<16) Delay_Auto_Shift = 16;
      }
    
    else if (Delay_Auto_Shift == 0) {
      Delay_Auto_Shift = 6;
      Game_Instance->Process_Command(Up_State,Down_State,Left_State,Right_State, Counter_Clockwise_State, Clockwise_State);
    }

    if (Frames_Until_Fall == 0) {
      Frames_Until_Fall = Game_Instance->Level;
      Game_Instance->Advance_Frame();
      
    }

    if (Up_State | Down_State | Left_State | Right_State | Counter_Clockwise_State | Clockwise_State) {
      Delay_Auto_Shift--;
    }
    
    Frames_Until_Fall--;
    Right_Previous_State = Right_State;
    Left_Previous_State = Left_State;
    Up_Previous_State = Up_State;
    Down_Previous_State = Down_State;
    Clockwise_Previous_State = Clockwise_State;
    Counter_Clockwise_Previous_State = Counter_Clockwise_State;
    std::this_thread::sleep_for(std::chrono::microseconds(16666));
    
  }
  

  return 0;

}
