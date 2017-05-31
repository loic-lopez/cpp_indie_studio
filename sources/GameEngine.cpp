//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Wed May 31 14:03:35 2017 Stanislas Deneubourg
//

#include "GameEngine.hpp"
#include <iostream>

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr,
				      irr::video::IVideoDriver *driver,
				      const size_t &nb_textures,
				      const size_t &nb_shapes,
				      irr::IrrlichtDevice *device,
				      const bool &playSound,
				      const bool &drawWalls) : smgr(smgr), driver(driver),
							       device(device),
							       nb_shapes(nb_shapes),
							       menuInGame(new MenuInGame(this->device, this->driver,
											 this->smgr)),
							       playSound(playSound),
							       drawWalls(drawWalls)
{
  this->file_shape = "./ressources/shapes/Rock_0.dae";
  this->worm = "ressources/textures/Worm/Worm.obj";
  this->lastFrame = this->device->getTimer()->getTime();
  this->device->setEventReceiver(&this->receiver);
  this->cameraMovementSpeed = 50.0f;
  this->generations = 5;
  this->size_x = 40;
  this->size_y = 40;
  this->fillProbe = (std::rand() % 21) + 30;
  this->r1_cutoff = 3;
  this->r2_cutoff = 2;
  this->file_texture = "./ressources/textures/ground/ground" + std::to_string(std::rand() % nb_textures) + ".bmp";
  this->worm_texture = "./ressources/textures/Worm/WormTextures.png";
  this->max_y = this->size_y * (-1);
  this->worms_par_team = 4;
  this->number_of_teams = 2;
}

GameNamespace::GameEngine::~GameEngine()
{
}

void GameNamespace::GameEngine::setBlockProperties(int x, int y)
{
  this->groundObject = this->smgr->addMeshSceneNode(smgr->getMesh(file_shape.c_str()));
  if (this->groundObject != nullptr)
    {
      this->groundObject->setMaterialTexture(0,
					     this->driver->getTexture(file_texture.c_str())); // set diffuse texture
      this->groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
      this->smgr->getMeshManipulator()->makePlanarTextureMapping(this->groundObject->getMesh(), 1.0f);
      this->groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
      irr::f32 minRadius = this->groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.70f;
      this->block_size = minRadius;
      this->the_farthest_map_point = this->size_x * minRadius;
      this->groundObject->setPosition(irr::core::vector3df(x * minRadius, -y * (minRadius / 3), 0));
      this->groundObjects.push_back(this->groundObject);
    }
}

void GameNamespace::GameEngine::setWorms()
{
  for (int i = 0; i < number_of_teams; i++)
    {
      irr::scene::IAnimatedMesh* m = this->device->getSceneManager()->getMesh(worm.c_str());
      if (!m)
	return;
      irr::scene::IAnimatedMeshSceneNode* animworms = this->device->getSceneManager()->addAnimatedMeshSceneNode(m);
      animworms->setAnimationSpeed(30);
      this->worms = animworms;
      this->worms->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->worms->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
    }
      this->worms->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
}

EventStatus GameNamespace::GameEngine::launchModel()
{
  EventStatus eventStatus = EventStatus::QUIT;
  EventStatus eventStatusMenu = EventStatus::STAND_BY;
  irr::s32	lastFPS = -1;
  
  while(this->device->run())
    if (this->device->isWindowActive())
      {
	const irr::s32 fps = this->driver->getFPS();
	if (lastFPS != fps)
	  {
	    irr::core::stringw caption = L"Worms 3D, running at ";
	    caption += fps;
	    caption += L" fps, with the engine ";
	    caption += driver->getName();
	    caption += L".";
	    this->device->setWindowCaption(caption.c_str());
	    lastFPS = fps;
	  }
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
	if (this->receiver.IsKeyUp(irr::KEY_ESCAPE) && eventStatusMenu != EventStatus::ENTER_IN_GAME)
	  {
	    this->device->getCursorControl()->setVisible(true);
	    eventStatusMenu = this->menuInGame->launchModel();
	    this->device->getCursorControl()->setVisible(false);
	    this->device->setEventReceiver(&this->receiver);
	    if (eventStatusMenu == EventStatus::QUIT || eventStatusMenu == EventStatus::BACK_TO_MENU)
	      {
		eventStatus = EventStatus::BACK_TO_MENU;
		break;
	      }
	  }
	else if (eventStatusMenu == EventStatus::ENTER_IN_GAME)
	    eventStatusMenu = EventStatus::STAND_BY;

	// Algo de limitation de déplacement de la caméra

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
	if (realTimeCameraPosition.Y >= this->size_y + 5)
	  {
	    realTimeCameraPosition.Y = this->size_y + 5;
	    realTimeCameraTarget.Y = this->size_y + 5;
	  }
	else if (realTimeCameraPosition.Y <= 5 - this->size_y)
	  {
	    realTimeCameraPosition.Y = 5 - this->size_y;
	    realTimeCameraTarget.Y = 5 - this->size_y;
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
	this->driver->beginScene(true, true, 0);
	this->smgr->drawAll();
	this->driver->endScene();
      }
  this->driver->removeAllTextures();
  this->smgr->clear();
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
  this->mapGen();
  this->backgroundGen();
  this->setWorms();
}

GameNamespace::GameMap::GameMap(int x, int y)
{
  this->terrain = GameNamespace::TerrainType::AIR;
  this->x = x;
  this->y = y;
}
