//
// IWeapon.hpp for iweapon in /home/deneub_s/cpp_indie_studio/include
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 07:49:15 2017 Stanislas Deneubourg
// Last update Thu Jun  1 07:53:21 2017 Stanislas Deneubourg
//

#ifndef	IWEAPON_HPP
#define IWEAPON_HPP

class	IWeapon
{
public:
  virtual	~IWeapon() {};
  virtual	bool	fire() = 0;
  virtual 	void	showWeapon() = 0;
};

#endif
