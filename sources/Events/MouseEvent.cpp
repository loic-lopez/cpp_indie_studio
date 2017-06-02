/*
** MouseEvent.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/MouseEvent.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 02 12:47:59 2017 Loïc Lopez
** Last update ven. juin 02 12:47:59 2017 Loïc Lopez
*/

#include <iostream>
#include "Events/MouseEvent.hpp"

MouseEvent::MouseEvent()
{
}

bool MouseEvent::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EEVENT_TYPE::EET_MOUSE_INPUT_EVENT)
    {
      this->event = event;
      switch(event.MouseInput.Event)
	{
	  case irr::EMOUSE_INPUT_EVENT::EMIE_MOUSE_MOVED:
	    {
	      std::cout << "MOUSE MOVED" << std::endl;
	      MouseState.Position.X = event.MouseInput.X;
	      MouseState.Position.Y = event.MouseInput.Y;
	      break;
	    }
	  case irr::EMOUSE_INPUT_EVENT::EMIE_MOUSE_WHEEL:
	    {
	      std::cout << "WHEEL VALUE: " + std::to_string(event.MouseInput.Wheel) << std::endl;
	      if (event.MouseInput.Wheel > 0)
		MouseState.mouseWheelState = MouseWheelState::SCROLL_UP;
	      else if (event.MouseInput.Wheel < 0)
		MouseState.mouseWheelState = MouseWheelState::SCROLL_DOWN;
	      else
		MouseState.mouseWheelState = MouseWheelState::STANDBY;
	      break;
	    }
	  default:
	    break;
	}
    }
  return false;
}

MouseEvent::SMouseState::SMouseState() : leftButtonDown(false)
{
}

irr::core::position2di	const	&MouseEvent::getMousePosition() const
{
  return this->MouseState.Position;
}

MouseWheelState const &MouseEvent::getMouseWheelState() const
{
  return this->MouseState.mouseWheelState;
}

irr::EMOUSE_INPUT_EVENT const &MouseEvent::getMouseEvent() const
{
  return this->event.MouseInput.Event;
}