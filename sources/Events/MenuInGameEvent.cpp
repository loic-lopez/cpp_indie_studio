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
  this->guienv = device->getGUIEnvironment();
  this->driver = device->getVideoDriver();
  this->eventStatus = EventStatus::STAND_BY;
}

bool	MenuInGameEvent::OnEvent(const irr::SEvent &event)
{
  this->eventStatus = EventStatus::STAND_BY;
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
		this->eventStatus = EventStatus::ENTER_IN_GAME;
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
	    {
	      break;
	    }
	}
    }
  else
    this->eventReceiver.OnEvent(event);
  return (false);
}

void 	MenuInGameEvent::setMenuInGameButtons(irr::gui::IGUITabControl *tabctrl)
{
  irr::video::ITexture	*buttonTexture;
  irr::core::dimension2d<irr::s32>	image_size;

  buttonTexture = this->driver->getTexture("ressources/buttons/back_to_game.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->backToGameButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (8 * 34) / 4,
							(image_size.Height / 2) + 38,
							(image_size.Width / 2) + 8 * 34,
							image_size.Height + 38),
			      tabctrl, MenuInGameButton::BACK_TO_GAME, L"");
      this->backToGameButton->setImage(buttonTexture);
      this->backToGameButton->setUseAlphaChannel(false);

    }
}

EventStatus const &MenuInGameEvent::getEventStatus() const
{
  return this->eventStatus;
}

bool MenuInGameEvent::IsKeyUp(irr::EKEY_CODE keyCode)
{
  return this->eventReceiver.IsKeyUp(keyCode);
}
