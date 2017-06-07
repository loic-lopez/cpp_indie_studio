//
// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Wed Jun  7 16:40:01 2017 Stanislas Deneubourg
//

#include "Worms/Worm.hpp"

Worm::Worm(int nb, irr::core::vector3df vectorPos,
	   irr::IrrlichtDevice *device, std::string wormFile,
	   bool	isBot)
{
  int	dir = std::rand() % 3;
  this->wormName = "Player ";
  this->wormName += std::to_string(nb);
  this->healthPoints = 100;
  this->damageReceived = 0;
  this->damageDealt = 0;
  this->totalTime = 0;
  this->posX = vectorPos.X;
  this->posY = vectorPos.Y;
  this->posZ = vectorPos.Z;
  this->wormType = static_cast<Worm::WormType>(isBot);
  this->wormPosition = vectorPos;
  this->m = device->getSceneManager()->getMesh(wormFile.c_str());
  if (!this->m)
    return;
  this->wormMesh = device->getSceneManager()->addAnimatedMeshSceneNode(m);
  this->wormMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->wormMesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  if (dir == 0)
    this->wormMesh->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
  else if (dir == 1)
    this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
  else
    this->wormMesh->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
  this->lookingDirection = static_cast<Worm::LookingDirection>(dir);
  this->wormMesh->setFrameLoop(0, 15);
  this->wormMesh->setAnimationSpeed(5);
  this->wormMesh->setPosition(irr::core::vector3df(this->posX, this->posY, this->posZ));
  this->wormStatus = Worm::WormStatus::WALKING;
}

Worm::~Worm()
{

}

void	Worm::setHealthPoints(int nb)
{
  this->healthPoints += nb;
}

void	Worm::setDamageDealt(int nb)
{
  this->damageDealt += nb;
}

void	Worm::setDamageReceived(int nb)
{
  this->damageReceived += nb;
}

int	Worm::getHealthPoints()
{
  return (this->healthPoints);
}

unsigned int Worm::getDamageDealt()
{
  return (this->damageDealt);
}

unsigned int Worm::getDamageReceived()
{
  return (this->damageReceived);
}

double	Worm::turnOfThatWorm(std::time_t turn_start)
{
  std::time_t	end = std::time(NULL);
  this->totalTime = std::difftime(end, turn_start);
  return(this->totalTime);
}

void	Worm::wormMoveLeft(irr::IrrlichtDevice *device)
{
  irr::f32		wormMovementSpeed = 0.07f;

  this->posX -= wormMovementSpeed;
  if (this->lookingDirection == Worm::LookingDirection::RIGHT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
      this->lookingDirection = Worm::LookingDirection::LEFT;
    }
  this->wormMesh->setPosition(irr::core::vector3df(this->posX, this->posY, this->posZ));
}

void	Worm::wormMoveRight(irr::IrrlichtDevice *device)
{
  irr::f32		wormMovementSpeed = 0.07f;
  
  this->posX += wormMovementSpeed;
  if (this->lookingDirection == Worm::LookingDirection::LEFT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
      this->lookingDirection = Worm::LookingDirection::RIGHT;
    }
  this->wormMesh->setPosition(irr::core::vector3df(this->posX, this->posY, this->posZ));
}
