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

enum 		MenuButton		: uint8_t
{
  PLAY			=		1,
  EXIT			=		2,
  OPTIONS		=		3,
  OPTION_SOUND		=		4,
  OPTION_MAP		=		5,
  BACK			=		6,
  SAVES			=		7
};

#endif //CPP_INDIE_STUDIO_MENUBUTTON_HPP