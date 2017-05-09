//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Fri May  5 18:56:09 2017 Stanislas Deneubourg
//

#include "GameEngine.hpp"
#include <iostream>

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr,
				      irr::video::IVideoDriver *driver,
				      const size_t &nb_textures,
				      const size_t &nb_shapes,
				      irr::IrrlichtDevice *device) : smgr(smgr), driver(driver),
								     device(device),
								     nb_shapes(nb_shapes)
{
  this->file_shape = "./ressources/shapes/Rock_0.dae";
  this->lastFrame = this->device->getTimer()->getTime();
  this->device->setEventReceiver(&this->receiver);
  this->cameraMovementSpeed = 50.0f;
  this->file_texture = "./ressources/textures/ground/ground" + std::to_string(std::rand() % nb_textures) + ".bmp";
  this->old_pos_x = 0;
  this->maxNumberPlatforms = (std::rand() % 8) + 2;
  this->menuInGame = new MenuInGame(this->device, this->driver, this->smgr);
}

void GameNamespace::GameEngine::setBlockProperties(int x, int y)
{
  this->groundObject = this->smgr->addMeshSceneNode(smgr->getMesh(file_shape.c_str()));
  if (this->groundObject != nullptr)
    {
      this->groundObject->setMaterialTexture(0,
					     this->driver->getTexture(file_texture.c_str())); // set diffuse texture
      this->groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
      smgr->getMeshManipulator()->makePlanarTextureMapping(this->groundObject->getMesh(), 1.0f);
      this->groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
      irr::f32 minRadius = this->groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.70f;
      this->groundObject->setPosition(irr::core::vector3df(this->old_pos_x + minRadius, y + minRadius, 0));
      if (x == 0)
	{
	  this->max_pos_x_tab.push_back(this->old_pos_x);
	  this->old_pos_x = 0;
	}
      this->old_pos_x += minRadius;
      this->groundObjects.push_back(this->groundObject);
    }
}

EventStatus GameNamespace::GameEngine::launchModel()
{
  EventStatus eventStatus = EventStatus::QUIT;

  while(this->device->run())
    if (this->device->isWindowActive())
      {
	const irr::u32 now = this->device->getTimer()->getTime();
	const irr::f32 frameDeltaTime = (irr::f32)(now - this->lastFrame) / 1000.0f;
	this->lastFrame = now;
	irr::core::vector3df realTimeCameraPosition = this->gameCamera->getPosition();
	irr::core::vector3df realTimeCameraTarget = this->gameCamera->getTarget();
	
	if (this->receiver.IsKeyDown(irr::KEY_KEY_A))
	  {
	    realTimeCameraPosition.Y += this->cameraMovementSpeed * frameDeltaTime;
	    realTimeCameraTarget.Y += this->cameraMovementSpeed * frameDeltaTime;
	  }
	else if (this->receiver.IsKeyDown(irr::KEY_KEY_E))
	  {
	    realTimeCameraPosition.Y -= this->cameraMovementSpeed * frameDeltaTime;
	    realTimeCameraTarget.Y -= this->cameraMovementSpeed * frameDeltaTime;
	  }
	if (this->receiver.IsKeyDown(irr::KEY_KEY_Q))
	  {
	    realTimeCameraPosition.X -= this->cameraMovementSpeed * frameDeltaTime;
	    realTimeCameraTarget.X -= this->cameraMovementSpeed * frameDeltaTime;
	  }
	else if (this->receiver.IsKeyDown(irr::KEY_KEY_D))
	  {
	    realTimeCameraPosition.X += this->cameraMovementSpeed * frameDeltaTime;
	    realTimeCameraTarget.X += this->cameraMovementSpeed * frameDeltaTime;
	  }
	if (this->receiver.IsKeyDown(irr::KEY_KEY_Z))
	  {
	    realTimeCameraPosition.Z += this->cameraMovementSpeed * frameDeltaTime;
	    realTimeCameraTarget.Z += this->cameraMovementSpeed * frameDeltaTime;
	  }
	else if (this->receiver.IsKeyDown(irr::KEY_KEY_S))
	  {
	    realTimeCameraPosition.Z -= this->cameraMovementSpeed * frameDeltaTime;
	    realTimeCameraTarget.Z -= this->cameraMovementSpeed * frameDeltaTime;
	  }
	if (this->receiver.IsKeyDown(irr::KEY_ESCAPE))
	  {
	    EventStatus eventStatusMenu = this->menuInGame->launchModel();
	    if (eventStatusMenu == EventStatus::QUIT || eventStatusMenu == EventStatus::BACK_TO_MENU)
	      break;
	  }

	// Algo de limitation de déplacement de la caméra

	/*
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
	    */
	if (realTimeCameraPosition.Y >= 150)
	  {
	    realTimeCameraPosition.Y = 150;
	    realTimeCameraTarget.Y = 150;
	  } else
	  if (realTimeCameraPosition.Y <= -150)
	    {
	      realTimeCameraPosition.Y = -150;
	      realTimeCameraPosition.Y = -150;
	    }
	if (realTimeCameraPosition.Z >= -20)
	  {
	    realTimeCameraPosition.Z = -20;
	    realTimeCameraTarget.Z = 80;
	  } else
	  if (realTimeCameraPosition.Z <= -120)
	    {
	      realTimeCameraPosition.Z = -120;
	      realTimeCameraTarget.Z = -20;
	    }

	this->gameCamera->setPosition(realTimeCameraPosition);
	this->gameCamera->setTarget(realTimeCameraTarget);
	this->driver->beginScene(true, true, 0);


	// draw scene normally
	this->smgr->drawAll();

	//        env->drawAll();

	this->driver->endScene();

	// display frames per second in window title
      }
  return (eventStatus);
}

static void fixRandPosition(int &value, int stop)
{
  for (int end = value; end < stop; ++end)
    {
      end = std::rand() % 30;
      value = end;
    }
  if (value == stop)
    {
      for (int end = value; end == stop; ++end)
	{
	  end = std::rand() % 30;
	  value = end;
	}
      if (value < stop)
	fixRandPosition(value, stop);
    }
}

void GameNamespace::GameEngine::setModelProperties()
{
  int init_start_x;
  int init_start_y;
  int init_end_x;
  int start_x;
  int start_y;
  int end_x;
  int end_y;

  this->menuInGame->setModelProperties();
  for (size_t i = 0; i < 30; i++)
    {
      for (size_t j = 0; j < 30; j++)
	this->gameMap.emplace_back(j, i);
    }

  for (size_t i = 1; i <= this->maxNumberPlatforms; i++)
    {
      init_start_x = std::rand() % 30;
      init_start_y = std::rand() % 30;
      init_end_x = std::rand() % 30;

      fixRandPosition(init_end_x, init_start_x);

      for (int plateformHeight = ((std::rand() % (init_start_y + 1))); plateformHeight > 0; plateformHeight--)
	{
	  start_x = std::rand() % 30;
	  start_y = std::rand() % 30;
	  end_x = std::rand() % 30;
	  end_y = start_y;

	  fixRandPosition(end_x, start_x);
	  this->gameMap.at(start_x + 30 * start_y).terrain = GameNamespace::TerrainType::GROUND;
	  this->gameMap.at(end_x + 30 * end_y).terrain = GameNamespace::TerrainType::GROUND;
	  this->gameMap.at(start_x + 30 * start_y).isStart = true;
	  this->gameMap.at(end_x + 30 * end_y).isEnd = true;
	  start_x++;
	  for (int start = start_x; start < end_x; start++)
	    this->gameMap.at(start + 30 * start_y).terrain = GameNamespace::TerrainType::GROUND;
	}

    }

  for (size_t i = 0; i < 30 * 30; i++)
    {
      if (this->gameMap.at(i).terrain == GameNamespace::TerrainType::GROUND)
	{

	      this->setBlockProperties(this->gameMap.at(i).x, this->gameMap.at(i).y);
	}
    }

  this->the_farthest_map_point_x = this->max_pos_x_tab[0];
  for (float i : this->max_pos_x_tab)
    {
      if (i > this->the_farthest_map_point_x)
	this->the_farthest_map_point_x = i;
      this->final_pos_x_avg += i;
    }
  this->final_pos_x_avg = final_pos_x_avg / this->max_pos_x_tab.size();
  this->gameCamera = smgr->addCameraSceneNode(nullptr,
					      irr::core::vector3df(/*this->final_pos_x_avg / 2 */ 0,
												  0, -100),
					      irr::core::vector3df(/*this->final_pos_x_avg / 2 */ 0,
												  0, 0),
					      -1, true);
}

GameNamespace::GameMap::GameMap(int x, int y)
{
  this->terrain = GameNamespace::TerrainType::AIR;
  this->isStart = false;
  this->isEnd = false;
  this->x = x;
  this->y = y;
}