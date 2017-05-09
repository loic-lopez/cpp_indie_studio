/*
** MenuInGameEventModel.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameEventModel.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 18:05:17 2017 Yassir Jabbari
** Last update Mon May 08 18:05:17 2017 Yassir Jabbari
*/

#include "MenuInGameEventModel.hpp"

MenuInGameEventModel::MenuInGameEventModel(irr::IrrlichtDevice *device)
{
  this->device = device;
}

bool MenuInGameEventModel::OnEvent(const irr::SEvent &event)
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
	}
    }
  return (false);
}

void MenuInGameEventModel::setEventStatus(EventStatus &status)
{
  this->eventStatus = &status;
}

bool MenuInGameEventModel::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->eventReceiver.IsKeyDown(keyCode));
}

bool MenuInGameEventModel::IsKeyUp(irr::EKEY_CODE keyCode)
{
  return (this->eventReceiver.IsKeyUp(keyCode));
}

void MenuInGameEventModel::setExitButton(irr::gui::IGUIButton *exitButton)
{
  this->exitButton = exitButton;
}