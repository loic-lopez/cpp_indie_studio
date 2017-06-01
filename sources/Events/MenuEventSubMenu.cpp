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
  this->checkboxSound->setImage(checkboxSoundChecked);
  this->checkboxSoundStatus = true;
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
