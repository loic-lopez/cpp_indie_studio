// Worm.cpp for worm in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:43:41 2017 Stanislas Deneubourg
// Last update Sun Jun 18 12:16:50 2017 Stanislas Deneubourg
//

#include "Worms/Worm.hpp"

Worm::Worm(int nb, irr::core::vector3df vectorPos,
	   irr::IrrlichtDevice *device, std::string const &wormFile,
	   bool	isBot, irrklang::ISoundEngine *soundEngine, irr::gui::IGUIFont *teamColor) : inventory(device, soundEngine)
{
  int	dir = std::rand() % 3;
  this->teamFont = teamColor;
  this->isDrowned = false;
  this->wormName = this->genName();
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
  this->jumpConstraintsY = 0.1f;
  this->jumpConstraintsX = 0.1f;
  this->isCollisioning = false;
  this->isJumping = false;
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

int	Worm::getHealthPoints() const
{
  return (this->healthPoints);
}

unsigned int Worm::getDamageDealt() const
{
  return (this->damageDealt);
}

unsigned int Worm::getDamageReceived() const
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

std::string	const &Worm::getWormName() const
{
  return (this->wormName);
}

const char      *Worm::genName() const
{
  const char    *names[32] = {"Ver-nissage", "Ver-mifuge", "Ver-tical", "Ver-tige", "Ver-tebre", "Ver-satile", "Ver-ger", "Ver-dir", "Ver-rouiller", "Ver-sion",
			      "Ver-mine", "Ver-glas", "Ver-dict", "Ver-doyant", "Ver-tex", "Ver-gogne", "Ta-ver-ne", "Uni-ver-s", "Tra-ver-s", "Cou-ver-ture",
			      "A-ver-se", "Ren-ver-ser", "Revol-ver", "Hi-ver-nale", "Bali-ver-ne", "Tergi-ver-ser", "In-ver-te-bre", "Per-ver-s", "Ad-ver-saire", "Intro-ver-ti",
			      "Fait-di-ver-s", "Culti-ver"};

  return (names[std::rand()%32]);
}

irr::gui::IGUIFont *Worm::getTeamFont() const
{
  return (this->teamFont);
}

void    Worm::wormUpCollision(std::vector<irr::scene::IMeshSceneNode *> groundObjects)
{
  int		collision = 0;
  irr::f32      collision_pos = 0;
  for (unsigned int i = 0; i < groundObjects.size(); i++)
    {
      if ((this->wormMesh->getPosition().Y <= groundObjects.at(i)->getPosition().Y + 1.3f)
          && (this->wormMesh->getPosition().Y >= groundObjects.at(i)->getPosition().Y + 1.1f)
          && (this->wormMesh->getPosition().X >= groundObjects.at(i)->getPosition().X - 3.35f)
          && (this->wormMesh->getPosition().X <= groundObjects.at(i)->getPosition().X + 3.35f))
	{
	  collision = 1;
          this->isCollisioning = true;
          collision_pos = groundObjects.at(i)->getPosition().Y + 1.4f;
	}
    }
  if (collision == 1)
    {
      this->wormPos.Y = collision_pos;
      this->wormMesh->setPosition(this->wormPos);
      this->infos->setPosition(irr::core::vector3df(this->wormPos.X, this->wormPos.Y + 5.0f, this->wormPos.Z - 1.75f));
    }
  else
    this->isCollisioning = false;
}
