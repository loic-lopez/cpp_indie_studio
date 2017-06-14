//
// Worm.hpp for worm in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:39:05 2017 Stanislas Deneubourg
// Last update Wed Jun 14 14:02:25 2017 Stanislas Deneubourg
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

 public:

  //  Weapon				weaponSelected;
  bool 					isPoisoned;
  Inventory             		inventory;
  Worm(int, irr::core::vector3df,
       irr::IrrlichtDevice *, std::string const &,
       bool, irr::video::IVideoDriver *, irrklang::ISoundEngine *soundEngine, EventReceiver &eventReceiver);
  ~Worm();
  int					getHealthPoints();
  void					setHealthPoints(int);
  unsigned int				getDamageDealt();
  unsigned int				getDamageReceived();
  double				turnOfThatWorm(std::time_t);
  void					wormResetAnimationSpeed();
  void					wormMoveLeft(size_t const &currentSelectedWeapon);
  void					wormMoveRight(size_t const &currentSelectedWeapon);
  const irr::core::vector3df 		&wormGetPosition() const;
  const irr::core::vector3df 		&wormGetRotation() const;
  void 					wormGravity(std::vector<irr::core::vector3d<irr::f32> *>);
};

#endif
