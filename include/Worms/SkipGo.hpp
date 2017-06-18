/*
** SkipGo.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/SkipGo.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  dim. juin 18 11:52:27 2017 Loïc Lopez
** Last update dim. juin 18 11:52:27 2017 Loïc Lopez
*/

#ifndef SKIP_GO_HPP
# define SKIP_GO_HPP

#include "Interface/IWeapon.hpp"

class	SkipGo : public IWeapon
{
 private:
  irr::IrrlichtDevice 		*device;
  irrklang::ISoundEngine 	*soundEngine;
  irr::scene::ISceneNode	*skipGoSceneNode;
  irr::core::aabbox3d<irr::f32> skipGoBox;

 public:
  SkipGo(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine);
  ~SkipGo() override;
  bool		fire()	override;
  void		showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation) override;
  void		deleteWeapon() override;
  void		setWeaponPosition(const irr::core::vector3df &position) override;
  void		setWeaponRotation(const irr::core::vector3df &rotation) override;
  bool		updateBullets() override;
  irr::core::vector3df	const &getWeaponRotation() const override;
};

#endif