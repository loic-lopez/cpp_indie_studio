//
// HolyHandGrenade.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/HolyHandGrenade.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  ven. juin 16 10:35:53 2017 Loïc Lopez
// Last update Sun Jun 18 16:28:04 2017 Stanislas Deneubourg
//

#include <iostream>
#include "Worms/HolyHandGrenade.hpp"

HolyHandGrenade::HolyHandGrenade(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine)
{
  this->device = device;
  this->soundEngine = soundEngine;
  this->chargerNumber = 1;
  this->maxSpeedX = 0.2f;
  this->actualSpeedX = this->maxSpeedX;
  this->maxSpeedY = 0.2f;
  this->actualSpeedY = this->maxSpeedY;
  this->updateReverseConstraints = false;
  this->updateZeroConstraints = false;
}

HolyHandGrenade::~HolyHandGrenade()
{

}

bool	HolyHandGrenade::fire()
{
  if (this->chargerNumber > 0)
    {
      if (this->holyHandGrenadeSceneNode != nullptr)
	{
	  this->chargerNumber--;
	  std::cout << "FIRE HOLY" << std::endl;
	  return (true);
	}
    }
  std::cout << "NO MORE " << std::endl;
  return (false);
}

void	HolyHandGrenade::showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation)
{
  this->holyHandGrenadeSceneNode = this->device->getSceneManager()->addMeshSceneNode
	  (this->device->getSceneManager()->getMesh("ressources/weapons/HolyHandGrenade/HolyHandGrenade.obj"));
  std::cout << this->holyHandGrenadeSceneNode << std::endl;
  this->holyHandGrenadeSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->holyHandGrenadeSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->setWeaponRotation(rotation);
  this->setWeaponPosition(position);
  this->holyHandGrenadeSceneNode->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  this->holyHandGrenadeBox = this->holyHandGrenadeSceneNode->getBoundingBox();
}

void	HolyHandGrenade::deleteWeapon()
{
  this->holyHandGrenadeSceneNode->getParent()->removeChild(this->holyHandGrenadeSceneNode);
}

void	HolyHandGrenade::setWeaponPosition(const irr::core::vector3df &position)
{
  irr::f32	yRotation = this->holyHandGrenadeSceneNode->getRotation().Y;

  if (yRotation == 90.0f)
    this->holyHandGrenadeSceneNode->setPosition(
	    irr::core::vector3df(position.X + this->holyHandGrenadeBox.getExtent().getLength() / 6,
				 position.Y + this->holyHandGrenadeBox.getExtent().getLength() / 2,
				 position.Z - this->holyHandGrenadeBox.getExtent().getLength() / 6));
  else if (yRotation == -90.0f)
    this->holyHandGrenadeSceneNode->setPosition(
	    irr::core::vector3df(position.X - this->holyHandGrenadeBox.getExtent().getLength() / 6,
				 position.Y + this->holyHandGrenadeBox.getExtent().getLength() / 2,
				 position.Z - this->holyHandGrenadeBox.getExtent().getLength() / 6));

  this->startGrenadeX = this->holyHandGrenadeSceneNode->getPosition().X;
}

void	HolyHandGrenade::setWeaponRotation(const irr::core::vector3df &rotation)
{
  this->holyHandGrenadeSceneNode->setRotation(irr::core::vector3df(rotation.X, -rotation.Y, rotation.Z));
}

bool	HolyHandGrenade::updateBullets()
{
  irr::core::vector3df	grenadePos = this->holyHandGrenadeSceneNode->getPosition();

  if (this->holyHandGrenadeSceneNode->getRotation().Y == 90.0f)
    {
      if (this->updateZeroConstraints == false)
	{
	  if (this->actualSpeedY > 0 && this->updateReverseConstraints == false)
	    {
	      grenadePos.X += this->actualSpeedX;
	      grenadePos.Y += this->actualSpeedY;
	      this->holyHandGrenadeSceneNode->setPosition(grenadePos);
	      this->actualSpeedX -= 0.001f;
	      this->actualSpeedY -= 0.001f;
	    }
	  if (this->actualSpeedY <= 0 && this->updateReverseConstraints == false)
	    {
	      this->actualSpeedY = 0;
	      this->updateReverseConstraints = true;
	    }
	  if (this->actualSpeedY < this->maxSpeedY && this->updateReverseConstraints == true)
	    {
              grenadePos.X -= this->actualSpeedX;
              grenadePos.Y -= this->actualSpeedY;
              this->holyHandGrenadeSceneNode->setPosition(grenadePos);
              this->actualSpeedX -= 0.001f;
              this->actualSpeedY -= 0.001f;
            }
          if (this->actualSpeedY >= this->maxSpeedY)
            {
              this->actualSpeedY = this->maxSpeedY;
	      this->actualSpeedX = this->maxSpeedX;
              this->update = true;
            }
	}
      else
	return false;
    }
  else
    {
      if (grenadePos.X > this->startGrenadeX - HOLY_GRENADE_RANGE)
	{
	  grenadePos.X -= HOLY_GRENADE_SPEED;
	  this->holyHandGrenadeSceneNode->setPosition(
		  irr::core::vector3df(grenadePos.X - this->holyHandGrenadeBox.getExtent().getLength() / 6,
				       grenadePos.Y + this->holyHandGrenadeBox.getExtent().getLength() / 2,
				       grenadePos.Z - this->holyHandGrenadeBox.getExtent().getLength() / 6));
	}
      else
	return (false);
    }
  return true;
}

irr::core::vector3df const &HolyHandGrenade::getWeaponRotation() const
{
  return this->holyHandGrenadeSceneNode->getRotation();
}
