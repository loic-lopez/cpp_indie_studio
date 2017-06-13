/*
** Uzi.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Uzi.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:34:24 2017 Loïc Lopez
// Last update Mon Jun 12 18:20:15 2017 Stanislas Deneubourg
*/

#ifndef CPP_INDIE_STUDIO_UZI_HPP
#define CPP_INDIE_STUDIO_UZI_HPP

#include <vector>
#include "Interface/IWeapon.hpp"

class	Uzi : public IWeapon
{
 private:
  class Bullet
  {
   private:
    irr::scene::ISceneNode *bullet;
   public:
    Bullet(const irr::core::vector3df &position,
	   const irr::core::vector3df &rotation, irr::IrrlichtDevice *device);
  };

  int				bulletsNumber;
  int 				damagePerBullet;
  float				weight;
  irr::IrrlichtDevice		*device;
  irr::scene::ISceneNode	*uziSceneNode;
  irr::core::aabbox3d<irr::f32>	uziBox;
  std::vector<Bullet>		firedBullets;

 public:
  explicit	Uzi(irr::IrrlichtDevice *device);
  ~Uzi() 		override;
  bool		fire()	override;
  void		showWeapon() override;
  void		deleteWeapon() override;
  void		setWeaponPosition(const irr::core::vector3df &position) override;
  void		setWeaponRotation(const irr::core::vector3df &rotation) override;
  void		displayBullets() override;
};

#endif //CPP_INDIE_STUDIO_UZI_HPP
