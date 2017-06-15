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
#include "Worms/Surrender.hpp"

class	Inventory
{
  private:
  std::vector<std::shared_ptr<IWeapon>>	weaponsInInventory;
  irr::IrrlichtDevice				*_device;

 public:
  Inventory(irr::IrrlichtDevice *device,
	    irrklang::ISoundEngine *soundEngine);
  ~Inventory();
  bool	fireWithSelectedWeapon(size_t const &weaponSelectedInGui);
  void   showSelectedWeapon(size_t const &weaponSelectedInGui, const irr::core::vector3df &position,
			     const irr::core::vector3df &rotation);
  void	setWeaponPositionToWormPosition(size_t const &weaponSelectedInGui,
					      const irr::core::vector3df &position);
  void	setWeaponRotationToWormPosition(size_t const &weaponSelectedInGui,
					      const irr::core::vector3df &rotation);
  bool	updateWeaponBullets(size_t const &weaponSelectedInGui);
  void	deleteWeapon(size_t toDelete);
};

#endif //CPP_INDIE_STUDIO_INVENTORY_HPP