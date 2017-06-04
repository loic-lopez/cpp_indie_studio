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
		       irr::scene::ISceneManager *smgr, EventReceiver &eventReceiver) :
	_device(device), _driver(driver), _smgr(smgr), eventReceiver(eventReceiver)
{
  this->_guienv = this->_device->getGUIEnvironment();
  this->_skin = this->_guienv->createSkin(irr::gui::EGST_WINDOWS_METALLIC);
  for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT ; ++i)
    this->_skin->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, irr::video::SColor(0, 0, 0, 0));
  this->_guienv->setSkin(this->_skin);
  this->_skin->drop();
}

MenuInGame::~MenuInGame()
{
  this->_driver->removeAllTextures();
  this->_guienv->clear();
}

void	MenuInGame::setModelProperties()
{
  this->screenSize = this->_driver->getScreenSize();
  irr::video::ITexture			*texture;
  irr::video::ITexture			*cursor;

  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(screenSize.Width / 3,
								    screenSize.Height / 5,
								    screenSize.Width - (screenSize.Width / 3),
								    screenSize.Height - (screenSize.Height / 7)),
					       nullptr, false, false);
  texture = this->_driver->getTexture("ressources/images/game_menu.png");
  this->spriteBank = this->_guienv->addEmptySpriteBank(irr::io::path("ressources/images"));
  if (texture != nullptr)
    this->spriteBank->addTextureAsSprite(texture);

  cursor = this->_driver->getTexture("ressources/cursor/cursor.png");
  if (cursor != nullptr)
    {
      this->cursorSize = cursor->getSize();
      this->spriteBank->addTextureAsSprite(cursor);
    }
  this->eventReceiver.setMenuInGameButtons(this->tabctrl);
}

EventStatus		MenuInGame::launchModel()
{
  this->eventStatus = this->eventReceiver.getEventStatus();
  if (this->spriteBank->getTexture(irr::u32(MenuInGame::MenuInGameSpriteName::LITTLE_MENU)) != nullptr)
    this->spriteBank->draw2DSprite(irr::u32(MenuInGame::MenuInGameSpriteName::LITTLE_MENU),
				  irr::core::position2di(0, 0),
				  nullptr,
				  irr::video::SColor(255, 255, 255, 255), 0);
  this->_guienv->drawAll();
  if (this->spriteBank->getTexture(irr::u32(MenuInGame::MenuInGameSpriteName::CURSOR)) != nullptr)
    {
      irr::core::position2d<irr::s32> mousePosition = this->_device->getCursorControl()->getPosition();
	  this->spriteBank->draw2DSprite(irr::u32(MenuInGame::MenuInGameSpriteName::CURSOR),
					 irr::core::position2di(mousePosition.X - this->cursorSize.Width / 4,
								mousePosition.Y - this->cursorSize.Height / 8),
					 nullptr,
					 irr::video::SColor(255, 255, 255, 255), 0);
    }
  return (this->eventStatus);
}