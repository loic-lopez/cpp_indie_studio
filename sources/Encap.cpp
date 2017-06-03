//
// Encap.cpp for Encap.cpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 14:06:03 2017 Loïc Dupil
// Last update Wed May  3 14:15:20 2017 Loïc Dupil
//

#include "Encap.hpp"

DIR		*Encap::c_opendir(const char *path)
{
  return (opendir(path));
}

int		Encap::c_closedir(DIR *dir)
{
  return (closedir(dir));
}

struct dirent	*Encap::c_readdir(DIR *dir)
{
  return (readdir(dir));
}

int		Encap::c_stat(const char *path, struct stat *sb)
{
  return (stat(path, sb));
}
