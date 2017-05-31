/*
** MenuController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:52:58 2017 Yassir Jabbari
// Last update Wed May 31 14:41:04 2017 Stanislas Deneubourg
*/

#include "Model/MenuModel.hpp"

MenuModel::MenuModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		     irr::scene::ISceneManager *smgr, irr::gui::IGUIEnvironment *guienv,
		     std::vector<std::string> const &saves, bool &playSound, bool &drawWalls)
  : _device(device), _driver(driver), _smgr(smgr),_guienv(guienv), event(device)
{
  this->_device->setWindowCaption(L"Worms 3D");
  this->_device->setEventReceiver(&this->event);
  this->skin = this->_guienv->createSkin(irr::gui::EGST_WINDOWS_METALLIC);
  this->_guienv->setSkin(this->skin);
  this->font = this->_guienv->getFont("ressources/fonts/SoftMarshmallow.png");
  if (this->font != nullptr)
    this->_guienv->getSkin()->setFont(this->font);
  this->playSound = &playSound;
  this->drawWalls = &drawWalls;
  this->selected = 0;
  this->_saves = saves;
}

MenuModel::~MenuModel()
{
  this->skin->drop();
}

void	MenuModel::setModelProperties()
{
  irr::video::ITexture			*cursor;
  irr::core::dimension2d<irr::s32>	image_size;
  irr::video::ITexture			*texture;

  this->screenSize = this->_driver->getScreenSize();
  this->setSkinTransparency();
  this->background = this->_driver->getTexture("ressources/images/worms_main_menu.png");
  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(this->screenSize.Width / 3,
								    this->screenSize.Height / 5,
								    this->screenSize.Width - (this->screenSize.Width / 3),
								    this->screenSize.Height - (this->screenSize.Height / 7)),
					       nullptr, false, false);

  // CURSOR
  this->spriteBank = this->_guienv->addEmptySpriteBank(irr::io::path("ressources/cursor"));
  cursor = this->_driver->getTexture("ressources/cursor/cursor.png");
  this->cursorSize = cursor->getSize();
  this->spriteBank->addTextureAsSprite(cursor);
  this->SetMenuModelMainOptions();

  irr::gui::SCursorSprite	cursorSprite(this->spriteBank, 0,  irr::core::position2d<irr::s32>(0,0));

  this->_device->getCursorControl()->addIcon(cursorSprite);
  this->_device->getCursorControl()->setActiveIcon((irr::gui::ECURSOR_ICON)0);
  this->_device->getCursorControl()->setVisible(false);

  // CHECKBOXES
  texture = this->_driver->getTexture("ressources/buttons/checkboxes/sound_checked.png");
  image_size = texture->getSize();
  this->checkboxSound = this->_guienv->addButton(irr::core::rect<int>((image_size.Width / 9),
								      ((image_size.Height / 2)),
								      (image_size.Width),
								      ((image_size.Height) * 3) / 2),
						   this->tabctrl, MenuButton::OPTION_SOUND, L"");
  this->event.setSoundCheckboxAndTextures(this->checkboxSound,
					  texture,
					  this->_driver->getTexture("ressources/buttons/checkboxes/sound_not_checked.png"));

  texture = this->_driver->getTexture("ressources/buttons/checkboxes/closed_map_checked.png");
  image_size = texture->getSize();
  this->wallsCheckbox = this->_guienv->addButton(irr::core::rect<int>((image_size.Width / 9),
								    ((image_size.Height / 2) * 4),
								    (image_size.Width),
								    ((image_size.Height) * 6) / 2),
					       this->tabctrl, MenuButton::OPTION_MAP, L"");
  this->event.setWallsCheckboxAndTextures(this->wallsCheckbox,
					  texture,
					  this->_driver->getTexture("ressources/buttons/checkboxes/closed_map_not_checked.png"));

  // BACK
  texture = this->_driver->getTexture("ressources/buttons/back.png");
  image_size = texture->getSize();
  this->event.setBackButton(this->_guienv->addButton(irr::core::rect<irr::s32>(this->tabctrl->getTabExtraWidth(),
									       (image_size.Height * 8),
									       (image_size.Width * 2),
									       (image_size.Height * 9)) ,
						     this->tabctrl, MenuButton::BACK, L""), texture);

  irr::core::rect<irr::s32> tabctrlSize = this->tabctrl->getRelativePosition();
  irr::s32 tabctrlWidth = tabctrlSize.getWidth();
  irr::s32 tabctrlHeight = tabctrlSize.getHeight();
  irr::core::position2d<int> midTabctrl = tabctrlSize.getCenter();

  this->event.setSelected(this->selected);
  this->event.setSavesListBox(this->_guienv->addListBox(irr::core::rect<int>(tabctrlWidth / 10,
									     tabctrlHeight / 5,
									     tabctrlWidth - (midTabctrl.X / 8),
									     tabctrlHeight - (midTabctrl.Y / 3)),
							this->tabctrl, 1), this->_saves);

  this->saveSubMenuSpriteSize = this->spriteBank->getTexture(irr::u32(MenuModel::SpriteName::SAVE_SUB_MENU))->getSize();
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
	  if (this->spriteBank != nullptr && this->event.getPressedButton() == MenuButton::SAVES)
	    {
	      this->spriteBank->draw2DSprite(irr::u32(MenuModel::SpriteName::SAVE_SUB_MENU),
					     irr::core::position2di(
						     (this->screenSize.Width / 2) - this->saveSubMenuSpriteSize.Width / 2,
						     (this->screenSize.Height / 4) - this->saveSubMenuSpriteSize.Height / 2),
					     nullptr,
					     irr::video::SColor(255, 255, 255, 255), 0);
	    }
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
	      this->spriteBank->draw2DSprite(irr::u32(MenuModel::SpriteName::BACKGROUND),
					     irr::core::position2di(mousePosition.X - cursorSize.Width / 4,
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

void	MenuModel::setSkinTransparency()
{

  for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT ; ++i)
    {
      if ((irr::gui::EGUI_DEFAULT_COLOR)i != irr::gui::EGDC_HIGH_LIGHT_TEXT)
	this->skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, irr::video::SColor(0, 0, 0, 0));
    }
  this->skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 190, 0));
}
