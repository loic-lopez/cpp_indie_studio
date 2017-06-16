//
// HolyHandGrenade.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/HolyHandGrenade.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  ven. juin 16 10:35:53 2017 Loïc Lopez
// Last update ven. juin 16 10:35:53 2017 Loïc Lopez
//

#ifndef CPP_INDIE_STUDIO_HOLYHANDGRENADE_HPP
#define CPP_INDIE_STUDIO_HOLYHANDGRENADE_HPP

#include "Interface/IWeapon.hpp"

class	HolyHandGrenade : public IWeapon
{
 private:
  int				chargerNumber;
  irr::IrrlichtDevice		*device;
  irrklang::ISoundEngine	*soundEngine;
  irr::scene::ISceneNode	*holyHandGrenadeSceneNode;
  irr::core::aabbox3d<irr::f32>	holyHandGrenadeBox;
 public:
  explicit HolyHandGrenade(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine);
  ~HolyHandGrenade() override;

  bool	fire() 		override;
  void	showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation) 	override;
  void	deleteWeapon() 	override;
  void	setWeaponPosition(const irr::core::vector3df &position) override;
  void	setWeaponRotation(const irr::core::vector3df &rotation) override;
  bool	updateBullets() override;
};


#endif //CPP_INDIE_STUDIO_HOLYHANDGRENADE_HPP