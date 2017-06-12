/*
** Inventory.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Inventory.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:31:33 2017 Loïc Lopez
// Last update Mon Jun 12 18:23:21 2017 Stanislas Deneubourg
*/

// TODO: REMOVE PRINT
#include <iostream>
#include "Worms/Inventory.hpp"

Inventory::Inventory(irr::IrrlichtDevice *device)
{
  this->weaponsInInventory.emplace_back(new Uzi(device));
  this->weaponsInInventory.emplace_back(new Shotgun(device));
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

void	Inventory::showSelectedWeapon(size_t const &weaponSelectedInGui)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->showWeapon();
}

void	Inventory::setWeaponPositionToWormPosition(size_t const &weaponSelectedInGui,
						       const irr::core::vector3df &position)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->setWeaponPosition(position);
}

void	Inventory::setWeaponRotationToWormPosition(size_t const &weaponSelectedInGui,
						       const irr::core::vector3df &rotation)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->setWeaponRotation(rotation);
}
