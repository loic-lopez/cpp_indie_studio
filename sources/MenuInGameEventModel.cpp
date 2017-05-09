/*
** MenuInGameEventModel.cpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuInGameEventModel.cpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Mon May 08 18:05:17 2017 Yassir Jabbari
** Last update Mon May 08 18:05:17 2017 Yassir Jabbari
*/

#include "MenuInGameEventModel.hpp"

MenuInGameEventModel::MenuInGameEventModel(irr::IrrlichtDevice *device)
{
  this->device = device;
}

bool MenuInGameEventModel::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return (false);
}

void MenuInGameEventModel::setEventStatus(EventStatus &status)
{
  this->eventStatus = &status;
}

bool MenuInGameEventModel::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->KeyIsDown[keyCode]);
}