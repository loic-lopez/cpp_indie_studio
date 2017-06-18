/*
** SkipGo.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/SkipGo.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  dim. juin 18 11:44:16 2017 Loïc Lopez
** Last update dim. juin 18 11:44:16 2017 Loïc Lopez
*/

#include "Worms/SkipGo.hpp"

SkipGo::SkipGo(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine)
{
  this->device = device;
  this->soundEngine = soundEngine;
}

SkipGo::~SkipGo()
{

}

bool	SkipGo::fire()
{
  return false;
}

void	SkipGo::showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation)
{
  this->skipGoSceneNode = this->device->getSceneManager()->addMeshSceneNode
	  (this->device->getSceneManager()->getMesh("ressources/weapons/SkipGo/SkipGo.obj"));
  this->skipGoSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->skipGoSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->setWeaponRotation(rotation);
  this->setWeaponPosition(position);
  this->skipGoSceneNode->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  this->skipGoBox = this->skipGoSceneNode->getBoundingBox();
}

void	SkipGo::deleteWeapon()
{
  this->skipGoSceneNode->getParent()->removeChild(this->skipGoSceneNode);
}

void	SkipGo::setWeaponPosition(const irr::core::vector3df &position)
{
  irr::f32	yRotation = this->skipGoSceneNode->getRotation().Y;

  if (yRotation == 90.0f)
    this->skipGoSceneNode->setPosition(
	    irr::core::vector3df(position.X + this->skipGoBox.getExtent().getLength() / 6,
				 position.Y + this->skipGoBox.getExtent().getLength() / 2,
				 position.Z - this->skipGoBox.getExtent().getLength() / 6));
  else if (yRotation == -90.0f)
    this->skipGoSceneNode->setPosition(
	    irr::core::vector3df(position.X - this->skipGoBox.getExtent().getLength() / 6,
				 position.Y + this->skipGoBox.getExtent().getLength() / 2,
				 position.Z - this->skipGoBox.getExtent().getLength() / 6));
}

void	SkipGo::setWeaponRotation(const irr::core::vector3df &rotation)
{
  this->skipGoSceneNode->setRotation(irr::core::vector3df(rotation.X, -rotation.Y, rotation.Z));
}

bool	SkipGo::updateBullets()
{
  return false;
}

irr::core::vector3df const 	&SkipGo::getWeaponRotation() const
{
  return this->skipGoSceneNode->getRotation();
}
