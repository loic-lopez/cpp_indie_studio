//
// GameEngine.hpp for GameEngine.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:17:30 2017 Stanislas Deneubourg
// Last update Thu May  4 13:49:17 2017 Stanislas Deneubourg
//

#ifndef	GAME_ENGINE_HPP__
#define GAME_ENGINE_HPP__

#include <vector>
#include <string>
#include "IModel.hpp"

class	GameEngine : public IModel
{
private:
  std::vector<irr::scene::IAnimatedMeshSceneNode *>	groundObjects;
  irr::SKeyMap						cameraActions[4];
  irr::scene::ICameraSceneNode				*gameCamera;
  
public:
  GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
  virtual	~GameEngine() {};
  virtual void	setModelProperties();
};


#endif
