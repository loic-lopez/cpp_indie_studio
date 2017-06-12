//
// Shotgun.cpp for shotgun in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 08:05:48 2017 Stanislas Deneubourg
// Last update Thu Jun  1 08:06:48 2017 Stanislas Deneubourg
//

// TODO: ENLEVER LES PRINTS
#include <iostream>
#include "Worms/Shotgun.hpp"

Shotgun::Shotgun(irr::IrrlichtDevice *device)
{
  this->splash_damage_range = 0.5;
  this->chargerNumber = 4;
  this->weight = 0.1;
  this->damagePerBullet = 5;
  this->device = device;
}

Shotgun::~Shotgun()
{
}

bool	Shotgun::fire()
{
  if (this->chargerNumber > 0)
    {
      this->chargerNumber--;
      std::cout << "FIRE SHOTGUN" << std::endl;
      return (true);
    }
  else
    {
      std::cout << "NO MORE " << std::endl;
      return (false);
    }

}

void	Shotgun::showWeapon()
{
  this->shotgunSceneNode = this->device->getSceneManager()->addMeshSceneNode
	  (this->device->getSceneManager()->getMesh("ressources/weapons/Shotgun/Shotgun.obj"));
  this->shotgunSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->shotgunSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->shotgunSceneNode->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  this->shotgunBox = this->shotgunSceneNode->getBoundingBox();
}

void	Shotgun::deleteWeapon()
{

}

void	Shotgun::setWeaponPosition(const irr::core::vector3df &position)
{
  irr::f32	yRotation = this->shotgunSceneNode->getRotation().Y;

  if (yRotation == 90.0f)
    this->shotgunSceneNode->setPosition(
	    irr::core::vector3df(position.X + this->shotgunBox.getExtent().getLength() / 6,
				 position.Y + this->shotgunBox.getExtent().getLength() / 2,
				 position.Z - this->shotgunBox.getExtent().getLength() / 6));
  else if (yRotation == -90.0f)
      this->shotgunSceneNode->setPosition(
	      irr::core::vector3df(position.X - this->shotgunBox.getExtent().getLength() / 6,
				   position.Y + this->shotgunBox.getExtent().getLength() / 2,
				   position.Z - this->shotgunBox.getExtent().getLength() / 6));
}

void	Shotgun::setWeaponRotation(const irr::core::vector3df &rotation)
{
  this->shotgunSceneNode->setRotation(rotation);
}
