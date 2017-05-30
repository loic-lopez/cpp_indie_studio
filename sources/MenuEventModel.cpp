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
	  case MenuButton::OPTIONS:
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		this->optionButton->setVisible(false);
		this->startButton->setVisible(false);
		this->exitButton->setVisible(false);
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
		this->optionButton->setVisible(true);
		this->startButton->setVisible(true);
		this->exitButton->setVisible(true);
		this->checkboxSound->setVisible(false);
		this->backButton->setVisible(false);
		this->checkboxWalls->setVisible(false);
		break;
	      }
	  default:
	    break;
	}
    }
  return (false);
}

void	MenuEventModel::setSelected(irr::s32 const &selected)
{
  this->selected = selected;
}

void	MenuEventModel::setEventStatus(EventStatus &eventStatus)
{
  this->eventStatus = &eventStatus;
}

// BUTTONS
void	MenuEventModel::setStartButton(irr::gui::IGUIButton *startButton)
{
  this->startButton = startButton;
}

void	MenuEventModel::setOptionButton(irr::gui::IGUIButton *optionButton)
{
  this->optionButton = optionButton;
}

void	MenuEventModel::setExitButton(irr::gui::IGUIButton *exitButton)
{
  this->exitButton = exitButton;
}

void	MenuEventModel::setBackButton(irr::gui::IGUIButton *backButton)
{
  this->backButton = backButton;
  this->backButton->setUseAlphaChannel(true);
  this->backButton->setDrawBorder(false);
  this->backButton->setVisible(false);
}

//CHECKBOXES

void	MenuEventModel::setSoundCheckboxAndTextures(irr::gui::IGUIButton *checkboxSound,
							irr::video::ITexture *checkboxSoundChecked,
							irr::video::ITexture *checkboxSoundNotChecked)
{
  this->checkboxSound = checkboxSound;
  this->checkboxSound->setUseAlphaChannel(true);
  this->checkboxSound->setDrawBorder(false);
  this->checkboxSound->setVisible(false);
  this->checkboxSound->setImage(checkboxSoundChecked);
  this->checkboxSoundStatus = true;
  this->checkboxSoundChecked = checkboxSoundChecked;
  this->checkboxSoundNotChecked = checkboxSoundNotChecked;
}
void	MenuEventModel::setWallsCheckboxAndTextures(irr::gui::IGUIButton *checkboxWalls,
							irr::video::ITexture *checkboxWallsChecked,
							irr::video::ITexture *checkboxWallsNotChecked)
{
  this->checkboxWalls = checkboxWalls;
  this->checkboxWalls->setUseAlphaChannel(true);
  this->checkboxWalls->setDrawBorder(false);
  this->checkboxWalls->setVisible(false);
  this->checkboxWallsStatus = true;
  this->checkboxWallsChecked = checkboxWallsChecked;
  this->checkboxWallsNotChecked = checkboxWallsNotChecked;
  this->checkboxWalls->setImage(checkboxWallsChecked);
}

const bool &MenuEventModel::getCheckboxSoundStatus() const
{
  return (this->checkboxSoundStatus);
}

bool const &MenuEventModel::getCheckboxWallsStatus() const
{
  return (this->checkboxWallsStatus);
}

