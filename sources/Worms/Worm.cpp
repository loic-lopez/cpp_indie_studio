//
// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Wed Jun  7 09:16:32 2017 Stanislas Deneubourg
//

#include "Worms/Worm.hpp"

Worm::Worm(int nb, irr::core::vector3df vector_pos,
	   irr::IrrlichtDevice *device, std::string worm_file,
	   bool	is_bot)
{
  int	dir = std::rand() % 3;
  this->worm_name = "Player ";
  this->worm_name += std::to_string(nb);
  this->health_points = 100;
  this->damage_received = 0;
  this->damage_dealt = 0;
  this->total_time = 0;
  this->pos_x = vector_pos.X;
  this->pos_y = vector_pos.Y;
  this->pos_z = vector_pos.Z;
  this->worm_type = static_cast<Worm::WormType>(is_bot);
  this->worm_position = vector_pos;
  this->m = device->getSceneManager()->getMesh(worm_file.c_str());
  if (!this->m)
    return;
  this->worm_mesh = device->getSceneManager()->addAnimatedMeshSceneNode(m);
  this->worm_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->worm_mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  if (dir == 0)
    this->worm_mesh->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
  else if (dir == 1)
    this->worm_mesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
  else
    this->worm_mesh->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
  this->looking_direction = static_cast<Worm::LookingDirection>(dir);
  this->worm_mesh->setFrameLoop(0, 15);
  this->worm_mesh->setAnimationSpeed(5);
  std::cout << this->worm_mesh->getEndFrame() << std::endl;
  this->worm_mesh->setPosition(irr::core::vector3df(this->pos_x, this->pos_y, this->pos_z));
}

Worm::~Worm()
{

}

void	Worm::setHealthPoints(int nb)
{
  this->health_points += nb;
}

void	Worm::setDamageDealt(int nb)
{
  this->damage_dealt += nb;
}

void	Worm::setDamageReceived(int nb)
{
  this->damage_received += nb;
}

int	Worm::getHealthPoints()
{
  return (this->health_points);
}

unsigned int Worm::getDamageDealt()
{
  return (this->damage_dealt);
}

unsigned int Worm::getDamageReceived()
{
  return (this->damage_received);
}

double	Worm::turn_of_that_worm(std::time_t turn_start)
{
  std::time_t	end = std::time(NULL);
  this->total_time = std::difftime(end, turn_start);
  return(this->total_time);
}

void	Worm::worm_move_left(irr::IrrlichtDevice *device)
{
  irr::f32		worm_movement_speed = 0.07f;

  this->pos_x -= worm_movement_speed;
  if (this->looking_direction == Worm::LookingDirection::RIGHT
      || this->looking_direction == Worm::LookingDirection::FRONT)
    {
      this->worm_mesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
      this->looking_direction = Worm::LookingDirection::LEFT;
    }
  this->worm_mesh->setPosition(irr::core::vector3df(this->pos_x, this->pos_y, this->pos_z));
}

void	Worm::worm_move_right(irr::IrrlichtDevice *device)
{
  irr::f32		worm_movement_speed = 0.07f;
  
  this->pos_x += worm_movement_speed;
  if (this->looking_direction == Worm::LookingDirection::LEFT
      || this->looking_direction == Worm::LookingDirection::FRONT)
    {
      this->worm_mesh->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
      this->looking_direction = Worm::LookingDirection::RIGHT;
    }
  this->worm_mesh->setPosition(irr::core::vector3df(this->pos_x, this->pos_y, this->pos_z));
}
