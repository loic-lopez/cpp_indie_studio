//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Wed Jun  7 12:01:30 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
				      const size_t &nb_textures, const size_t &nb_shapes, irr::IrrlichtDevice *device,
				      const bool &playSound, const bool &drawWalls, const irr::s32 &bot_teams,
				      const irr::s32 &human_teams, const irr::s32 &teams, const irr::s32 &worms_in_each_team,
				      irrklang::ISound *mainSound, bool *playMainSound) : smgr(smgr), driver(driver),
											  device(device),
												nb_shapes(nb_shapes),
												eventReceiver(device,
													      mainSound,
													      playMainSound),
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
  this->time_before_pause = 60;
  this->time_before_sudden_death = 600;
  this->time_before_sudden_death_end_turn = this->time_before_sudden_death;
  this->is_game_paused = false;
  this->game_start = false;
  this->guienv = this->device->getGUIEnvironment();
  this->screenSize = this->driver->getScreenSize();
  this->skin = this->guienv->createSkin(irr::gui::EGST_WINDOWS_METALLIC);
  this->guienv->setSkin(this->skin);
  this->skin->drop();
  this->font = this->guienv->getFont("ressources/fonts/SoftMarshmallow.png");
  if (this->font != nullptr)
    this->guienv->getSkin()->setFont(this->font);
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

  this->menuInGame->setModelProperties(); // Set des propriétés du menu ingame
  while(this->device->run())
    if (this->device->isWindowActive())
      {
	// Affichage des FPS et du driver choisi
	
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

	if (!this->game_start)
	  {
	    this->turn_start = std::time(nullptr); // Set du timer a chaque tour
	    this->game_start = true;
	  }
        
	this->turn_now = this->teams.at(this->current_team_id_playing).turn_of_that_team(this->current_worm_id_playing, this->turn_start); // Revoie le temps écoulé depuis le début du tour

	// Bloquage du timer en cas de pause
	if (this->is_game_paused == false)
	  {
	    this->turn_time_left = this->time_before_pause - this->turn_now;
	    this->time_before_sudden_death = this->time_before_sudden_death_end_turn - turn_time_left;
	  }
	else if (this->is_game_paused == true)
	  {
	    this->turn_time_left = this->time_before_pause;
	    this->time_before_sudden_death = this->time_before_sudden_death_end_turn - turn_time_left;
	  }

	// Si le temps est écoulé, au joueur suivant de jouer
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
	    this->time_before_pause = 60;
	    this->time_before_sudden_death_end_turn -= turn_time_left;
	  }

	// Fonctions de mouvements des worms
	if (this->eventReceiver.IsKeyDown(irr::KEY_KEY_Q))
	  this->teams.at(this->current_team_id_playing).team_move_left(this->current_worm_id_playing, this->device);
	else if (this->eventReceiver.IsKeyDown(irr::KEY_KEY_D))
	  this->teams.at(this->current_team_id_playing).team_move_right(this->current_worm_id_playing, this->device);
	
	// FIN DE LA BOUCLE DE JEU
	this->driver->beginScene();
	this->smgr->drawAll();
	if (this->spriteBank->getTexture(0) != nullptr)
	  {
	    int			turn_time_left_to_int = std::round(this->turn_time_left);	// Affichage du timer du tour
	    int			time_before_sudden_death_to_int = std::round(this->time_before_sudden_death); // Affichage du timer de mort subite
	    std::string		string_turn_timer = std::to_string(turn_time_left_to_int);
	    std::string		string_sudden_death_time;

	    if (this->time_before_sudden_death > 60)
	      {
		string_sudden_death_time = std::to_string(time_before_sudden_death_to_int / 60);
		string_sudden_death_time += ":";
		string_sudden_death_time += std::to_string(60 - (time_before_sudden_death_to_int % 60));
	      }
	    else
	      string_sudden_death_time = std::to_string(time_before_sudden_death_to_int % 60);
	    std::cout << string_sudden_death_time << std::endl;		
	    this->spriteBank->draw2DSprite(irr::u32(0),
					   irr::core::position2di(this->screenSize.Width * 9 / 10,
								  this->screenSize.Height * 9 / 10),
					   nullptr,
					   irr::video::SColor(255, 255, 255, 255), 0);

	    // Affichage des deux timers dans la box
	    
	    if (this->turn_time_left > 10)
	      this->font->draw(string_turn_timer.c_str(),
			       irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 30,
							 this->screenSize.Height * 9 / 10 + 30,
							 this->screenSize.Width * 9 / 10 + 60,
							 this->screenSize.Height * 9 / 10 + 60),
			       irr::video::SColor(255, 255, 190, 0));
	    else
	      this->font->draw(string_turn_timer.c_str(),
                               irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 30,
                                                         this->screenSize.Height * 9 / 10 + 30,
                                                         this->screenSize.Width * 9 / 10 + 60,
                                                         this->screenSize.Height * 9 / 10 + 60),
                               irr::video::SColor(255, 255, 0, 0));
	    if (this->time_before_sudden_death > 60)
              this->font->draw(string_sudden_death_time.c_str(),
                               irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 5,
                                                         this->screenSize.Height * 9 / 10 + 5,
                                                         this->screenSize.Width * 9 / 10 + 25,
                                                         this->screenSize.Height * 9 / 10 + 25),
                               irr::video::SColor(255, 255, 190, 0));
            else
              this->font->draw(string_sudden_death_time.c_str(),
                               irr::core::rect<irr::s32>(this->screenSize.Width * 9 / 10 + 5,
                                                         this->screenSize.Height * 9 / 10 + 5,
                                                         this->screenSize.Width * 9 / 10 + 25,
                                                         this->screenSize.Height * 9 / 10 + 25),
                               irr::video::SColor(255, 255, 0, 0));
	  }
	if (eventStatusMenu != EventStatus::IN_GAME_MENU && this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	  {
	    eventStatusMenu = EventStatus::IN_GAME_MENU;
	    this->is_game_paused = true;
	    this->time_before_pause = this->turn_time_left;
	  }
	if (eventStatusMenu == EventStatus::IN_GAME_MENU)
	  {
	    eventStatusMenu = this->menuInGame->launchModel();
	    if (this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	      {
		eventStatusMenu = EventStatus::STAND_BY;
		this->is_game_paused = false;
		this->turn_start = std::time(nullptr);
	      }
	    else if (eventStatusMenu == EventStatus::BACK_TO_GAME)
	      {
		this->is_game_paused = false;
                this->turn_start = std::time(nullptr);
	      }
	    else if (eventStatusMenu == EventStatus::QUIT || eventStatusMenu == EventStatus::BACK_TO_MENU)
	      break;
	  }
	this->driver->endScene();
      }
  return (eventStatusMenu);
}

void	GameNamespace::GameEngine::setModelProperties()
{
  irr::video::ITexture		*timer;
  
  if (this->guienv->getSpriteBank(irr::io::path("ressources")) == nullptr)
    this->spriteBank = this->guienv->addEmptySpriteBank(irr::io::path("ressources"));
  else
    this->spriteBank = this->guienv->getSpriteBank(irr::io::path("ressources"));
  timer = this->driver->getTexture("ressources/images/timer.png");
  if (timer != nullptr)
    {
      this->timerSize = timer->getSize();
      this->spriteBank->addTextureAsSprite(timer);
    }
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
