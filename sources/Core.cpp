//
// Core.cpp for Core.cpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 13:51:01 2017 Loïc Dupil
// Last update Wed May  3 17:33:49 2017 Loïc Dupil
//

#include "Core.hpp"
#include "Encap.hpp"

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
	  if (direntp->d_type != 4 && (file.find(".xml") != std::string::npos))
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
	  if (direntp->d_type != 4 && (file.find(".oav") != std::string::npos))
	    this->saves.push_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);  
}
