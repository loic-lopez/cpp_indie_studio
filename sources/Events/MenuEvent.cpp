/*
** MenuEventController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuEventController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 17:36:48 2017 Yassir Jabbari
// Last update Wed Jun 14 11:02:32 2017 Stanislas Deneubourg
*/

#include "Events/MenuEvent.hpp"

MenuEvent::MenuEvent(irr::IrrlichtDevice *device, irrklang::ISound *mainSound, bool *playMainSound)
{
  this->device = device;
  this->button = MenuButton::STANDBY;
  this->mainSound = mainSound;
  this->playMainSound = playMainSound;
  this->checkboxSoundStatus = *playMainSound;
  std::srand(std::time(nullptr));
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
	      case MenuButton::PLAY_A_GAME:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    this->button = static_cast<MenuButton>(id);
		    this->setMainButtonsHidden();
		    this->setPlaySubMenuVisible();
		    break;
		  }
	      case MenuButton::PLAY:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    *this->eventStatus = EventStatus::ENTER_IN_GAME;
		    return true;
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
			if (this->mainSound != nullptr)
			  this->mainSound->setIsPaused(true);
		      }
		    else
		      {
			this->checkboxSoundStatus = true;
			this->checkboxSound->setImage(this->checkboxSoundChecked);
			if (this->mainSound != nullptr)
			  this->mainSound->setIsPaused(false);
		      }
		    *this->playMainSound = this->checkboxSoundStatus;
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
		    this->setSubButtonHidden();
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_ADD_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrTeams < 4)
		      {
			*this->NbrTeams += 1;
			if (*this->NbrBotTeams == *this->NbrHumanTeams)
			  {
			    if ((std::rand() % 2) == 0)
			      *this->NbrHumanTeams += 1;
			    else
			      *this->NbrBotTeams += 1;
			  }
			else if (*this->NbrBotTeams > *this->NbrHumanTeams)
			  *this->NbrHumanTeams += 1;
			else if (*this->NbrBotTeams < *this->NbrHumanTeams)
			  *this->NbrBotTeams += 1;
		      }
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrTeams > 2)
		      {
			*this->NbrTeams -= 1;
			if (*this->NbrBotTeams == *this->NbrHumanTeams)
			  {
			    if ((std::rand() % 2) == 0)
			      *this->NbrHumanTeams -= 1;
			    else
			      *this->NbrBotTeams -= 1;
			  }
			else if (*this->NbrHumanTeams > *this->NbrBotTeams)
			  *this->NbrHumanTeams -= 1;
			else if (*this->NbrBotTeams > *this->NbrHumanTeams)
			  *this->NbrBotTeams -= 1;

		      }
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_ADD_HUMAN_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrHumanTeams + *this->NbrBotTeams < *this->NbrTeams)
		      *this->NbrHumanTeams += 1;
		    else if (*this->NbrHumanTeams + *this->NbrBotTeams == *this->NbrTeams && *this->NbrBotTeams > 0)
		      {
			*this->NbrHumanTeams += 1;
			*this->NbrBotTeams -= 1;
		      }
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_HUMAN_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrHumanTeams + *this->NbrBotTeams > *this->NbrTeams)
		      *this->NbrHumanTeams -= 1;
		    else if (*this->NbrHumanTeams + *this->NbrBotTeams == *this->NbrTeams && *this->NbrHumanTeams > 0)
		      {
			*this->NbrHumanTeams -= 1;
			*this->NbrBotTeams += 1;
		      }
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_ADD_BOT_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrHumanTeams + *this->NbrBotTeams < *this->NbrTeams)
		      *this->NbrBotTeams += 1;
		    else if (*this->NbrHumanTeams + *this->NbrBotTeams == *this->NbrTeams && *this->NbrHumanTeams > 0)
		      {
			*this->NbrHumanTeams -= 1;
			*this->NbrBotTeams += 1;
		      }
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_BOT_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrHumanTeams + *this->NbrBotTeams > *this->NbrTeams)
		      {
			*this->NbrBotTeams -= 1;
		      }
		    else if (*this->NbrHumanTeams + *this->NbrBotTeams == *this->NbrTeams && *this->NbrBotTeams > 0)
		      {
			  *this->NbrBotTeams -= 1;
			  *this->NbrHumanTeams += 1;
		      }
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_ADD_WORMS_PER_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrWormsPerTeam < 8)
		      *this->NbrWormsPerTeam += 1;
		    break;
		  }
	      case MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_WORMS_PER_TEAM:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		  {
		    if (*this->NbrWormsPerTeam > 2)
		      *this->NbrWormsPerTeam -= 1;
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

void MenuEvent::setNbrHumanTeams(irr::s32 *NbrHumanTeams)
{
  this->NbrHumanTeams = NbrHumanTeams;
}

void MenuEvent::setNbrBotTeams(irr::s32 *NbrBotTeams)
{
  this->NbrBotTeams = NbrBotTeams;
}

void MenuEvent::setNbrTeams(irr::s32 *NbrTeams)
{
  this->NbrTeams = NbrTeams;
}

irr::s32 	const 	&MenuEvent::getNbrHumanTeams() const
{
  return *this->NbrHumanTeams;
}

irr::s32	const	&MenuEvent::getNbrBotTeams() const
{
  return *this->NbrBotTeams;
}


irr::s32 const &MenuEvent::getNbrTeams() const
{
  return *this->NbrTeams;
}

irr::s32 const &MenuEvent::getNbrWormsPerTeam() const
{
  return *this->NbrWormsPerTeam;
}

void	MenuEvent::setNbrWormsPerTeam(irr::s32 *NbrWormsPerTeam)
{
  this->NbrWormsPerTeam = NbrWormsPerTeam;
}

MenuEvent::~MenuEvent()
{

}
