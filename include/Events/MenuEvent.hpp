/*
** MenuEventController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuEventController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 17:31:42 2017 Yassir Jabbari
// Last update Wed Jun 14 10:56:06 2017 Stanislas Deneubourg
*/
#ifndef CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP

#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
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
  void			setPlaySubMenuVisible();

  irr::IrrlichtDevice	*device;
  irrklang::ISound	*mainSound;
  EventStatus		*eventStatus;
  irr::s32		selected;
  irr::gui::IGUIListBox *savesListBox;
  irr::s32		*NbrHumanTeams;
  irr::s32		*NbrBotTeams;
  irr::s32		*NbrTeams;
  irr::s32		*NbrWormsPerTeam;

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
  irr::gui::IGUIButton	*subtractNbrWormsPerTeamButton;
  irr::gui::IGUIButton	*addNbrWormsPerTeamButton;
  irr::gui::IGUIButton	*playButton;

  bool 			*playMainSound;

 public:
  MenuEvent(irr::IrrlichtDevice *device, irrklang::ISound *mainSound, bool *playMainSound);
  virtual bool 	OnEvent(const irr::SEvent &event);
  virtual	~MenuEvent();
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
  void		setNbrWormsPerTeam(irr::s32 *NbrWormsPerTeam);
  void		setPlayAGameSubMenu(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment *guienv,
					  irr::gui::IGUITabControl*tabctrl);

  bool 	const	&getCheckboxSoundStatus() const;
  bool 	const	&getCheckboxWallsStatus() const;
  MenuButton	const	&getPressedButton() const;
  irr::s32	const	&getNbrHumanTeams() const;
  irr::s32	const	&getNbrBotTeams() const;
  irr::s32	const	&getNbrTeams() const;
  irr::s32	const	&getNbrWormsPerTeam() const;

};
#endif //CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
