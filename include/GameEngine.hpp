//
// GameEngine.hpp for GameEngine.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:17:30 2017 Stanislas Deneubourg
// Last update Wed May  3 18:23:54 2017 Stanislas Deneubourg
//

#ifndef	GAME_ENGINE_HPP__
#define GAME_ENGINE_HPP__

#include "IModel.hpp"

class	GameEngine : public IModel
{
public:
  GameEngine();
  virtual	~GameEngine() {};
  virtual void	init();
  virtual void	setModelProperties();
};


#endif
