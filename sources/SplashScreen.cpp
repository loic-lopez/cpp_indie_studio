//
// SplashScreen.cpp for SplashScreen.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:58:37 2017 Stanislas Deneubourg
// Last update Mon May  8 19:59:25 2017 Loic Lopez
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

#include <iostream>

EventStatus SplashScreen::launchModel()
{
  irr::u32	alphaColorText = 0;
  irr::u32	alphaColorIrrlichtLogo = 0;
  irr::u32	alphaColorIrrKlangLogo = 0;
  bool 		displayIrrlicht = true;
  bool 		displayIrrKlang = false;
  bool 		mustDecrement = false;
  irr::core::dimension2d<irr::u32> irrlichLogoSize = this->irrlichtLogo->getSize();
  irr::core::dimension2d<irr::u32> irrklangLogoSize = this->irrklangLogo->getSize();
  irr::core::dimension2d<irr::u32> screenSize = this->driver->getScreenSize();
  irr::core::dimension2d<irr::u32> textSize = this->font->getDimension(reinterpret_cast<const wchar_t *>("Powered By:"));

  while (this->device->run())
    if (this->device->isWindowActive())
      {
	const irr::u32 now = this->device->getTimer()->getTime();
	const irr::u32 frameDeltaTime = (now - this->lastFrame);
	this->lastFrame = now;

	if (alphaColorIrrlichtLogo <= 255 && mustDecrement && frameDeltaTime >= 1 && displayIrrlicht)
	  {
	    alphaColorIrrlichtLogo--;
	    if (alphaColorIrrlichtLogo == 0)
	      {
		displayIrrlicht = false;
		displayIrrKlang = true;
		mustDecrement = false;
	      }
	  }
	else if (frameDeltaTime >= 3 && displayIrrlicht)
	  {
	      alphaColorText++;
	      alphaColorIrrlichtLogo++;
	      if (alphaColorIrrlichtLogo == 255)
		mustDecrement = true;
	  }

	if (alphaColorIrrKlangLogo <= 255 && mustDecrement && frameDeltaTime >= 1 && displayIrrKlang)
	  {
	    alphaColorIrrKlangLogo--;
	    alphaColorText--;
	    if (alphaColorIrrKlangLogo == 0)
	      break;
	  }
	else if (frameDeltaTime >= 3 && displayIrrKlang)
	  {
	    alphaColorIrrKlangLogo++;
	    if (alphaColorIrrKlangLogo == 255)
	      mustDecrement = true;
	  }


	this->driver->enableMaterial2D();
	this->driver->beginScene(true, true, 0);

	if (displayIrrlicht)
		this->driver->draw2DImage(this->irrlichtLogo,
				  irr::core::vector2d<irr::s32>((screenSize.Width / 2) - (irrlichLogoSize.Width / 2),
					  (screenSize.Height / 2) - (irrlichLogoSize.Height / 2)),
				  irr::core::rect<irr::s32>(0,0, irrlichLogoSize.Width,irrlichLogoSize.Height), nullptr,
				  irr::video::SColor(alphaColorIrrlichtLogo, 255, 255, 255), false);

	if (displayIrrKlang)
	  this->driver->draw2DImage(this->irrklangLogo,
				  irr::core::vector2d<irr::s32>((screenSize.Width / 2) - ((irrklangLogoSize.Width / 2)),
					  (screenSize.Height / 2) - (irrklangLogoSize.Height / 2)),
				  irr::core::rect<irr::s32>(0,0, irrklangLogoSize.Width,irrklangLogoSize.Height), nullptr,
				  irr::video::SColor(alphaColorIrrKlangLogo, 255, 255, 255), false);
	if (this->font != nullptr)
	  {
	    this->font->draw("Powered By:",
			     irr::core::rect<irr::s32>((screenSize.Width / 2) - ((textSize.Width / 2) * 1.30f),
						       ((screenSize.Height / 2) - irrlichLogoSize.Height) - (textSize.Height * 2), 300, 300),
			     irr::video::SColor(alphaColorText, 255, 255, 255));
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
  this->font = this->device->getGUIEnvironment()->getFont("ressources/fonts/SplashScreen.xml");
}
