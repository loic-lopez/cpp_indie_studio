/*
** Inventory.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Inventory.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:31:33 2017 Loïc Lopez
** Last update ven. juin 09 14:31:33 2017 Loïc Lopez
*/

#include <iostream>
#include "Worms/Inventory.hpp"

Inventory::Inventory()
{
  this->weaponsInInventory.emplace_back(new Uzi);
}

Inventory::~Inventory()
{

}

void	Inventory::fireWithSelectedWeapon(size_t const &weaponInGui)
{
  if (this->weaponsInInventory.at(weaponInGui)->fire())
    std::cout << "FIRE !" << std::endl;
  else
    std::cout << "NO MORE BULLETS" << std::endl;
}
