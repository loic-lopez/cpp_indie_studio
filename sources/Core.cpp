//
// Core.cpp for Core.cpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 13:51:01 2017 Loïc Dupil
// Last update Thu May  4 17:04:15 2017 Stanislas Deneubourg
//

#include "Core.hpp"
#include "Encap.hpp"

int		check_extension_file(std::string filename, std::string extension)
{
  std::string   tmp = filename;
  std::size_t   pos = tmp.find_last_of(".");

  if (pos == std::string::npos || tmp.substr(pos, tmp.size()) != extension)
    {
      std::cout << "Error: Bad file extension." << std::endl;
      return (-1);
    }
  return (0);
}

Core::Core()
{
  this->device = irr::createDevice(irr::video::EDT_OPENGL,
                                                  irr::core::dimension2d<irr::u32>(1920,1080), 32);
  this->driver = device->getVideoDriver();
  this->smgr = device->getSceneManager();
  this->smgr->addLightSceneNode(0, irr::core::vector3df(-15,5,-105),
			  irr::video::SColorf(0.5f, 0.5f, 0.5f));
  
  // set ambient light
  this->smgr->setAmbientLight(irr::video::SColor(0,60,60,60));
  this->device->setWindowCaption(L"Irrlicht Engine - Worms3D");
  this->device->getCursorControl()->setVisible(false);
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
  
  if ((dir = Encap::c_opendir("saves/")) == NULL)
    {
      std::cerr << "No saves directory" << std::endl;
      return ;
    }
  while ((direntp = Encap::c_readdir(dir)) != NULL)
    {
      file = direntp->d_name;
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (check_extension_file(file, ".xml") == 0))
	    this->saves.push_back(direntp->d_name);
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
  
  if ((dir = Encap::c_opendir("ressources/sounds/")) == NULL)
    {
      std::cerr << "No saves directory" << std::endl;
      return ;
    }
  while ((direntp = Encap::c_readdir(dir)) != NULL)
    {
      file = direntp->d_name;
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (check_extension_file(file, ".wav") == 0))
	    this->saves.push_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);  
}

std::vector<std::string>			Core::loadDir(const std::string &path, const std::string &file_extension)
{
  DIR				*dir;
  struct dirent			*direntp;
  std::vector<std::string>	content;

  if ((dir = Encap::c_opendir(path.c_str())) == NULL)
    {
      std::cerr << path << ": No such file or directory directory" << std::endl;
      return (content);
    }
  while ((direntp = Encap::c_readdir(dir)) != NULL)
    {
      
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (check_extension_file(direntp->d_name, file_extension) == 0))
	    content.push_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
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
  this->gameEngine = new GameNamespace::GameEngine(this->smgr, this->driver,
				    this->loadDir("./ressources/textures/ground/", ".bmp").size(),
				    this->loadDir("./ressources/shapes/", ".dae").size());
  return ;
}

void						Core::launchGame()
{
  this->device->getCursorControl()->setVisible(false);
  this->gameEngine->launchModel(this->device);
}

void						Core::launch()
{
  this->launchSplashScreen();
  while(device->run())
    {
      this->launchMenu();
      this->launchGame();
    }
}
