/*
** MenuModelMainOptions.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/MenuModelMainOptions.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 31 14:02:11 2017 Loïc Lopez
** Last update mer. mai 31 14:02:11 2017 Loïc Lopez
*/

#include "MenuModel.hpp"

void	MenuModel::SetMenuModelMainOptions()
{
  irr::core::dimension2d<irr::s32>	image_size;
  irr::video::ITexture			*texture;

  //play button
  texture = this->_driver->getTexture("ressources/buttons/play.png");
  image_size = texture->getSize();
  this->event.setStartButton(this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3),
										image_size.Height / 2,
										(image_size.Width / 2) + 4 * 34,
										image_size.Height),
						      this->tabctrl, MenuButton::PLAY, L""), texture);


  // OPTION BUTTON
  texture = this->_driver->getTexture("ressources/buttons/options.png");
  image_size = texture->getSize();
  this->event.setOptionButton(this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 4),
										 ((image_size.Height / 2) * 2),
										 (image_size.Width / 2) + 6 * 34,
										 (image_size.Height * 2) - 45),
						       this->tabctrl, MenuButton::OPTIONS, L""), texture);


  //exit button
  texture = this->_driver->getTexture("ressources/buttons/exit.png");
  image_size = texture->getSize();
  this->exitButton = this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 4),
									((image_size.Height / 2) * 3),
									(image_size.Width / 2) + 7 * 34,
									(image_size.Height * 3) - 85) ,
					      this->tabctrl, MenuButton::EXIT, L"");
  this->exitButton->setImage(texture);
  this->exitButton->setUseAlphaChannel(true);
  this->exitButton->setDrawBorder(false);

}