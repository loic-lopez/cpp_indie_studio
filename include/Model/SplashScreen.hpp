//
// SplashScreen.hpp for SplashScreen.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:56:42 2017 Stanislas Deneubourg
// Last update Wed May 31 14:37:58 2017 Stanislas Deneubourg
//

#ifndef	SPLASH_SCREEN_HPP__
#define SPLASH_SCREEN_HPP__

#include "Interface/IModel.hpp"

class	SplashScreen : public IModel
{
 private:
  irr::scene::ISceneManager 		*smgr;
  irr::video::IVideoDriver 		*driver;
  irr::IrrlichtDevice 			*device;
  irr::u32 				lastFrame;
  irr::f32 				objectMovementSpeed;
  irr::video::ITexture			*irrlichtLogo;
  irr::video::ITexture			*irrklangLogo;
  irr::scene::ITextSceneNode		*textSceneNode;
  irr::gui::IGUIFont			*font;

 public:
  SplashScreen(irr::scene::ISceneManager *smgr,
	       irr::video::IVideoDriver *driver,
	       irr::IrrlichtDevice *device);
  virtual	~SplashScreen();
  virtual void setBlockProperties(int, int);

  virtual EventStatus launchModel();
  virtual void setModelProperties();
};

#endif
