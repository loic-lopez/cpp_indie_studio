//
// HumanTeam.hpp for humanteam in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:50:07 2017 Stanislas Deneubourg
// Last update Sun Jun 18 16:47:50 2017 Stanislas Deneubourg
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
#include "Events/EventReceiver.hpp"
#include "Events/MenuButton.hpp"
#include "GameEngine/GameMap.hpp"

class	Team
{
protected:
  EventReceiver				&eventReceiver;
  std::vector<Worm>			teamPlayers;
  std::string				teamName;
  unsigned int				players;
  bool 					canFire;
  bool 					displayBullet;
  std::vector<irr::core::vector3df>	humanWormsRelativePos;

public:
  Team(unsigned int, unsigned int,
       std::vector<irr::core::vector3df>,
       std::string const &, bool, irr::IrrlichtDevice *device,
       irrklang::ISoundEngine *soundEngine, EventReceiver &eventReceiver, irr::gui::IGUIFont *teamFont);
  Team	&operator=(Team const &);
  ~Team();
  double		teamTimerRollback(unsigned int, std::time_t);
  void			teamMoveLeft(unsigned int, size_t selectedWeapon);
  void			teamMoveRight(unsigned int, size_t selectedWeapon);
  bool			teamFire(size_t, size_t selectedWeapon);
  void 			showWormWeapon(size_t, size_t);
  bool			updateTeamWormBullets(unsigned currentPlayer, size_t selectedWeapon,
					      std::vector<irr::scene::IMeshSceneNode *> groundObjects);
  void			teamResetAnimationSpeed(unsigned int);
  void 			poisonEffect();
  void 			teamGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects);
  void			teamGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects, size_t currentWeapon);
  void			teamLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
					  unsigned int, size_t);
  void			teamRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
					   unsigned int, size_t);
  void    		teamLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects, unsigned int player);
  void    		teamRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects, unsigned int player);
  bool 			playerIsHuman(unsigned int currentPlayer);
  void 			playTeamHuman(unsigned int currentPlayer);
  void 			playTeamBot(unsigned int currentPlayer, std::vector<irr::scene::IMeshSceneNode *> groundObjects,  std::vector<irr::core::vector3df> allWormsPos);
  bool 			playTeamHuman(unsigned int currentPlayer, size_t selectedWeapon,
				      InventoryButton const &lastWeaponSelected,
				      std::vector<irr::scene::IMeshSceneNode *> groundObjects);
  void 			teamJump(unsigned int, size_t);
  void 			teamJump(unsigned int);
  void 			deleteWormWeapon(size_t currentPlayer, size_t selectedWeapon);
  const unsigned int	getAliveTeamPlayers();
  irr::core::vector3df	getCurrentWormPosition(unsigned int currentPlayer);
  const bool 		&getWormIsDrowned(unsigned int currentPlayer);
  void 			setWormIsDrowned(unsigned int currentPlayer, bool isDrowned);
  std::string		const &getWormName(unsigned int) const;
  std::vector<Worm>	getWorm();
  void	                teamUpCollision(std::vector<irr::scene::IMeshSceneNode *>);
  void 			removeWormsInCurrentTeam();
  const	bool		&getCanFire() const;
};

#endif
