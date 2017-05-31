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

EventReceiver::EventReceiver()
{
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    this->KeyIsDown[i] = false;

  for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    KeyIsUp[i] = BS_DOWN;

}

bool	EventReceiver::OnEvent(const irr::SEvent& event)
{
  // Remember whether each key is down or up
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      if (event.KeyInput.PressedDown)
	{
	  this->KeyIsUp[event.KeyInput.Key] = buttonState::BS_DOWN;
	  this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
      else
	{
	  this->KeyIsUp[event.KeyInput.Key] = buttonState::BS_UP;
	  this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
    }

  return (false);
}

    // This is used to check whether a key is being held down
bool	EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->KeyIsDown[keyCode]);
}

bool EventReceiver::IsKeyUp(irr::EKEY_CODE keyCode)
{
  if (KeyIsUp[keyCode] == BS_UP)
    {
      KeyIsUp[keyCode] = BS_DOWN;
      return (true);
    }
  return (false);
}

