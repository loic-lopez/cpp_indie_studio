/*
** MenuController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:52:58 2017 Yassir Jabbari
// Last update Wed May 10 14:01:20 2017 Stanislas Deneubourg
*/

#include "MenuModel.hpp"

MenuModel::MenuModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr, irr::gui::IGUIEnvironment *guienv, std::vector<std::string> saves,
bool &playSound, bool &drawWalls)
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
  this->playSound = &playSound;
  this->drawWalls = &drawWalls;
}

MenuModel::~MenuModel()
{
}

void	MenuModel::setModelProperties()
{
  const irr::s32 leftX = 260;
  const irr::s32 d = 40;

  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(leftX, 10, 512 - 10, 384 - 10),
					       0, false, false);
  this->mainCtrl = this->tabctrl->addTab(L"Menu");
  this->optionCtrl = this->tabctrl->addTab(L"Option");
  this->checkboxSound = this->_guienv->addCheckBox(*this->playSound, irr::core::rect<int>(20, 85 + d, 130, 110 + d),
						   this->optionCtrl, 3, L"Sound");
  this->checkboxWalls = this->_guienv->addCheckBox(*this->drawWalls, irr::core::rect<int>(20, 110 + d, 135, 135 + d),
						   this->optionCtrl, 4, L"Generation Alternative");
  this->boxSave = this->_guienv->addListBox(irr::core::rect<int>(10, 10, 220, 120),
					    this->mainCtrl, 1);
  this->boxSave->addItem(L"Create new game");
  if (this->_saves.size() > 0)
    {
      for (auto i = this->_saves.begin(); i != this->_saves.end(); ++i)
	{
	  std::wstring tmp = std::wstring(i->begin(), i->end());
	  const wchar_t *toPrint = tmp.c_str();
	  this->boxSave->addItem(toPrint);
	}
    }
  this->boxSave->setSelected(this->selected);
  this->event.setSelected(this->selected);
  this->startButton = this->_guienv->addButton(irr::core::rect<int>(30, 295, 200, 324), this->mainCtrl, 2, L"");
  this->textuStart = this->_driver->getTexture("ressources/images/start.png");
  this->startButton->setUseAlphaChannel(true);
  this->startButton->setDrawBorder(false);
  this->startButton->setImage(this->textuStart);
  this->exitButton = this->_guienv->addButton(irr::core::rect<int>(30, 213, 200, 242), this->mainCtrl, 42, L"");
  this->textuExit = this->_driver->getTexture("ressources/images/exit.png");
  this->exitButton->setUseAlphaChannel(true);
  this->exitButton->setDrawBorder(false);
  this->exitButton->setImage(this->textuExit);
  this->_smgr->addCameraSceneNode(0, irr::core::vector3df(45, 0, 0), irr::core::vector3df(0, 0, 10));
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  this->background = this->_driver->getTexture("ressources/images/181192.jpg");
  this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, this->_driver->getTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS));
  this->event.setStartButton(this->startButton);
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
	  *this->playSound = this->checkboxSound->isChecked();
	  *this->drawWalls = this->checkboxWalls->isChecked();
	  this->_guienv->drawAll();
	  this->_driver->endScene();
	}
    }
  this->_driver->removeAllTextures();
  this->_guienv->clear();
  return (eventStatus);
}

void MenuModel::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}
