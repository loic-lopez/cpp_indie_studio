//
// GameEngine.hpp for GameEngine.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:17:30 2017 Stanislas Deneubourg
// Last update Tue Jun 13 17:32:08 2017 Stanislas Deneubourg
//

#ifndef	GAME_ENGINE_HPP__
#define GAME_ENGINE_HPP__

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <list>
#include "Interface/IModel.hpp"
#include "Model/MenuInGameModel.hpp"
#include "Worms/Team.hpp"

namespace	GameNamespace
{
  enum		class	TerrainType : uint16_t
    {
    AIR = 0,
    GROUND = 1,
    WORM = 2
    };
    
  struct	GameMap
  {
    int x;
    int y;
    TerrainType terrain;

    GameMap(int, int);
  };
  
  class	GameEngine : public IModel
  {
  private:
    std::vector<irr::scene::IMeshSceneNode *>		groundObjects;
    std::vector<irr::scene::IAnimatedMeshSceneNode *>	wormObjects;
    irr::scene::ICameraSceneNode			*gameCamera;
    std::vector<GameMap>				gameMap;
    std::vector<GameMap>				gameMap2;
    irr::scene::ISceneManager				*smgr;
    irr::video::IVideoDriver				*driver;
    irr::IrrlichtDevice					*device;
    irr::scene::IAnimatedMesh				*waterMesh;
    irr::scene::ISceneNode				*sea;
    std::string						fileTexture;
    std::string						wormTexture;
    std::string						fileShape;
    std::string						worm;
    const size_t					nbShapes;
    float						theFarthestMapPoint;
    std::list<btRigidBody *>				rigidBodyObjects;
    btDiscreteDynamicsWorld				*World;
    btDefaultCollisionConfiguration			*collisionConfiguration;
    btBroadphaseInterface				*broadphaseInterface;
    btCollisionDispatcher				*dispatcher;
    btSequentialImpulseConstraintSolver			*solver;


    //Génération de map
    int                                                 fillProbe;
    int							maxY;
    int                                                 r1Cutoff;
    int                                                 r2Cutoff;
    int                                                 sizeX;
    int                                                 sizeY;
    int                                                 generations;

    //Variables relatives à la boucle de jeu
    irr::u32						lastFrame;
    irr::f32						cameraMovementSpeed;
    irr::scene::IMeshSceneNode				*groundObject;
    EventReceiver					eventReceiver;
    std::unique_ptr<MenuInGame>				menuInGame;
    bool						playSound;
    bool						drawWalls;
    irr::f32						blockSize;
    irr::scene::ISceneNode				*skybox;
    irr::scene::ITerrainSceneNode			*backgroundTerrain;

    //Données des tours
    unsigned int					wormsPerTeam;
    unsigned int	       				numberOfHumanTeams;
    unsigned int			      		numberOfBotTeams;
    unsigned int					numberOfTeams;
    std::vector<Team>					teams;
    std::vector<irr::core::vector3df>			wormsRelativePos;
    unsigned int					currentWormIdPlaying;
    unsigned int					currentTeamIdPlaying;

    //Variables timer
    std::time_t						turnStart;
    double						turnNow;
    bool						gameStart;
    double						turnTimeLeft;
    double						timeBeforePause;
    double						timeBeforeSuddenDeath;
    std::time_t						timeBeforeSuddenDeathEndTurn;
    bool						isGamePaused;
    std::time_t						suddenDeathCooldown;
    double						suddenDeathTimeBeforePause;

    //Affichage timer
    irr::gui::IGUIEnvironment				*guienv;
    irr::gui::IGUISpriteBank				*spriteBank;
    irr::core::dimension2d<irr::u32>			timerSize;
    irr::core::dimension2du				screenSize;
    irr::gui::IGUISkin					*skin;
    irr::gui::IGUIFont					*font;
    
    
    virtual	void					setModelProperties();
    virtual	void					mapGen();
    virtual	void					backgroundGen();
    virtual	void					teamsGen();
    virtual	irr::core::vector3df			wormsPosGen();
    virtual	void					cameraMovements();
    virtual	void					setBlockProperties(int, int);
    virtual	void					triggerTimer();
    virtual 	void 					UpdatePhysics(irr::u32);
    virtual 	void 					UpdateRender(btRigidBody *);
    virtual 	void 					ClearObject();

   public:

    GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
	       const size_t &, const size_t &, irr::IrrlichtDevice *,
	       const bool &, const bool &,
	       const irr::s32 &, const irr::s32 &,
	       const irr::s32 &, const irr::s32 &, irrklang::ISound *mainSound, bool *playMainSound);

    virtual						~GameEngine();
    virtual EventStatus					launchModel();
  };
};


#endif
