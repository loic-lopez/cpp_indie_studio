/*
** MenuController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:44:49 2017 Yassir Jabbari
// Last update Wed May 10 14:00:57 2017 Stanislas Deneubourg
*/
#ifndef CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUCONTROLLER_HPP

# include "IModel.hpp"
#include "MenuEventModel.hpp"
#include <vector>
#include <iostream>
# include "MenuButton.hpp"

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

  irr::gui::IGUIButton				*startButton;
  irr::gui::IGUIButton				*exitButton;
  irr::gui::IGUIButton				*optionButton;

  ///
  irr::video::ITexture				*background;
  irr::core::dimension2d<irr::u32> 		cursorSize;
  MenuEventModel				event;
  std::vector<std::string>			_saves;
  bool 						*playSound;
  bool 						*drawWalls;
  irr::gui::IGUICheckBox			*checkboxSound;
  irr::gui::IGUICheckBox			*checkboxWalls;
  irr::gui::IGUISpriteBank			*spriteBank;
};

#endif //CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
