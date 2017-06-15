/*
** EventInventory.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/EventInventory.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Thu Jun 15 02:26:56 2017 Yassir Jabbari
** Last update Thu Jun 15 02:26:56 2017 Yassir Jabbari
*/
#ifndef CPP_INDIE_STUDIO_EVENTINVENTORY_HPP
#define CPP_INDIE_STUDIO_EVENTINVENTORY_HPP
#include "Dependencies/Dependencies.hpp"
#include "Events/MenuButton.hpp"
#include "Events/buttonState.hpp"
#include "Events/EventStatus.hpp"

class 		InventoryEvent : public irr::IEventReceiver
{
 public:

  InventoryEvent(irr::IrrlichtDevice *device);
  virtual ~InventoryEvent();
  virtual bool 					OnEvent(const irr::SEvent &event);
  void 						setEventStatus(EventStatus &);

 private:
  irr::IrrlichtDevice				*device;
  irr::gui::IGUIEnvironment			*guienv;
  irr::video::IVideoDriver			*driver;
  EventStatus					*eventStatus;
};
#endif //CPP_INDIE_STUDIO_EVENTINVENTORY_HPP
