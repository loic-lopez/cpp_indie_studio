//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
//
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
//
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Wed Jun 14 14:14:34 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
				      const size_t &nbTextures, const size_t &nbShapes, irr::IrrlichtDevice *device,
				      const bool &playSound, const bool &drawWalls, const irr::s32 &botTeams,
				      const irr::s32 &humanTeams, const irr::s32 &teams, const irr::s32 &wormsInEachTeam,
				      irrklang::ISound *mainSound, bool *playMainSound,
				      irrklang::ISoundEngine *soundEngine) : smgr(smgr), driver(driver), device(device),
									     nbShapes(nbShapes), eventReceiver(device,
													       mainSound,
													       playMainSound),
									     menuInGame(new MenuInGame(this->device,
												       this->driver,
												       this->smgr,
												       this->eventReceiver)),
									     inventoryModel(new InventoryModel(this->device,
													       this->driver,
													       this->eventReceiver)),
									     playSound(playSound),
									     drawWalls(drawWalls)
{
  this->soundEngine = soundEngine;
  this->fileShape = "./ressources/shapes/Rock_0.dae";
  this->worm = "ressources/textures/Worm/Worm.b3d";
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
  this->suddenDeathTimeBeforePause = 0;
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
					     this->driver->getTexture(this->fileTexture.c_str()));
      this->groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->groundObject->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
      this->smgr->getMeshManipulator()->makePlanarTextureMapping(this->groundObject->getMesh(), 1.0f);
      this->groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
      irr::f32 minRadius = this->groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.70f;
      this->blockSize = minRadius;
      this->theFarthestMapPoint = this->sizeX * minRadius;
      this->groundObject->setPosition(irr::core::vector3df(x * minRadius, -y * (minRadius / 3), 0));
      this->groundObjects.push_back(this->groundObject);
      irr::core::vector3d<irr::f32>	*edge = new irr::core::vector3d<irr::f32>[8];
      irr::core::aabbox3d<irr::f32>	boundingBox = this->groundObject->getTransformedBoundingBox();
      boundingBox.getEdges(edge);
      this->terrainShapes.push_back(boundingBox);
      this->terrainBoundingBox.push_back(edge);
    }
}

EventStatus GameNamespace::GameEngine::launchModel()
{
  bool 		canFire = true;
  bool 		displayBullet = false;
  bool 		alreadyInMenu = false;
  EventStatus 	eventStatusMenu = EventStatus::STAND_BY;
  EventStatus 	eventStatusInventory = EventStatus::STAND_BY;
  irr::s32	lastFPS = -1;

  this->menuInGame->setModelProperties(); // Set des propriétés du menu ingame
  this->inventoryModel->setModelProperties();
  this->suddenDeathCooldown = std::time(nullptr);
  this->teams.at(this->currentTeamIdPlaying).showWormWeapon(this->currentWormIdPlaying, 1);
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

	if (this->eventReceiver.IsKeyDown(irr::KEY_SPACE))
	  {
	    canFire = this->teams.at(this->currentTeamIdPlaying).teamFire(this->currentWormIdPlaying, 1);
	    displayBullet = true;
	  }

	if (canFire || displayBullet)
	  displayBullet = this->teams.at(this->currentTeamIdPlaying)
		  .updateTeamWormBullets(this->currentWormIdPlaying, 1);

	// BOUCLE DE JEU

	if (!this->gameStart)
	  {
	    this->soundEngine->play2D("ressources/sounds/StartRound.wav");
	    this->turnStart = std::time(nullptr); // Set du timer a chaque tour
	    this->gameStart = true;
	  }

	this->turnNow = this->teams.at(this->currentTeamIdPlaying).turnOfThatTeam(this->currentWormIdPlaying, this->turnStart); // Revoie le temps écoulé depuis le début du tour

	// Bloquage du timer en cas de pause
	if (this->isGamePaused == false)
	  {
	    this->timeBeforeSuddenDeathEndTurn = std::time(nullptr);
	    this->turnTimeLeft = this->timeBeforePause - this->turnNow;
	    this->timeBeforeSuddenDeath = 600 - this->suddenDeathTimeBeforePause - (std::difftime(this->timeBeforeSuddenDeathEndTurn, this->suddenDeathCooldown));
	  }
	else if (this->isGamePaused == true)
	    {
	      this->turnTimeLeft = this->timeBeforePause;
	      //	    this->timeBeforeSuddenDeath = 600;
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
	    this->poisonEffect();
	    this->gameStart = false;
	    this->timeBeforePause = 59;
	  }

	// Fonctions de mouvements des worms
	
	if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_Q))
	  this->teams.at(this->currentTeamIdPlaying).teamResetAnimationSpeed(this->currentWormIdPlaying);
	if (this->eventReceiver.IsKeyDown(irr::KEY_KEY_Q))
	  this->teams.at(this->currentTeamIdPlaying).teamMoveLeft(this->currentWormIdPlaying, 1);
	else if (this->eventReceiver.IsKeyDown(irr::KEY_KEY_D))
	  this->teams.at(this->currentTeamIdPlaying).teamMoveRight(this->currentWormIdPlaying, 1);
	if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_D))
	  this->teams.at(this->currentTeamIdPlaying).teamResetAnimationSpeed(this->currentWormIdPlaying);
	  

	// FIN DE LA BOUCLE DE JEU
	this->driver->beginScene();
	this->smgr->drawAll();
	this->triggerTimer();
	if (eventStatusInventory != EventStatus::INVENTORY
	    && eventStatusMenu != EventStatus::IN_GAME_MENU && this->eventReceiver.IsKeyUp(irr::KEY_KEY_I) && !alreadyInMenu)
	  {
	    this->inventoryModel->showTabCtrl();
	    eventStatusInventory = EventStatus::INVENTORY;
	    alreadyInMenu = true;
	  }
	else if (eventStatusMenu != EventStatus::IN_GAME_MENU
	    && eventStatusInventory != EventStatus::INVENTORY && this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE) && !alreadyInMenu)
	  {
	    eventStatusMenu = EventStatus::IN_GAME_MENU;
	    this->menuInGame->showTabCtrl();
	    this->isGamePaused = true;
	    alreadyInMenu = true;
	    this->timeBeforePause = this->turnTimeLeft;
	  }
	if (eventStatusInventory == EventStatus::INVENTORY && eventStatusMenu != EventStatus::IN_GAME_MENU)
	  {
	    this->inventoryModel->launchModel();
	    if (this->eventReceiver.IsKeyUp(irr::KEY_KEY_I))
	      {
		eventStatusInventory = EventStatus::STAND_BY;
		eventStatusMenu = EventStatus::STAND_BY;
		this->inventoryModel->hideTabCtrl();
		alreadyInMenu = false;
	      }
	  }
	else if (eventStatusMenu == EventStatus::IN_GAME_MENU && eventStatusInventory != EventStatus::INVENTORY)
	  {
	    eventStatusMenu = this->menuInGame->launchModel();
	    if (this->eventReceiver.IsKeyUp(irr::KEY_ESCAPE))
	      {
		eventStatusMenu = EventStatus::STAND_BY;
		eventStatusInventory = EventStatus::STAND_BY;
		this->isGamePaused = false;
		this->turnStart = std::time(nullptr);
		this->suddenDeathCooldown = std::time(nullptr);
		this->timeBeforeSuddenDeathEndTurn = std::time(nullptr);
		this->suddenDeathTimeBeforePause = 600 - this->timeBeforeSuddenDeath;
		alreadyInMenu = false;
		this->menuInGame->hideTabCtrl();
	      }
	    else if (eventStatusMenu == EventStatus::BACK_TO_GAME)
		{
		  this->isGamePaused = false;
		  this->turnStart = std::time(nullptr);
		  this->suddenDeathCooldown = std::time(nullptr);
		  this->timeBeforeSuddenDeathEndTurn = std::time(nullptr);
		  this->suddenDeathTimeBeforePause = 600 - this->timeBeforeSuddenDeath;
		  alreadyInMenu = false;
		  this->menuInGame->hideTabCtrl();
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
