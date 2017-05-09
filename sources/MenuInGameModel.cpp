/*
** MenuInGameModel.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameModel.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 16:18:52 2017 Yassir Jabbari
** Last update Mon May 08 16:18:52 2017 Yassir Jabbari
*/

#include "MenuInGameModel.hpp"

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
}

MenuInGame::~MenuInGame()
{
}

void MenuInGame::setModelProperties()
{
  const irr::s32 leftX = 260;
  this->tabCtrl = this->_guienv->addTabControl(irr::core::rect<int>(leftX, 10, 512 - 10, 384 - 10),
					       0, true, true);
  this->_smgr->addCameraSceneNode(0, irr::core::vector3df(45, 0, 0), irr::core::vector3df(0, 0, 10));
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  this->background = this->_driver->getTexture("ressources/images/MenuInGame.jpg");
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS,
					this->_driver->getTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS));
}

#include <iostream>

EventStatus MenuInGame::launchModel()
{
  EventStatus eventStatus = EventStatus::STAND_BY;

  this->_device->setEventReceiver(&this->event);
  while (this->_device->run())
    {
      if (this->_device->isWindowActive())
	{
	  this->_driver->beginScene(false, true, irr::video::SColor(0, 0, 0, 0));
	  if (this->background != nullptr)
	    this->_driver->draw2DImage(this->background, irr::core::position2d<int>(0, 0));
	  if (eventStatus == EventStatus::BACK_TO_MENU || eventStatus == EventStatus::QUIT)
	    break;
	  this->_guienv->drawAll();
	  this->_driver->endScene();
	}
    }
  return (eventStatus);
}

void MenuInGame::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}
