//
// Shotgun.cpp for shotgun in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 08:05:48 2017 Stanislas Deneubourg
// Last update Wed Jun 14 09:58:38 2017 Stanislas Deneubourg
//

// TODO: ENLEVER LES PRINTS
#include <ctime>
#include <iostream>
#include "Worms/Shotgun.hpp"

Shotgun::Shotgun(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine)
{
  this->splash_damage_range = 0.5;
  this->chargerNumber = 4;
  this->weight = 0.1;
  this->damagePerBullet = 5;
  this->device = device;
  this->soundEngine = soundEngine;
}

Shotgun::~Shotgun()
{
}

bool	Shotgun::fire()
{
  if (this->chargerNumber > 0)
    {
      if (this->shotgunSceneNode != nullptr)
	{
	  irr::core::vector3df	position = this->shotgunSceneNode->getPosition();
	  irr::core::vector3df	rotation = this->shotgunSceneNode->getRotation();
	  this->soundEngine->play2D("ressources/sounds/Shotgun.wav");
	  for (size_t i = 0; i < SHOTGUN_BULLETS_PER_CHARGER; i++)
	    this->firedBullets.emplace_back(position, rotation, this->device, this->shotgunBox);
	  this->chargerNumber--;
	  std::cout << "FIRE SHOTGUN" << std::endl;
	  return (true);
	}
    }
  std::cout << "NO MORE " << std::endl;
  return (false);
}

void	Shotgun::showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation)
{
  this->shotgunSceneNode = this->device->getSceneManager()->addMeshSceneNode
	  (this->device->getSceneManager()->getMesh("ressources/weapons/Shotgun/Shotgun.obj"));
  this->shotgunSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->shotgunSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->setWeaponRotation(rotation);
  this->setWeaponPosition(position);
  this->shotgunSceneNode->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  this->shotgunBox = this->shotgunSceneNode->getBoundingBox();
}

void	Shotgun::deleteWeapon()
{
  this->shotgunSceneNode->getParent()->removeChild(this->shotgunSceneNode);
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
  this->shotgunSceneNode->setRotation(irr::core::vector3df(rotation.X, -rotation.Y, rotation.Z));
}

bool	Shotgun::updateBullets()
{
  size_t i = 0;
  std::vector<size_t>	toRemove;

  for (auto &firedBullet: this->firedBullets)
    {
      auto bulletPosition = firedBullet.bullet->getPosition();
      if (firedBullet.startBulletRotationY == 90)
	{
	  if (bulletPosition.X < firedBullet.startBulletX + SHOTGUN_BULLET_RANGE)
	    {
	      bulletPosition.X += SHOTGUN_BULLET_SPEED;
	      firedBullet.bullet->setPosition(bulletPosition);
	    }
	  else
	    toRemove.push_back(i);
	}
      else
	if (bulletPosition.X > firedBullet.startBulletX - SHOTGUN_BULLET_RANGE)
	  {
	    bulletPosition.X -= SHOTGUN_BULLET_SPEED;
	    firedBullet.bullet->setPosition(bulletPosition);
	  }
	else
	  toRemove.push_back(i);
      i++;
    }

  if (toRemove.size() == firedBullets.size() && !firedBullets.empty())
    {
      i = toRemove.size() - 1;
      for (; i > 0; i--)
	{
	  this->firedBullets.at(i).deleteBullet();
	  this->firedBullets.erase(this->firedBullets.begin() + i);
	}
      this->firedBullets.at(i).deleteBullet();
      this->firedBullets.erase(this->firedBullets.begin() + i);
      this->firedBullets.empty();
    }
  return !this->firedBullets.empty();
}

irr::core::vector3df const &Shotgun::getWeaponRotation() const
{
  return this->shotgunSceneNode->getRotation();
}

Shotgun::Bullet::Bullet(const irr::core::vector3df &position, const irr::core::vector3df &rotation,
			irr::IrrlichtDevice *device, irr::core::aabbox3d<irr::f32> const &uziBox)
{
  int 	randomPosY = std::rand() % 5;
  int 	randHB = std::rand() % 10;

  this->bullet = device->getSceneManager()->addMeshSceneNode
	  (device->getSceneManager()->getMesh("ressources/weapons/Bullet/bullet.obj"));
  this->bullet->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->bullet->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  this->bullet->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
  this->bullet->setRotation(rotation);
  this->startBulletX = position.X;
  if (randHB >= 5)
    this->bullet->setPosition(irr::core::vector3df(position.X,
						     position.Y + static_cast<irr::f32>(
									  uziBox.getExtent().getLength() / 5
									  + randomPosY / 10.0f),
						     position.Z));
  else
    this->bullet->setPosition(irr::core::vector3df(position.X,
						   (position.Y + uziBox.getExtent().getLength() / 5)
						   - randomPosY / 10.0f,
						   position.Z));
  this->startBulletRotationY = rotation.Y;
}

void	Shotgun::Bullet::deleteBullet()
{
  this->bullet->getParent()->removeChild(this->bullet);
}
