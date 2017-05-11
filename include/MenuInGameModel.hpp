/*
** MenuInGameModel.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameModel.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 16:15:32 2017 Yassir Jabbari
** Last update Mon May 08 16:15:32 2017 Yassir Jabbari
*/
#ifndef CPP_INDIE_STUDIO_MENUINGAMEMODEL_HPP
#define CPP_INDIE_STUDIO_MENUINGAMEMODEL_HPP

#include "IModel.hpp"
#include "MenuInGameEventModel.hpp"

class 			MenuInGame : public IModel
{
 public:
  MenuInGame(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
	     irr::scene::ISceneManager *smgr);
  virtual ~MenuInGame();
  virtual void setModelProperties();

  virtual EventStatus launchModel();

 private:
  virtual void setBlockProperties(int, int);

 private:
  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::scene::ISceneManager			*_smgr;
  irr::gui::IGUIEnvironment			*_guienv;
  irr::gui::IGUISkin				*_skin;
  irr::gui::IGUIFont				*_font;
  irr::gui::IGUITabControl			*tabCtrl;
  irr::video::ITexture				*background;
  MenuInGameEventModel				event;
  irr::gui::IGUIButton				*exitButton;
  irr::gui::IGUIButton				*playButton;
  irr::gui::IGUIButton				*saveButton;
  irr::gui::IGUIButton				*backToMenuButton;
  irr::video::ITexture				*textuExit;
  irr::video::ITexture				*textuPlay;
  irr::video::ITexture				*textuSave;
  irr::video::ITexture				*textuBackToMenu;
};

#endif //CPP_INDIE_STUDIO_MENUINGAMEMODEL_HPP
