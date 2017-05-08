/*
** MenuController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:44:49 2017 Yassir Jabbari
// Last update Sat May  6 18:30:15 2017 Jabbari Yassir
*/
#ifndef CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
# include "IModel.hpp"
#include "MenuEventModel.hpp"
#include <vector>
#include <iostream>

class		MenuModel : public IModel
{
 public:
  MenuModel(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		 irr::scene::ISceneManager *smgr,
		 irr::gui::IGUIEnvironment *guienv, std::vector<std::string> saves);
  MenuModel(MenuModel const &);
  MenuModel &operator=(MenuModel const &);
  virtual ~MenuModel();
  virtual void setModelProperties();

  virtual bool launchModel(irr::IrrlichtDevice *);

 private:
  virtual void setBlockProperties(int, int);

  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::scene::ISceneManager			*_smgr;
  irr::gui::IGUIEnvironment			*_guienv;
  irr::gui::IGUISkin				*skin;
  irr::gui::IGUIFont				*font;
  irr::gui::IGUITabControl			*tabctrl;
  irr::gui::IGUITab				*mainCtrl;
  irr::gui::IGUITab				*aboutTab;
  irr::gui::IGUIListBox				*boxSave;
  irr::s32					selected;
  irr::gui::IGUIButton				*startButton;
  irr::gui::IGUIButton				*optionButton;
  irr::gui::IGUIButton				*exitButton;
  irr::video::ITexture				*background;
  MenuEventModel				event;
  std::vector<std::string>			_saves;
};

#endif //CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
