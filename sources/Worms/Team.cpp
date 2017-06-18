//
// HumanTeam.cpp for human team in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:51:11 2017 Stanislas Deneubourg
// Last update Sun Jun 18 12:13:08 2017 Stanislas Deneubourg
//

#include "Worms/Team.hpp"

Team::Team(unsigned int players_, unsigned int teamNb,
	   std::vector<irr::core::vector3df> vectorPos,
	   std::string const &wormFile, bool isBot,
	   irr::IrrlichtDevice *device,
	   irrklang::ISoundEngine *soundEngine, EventReceiver  &eventReceiver, irr::gui::IGUIFont *teamFont) : eventReceiver(eventReceiver)
{
  this->players = players_;
  this->teamName = "Humans ";
  this->teamName += std::to_string(teamNb);
  for (unsigned int i = 0; i < this->players; i++)
    this->teamPlayers.emplace_back(Worm(i, vectorPos.at(i), device, wormFile, isBot, soundEngine, teamFont));
  this->canFire = true;
  this->displayBullet = false;
}

Team::~Team()
{
}

double	Team::teamTimerRollback(unsigned currentPlayer, std::time_t turnStart)
{
  if (!this->canFire)
    return (5);
  else
    return (this->teamPlayers.at(currentPlayer).wormTimerRollback(turnStart));
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
  this->teamPlayers.at(currentPlayer).inventory.showSelectedWeapon(selectedWeapon,
								   this->teamPlayers.at(currentPlayer).wormGetPosition(),
								   this->teamPlayers.at(currentPlayer).wormGetRotation());
}

void 	Team::deleteWormWeapon(size_t currentPlayer, size_t selectedWeapon)
{
  this->teamPlayers.at(currentPlayer).inventory.deleteWeapon(selectedWeapon);
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

void 	Team::teamGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects, size_t currentWeapon)
{
  for (unsigned int i = 0; i < this->teamPlayers.size(); i++)
    {
      this->teamPlayers.at(i).wormGravity(groundObjects, currentWeapon);
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

void    Team::teamLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
				unsigned int player)
{
  this->teamPlayers.at(player).wormLeftCollision(groundObjects);
}

void    Team::teamRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
				 unsigned int player)
{
  this->teamPlayers.at(player).wormRightCollision(groundObjects);
}

void    Team::teamJump(unsigned int player, size_t currentSelectedWeapon)
{
  this->teamPlayers.at(player).wormJump(currentSelectedWeapon);
}

void    Team::teamJump(unsigned int player)
{
  this->teamPlayers.at(player).wormJump();
}

bool	Team::playerIsHuman(unsigned int currentPlayer)
{
  return this->teamPlayers.at(currentPlayer).getWormType();
}

void	Team::playTeamHuman(unsigned int currentPlayer)
{
  if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_Q))
    this->teamResetAnimationSpeed(currentPlayer);
  if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_D))
    this->teamResetAnimationSpeed(currentPlayer);
}

void	Team::playTeamBot(unsigned int currentPlayer, std::vector<irr::scene::IMeshSceneNode *> groundObjects, std::vector<irr::core::vector3df> allWormsPos)
{
  this->teamPlayers.at(currentPlayer).playWormBot(groundObjects, allWormsPos);
}

bool	Team::playTeamHuman(unsigned int currentPlayer, size_t selectedWeapon, InventoryButton const &lastWeaponSelected)
{
  if (selectedWeapon == InventoryButton::UZI - 20)
    {
      if (this->eventReceiver.IsKeyDown(irr::KEY_SPACE))
	{
	  canFire = this->teamFire(currentPlayer, selectedWeapon);
	  displayBullet = true;
	}
    }
  else
    {
      if (this->eventReceiver.IsKeyUp(irr::KEY_SPACE))
	{
	  canFire = this->teamFire(currentPlayer, selectedWeapon);
	  if (!canFire)

	  if (selectedWeapon == InventoryButton::SURRENDER - 20)
	    return true;
	  displayBullet = true;
	}
    }
  if (displayBullet && lastWeaponSelected != InventoryButton::IN_STAND_BY)
    displayBullet = this->updateTeamWormBullets(currentPlayer, selectedWeapon);
  if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_Q))
    this->teamResetAnimationSpeed(currentPlayer);
  if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_D))
    this->teamResetAnimationSpeed(currentPlayer);
  return false;
}

const unsigned int	Team::getAliveTeamPlayers()
{
  return (this->teamPlayers.size());
}

irr::core::vector3df	Team::getCurrentWormPosition(unsigned int currentPlayer)
{
  return this->teamPlayers.at(currentPlayer).wormGetPosition();
}

void 	Team::setWormIsDrowned(unsigned int currentPlayer, bool isDrowned)
{
  this->teamPlayers.at(currentPlayer).isDrowned = isDrowned;
}

const bool &Team::getWormIsDrowned(unsigned int currentPlayer)
{
  return this->teamPlayers.at(currentPlayer).isDrowned;
}

std::string	const &Team::getWormName(unsigned int currentPlayer) const
{
  return (this->teamPlayers.at(currentPlayer).getWormName());
}

std::vector<Worm> Team::getWorm()
{
  return (this->teamPlayers);
}

Team	&Team::operator=(Team const &team)
{
  if (this != &team)
    {
      this->teamPlayers = team.teamPlayers;
      this->teamName = team.teamName;
      this->players = team.players;
      this->canFire = team.canFire;
      this->displayBullet = team.displayBullet;
      this->humanWormsRelativePos = team.humanWormsRelativePos;
    }
  return (*this);
}

void    Team::teamUpCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  for (unsigned int i = 0; i < this->teamPlayers.size(); i++)
    {
      this->teamPlayers.at(i).wormUpCollision(groundObjects);
    }
}

void	Team::removeWormsInCurrentTeam()
{
  for (size_t len = 0; len < this->teamPlayers.size(); len++)
    {
      this->teamPlayers.at(len).removeMeshSceneNode();
    }
}
