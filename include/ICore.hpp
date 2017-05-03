/*
** ICore.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/ICore.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Wed May 03 13:24:18 2017 Yassir Jabbari
** Last update Wed May 03 13:24:18 2017 Yassir Jabbari
*/

#ifndef CPP_INDIE_STUDIO_ICORE_HPP
#define CPP_INDIE_STUDIO_ICORE_HPP
# include <iostream>
# include <vector>
# include <irrlicht.h>
# include <IImageLoader.h>

class ICore
{
 public:
  virtual ~ICore() {};
  virtual std::vector<std::string> &getSaves() const = 0;
  virtual void setSave(const std::string &) = 0;
  virtual void fillSaves() = 0;
  virtual void fillTextures() = 0;
  virtual std::vector<irr::video::IImage *> &getTextures() const = 0;
  virtual void setSound(const std::string &) = 0;
  virtual std::vector<std::string> getSound() const = 0;
};

#endif //CPP_INDIE_STUDIO_ICORE_HPP
