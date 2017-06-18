//
// HolyHandGrenade.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/HolyHandGrenade.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  ven. juin 16 10:35:53 2017 Loïc Lopez
// Last update Sun Jun 18 18:52:45 2017 Stanislas Deneubourg
//

#ifndef CPP_INDIE_STUDIO_HOLYHANDGRENADE_HPP
#define CPP_INDIE_STUDIO_HOLYHANDGRENADE_HPP

#include "Interface/IWeapon.hpp"

#define	HOLY_GRENADE_SPEED	2.0f
#define HOLY_GRENADE_RANGE	25.0f

class	HolyHandGrenade : public IWeapon
{
 private:
  int				chargerNumber;
  irr::IrrlichtDevice		*device;
  irrklang::ISoundEngine	*soundEngine;
  irr::scene::ISceneNode	*holyHandGrenadeSceneNode;
  irr::core::aabbox3d<irr::f32>	holyHandGrenadeBox;
  irr::f32 			startGrenadeX;
  irr::f32			actualSpeedX;
  irr::f32			maxSpeedX;
  irr::f32			actualSpeedY;
  irr::f32			maxSpeedY;
  irr::f32			actualLeftSpeedX;
  irr::f32			actualLeftSpeedY;
  bool				updateReverseConstraints;
  bool				updateZeroConstraints;
  bool				throwLeft;
  bool				throwRight;

 public:
  explicit HolyHandGrenade(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine);
  ~HolyHandGrenade() override;

  bool	fire() 		override;
  void	showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation) 	override;
  void	deleteWeapon() 	override;
  void	setWeaponPosition(const irr::core::vector3df &position) override;
  void	setWeaponRotation(const irr::core::vector3df &rotation) override;
  bool	updateBullets() override;
  bool	updateBullets(std::vector<irr::scene::IMeshSceneNode *>) override;
  irr::core::vector3df	const &getWeaponRotation() const override;
};


#endif //CPP_INDIE_STUDIO_HOLYHANDGRENADE_HPP
