//
// HumanTeam.cpp for human team in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:51:11 2017 Stanislas Deneubourg
// Last update Thu Jun 15 11:39:59 2017 Stanislas Deneubourg
//

#include "Worms/Team.hpp"

Team::Team(unsigned int players_, unsigned int teamNb,
	   std::vector<irr::core::vector3df> vectorPos,
	   std::string const &wormFile, bool isBot,
	   irr::IrrlichtDevice *device,
	   irrklang::ISoundEngine *soundEngine)
{
  this->players = players_;
  this->teamName = "Humans ";
  this->teamName += std::to_string(teamNb);
  for (unsigned int i = 0; i < this->players; i++)
    this->teamPlayers.emplace_back(Worm(i, vectorPos.at(i), device, wormFile, isBot, soundEngine));
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

bool 	Team::teamFire(size_t currentPlayer, size_t selectedWeapon)
{
  return this->teamPlayers.at(currentPlayer).inventory.fireWithSelectedWeapon(selectedWeapon);
}

void 	Team::showWormWeapon(size_t currentPlayer, size_t selectedWeapon)
{
  this->teamPlayers.at(currentPlayer).inventory.showSelectedWeapon(selectedWeapon, this->teamPlayers.at(currentPlayer).wormGetPosition(), this->teamPlayers.at(currentPlayer).wormGetRotation());
}

bool	Team::updateTeamWormBullets(unsigned currentPlayer, size_t selectedWeapon)
{
  return this->teamPlayers.at(currentPlayer).inventory.updateWeaponBullets(selectedWeapon);
}

void    Team::teamResetAnimationSpeed(unsigned int currentWormIdPlaying)
{
  this->teamPlayers.at(currentWormIdPlaying).wormResetAnimationSpeed();
}

void 	Team::poisonEffect()
{
  int	pv;
  for (unsigned int i = 0; i < this->teamPlayers.size(); i++)
    {
      if (this->teamPlayers[i].isPoisoned)
	{
	  pv = this->teamPlayers[i].getHealthPoints();
	  if (pv > 5)
	    this->teamPlayers[i].setHealthPoints(-5);
	  else
	    this->teamPlayers[i].setHealthPoints(-pv + 1);
	}
    }
}

void 	Team::teamGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  for (unsigned int i = 0; i < this->teamPlayers.size(); i++)
    {
      this->teamPlayers.at(i).wormGravity(groundObjects);
    }
}

void    Team::teamLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
				unsigned int player, size_t currentSelectedWeapon)
{
  this->teamPlayers.at(player).wormLeftCollision(groundObjects, currentSelectedWeapon);
}

void    Team::teamRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
				 unsigned int player, size_t currentSelectedWeapon)
{
  this->teamPlayers.at(player).wormRightCollision(groundObjects, currentSelectedWeapon);
}
