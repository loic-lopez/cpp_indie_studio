/*
** Inventory.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Inventory.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:31:33 2017 Loïc Lopez
// Last update Mon Jun 12 18:23:21 2017 Stanislas Deneubourg
*/

// TODO: REMOVE PRINT
#include <iostream>
#include "Worms/Inventory.hpp"

Inventory::Inventory(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		     irrklang::ISoundEngine *soundEngine, EventReceiver &eventReceiver) : _device(device), _driver(driver), eventReceiver(eventReceiver)
{
  this->_guienv = this->_device->getGUIEnvironment();
  this->_skin = this->_guienv->createSkin(irr::gui::EGST_WINDOWS_METALLIC);
  this->_guienv->setSkin(this->_skin);
  this->_skin->drop();
  this->weaponsInInventory.emplace_back(static_cast<IWeapon *>(new Uzi(device, soundEngine)));
  this->weaponsInInventory.emplace_back(static_cast<IWeapon *>(new Shotgun(device, soundEngine)));
  this->weaponsInInventory.emplace_back(static_cast<IWeapon *>(new Surrender(device, soundEngine)));
}

Inventory::~Inventory()
{

}

bool	Inventory::fireWithSelectedWeapon(size_t const &weaponSelectedInGui)
{
  return this->weaponsInInventory.at(weaponSelectedInGui)->fire();
}

void    Inventory::showSelectedWeapon(size_t const &weaponSelectedInGui,
				      const irr::core::vector3df &position, const irr::core::vector3df &rotation)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->showWeapon(position, rotation);
}

void	Inventory::setWeaponPositionToWormPosition(size_t const &weaponSelectedInGui,
						       const irr::core::vector3df &position)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->setWeaponPosition(position);
}

void	Inventory::setWeaponRotationToWormPosition(size_t const &weaponSelectedInGui,
						       const irr::core::vector3df &rotation)
{
  this->weaponsInInventory.at(weaponSelectedInGui)->setWeaponRotation(rotation);
}

void Inventory::launchInventory()
{
  irr::video::ITexture                   *texture;
  irr::video::ITexture			*cursor;

  for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT ; ++i)
    this->_guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, irr::video::SColor(0, 0, 0, 0));
  this->tabctrl = this->_guienv->addTabControl(irr::core::rect<int>(screenSize.Width / 3,
                                                                    screenSize.Height / 5,
                                                                    screenSize.Width - (screenSize.Width / 3),
                                                                    screenSize.Height - (screenSize.Height / 7)),
                                               nullptr, false, false);
  texture = this->_driver->getTexture("ressources/inventory/inventory.png");
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
  this->eventReceiver.setInventoryButtons(this->tabctrl);
  if (this->spriteBank->getTexture(irr::u32(0)) != nullptr)
    this->spriteBank->draw2DSprite(irr::u32(0),
				   irr::core::position2di(0, 0),
				   nullptr,
				   irr::video::SColor(255, 255, 255, 255), 0);
  if (this->spriteBank->getTexture(irr::u32(1)) != nullptr)
    {
      irr::core::position2d<irr::s32> mousePosition = this->_device->getCursorControl()->getPosition();
      this->spriteBank->draw2DSprite(irr::u32(1),
				     irr::core::position2di(mousePosition.X - this->cursorSize.Width / 4,
							    mousePosition.Y - this->cursorSize.Height / 8),
				     nullptr,
				     irr::video::SColor(255, 255, 255, 255), 0);
    }
}

bool	Inventory::updateWeaponBullets(size_t const &weaponSelectedInGui)
{
  return this->weaponsInInventory.at(weaponSelectedInGui)->updateBullets();
}
