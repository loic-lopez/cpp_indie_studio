/*
** MouseWheelState.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/MouseWheelState.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 02 12:56:36 2017 Loïc Lopez
** Last update ven. juin 02 12:56:36 2017 Loïc Lopez
*/

#ifndef CPP_INDIE_STUDIO_MOUSEWHEELSTATE_HPP
#define CPP_INDIE_STUDIO_MOUSEWHEELSTATE_HPP

#include <cstdint>

enum	class	MouseWheelState	: uint8_t
{
  STANDBY	=		1,
  SCROLL_UP	=		2,
  SCROLL_DOWN	=		3,
};

#endif //CPP_INDIE_STUDIO_MOUSEWHEELSTATE_HPP