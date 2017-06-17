//
// Surrender.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Surrender.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  mer. juin 14 13:40:06 2017 Loïc Lopez
// Last update mer. juin 14 13:40:06 2017 Loïc Lopez
//

#ifndef CPP_INDIE_STUDIO_SURRENDER_HPP
#define CPP_INDIE_STUDIO_SURRENDER_HPP

#include "Interface/IWeapon.hpp"

class Surrender : public IWeapon
{
 private:
  irr::IrrlichtDevice	*device;
  irr::scene::ISceneNode	*surrenderSceneNode;
  irr::core::aabbox3d<irr::f32>	surrenderBox;
  irrklang::ISoundEngine	*soundEngine;
  bool 				fired;

 public:
  explicit Surrender(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine);
  ~Surrender() override;

  bool	fire() 		override;
  void	showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation) 	override;
  void	deleteWeapon() 	override;
  void	setWeaponPosition(const irr::core::vector3df &position) override;
  void	setWeaponRotation(const irr::core::vector3df &rotation) override;
  bool	updateBullets() override;
  irr::core::vector3df	const &getWeaponRotation() const override;
};


#endif //CPP_INDIE_STUDIO_SURRENDER_HPP