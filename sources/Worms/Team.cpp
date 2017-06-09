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
    this->teamPlayers.emplace_back(Worm(i, vectorPos.at(i), device, wormFile, isBot));
}

Team::~Team()
{
}

double	Team::turnOfThatTeam(unsigned currentPlayer, std::time_t turnStart)
{
  return (this->teamPlayers.at(currentPlayer).turnOfThatWorm(turnStart));
}

void	Team::teamMoveLeft(unsigned currentPlayer, irr::IrrlichtDevice *device)
{
  this->teamPlayers.at(currentPlayer).wormMoveLeft(device);
}

void	Team::teamMoveRight(unsigned currentPlayer, irr::IrrlichtDevice *device)
{
  this->teamPlayers.at(currentPlayer).wormMoveRight(device);
}

void 	Team::teamFire(size_t currentPlayer)
{
  this->teamPlayers.at(currentPlayer).inventory.fireWithSelectedWeapon(0);
}
