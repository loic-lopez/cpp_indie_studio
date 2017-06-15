/*
** MenuButton.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/MenuButton.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  dim. mai 28 15:25:47 2017 Loïc Lopez
** Last update dim. mai 28 15:25:47 2017 Loïc Lopez
*/

#ifndef CPP_INDIE_STUDIO_MENUBUTTON_HPP
#define CPP_INDIE_STUDIO_MENUBUTTON_HPP

#include <cstdint>

enum 						MenuButton		: uint8_t
{
  PLAY_A_GAME					=			1,
  EXIT						=			2,
  OPTIONS					=			3,
  OPTION_SOUND					=			4,
  OPTION_MAP					=			5,
  BACK						=			6,
  SAVES						=			7,
  PLAY_A_GAME_SUBMENU_ADD_HUMAN_TEAM 		=			8,
  PLAY_A_GAME_SUBMENU_SUBTRACT_HUMAN_TEAM 	=			9,
  PLAY_A_GAME_SUBMENU_ADD_BOT_TEAM 		=			10,
  PLAY_A_GAME_SUBMENU_SUBTRACT_BOT_TEAM 	=			11,
  PLAY_A_GAME_SUBMENU_ADD_TEAM	 		=			12,
  PLAY_A_GAME_SUBMENU_SUBTRACT_TEAM 		=			13,
  PLAY_A_GAME_SUBMENU_ADD_WORMS_PER_TEAM	=			14,
  PLAY_A_GAME_SUBMENU_SUBTRACT_WORMS_PER_TEAM	=			15,
  PLAY					 	=			16,
  STANDBY					=			17
};

enum						MenuInGameButton	: uint8_t
{
  BACK_TO_GAME					=			1,
  SAVE_CURRENT_GAME				=			2,
  SOUND_OPTION					=			3,
  BACK_TO_MENU					=			4,
  EXIT_IN_GAME					=			5,
  SOUND_OPTION_SUBMENU_SOUND_CHECKBOX		=			6,
  SUBMENU_BACK					=			7
};

enum 						InventoryButton		: uint8_t
{
  UZI						=			20,
  SHOTGUN					=			21,
  SURRENDER					=			22
};

#endif //CPP_INDIE_STUDIO_MENUBUTTON_HPP