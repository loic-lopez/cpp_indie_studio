/*
** MenuInGameEventModel.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameEventModel.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 18:05:17 2017 Yassir Jabbari
** Last update Mon May 08 18:05:17 2017 Yassir Jabbari
*/

#include "Events/MenuInGameEvent.hpp"

MenuInGameEvent::MenuInGameEvent(irr::IrrlichtDevice *device)
{
  this->device = device;
}

bool MenuInGameEvent::OnEvent(const irr::SEvent &event)
{
  this->eventReceiver.OnEvent(event);
  if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32 id = event.GUIEvent.Caller->getID();
      this->exitButton->setEnabled(true);
      switch (id)
	{
	  case 42 :
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		*this->eventStatus = EventStatus::QUIT;
		this->device->closeDevice();
		break;
	      }
	  case 1 :
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	    {
		*this->eventStatus = EventStatus ::ENTER_IN_GAME;
		break;
	    }
	  case 2 :
	    {
	      *this->eventStatus = EventStatus::SAVES;
	      break;
	    }
	  case 3 :
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  *this->eventStatus = EventStatus::BACK_TO_MENU;
		  break;
		}
	    }
	}
    }
  return (false);
}

void MenuInGameEvent::setEventStatus(EventStatus &status)
{
  this->eventStatus = &status;
}

bool MenuInGameEvent::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->eventReceiver.IsKeyDown(keyCode));
}

bool MenuInGameEvent::IsKeyUp(irr::EKEY_CODE keyCode)
{
  return (this->eventReceiver.IsKeyUp(keyCode));
}

void MenuInGameEvent::setExitButton(irr::gui::IGUIButton *exitButton)
{
  this->exitButton = exitButton;
}