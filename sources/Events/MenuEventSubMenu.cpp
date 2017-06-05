/*
** MenuEventSubMenu.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/MenuEventSubMenu.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 31 15:34:36 2017 Loïc Lopez
** Last update mer. mai 31 15:34:36 2017 Loïc Lopez
*/

#include "Events/MenuEvent.hpp"

void	MenuEvent::setSoundCheckboxAndTextures(irr::gui::IGUIButton *checkboxSound,
						   irr::video::ITexture *checkboxSoundChecked,
						   irr::video::ITexture *checkboxSoundNotChecked)
{
  this->checkboxSound = checkboxSound;
  this->checkboxSound->setUseAlphaChannel(true);
  this->checkboxSound->setDrawBorder(false);
  this->checkboxSound->setVisible(false);
  if (this->checkboxSoundStatus)
    this->checkboxSound->setImage(checkboxSoundChecked);
  else
    this->checkboxSound->setImage(checkboxSoundNotChecked);
  this->checkboxSoundChecked = checkboxSoundChecked;
  this->checkboxSoundNotChecked = checkboxSoundNotChecked;
}

void	MenuEvent::setWallsCheckboxAndTextures(irr::gui::IGUIButton *checkboxWalls,
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

const bool &MenuEvent::getCheckboxSoundStatus() const
{
  return (this->checkboxSoundStatus);
}

bool const &MenuEvent::getCheckboxWallsStatus() const
{
  return (this->checkboxWallsStatus);
}

void	MenuEvent::setBackButton(irr::gui::IGUIButton *backButton, irr::video::ITexture *texture)
{
  this->backButton = backButton;
  this->backButton->setImage(texture);
  this->backButton->setUseAlphaChannel(true);
  this->backButton->setDrawBorder(false);
  this->backButton->setVisible(false);
}

void	MenuEvent::setSavesListBox(irr::gui::IGUIListBox *savesListBox, std::vector<std::string> const &saves)
{
  this->savesListBox = savesListBox;
  this->savesListBox->setVisible(false);
  for (auto const &save : saves)
    {
      std::string found = save.substr(0, save.find_last_of(".xml") - 3);
      this->savesListBox->addItem(std::wstring(found.begin(), found.end()).c_str());
    }
  this->savesListBox->setSelected(irr::s32(this->selected));
}

MenuButton	const	&MenuEvent::getPressedButton() const
{
  return (this->button);
}

void	MenuEvent::setPlayAGameSubMenu(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment *guienv,
					   irr::gui::IGUITabControl *tabctrl)
{
  irr::core::dimension2d<irr::s32>		button_size;
  irr::video::ITexture				*subtractTexture;
  irr::video::ITexture				*addTexture;
  irr::video::ITexture				*playTexture;

  subtractTexture = driver->getTexture("ressources/buttons/subtract_button.png");
  addTexture = driver->getTexture("ressources/buttons/add_button.png");
  if (addTexture != nullptr)
	button_size = subtractTexture->getSize();

  // ADD BUTTONS
  this->addNbrTeamButton = guienv->addButton(irr::core::rect<irr::s32>((button_size.Width * 3) / 2,
								       (button_size.Height),
								       button_size.Width * 3,
								       (button_size.Height * 2)),
						    tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_ADD_TEAM, L"");
  this->addNbrTeamButton->setImage(addTexture);
  this->addNbrTeamButton->setUseAlphaChannel(true);
  this->addNbrTeamButton->setVisible(false);

  this->addNbrHumanTeamsButton = guienv->addButton(irr::core::rect<irr::s32>((button_size.Width * 3) / 2,
									     (button_size.Height * 2)
									     + (button_size.Height / 2),
									     button_size.Width * 3,
									     (button_size.Height * 3)
									     + (button_size.Height / 2)),
						   tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_ADD_HUMAN_TEAM, L"");
  this->addNbrHumanTeamsButton->setImage(addTexture);
  this->addNbrHumanTeamsButton->setUseAlphaChannel(true);
  this->addNbrHumanTeamsButton->setVisible(false);

  this->addNbrBotTeamsButton = guienv->addButton(irr::core::rect<irr::s32>((button_size.Width * 3) / 2,
									   (button_size.Height * 4),
									   button_size.Width * 3,
									   (button_size.Height * 5)),
						   tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_ADD_BOT_TEAM, L"");
  this->addNbrBotTeamsButton->setImage(addTexture);
  this->addNbrBotTeamsButton->setUseAlphaChannel(true);
  this->addNbrBotTeamsButton->setVisible(false);

  this->addNbrWormsPerTeamButton = guienv->addButton(irr::core::rect<irr::s32>((button_size.Width * 3) / 2,
									       (button_size.Height * 5)
									       + (button_size.Height / 2),
									       button_size.Width * 3,
									       (button_size.Height * 6)
									       + (button_size.Height / 2)),
					       tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_ADD_WORMS_PER_TEAM, L"");
  this->addNbrWormsPerTeamButton->setImage(addTexture);
  this->addNbrWormsPerTeamButton->setUseAlphaChannel(true);
  this->addNbrWormsPerTeamButton->setVisible(false);

  // SUBTRACT BUTTONS
  this->subtractNbrTeamButton =  guienv->addButton(irr::core::rect<irr::s32>(button_size.Width / 2,
									     (button_size.Height),
									     (button_size.Width * 3) / 2,
									     (button_size.Height * 2)),
						   tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_TEAM, L"");
  this->subtractNbrTeamButton->setImage(subtractTexture);
  this->subtractNbrTeamButton->setUseAlphaChannel(true);
  this->subtractNbrTeamButton->setVisible(false);

  this->subtractNbrHumanTeamsButton =  guienv->addButton(irr::core::rect<irr::s32>(button_size.Width / 2,
										   (button_size.Height * 2)
										   + (button_size.Height / 2),
										   (button_size.Width * 3) / 2,
										   (button_size.Height * 3)
										   + (button_size.Height / 2)),
						   tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_HUMAN_TEAM, L"");
  this->subtractNbrHumanTeamsButton->setImage(subtractTexture);
  this->subtractNbrHumanTeamsButton->setUseAlphaChannel(true);
  this->subtractNbrHumanTeamsButton->setVisible(false);

  this->subtractNbrBotTeamsButton =  guienv->addButton(irr::core::rect<irr::s32>(button_size.Width / 2,
										 (button_size.Height * 4),
										 (button_size.Width * 3) / 2,
										 (button_size.Height * 5)),
						   tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_BOT_TEAM, L"");
  this->subtractNbrBotTeamsButton->setImage(subtractTexture);
  this->subtractNbrBotTeamsButton->setUseAlphaChannel(true);
  this->subtractNbrBotTeamsButton->setVisible(false);

  this->subtractNbrWormsPerTeamButton =  guienv->addButton(irr::core::rect<irr::s32>(button_size.Width / 2,
										     (button_size.Height * 5)
										     + (button_size.Height / 2),
										 (button_size.Width * 3) / 2,
										     (button_size.Height * 6)
										     + (button_size.Height / 2)),
						   tabctrl, MenuButton::PLAY_A_GAME_SUBMENU_SUBTRACT_WORMS_PER_TEAM, L"");
  this->subtractNbrWormsPerTeamButton->setImage(subtractTexture);
  this->subtractNbrWormsPerTeamButton->setUseAlphaChannel(true);
  this->subtractNbrWormsPerTeamButton->setVisible(false);

  // PLAY BUTTON
  playTexture = driver->getTexture("ressources/buttons/play.png");
  if (playTexture != nullptr)
  {
	  button_size = playTexture->getSize();
	  this->playButton = guienv->addButton(irr::core::rect<irr::s32>((button_size.Width / 3),
		  ((button_size.Height / 2) * 14) - 38 / 2,
		  (button_size.Width / 2) + 4 * 34,
		  ((button_size.Height / 2) * 15) - 38 / 2),
		  tabctrl, MenuButton::PLAY, L"");
	  this->playButton->setImage(playTexture);
	  this->playButton->setUseAlphaChannel(true);
	  this->playButton->setVisible(false);
  }
}



void	MenuEvent::setSubButtonHidden()
{
  this->checkboxSound->setVisible(false);
  this->backButton->setVisible(false);
  this->checkboxWalls->setVisible(false);
  this->savesListBox->setVisible(false);
  this->addNbrTeamButton->setVisible(false);
  this->subtractNbrTeamButton->setVisible(false);
  this->playButton->setVisible(false);
  this->addNbrHumanTeamsButton->setVisible(false);
  this->subtractNbrHumanTeamsButton->setVisible(false);
  this->subtractNbrBotTeamsButton->setVisible(false);
  this->addNbrBotTeamsButton->setVisible(false);
  this->addNbrWormsPerTeamButton->setVisible(false);
  this->subtractNbrWormsPerTeamButton->setVisible(false);
}

void	MenuEvent::setPlaySubMenuVisible()
{
  this->addNbrTeamButton->setVisible(true);
  this->subtractNbrTeamButton->setVisible(true);
  this->addNbrHumanTeamsButton->setVisible(true);
  this->subtractNbrHumanTeamsButton->setVisible(true);
  this->addNbrBotTeamsButton->setVisible(true);
  this->subtractNbrBotTeamsButton->setVisible(true);
  this->addNbrWormsPerTeamButton->setVisible(true);
  this->subtractNbrWormsPerTeamButton->setVisible(true);
  this->playButton->setVisible(true);
  this->backButton->setVisible(true);
}
