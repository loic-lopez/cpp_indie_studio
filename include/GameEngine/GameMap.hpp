/*
** GameMap.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/GameMap.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. juin 15 16:52:21 2017 Loïc Lopez
** Last update jeu. juin 15 16:52:21 2017 Loïc Lopez
*/

#ifndef CPP_INDIE_STUDIO_GAMEMAP_HPP
#define CPP_INDIE_STUDIO_GAMEMAP_HPP

#include <cstdint>

namespace	GameNamespace
{
  enum		class	TerrainType : uint16_t
  {
    AIR = 0,
    GROUND = 1,
    WORM = 2
  };

  struct	GameMap
  {
    int 	x;
    int 	y;
    TerrainType terrain;

    GameMap(int, int);
  };
}

#endif //CPP_INDIE_STUDIO_GAMEMAP_HPP