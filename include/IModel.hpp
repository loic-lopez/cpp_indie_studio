//
// IModel.hpp for IModel.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:13:18 2017 Stanislas Deneubourg
// Last update Mon May 29 17:56:39 2017 Stanislas Deneubourg
//

#ifndef	IMODEL_HPP__
#define IMODEL_HPP__

#include <irrlicht.h>
#include "EventStatus.hpp"

class	IModel
{
 public:
  virtual	~IModel() {};

  virtual void setModelProperties() = 0;

  virtual EventStatus launchModel() = 0;
};

#endif
