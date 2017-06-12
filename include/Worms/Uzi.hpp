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

#include "Interface/IWeapon.hpp"

class	Uzi : public IWeapon
{
 private:
  int				bulletsNumber;
  int 				damagePerBullet;
  float				weight;
  irr::IrrlichtDevice		*device;
  irr::scene::ISceneNode	*uziSceneNode;

 public:
  Uzi(irr::IrrlichtDevice *device);
  virtual 	~Uzi();
  virtual	bool	fire();
  virtual 	void	showWeapon();
  virtual 	void	deleteWeapon();
  virtual 	void	setWeaponPosition(const irr::core::vector3df &position);
  virtual 	void	setWeaponRotation(const irr::core::vector3df &rotation);
};

#endif //CPP_INDIE_STUDIO_UZI_HPP
