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
  irr::video::ITexture			*cursor;
  irr::core::dimension2d<irr::s32>	image_size;
  irr::video::ITexture			*texture;

  // SET TAB CTRL TO TRANSPARENCY
  this->skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)3, irr::video::SColor(0, 0, 0,0));
  this->background = this->_driver->getTexture("ressources/images/worms_main_menu.png");
  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(screenSize.Width / 3,
								    screenSize.Height / 5,
								    screenSize.Width - (screenSize.Width / 3),
								    screenSize.Height - (screenSize.Height / 7)),
					       nullptr, false, false);

  this->SetMenuModelMainOptions();
  // CURSOR
  this->spriteBank = this->_guienv->addEmptySpriteBank(irr::io::path("ressources/cursor"));
  cursor = this->_driver->getTexture("ressources/cursor/cursor.png");
  this->cursorSize = cursor->getSize();
  this->spriteBank->addTextureAsSprite(cursor);

  irr::gui::SCursorSprite	cursorSprite(this->spriteBank, 0,  irr::core::position2d<irr::s32>(0,0));

  this->_device->getCursorControl()->addIcon(cursorSprite);
  this->_device->getCursorControl()->setActiveIcon((irr::gui::ECURSOR_ICON)0);
  this->_device->getCursorControl()->setVisible(false);

  // CHECKBOXES
  image_size = texture->getSize();
  this->checkboxSound = this->_guienv->addButton(irr::core::rect<int>((image_size.Width / 9),
								      ((image_size.Height / 2)),
								      (image_size.Width),
								      ((image_size.Height) * 3) / 2),
						   this->tabctrl, MenuButton::OPTION_SOUND, L"");
  this->event.setSoundCheckboxAndTextures(this->checkboxSound,
					  this->_driver->getTexture("ressources/buttons/checkboxes/sound_checked.png"),
					  this->_driver->getTexture("ressources/buttons/checkboxes/sound_not_checked.png"));
  image_size = texture->getSize();
  this->wallsCheckbox = this->_guienv->addButton(irr::core::rect<int>((image_size.Width / 9),
								    ((image_size.Height / 2) * 4),
								    (image_size.Width),
								    ((image_size.Height) * 6) / 2),
					       this->tabctrl, MenuButton::OPTION_MAP, L"");
  this->event.setWallsCheckboxAndTextures(this->wallsCheckbox,
					  this->_driver->getTexture("ressources/buttons/checkboxes/closed_map_checked.png"),
					  this->_driver->getTexture("ressources/buttons/checkboxes/closed_map_not_checked.png"));

  // BACK
  texture = this->_driver->getTexture("ressources/buttons/back.png");
  image_size = texture->getSize();
  this->backButton = this->_guienv->addButton(irr::core::rect<irr::s32>(this->tabctrl->getTabExtraWidth(),
									(image_size.Height * 8),
									(image_size.Width * 2),
									(image_size.Height * 9)) ,
					      this->tabctrl, MenuButton::BACK, L"");
  this->backButton->setImage(texture);
  this->event.setBackButton(this->backButton);


  //event controller
  this->event.setSelected(this->selected);

  //set button events
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
	    {
	      *this->playSound = this->event.getCheckboxSoundStatus();
	      *this->drawWalls = this->event.getCheckboxWallsStatus();
	      break;
	    }
	  this->_guienv->drawAll();
	  if (this->spriteBank != nullptr)
	    {
	      irr::core::position2d<irr::s32> mousePosition = this->_device->getCursorControl()->getPosition();
	      this->spriteBank->draw2DSprite(irr::u32(0), irr::core::position2di(mousePosition.X - cursorSize.Width / 4,
									   mousePosition.Y - cursorSize.Height / 8),
				       nullptr,
				       irr::video::SColor(255, 255, 255, 255), 0);
	    }

	  this->_driver->endScene();
	}
    }
  this->_driver->removeAllTextures();
  this->_guienv->clear();
  return (eventStatus);
}