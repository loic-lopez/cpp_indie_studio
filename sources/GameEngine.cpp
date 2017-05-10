//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Wed May 10 14:16:33 2017 Stanislas Deneubourg
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
							       playSound(playSound),
							       drawWalls(drawWalls)
{
  this->file_shape = "./ressources/shapes/Rock_0.dae";
  this->lastFrame = this->device->getTimer()->getTime();
  this->device->setEventReceiver(&this->receiver);
  this->cameraMovementSpeed = 50.0f;
  this->generations = 5;
  this->size_x = 30;
  this->size_y = 30;
  this->fillProbe = 40;
  this->r1_cutoff = 3;
  this->r2_cutoff = 2;
  this->file_texture = "./ressources/textures/ground/ground" + std::to_string(std::rand() % nb_textures) + ".bmp";
  this->menuInGame = new MenuInGame(this->device, this->driver, this->smgr);
  this->max_y = this->size_y * (-1);
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
      this->the_farthest_map_point = this->size_x * minRadius;
      this->groundObject->setPosition(irr::core::vector3df(x * minRadius, -y, 0));
      this->groundObjects.push_back(this->groundObject);
    }
}

EventStatus GameNamespace::GameEngine::launchModel()
{
  EventStatus eventStatus = EventStatus::QUIT;
  EventStatus eventStatusMenu = EventStatus::STAND_BY;

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
	if (this->receiver.IsKeyUp(irr::KEY_ESCAPE) && eventStatusMenu != EventStatus::ENTER_IN_GAME)
	  {
	    this->device->getCursorControl()->setVisible(true);
	    eventStatusMenu = this->menuInGame->launchModel();
	    this->device->getCursorControl()->setVisible(false);
	    this->device->setEventReceiver(&this->receiver);
	    if (eventStatusMenu == EventStatus::QUIT || eventStatusMenu == EventStatus::BACK_TO_MENU)
	      break;
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
  int   x1, y1, y2, x2;
    
  //this->menuInGame->setModelProperties();

  for (int i = 0; i < this->size_y; i++)
    for (int j = 0; j < this->size_x; j++)
      this->gameMap.emplace_back(j, i);
  for (int i = 0; i < this->size_y; i++)
    for (int j = 0; j < this->size_x; j++)
      this->gameMap2.emplace_back(j, i);
  for (int i = 0; i < this->size_y * this->size_x; i++)
    {
      if ((i % this->size_y) == 0 || (i % this->size_x) == 29)
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
      if ((std::rand() % 100) < this->fillProbe)
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
      else
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
    }
  for (int i = 0; i < this->size_y * this->size_x; i++)
    this->gameMap2.at(i).terrain = GameNamespace::TerrainType::GROUND;
  for (int i = 0; i < this->generations; i++)
    {
      for (y1 = 1; y1 < this->size_y - 1; y1++)
        {
          for (x1 = 1; x1 < this->size_x - 1; x1++)
            {
              int       adjcount_r1 = 0;
              int       adjcount_r2 = 0;

              for (y2 = -1; y2 < 1; y2++)
		for (x2 = -1; x2 < 1; x2++)
		  if ((this->gameMap.at((x1-x2) + this->size_y * (y1-y2)).terrain) != GameNamespace::TerrainType::AIR)
		    adjcount_r1++;
              for (y2 = y1 - 2; y2 <= y1 + 2; y2++)
                {
                  for (x2 = x1 - 2; x2 <= x1 + 2; x2++)
                    {
                      if ((std::abs((y2-y1))) == 2 && (std::abs((x2-x1))) == 2)
                        continue;
                      if (y2 < 0 || x2 < 0 || y2 >= this->size_y || x2 >= this->size_x)
                        continue;
                      if ((this->gameMap.at(x2 + this->size_y * y2).terrain) != GameNamespace::TerrainType::AIR)
                        adjcount_r2++;
                    }
                }
              if (adjcount_r1 >= this->r1_cutoff || adjcount_r2 <= this->r2_cutoff)
                this->gameMap2.at(x1 + this->size_y * y1).terrain = GameNamespace::TerrainType::GROUND;
              else
                this->gameMap2.at(x1 + this->size_y * y1).terrain = GameNamespace::TerrainType::AIR;
            }
        }
      for (y1 = 1; y1 < this->size_y - 1; y1++)
	for (x1 = 1; x1 < this->size_x - 1; x1++)
	  this->gameMap.at(x1 + this->size_y * y1) = this->gameMap2.at(x1 + this->size_y * y1);
    }

  if (this->drawWalls)
    {
      for (int i = 0; i < this->size_x * this->size_y; i++)
	{
	  if ((i < this->size_x) || ((i % 30) == 0) || ((i % 30) == 29))
	    this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
	  if (i >= (this->size_x * (this->size_y - 1)))
	    this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
	}
      
    }
  else
    {
      for (int i = 0; i < this->size_x * this->size_y; i++)
        if ((i < this->size_x) || ((i % 30) == 0) || ((i % 30) == 29) || (i >= (this->size_x * (this->size_y - 1))))
          this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
    }

  for (int i = 0; i < this->size_x * this->size_y; i++)
    if (this->gameMap.at(i).terrain == GameNamespace::TerrainType::GROUND)
      this->setBlockProperties(this->gameMap.at(i).x, this->gameMap.at(i).y);

  // PRINT DE TEST DANS LE TERMINAL
  
  for (int i = 0; i < this->size_y * this->size_x; i++)
    {
      if (this->gameMap.at(i).terrain == GameNamespace::TerrainType::GROUND)
        std::cout << "X";
      else if (this->gameMap.at(i).terrain == GameNamespace::TerrainType::AIR)
        std::cout << ".";
      if (i % 30 == 29)
        std::cout << std::endl;
    }

  // FIN DES PRINT DE TEST

  std::cout << this->drawWalls << std::endl;
  
  this->gameCamera = smgr->addCameraSceneNode(nullptr,
					      irr::core::vector3df(this->the_farthest_map_point / 2,
								   0, -100),
					      irr::core::vector3df(this->the_farthest_map_point / 2,
								   0, 0),
					      -1, true);
  this->water_mesh = this->smgr->addHillPlaneMesh("water",
						  irr::core::dimension2d<irr::f32>(20,20), //	Taille du mesh initial
						  irr::core::dimension2d<irr::u32>(40,40), nullptr, 0, // Multiplicateur de taille du mesh
						  irr::core::dimension2d<irr::f32>(0,0), // Material
						  irr::core::dimension2d<irr::f32>(10,10)); // countHills
  this->sea = this->smgr->addWaterSurfaceSceneNode(this->water_mesh->getMesh(0),
						   0.5f, 300.0f, 0.5f);
  this->sea->setMaterialTexture(0, this->driver->getTexture("./ressources/textures/stones.jpg"));
  this->sea->setMaterialTexture(1, this->driver->getTexture("./ressources/textures/water.jpg"));
  this->sea->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  this->sea->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
  this->sea->setPosition(irr::core::vector3df(0.0f, this->max_y, 0.0f));
}

GameNamespace::GameMap::GameMap(int x, int y)
{
  this->terrain = GameNamespace::TerrainType::AIR;
  this->x = x;
  this->y = y;
}
