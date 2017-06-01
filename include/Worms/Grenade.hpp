//
// Grenade.hpp for grenade in /home/deneub_s/cpp_indie_studio/include
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 07:50:34 2017 Stanislas Deneubourg
// Last update Thu Jun  1 08:06:35 2017 Stanislas Deneubourg
//

#ifndef	GRENADE_HPP
#define	GRENADE_HPP

#include "Interface/IWeapon.hpp"

class	Grenade : public IWeapon
{
private:
  float		splash_damage_range;
  int		max_damage;
  float		weight;
  
public:
  Grenade();
  virtual ~Grenade();
};

#endif
