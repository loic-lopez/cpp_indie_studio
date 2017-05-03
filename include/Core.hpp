//
// Core.hpp for Core.hpp in /home/dupil_l/Module_C++/cpp_indie_studio/include
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 13:21:55 2017 Loïc Dupil
// Last update Wed May  3 19:00:30 2017 Stanislas Deneubourg
//

#ifndef CORE_HPP
# define CORE_HPP

#include <memory>
#include "ICore.hpp"
#include "GameEngine.hpp"
#include "SplashScreen.hpp"

class Core : public ICore
{
  std::vector<std::string>			saves;
  std::vector<std::string>			soundlib;
  std::vector<irr::video::IImage *>		textures;
  
public:
  Core();
  Core(Core const &);
  Core &operator=(Core const &);
  ~Core();

  virtual std::vector<std::string>			getSaves() const;
  virtual void						setSave(const std::string &);
  virtual void						fillSaves();
  virtual std::vector<irr::video::IImage *>		getTextures() const;
  virtual void						fillTextures();
  virtual std::vector<std::string>			getSoundLib() const;
  virtual void						fillSoundLib();
  virtual std::vector<std::string>			loadDir(const std::string &);
  virtual void						launchSplashScreen();
  virtual void						launchMenu();
  virtual void						launchGame();
  virtual void						launch();
};

#endif	// CORE_HPP
