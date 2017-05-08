//
// IModel.hpp for IModel.hpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:13:18 2017 Stanislas Deneubourg
// Last update Thu May  4 16:59:47 2017 Stanislas Deneubourg
//

#ifndef	IMODEL_HPP__
#define IMODEL_HPP__

#include <irrlicht.h>

class	IModel
{
 private:
  virtual void setBlockProperties(int, int) = 0;

 public:
  virtual	~IModel() {};

  virtual void setModelProperties() = 0;

  virtual bool launchModel(irr::IrrlichtDevice *) = 0;
};

#endif
