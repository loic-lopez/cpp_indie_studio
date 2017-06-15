//
// EventReceiver.cpp for event receiver in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Fri May  5 18:12:56 2017 Stanislas Deneubourg
// Last update Wed May 31 14:24:48 2017 Stanislas Deneubourg
//

#include "Events/EventReceiver.hpp"
#include <iostream>

EventStatus const &EventReceiver::getEventStatus() const
{
  return this->eventStatus;
}

EventReceiver::EventReceiver(irr::IrrlichtDevice *device, irrklang::ISound *mainSound, bool *playMainSound)
{
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    this->KeyIsDown[i] = false;

  for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    this->KeyIsUp[i] = BS_DOWN;

  this->guienv = device->getGUIEnvironment();
  this->driver = device->getVideoDriver();
  this->eventStatus = EventStatus::IN_GAME_MENU;
  this->device = device;
  this->isSoundCheckboxChecked = *playMainSound;
  this->playMainSound = playMainSound;
  this->mainSound = mainSound;
}

bool	EventReceiver::OnEvent(const irr::SEvent& event)
{
  this->eventStatus = EventStatus::IN_GAME_MENU;
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      if (event.KeyInput.PressedDown)
	this->KeyIsUp[event.KeyInput.Key] = buttonState::BS_DOWN;
      else
	this->KeyIsUp[event.KeyInput.Key] = buttonState::BS_UP;
      this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
  else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
	switch (event.MouseInput.Event)
	  {
	    case irr::EMIE_LMOUSE_PRESSED_DOWN:
	      {
		MouseState.LeftButtonDown = true;
		break;
	      }
	    case irr::EMIE_LMOUSE_LEFT_UP:
	      {
		MouseState.LeftButtonDown = false;
		break;
	      }
	    default:
	      break;
	  }
      }
  else if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32 id = event.GUIEvent.Caller->getID();
      switch (id)
	{
	  case MenuInGameButton::EXIT_IN_GAME:
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		this->eventStatus = EventStatus::QUIT;
		this->device->closeDevice();
		break;
	      }
	  case MenuInGameButton::BACK_TO_GAME:
	    if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	      {
		this->eventStatus = EventStatus::BACK_TO_GAME;
		break;
	      }
	  case MenuInGameButton::SAVE_CURRENT_GAME:
	    {
	      break;
	    }
	  case MenuInGameButton::SOUND_OPTION:
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  this->setMainButtonsHidden();
		  this->soundCheckboxButton->setVisible(true);
		  this->backButton->setVisible(true);
		  break;
		}
	    }
	  case MenuInGameButton::BACK_TO_MENU:
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  this->eventStatus = EventStatus::BACK_TO_MENU;
		  break;
		}
	    }
	  case MenuInGameButton::SOUND_OPTION_SUBMENU_SOUND_CHECKBOX:
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  if (this->isSoundCheckboxChecked)
		    {
		      this->soundCheckboxButton->setImage(this->soundCheckboxNotCheckedButton);
		      this->mainSound->setIsPaused(true);
		      this->isSoundCheckboxChecked = false;
		    }
		  else
		    {
		      this->soundCheckboxButton->setImage(this->soundCheckboxCheckedButton);
		      this->mainSound->setIsPaused(false);
		      this->isSoundCheckboxChecked = true;
		    }
		  *this->playMainSound = this->isSoundCheckboxChecked;
		  break;
		}
	    }
	  case MenuInGameButton::SUBMENU_BACK:
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  this->setMainButtonsVisible();
		  this->soundCheckboxButton->setVisible(false);
		  this->backButton->setVisible(false);
		  break;
		}
	    }
	  case InventoryButton::UZI:
	    {
	      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
		  *this->idWeapon = InventoryButton::UZI - 20;
		  *this->weaponIsSelected = true;
		  break;
		}
	    }
	  default:
	    {
	      break;
	    }
	}
    }
  return (false);
}

bool	EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->KeyIsDown[keyCode]);
}

bool	EventReceiver::IsKeyUp(irr::EKEY_CODE	keyCode)
{
  if (KeyIsUp[keyCode] == BS_UP)
    {
      KeyIsUp[keyCode] = BS_DOWN;
      return (true);
    }
  return (false);
}

void	EventReceiver::setMenuInGameButtons(irr::gui::IGUITabControl *tabctrl)
{
  irr::video::ITexture			*buttonTexture;
  irr::core::dimension2d<irr::s32>	image_size;

  buttonTexture = this->driver->getTexture("ressources/buttons/back_to_game.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->backToGameButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (15 * 34) / 5,
										 (image_size.Height / 2) + 38,
										 (image_size.Width / 2) + 8 * 34,
										 image_size.Height + 38),
						       tabctrl, MenuInGameButton::BACK_TO_GAME, L"");
      this->backToGameButton->setImage(buttonTexture);
      this->backToGameButton->setUseAlphaChannel(true);

    }

  buttonTexture = this->driver->getTexture("ressources/buttons/save_game.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->saveCurrentGameButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (7 * 34)
													    / 4,
										      (image_size.Height) +
											      image_size.Height / 2 +
											      38,
										       (image_size.Width / 2) + 6 * 34,
										       (image_size.Height * 2) +
											      image_size.Height / 2),
							     tabctrl, MenuInGameButton::SAVE_CURRENT_GAME, L"");
      this->saveCurrentGameButton->setImage(buttonTexture);
      this->saveCurrentGameButton->setUseAlphaChannel(true);

    }

  buttonTexture = this->driver->getTexture("ressources/buttons/sound_options.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->soundOptionButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (20 * 34)
													   / 5,
										  (image_size.Height * 2) +
										  image_size.Height / 2 + 38,
										       (image_size.Width / 2) + 8 * 34,
										  (image_size.Height * 3) +
										  image_size.Height / 2),
							     tabctrl, MenuInGameButton::SOUND_OPTION, L"");
      this->soundOptionButton->setImage(buttonTexture);
      this->soundOptionButton->setUseAlphaChannel(true);

    }

  buttonTexture = this->driver->getTexture("ressources/buttons/back_to_menu.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->backToMenuButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (20 * 34)
													   / 5,
										  (image_size.Height * 3) +
										  image_size.Height / 2 + 38,
										       (image_size.Width / 2) + 8 * 34,
										  (image_size.Height * 4) +
										  image_size.Height / 2),
							     tabctrl, MenuInGameButton::BACK_TO_MENU, L"");
      this->backToMenuButton->setImage(buttonTexture);
      this->backToMenuButton->setUseAlphaChannel(true);

    }

  buttonTexture = this->driver->getTexture("ressources/buttons/exit.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->exitGameButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (20 * 34)
													   / 5,
										  (image_size.Height * 4) +
										  image_size.Height / 2 + 38,
										       (image_size.Width / 2) + 8 * 34,
										  (image_size.Height * 5) +
										  image_size.Height / 2),
							     tabctrl, MenuInGameButton::EXIT_IN_GAME, L"");
      this->exitGameButton->setImage(buttonTexture);
      this->exitGameButton->setUseAlphaChannel(true);

    }

  this->soundCheckboxCheckedButton = this->driver->getTexture("ressources/buttons/checkboxes/sound_checked.png");
  this->soundCheckboxNotCheckedButton = this->driver->getTexture("ressources/buttons/checkboxes/sound_not_checked.png");
  if (this->soundCheckboxNotCheckedButton != nullptr && this->soundCheckboxCheckedButton != nullptr)
    {
      this->soundCheckboxButton = this->guienv->addButton(irr::core::rect<irr::s32>((image_size.Width / 3) - (20 * 34)
													     / 5,
											   (image_size.Height / 2) + 38,
											   (image_size.Width / 2) + 8 * 34,
											   image_size.Height + 38 * 2),
								 tabctrl, MenuInGameButton::SOUND_OPTION_SUBMENU_SOUND_CHECKBOX, L"");
      if (*this->playMainSound)
	this->soundCheckboxButton->setImage(this->soundCheckboxCheckedButton);
      else
	this->soundCheckboxButton->setImage(this->soundCheckboxNotCheckedButton);
      this->soundCheckboxButton->setUseAlphaChannel(true);
      this->soundCheckboxButton->setVisible(false);
    }

  buttonTexture = this->driver->getTexture("ressources/buttons/back.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->backButton = this->guienv->addButton(irr::core::rect<irr::s32>(tabctrl->getTabExtraWidth(),
									   (image_size.Height * 8),
									   (image_size.Width * 2),
									   (image_size.Height * 9)),
							 tabctrl, MenuInGameButton::SUBMENU_BACK, L"");
      this->backButton->setImage(buttonTexture);
      this->backButton->setUseAlphaChannel(true);
      this->backButton->setVisible(false);
    }

}

void	EventReceiver::setMainButtonsHidden()
{
  this->backToGameButton->setVisible(false);
  this->saveCurrentGameButton->setVisible(false);
  this->soundOptionButton->setVisible(false);
  this->backToMenuButton->setVisible(false);
  this->exitGameButton->setVisible(false);
}

void 	EventReceiver::setMainButtonsVisible()
{
  this->backToGameButton->setVisible(true);
  this->saveCurrentGameButton->setVisible(true);
  this->soundOptionButton->setVisible(true);
  this->backToMenuButton->setVisible(true);
  this->exitGameButton->setVisible(true);
}

EventReceiver::SMouseState::SMouseState() : LeftButtonDown(false)
{
}

void EventReceiver::setWeaponsButtons(irr::gui::IGUITabControl *tabctrl)
{
  irr::video::ITexture			*buttonTexture;
  irr::core::dimension2d<irr::s32>	image_size;

  buttonTexture = this->driver->getTexture("ressources/inventory/weapons/uzi.png");
  if (buttonTexture != nullptr)
    {
      image_size = buttonTexture->getSize();
      this->uziButton = this->guienv->addButton(irr::core::rect<irr::s32>(50 + (image_size.Width / 4), (92 + (image_size.Height / 5)),
									  50 + image_size.Width + (image_size.Width / 4),
									      image_size.Height + 92 + (image_size.Height / 5)),
						    tabctrl, InventoryButton::UZI, L"");
      this->uziButton->setImage(buttonTexture);
      this->uziButton->setUseAlphaChannel(true);
    }
}

void EventReceiver::setWeaponId(size_t *weaponid)
{
  this->idWeapon = weaponid;
}

void EventReceiver::setweaponIsSelected(bool *isSelected)
{
  this->weaponIsSelected = isSelected;
}