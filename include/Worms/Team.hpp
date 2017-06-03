//
// HumanTeam.hpp for humanteam in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:50:07 2017 Stanislas Deneubourg
// Last update Fri Jun  2 18:29:30 2017 Stanislas Deneubourg
//

#ifndef TEAM_HPP
#define TEAM_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "Worms/Worm.hpp"

class	Team
{
private:
  enum class	TeamType : uint8_t
    {
      HUMAN_TEAM	=	0,
      BOT_TEAM		=	1
    };
  
  std::vector<Worm>			team_players;
  std::string				team_name;
  unsigned int				players;
  std::vector<irr::core::vector3df>	human_worms_relative_pos;
  TeamType				team_type;
  
public:
  Team(unsigned int players_, unsigned int team_nb,
       std::vector<irr::core::vector3df> vector_pos,
       irr::scene::IAnimatedMeshSceneNode *worm_mesh,
       irr::IrrlichtDevice *device,
       std::string worm_file, bool is_bot);
  ~Team();
};

#endif
