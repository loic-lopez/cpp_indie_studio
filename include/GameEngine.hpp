//
// GameEngine.hpp for GameEngine.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:17:30 2017 Stanislas Deneubourg
// Last update Wed May 10 18:02:27 2017 Stanislas Deneubourg
//

#ifndef	GAME_ENGINE_HPP__
#define GAME_ENGINE_HPP__

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include "IModel.hpp"
#include "MenuInGameModel.hpp"

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
    irr::scene::IAnimatedMesh				*water_mesh;
    irr::scene::ISceneNode				*sea;
    std::string						file_texture;
    std::string						worm_texture;
    std::string						file_shape;
    std::string						worm;
    const size_t					nb_shapes;
    float						the_farthest_map_point;
    int                                                 fillProbe;
    int							max_y;
    int                                                 r1_cutoff;
    int                                                 r2_cutoff;
    int                                                 size_x;
    int                                                 size_y;
    int                                                 generations;
    irr::u32						lastFrame;
    irr::f32						cameraMovementSpeed;
    EventReceiver					receiver;
    irr::scene::IMeshSceneNode				*groundObject;
    irr::scene::IAnimatedMeshSceneNode			*worms;
    std::unique_ptr<IModel>				menuInGame;
    bool						playSound;
    bool						drawWalls;
    irr::scene::ISceneNode				*skybox;
    irr::scene::ITerrainSceneNode			*backgroundTerrain;

    virtual void setModelProperties();
    virtual void setWorms();

    virtual void setBlockProperties(int, int);
   public:

    GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
	       const size_t &, const size_t &, irr::IrrlichtDevice *,
	       const bool &, const bool &);

    virtual                        ~GameEngine();

    virtual EventStatus launchModel();
  };
};


#endif
