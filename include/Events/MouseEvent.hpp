//
// MouseEvent.hpp for mouse event in /home/deneub_s/cpp_indie_studio/include/Events
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 14:28:50 2017 Stanislas Deneubourg
// Last update Thu Jun  1 14:47:43 2017 Stanislas Deneubourg
//

#ifndef	MOUSE_EVENT_HPP
#define	MOUSE_EVENT_HPP

#include <string>
#include <vector>
#include "Dependencies/Dependencies.hpp"
#include "Event/EventReceiver.hpp"

class MouseEvent : public irr::iEventReceiver
{
public:
  struct SMouseState
  {
    core::position2di	position;
    bool		leftButtonDown;
    SMouseState() : LeftButtonDown(false) {}
  }	MouseState;
    
  MouseEvent();
  virtual bool	OnEvent(const irr::SEvent &event);
  virtual
}

#endif
