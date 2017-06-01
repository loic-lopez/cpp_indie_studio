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
		 irr::gui::IGUIEnvironment *guienv, std::vector<std::string> const &saves, bool&, bool&);
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
  irr::s32					selected;
  irr::core::dimension2du 			screenSize;
  irr::core::dimension2d<irr::u32>		saveSubMenuSpriteSize;

  // BUTTONS
  irr::gui::IGUISpriteBank			*spriteBank;

  ///
  irr::video::ITexture				*background;
  irr::video::ITexture				*saveSubMenuText;
  irr::core::dimension2d<irr::u32> 		cursorSize;
  MenuEvent					event;
  std::vector<std::string>			_saves;

  // CHECKBOXES
  bool 						*playSound;
  bool 						*drawWalls;
  irr::gui::IGUIButton				*checkboxSound;
  irr::gui::IGUIButton				*wallsCheckbox;

  virtual	void				SetMenuModelMainOptions();
  virtual 	void				setSkinTransparency();

  enum		SpriteName	:	uint8_t
  {
    BACKGROUND			=	0,
    SAVE_SUB_MENU		=	1
  };
};

#endif //CPP_INDIE_STUDIO_MENUCONTROLLER_HPP