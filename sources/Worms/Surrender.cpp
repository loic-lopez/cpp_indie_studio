//
// Surrender.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Surrender.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  mer. juin 14 13:40:06 2017 Loïc Lopez
// Last update mer. juin 14 13:40:06 2017 Loïc Lopez
//

#include "Worms/Surrender.hpp"

Surrender::Surrender(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine)
{
  this->device = device;
  this->soundEngine = soundEngine;
  this->fired = false;
}

Surrender::~Surrender()
{

}

bool	Surrender::fire()
{
  if (!this->fired)
    {
      this->fired = true;
      return (true);
    }
  return (false);
}

void	Surrender::showWeapon()
{
  this->surrenderSceneNode = this->device->getSceneManager()->addMeshSceneNode
	  (this->device->getSceneManager()->getMesh("ressources/weapons/Surrender/Surrender.obj"));
  this->surrenderSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->surrenderSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->surrenderBox = this->surrenderSceneNode->getBoundingBox();
}

void	Surrender::deleteWeapon()
{
  this->surrenderSceneNode->getParent()->removeChild(this->surrenderSceneNode);
}

void	Surrender::setWeaponPosition(const irr::core::vector3df &position)
{
  irr::f32	yRotation = this->surrenderSceneNode->getRotation().Y;

  if (yRotation == 180)
    this->surrenderSceneNode->setPosition(
	    irr::core::vector3df(position.X + this->surrenderBox.getExtent().getLength() / 6,
				 position.Y + this->surrenderBox.getExtent().getLength() / 2,
				 position.Z - this->surrenderBox.getExtent().getLength() / 5));
  else
      this->surrenderSceneNode->setPosition(
	      irr::core::vector3df(position.X - this->surrenderBox.getExtent().getLength() / 6,
				   position.Y + this->surrenderBox.getExtent().getLength() / 2,
				   position.Z - this->surrenderBox.getExtent().getLength() / 5));
}

#include <iostream>

void	Surrender::setWeaponRotation(const irr::core::vector3df &rotation)
{
  /*
  if (rotation.Y == 90.0f)
    this->surrenderSceneNode->setRotation(irr::core::vector3df(rotation.X, (rotation.Y - 90), rotation.Z));
  else
*/
      this->surrenderSceneNode->setRotation(irr::core::vector3df(rotation.X, rotation.Y - 90, rotation.Z));

}

bool	Surrender::updateBullets()
{
  return false;
}
