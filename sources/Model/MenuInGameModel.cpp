/*
** MenuInGameModel.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameModel.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 16:18:52 2017 Yassir Jabbari
// Last update Wed May 31 14:41:26 2017 Stanislas Deneubourg
*/

#include "Model/MenuInGameModel.hpp"

MenuInGame::MenuInGame(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		       irr::scene::ISceneManager *smgr) :
	_device(device), _driver(driver), _smgr(smgr), event(device)
{
  this->_guienv = this->_device->getGUIEnvironment();
  this->_skin = this->_guienv->createSkin(irr::gui::EGST_BURNING_SKIN);
  this->_guienv->setSkin(this->_skin);
  this->_skin->drop();
  this->_font = this->_guienv->getFont("ressources/fonts/fonthaettenschweiler.bmp");
  if (this->_font)
    this->_guienv->getSkin()->setFont(this->_font);
  this->textuPlay = nullptr;
}

MenuInGame::~MenuInGame()
{
}

void MenuInGame::setModelProperties()
{
  const irr::core::dimension2du& screenSize = this->_driver->getScreenSize();

  this->tabCtrl = this->_guienv->addTabControl(irr::core::rect<int>((screenSize.Width / 2) - (500 / 2),
					       (screenSize.Height / 2) - (500 / 2), 950, 640), 0, false, false);
  this->exitButton = this->_guienv->addButton(irr::core::rect<int>(30, 295, 200, 324),
					      this->tabCtrl, 42, L"");
  this->textuExit = this->_driver->getTexture("ressources/images/exit.png");
  this->exitButton->setUseAlphaChannel(true);
  this->exitButton->setDrawBorder(false);
  this->exitButton->setImage(this->textuExit);
  this->playButton = this->_guienv->addButton(irr::core::rect<int>(30, 20, 200, 49),
					      this->tabCtrl, 1, L"");
  this->textuPlay = this->_driver->getTexture("ressources/images/play.png");
  this->playButton->setUseAlphaChannel(true);
  this->playButton->setDrawBorder(false);
  this->playButton->setImage(this->textuPlay);
  this->saveButton = this->_guienv->addButton(irr::core::rect<int>(30, 70, 200, 99), this->tabCtrl, 2, L"");
  this->textuSave = this->_driver->getTexture("ressources/images/save.png");
  this->saveButton->setUseAlphaChannel(true);
  this->saveButton->setDrawBorder(false);
  this->saveButton->setImage(this->textuSave);
  this->backToMenuButton = this->_guienv->addButton(irr::core::rect<int>(30, 120, 200, 149), this->tabCtrl, 3, L"");
  this->textuBackToMenu = this->_driver->getTexture("ressources/images/menu.png");
  this->backToMenuButton->setUseAlphaChannel(true);
  this->backToMenuButton->setDrawBorder(false);
  this->backToMenuButton->setImage(this->textuBackToMenu);
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  this->background = this->_driver->getTexture("ressources/images/MenuInGame.jpg");
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS,
					this->_driver->getTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS));
  this->event.setExitButton(this->exitButton);
}

EventStatus MenuInGame::launchModel()
{
  EventStatus 		event = EventStatus::IN_GAME_MENU;

  this->event.setEventStatus(event);
  this->_device->setEventReceiver(&this->event);
  this->setModelProperties();
  while (this->_device->run())
    {
      if (this->_device->isWindowActive())
	{
	  this->_driver->beginScene(false, true, irr::video::SColor(0, 0, 0, 0));
	  if (this->background != nullptr)
	    this->_driver->draw2DImage(this->background, irr::core::position2d<int>(0, 0));
	  if (event == EventStatus::BACK_TO_MENU || event == EventStatus::QUIT)
	    break;
	  this->_guienv->drawAll();
	  this->_driver->endScene();
	  if (event == EventStatus::ENTER_IN_GAME || this->event.IsKeyUp(irr::KEY_ESCAPE))
	    {
	      event = EventStatus::ENTER_IN_GAME;
	      break;
	    }
	}
    }
  this->_driver->removeAllTextures();
  this->_guienv->clear();
  return (event);
}

void MenuInGame::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}
