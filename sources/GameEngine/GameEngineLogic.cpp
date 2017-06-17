//
// GameEngineLogic.cpp for game engine logic in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Sat Jun  3 17:10:57 2017 Stanislas Deneubourg
// Last update Sat Jun 17 10:20:21 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

void	GameNamespace::GameEngine::cameraMovements()
{
  irr::core::vector3df    realTimeCameraPosition = this->gameCamera->getPosition();
  irr::core::vector3df    realTimeCameraTarget = this->gameCamera->getTarget();
  const irr::u32		now = this->device->getTimer()->getTime();
  const	auto		frameDeltaTime = static_cast<irr::f32>((now - this->lastFrame) / 1000.0f);

  this->lastFrame = now;
  if (this->eventReceiver.IsKeyDown(irr::KEY_UP))
    {
      realTimeCameraPosition.Y += this->cameraMovementSpeed * frameDeltaTime;
      realTimeCameraTarget.Y += this->cameraMovementSpeed * frameDeltaTime;
    }
  else if (this->eventReceiver.IsKeyDown(irr::KEY_DOWN))
    {
      realTimeCameraPosition.Y -= this->cameraMovementSpeed * frameDeltaTime;
      realTimeCameraTarget.Y -= this->cameraMovementSpeed * frameDeltaTime;
    }
  if (this->eventReceiver.IsKeyDown(irr::KEY_LEFT))
    {
      realTimeCameraPosition.X -= this->cameraMovementSpeed * frameDeltaTime;
      realTimeCameraTarget.X -= this->cameraMovementSpeed * frameDeltaTime;
    }
  else if (this->eventReceiver.IsKeyDown(irr::KEY_RIGHT))
    {
      realTimeCameraPosition.X += this->cameraMovementSpeed * frameDeltaTime;
      realTimeCameraTarget.X += this->cameraMovementSpeed * frameDeltaTime;
    }
  if (this->eventReceiver.IsKeyDown(irr::KEY_RSHIFT))
    {
      realTimeCameraPosition.Z += this->cameraMovementSpeed * frameDeltaTime;
      realTimeCameraTarget.Z += this->cameraMovementSpeed * frameDeltaTime;
    }
  else if (this->eventReceiver.IsKeyDown(irr::KEY_RCONTROL) || this->eventReceiver.IsKeyDown(irr::KEY_LCONTROL))
    {
      realTimeCameraPosition.Z -= this->cameraMovementSpeed * frameDeltaTime;
      realTimeCameraTarget.Z -= this->cameraMovementSpeed * frameDeltaTime;
    }
  if (realTimeCameraPosition.X >= this->theFarthestMapPoint + 50)
    {
      realTimeCameraPosition.X = this->theFarthestMapPoint + 50;
      realTimeCameraTarget.X = this->theFarthestMapPoint + 50;
    }
  else if (realTimeCameraPosition.X <= -50)
    {
      realTimeCameraPosition.X = -50;
      realTimeCameraTarget.X = -50;
    }
  if (realTimeCameraPosition.Y >= this->sizeY)
    {
      realTimeCameraPosition.Y = this->sizeY;
      realTimeCameraTarget.Y = this->sizeY;
    }
  else if (realTimeCameraPosition.Y <= -this->sizeY - 5)
    {
      realTimeCameraPosition.Y = -this->sizeY - 5;
      realTimeCameraTarget.Y = -this->sizeY - 5;
    }
  if (realTimeCameraPosition.Z >= -20)
    {
      realTimeCameraPosition.Z = -20;
      realTimeCameraTarget.Z = 80;
    }
  else if (realTimeCameraPosition.Z <= -120)
    {
      realTimeCameraPosition.Z = -120;
      realTimeCameraTarget.Z = -20;
    }
  this->gameCamera->setPosition(realTimeCameraPosition);
  this->gameCamera->setTarget(realTimeCameraTarget);
}

void	GameNamespace::GameEngine::triggerTimer()
{
  if (this->spriteBank->getTexture(0) != nullptr)
    {
      int                 turnTimeLeftToInt = std::round(this->turnTimeLeft);     // Affichage du timer du tour                                                                                               
      int                 timeBeforeSuddenDeathToInt = static_cast<int>(this->timeBeforeSuddenDeath); // Affichage du timer de mort subite                                                                    
      std::string         stringTurnTimer = std::to_string(turnTimeLeftToInt);
      std::string         stringSuddenDeathTime;

      if (this->timeBeforeSuddenDeath > 60)
	{
	  if ((timeBeforeSuddenDeathToInt % 60) == 60)
	    {
	      stringSuddenDeathTime = std::to_string(timeBeforeSuddenDeathToInt / 60);
	      stringSuddenDeathTime += ":";
	      stringSuddenDeathTime += "00";
	    }
	  else if ((timeBeforeSuddenDeathToInt % 60) < 10)
	    {
	      stringSuddenDeathTime = std::to_string(timeBeforeSuddenDeathToInt / 60);
	      stringSuddenDeathTime += ":";
	      stringSuddenDeathTime += "0";
	      stringSuddenDeathTime += std::to_string(timeBeforeSuddenDeathToInt % 60);
	    }
	  else
	    {
	      stringSuddenDeathTime = std::to_string(timeBeforeSuddenDeathToInt / 60);
	      stringSuddenDeathTime += ":";
	      stringSuddenDeathTime += std::to_string(timeBeforeSuddenDeathToInt % 60);
	    }
	}
      else
	stringSuddenDeathTime += std::to_string(timeBeforeSuddenDeathToInt % 60);

      this->spriteBank->draw2DSprite(irr::u32(0),
				     irr::core::position2di(this->screenSize.Width * 8 / 10,
							    this->screenSize.Height * 8 / 10),
				     nullptr,
				     irr::video::SColor(255, 255, 255, 255), 0);
      // Affichage des deux timers dans la box                                                                                                                                                                

      if (this->turnTimeLeft > 10)
	this->font->draw(stringTurnTimer.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 8 / 10 + this->timerSize.Width * 4 / 10,
						   this->screenSize.Height * 8 / 10 + this->timerSize.Height * 6 / 10,
						   this->screenSize.Width * 8 / 10,
						   this->screenSize.Height * 8 / 10),
			 irr::video::SColor(255, 255, 190, 0));
      else
	this->font->draw(stringTurnTimer.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 8 / 10 + this->timerSize.Width * 4 / 10,
						   this->screenSize.Height * 8 / 10 + this->timerSize.Height * 6 / 10,
						   this->screenSize.Width *  8/ 10 + 60,
						   this->screenSize.Height * 8 / 10 + 60),
			 irr::video::SColor(255, 255, 0, 0));
      if (this->timeBeforeSuddenDeath > 60)
	this->font->draw(stringSuddenDeathTime.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 8 / 10 + this->timerSize.Width / 3,
						   this->screenSize.Height * 8 / 10 + this->timerSize.Height / 7,
						   this->screenSize.Width * 8 / 10,
						   this->screenSize.Height * 8 / 10),
			 irr::video::SColor(255, 255, 190, 0));
      else
	this->font->draw(stringSuddenDeathTime.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 8 / 10 + this->timerSize.Width * 4 / 10,
						   this->screenSize.Height * 8 / 10 + this->timerSize.Height / 7,
						   this->screenSize.Width * 8 / 10,
						   this->screenSize.Height * 8 / 10),
			 irr::video::SColor(255, 255, 0, 0));
      if (this->turnTimeLeft <= 60 && this->turnTimeLeft >= 57)
	{
	  std::string	com = this->teams.at(this->currentWormIdPlaying).getWormName(this->currentWormIdPlaying).c_str();
	  com += " ";
	  if (!this->comm)
	    {
	      this->rng = this->genComm("begin");
	      this->comm = true;
	    }
	  com += this->rng;
	  this->font->draw(com.c_str() , irr::core::rect<irr::s32>(this->screenSize.Width / 2 - 200, this->screenSize.Height / 5, this->screenSize.Width / 2 + 700, this->screenSize.Height / 10 + 50), irr::video::SColor(255, 255, 0, 255));
	}
      if (this->turnTimeLeft < 57)
	this->comm = false;
    }
}

void 	GameNamespace::GameEngine::poisonEffect()
{
  for (unsigned int i = 0; i < this->teams.size(); i++)
    {
      this->teams.at(i).poisonEffect();
    }
}

void 	GameNamespace::GameEngine::gravity()
{
  for (unsigned int i = 0; i < this->teams.size(); i++)
  {
    this->teams.at(i).teamGravity(this->groundObjects);
      if (this->sea->getPosition().Y >=
	  this->teams.at(i).getCurrentWormPosition(this->currentWormIdPlaying).Y
	  && !this->teams.at(i).getWormIsDrowned(this->currentWormIdPlaying))
	{
	  this->teams.at(i).setWormIsDrowned(this->currentWormIdPlaying, true);
	  this->soundEngine->play2D("ressources/sounds/Splash.wav");
	}
  }
}

void 	GameNamespace::GameEngine::gravity(size_t currentWeapon)
{
  for (unsigned int i = 0; i < this->teams.size(); i++)
    {
      this->teams.at(i).teamGravity(this->groundObjects, currentWeapon);
      if (this->sea->getPosition().Y >=
	  this->teams.at(i).getCurrentWormPosition(this->currentWormIdPlaying).Y
	  && !this->teams.at(i).getWormIsDrowned(this->currentWormIdPlaying))
	{
	  this->teams.at(i).setWormIsDrowned(this->currentWormIdPlaying, true);
	  this->soundEngine->play2D("ressources/sounds/Splash.wav");
	}
    }
}

void    GameNamespace::GameEngine::leftCollision(size_t currentWeaponSelected)
{
  this->teams.at(this->currentTeamIdPlaying).teamLeftCollision(this->groundObjects, this->currentWormIdPlaying, currentWeaponSelected);
}

void    GameNamespace::GameEngine::rightCollision(size_t currentWeaponSelected)
{
  this->teams.at(this->currentTeamIdPlaying).teamRightCollision(this->groundObjects, this->currentWormIdPlaying, currentWeaponSelected);
}

void    GameNamespace::GameEngine::leftCollision()
{
  this->teams.at(this->currentTeamIdPlaying).teamLeftCollision(this->groundObjects, this->currentWormIdPlaying);
}

void    GameNamespace::GameEngine::rightCollision()
{
  this->teams.at(this->currentTeamIdPlaying).teamRightCollision(this->groundObjects, this->currentWormIdPlaying);
}

const char 	*GameNamespace::GameEngine::genComm(std::string const &which) const
{
  const char 	*begin[7] = {"va dechirer", "se prepare a faire mal", "comment vas-tu ?", "c'est a toi de jouer !",
			     "se chauffe", "a mange du lion ce matin...", "a une bonne tete de vainqueur"};
  const char 	*deaths[5] = {"n'aura pas fait long feu", "va nourrir les vers...", "s'est eteint trop tot",
			      "n'apprecie guere le plomb", "tu resteras a jamais dans nos coeurs"};
  const char	*drown[3] = {"va nourrir les poissons !", "a fini comme appat de peche !", "voulait devenir une sirene..."};

  if (which == "begin")
    return (begin[std::rand()%7]);
  else if (which == "deaths")
    return (deaths[std::rand()%5]);
  else
    return (drown[std::rand()%3]);
}

void    GameNamespace::GameEngine::jump(size_t currentWeaponSelected)
{
  this->teams.at(this->currentTeamIdPlaying).teamJump(this->currentWormIdPlaying, currentWeaponSelected);
}

void    GameNamespace::GameEngine::jump()
{
  this->teams.at(this->currentTeamIdPlaying).teamJump(this->currentWormIdPlaying);
}
