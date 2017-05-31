/*
** MenuEventController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuEventController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 17:31:42 2017 Yassir Jabbari
// Last update Sat May  6 18:30:54 2017 Jabbari Yassir
*/
#ifndef CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP

#include <string>
#include <vector>
#include "Dependencies/Dependencies.hpp"
#include "EventStatus.hpp"
#include "MenuButton.hpp"

class MenuEvent : public irr::IEventReceiver
{
private:
  // GENERAL
  void 			setMainButtonsHidden();
  void 			setMainButtonsVisible();
  irr::IrrlichtDevice	*device;
  EventStatus		*eventStatus;
  irr::s32		selected;
  irr::gui::IGUIListBox *savesListBox;

  // BUTTONS
  irr::gui::IGUIButton	*startButton;
  irr::gui::IGUIButton	*exitButton;
  irr::gui::IGUIButton	*optionButton;
  irr::gui::IGUIButton	*backButton;
  irr::gui::IGUIButton	*savesButton;

  //CHECKBOXES
  irr::gui::IGUIButton 	*checkboxSound;
  bool 			checkboxSoundStatus;
  irr::video::ITexture	*checkboxSoundChecked;
  irr::video::ITexture	*checkboxSoundNotChecked;

  //WALLS
  irr::gui::IGUIButton 	*checkboxWalls;
  bool 			checkboxWallsStatus;
  irr::video::ITexture	*checkboxWallsChecked;
  irr::video::ITexture	*checkboxWallsNotChecked;
  MenuButton 		button;

 public:
  MenuEvent(irr::IrrlichtDevice *device);
  virtual bool OnEvent(const irr::SEvent &event);
  void		setSelected(irr::s32 const &selected);

  //BUTTONS
  void		setStartButton(irr::gui::IGUIButton *startButton,
				     irr::video::ITexture *texture);
  void 		setExitButton(irr::gui::IGUIButton *exitButton,
				    irr::video::ITexture *texture);
  void		setOptionButton(irr::gui::IGUIButton *optionButton,
				      irr::video::ITexture *texture);
  void 		setSavesButton(irr::gui::IGUIButton *backButton,
				     irr::video::ITexture *texture);

  // SUBMENU
  void		setSoundCheckboxAndTextures(irr::gui::IGUIButton *checkboxSound,
						  irr::video::ITexture *checkboxSoundChecked,
						  irr::video::ITexture *checkboxSoundNotChecked);
  void		setWallsCheckboxAndTextures(irr::gui::IGUIButton *checkboxWalls,
						  irr::video::ITexture *checkboxWallsChecked,
						  irr::video::ITexture *checkboxWallsNotChecked);
  void		setBackButton(irr::gui::IGUIButton *backButton, irr::video::ITexture *texture);
  void		setSavesListBox(irr::gui::IGUIListBox *savesListBox, std::vector<std::string> const &saves);

  bool 	const	&getCheckboxSoundStatus() const;
  bool 	const	&getCheckboxWallsStatus() const;
  MenuButton	const	&getPressedButton() const;

  void setEventStatus(EventStatus &);
};
#endif //CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
