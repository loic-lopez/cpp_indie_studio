/*
** WormWithWeapon.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/WormWithWeapon.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. juin 15 19:15:02 2017 Loïc Lopez
// Last update Fri Jun 16 16:38:51 2017 Stanislas Deneubourg
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
  irr::f32      collision_pos = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 0.7f - 2.30f)
          && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.7f - 2.30f)
          && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.35f)
          && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X + 2.25f)
          && (this->collideRight == false))
        {
          collision = 1;
          collision_pos = groundObjects.at(i)->getPosition().X + 2.4f;
        }
    }
  if (collision == 0)
    {
      this->collideLeft = false;
      this->wormMoveLeft(currentSelectedWeapon);
    }
  else
    {
      this->wormPos.X = collision_pos;
      this->collideLeft = true;
    }
}

void    Worm::wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
                                 size_t currentSelectedWeapon)
{
  int		collision = 0;
  irr::f32      collision_pos = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 0.7f - 2.30f)
          && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.7f - 2.30f)
          && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.35f)
          && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X - 2.25f)
          && (this->collideLeft == false))
        {
          collision = 1;
          collision_pos = groundObjects.at(i)->getPosition().X - 2.4f;
        }
    }
  if (collision == 0)
    {
      this->collideRight = false;
      this->wormMoveRight(currentSelectedWeapon);
    }
  else
    {
      this->wormPos.X = collision_pos;
      this->collideRight = true;
    }
}

void 	Worm::wormGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects, size_t currentSelectedWeapon)
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
      this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
      this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
      this->isCollisioning = false;
    }
}
