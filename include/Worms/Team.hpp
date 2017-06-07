//
// HumanTeam.hpp for humanteam in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:50:07 2017 Stanislas Deneubourg
// Last update Wed Jun  7 16:30:03 2017 Stanislas Deneubourg
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
  
  std::vector<Worm>			teamPlayers;
  std::string				teamName;
  unsigned int				players;
  std::vector<irr::core::vector3df>	humanWormsRelativePos;
  
public:
  Team(unsigned int, unsigned int,
       std::vector<irr::core::vector3df>,
       irr::IrrlichtDevice *,
       std::string, bool);
  ~Team();
  double		turnOfThatTeam(unsigned int, std::time_t);
  void			teamMoveLeft(unsigned int, irr::IrrlichtDevice *);
  void			teamMoveRight(unsigned int, irr::IrrlichtDevice *);
};

#endif
