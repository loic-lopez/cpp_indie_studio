/*
** EventInventory.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/EventInventory.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Thu Jun 15 02:26:56 2017 Yassir Jabbari
** Last update Thu Jun 15 02:26:56 2017 Yassir Jabbari
*/
#include "Events/EventInventory.hpp"
#include <iostream>

InventoryEvent::InventoryEvent(irr::IrrlichtDevice *device)
{
  this->guienv = device->getGUIEnvironment();
  this->driver = device->getVideoDriver();
  this->device = device;
}

InventoryEvent::~InventoryEvent()
{

}

bool InventoryEvent::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32 id = event.GUIEvent.Caller->getID();
      switch (id)
	{
	  case InventoryButton::SHOTGUN :
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  std::cout << "Et voilà it works" << std::endl;
		  break;
		}
	    }
	  default:
	    break;
	}
    }
  return (false);
}

void InventoryEvent::setEventStatus(EventStatus &eventStatus)
{
  this->eventStatus = &eventStatus;
}