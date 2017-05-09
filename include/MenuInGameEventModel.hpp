/*
** MenuInGameEventModel.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameEventModel.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 17:20:28 2017 Yassir Jabbari
** Last update Mon May 08 17:20:28 2017 Yassir Jabbari
*/
#ifndef CPP_INDIE_STUDIO_MENUINGAMEEVENTMODEL_HPP
#define CPP_INDIE_STUDIO_MENUINGAMEEVENTMODEL_HPP

#include "EventStatus.hpp"
#include <irrlicht.h>

class		MenuInGameEventModel : public irr::IEventReceiver
{
 public:
  MenuInGameEventModel(irr::IrrlichtDevice *device);
  virtual bool OnEvent(const irr::SEvent &event);
  void setEventStatus(EventStatus &status);
  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

 private:
  bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  irr::IrrlichtDevice	*device;
  EventStatus *eventStatus;
};

#endif //CPP_INDIE_STUDIO_MENUINGAMEEVENTMODEL_HPP
