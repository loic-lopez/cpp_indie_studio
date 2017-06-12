/*
** Inventory.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Inventory.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:13:50 2017 Loïc Lopez
** Last update ven. juin 09 14:13:50 2017 Loïc Lopez
*/

#ifndef CPP_INDIE_STUDIO_INVENTORY_HPP
#define CPP_INDIE_STUDIO_INVENTORY_HPP

#include <vector>
#include <memory>
#include "Worms/Uzi.hpp"
#include "Worms/Shotgun.hpp"

class	Inventory
{
 private:
  std::vector<std::shared_ptr<IWeapon>>	weaponsInInventory;
 public:
  Inventory(irr::IrrlichtDevice *device);
  ~Inventory();
  void	fireWithSelectedWeapon(size_t const &weaponInGui);
  void	showSelectedWeapon(size_t const &weaponSelectedInGui);
};

#endif //CPP_INDIE_STUDIO_INVENTORY_HPP