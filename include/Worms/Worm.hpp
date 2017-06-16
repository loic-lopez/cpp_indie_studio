//
// Worm.hpp for worm in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:39:05 2017 Stanislas Deneubourg
// Last update Fri Jun 16 16:36:38 2017 Stanislas Deneubourg
//

#ifndef	WORM_HPP
#define	WORM_HPP

#include <string>
#include <cstdint>
#include <ctime>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>
#include "Dependencies/Dependencies.hpp"
#include "Worms/Inventory.hpp"
#include "GameEngine/GameMap.hpp"

#define	WORM_MOVEMENT_SPEED	0.1f

class	Worm
{  
private:
  enum class    WormType : uint8_t
    {
      HUMAN_WORM        =       0,
      BOT_WORM          =       1
    };

  enum class	LookingDirection : uint8_t
    {
      RIGHT		=	0,
      LEFT		=	1,
      FRONT		=	2
    };

  enum class	WormStatus : uint8_t
    {
      WALKING		=	0,
      IN_INVENTORY	=	1,
      HOLDING_WEAPON	=	2,
      USED_WEAPON	=	3
    };
  
  std::string				wormName;
  int					healthPoints;
  unsigned int				damageReceived;
  unsigned int				damageDealt;
  WormType				wormType;
  LookingDirection			lookingDirection;
  bool					canPlay;
  double				totalTime;
  irr::core::vector3df			wormPos;
  irr::scene::IAnimatedMesh		*m;
  irr::scene::IAnimatedMeshSceneNode	*wormMesh;
  WormStatus				wormStatus;
  void					setDamageDealt(int);
  void					setDamageReceived(int);
  irr::core::vector3d<irr::f32>		*edge;
  irr::core::aabbox3d<irr::f32>		boundingBox;
  bool					collideLeft;
  bool					collideRight;
  irr::scene::IBillboardTextSceneNode	*infos;
  irr::f32				jumpConstraintsY;
  irr::f32				jumpConstraintsX;
  bool					isJumping;
  bool					isCollisioning;

 public:
  bool 					isDrowned;
  bool 					isPoisoned;
  Inventory             		inventory;
  Worm(int, irr::core::vector3df,
       irr::IrrlichtDevice *, std::string const &,
       bool, irrklang::ISoundEngine *soundEngine);
  ~Worm();
  int					getHealthPoints() const;
  void					setHealthPoints(int);
  unsigned int				getDamageDealt() const;
  unsigned int				getDamageReceived() const;
  std::string	const 			&getWormName() const;
  double				wormTimerRollback(std::time_t);
  void					wormResetAnimationSpeed();
  void					wormMoveLeft(size_t const &currentSelectedWeapon);
  void					wormMoveRight(size_t const &currentSelectedWeapon);
  void					wormMoveLeft();
  void					wormMoveRight();
  const irr::core::vector3df 		&wormGetPosition() const;
  const irr::core::vector3df 		&wormGetRotation() const;
  void 					wormGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects);
  void					wormGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects, size_t currentSelectedWeapon);
  void					wormLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
							  size_t);
  void					wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
							   size_t);
  void					wormLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects);
  void					wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects);
  bool const 				&getWormType() const;
  void					playWormBot(std::vector<irr::scene::IMeshSceneNode *> groundObjects, std::vector<irr::core::vector3df> allWormsPos);
  void 					addInfos(irr::IrrlichtDevice *);
  void					wormJump(size_t);
  void					wormJump();

};

#endif
