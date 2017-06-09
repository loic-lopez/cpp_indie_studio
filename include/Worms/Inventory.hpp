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

class	Inventory
{
 private:
  std::vector<std::shared_ptr<IWeapon>>	weaponsInInventory;
 public:
  Inventory();
  ~Inventory();
  void	fireWithSelectedWeapon(size_t const &weaponInGui);
};

#endif //CPP_INDIE_STUDIO_INVENTORY_HPP