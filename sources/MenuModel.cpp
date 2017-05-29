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

MenuModel::MenuModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		     irr::scene::ISceneManager *smgr, irr::gui::IGUIEnvironment *guienv,
		     std::vector<std::string> saves, bool &playSound, bool &drawWalls)
  : _device(device), _driver(driver), _smgr(smgr),_guienv(guienv), event(device), _saves(saves)
{
  this->_device->setWindowCaption(L"Worms 3D");
  this->_device->setEventReceiver(&this->event);
  this->skin = this->_guienv->createSkin(irr::gui::EGST_BURNING_SKIN);
  this->_guienv->setSkin(this->skin);
  this->font = this->_guienv->getFont("ressources/fonts/fonthaettenschweiler.bmp");
  if (this->font != nullptr)
    this->_guienv->getSkin()->setFont(this->font);
  this->playSound = &playSound;
  this->drawWalls = &drawWalls;
  this->selected = 0;
}

MenuModel::~MenuModel()
{
  this->skin->drop();
}

void	MenuModel::setModelProperties()
{
  const irr::core::dimension2du& 	screenSize = this->_driver->getScreenSize();
  irr::core::dimension2d<irr::s32>	image_size;
  irr::video::ITexture			*texture;
  irr::video::ITexture			*cursor;

  // SET TAB CTRL TO TRANSPARENCY
  for (irr::s32 i=0; i < irr::gui::EGDC_COUNT; ++i)
    {
      irr::video::SColor col = this->skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
      col.set(0, 0, 0, 0);
      this->skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
    }
  this->background = this->_driver->getTexture("ressources/images/worms_main_menu.png");
  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(screenSize.Width / 3,
								    screenSize.Height / 5,
								    screenSize.Width - (screenSize.Width / 3),
								    screenSize.Height - (screenSize.Height / 7)),
					       nullptr, false, false);

  //play button
  texture = this->_driver->getTexture("ressources/buttons/play.png");
  image_size = texture->getSize();
  this->startButton = this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) + 34,
									 image_size.Height / 2,
									 (image_size.Width / 2) + 4 * 34,
									 image_size.Height),
					       this->tabctrl, MenuButton::PLAY, L"");
  this->startButton->setDrawBorder(false);
  this->startButton->setImage(texture);
  this->startButton->setUseAlphaChannel(true);

  // OPTION BUTTON
  texture = this->_driver->getTexture("ressources/buttons/options.png");
  image_size = texture->getSize();
  this->optionButton = this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 4) + 34,
									((image_size.Height / 2) * 2),
									(image_size.Width / 2) + 6 * 34,
									(image_size.Height * 2)),
					      this->tabctrl, MenuButton::OPTIONS, L"");
  this->optionButton->setImage(texture);
  this->optionButton->setUseAlphaChannel(true);
  this->optionButton->setDrawBorder(false);

  //exit button
  texture = this->_driver->getTexture("ressources/buttons/exit.png");
  image_size = texture->getSize();
  this->exitButton = this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 4) + 34,
									((image_size.Height / 2) * 3),
									(image_size.Width / 2) + 6 * 34,
									(image_size.Height * 3)),
					      this->tabctrl, MenuButton::EXIT, L"");
  this->exitButton->setImage(texture);
  this->exitButton->setUseAlphaChannel(true);
  this->exitButton->setDrawBorder(false);

  // CURSOR
  this->spriteBank = this->_guienv->addEmptySpriteBank(irr::io::path("ressources/cursor"));
  cursor = this->_driver->getTexture("ressources/cursor/cursor.png");
  this->cursorSize = cursor->getSize();
  this->spriteBank->addTextureAsSprite(cursor);

  irr::gui::SCursorSprite	cursorSprite(this->spriteBank, 0,  irr::core::position2d<irr::s32>(0,0));

  this->_device->getCursorControl()->addIcon(cursorSprite);
  this->_device->getCursorControl()->setActiveIcon((irr::gui::ECURSOR_ICON) 0);
  this->_device->getCursorControl()->setVisible(false);

  //event controller
  this->event.setSelected(this->selected);
  this->event.setStartButton(this->startButton);
  this->event.setExitButton(this->exitButton);
}

EventStatus	MenuModel::launchModel()
{
  EventStatus	eventStatus = EventStatus::STAND_BY;

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
	  if (this->spriteBank != nullptr)
	    {
	      irr::core::position2d<irr::s32> mousePosition = this->_device->getCursorControl()->getPosition();
	      this->spriteBank->draw2DSprite(irr::u32(0), irr::core::position2di(mousePosition.X - cursorSize.Width / 4,
									   mousePosition.Y - cursorSize.Height / 8),
				       nullptr,
				       irr::video::SColor(255, 255, 255, 255), 0);
	    }
	  /*
	  *this->playSound = this->checkboxSound->isChecked();
	  *this->drawWalls = this->checkboxWalls->isChecked();
	  */
	  this->_driver->endScene();
	}
    }
  this->_driver->removeAllTextures();
  this->_guienv->clear();
  return (eventStatus);
}