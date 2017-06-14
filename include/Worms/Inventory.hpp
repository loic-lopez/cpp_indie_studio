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
#include "Events/EventReceiver.hpp"

class	Inventory
{
 public:
  enum class	weaponsId : uint16_t
  {
    UZI = 0,
    SHOTGUN = 1,
    GRENADE = 2
  };

 private:
  std::vector<std::shared_ptr<IWeapon>>	weaponsInInventory;
  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::gui::IGUIEnvironment			*_guienv;
  irr::gui::IGUISkin				*_skin;
  irr::gui::IGUITabControl			*tabctrl;
  irr::core::dimension2du		 	screenSize;
  irr::gui::IGUISpriteBank			*spriteBank;
  irr::core::dimension2d<irr::u32> 		cursorSize;
  EventReceiver 				&eventReceiver;

  weaponsId 					*id;

 public:
  Inventory(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
	    irrklang::ISoundEngine *soundEngine, EventReceiver &receiver);
  ~Inventory();
  bool	fireWithSelectedWeapon(size_t const &weaponSelectedInGui);
  void	showSelectedWeapon(size_t const &weaponSelectedInGui);
  void	setWeaponPositionToWormPosition(size_t const &weaponSelectedInGui,
					      const irr::core::vector3df &position);
  void	setWeaponRotationToWormPosition(size_t const &weaponSelectedInGui,
					      const irr::core::vector3df &rotation);
  void	launchInventory();
  bool	updateWeaponBullets(size_t const &weaponSelectedInGui);
};

#endif //CPP_INDIE_STUDIO_INVENTORY_HPP