/*
** Uzi.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Uzi.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:45:54 2017 Loïc Lopez
// Last update Tue Jun 13 17:48:25 2017 Stanislas Deneubourg
*/

// TODO: ENLEVER LES PRINTS
#include <iostream>
#include "Worms/Uzi.hpp"

Uzi::Uzi(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine)
{
  this->bulletsNumber = 30;
  this->device = device;
  this->damagePerBullet = 5;
  this->soundEngine = soundEngine;
}

Uzi::~Uzi()
{

}

bool	Uzi::fire()
{
  if (this->bulletsNumber > 0)
    {
      this->firedBullets.emplace_back(this->uziSceneNode->getPosition(),
				      this->uziSceneNode->getRotation(), this->device, this->uziBox);
      this->soundEngine->play2D("ressources/sounds/Uzi.wav");
      std::cout << "FIRE WITH UZI" << std::endl;
      this->bulletsNumber--;
      return (true);
    }
  std::cout << "NO MORE BULLETS IN UZI" << std::endl;
  return (false);
}

void	Uzi::showWeapon()
{
  this->uziSceneNode = this->device->getSceneManager()->addMeshSceneNode
    (this->device->getSceneManager()->getMesh("ressources/weapons/Uzi/Uzi.obj"));
  this->uziSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  this->uziSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
  this->uziSceneNode->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  this->uziBox = this->uziSceneNode->getBoundingBox();
}

void	Uzi::deleteWeapon()
{
  this->uziSceneNode->getParent()->removeChild(this->uziSceneNode);
}

void 	Uzi::setWeaponPosition(const irr::core::vector3df &position)
{
  irr::f32	yRotation = this->uziSceneNode->getRotation().Y;

  if (yRotation == 90.0f)
    this->uziSceneNode->setPosition(
	    irr::core::vector3df(position.X + this->uziBox.getExtent().getLength() / 6,
				 position.Y + this->uziBox.getExtent().getLength() / 2,
				 position.Z - this->uziBox.getExtent().getLength() / 6));
  else if (yRotation == -90.0f)
    this->uziSceneNode->setPosition(
	    irr::core::vector3df(position.X - this->uziBox.getExtent().getLength() / 6,
				 position.Y + this->uziBox.getExtent().getLength() / 2,
				 position.Z - this->uziBox.getExtent().getLength() / 6));

}

void 	Uzi::setWeaponRotation(const irr::core::vector3df &rotation)
{
  this->uziSceneNode->setRotation(irr::core::vector3df(rotation.X, -rotation.Y, rotation.Z));
}

bool	Uzi::updateBullets()
{
  size_t i = 0;
  std::vector<size_t>	toRemove;

  for (auto &firedBullet: this->firedBullets)
    {
      auto bulletPosition = firedBullet.bullet->getPosition();
      if (firedBullet.startBulletRotationY == 90)
	{
	  if (bulletPosition.X < firedBullet.startBulletX + UZI_BULLET_RANGE && firedBullet.startBulletX -
										UZI_BULLET_RANGE > bulletPosition.X)
	    {
	      bulletPosition.X += UZI_BULLET_SPEED;
	      firedBullet.bullet->setPosition(bulletPosition);
	    }
	  else
	    toRemove.push_back(i);
	}
      else
	if (bulletPosition.X > firedBullet.startBulletX - UZI_BULLET_RANGE)
	  {
	    bulletPosition.X -= UZI_BULLET_SPEED;
	    firedBullet.bullet->setPosition(bulletPosition);
	  }
	else
	  toRemove.push_back(i);
      i++;
    }

  if (!toRemove.empty())
    for (auto &bulletToRemove: toRemove)
      {
	this->firedBullets.at(bulletToRemove).deleteBullet();
	this->firedBullets.erase(this->firedBullets.begin() + bulletToRemove);
      }
  return !this->firedBullets.empty();
}


Uzi::Bullet::Bullet(const irr::core::vector3df &position,
		    const irr::core::vector3df &rotation,
		    irr::IrrlichtDevice *device, irr::core::aabbox3d<irr::f32> const &uziBox)
{
  this->bullet = device->getSceneManager()->addMeshSceneNode
	  (device->getSceneManager()->getMesh("ressources/weapons/Bullet/bullet.obj"));
  this->bullet->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->bullet->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->bullet->setScale(irr::core::vector3df(0.25, 0.25, 0.25));
  this->bullet->setRotation(rotation);
  this->startBulletX = position.X;
  this->bullet->setPosition(irr::core::vector3df(position.X,
						 position.Y + uziBox.getExtent().getLength() / 5,
						 position.Z));
  this->startBulletRotationY = rotation.Y;
}

void	Uzi::Bullet::deleteBullet()
{
  this->bullet->getParent()->removeChild(this->bullet);
}
