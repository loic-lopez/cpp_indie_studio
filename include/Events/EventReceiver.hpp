//
// EventReceiver.hpp for event receiver in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Fri May  5 18:11:56 2017 Stanislas Deneubourg
// Last update Fri May  5 18:19:34 2017 Stanislas Deneubourg
//

#include "Dependencies/Dependencies.hpp"
#include "Events/buttonState.hpp"
#include "Events/EventStatus.hpp"
#include "Events/MenuButton.hpp"

class EventReceiver : public irr::IEventReceiver
{
public:
  explicit EventReceiver(irr::IrrlichtDevice *device);
  bool 	OnEvent(const irr::SEvent& event) override;
  virtual bool 	IsKeyDown(irr::EKEY_CODE keyCode) const;
  virtual bool 	IsKeyUp(irr::EKEY_CODE keyCode);

  // custom functions
  void setMenuInGameButtons(irr::gui::IGUITabControl *tabctrl);
  EventStatus const &getEventStatus() const;

 protected:
  bool 		KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  buttonState	KeyIsUp[irr::KEY_KEY_CODES_COUNT];
  irr::gui::IGUIEnvironment			*guienv;
  irr::video::IVideoDriver			*driver;
  irr::gui::IGUIButton				*backToGameButton;
  irr::gui::IGUIButton				*saveCurrentGameButton;
  irr::gui::IGUIButton				*soundOptionButton;
  irr::gui::IGUIButton				*backToMenuButton;
  EventStatus 					eventStatus;
};
