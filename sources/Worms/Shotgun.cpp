//
// Shotgun.cpp for shotgun in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 08:05:48 2017 Stanislas Deneubourg
// Last update Thu Jun  1 08:06:48 2017 Stanislas Deneubourg
//


// TODO: ENLEVER LES PRINTS
#include <iostream>
#include "Worms/Shotgun.hpp"

Shotgun::Shotgun()
{
  this->splash_damage_range = 0.5;
  this->chargerNumber = 4;
  this->weight = 0.1;
  this->damagePerBullet = 5;
}

Shotgun::~Shotgun()
{
}

bool	Shotgun::fire()
{
  if (this->chargerNumber > 0)
    {
      this->chargerNumber--;
      std::cout << "FIRE SHOTGUN" << std::endl;
      return (true);
    }
  else
    {
      std::cout << "NO MORE " << std::endl;
      return (false);
    }

}
