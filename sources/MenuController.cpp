/*
** MenuController.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuController.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 13:52:58 2017 Yassir Jabbari
** Last update Sat May 06 13:52:58 2017 Yassir Jabbari
*/

#include "MenuController.hpp"

MenuController::MenuController(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
irr::scene::ISceneManager *smgr, irr::video::E_DRIVER_TYPE driverType, irr::gui::IGUIEnvironment *guienv)
	: _device(device), _driver(driver), _smgr(smgr), _driverType(driverType), _guienv(guienv)
{

}

MenuController::MenuController(MenuController const &other)
{
  this->_device = other._device;
  this->_driver = other._driver;
  this->_smgr = other._smgr;
  this->_driverType = other._driverType;
  this->_guienv = other._guienv;
}

MenuController& MenuController::operator=(MenuController const &other)
{
  if (this != &other)
    {
      this->_device = other._device;
      this->_driver = other._driver;
      this->_smgr = other._smgr;
      this->_driverType = other._driverType;
      this->_guienv = other._guienv;
    }
  return (*this);
}

MenuController::~MenuController()
{
}

void MenuController::setModelProperties()
{

}

void MenuController::launchModel(irr::IrrlichtDevice *device)
{
  (void)device;
}

void MenuController::setBlockProperties(int x, int y)
{
  (void)x;
  (void)y;
}