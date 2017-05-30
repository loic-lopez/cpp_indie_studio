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

#include <irrlicht.h>
#include "EventStatus.hpp"
#include "MenuButton.hpp"

class MenuEventModel : public irr::IEventReceiver
{
private:
  // GENERAL
  irr::IrrlichtDevice	*device;
  EventStatus		*eventStatus;
  irr::s32		selected;

  // BUTTONS
  irr::gui::IGUIButton	*startButton;
  irr::gui::IGUIButton	*exitButton;
  irr::gui::IGUIButton	*optionButton;
  irr::gui::IGUIButton	*backButton;

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

 public:
  MenuEventModel(irr::IrrlichtDevice *device);
  virtual bool OnEvent(const irr::SEvent &event);
  void		setSelected(irr::s32 const &selected);

  //BUTTONS
  void		setStartButton(irr::gui::IGUIButton *startButton);
  void 		setExitButton(irr::gui::IGUIButton *exitButton);
  void		setOptionButton(irr::gui::IGUIButton *startButton);
  void		setBackButton(irr::gui::IGUIButton *backButton);
  void		setSoundCheckboxAndTextures(irr::gui::IGUIButton *checkboxSound,
						  irr::video::ITexture *checkboxSoundChecked,
						  irr::video::ITexture *checkboxSoundNotChecked);
  void		setWallsCheckboxAndTextures(irr::gui::IGUIButton *checkboxWalls,
						  irr::video::ITexture *checkboxWallsChecked,
						  irr::video::ITexture *checkboxWallsNotChecked);

  bool 	const	&getCheckboxSoundStatus() const;
  bool 	const	&getCheckboxWallsStatus() const;

  void setEventStatus(EventStatus &);
};
#endif //CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
