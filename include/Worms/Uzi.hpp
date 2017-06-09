/*
** Uzi.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Uzi.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:34:24 2017 Loïc Lopez
** Last update ven. juin 09 14:34:24 2017 Loïc Lopez
*/

#ifndef CPP_INDIE_STUDIO_UZI_HPP
#define CPP_INDIE_STUDIO_UZI_HPP

#include "Interface/IWeapon.hpp"

class	Uzi : public IWeapon
{
 private:
  int	bulletsNumber;
  int 	damagePerBullet;

 public:
  Uzi();
  virtual 	~Uzi();
  virtual	bool	fire();
};

#endif //CPP_INDIE_STUDIO_UZI_HPP