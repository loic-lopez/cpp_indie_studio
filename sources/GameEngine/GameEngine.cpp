//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Wed Jun  7 17:24:29 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
				      const size_t &nbTextures, const size_t &nbShapes, irr::IrrlichtDevice *device,
				      const bool &playSound, const bool &drawWalls, const irr::s32 &botTeams,
				      const irr::s32 &humanTeams, const irr::s32 &teams, const irr::s32 &wormsInEachTeam,
				      irrklang::ISound *mainSound, bool *playMainSound) : smgr(smgr), driver(driver),
											  device(device),
											  nbShapes(nbShapes),
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
  this->fileShape = "./ressources/shapes/Rock_0.dae";
  this->worm = "ressources/textures/Worm/Worm.obj";
  this->lastFrame = this->device->getTimer()->getTime();
  this->device->setEventReceiver(&this->eventReceiver);
  this->cameraMovementSpeed = 50.0f;
  this->generations = 5;
  this->sizeX = 40;
  this->sizeY = 40;
  this->fillProbe = (std::rand() % 21) + 30;
  this->r1Cutoff = 3;
  this->r2Cutoff = 2;
  this->fileTexture = "./ressources/textures/ground/ground" + std::to_string(std::rand() % nbTextures) + ".bmp";
  this->wormTexture = "./ressources/textures/Worm/WormTextures.png";
  this->maxY = this->sizeY * (-1);
  this->wormsPerTeam = wormsInEachTeam;
  this->numberOfHumanTeams = humanTeams;
  this->numberOfBotTeams = botTeams;
  this->numberOfTeams = teams;
  this->currentWormIdPlaying = 0;
  this->currentTeamIdPlaying = 0;
  this->timeBeforePause = 60;
  this->timeBeforeSuddenDeath = 600;
  this->timeBeforeSuddenDeathEndTurn = this->timeBeforeSuddenDeath;
  this->isGamePaused = false;
  this->gameStart = false;
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
  this->groundObject = this->smgr->addMeshSceneNode(smgr->getMesh(this->fileShape.c_str()));
  if (this->groundObject != nullptr)
    {
      this->groundObject->setMaterialTexture(0,
					     this->driver->getTexture(this->fileTexture.c_str())); // set diffuse texture
      this->groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
      this->smgr->getMeshManipulator()->makePlanarTextureMapping(this->groundObject->getMesh(), 1.0f);
      this->groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
      irr::f32 minRadius = this->groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.70f;
      this->blockSize = minRadius;
      this->theFarthestMapPoint = this->sizeX * minRadius;
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

	if (!this->gameStart)
	  {
	    this->turnStart = std::time(nullptr); // Set du timer a chaque tour
	    this->gameStart = true;
	  }
        
	this->turnNow = this->teams.at(this->currentTeamIdPlaying).turnOfThatTeam(this->currentWormIdPlaying, this->turnStart); // Revoie le temps écoulé depuis le début du tour

	// Bloquage du timer en cas de pause
	if (this->isGamePaused == false)
	  {
	    this->turnTimeLeft = this->timeBeforePause - this->turnNow;
	    this->timeBeforeSuddenDeath = this->timeBeforeSuddenDeathEndTurn - turnTimeLeft;
	  }
	else if (this->isGamePaused == true)
	  {
	    this->turnTimeLeft = this->timeBeforePause;
	    this->timeBeforeSuddenDeath = this->timeBeforeSuddenDeathEndTurn - turnTimeLeft;
	  }

	// Si le temps est écoulé, au joueur suivant de jouer
	if (this->turnTimeLeft < 0)
	  {
	    if (this->currentTeamIdPlaying < this->numberOfTeams - 1)
		this->currentTeamIdPlaying++;
	    else
	      {
		this->currentTeamIdPlaying = 0;
		if (this->currentWormIdPlaying < this->wormsPerTeam - 1)
		  this->currentWormIdPlaying++;
		else
		  this->currentWormIdPlaying = 0;
	      }
	    this->gameStart = false;
	    this->timeBeforePause = 60;
	    this->timeBeforeSuddenDeathEndTurn -= this->timeBeforePause;
	  }

	// Fonctions de mouvements des worms
	if (this->eventReceiver.IsKeyDown(irr::KEY_KEY_Q))
	  this->teams.at(this->currentTeamIdPlaying).teamMoveLeft(this->currentWormIdPlaying, this->device);
	else if (this->eventReceiver.IsKeyDown(irr::KEY_KEY_D))
	  this->teams.at(this->currentTeamIdPlaying).teamMoveRight(this->currentWormIdPlaying, this->device);
	
	// FIN DE LA BOUCLE DE JEU
	this->driver->beginScene();
	this->smgr->drawAll();
	if (this->spriteBank->getTexture(0) != nullptr)
	  {
	    int			turnTimeLeftToInt = std::round(this->turnTimeLeft);	// Affichage du timer du tour
	    int			timeBeforeSuddenDeathToInt = std::round(this->timeBeforeSuddenDeath); // Affichage du timer de mort subite
	    std::string		stringTurnTimer = std::to_string(turnTimeLeftToInt);
	    std::string		stringSuddenDeathTime;

	    if (this->timeBeforeSuddenDeath > 60)
	      {
		if ((60 - (timeBeforeSuddenDeathToInt % 60)) == 60)
		  {
		    stringSuddenDeathTime = std::to_string((timeBeforeSuddenDeathToInt / 60) + 1);
		    stringSuddenDeathTime += ":";
		    stringSuddenDeathTime += "00";
		  }
		else if ((60 - (timeBeforeSuddenDeathToInt % 60)) < 10)
		  {
		    stringSuddenDeathTime = std::to_string(timeBeforeSuddenDeathToInt / 60);
		    stringSuddenDeathTime += ":";
		    stringSuddenDeathTime += "0";
		    stringSuddenDeathTime += std::to_string(60 - (timeBeforeSuddenDeathToInt % 60));
		  }
		else
		  {
		    stringSuddenDeathTime = std::to_string(timeBeforeSuddenDeathToInt / 60);
		    stringSuddenDeathTime += ":";
		    stringSuddenDeathTime += std::to_string(60 - (timeBeforeSuddenDeathToInt % 60));
		  }	
	      }
	    else
	      stringSuddenDeathTime += std::to_string(60 - (timeBeforeSuddenDeathToInt % 60));

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
	if (eventStatusMenu != EventStatus::IN_GAME_MENU && this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	  {
	    eventStatusMenu = EventStatus::IN_GAME_MENU;
	    this->isGamePaused = true;
	    this->timeBeforePause = this->turnTimeLeft;
	  }
	if (eventStatusMenu == EventStatus::IN_GAME_MENU)
	  {
	    eventStatusMenu = this->menuInGame->launchModel();
	    if (this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	      {
		eventStatusMenu = EventStatus::STAND_BY;
		this->isGamePaused = false;
		this->turnStart = std::time(nullptr);
	      }
	    else if (eventStatusMenu == EventStatus::BACK_TO_GAME)
	      {
		this->isGamePaused = false;
                this->turnStart = std::time(nullptr);
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
