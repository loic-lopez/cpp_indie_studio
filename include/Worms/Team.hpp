//
// HumanTeam.hpp for humanteam in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:50:07 2017 Stanislas Deneubourg
// Last update Tue Jun  6 15:39:43 2017 Stanislas Deneubourg
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
  
  std::vector<Worm>			team_players;
  std::string				team_name;
  unsigned int				players;
  std::vector<irr::core::vector3df>	human_worms_relative_pos;
  
public:
  Team(unsigned int players_, unsigned int team_nb,
       std::vector<irr::core::vector3df> vector_pos,
       irr::IrrlichtDevice *device,
       std::string worm_file, bool is_bot);
  ~Team();
  double		turn_of_that_team(unsigned int, std::time_t);
  void			team_move_left(unsigned int, irr::IrrlichtDevice *);
  void			team_move_right(unsigned int, irr::IrrlichtDevice *);
};

#endif
