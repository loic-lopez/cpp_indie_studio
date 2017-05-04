//
// GameEngine.hpp for GameEngine.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:17:30 2017 Stanislas Deneubourg
// Last update Thu May  4 18:06:00 2017 Stanislas Deneubourg
//

#ifndef	GAME_ENGINE_HPP__
#define GAME_ENGINE_HPP__

#include <vector>
#include <string>
#include "IModel.hpp"

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
    int	x;
    int	y;
    TerrainType terrain;
  };
  
  class	GameEngine : public IModel
  {
  private:
    std::vector<irr::scene::IAnimatedMeshSceneNode *>	groundObjects;
    irr::SKeyMap					cameraActions[6];
    irr::scene::ICameraSceneNode			*gameCamera;
    std::vector<GameMap>				gameMap;
    irr::scene::ISceneManager				*smgr;
    irr::video::IVideoDriver				*driver;
    std::string						file_texture;
    std::string						file_shape;
    const size_t					nb_shapes;
    float						old_pos;
    float						initialCameraPositionX;
    float						initialCameraPositionY;
    
  
  public:
    GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
	       const size_t &, const size_t &);
    virtual	~GameEngine() {};
    virtual void	setModelProperties(int, int);
  };
};


#endif
