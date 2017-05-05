//
// EventReceiver.hpp for event receiver in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Fri May  5 18:11:56 2017 Stanislas Deneubourg
// Last update Fri May  5 18:19:34 2017 Stanislas Deneubourg
//

#include <irrlicht.h>
#include <IEventReceiver.h>

class EventReceiver : public irr::IEventReceiver
{
public:
  EventReceiver();
  virtual bool OnEvent(const irr::SEvent& event);
  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

private:
  bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};
