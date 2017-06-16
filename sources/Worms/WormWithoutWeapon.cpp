/*
** WormWithoutWeapon.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/WormWithoutWeapon.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. juin 15 19:16:29 2017 Loïc Lopez
// Last update Fri Jun 16 16:38:16 2017 Stanislas Deneubourg
*/

#include "Worms/Worm.hpp"

void    Worm::wormLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
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
      this->wormMoveLeft();
    }
  else
    {
      this->wormPos.X = collision_pos;
      this->collideLeft = true;
    }
}

void    Worm::wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
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
      this->wormMoveRight();
    }
  else
    {
      this->wormPos.X = collision_pos;
      this->collideRight = true;
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
  irr::gui::IGUIFont	*font = device->getGUIEnvironment()->getFont("ressources/fonts/SoftMarshmallow.png");
  irr::scene::ISceneManager	*smgr = device->getSceneManager();

  this->infos = smgr->addBillboardTextSceneNode(font, name.c_str(), 0,
						irr::core::dimension2d<irr::f32>(3.5f, 1.25f), irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f),
						-1, irr::video::SColor(0xFF00FF00), irr::video::SColor (0xFF00FF00));
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
