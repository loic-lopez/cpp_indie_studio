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
  this->eventReceiver.OnEvent(event);
  return (false);
}

void MenuInGameEventModel::setEventStatus(EventStatus &status)
{
  this->eventStatus = &status;
}

bool MenuInGameEventModel::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return (this->eventReceiver.IsKeyDown(keyCode));
}

bool MenuInGameEventModel::IsKeyUp(irr::EKEY_CODE keyCode)
{
  return (this->eventReceiver.IsKeyUp(keyCode));
}