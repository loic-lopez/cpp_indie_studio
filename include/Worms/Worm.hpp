//
// Worm.hpp for worm in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:39:05 2017 Stanislas Deneubourg
// Last update Thu Jun  1 13:48:31 2017 Stanislas Deneubourg
//

#ifndef	WORM_HPP
#define	WORM_HPP

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include "Dependencies/Dependencies.hpp"

class	Worm
{  
private:
  std::string		worm_name;
  int			health_points;
  unsigned int		damage_received;
  unsigned int		damage_dealt;
  irr::core::vector3df	worm_position;
  char			looking_direction;
  
  void			setHealthPoints(int);
  void			setDamageDealt(int);
  void			setDamageReceived(int);
  
public:
  Worm(int, irr::core::vector3df,
       irr::scene::IAnimatedMeshSceneNode *,
       irr::IrrlichtDevice *, std::string);
  ~Worm();
  int			getHealthPoints();
  unsigned int		getDamageDealt();
  unsigned int		getDamageReceived();
};

#endif