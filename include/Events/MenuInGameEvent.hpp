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

#include "Dependencies/Dependencies.hpp"
#include "EventReceiver.hpp"
#include "EventStatus.hpp"
#include "MenuButton.hpp"

class		MenuInGameEvent : public EventReceiver
{
 public:
  MenuInGameEvent(irr::IrrlichtDevice *device);
  virtual bool OnEvent(const irr::SEvent &event);
  bool 		IsKeyUp(irr::EKEY_CODE keyCode);

  void 	setMenuInGameButtons(irr::gui::IGUITabControl *tabctrl);
  EventStatus const &getEventStatus() const;

 private:
  irr::gui::IGUIEnvironment			*guienv;
  irr::video::IVideoDriver				*driver;
  irr::gui::IGUIButton				*backToGameButton;
  irr::gui::IGUIButton				*saveCurrentGameButton;
  irr::gui::IGUIButton				*soundOptionButton;
  irr::gui::IGUIButton				*backToMenuButton;
  EventStatus 					eventStatus;
  EventReceiver	 				eventReceiver;
};

#endif //CPP_INDIE_STUDIO_MENUINGAMEEVENTMODEL_HPP
