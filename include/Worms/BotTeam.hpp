//
// BotTeam.hpp for bot team in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 11:41:42 2017 Stanislas Deneubourg
// Last update Thu Jun  1 13:47:50 2017 Stanislas Deneubourg
//

#ifndef BOT_TEAM_HPP
#define BOT_TEAM_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include "Worms/Worm.hpp"

class	BotTeam
{
private:
  std::vector<Worm>			team_players;
  std::string				team_name;
  unsigned int				players;
  std::vector<irr::core::vector3df>	human_worms_relative_pos;
  
public:
  BotTeam(unsigned int, unsigned int, std::vector<irr::core::vector3df>,
	  irr::scene::IAnimatedMeshSceneNode *,
	  irr::IrrlichtDevice *, std::string);
  ~BotTeam();
};

#endif
