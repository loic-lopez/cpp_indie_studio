//
// HumanTeam.cpp for human team in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:51:11 2017 Stanislas Deneubourg
// Last update Tue Jun 13 17:52:11 2017 Stanislas Deneubourg
//

#include "Worms/Team.hpp"

Team::Team(unsigned int players_, unsigned int teamNb,
	   std::vector<irr::core::vector3df> vectorPos,
	   irr::IrrlichtDevice *device,
	   std::string const &wormFile, bool isBot)
{
  this->players = players_;
  this->teamName = "Humans ";
  this->teamName += std::to_string(teamNb);
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

void	Team::teamMoveLeft(unsigned currentPlayer, size_t selectedWeapon)
{
  this->teamPlayers.at(currentPlayer).wormMoveLeft(selectedWeapon);
}

void	Team::teamMoveRight(unsigned currentPlayer, size_t selectedWeapon)
{
  this->teamPlayers.at(currentPlayer).wormMoveRight(selectedWeapon);
}

bool 	Team::teamFire(size_t currentPlayer)
{
  return this->teamPlayers.at(currentPlayer).inventory.fireWithSelectedWeapon(0);
}

void 	Team::showWormWeapon(size_t currentPlayer, size_t selectedWeapon)
{
  this->teamPlayers.at(currentPlayer).inventory.showSelectedWeapon(selectedWeapon);
  this->teamPlayers.at(currentPlayer).inventory.
	  setWeaponPositionToWormPosition(selectedWeapon, this->teamPlayers.at(currentPlayer).wormGetPosition());
  this->teamPlayers.at(currentPlayer).inventory.
	  setWeaponRotationToWormPosition(selectedWeapon, this->teamPlayers.at(currentPlayer).wormGetRotation());
}

bool	Team::updateTeamWormBullets(unsigned currentPlayer, size_t selectedWeapon)
{
  return this->teamPlayers.at(currentPlayer).inventory.updateWeaponBullets(selectedWeapon);
}
