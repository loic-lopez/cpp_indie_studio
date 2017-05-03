//
// IModel.hpp for IModel.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:13:18 2017 Stanislas Deneubourg
// Last update Wed May  3 18:58:13 2017 Stanislas Deneubourg
//

#ifndef	IMODEL_HPP__
#define IMODEL_HPP__

#include <irrlicht.h>

class	IModel
{
public:
  virtual	~IModel() {};
  virtual void	init() = 0;
  virtual void	setModelProperties() = 0;
};

#endif
