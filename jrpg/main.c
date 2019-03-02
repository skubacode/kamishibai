#include<stdio.h>

#define _INDEX_MAIN_MENU_           0
#define _INDEX_LOCAL_MAP_            1
#define _INDEX_WORLD_MAP_          2
#define _INDEX_BATTLE_                     3
#define _INDEX_IN_GAME_MENU_   4

#define _GAME_MODES_NUMBER_  5

struct  Game_Mode
{
  int id;
  void (*update)(float elapsed_time) ;
  void (*render)();
  void (*on_enter)();
  void (*on_exit)();
};

/**************************************************
 * GAME MODE: 
 * MAIN MENU 
 **************************************************/
void main_menu_update( float elapsed_time ) 
{
  puts("main menu update");
}//main_menu_update

void main_menu_render()
{
  puts("main menu render");	
}//main_menu_render

void main_menu_enter()
{
  puts("main menu enter");	
}//main_menu_enter

void main_menu_exit()
{
  puts("main menu exit");	
}//main_menu_exit

/**************************************************
 * GAME MODE: 
 * LOCAL MAP
 **************************************************/
void local_map_update( float elapsed_time ) 
{
  puts("local map update");
}//local_map_update

void local_map_render()
{
  puts("local map render");	
}//local_map_render

void local_map_enter()
{
  puts("local map enter");	
}//local_map_enter

void local_map_exit()
{
  puts("local map exit");	
}//local_map_exit


/**************************************************
 * GAME MODE: 
 * WORLD MAP
 **************************************************/
void world_map_update( float elapsed_time ) 
{
  puts("world map update");
}//world_map_update

void world_map_render()
{
  puts("world map render");	
}//world_map_render

void world_map_enter()
{
  puts("world map enter");	
}//world_map_enter

void world_map_exit()
{
  puts("world map exit");	
}//world_map_exit

/**************************************************
 * GAME MODE: 
 * BATTLE
 **************************************************/
void battle_update( float elapsed_time ) 
{
  puts("battle update");
}//battle_update

void battle_render()
{
  puts("battle render");	
}//battle_render

void battle_enter()
{
  puts("battle enter");	
}//battle_enter

void battle_exit()
{
  puts("battle exit");	
}//battle_exit

/**************************************************
 * GAME MODE: 
 * IN GAME MENU
**************************************************/
void in_game_menu_update( float elapsed_time ) 
{
  puts("in game menu update");
}//battle_update

void in_game_menu_render()
{
  puts("in game menu render");	
}//battle_render

void in_game_menu_enter()
{
  puts("in game menu enter");	
}//void in_game_menu_enter()

void in_game_menu_exit()
{
  puts("in game menu exit");	
}//in_game_menu_exit


struct State_Machine
{
  struct Game_Mode game_modes[_GAME_MODES_NUMBER_];
  int index_current_game_mode;

  void (*update)(float elapsed_time) ;
  void (*render)();
  void (*change)();
  void (*add)();  
};//State_Machine

void state_machine_update(float elapsed_time)
{
  puts("state machine update");	
}//state_machine_update

void state_machine_render( const struct Game_Mode *game_mode )
{
  puts("state machine render");
  game_mode->render();	  
}//state_machine_render

void state_machine_change()
{
  puts("state machine change");
}//state_machine_change

void state_machine_add()
{
  puts("state machine add");
}//state_machine_add


int main(int argc, char** argv) 
{
  puts("jrpg");	
  /* Game Modes initialization */
  struct  Game_Mode menu_game_mode;
  menu_game_mode.id = _INDEX_MAIN_MENU_;
  menu_game_mode.update = main_menu_update;
  menu_game_mode.render = main_menu_render;
  menu_game_mode.on_enter = main_menu_enter;
  menu_game_mode.on_exit = main_menu_exit;

  struct  Game_Mode local_map_game_mode;
  local_map_game_mode.id = _INDEX_LOCAL_MAP_;
  local_map_game_mode.update = local_map_update;
  local_map_game_mode.render =  local_map_render;
  local_map_game_mode.on_enter =   local_map_enter;
  local_map_game_mode.on_exit =  local_map_exit;
  
  struct  Game_Mode world_map_game_mode;
  world_map_game_mode.id = _INDEX_WORLD_MAP_;
  world_map_game_mode.update =  world_map_update;
  world_map_game_mode.render =  world_map_render;
  world_map_game_mode.on_enter =  world_map_enter;
  world_map_game_mode.on_exit =  world_map_exit;

  struct  Game_Mode battle_game_mode;
  battle_game_mode.id = _INDEX_BATTLE_;
  battle_game_mode.update = world_map_update;
  battle_game_mode.render = world_map_render;
  battle_game_mode.on_enter = world_map_enter;
  battle_game_mode.on_exit = world_map_exit;

  struct Game_Mode in_game_menu_game_mode;
  in_game_menu_game_mode.id = _INDEX_IN_GAME_MENU_;
  in_game_menu_game_mode.update = in_game_menu_update;
  in_game_menu_game_mode.render = in_game_menu_render;
  in_game_menu_game_mode.on_enter = in_game_menu_enter;
  in_game_menu_game_mode.on_exit = in_game_menu_exit;
  /* Eo Game Mode initialization */

  /* Statem Machine initialization*/
 struct State_Machine state_machine;
 state_machine.game_modes[_INDEX_MAIN_MENU_] = menu_game_mode;
 state_machine.game_modes[_INDEX_LOCAL_MAP_] = local_map_game_mode;
 state_machine.game_modes[_INDEX_WORLD_MAP_] = world_map_game_mode;
 state_machine.game_modes[_INDEX_BATTLE_] = battle_game_mode;
 state_machine.game_modes[_INDEX_IN_GAME_MENU_] = in_game_menu_game_mode;
 state_machine.index_current_game_mode = _INDEX_MAIN_MENU_;  //menu_game_mode

 state_machine.update = state_machine_update;
 state_machine.render = state_machine_render;
 state_machine.change = state_machine_change;
 state_machine.add = state_machine_add;

 state_machine.render( &state_machine.game_modes[state_machine.index_current_game_mode] );

 // Command
  state_machine.index_current_game_mode = _INDEX_WORLD_MAP_;  //menu_game_mode
  state_machine.render( &state_machine.game_modes[state_machine.index_current_game_mode] );

  return 0;
}//main