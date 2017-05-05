//
// EventReceiver.cpp for event receiver in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Fri May  5 18:12:56 2017 Stanislas Deneubourg
// Last update Fri May  5 18:45:52 2017 Stanislas Deneubourg
//

#include "EventReceiver.hpp"
#include <iostream>

EventReceiver::EventReceiver()
{
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    this->KeyIsDown[i] = false;
}

bool	EventReceiver::OnEvent(const irr::SEvent& event)
{
  // Remember whether each key is down or up
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return (false);
}

    // This is used to check whether a key is being held down
bool	EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->KeyIsDown[keyCode]);
}

