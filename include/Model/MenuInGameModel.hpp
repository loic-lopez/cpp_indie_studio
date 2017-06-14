/*
** MenuInGameModel.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameModel.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 16:15:32 2017 Yassir Jabbari
// Last update Wed May 31 14:36:59 2017 Stanislas Deneubourg
*/

#ifndef CPP_INDIE_STUDIO_MENUINGAMEMODEL_HPP
#define CPP_INDIE_STUDIO_MENUINGAMEMODEL_HPP

#include "Dependencies/Dependencies.hpp"
#include "Events/EventStatus.hpp"
#include "Events/EventReceiver.hpp"

class 			MenuInGame
{
 public:
  MenuInGame(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
	     irr::scene::ISceneManager *smgr, EventReceiver &receiver);
  ~MenuInGame();
  void 		setModelProperties();
  EventStatus 	launchModel();
  void		showTabCtrl();
  void		hideTabCtrl();

 private:
  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::scene::ISceneManager			*_smgr;
  irr::gui::IGUIEnvironment			*_guienv;
  irr::gui::IGUISkin				*_skin;
  irr::gui::IGUITabControl			*tabctrl;
  EventStatus 					eventStatus;
  irr::core::dimension2du		 	screenSize;
  irr::gui::IGUISpriteBank			*spriteBank;
  irr::core::dimension2d<irr::u32> 		cursorSize;
  EventReceiver 				&eventReceiver;

  enum		MenuInGameSpriteName	:	uint8_t
  {
    LITTLE_MENU			=	0,
    CURSOR			=	1
  };

};

#endif //CPP_INDIE_STUDIO_MENUINGAMEMODEL_HPP
