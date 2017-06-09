//
// Worm.hpp for worm in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:39:05 2017 Stanislas Deneubourg
// Last update Wed Jun  7 16:35:10 2017 Stanislas Deneubourg
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
#include "Dependencies/Dependencies.hpp"
#include "Worms/Inventory.hpp"

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
  irr::core::vector3df			wormPosition;
  WormType				wormType;
  LookingDirection			lookingDirection;
  bool					canPlay;
  double				totalTime;
  irr::f32				posX;
  irr::f32				posY;
  irr::f32				posZ;
  irr::scene::IAnimatedMesh		*m;
  irr::scene::IAnimatedMeshSceneNode	*wormMesh;
  WormStatus				wormStatus;
  //  Weapon				weaponSelected;
  
  void					setHealthPoints(int);
  void					setDamageDealt(int);
  void					setDamageReceived(int);
  
public:
  Inventory             		inventory;
  Worm(int, irr::core::vector3df,
       irr::IrrlichtDevice *, std::string const &,
       bool);
  ~Worm();
  int					getHealthPoints();
  unsigned int				getDamageDealt();
  unsigned int				getDamageReceived();
  double				turnOfThatWorm(std::time_t);
  void					wormMoveLeft(irr::IrrlichtDevice *);
  void					wormMoveRight(irr::IrrlichtDevice *);
};

#endif
