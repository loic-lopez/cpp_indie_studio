/*
** MenuEventController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuEventController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 17:36:48 2017 Yassir Jabbari
// Last update Sat May  6 18:26:44 2017 Jabbari Yassir
*/

#include "MenuEventModel.hpp"

MenuEventModel::MenuEventModel(irr::IrrlichtDevice *device)
{
  this->device = device;
}

bool	MenuEventModel::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32 id = event.GUIEvent.Caller->getID();
      switch (id)
	{
	  case 42 :
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		*this->eventStatus = EventStatus::QUIT;
		this->device->closeDevice();
		break;
	      }
	  case MenuButton::PLAY:
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		*this->eventStatus = EventStatus::ENTER_IN_GAME;
		break;
	      }
	}
    }
  return (false);
}

void	MenuEventModel::setSelected(irr::s32 const &selected)
{
  this->selected = selected;
}

void	MenuEventModel::setStartButton(irr::gui::IGUIButton *startButton)
{
  this->startButton = startButton;
}

void MenuEventModel::setEventStatus(EventStatus &eventStatus)
{
  this->eventStatus = &eventStatus;
}

void MenuEventModel::setExitButton(irr::gui::IGUIButton *exitButton)
{
  this->exitButton = exitButton;
}