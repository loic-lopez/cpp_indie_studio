//
// EventStatus.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/EventStatus.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  lun. mai 08 12:51:59 2017 Loïc Lopez
// Last update Mon May  8 13:21:10 2017 Loïc Dupil
//

#ifndef CPP_INDIE_STUDIO_EVENTSTATUS_HPP
#define CPP_INDIE_STUDIO_EVENTSTATUS_HPP

#include <cstdint>

enum class EventStatus : uint16_t
{
  STAND_BY = 0,
  ENTER_IN_GAME = 1,
  BACK_TO_MENU = 2,
  IN_GAME_MENU = 3,
  SETTINGS = 4,
  SAVES = 5,
  LOAD = 6,
  QUIT = 7,
  SPLASH = 8
};

#endif //CPP_INDIE_STUDIO_EVENTSTATUS_HPP
