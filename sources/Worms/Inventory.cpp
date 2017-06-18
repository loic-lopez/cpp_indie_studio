/*
** Inventory.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Inventory.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:31:33 2017 Loïc Lopez
// Last update Sun Jun 18 16:53:07 2017 Stanislas Deneubourg
*/

// TODO: REMOVE PRINT
#include <iostream>
#include "Worms/Inventory.hpp"

Inventory::Inventory(irr::IrrlichtDevice *device,
		     irrklang::ISoundEngine *soundEngine) : _device(device)
{
  this->weaponsInInventory.emplace_back(reinterpret_cast<IWeapon *>(new Uzi(device, soundEngine)));
  this->weaponsInInventory.emplace_back(reinterpret_cast<IWeapon *>(new Shotgun(device, soundEngine)));
  this->weaponsInInventory.emplace_back(reinterpret_cast<IWeapon *>(new Surrender(device, soundEngine)));
  this->weaponsInInventory.emplace_back(reinterpret_cast<IWeapon *>(new HolyHandGrenade(device, soundEngine)));
  this->weaponsInInventory.emplace_back(reinterpret_cast<IWeapon *>(new SkipGo(device, soundEngine)));
}

Inventory::~Inventory()
{

}

bool	Inventory::fireWithSelectedWeapon(size_t const &weaponSelectedInGui)
{
  return this->weaponsInInventory.at(weaponSelectedInGui)->fire();
}

void    Inventory::showSelectedWeapon(size_t const &weaponSelectedInGui,
				      const irr::core::vector3df &position, const irr::core::vector3df &rotation)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->showWeapon(position, rotation);
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

bool	Inventory::updateWeaponBullets(size_t const &weaponSelectedInGui,
				       std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  if (weaponSelectedInGui == 3)
    return this->weaponsInInventory.at(weaponSelectedInGui)->updateBullets(groundObjects);
  else
    return this->weaponsInInventory.at(weaponSelectedInGui)->updateBullets();
}

void	Inventory::deleteWeapon(size_t toDelete)
{
  this->weaponsInInventory.at(toDelete)->deleteWeapon();
}
