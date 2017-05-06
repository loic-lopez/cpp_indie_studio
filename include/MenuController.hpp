/*
** MenuController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:44:49 2017 Yassir Jabbari
** Last update Sat May 06 13:44:49 2017 Yassir Jabbari
*/
#ifndef CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
# include "indie.hpp"

class		MenuController : public IModel
{
 public:
  MenuController(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		 irr::scene::ISceneManager *smgr,
		 irr::video::E_DRIVER_TYPE driverType, irr::gui::IGUIEnvironment *guienv);
  MenuController(MenuController const &);
  MenuController &operator=(MenuController const &);
  virtual ~MenuController();
  virtual void setModelProperties();
  virtual void	launchModel(irr::IrrlichtDevice *);

 private:
  virtual void setBlockProperties(int, int);

  irr::IrrlichtDevice				*_device;
  irr::video::IVideoDriver			*_driver;
  irr::scene::ISceneManager			*_smgr;
  irr::video::E_DRIVER_TYPE			_driverType;
  irr::gui::IGUIEnvironment			*_guienv;
};

#endif //CPP_INDIE_STUDIO_MENUCONTROLLER_HPP
