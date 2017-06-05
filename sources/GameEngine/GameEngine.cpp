//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Sat Jun  3 17:20:54 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr,
				      irr::video::IVideoDriver *driver,
				      const size_t &nb_textures,
				      const size_t &nb_shapes,
				      irr::IrrlichtDevice *device,
				      const bool &playSound,
				      const bool &drawWalls,
				      const irr::s32 &bot_teams,
				      const irr::s32 &human_teams,
				      const irr::s32 &teams,
				      const irr::s32 &worms_in_each_team) : smgr(smgr), driver(driver),
									    device(device),
									    nb_shapes(nb_shapes),
									    eventReceiver(device),
									    menuInGame(new MenuInGame(this->device,
												      this->driver,
												      this->smgr,
												      this->eventReceiver)),
									    playSound(playSound),
									    drawWalls(drawWalls)
{
  this->file_shape = "./ressources/shapes/Rock_0.dae";
  this->worm = "ressources/textures/Worm/Worm.obj";
  this->lastFrame = this->device->getTimer()->getTime();
  this->device->setEventReceiver(&this->eventReceiver);
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
  this->worms_per_team = worms_in_each_team;
  this->number_of_human_teams = human_teams;
  this->number_of_bot_teams = bot_teams;
  this->number_of_teams = teams;
  this->current_worm_id_playing = 0;
  this->current_team_id_playing = 0;
  this->game_start = false;
}

GameNamespace::GameEngine::~GameEngine()
{
  this->smgr->clear();
}

void	GameNamespace::GameEngine::setBlockProperties(int x, int y)
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

EventStatus GameNamespace::GameEngine::launchModel()
{
  EventStatus 	eventStatusMenu = EventStatus::STAND_BY;
  irr::s32	lastFPS = -1;

  this->menuInGame->setModelProperties();
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

	this->cameraMovements();
	
	// BOUCLE DE JEU

	if (this->game_start == false)
	  {
	    this->turn_start = std::time(NULL);
	    this->game_start = true;
	  }

	//std::cout << "Team " << this->current_team_id_playing << " : ";
	this->turn_now = this->teams.at(this->current_team_id_playing).play_team(this->worms, this->device,
										 this->current_worm_id_playing, this->turn_start);
	this->turn_time_left = 60 - this->turn_now;
	//std::cout << "Time left : " << this->turn_time_left << std::endl;
	if (this->turn_time_left < 0)
	  {
	    if (this->current_team_id_playing < this->number_of_teams - 1)
		this->current_team_id_playing++;
	    else
	      {
		this->current_team_id_playing = 0;
		if (this->current_worm_id_playing < this->worms_per_team - 1)
		  this->current_worm_id_playing++;
		else
		  this->current_worm_id_playing = 0;
	      }
	    this->game_start = false;
	  }

	// FIN DE LA BOUCLE DE JEU
	this->driver->beginScene();
	this->smgr->drawAll();
	if (eventStatusMenu != EventStatus::IN_GAME_MENU && this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	  eventStatusMenu = EventStatus::IN_GAME_MENU;
	if (eventStatusMenu == EventStatus::IN_GAME_MENU)
	  {
	    eventStatusMenu = this->menuInGame->launchModel();
	    if (this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	      eventStatusMenu = EventStatus::STAND_BY;
	    else if (eventStatusMenu == EventStatus::QUIT || eventStatusMenu == EventStatus::BACK_TO_MENU)
	      break;
	  }
	this->driver->endScene();
      }
  return (eventStatusMenu);
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

void	GameNamespace::GameEngine::setModelProperties()
{
  this->mapGen();
  this->backgroundGen();
  this->teamsGen();
}

GameNamespace::GameMap::GameMap(int x, int y)
{
  this->terrain = GameNamespace::TerrainType::AIR;
  this->x = x;
  this->y = y;
}
