/*
** MenuController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:44:49 2017 Yassir Jabbari
// Last update Wed May 31 14:34:58 2017 Stanislas Deneubourg
*/

#ifndef CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUCONTROLLER_HPP

# include <vector>
# include <iostream>
# include "Interface/IModel.hpp"
# include "Events/MenuEvent.hpp"
# include "Events/MenuButton.hpp"

class		MenuModel : public IModel
{
 public:
  MenuModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		 irr::scene::ISceneManager *smgr,
		 irr::gui::IGUIEnvironment *guienv, std::vector<std::string> saves, bool&, bool&);
  virtual ~MenuModel();
  virtual void setModelProperties();

  virtual EventStatus launchModel();

 private:
  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::scene::ISceneManager			*_smgr;
  irr::gui::IGUIEnvironment			*_guienv;
  irr::gui::IGUISkin				*skin;
  irr::gui::IGUIFont				*font;
  irr::gui::IGUITabControl			*tabctrl;
  irr::gui::IGUIListBox				*boxSave;
  irr::s32					selected;

  // BUTTONS
  irr::gui::IGUISpriteBank			*spriteBank;
  irr::gui::IGUIButton				*exitButton;
  irr::gui::IGUIButton				*optionButton;
  irr::gui::IGUIButton				*backButton;

  ///
  irr::video::ITexture				*background;
  irr::core::dimension2d<irr::u32> 		cursorSize;
  MenuEvent				event;
  std::vector<std::string>			_saves;

  // CHECKBOXES
  bool 						*playSound;
  bool 						*drawWalls;
  irr::gui::IGUIButton				*checkboxSound;
  irr::gui::IGUIButton				*wallsCheckbox;

  virtual	void				SetMenuModelMainOptions();
};

#endif //CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
