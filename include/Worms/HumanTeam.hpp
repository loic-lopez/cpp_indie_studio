//
// HumanTeam.hpp for humanteam in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:50:07 2017 Stanislas Deneubourg
// Last update Thu Jun  1 13:47:59 2017 Stanislas Deneubourg
//

#ifndef HUMAN_TEAM_HPP
#define HUMAN_TEAM_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include "Worms/Worm.hpp"

class	HumanTeam
{
private:
  std::vector<Worm>			team_players;
  std::string				team_name;
  unsigned int				players;
  std::vector<irr::core::vector3df>	human_worms_relative_pos;
  
public:
  HumanTeam(unsigned int, unsigned int, std::vector<irr::core::vector3df>,
	    irr::scene::IAnimatedMeshSceneNode *,
	    irr::IrrlichtDevice *, std::string);
  ~HumanTeam();
};

#endif
