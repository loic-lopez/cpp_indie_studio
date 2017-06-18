//
// HolyHandGrenade.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/HolyHandGrenade.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  ven. juin 16 10:35:53 2017 Loïc Lopez
// Last update Sun Jun 18 18:53:15 2017 Stanislas Deneubourg
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
  this->actualLeftSpeedX = -(this->maxSpeedX);
  this->actualLeftSpeedY = -(this->maxSpeedY);
  this->updateReverseConstraints = false;
  this->updateZeroConstraints = false;
  this->throwLeft = false;
  this->throwRight = false;
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
	  if (this->holyHandGrenadeSceneNode->getRotation().Y == 90.0f)
	    this->throwRight = true;
	  else
	    this->throwLeft = true;
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
  return true;
}

bool	HolyHandGrenade::updateBullets(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  irr::core::vector3df	grenadePos = this->holyHandGrenadeSceneNode->getPosition();
  int			collision = 0;
  irr::f32		collisionPos = 0;
  
  if (this->throwRight == true)
    {
      // SI ON LANCE VERS LA DROITE
      if (this->updateZeroConstraints == false)
	{
	  //COLLISION GAUCHE
	  
	  for (unsigned int i = 0; i < groundObjects.size(); i++)
	    {
	      if ((this->holyHandGrenadeSceneNode->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 1.5f)
		  && (this->holyHandGrenadeSceneNode->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 1.5f)
		  && (this->holyHandGrenadeSceneNode->getPosition().X <= groundObjects.at(i)->getPosition().X + 3.35f)
		  && (this->holyHandGrenadeSceneNode->getPosition().X >= groundObjects.at(i)->getPosition().X + 3.25f))
		{
		  collision = 1;
		  collisionPos = groundObjects.at(i)->getPosition().X + 3.4f;
		}
	    }
	  if (collision == 1)
	    {
	      this->holyHandGrenadeSceneNode->setPosition
		(irr::core::vector3d<irr::f32>(collisionPos,
					       this->holyHandGrenadeSceneNode->getPosition().Y,
					       this->holyHandGrenadeSceneNode->getPosition().Z));
	      
	    }
	  collision = 0;
	  collisionPos = 0;

	  //COLLISION DROITE
	  
	  for (unsigned int i = 0; i < groundObjects.size(); i++)
	    {
	      if ((this->holyHandGrenadeSceneNode->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 1.5f)
		  && (this->holyHandGrenadeSceneNode->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 1.5f)
		  && (this->holyHandGrenadeSceneNode->getPosition().X >= groundObjects.at(i)->getPosition().X - 3.35f)
		  && (this->holyHandGrenadeSceneNode->getPosition().X <= groundObjects.at(i)->getPosition().X - 3.25f))
		{
		  collision = 1;
		  collisionPos = groundObjects.at(i)->getPosition().X - 3.4f;
		}
	    }
	  if (collision == 1)
	    {
	      this->holyHandGrenadeSceneNode->setPosition
		(irr::core::vector3d<irr::f32>(collisionPos,
					       this->holyHandGrenadeSceneNode->getPosition().Y,
					       this->holyHandGrenadeSceneNode->getPosition().Z));
	    }
	  collision = 0;
	  collisionPos = 0;

	  //GRAVITE

	  for (unsigned int i = 0; i < groundObjects.size(); i++)
	    {
	      if ((this->holyHandGrenadeSceneNode->getPosition().Y >= groundObjects.at(i)->getPosition().Y + 1.0)
		  && (this->holyHandGrenadeSceneNode->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.8)
		  && (this->holyHandGrenadeSceneNode->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.3)
		  && (this->holyHandGrenadeSceneNode->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.3))
		collision = 1;
	    }
	  if (collision == 0)
	    {
	      this->holyHandGrenadeSceneNode->setPosition
		(irr::core::vector3d<irr::f32>(this->holyHandGrenadeSceneNode->getPosition().X,
					       this->holyHandGrenadeSceneNode->getPosition().Y - 0.3f,
					       this->holyHandGrenadeSceneNode->getPosition().Z));
	    }
	  collision = 0;
	  collisionPos = 0;
	  
	  //BALLISTIQUE
  
	  if (this->actualSpeedY > 0.0f && this->updateReverseConstraints == false)
	    {
	      grenadePos.X += this->actualSpeedX;
	      grenadePos.Y += this->actualSpeedY;
	      this->holyHandGrenadeSceneNode->setPosition(grenadePos);
	      this->actualSpeedX -= 0.001f;
	      this->actualSpeedY -= 0.001f;
	    }
	  if (this->actualSpeedY <= 0.0f && this->updateReverseConstraints == false)
	    {
	      this->actualSpeedY = 0.0f;
	      this->updateReverseConstraints = true;
	    }
	  if (this->actualSpeedY < this->maxSpeedY && this->updateReverseConstraints == true)
	    {
              grenadePos.X -= this->actualSpeedX;
              grenadePos.Y -= this->actualSpeedY;
              this->holyHandGrenadeSceneNode->setPosition(grenadePos);
              this->actualSpeedX -= 0.001f;
              this->actualSpeedY += 0.001f;
            }
          if (this->actualSpeedY >= this->maxSpeedY)
            {
              this->actualSpeedY = this->maxSpeedY;
	      this->actualSpeedX = this->maxSpeedX;
              this->updateZeroConstraints = true;
            }
	}
      else
	{
	  this->updateZeroConstraints = false;
	  this->updateReverseConstraints = false;
	  this->throwRight = false;
	  return false;
	}
    }
  else if (this->throwLeft == true)
    {
      // SI ON LANCE VERS LA GAUCHE
      if (this->updateZeroConstraints == false)
        {
	  //COLLISION GAUCHE

	  for (unsigned int i = 0; i < groundObjects.size(); i++)
            {
              if ((this->holyHandGrenadeSceneNode->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 0.7f)
                  && (this->holyHandGrenadeSceneNode->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.7f)
                  && (this->holyHandGrenadeSceneNode->getPosition().X <= groundObjects.at(i)->getPosition().X + 3.35f)
                  && (this->holyHandGrenadeSceneNode->getPosition().X >= groundObjects.at(i)->getPosition().X + 3.25f))
                {
                  collision = 1;
                  collisionPos = groundObjects.at(i)->getPosition().X + 3.4f;
                }
            }
          if (collision == 1)
            {
              this->holyHandGrenadeSceneNode->setPosition
                (irr::core::vector3d<irr::f32>(collisionPos,
                                               this->holyHandGrenadeSceneNode->getPosition().Y,
                                               this->holyHandGrenadeSceneNode->getPosition().Z));

            }
          collision = 0;
          collisionPos = 0;

	  //COLLISION DROITE

	  for (unsigned int i = 0; i < groundObjects.size(); i++)
            {
              if ((this->holyHandGrenadeSceneNode->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 0.7f)
                  && (this->holyHandGrenadeSceneNode->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.7f)
                  && (this->holyHandGrenadeSceneNode->getPosition().X >= groundObjects.at(i)->getPosition().X - 3.35f)
                  && (this->holyHandGrenadeSceneNode->getPosition().X <= groundObjects.at(i)->getPosition().X - 3.25f))
                {
                  collision = 1;
                  collisionPos = groundObjects.at(i)->getPosition().X - 3.4f;
                }
            }
          if (collision == 1)
            {
              this->holyHandGrenadeSceneNode->setPosition
                (irr::core::vector3d<irr::f32>(collisionPos,
                                               this->holyHandGrenadeSceneNode->getPosition().Y,
                                               this->holyHandGrenadeSceneNode->getPosition().Z));
            }
          collision = 0;
          collisionPos = 0;

	  //GRAVITE

	  for (unsigned int i = 0; i < groundObjects.size(); i++)
            {
              if ((this->holyHandGrenadeSceneNode->getPosition().Y >= groundObjects.at(i)->getPosition().Y + 1.0)
                  && (this->holyHandGrenadeSceneNode->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.8)
                  && (this->holyHandGrenadeSceneNode->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.3)
                  && (this->holyHandGrenadeSceneNode->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.3))
                collision = 1;
            }
          if (collision == 0)
            {
              this->holyHandGrenadeSceneNode->setPosition
                (irr::core::vector3d<irr::f32>(this->holyHandGrenadeSceneNode->getPosition().Y - 0.3f,
                                               this->holyHandGrenadeSceneNode->getPosition().Y,
                                               this->holyHandGrenadeSceneNode->getPosition().Z));
            }
          collision = 0;
          collisionPos = 0;

	  //BALLISTIQUE
	  
          if (this->actualSpeedY > 0.0f && this->updateReverseConstraints == false)
            {
              grenadePos.X += this->actualSpeedX;
              grenadePos.Y -= this->actualSpeedY;
              this->holyHandGrenadeSceneNode->setPosition(grenadePos);
              this->actualSpeedX -= 0.001f;
              this->actualSpeedY -= 0.001f;
            }
          if (this->actualSpeedY <= 0.0f && this->updateReverseConstraints == false)
            {
              this->actualSpeedY = 0.0f;
              this->updateReverseConstraints = true;
            }
          if (this->actualSpeedY < this->maxSpeedY && this->updateReverseConstraints == true)
            {
              grenadePos.X -= this->actualSpeedX;
              grenadePos.Y += this->actualSpeedY;
              this->holyHandGrenadeSceneNode->setPosition(grenadePos);
              this->actualSpeedX -= 0.001f;
              this->actualSpeedY -= 0.001f;
            }
          if (this->actualSpeedY >= this->maxSpeedY)
            {
              this->actualSpeedY = this->maxSpeedY;
              this->actualSpeedX = this->maxSpeedX;
              this->updateZeroConstraints = true;
            }
        }
      else
	{
	  this->updateZeroConstraints = false;
          this->updateReverseConstraints = false;
	  this->throwLeft = false;
	  return (false);
	}
    }
  return true;
}

irr::core::vector3df const &HolyHandGrenade::getWeaponRotation() const
{
  return this->holyHandGrenadeSceneNode->getRotation();
}
