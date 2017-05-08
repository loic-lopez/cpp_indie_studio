//
// EventStatus.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/EventStatus.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  lun. mai 08 12:51:59 2017 Loïc Lopez
// Last update lun. mai 08 12:51:59 2017 Loïc Lopez
//

#ifndef CPP_INDIE_STUDIO_EVENTSTATUS_HPP
#define CPP_INDIE_STUDIO_EVENTSTATUS_HPP

#include <cstdint>

enum class EventStatus : uint16_t
{
  STAND_BY = 0,
  ENTER_IN_GAME = 1,
  BACK_TO_MENU = 2,
  QUIT = 3
};

#endif //CPP_INDIE_STUDIO_EVENTSTATUS_HPP