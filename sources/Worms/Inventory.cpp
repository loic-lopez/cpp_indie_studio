/*
** Inventory.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Inventory.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:31:33 2017 Loïc Lopez
** Last update ven. juin 09 14:31:33 2017 Loïc Lopez
*/

// TODO: REMOVE PRINT
#include <iostream>
#include "Worms/Inventory.hpp"

Inventory::Inventory()
{
  this->weaponsInInventory.emplace_back(new Uzi);
  this->weaponsInInventory.emplace_back(new Shotgun);
}

Inventory::~Inventory()
{

}

void	Inventory::fireWithSelectedWeapon(size_t const &weaponSelectedInGui)
{
  if (this->weaponsInInventory.at(weaponSelectedInGui)->fire())
    std::cout << "FIRE !" << std::endl;
  else
    std::cout << "NO MORE BULLETS" << std::endl;
}
