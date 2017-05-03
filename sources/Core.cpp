//
// Core.cpp for Core.cpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 13:51:01 2017 Loïc Dupil
// Last update Wed May  3 18:56:04 2017 Stanislas Deneubourg
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

std::vector<std::string>			Core::loadDir(const std::string &path)
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
	  if (direntp->d_type != 4)
	    content.push_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
  return (content);
}

void						Core::launchSplashScreen()
{
  std::unique_ptr<IModel>			splashScreen(new SplashScreen);

  
}

void						Core::launchMenu()
{
  return ;
}

void						Core::launchGame()
{
  return ;
}

void						Core::launch()
{

}
