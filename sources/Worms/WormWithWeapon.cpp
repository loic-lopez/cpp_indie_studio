/*
** WormWithWeapon.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/WormWithWeapon.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. juin 15 19:15:02 2017 Loïc Lopez
// Last update Sun Jun 18 16:27:36 2017 Stanislas Deneubourg
*/

#include "Worms/Worm.hpp"

void	Worm::wormMoveLeft(size_t const &currentSelectedWeapon)
{
  this->wormPos.X -= WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::RIGHT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, 90.0f, 0.0));
      this->lookingDirection = Worm::LookingDirection::LEFT;
      this->inventory.setWeaponRotationToWormPosition(currentSelectedWeapon, this->wormMesh->getRotation());
    }
  this->wormMesh->setPosition(this->wormPos);
  this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
  this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
}

void	Worm::wormMoveRight(size_t const &currentSelectedWeapon)
{
  this->wormPos.X += WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::LEFT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0f, 0.0));
      this->lookingDirection = Worm::LookingDirection::RIGHT;
      this->inventory.setWeaponRotationToWormPosition(currentSelectedWeapon, this->wormMesh->getRotation());
    }
  this->wormMesh->setPosition(this->wormPos);
  this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
  this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
}

void    Worm::wormLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
                                size_t currentSelectedWeapon)
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
      this->wormMoveLeft(currentSelectedWeapon);
    }
  else
    {
      this->wormPos.X = collisionPos;
      this->collideLeft = true;
      this->collideRight = false;
    }
}

void    Worm::wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
                                 size_t currentSelectedWeapon)
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
      this->wormMoveRight(currentSelectedWeapon);
    }
  else
    {
      this->wormPos.X = collisionPos;
      this->collideRight = true;
      this->collideLeft = false;
    }
}

void 	Worm::wormGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects, size_t currentSelectedWeapon)
{
  int collision = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 1.0f)
	  && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y - 0.8f)
	  && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.3f)
	  && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.3f))
	{
	  collision = 1;
	  this->isCollisioning = true;
	}
    }
  if (collision == 0)
    {
      this->wormPos.Y -= WORM_MOVEMENT_SPEED;
      this->wormMesh->setPosition(this->wormPos);
      this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
      this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
      this->isCollisioning = false;
    }
}

void    Worm::wormJump(size_t currentSelectedWeapon)
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
	      this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
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
	      this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
            }
          this->isJumping = false;
        }
    }
}

void	Worm::removeMeshSceneNode()
{
  this->wormMesh->getParent()->removeChild(this->wormMesh);
  this->infos->getParent()->removeChild(this->infos);
}
