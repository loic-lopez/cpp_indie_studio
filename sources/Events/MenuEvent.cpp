/*
** MenuEventController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuEventController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 17:36:48 2017 Yassir Jabbari
// Last update Sat May  6 18:26:44 2017 Jabbari Yassir
*/

#include "Events/MenuEvent.hpp"

MenuEvent::MenuEvent(irr::IrrlichtDevice *device)
{
  this->device = device;
  this->button = MenuButton::PLAY;
}

bool	MenuEvent::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_GUI_EVENT)
    {
      if (event.GUIEvent.EventType == irr::gui::EGET_LISTBOX_CHANGED ||
	  event.GUIEvent.EventType == irr::gui::EGET_LISTBOX_SELECTED_AGAIN)
	{
	  this->selected = reinterpret_cast<irr::gui::IGUIListBox *>(event.GUIEvent.Caller)->getSelected();
	}
      else
	{
	  irr::s32 id = event.GUIEvent.Caller->getID();
	  switch (id)
	    {
	      case MenuButton::EXIT:
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
	      case MenuButton::SAVES:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    this->setMainButtonsHidden();
		    this->button = static_cast<MenuButton>(id);
		    // SUB BUTTONS
		    this->savesListBox->setVisible(true);
		    this->backButton->setVisible(true);
		    break;
		  }
	      case MenuButton::OPTIONS:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    this->setMainButtonsHidden();

		    // SUB BUTTONS
		    this->checkboxSound->setVisible(true);
		    this->checkboxWalls->setVisible(true);
		    this->backButton->setVisible(true);

		    break;
		  }
	      case MenuButton::OPTION_SOUND:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (this->checkboxSoundStatus)
		      {
			this->checkboxSoundStatus = false;
			this->checkboxSound->setImage(this->checkboxSoundNotChecked);
		      }
		    else
		      {
			this->checkboxSoundStatus = true;
			this->checkboxSound->setImage(this->checkboxSoundChecked);
		      }
		    break;
		  }
	      case MenuButton::OPTION_MAP:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (this->checkboxWallsStatus)
		      {
			this->checkboxWallsStatus = false;
			this->checkboxWalls->setImage(this->checkboxWallsNotChecked);
		      }
		    else
		      {
			this->checkboxWallsStatus = true;
			this->checkboxWalls->setImage(this->checkboxWallsChecked);
		      }
		    break;
		  }
	      case MenuButton::BACK:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    this->setMainButtonsVisible();
		    this->button = static_cast<MenuButton>(id);
		    // SUB BUTTONS
		    this->checkboxSound->setVisible(false);
		    this->backButton->setVisible(false);
		    this->checkboxWalls->setVisible(false);
		    this->savesListBox->setVisible(false);
		    break;
		  }
	      default:
		break;
	    }
	}
    }
  return (false);
}

void	MenuEvent::setSelected(irr::s32 const &selected)
{
  this->selected = selected;
}

void	MenuEvent::setEventStatus(EventStatus &eventStatus)
{
  this->eventStatus = &eventStatus;
}

// BUTTONS
void	MenuEvent::setStartButton(irr::gui::IGUIButton *startButton,
					   irr::video::ITexture *texture)
{
  this->startButton = startButton;
  this->startButton->setDrawBorder(false);
  this->startButton->setImage(texture);
  this->startButton->setUseAlphaChannel(true);
}

void	MenuEvent::setOptionButton(irr::gui::IGUIButton *optionButton,
					    irr::video::ITexture *texture)
{
  this->optionButton = optionButton;
  this->optionButton->setImage(texture);
  this->optionButton->setUseAlphaChannel(true);
  this->optionButton->setDrawBorder(false);
}

void	MenuEvent::setExitButton(irr::gui::IGUIButton *exitButton, irr::video::ITexture *texture)
{
  this->exitButton = exitButton;
  this->exitButton->setImage(texture);
  this->exitButton->setUseAlphaChannel(true);
  this->exitButton->setDrawBorder(false);
}

void	MenuEvent::setSavesButton(irr::gui::IGUIButton *savesButton, irr::video::ITexture *texture)
{
  this->savesButton = savesButton;
  this->savesButton->setImage(texture);
  this->savesButton->setUseAlphaChannel(true);
  this->savesButton->setDrawBorder(false);
}


void	MenuEvent::setMainButtonsHidden()
{
  this->optionButton->setVisible(false);
  this->startButton->setVisible(false);
  this->exitButton->setVisible(false);
  this->savesButton->setVisible(false);
}


void	MenuEvent::setMainButtonsVisible()
{
  this->optionButton->setVisible(true);
  this->startButton->setVisible(true);
  this->exitButton->setVisible(true);
  this->savesButton->setVisible(true);
}

