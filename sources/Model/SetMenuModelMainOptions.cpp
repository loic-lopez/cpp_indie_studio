/*
** MenuModelMainOptions.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/MenuModelMainOptions.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 31 14:02:11 2017 Loïc Lopez
// Last update Wed May 31 14:43:35 2017 Stanislas Deneubourg
*/

#include "Model/MenuModel.hpp"

void	MenuModel::SetMenuModelMainOptions()
{
  irr::core::dimension2d<irr::s32>	image_size;
  irr::video::ITexture			*texture;

  //play button
  texture = this->_driver->getTexture("ressources/buttons/play_a_game.png");
  image_size = texture->getSize();
  this->event.setStartButton(this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (7 * 34) / 4,
										(image_size.Height / 2),
										(image_size.Width / 2) + 7 * 34,
										image_size.Height),
						      this->tabctrl, MenuButton::PLAY_A_GAME, L""), texture);

  // OPTION BUTTON
  texture = this->_driver->getTexture("ressources/buttons/options.png");
  image_size = texture->getSize();
  this->event.setOptionButton(this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (6 * 34) / 4,
										 (image_size.Height * 3) / 2,
										 (image_size.Width / 2) + 6 * 34,
										 (image_size.Height * 4) / 2),
						       this->tabctrl, MenuButton::OPTIONS, L""), texture);

  // SAVES BUTTON
  texture = this->_driver->getTexture("ressources/buttons/saves.png");
  this->spriteBank->addTextureAsSprite(this->_driver->getTexture("ressources/buttons/saves.png"));
  image_size = texture->getSize();
  this->event.setSavesButton(this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3),
									       (image_size.Height * 5) / 2,
										(image_size.Width / 2) + 4 * 34,
									       (image_size.Height * 6) / 2),
						     this->tabctrl, MenuButton::SAVES, L""), texture);

  //exit button
  texture = this->_driver->getTexture("ressources/buttons/exit.png");
  image_size = texture->getSize();
  this->event.setExitButton(this->_guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (6 * 34) / 4,
									       (image_size.Height * 7) / 2,
									       (image_size.Width / 2) + 6 * 34,
									       (image_size.Height * 8) / 2) ,
						     this->tabctrl, MenuButton::EXIT, L""), texture);
}
