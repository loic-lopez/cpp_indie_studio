//
// GameEngine.hpp for GameEngine.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:17:30 2017 Stanislas Deneubourg
// Last update Fri May  5 19:55:18 2017 Stanislas Deneubourg
//

#ifndef	GAME_ENGINE_HPP__
#define GAME_ENGINE_HPP__

#include <vector>
#include <string>
#include <cstdlib>
#include "IModel.hpp"
#include "EventReceiver.hpp"
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
    bool isStart;
    bool isEnd;

    GameMap(int, int);
  };
  
  class	GameEngine : public IModel
  {
  private:
    std::vector<irr::scene::IMeshSceneNode *> groundObjects;
    irr::scene::ICameraSceneNode			*gameCamera;
    std::vector<GameMap>				gameMap;
    irr::scene::ISceneManager				*smgr;
    irr::video::IVideoDriver				*driver;
    irr::IrrlichtDevice *device;
    std::string						file_texture;
    std::string						file_shape;
    const size_t					nb_shapes;
    float old_pos_x;
    std::vector<float>			       		max_pos_x_tab;
    float						final_pos_x_avg;
    float the_farthest_map_point_x;
    irr::u32						lastFrame;
    irr::f32						cameraMovementSpeed;
    EventReceiver					receiver;
    size_t maxNumberPlatforms;
    irr::scene::IMeshSceneNode *groundObject;
    IModel						*menuInGame;

    virtual void setBlockProperties(int, int);
  
  public:
    GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
	       const size_t &, const size_t &, irr::IrrlichtDevice *);

    virtual                        ~GameEngine()
    {};

    virtual EventStatus launchModel();

    virtual void setModelProperties();
  };
};


#endif
