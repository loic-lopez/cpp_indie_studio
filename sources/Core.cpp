//
// Core.cpp for Core.cpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 13:51:01 2017 Loïc Dupil
// Last update Sat May  6 18:15:09 2017 Jabbari Yassir
//

#include "Core.hpp"
#include "Encap.hpp"

static int check_extension_file(std::string const &filename, std::string const &extension)
{
  const auto &tmp = filename;
  std::size_t pos = tmp.find_last_of('.');

  if (pos == std::string::npos || tmp.substr(pos, tmp.size()) != extension)
    {
      std::cout << "Error: Bad file extension." << std::endl;
      return (-1);
    }
  return (0);
}

Core::Core()
{
  this->driverType = irr::video::EDT_OPENGL;
  this->device = irr::createDevice(this->driverType,
				   irr::core::dimension2d<irr::u32>(1920, 1080), 32);

  this->driver = device->getVideoDriver();
  this->smgr = device->getSceneManager();
  this->smgr->addLightSceneNode(0, irr::core::vector3df(-15,5,-105),
				irr::video::SColorf(0.5f, 0.5f, 0.5f));
  this->guienv = this->device->getGUIEnvironment();

  // set ambient light
  this->smgr->setAmbientLight(irr::video::SColor(0,60,60,60));
  this->device->getCursorControl()->setVisible(false);
  this->gameEngine = nullptr;
  this->menu = nullptr;
  this->play = true;
}

Core::Core(Core const &obj)
{

}

Core				&Core::operator=(Core const &obj)
{
  return (*this);
}

Core::~Core()
{
  this->device->drop();
  delete this->gameEngine;
  delete this->menu;
}

std::vector<std::string>	Core::getSaves() const
{
  return (this->saves);
}

void				Core::setSave(const std::string &saveName)
{
  this->saves.push_back(saveName);
}

void				Core::fillSaves()
{
  DIR				*dir;
  struct dirent			*direntp;
  std::string			file;

  if ((dir = Encap::c_opendir("saves/")) == nullptr)
    {
      std::cerr << "No saves directory" << std::endl;
      return ;
    }
  while ((direntp = Encap::c_readdir(dir)) != nullptr)
    {
      file = direntp->d_name;
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (check_extension_file(file, ".xml") == 0))
	    this->saves.emplace_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
}

std::vector<irr::video::IImage *>		Core::getTextures() const
{
  return (this->textures);
}

void						Core::fillTextures()
{
  return ;
}

std::vector<std::string>			Core::getSoundLib() const
{
  return (this->soundlib);
}

void						Core::fillSoundLib()
{
  DIR				*dir;
  struct dirent			*direntp;
  std::string			file;

  if ((dir = Encap::c_opendir("ressources/sounds/")) == nullptr)
    {
      std::cerr << "No saves directory" << std::endl;
      return ;
    }
  while ((direntp = Encap::c_readdir(dir)) != nullptr)
    {
      file = direntp->d_name;
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (check_extension_file(file, ".wav") == 0))
	    this->saves.emplace_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
}

std::vector<std::string>			Core::loadDir(const std::string &path, const std::string &file_extension)
{
  DIR				*dir;
  struct dirent			*direntp;
  std::vector<std::string>	content;

  if ((dir = Encap::c_opendir(path.c_str())) == nullptr)
    {
      std::cerr << path << ": No such file or directory directory" << std::endl;
      return (content);
    }
  while ((direntp = Encap::c_readdir(dir)) != nullptr)
    {

      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (check_extension_file(direntp->d_name, file_extension) == 0))
	    content.emplace_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
  free(direntp);
  return (content);
}

void						Core::launchSplashScreen()
{
  std::unique_ptr<IModel>			splashScreen(new SplashScreen);

  return;
}

void						Core::launchMenu()
{
  this->device->getCursorControl()->setVisible(true);
  this->menu = new MenuModel(this->device, this->driver,
			     this->smgr, this->guienv, this->saves);
  this->menu->setModelProperties();
  this->play = this->menu->launchModel(this->device);
  if (this->play)
    this->gameEngine = new GameNamespace::GameEngine(this->smgr, this->driver,
						   this->loadDir("./ressources/textures/ground/", ".bmp").size(),
						   this->loadDir("./ressources/shapes/", ".dae").size(),
						   this->device);
  return ;
}

void						Core::launchGame()
{
  this->device->getCursorControl()->setVisible(false);
  this->gameEngine->setModelProperties();
  this->play = this->gameEngine->launchModel(this->device);
}

void						Core::launch()
{
  this->launchSplashScreen();
  while(device->run())
    {
      this->launchMenu();
      if (this->play)
	{
	  this->launchGame();
	  if (!this->play)
	    break;
	} else
	break;
    }
}
