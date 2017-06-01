//
// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Thu Jun  1 13:49:26 2017 Stanislas Deneubourg
//

#include "Worms/Worm.hpp"

Worm::Worm(int nb, irr::core::vector3df vector_pos,
	   irr::scene::IAnimatedMeshSceneNode *worm_mesh,
	   irr::IrrlichtDevice *device, std::string worm_file)
{
  int	dir = rand() % 3;
  this->worm_name = "Player ";
  this->worm_name += std::to_string(nb);
  this->health_points = 100;
  this->damage_received = 0;
  this->damage_dealt = 0;
  this->worm_position = vector_pos;
  irr::scene::IAnimatedMesh* m = device->getSceneManager()->getMesh(worm_file.c_str());
  if (!m)
    return;
  irr::scene::IAnimatedMeshSceneNode* animworms = device->getSceneManager()->addAnimatedMeshSceneNode(m);
  animworms->setAnimationSpeed(30);
  worm_mesh = animworms;
  worm_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  worm_mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  if (dir == 0)
    {
      this->looking_direction = 'r';
      worm_mesh->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
    }
  else if (dir == 1)
    {
      this->looking_direction = 'l';
      worm_mesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
    }
  else
    {
      this->looking_direction = 'm';
      worm_mesh->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
    }
  worm_mesh->setPosition(vector_pos);
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

