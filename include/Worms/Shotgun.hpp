//
// Shotgun.hpp for shotgun in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 07:54:52 2017 Stanislas Deneubourg
// Last update Thu Jun  1 08:07:02 2017 Stanislas Deneubourg
//

#ifndef	SHOTGUN_HPP
#define	SHOTGUN_HPP

#include "Interface/IWeapon.hpp"

class	Shotgun : public IWeapon
{
private:
  float			splash_damage_range;
  float			weight;
  int 			damagePerBullet;
  int			chargerNumber;
  irr::IrrlichtDevice	*device;
  irr::scene::ISceneNode	*shotgunSceneNode;
  
public:
  Shotgun(irr::IrrlichtDevice *device);
  virtual ~Shotgun();

  virtual	bool	fire();
  virtual 	void	showWeapon();
  virtual 	void	deleteWeapon();
  virtual 	void	setWeaponPosition(const irr::core::vector3df &position);
  virtual 	void	setWeaponRotation(const irr::core::vector3df &rotation);
};

#endif
