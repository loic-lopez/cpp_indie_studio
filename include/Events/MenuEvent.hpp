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
  void			setSubButtonHidden();
  irr::IrrlichtDevice	*device;
  EventStatus		*eventStatus;
  irr::s32		selected;
  irr::gui::IGUIListBox *savesListBox;
  irr::s32		*NbrHumanTeams;
  irr::s32		*NbrBotTeams;
  irr::s32		*NbrTeams;

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

  // PLAY SUB MENU
  irr::gui::IGUIButton	*subtractNbrTeamButton;
  irr::gui::IGUIButton	*addNbrTeamButton;
  irr::gui::IGUIButton	*subtractNbrHumanTeamsButton;
  irr::gui::IGUIButton	*addNbrHumanTeamsButton;
  irr::gui::IGUIButton	*subtractNbrBotTeamsButton;
  irr::gui::IGUIButton	*addNbrBotTeamsButton;
  irr::gui::IGUIButton	*playButton;

 public:
  MenuEvent(irr::IrrlichtDevice *device);
  virtual bool 	OnEvent(const irr::SEvent &event);
  void		setSelected(irr::s32 const &selected);

  //MAIN BUTTONS
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

  void 		setEventStatus(EventStatus &);
  void		setNbrHumanTeams(irr::s32 *NbrHumanTeams);
  void		setNbrBotTeams(irr::s32 *NbrBotTeams);
  void		setNbrTeams(irr::s32 *NbrBotTeams);
  void		setPlayAGameSubMenu(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment *guienv,
					  irr::gui::IGUITabControl*tabctrl);

  bool 	const	&getCheckboxSoundStatus() const;
  bool 	const	&getCheckboxWallsStatus() const;
  MenuButton	const	&getPressedButton() const;
  irr::s32	const	&getNbrHumanTeams() const;
  irr::s32	const	&getNbrBotTeams() const;
  irr::s32	const	&getNbrTeams() const;

};
#endif //CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
