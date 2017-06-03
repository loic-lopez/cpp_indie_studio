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
  this->guienv = this->device->getGUIEnvironment();
}

bool MenuInGameEvent::OnEvent(const irr::SEvent &event)
{
  this->eventReceiver.OnEvent(event);
  if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32 id = event.GUIEvent.Caller->getID();
      switch (id)
	{
	  /*
	  case 42:
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		*this->eventStatus = EventStatus::QUIT;
		this->device->closeDevice();
		break;
	      }
	      */
	  case MenuInGameButton::BACK_TO_GAME:
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	    {
		this->eventStatus = EventStatus ::ENTER_IN_GAME;
		break;
	    }
	  case MenuInGameButton::SAVE_CURRENT_GAME:
	    {

	      break;
	    }
	  case MenuInGameButton::BACK_TO_MENU:
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  this->eventStatus = EventStatus::BACK_TO_MENU;
		  break;
		}
	    }
	  default:
	    break;
	}
    }
  return (false);
}

void 	MenuInGameEvent::setBackToGameButton()
{
}

void 	MenuInGameEvent::hideMenuInGameButtons()
{
  this->backToGameButton->setVisible(false);
  this->saveCurrentGameButton->setVisible(false);
  this->soundOptionButton->setVisible(false);
  this->backToMenuButton->setVisible(false);
}

void 	MenuInGameEvent::showMenuInGameButtons()
{
  this->backToGameButton->setVisible(true);
  this->saveCurrentGameButton->setVisible(true);
  this->soundOptionButton->setVisible(true);
  this->backToMenuButton->setVisible(true);
}

EventStatus const &MenuInGameEvent::getEventStatus() const
{
  return this->eventStatus;
}

bool MenuInGameEvent::IsKeyUp(irr::EKEY_CODE keyCode)
{
  return this->eventReceiver.IsKeyUp(keyCode);
}
