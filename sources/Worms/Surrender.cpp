//
// Surrender.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Surrender.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  mer. juin 14 13:40:06 2017 Loïc Lopez
// Last update Sun Jun 18 17:13:48 2017 Stanislas Deneubourg
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
      this->soundEngine->play2D("ressources/sounds/Surrender.wav");
      return (false);
    }
  return (false);
}

void	Surrender::showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation)
{
  this->surrenderSceneNode = this->device->getSceneManager()->addMeshSceneNode
	  (this->device->getSceneManager()->getMesh("ressources/weapons/Surrender/Surrender.obj"));
  this->surrenderSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->surrenderSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->surrenderBox = this->surrenderSceneNode->getBoundingBox();
  this->setWeaponRotation(rotation);
  this->setWeaponPosition(position);
}

void	Surrender::deleteWeapon()
{
  this->surrenderSceneNode->getParent()->removeChild(this->surrenderSceneNode);
}

void	Surrender::setWeaponPosition(const irr::core::vector3df &position)
{
  irr::f32	yRotation = this->surrenderSceneNode->getRotation().Y;

  if (yRotation == 0)
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

void	Surrender::setWeaponRotation(const irr::core::vector3df &rotation)
{
  if (rotation.Y != 90.0f)
    this->surrenderSceneNode->setRotation(irr::core::vector3df(rotation.X, rotation.Y - 90, rotation.Z));
  else
    this->surrenderSceneNode->setRotation(irr::core::vector3df(rotation.X, rotation.Y + 90, rotation.Z));
}

bool    Surrender::updateBullets(std::vector<irr::scene::IMeshSceneNode*> groundObjects)
{
  (void)groundObjects;
  return false;
}

bool	Surrender::updateBullets()
{
  return false;
}

irr::core::vector3df const &Surrender::getWeaponRotation() const
{
  return this->surrenderSceneNode->getRotation();
}
