//
// GameEngineLogic.cpp for game engine logic in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Sat Jun  3 17:10:57 2017 Stanislas Deneubourg
// Last update Sat Jun  3 17:21:18 2017 Stanislas Deneubourg
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
  if (realTimeCameraPosition.X >= this->the_farthest_map_point + 50)
    {
      realTimeCameraPosition.X = this->the_farthest_map_point + 50;
      realTimeCameraTarget.X = this->the_farthest_map_point + 50;
    }
  else if (realTimeCameraPosition.X <= -50)
    {
      realTimeCameraPosition.X = -50;
      realTimeCameraTarget.X = -50;
    }
  if (realTimeCameraPosition.Y >= this->size_y)
    {
      realTimeCameraPosition.Y = this->size_y;
      realTimeCameraTarget.Y = this->size_y;
    }
  else if (realTimeCameraPosition.Y <= -this->size_y - 5)
    {
      realTimeCameraPosition.Y = -this->size_y - 5;
      realTimeCameraTarget.Y = -this->size_y - 5;
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
