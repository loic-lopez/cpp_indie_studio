/*
** InventoryModel.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/InventoryModel.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Wed Jun 14 16:41:35 2017 Yassir Jabbari
** Last update Wed Jun 14 16:41:35 2017 Yassir Jabbari
*/
#ifndef CPP_INDIE_STUDIO_INVENTORYMODEL_HPP
#define CPP_INDIE_STUDIO_INVENTORYMODEL_HPP

#include <Events/EventReceiver.hpp>
#include "Events/EventStatus.hpp"
#include "Events/EventInventory.hpp"

class 	InventoryModel
{
 public:
  enum class	weaponsId : uint16_t
  {
    UZI = 0,
    SHOTGUN = 1,
    GRENADE = 2
  };

 private:
  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::gui::IGUIEnvironment			*_guienv;
  irr::gui::IGUISkin				*_skin;
  irr::gui::IGUITabControl			*tabctrl;
  irr::core::dimension2du		 	screenSize;
  irr::gui::IGUISpriteBank			*spriteBank;
  irr::core::dimension2d<irr::u32> 		cursorSize;
  InventoryEvent 				event;
  EventStatus 					eventStatus;
  irr::core::dimension2d<irr::u32>		backgroundSize;
  irr::gui::IGUIButton				*shotgunButton;
  weaponsId 					*id;

 public:
  InventoryModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver);
  virtual ~InventoryModel();
  virtual void setModelProperties();
  virtual EventStatus launchModel();
  virtual void	showTabCtrl();
  virtual void	hideTabCtrl();
};

#endif //CPP_INDIE_STUDIO_INVENTORYMODEL_HPP
