/*
** MenuController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:52:58 2017 Yassir Jabbari
// Last update Sat May  6 18:23:22 2017 Jabbari Yassir
*/

#include "MenuModel.hpp"

MenuModel::MenuModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr, irr::gui::IGUIEnvironment *guienv, std::vector<std::string> saves)
  : _device(device), _driver(driver), _smgr(smgr),_guienv(guienv), event(device), _saves(saves)
{
  irr::core::stringw str = "Worms 3D";
  this->_device->setWindowCaption(str.c_str());
  this->_device->setEventReceiver(&this->event);
  this->skin = this->_guienv->createSkin(irr::gui::EGST_BURNING_SKIN);
  this->_guienv->setSkin(this->skin);
  this->skin->drop();
  this->font = this->_guienv->getFont("ressources/fonts/fonthaettenschweiler.bmp");
  if (this->font)
    this->_guienv->getSkin()->setFont(this->font);
}

MenuModel::~MenuModel()
{
}

void	MenuModel::setModelProperties()
{
  const wchar_t *text2 = L"Created by :\n"	  \
    L"DENEUBOURG Stanislas,\n"			  \
    L"DUPIL Loïc,\n"				  \
    L"GIANGIACOMI Jade,\n"			  \
    L"JABBARI Yassir,\n"			  \
    L"LOPEZ Loîc.";
  const irr::s32 leftX = 260;

  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(leftX, 10, 512 - 10, 384 - 10),
					       0, true, true);
  this->mainCtrl = this->tabctrl->addTab(L"Menu");
  this->aboutTab = this->tabctrl->addTab(L"About");
  this->boxSave = this->_guienv->addListBox(irr::core::rect<int>(10, 10, 220, 120),
					    this->mainCtrl, 1);
  this->boxSave->addItem(L"Create new game");
  this->boxSave->setSelected(this->selected);
  this->event.setSelected(this->selected);
  this->startButton = this->_guienv->addButton(irr::core::rect<int>(30, 295, 200, 324), this->mainCtrl, 2, L"Play");
  this->optionButton = this->_guienv->addButton(irr::core::rect<int>(30, 254, 200, 283), this->mainCtrl, 21, L"Option");
  this->exitButton = this->_guienv->addButton(irr::core::rect<int>(30, 213, 200, 242), this->mainCtrl, 42, L"Exit");
  this->_guienv->addStaticText(text2, irr::core::rect<int>(10, 10, 230, 320),
			       true, true, this->aboutTab);
  this->_smgr->addCameraSceneNode(0, irr::core::vector3df(45, 0, 0), irr::core::vector3df(0, 0, 10));
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  this->background = this->_driver->getTexture("ressources/images/181192.jpg");
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, this->_driver->getTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS));
  this->event.setStartButton(this->startButton);
  this->event.setOptionButton(this->optionButton);
  this->event.setExitButton(this->exitButton);
}

EventStatus MenuModel::launchModel()
{
  EventStatus eventStatus = EventStatus::STAND_BY;

  this->event.setEventStatus(eventStatus);
  while (this->_device->run())
    {
      if (this->_device->isWindowActive())
	{
	  this->_driver->beginScene(false, true, irr::video::SColor(0, 0, 0, 0));
	  if (this->background != nullptr)
	    this->_driver->draw2DImage(this->background, irr::core::position2d<int>(0, 0));
	  if (eventStatus != EventStatus::STAND_BY)
	    break;
	  this->_guienv->drawAll();
	  this->_driver->endScene();
	}
    }
  return (eventStatus);
}

void MenuModel::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}
