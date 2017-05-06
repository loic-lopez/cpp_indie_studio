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

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
				      const size_t &nb_textures, const size_t &nb_shapes, irr::IrrlichtDevice *device) : smgr(smgr), driver(driver), device(device), nb_shapes(nb_shapes)
{
  this->lastFrame = this->device->getTimer()->getTime();
  this->device->setEventReceiver(&this->receiver);
  this->cameraMovementSpeed = 50.0f;
  this->file_texture = "./ressources/textures/ground/ground" + std::to_string(std::rand() % nb_textures) + ".bmp";
  this->old_pos = 0;

}

void GameNamespace::GameEngine::setBlockProperties(int x, int y)
{
  this->file_shape = "./ressources/shapes/Rock_" + std::to_string(std::rand() % this->nb_shapes) + ".dae";
  irr::scene::IAnimatedMeshSceneNode *groundObject = this->smgr->addAnimatedMeshSceneNode(smgr->getMesh(file_shape.c_str()));
  if (groundObject != nullptr)
    {
      groundObject->setMaterialTexture(0,
				       this->driver->getTexture(file_texture.c_str())); // set diffuse texture
      groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
      smgr->getMeshManipulator()->makePlanarTextureMapping(groundObject->getMesh(), 1.0f);
      groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
      irr::f32 minRadius = groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.70f;
      //      groundObject->setPosition(irr::core::vector3df(old_pos + minRadius,0,0));
      groundObject->setPosition(irr::core::vector3df(this->old_pos + minRadius, y + minRadius, 0));
      groundObject->setRotation(irr::core::vector3df(std::rand() % 360, std::rand() % 360, 0));
      if (x == 0)
	{
	  this->max_pos_x_tab.push_back(old_pos);
	  this->old_pos = 0;
	}
      this->old_pos += minRadius;
      this->groundObjects.push_back(groundObject);
    }
}

void	GameNamespace::GameEngine::launchModel(irr::IrrlichtDevice *device)
{
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
	  this->device->closeDevice();

	// Algo de limitation de déplacement de la caméra

	if (realTimeCameraPosition.X >= this->the_farthest_map_point + 50)
	  {
	    realTimeCameraPosition.X = this->the_farthest_map_point + 50;
	    realTimeCameraTarget.X = this->the_farthest_map_point + 50;
	  } else
	  if (realTimeCameraPosition.X <= -50)
	    {
	      realTimeCameraPosition.X = -50;
	      realTimeCameraTarget.X = -50;
	    }
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
}

void GameNamespace::GameEngine::setModelProperties()
{
  int start_x;
  int start_y;
  int end_x;
  int end_y;

  for (size_t i = 0; i < 30; i++)
    {
      for (size_t j = 0; j < 30; j++)
	{
	  GameMap tmp;

	  tmp.x = j;
	  tmp.y = i;
	  tmp.terrain = GameNamespace::TerrainType::AIR;
	  this->gameMap.push_back(tmp);
	}
    }

  for (size_t i = 0; i < 2; i = i)
    {
      start_x = rand() % 30;
      start_y = rand() % 30;
      end_x = rand() % 30;
      end_y = rand() % 30;

      if ((this->gameMap.at(start_x + 30 * start_y).terrain) != GameNamespace::TerrainType::GROUND)
	{
	  this->gameMap.at(start_x + 30 * start_y).terrain = GameNamespace::TerrainType::GROUND;
	  i++;
	}
      if ((this->gameMap.at(end_x + 30 * end_y).terrain) != GameNamespace::TerrainType::GROUND)
	{
	  this->gameMap.at(end_x + 30 * end_y).terrain = GameNamespace::TerrainType::GROUND;
	  i++;
	}
    }
  for (size_t i = 0; i < 30 * 30; i++)
    {
      if ((this->gameMap.at(i).terrain) == GameNamespace::TerrainType::GROUND)
	{
	  size_t pos = i % 30;
	  for (size_t j = i; j - pos > 0; j--)
	    this->gameMap.at(j).terrain = GameNamespace::TerrainType::GROUND;
	}
    }
  for (size_t i = 0; i < 30 * 30; i++)
    {
      if ((this->gameMap.at(i).terrain) == GameNamespace::TerrainType::GROUND)
	{
	  //if (this->old_pos == 0)
	  //	    this->old_pos = this->gameMap.at(i).x;
	  this->setBlockProperties(this->gameMap.at(i).x, this->gameMap.at(i).y);
	}
    }

  this->the_farthest_map_point = this->max_pos_x_tab[0];
  for (float i : this->max_pos_x_tab)
    {
      if (i > this->the_farthest_map_point)
	this->the_farthest_map_point = i;
      this->final_pos_x_avg += i;
    }
  this->final_pos_x_avg = final_pos_x_avg / this->max_pos_x_tab.size();
  this->gameCamera = smgr->addCameraSceneNode(nullptr,
					      irr::core::vector3df(this->final_pos_x_avg / 2,
								   0, -100),
					      irr::core::vector3df(this->final_pos_x_avg / 2,
								   0, 0),
					      -1, true);
}
