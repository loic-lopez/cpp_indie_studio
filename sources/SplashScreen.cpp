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
  this->driver->removeAllTextures();
  this->smgr->clear();
}

void SplashScreen::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}

EventStatus SplashScreen::launchModel()
{
  irr::u32	alphaColor = 255;
  irr::core::dimension2d<irr::u32> irrlichLogoSize = this->irrlichtLogo->getSize();
  irr::core::dimension2d<irr::u32> irrklangLogoSize = this->irrklangLogo->getSize();
  irr::core::dimension2d<irr::u32> screenSize = this->driver->getScreenSize();


  while (this->device->run())
    if (this->device->isWindowActive())
      {
	const irr::u32 now = this->device->getTimer()->getTime();
	const auto frameDeltaTime = (now - this->lastFrame);
	this->lastFrame = now;

	if (alphaColor == 0)
	  break;

	if (frameDeltaTime == 2)
	  alphaColor--;

	this->driver->enableMaterial2D();
	this->driver->beginScene(true, true, 0);

	this->driver->draw2DImage(this->irrlichtLogo,
				  irr::core::vector2d<irr::s32>(
					  (screenSize.Width / 2) - ((irrlichLogoSize.Width / 2) * 3),
					  (screenSize.Height / 2) - (irrlichLogoSize.Height / 2)),
				  irr::core::rect<irr::s32>(0,0, irrlichLogoSize.Width,irrlichLogoSize.Height), nullptr,
				  irr::video::SColor(alphaColor, 255, 255, 255), false);


	this->driver->draw2DImage(this->irrklangLogo,
				  irr::core::vector2d<irr::s32>(
					  (screenSize.Width / 2) + ((irrklangLogoSize.Width / 2)),
					  (screenSize.Height / 2) - (irrklangLogoSize.Height / 2)),
				  irr::core::rect<irr::s32>(0,0, irrklangLogoSize.Width,irrklangLogoSize.Height), nullptr,
				  irr::video::SColor(alphaColor, 255, 255, 255), false);
	if (this->font != nullptr)
	  {
	    this->font->draw("Powered By:",
			     irr::core::rect<irr::s32>(screenSize.Width / 2, (screenSize.Height / 2) - irrlichLogoSize.Height, 300, 300),
			     irr::video::SColor(alphaColor, 255, 255, 255));
	  }
	this->driver->enableMaterial2D(false);
	this->driver->endScene();
      }
  return (EventStatus::STAND_BY);
}

void SplashScreen::setModelProperties()
{
  this->irrlichtLogo = this->driver->getTexture("ressources/splashscreen/irrlicht_logo.png");
  this->irrklangLogo = this->driver->getTexture("ressources/splashscreen/irrklang_logo.png");
  this->font = this->device->getGUIEnvironment()->getFont("ressources/fonts/fonthaettenschweiler.bmp");
}
