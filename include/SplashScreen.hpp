//
// SplashScreen.hpp for SplashScreen.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:56:42 2017 Stanislas Deneubourg
// Last update Thu May  4 17:02:22 2017 Stanislas Deneubourg
//

#ifndef	SPLASH_SCREEN_HPP__
#define SPLASH_SCREEN_HPP__

#include "IModel.hpp"

class	SplashScreen : public IModel
{
public:
  SplashScreen();
  virtual	~SplashScreen();
  virtual void	init();
  virtual void	setModelProperties(int, int);
};

#endif
