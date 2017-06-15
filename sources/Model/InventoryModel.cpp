/*
** InventoryModel.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/InventoryModel.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Wed Jun 14 16:41:07 2017 Yassir Jabbari
** Last update Wed Jun 14 16:41:07 2017 Yassir Jabbari
*/

#include "Model/InventoryModel.hpp"

InventoryModel::InventoryModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
			       EventReceiver &eventReceiver) : eventReceiver(eventReceiver)
{
  this->_device = device;
  this->_driver = driver;
  this->_guienv = this->_device->getGUIEnvironment();
  this->_skin = this->_guienv->createSkin(irr::gui::EGST_WINDOWS_METALLIC);
  this->_guienv->setSkin(this->_skin);
  this->_skin->drop();
  this->screenSize = this->_driver->getScreenSize();
}

InventoryModel::~InventoryModel()
{
  this->_guienv->clear();
}

void InventoryModel::setModelProperties()
{
  irr::video::ITexture                  *texture;
  irr::video::ITexture			*cursor;

for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT ; ++i)
    this->_guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, irr::video::SColor(0, 0, 0, 0));
  texture = this->_driver->getTexture("ressources/inventory/inventory.png");
  this->backgroundSize = texture->getSize();
  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(this->screenSize.Width / 3 + this->backgroundSize.Width / 5,
								    this->screenSize.Height / 6,
								    this->screenSize.Width / 3 + this->backgroundSize.Width + (this->backgroundSize.Width / 5),
								    screenSize.Height - this->backgroundSize.Height / 5),
					       nullptr, false, false);
  this->hideTabCtrl();
  if (this->_guienv->getSpriteBank(irr::io::path("ressources/inventory/weapons")) == nullptr)
    this->spriteBank = this->_guienv->addEmptySpriteBank(irr::io::path("ressources/inventory/weapons"));
  else
    this->spriteBank = this->_guienv->getSpriteBank(irr::io::path("ressources/inventory/weapons"));
  if (texture != nullptr)
    this->spriteBank->addTextureAsSprite(texture);
  cursor = this->_driver->getTexture("ressources/cursor/cursor.png");
  if (cursor != nullptr)
    {
      this->cursorSize = cursor->getSize();
      this->spriteBank->addTextureAsSprite(cursor);
    }
  this->eventReceiver.setWeaponsButtons(this->tabctrl);
}

EventStatus InventoryModel::launchModel()
{
  this->eventStatus = this->eventReceiver.getEventStatus();
  if (this->spriteBank->getTexture(irr::u32(0)) != nullptr)
  this->spriteBank->draw2DSprite(irr::u32(0),
				 irr::core::position2di(this->screenSize.Width / 3 + this->backgroundSize.Width / 5, this->screenSize.Height / 6),
				 nullptr,
				 irr::video::SColor(255, 255, 255, 255), 0);
  this->_guienv->drawAll();
  if (this->spriteBank->getTexture(irr::u32(1)) != nullptr)
    {
      irr::core::position2d<irr::s32> mousePosition = this->_device->getCursorControl()->getPosition();
      this->spriteBank->draw2DSprite(irr::u32(1),
				     irr::core::position2di(mousePosition.X - this->cursorSize.Width / 4,
							    mousePosition.Y - this->cursorSize.Height / 8),
				     nullptr,
				     irr::video::SColor(255, 255, 255, 255), 0);
    }
  return (this->eventStatus);
}

void	InventoryModel::showTabCtrl()
{
  this->tabctrl->setVisible(true);
}

void	InventoryModel::hideTabCtrl()
{
  this->tabctrl->setVisible(false);
}
