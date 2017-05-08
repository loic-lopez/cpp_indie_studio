//
// SplashScreen.cpp for SplashScreen.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:58:37 2017 Stanislas Deneubourg
// Last update Thu May  4 17:34:34 2017 Stanislas Deneubourg
//

#include "SplashScreen.hpp"

SplashScreen::SplashScreen(irr::scene::ISceneManager *smgr,
			   irr::video::IVideoDriver *driver,
			   irr::IrrlichtDevice *device)
{
  this->smgr = smgr;
  this->device = device;
  this->lastFrame = this->device->getTimer()->getTime();
  this->objectMovementSpeed = 50.0f;
  this->driver = driver;
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}

EventStatus SplashScreen::launchModel()
{
  while (this->device->run())
    if (this->device->isWindowActive())
      {
	const irr::u32 now = this->device->getTimer()->getTime();
	const irr::f32 frameDeltaTime = (irr::f32) (now - this->lastFrame) / 1000.0f;
	this->lastFrame = now;

	this->driver->beginScene(true, true, 0);


	// draw scene normally
	this->smgr->drawAll();

	//        env->drawAll();

	this->driver->endScene();
      }
  return (EventStatus::STAND_BY);
}

void SplashScreen::setModelProperties()
{
  this->irrlichtLogo = this->smgr->addAnimatedMeshSceneNode(
	  smgr->getMesh("ressources/splashscreen/irrlicht_logo_center.dae"));
}
