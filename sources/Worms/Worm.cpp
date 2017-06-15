//
// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Thu Jun 15 15:31:09 2017 Stanislas Deneubourg
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
  this->wormStatus = Worm::WormStatus::WALKING;
  this->isPoisoned = false;
  this->edge = new irr::core::vector3d<irr::f32>[8];
  this->boundingBox = this->wormMesh->getTransformedBoundingBox();
  this->boundingBox.getEdges(this->edge);
  this->collideLeft = false;
  this->collideRight = false;
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
}

void	Worm::wormMoveRight(size_t const &currentSelectedWeapon)
{
  this->wormPos.X += WORM_MOVEMENT_SPEED;
  this->wormMesh->setAnimationSpeed(10);
  if (this->lookingDirection == Worm::LookingDirection::LEFT
      || this->lookingDirection == Worm::LookingDirection::FRONT)
    {
      this->wormMesh->setRotation(irr::core::vector3df(0.0, -90.0, 0.0));
      this->lookingDirection = Worm::LookingDirection::RIGHT;
      this->inventory.setWeaponRotationToWormPosition(currentSelectedWeapon, this->wormMesh->getRotation());
    }
  this->wormMesh->setPosition(this->wormPos);
  this->inventory.setWeaponPositionToWormPosition(currentSelectedWeapon, this->wormPos);
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

void 	Worm::wormGravity(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  int collision = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y - 1.0)
	  && (this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y - 0.8)
	  && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.3)
	  && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.3))
	collision = 1;
    }
  if (collision == 0)
    {
      this->wormPos.Y -= WORM_MOVEMENT_SPEED;
      this->wormMesh->setPosition(this->wormPos);
    }
}

void	Worm::wormLeftCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
				size_t currentSelectedWeapon)
{
  int	collision = 0;
  irr::f32	collision_pos;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.8)
	  && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 2.35)
	  && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X + 2.25)
	  && (this->collideRight == false))
	{
	  collision = 1;
	  collision_pos = groundObjects.at(i)->getPosition().X + 2.4;
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
      //      this->wormMesh->setPosition(this->wormPos);
    }
}

void	Worm::wormRightCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
				 size_t currentSelectedWeapon)
{
  int	collision = 0;
  irr::f32	collision_pos;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 0.8)
	  && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 2.35)
	  && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X - 2.25)
	  && (this->collideLeft == false))
	{
	  collision = 1;
	  collision_pos = groundObjects.at(i)->getPosition().X - 2.4;
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
      //      this->wormMesh->setPosition(this->wormPos);
    }
}

bool const 	&Worm::getWormType() const
{
  return reinterpret_cast<const bool &>(this->wormType);
}
