//
// Worm.hpp for worm in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:39:05 2017 Stanislas Deneubourg
// Last update Tue Jun  6 15:38:13 2017 Stanislas Deneubourg
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
  
  std::string				worm_name;
  int					health_points;
  unsigned int				damage_received;
  unsigned int				damage_dealt;
  irr::core::vector3df			worm_position;
  WormType				worm_type;
  LookingDirection			looking_direction;
  bool					canPlay;
  double				total_time;
  irr::f32				pos_x;
  irr::f32				pos_y;
  irr::f32				pos_z;
  irr::scene::IAnimatedMesh		*m;
  irr::scene::IAnimatedMeshSceneNode	*worm_mesh;
  
  void			setHealthPoints(int);
  void			setDamageDealt(int);
  void			setDamageReceived(int);
  
public:
  Worm(int, irr::core::vector3df,
       irr::IrrlichtDevice *, std::string,
       bool);
  ~Worm();
  int			getHealthPoints();
  unsigned int		getDamageDealt();
  unsigned int		getDamageReceived();
  double		turn_of_that_worm(std::time_t);
  void			worm_move_left(irr::IrrlichtDevice *);
  void			worm_move_right(irr::IrrlichtDevice *);
};

#endif
