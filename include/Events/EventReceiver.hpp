//
// EventReceiver.hpp for event receiver in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Fri May  5 18:11:56 2017 Stanislas Deneubourg
// Last update Fri May  5 18:19:34 2017 Stanislas Deneubourg
//

#ifndef EVENTRECEIVER_HPP
  #define EVENTRECEIVER_HPP
#include "Dependencies/Dependencies.hpp"
#include "Events/buttonState.hpp"
#include "Events/EventStatus.hpp"
#include "Events/MenuButton.hpp"

class EventReceiver : public irr::IEventReceiver
{
public:
  struct SMouseState
  {
    bool 		LeftButtonDown;
    SMouseState();
  } MouseState;

  explicit 					EventReceiver(irr::IrrlichtDevice *device,
								irrklang::ISound *mainSound, bool *playMainSound);
  bool 						OnEvent(const irr::SEvent& event) override;
  virtual 				bool	IsKeyDown(irr::EKEY_CODE keyCode) const;
  virtual 				bool	IsKeyUp(irr::EKEY_CODE keyCode);

  // custom functions
  void 						setMenuInGameButtons(irr::gui::IGUITabControl *tabctrl);
  void 						setWeaponsButtons(irr::gui::IGUITabControl *tabctrl);
  EventStatus 				const	&getEventStatus() const;
  void						setMainButtonsHidden();
  void						setMainButtonsVisible();
  void 						setWeaponId(size_t *);

 protected:
  // ESSENTIALS
  bool 						KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool 						*playMainSound;
  buttonState					KeyIsUp[irr::KEY_KEY_CODES_COUNT];
  irr::gui::IGUIEnvironment			*guienv;
  irr::video::IVideoDriver			*driver;
  irr::IrrlichtDevice				*device;

  // BUTTONS
  irr::gui::IGUIButton				*backToGameButton;
  irr::gui::IGUIButton				*uziButton;
  irr::gui::IGUIButton				*shotgunButton;
  irr::gui::IGUIButton				*saveCurrentGameButton;
  irr::gui::IGUIButton				*soundOptionButton;
  irr::gui::IGUIButton				*backToMenuButton;
  irr::gui::IGUIButton				*exitGameButton;
  irr::gui::IGUIButton				*soundCheckboxButton;
  irr::video::ITexture				*soundCheckboxCheckedButton;
  irr::video::ITexture				*soundCheckboxNotCheckedButton;
  bool						isSoundCheckboxChecked;
  irr::gui::IGUIButton				*backButton;
  irrklang::ISound 				*mainSound;

  // OTHER
  EventStatus 					eventStatus;
  size_t					*idWeapon;
};

#endif //EVENTRECEIVER_HPP