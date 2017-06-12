/*
** Uzi.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Uzi.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:45:54 2017 Loïc Lopez
** Last update ven. juin 09 14:45:54 2017 Loïc Lopez
*/

// TODO: ENLEVER LES PRINTS
#include <iostream>
#include "Worms/Uzi.hpp"

Uzi::Uzi()
{
  this->bulletsNumber = 30;
  this->damagePerBullet = 5;
  this->weight = 0;
}

Uzi::~Uzi()
{

}

bool	Uzi::fire()
{
  if (this->bulletsNumber > 0)
    {
      std::cout << "FIRE WITH UZI" << std::endl;
      this->bulletsNumber--;
      return (true);
    }
  std::cout << "NO MORE BULLETS IN UZI" << std::endl;
  return (false);
}

void  Uzi::showWeapon()
{

}
