//
// IWeapon.hpp for iweapon in /home/deneub_s/cpp_indie_studio/include
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 07:49:15 2017 Stanislas Deneubourg
// Last update Sun Jun 18 17:07:09 2017 Stanislas Deneubourg
//

#ifndef	IWEAPON_HPP
#define IWEAPON_HPP

#include <vector>
#include "Dependencies/Dependencies.hpp"

class	IWeapon
{
public:
  virtual	~IWeapon() {};
  virtual	bool	fire() = 0;
  virtual 	void	showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation) = 0;
  virtual 	void	deleteWeapon() = 0;
  virtual 	void	setWeaponPosition(const irr::core::vector3df &position) = 0;
  virtual 	void	setWeaponRotation(const irr::core::vector3df &rotation) = 0;
  virtual 	bool	updateBullets() = 0;
  virtual	bool	updateBullets(std::vector<irr::scene::IMeshSceneNode*>) = 0;
  virtual 	irr::core::vector3df	const &getWeaponRotation() const = 0;
};

#endif
