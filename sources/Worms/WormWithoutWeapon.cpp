/*
** WormWithoutWeapon.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/WormWithoutWeapon.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. juin 15 19:16:29 2017 Loïc Lopez
// Last update Sun Jun 18 12:14:23 2017 Stanislas Deneubourg
*/

#include "Worms/Worm.hpp"

void    Worm::wormLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  int		collision = 0;
  irr::f32      collisionPos = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 0.7f - 2.30f)
          && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.7f - 2.30f)
          && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 3.35f)
          && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X + 3.25f))
        {
          collision = 1;
          collisionPos = groundObjects.at(i)->getPosition().X + 3.4f;
        }
    }
  if (collision == 0)
    {
      this->collideLeft = false;
      this->wormMoveLeft();
    }
  else
    {
      this->wormPos.X = collisionPos;
      this->collideLeft = true;
      this->collideRight = false;
    }
}

void    Worm::wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  int		collision = 0;
  irr::f32      collisionPos = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 0.7f - 2.30f)
          && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.7f - 2.30f)
          && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 3.35f)
          && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X - 3.25f))
        {
          collision = 1;
          collisionPos = groundObjects.at(i)->getPosition().X - 3.4f;
        }
    }
  if (collision == 0)
    {
      this->collideRight = false;
      this->wormMoveRight();
    }
  else
    {
      this->wormPos.X = collisionPos;
      this->collideRight = true;
      this->collideLeft = false;
    }
}

void	Worm::wormMoveLeft()
{
  this->wormPos.X -= WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::RIGHT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, 90.0f, 0.0));
      this->lookingDirection = Worm::LookingDirection::LEFT;
    }
  this->wormMesh->setPosition(this->wormPos);
  this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
}

void	Worm::wormMoveRight()
{
  this->wormPos.X += WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::LEFT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
      this->lookingDirection = Worm::LookingDirection::RIGHT;
    }
  this->wormMesh->setPosition(this->wormPos);
  this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
}

void 	Worm::addInfos(irr::IrrlichtDevice *device)
{
  irr::core::stringw	name = this->wormName.c_str();
  name += L" : ";
  name += std::to_string(this->getHealthPoints()).c_str();
  irr::scene::ISceneManager	*smgr = device->getSceneManager();

  this->infos = smgr->addBillboardTextSceneNode(this->teamFont, name.c_str(), 0,
						irr::core::dimension2d<irr::f32>(3.5f, 1.25f), irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f),
						-1, irr::video::SColor(255, 255, 255, 255), irr::video::SColor(255, 255, 255, 255));
}

void 	Worm::wormGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  int collision = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 1.0)
	  && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y - 0.8)
	  && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.3)
	  && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.3))
	{
	  collision = 1;
	  this->isCollisioning = true;
	}
    }
  if (collision == 0)
    {
      this->wormPos.Y -= WORM_MOVEMENT_SPEED;
      this->wormMesh->setPosition(this->wormPos);
      this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
      this->isCollisioning = false;
    }
}

void    Worm::wormJump()
{
  if (this->lookingDirection == Worm::LookingDirection::RIGHT)
    {
      if (this->isJumping == false && this->isCollisioning == true)
        {
          for (irr::f32 i = jumpConstraintsY; i >= 0; i = i - 0.001f)
            {
              this->isJumping = true;
              this->wormPos.X += i;
              this->wormPos.Y += i;
              this->wormMesh->setPosition(this->wormPos);
            }
          this->isJumping = false;
        }
    }
  else if (this->lookingDirection == Worm::LookingDirection::LEFT)
    {
      if (this->isJumping == false && this->isCollisioning == true)
        {
          for (irr::f32 i = -jumpConstraintsY; i <= 0; i = i + 0.001f)
            {
              this->isJumping = true;
              this->wormPos.X += i;
              this->wormPos.Y -= i;
              this->wormMesh->setPosition(this->wormPos);
            }
          this->isJumping = false;
        }
    }
}
