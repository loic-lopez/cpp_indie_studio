//
// HumanTeam.cpp for human team in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:51:11 2017 Stanislas Deneubourg
// Last update Wed Jun  7 16:39:12 2017 Stanislas Deneubourg
//

#include "Worms/Team.hpp"

Team::Team(unsigned int players_, unsigned int teamNb,
	   std::vector<irr::core::vector3df> vectorPos,
	   irr::IrrlichtDevice *device,
	   std::string wormFile, bool isBot)
{
  this->players = players_;
  this->teamName = "Humans ";
  this->teamName += teamNb;
  for (unsigned int i = 0; i < this->players; i++)
    this->teamPlayers.push_back(Worm(i, vectorPos.at(i), device, wormFile, isBot));
}

Team::~Team()
{
  for (int i = this->teamPlayers.size() != 0; i > 0; i = this->teamPlayers.size())
    this->teamPlayers.pop_back();
}

double	Team::turnOfThatTeam(unsigned int i, std::time_t turnStart)
{
  return (this->teamPlayers.at(i).turnOfThatWorm(turnStart));
}

void	Team::teamMoveLeft(unsigned int i, irr::IrrlichtDevice *device)
{
  this->teamPlayers.at(i).wormMoveLeft(device);
}

void	Team::teamMoveRight(unsigned int i, irr::IrrlichtDevice *device)
{
  this->teamPlayers.at(i).wormMoveRight(device);
}
