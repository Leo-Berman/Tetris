// Library imports
#include "SDL/SDL.h"
#include "class_definitions.h"



  
int main(){
  Game* Game_Instance = new Game();
  SDL_Event Keyboard_Event;
  int Delay_Auto_Shift = 16;
  int First_Hit_Timer = 6;
  int Frames_Until_Fall = Game_Instance->Level;

  bool Advance_Frame = false;
  
  bool Down_First_Hit = false;
  bool Left_First_Hit = false;
  bool Right_First_Hit = false;
  bool Up_First_Hit = false;
  bool Clockwise_First_Hit = false;
  bool Counter_Clockwise_First_Hit = false;
  
  bool Down_State = false;
  bool Left_State = false;
  bool Right_State = false;
  bool Up_State = false;
  bool Clockwise_State = false;
  bool Counter_Clockwise_State = false;

  auto Previous_Time = std::chrono::high_resolution_clock::now();
  
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
	if (Down_State == false) {
	  Game_Instance->Process_Command(false,true,false,false,false,false);
	}
	Down_State = true;
	Down_First_Hit = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Down_State = false;
	Down_First_Hit = false;
      }
      break;
    case SDLK_UP:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	if (Up_State == false) {
	  Game_Instance->Process_Command(true,false,false,false,false,false);

	}
	Up_State = true;
	Up_First_Hit = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Up_State = false;
	Up_First_Hit = false;
      }
      break;
    case SDLK_LEFT:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	if (Left_State == false) {
	  Game_Instance->Process_Command(false,false,true,false,false,false);
	  Delay_Auto_Shift = 16;
	}
	Left_State = true;
	Left_First_Hit = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Left_State = false;
	Left_First_Hit = false;
      }
      break;
    case SDLK_RIGHT:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	if (Right_State == false) {
	  Game_Instance->Process_Command(false,false,false,true,false,false);
	  Delay_Auto_Shift = 16;
	}
	Right_State = true;
	Right_First_Hit = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Right_State = false;
	Right_First_Hit = false;
      }
      break;
    case SDLK_q:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	if (Counter_Clockwise_State == false) {
	  Game_Instance->Process_Command(false,false,false,false,true,false);
	}
	Counter_Clockwise_State = true;
	Counter_Clockwise_First_Hit  = true;
      }
	else if (Keyboard_Event.type == SDL_KEYUP) {
	  Counter_Clockwise_State = false;
	  Counter_Clockwise_First_Hit = false;
	}
      break;
    case SDLK_e:
      if (Keyboard_Event.type == SDL_KEYDOWN) {
	if (Clockwise_State == false) {
	  Game_Instance->Process_Command(false,false,false,false,false,true);
	}
	Clockwise_State = true;
	Clockwise_First_Hit = true;
      }
      else if (Keyboard_Event.type == SDL_KEYUP) {
	Clockwise_State = false;
	Clockwise_First_Hit = false;
	break;
      }
    }

    if (Advance_Frame) {

      Advance_Frame = false;
      if (Delay_Auto_Shift == 0) {
	Game_Instance->Process_Command(Up_State,Down_State,Left_State,Right_State, false, false);
	Delay_Auto_Shift = 6;
      }

      if (Frames_Until_Fall == 0) {
	Frames_Until_Fall = Game_Instance->Level;
	Game_Instance->Advance_Frame();
      
      }

      if (Up_State | Down_State | Left_State | Right_State | Counter_Clockwise_State | Clockwise_State) {
	Delay_Auto_Shift--;
      }

      First_Hit_Timer--;
      Frames_Until_Fall--;
    }

    auto Current_Time = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::microseconds>(Current_Time - Previous_Time).count() >= 16683) {
      Previous_Time = std::chrono::high_resolution_clock::now();
      Advance_Frame = true;
    }
        
  }
  

  return 0;

}
