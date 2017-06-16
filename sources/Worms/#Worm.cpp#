//
// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Fri Jun 16 09:19:16 2017 Stanislas Deneubourg
//

#include "Worms/Worm.hpp"

Worm::Worm(int nb, irr::core::vector3df vectorPos,
	   irr::IrrlichtDevice *device, std::string const &wormFile,
	   bool	isBot, irrklang::ISoundEngine *soundEngine) : inventory(device, soundEngine)
{
  int	dir = std::rand() % 3;
  this->wormName = "Player ";
  this->wormName += std::to_string(nb);
  this->healthPoints = 100;
  this->damageReceived = 0;
  this->damageDealt = 0;
  this->totalTime = 0;
  this->wormPos = vectorPos;
  this->wormType = static_cast<Worm::WormType>(isBot);
  this->m = device->getSceneManager()->getMesh(wormFile.c_str());
  if (this->m == nullptr)
    return;
  this->wormMesh = device->getSceneManager()->addAnimatedMeshSceneNode(m);
  this->wormMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->wormMesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
  if (dir == 0)
    this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
  else if (dir == 1)
    this->wormMesh->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
  else
    this->wormMesh->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
  this->lookingDirection = static_cast<Worm::LookingDirection>(dir);
  this->wormMesh->setFrameLoop(0, 20);
  this->wormMesh->setAnimationSpeed(0);
  this->wormMesh->setPosition(this->wormPos);
  this->wormMesh->setScale(irr::core::vector3df(0.8, 0.8, 0.8));
  this->wormStatus = Worm::WormStatus::WALKING;
  this->isPoisoned = false;
  this->edge = new irr::core::vector3d<irr::f32>[8];
  this->boundingBox = this->wormMesh->getTransformedBoundingBox();
  this->boundingBox.getEdges(this->edge);
  this->collideLeft = false;
  this->collideRight = false;
  this->addInfos(device);
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

double	Worm::wormTimerRollback(std::time_t turn_start)
{
  std::time_t	end = std::time(nullptr);
  this->totalTime = std::difftime(end, turn_start);
  return(this->totalTime);
}

void	Worm::wormResetAnimationSpeed()
{
  this->wormMesh->setAnimationSpeed(0);
}

const irr::core::vector3df	&Worm::wormGetPosition() const
{
  return (this->wormPos);
}

const irr::core::vector3df	&Worm::wormGetRotation() const
{
  return this->wormMesh->getRotation();
}

bool const 	&Worm::getWormType() const
{
  return reinterpret_cast<const bool &>(this->wormType);
}

