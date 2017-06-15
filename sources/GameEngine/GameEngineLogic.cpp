//
// GameEngineLogic.cpp for game engine logic in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Sat Jun  3 17:10:57 2017 Stanislas Deneubourg
// Last update Thu Jun 15 11:37:23 2017 Stanislas Deneubourg
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
				     irr::core::position2di(this->screenSize.Width * 9 / 10,
							    this->screenSize.Height * 9 / 10),
				     nullptr,
				     irr::video::SColor(255, 255, 255, 255), 0);
      // Affichage des deux timers dans la box                                                                                                                                                                

      if (this->turnTimeLeft > 10)
	this->font->draw(stringTurnTimer.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 30,
						   this->screenSize.Height * 9 / 10 + 30,
						   this->screenSize.Width * 9 / 10 + 60,
						   this->screenSize.Height * 9 / 10 + 60),
			 irr::video::SColor(255, 255, 190, 0));
      else
	this->font->draw(stringTurnTimer.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 30,
						   this->screenSize.Height * 9 / 10 + 30,
						   this->screenSize.Width * 9 / 10 + 60,
						   this->screenSize.Height * 9 / 10 + 60),
			 irr::video::SColor(255, 255, 0, 0));
      if (this->timeBeforeSuddenDeath > 60)
	this->font->draw(stringSuddenDeathTime.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 5,
						   this->screenSize.Height * 9 / 10 + 5,
						   this->screenSize.Width * 9 / 10 + 25,
						   this->screenSize.Height * 9 / 10 + 25),
			 irr::video::SColor(255, 255, 190, 0));
      else
	this->font->draw(stringSuddenDeathTime.c_str(),
			 irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 5,
						   this->screenSize.Height * 9 / 10 + 5,
						   this->screenSize.Width * 9 / 10 + 25,
						   this->screenSize.Height * 9 / 10 + 25),
			 irr::video::SColor(255, 255, 0, 0));
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
