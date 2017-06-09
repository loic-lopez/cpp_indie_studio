/*
** Uzi.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Uzi.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:45:54 2017 Loïc Lopez
** Last update ven. juin 09 14:45:54 2017 Loïc Lopez
*/

#include "Worms/Uzi.hpp"

Uzi::Uzi()
{
  this->bulletsNumber = 30;
}

Uzi::~Uzi()
{

}

bool	Uzi::fire()
{
  if (this->bulletsNumber > 0)
    {
      this->bulletsNumber--;
      return (true);
    }
  return (false);
}
