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

#include "Dependencies/Dependencies.hpp"
#include "Events/MouseWheelState.hpp"

class MouseEvent : public irr::IEventReceiver
{
 private:
  struct SMouseState
  {
    irr::core::position2di	Position;
    bool			leftButtonDown;
    MouseWheelState 		mouseWheelState;
    SMouseState();
  }	MouseState;
  irr::SEvent	event;
public:

    
  MouseEvent();
  virtual bool	OnEvent(const irr::SEvent &event);
  irr::core::position2di	const	&getMousePosition() const;
  MouseWheelState	const	&getMouseWheelState() const;
  irr::EMOUSE_INPUT_EVENT const &getMouseEvent() const;
};

#endif
