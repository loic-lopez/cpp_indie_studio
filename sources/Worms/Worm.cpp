//
// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Wed Jun 14 14:07:15 2017 Stanislas Deneubourg
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
  this->worm_pos = vectorPos;
  this->wormType = static_cast<Worm::WormType>(isBot);
  this->wormPosition = vectorPos;
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
  this->wormMesh->setPosition(this->worm_pos);
  this->wormStatus = Worm::WormStatus::WALKING;
  this->isPoisoned = false;
  this->edge = new irr::core::vector3d<irr::f32>[8];
  this->boundingBox = this->wormMesh->getTransformedBoundingBox();
  this->boundingBox.getEdges(this->edge);

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
  std::time_t	end = std::time(nullptr);
  this->totalTime = std::difftime(end, turn_start);
  return(this->totalTime);
}

void	Worm::wormMoveLeft(size_t const &currentSelectedWeapon)
{
  this->worm_pos.X -= WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::RIGHT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, 90.0f, 0.0));
      this->lookingDirection = Worm::LookingDirection::LEFT;
      this->inventory.setWeaponRotationToWormPosition(currentSelectedWeapon, this->wormMesh->getRotation());
    }
  this->wormMesh->setPosition(this->worm_pos);
  this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->worm_pos);
}

void	Worm::wormMoveRight(size_t const &currentSelectedWeapon)
{
  this->worm_pos.X += WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::LEFT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
      this->lookingDirection = Worm::LookingDirection::RIGHT;
      this->inventory.setWeaponRotationToWormPosition(currentSelectedWeapon, this->wormMesh->getRotation());
    }
  this->wormMesh->setPosition(this->worm_pos);
  this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->worm_pos);
}

void	Worm::wormResetAnimationSpeed()
{
  this->wormMesh->setAnimationSpeed(0);
}

const irr::core::vector3df	&Worm::wormGetPosition() const
{
  return (this->worm_pos);
}

const irr::core::vector3df	&Worm::wormGetRotation() const
{
  return this->wormMesh->getRotation();
}

